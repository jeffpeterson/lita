#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "common.h"
#include "compiler.h"
#include "debug.h"
#include "lib.h"
#include "memory.h"
#include "native.h"
#include "object.h"
#include "string.h"
#include "term.h"
#include "tuple.h"
#include "vm.h"

VM vm;

static void resetStack() {
  vm.stackTop = vm.stackHigh = vm.stack;
  vm.frameCount = 0;
  vm.openUpvalues = NULL;
}

InterpretResult runtimeError(const char *format, ...) {
  va_list args;
  va_start(args, format);
  vfprintf(stderr, format, args);
  va_end(args);
  fputs("\n", stderr);

  fprintf(stderr, "%d frames:\n", vm.frameCount);
  for (int i = vm.frameCount - 1; i >= 0; i--) {
    CallFrame *frame = &vm.frames[i];
    ObjFun *fun = frame->closure->fun;
    size_t instruction = frame->ip - fun->chunk.code - 1;
    int line = fun->chunk.lines[instruction];
    fprintf(stderr, "[line %d] in ", line);
    fprintFunction(stderr, "ObjFun", fun);
    fprintf(stderr, "\n");
  }

  resetStack();
  return INTERPRET_RUNTIME_ERROR;
}

void assertOkResult(InterpretResult result) {
  if (result == INTERPRET_COMPILE_ERROR) exit(65);

  if (result == INTERPRET_RUNTIME_ERROR) exit(70);
}

void crash(const char *str) {
  runtimeError("Crash: %s", str);
  freeVM();
  exit(70);
}

void panic(const char *str) {
  fprintf(stderr, "Panic: %s", str);
  exit(70);
}

Value setGlobal(Value name, Value val) {
  tableSet(&vm.globals, push(name), push(val));
  popn(2);
  return val;
}

Value global(Value name) {
  return tableGet(&vm.globals, name, &name) ? name : nil;
}

void initVM() {
  resetStack();

  vm.objects = NULL;
  vm.bytesAllocated = 0;
  /** Start collecting after 100MB is allocated. */
  vm.nextGC = 100 * 1024 * 1024;

  vm.grayCount = 0;
  vm.grayCapacity = 0;
  vm.grayStack = NULL;

  initTable(&vm.globals);
  initTable(&vm.interned);
  initTable(&vm.keep);

  vm.str.init = newString("init");

  vm.Any = nil;
  vm.Bool = nil;
  vm.Class = nil;
  vm.Error = nil;
  vm.Function = nil;
  vm.Method = nil;
  vm.NativeFunction = nil;
  vm.Nil = nil;
  vm.Number = nil;
  vm.Object = nil;
  vm.Range = nil;
  vm.String = nil;
  vm.Table = nil;
  vm.Tuple = nil;

  // fprintTable(stderr, &vm.globals);
  // pp(global(str("hash")));
  // pp(global(str("Any")));
  // pp(global(str("Object")));
  // pp(global(str("Number")));

  /** Start collecting after 1MB is allocated. */
  vm.nextGC = 1024 * 1024;
}

InterpretResult bootVM() { return defineNatives(); }

void freeVM() {
  vm.str.init = NULL;
  freeTable(&vm.interned);
  freeObjects();
}

Value push(Value value) {
  *vm.stackTop = value;
  vm.stackTop++;

  if (vm.stackTop > vm.stackHigh) vm.stackHigh = vm.stackTop;

  return value;
}

static Value peek(int distance) { return vm.stackTop[-1 - distance]; }

Value pop() {
  vm.stackTop--;
  return *vm.stackTop;
}

Value pope(Value val) {
  pop();
  return val;
}

inline Value *popn(u8 n) {
  vm.stackTop -= n;
  return vm.stackTop;
}

void vm_swap(u8 a, u8 b) {
  Value aa = peek(a);
  vm.stackTop[-1 - a] = peek(b);
  vm.stackTop[-1 - b] = aa;
}

/**
 * Invoke a closure with arguments on the stack.
 *
 * Returns whether or not the call was successful.
 */
static bool call(ObjClosure *closure, int argCount) {
  ObjFun *fun = closure->fun;

  if (argCount != fun->arity) {
    runtimeError("Expected %d arguments but got %d.", fun->arity, argCount);
    return false;
  }

  if (vm.frameCount == FRAMES_MAX) {
    runtimeError("Call stack overflow.");
    return false;
  }

  CallFrame *frame = &vm.frames[vm.frameCount++];
  frame->closure = closure;
  frame->ip = fun->chunk.code; // Start instruction pointer at function's code.

  /**
   * Account for args and the receiver (if method).
   * stack: [..., this, arg1, arg2]
   *     receiver-^               ^-stackTop
   */
  frame->slots = vm.stackTop - argCount - 1;
  return true;
}

ObjClass *valueClass(Value v) {
  const char *name = NULL;

  if (IS_OBJ(v)) {
    Obj *obj = AS_OBJ(v);

    if (obj->type == OBJ_INSTANCE) return ((ObjInstance *)obj)->klass;

    name = objInfo[obj->type].className;
  } else {
    name = IS_NIL(v)      ? "Nil"
           : IS_NUMBER(v) ? "Number"
           : IS_BOOL(v)   ? "Bool"
                          : "Any";
  }

  if (name) {
    Value klass = global(string(name));

    if (IS_CLASS(klass)) return AS_CLASS(klass);
  }

  return NULL;
}

/**
 * Invoke some Value as a function.
 *
 * Returns whether or not the call was successful.
 */
static bool callValue(Value callee, int argCount) {
  if (IS_OBJ(callee)) {
    switch (OBJ_TYPE(callee)) {
    case OBJ_BOUND: {
      ObjBound *bound = AS_BOUND(callee);
      vm.stackTop[-argCount - 1] = bound->receiver;
      return call(bound->method, argCount);
    }

    case OBJ_CLASS: {
      vm.stackTop[-argCount - 1] = OBJ_VAL(newInstance(AS_CLASS(callee)));

      let init = findMethod(callee, obj(vm.str.init));

      if (notNil(init)) {
        return call(asFn(init), argCount);
      } else if (argCount != 0) {
        return !runtimeError("Expected 0 arguments but got %d.", argCount);
      }

      return true;
    }

    case OBJ_CLOSURE:
      return call(AS_CLOSURE(callee), argCount);

    case OBJ_NATIVE: {
      ObjNative *native = AS_NATIVE(callee);

      if (argCount < native->arity) {
        runtimeError("Expected %d arguments but got %d.", native->arity,
                     argCount);
        return false;
      }

      Value result =
          native->fun(peek(argCount), argCount, vm.stackTop - argCount);
      vm.stackTop -= argCount + 1;
      push(result);
      return true;
    }

    default:
      break; // Non-callable object type.
    }
  }

  if (argCount == 1) {
    let b = pop();
    let a = pop();
    push(multiply(a, b));
    return true;
  }

  return false;
}

static bool invokeFromClass(ObjClass *klass, ObjString *name, int argCount) {
  Value method;

  if (!tableGet(&klass->methods, OBJ_VAL(name), &method)) {
    if (!klass->parent) return false;

    return invokeFromClass(klass->parent, name, argCount);
  }

  if (IS_CLOSURE(method)) return call(AS_CLOSURE(method), argCount);
  else return callValue(method, argCount);
}

/** [argCount self][0 ...args] */
static InterpretResult vm_invoke(Value name, int argCount) {
  Value receiver = peek(argCount);

  // Value value = find(receiver, name);

  if (IS_INSTANCE(receiver)) {
    ObjInstance *inst = AS_INSTANCE(receiver);

    Value value;
    if (tableGet(&inst->fields, OBJ_VAL(name), &value)) {
      vm.stackTop[-argCount - 1] = value;
      return !callValue(value, argCount);
    }
  }

  ObjClass *klass = valueClass(receiver);
  // printf("invoke: %s_%s()\n", klass->name->chars, name->chars);
  if (!invokeFromClass(klass, asStr(name), argCount)) {
    return runtimeError("Undefined property '%s' on %s.", asStr(name)->chars,
                        klass->name->chars);
  }

  return INTERPRET_OK;
}

static bool bindMethod(ObjClass *klass, ObjString *name) {
  Value method;
  if (!tableGet(&klass->methods, OBJ_VAL(name), &method)) {
    // Todo: store error in case of `!` postfix operator.
    return false;
  }

  ObjBound *bound = newBound(peek(0), AS_CLOSURE(method));

  pop();
  push(OBJ_VAL(bound));
  return true;
}

static ObjUpvalue *captureUpvalue(Value *local) {
  ObjUpvalue *prevUpvalue = NULL;
  ObjUpvalue *upvalue = vm.openUpvalues;

  while (upvalue != NULL && upvalue->location > local) {
    prevUpvalue = upvalue;
    upvalue = upvalue->next;
  }

  if (upvalue != NULL && upvalue->location == local) return upvalue;

  ObjUpvalue *createdUpvalue = newUpvalue(local);
  createdUpvalue->next = upvalue;

  if (prevUpvalue == NULL) vm.openUpvalues = createdUpvalue;
  else prevUpvalue->next = createdUpvalue;

  return createdUpvalue;
}

/**
 * Takes a pointer to the stack and closes all upvalues pointing to values
 * above this pointer.
 */
static void closeUpvalues(Value *last) {
  while (vm.openUpvalues != NULL && vm.openUpvalues->location >= last) {
    ObjUpvalue *upvalue = vm.openUpvalues;

    // Move the existing value into `closed`.
    upvalue->closed = *upvalue->location;

    // Point `location` to the new `closed` value.
    upvalue->location = &upvalue->closed;

    // Remove this upvalue from the VM's list of open upvalues.
    vm.openUpvalues = upvalue->next;
  }
}

static void defineMethod(ObjString *name) {
  Value method = peek(0);
  ObjClass *klass = AS_CLASS(peek(1));
  tableSet(&klass->methods, OBJ_VAL(name), method);
  pop();
}

static bool isFalsey(Value value) {
  return IS_NIL(value) || (IS_BOOL(value) && !AS_BOOL(value));
}

/** [1 a][0 b] -> [0 result] */
InterpretResult vm_add() {
  Value b = peek(0);
  Value a = peek(1);
  Value res = nil;

  if (isNum(a) && isNum(b)) res = num(AS_NUMBER(a) + AS_NUMBER(b));

  if (isNil(res)) return vm_invoke(string("+"), 1);

  popn(2);
  push(res);
  return INTERPRET_OK;
}

InterpretResult vm_assert(Value src) {
  let value = pop();
  if (isFalsey(value)) {
    fprintf(stderr, "\n\n");
    fprintValue(stderr, src);
    fprintf(stderr, " //=> ");
    fprintValue(stderr, value);
    printf("\n");
    return runtimeError(FG_RED "Assertion failed." FG_DEFAULT);
  }

#ifdef DEBUG_ASSERTS
  fprintf(stderr, "%s", FG_GREEN "." FG_DEFAULT);
#endif

  return INTERPRET_OK;
}

InterpretResult vm_call(int argc) {
  return callValue(peek(argc), argc) ? INTERPRET_OK : INTERPRET_RUNTIME_ERROR;
}

// [0 self] -> [0 value]
InterpretResult vm_get(Value name) {
  return arity(push(get(pop(), name))) == 0 ? vm_call(0) : INTERPRET_OK;
}

// [0 self] -> [0 value]
InterpretResult vm_get_global(Value name) {
  let value;

  if (!tableGet(&vm.globals, name, &value)) {
    return runtimeError("Cannot get undefined variable '%s'.",
                        AS_STRING(name)->chars);
  }
  push(value);
  return INTERPRET_OK;
}

/** [1 start][0 end] -> [0 range] */
void vm_range() {
  let b = pop();
  let a = pop();
  push(range(a, b));
}

/** [length ...args][0 arg] -> [0 tuple] */
void vm_tuple(u8 length) {
  ObjTuple *tuple = copyTuple(vm.stackTop - length, length);
  popn(length);
  push(OBJ_VAL(tuple));
}

static InterpretResult run() {
  register CallFrame *frame = &vm.frames[vm.frameCount - 1];

#define READ_BYTE() (*frame->ip++)
/** Update the cached frame variable. Idempotent. */
#define SYNC_FRAME() (frame = &vm.frames[vm.frameCount - 1])
#define READ_SHORT()                                                           \
  (frame->ip += 2, (uint16_t)((frame->ip[-2] << 8) | frame->ip[-1]))
#define READ_CONSTANT()                                                        \
  (frame->closure->fun->chunk.constants.values[READ_BYTE()])
#define READ_STRING() AS_STRING(READ_CONSTANT())
#define BINARY_OP(valueType, op)                                               \
  do {                                                                         \
    if (!IS_NUMBER(peek(0)) || !IS_NUMBER(peek(1))) {                          \
      runtimeError("Operands must be numbers.");                               \
      return INTERPRET_RUNTIME_ERROR;                                          \
    }                                                                          \
    double b = AS_NUMBER(pop());                                               \
    double a = AS_NUMBER(pop());                                               \
    push(valueType(a op b));                                                   \
  } while (false)

  for (;;) {
#ifdef DEBUG_TRACE_EXECUTION
    debugExecution();
#endif

    vm.stackHigh = vm.stackTop;

    InterpretResult err;
    uint8_t instruction;
    switch (instruction = READ_BYTE()) {

    case OP_CONSTANT: {
      push(READ_CONSTANT());
      break;
    }
    case OP_NIL:
      push(NIL_VAL);
      break;
    case OP_TRUE:
      push(BOOL_VAL(true));
      break;
    case OP_FALSE:
      push(BOOL_VAL(false));
      break;

    case OP_PEEK:
      push(peek(READ_BYTE()));
      break;
    case OP_POP:
      pop();
      break;
    case OP_POPN:
      popn(READ_BYTE());
      break;
    case OP_SWAP: {
      uint8_t args = READ_BYTE();
      vm_swap(args & 0x0f, args >> 4);
      break;
    }
    case OP_DEFAULT:
      if (IS_NIL(peek(0))) {
        pop();
        push(READ_CONSTANT());
      } else {
        // Skip constant byte.
        frame->ip++;
      }
      break;

    case OP_RANGE:
      vm_range();
      break;

    case OP_TUPLE:
      vm_tuple(READ_BYTE());
      break;

    case OP_DEFINE_GLOBAL:
      tableSet(&vm.globals, READ_CONSTANT(), pop());
      break;

    case OP_GET_GLOBAL:
      if ((err = vm_get_global(READ_CONSTANT()))) return err;
      break;

    case OP_SET_GLOBAL: {
      Value name = READ_CONSTANT();
      if (tableSet(&vm.globals, name, peek(0))) {
        // This is a new key and hasn't been defined.
        tableDelete(&vm.globals, name);
        return runtimeError("Cannot set undefined variable '%s'.",
                            AS_STRING(name)->chars);
      }
      break;
    }

    case OP_GET_LOCAL: {
      uint8_t slot = READ_BYTE();
      push(frame->slots[slot]);
      break;
    }
    case OP_SET_LOCAL: {
      uint8_t slot = READ_BYTE();
      frame->slots[slot] = peek(0);
      break;
    }

    case OP_GET_PROPERTY: {
      vm_get(READ_CONSTANT());
      SYNC_FRAME();
      break;
    }
    case OP_SET_PROPERTY: { // [1 self][0 value] -> [0 value]
      let name = READ_CONSTANT();

      if (!IS_INSTANCE(peek(1))) {
        return runtimeError("Only instances have properties.");
      }

      ObjInstance *inst = AS_INSTANCE(peek(1));

      // Keep on stack to prevent GC collection.
      Value value = peek(0);

      // Assigning 'nil' is deletion.
      if (IS_NIL(value)) tableDelete(&inst->fields, name);
      else tableSet(&inst->fields, name, value);

      popn(2);
      push(value);
      break;
    }

    case OP_GET_UPVALUE: {
      uint8_t slot = READ_BYTE();
      push(*frame->closure->upvalues[slot]->location);
      break;
    }

    case OP_SET_UPVALUE: {
      uint8_t slot = READ_BYTE();
      *frame->closure->upvalues[slot]->location = peek(0);
      break;
    }

    case OP_EQUAL: {
      Value b = pop();
      Value a = pop();
      push(BOOL_VAL(valuesEqual(a, b)));
      break;
    }
    case OP_GREATER:
      BINARY_OP(BOOL_VAL, >);
      break;
    case OP_LESS:
      BINARY_OP(BOOL_VAL, <);
      break;

    case OP_ADD:
      if ((err = vm_add())) return err;
      SYNC_FRAME();
      break;
    case OP_SUBTRACT:
      BINARY_OP(NUMBER_VAL, -);
      break;
    case OP_MULTIPLY:
      BINARY_OP(NUMBER_VAL, *);
      break;
    case OP_DIVIDE:
      BINARY_OP(NUMBER_VAL, /);
      break;
    case OP_NOT:
      push(BOOL_VAL(isFalsey(pop())));
      break;
    case OP_NEGATE:
      if (!IS_NUMBER(peek(0))) {
        runtimeError("Operand must be a number.");
        return INTERPRET_RUNTIME_ERROR;
      }
      push(NUMBER_VAL(-AS_NUMBER(pop())));
      break;

    case OP_JUMP: {
      uint16_t offset = READ_SHORT();
      frame->ip += offset;
      break;
    }
    case OP_JUMP_IF_FALSE: {
      uint16_t offset = READ_SHORT();
      if (isFalsey(peek(0))) frame->ip += offset;
      break;
    }
    case OP_LOOP: {
      uint16_t offset = READ_SHORT();
      frame->ip -= offset;
      break;
    }

    case OP_CALL: // [argc fn][1 arg1][0 ...args ]
      vm_call(READ_BYTE());
      SYNC_FRAME();
      break;

    case OP_CLASS: { // []
      let name = READ_CONSTANT();
      bool isLocal = (bool)READ_BYTE();
      let klass;

      // Re-open existing global classes
      if (isLocal || !tableGet(&vm.globals, name, &klass)) {
        klass = class(name);
        if (!isLocal) tableSet(&vm.globals, name, klass);
      }

      push(klass);
      break;
    }

    case OP_INHERIT: { // [1 class][0 super]
      if (!IS_CLASS(peek(0))) {
        return runtimeError("Superclass must be a class.");
      }

      ObjClass *superclass = AS_CLASS(peek(0));
      ObjClass *subclass = AS_CLASS(peek(1));
      subclass->parent = superclass;
      // tableAddAll(&superclass->methods, &subclass->methods);
      break;
    }

    case OP_GET_SUPER: {
      ObjString *name = READ_STRING();
      ObjClass *superclass = AS_CLASS(pop());

      if (!bindMethod(superclass, name)) return INTERPRET_RUNTIME_ERROR;
      break;
    }

    case OP_METHOD: // (name) [1 class][0 closure] -> [0 class]
      defineMethod(READ_STRING());
      break;

    case OP_INVOKE: { // [n self][0 ...args]
      let name = READ_CONSTANT();
      u8 argc = READ_BYTE();
      if ((err = vm_invoke(name, argc))) return err;
      SYNC_FRAME();
      break;
    }

    case OP_SUPER_INVOKE: {
      ObjClass *superclass = AS_CLASS(pop());

      if (!invokeFromClass(superclass, READ_STRING(), READ_BYTE()))
        return INTERPRET_RUNTIME_ERROR;

      SYNC_FRAME();
      break;
    }

    case OP_CLOSURE: {
      ObjFun *fun = AS_FUN(READ_CONSTANT());
      ObjClosure *closure = newClosure(fun);
      push(OBJ_VAL(closure));

      for (int i = 0; i < closure->upvalueCount; i++) {
        uint8_t isLocal = READ_BYTE();
        uint8_t index = READ_BYTE();

        if (isLocal)
          closure->upvalues[i] = captureUpvalue(frame->slots + index);
        else closure->upvalues[i] = frame->closure->upvalues[index];
      }

      break;
    }

    case OP_CLOSE_UPVALUE:
      closeUpvalues(vm.stackTop - 1);
      pop();
      break;

    case OP_ASSERT:
      if ((err = vm_assert(READ_CONSTANT()))) return err;
      break;

    case OP_PRINT:
      fprintValue(stdout, pop());
      printf("\n");
      break;

    case OP_RETURN: {
      Value result = pop(); // Pop return value off stack.
      closeUpvalues(frame->slots);
      vm.frameCount--;

      if (vm.frameCount == 0) {
        pop(); // Pop <script> function off stack.
        return INTERPRET_OK;
      }

      vm.stackTop = frame->slots;
      push(result);
      SYNC_FRAME();
      break;
    }

    default:
      runtimeError("Error: Instruction not implemented: 0x%02x.", instruction);
      return INTERPRET_RUNTIME_ERROR;
    }
  }

#undef READ_BYTE
#undef READ_SHORT
#undef READ_CONSTANT
#undef READ_STRING
#undef BINARY_OP
#undef SYNC_FRAME
}

InterpretResult runFun(ObjFun *fun) {
  if (fun == NULL) return INTERPRET_COMPILE_ERROR;

  push(OBJ_VAL(fun));
  ObjClosure *closure = newClosure(fun);
  pop();
  push(OBJ_VAL(closure));
  call(closure, 0);

  return run();
}

InterpretResult interpret(const char *source, ObjString *name) {
  return runFun(compile(source, name));
}

Value intern(Value val) {
  push(val);
  tableSet(&vm.interned, val, TRUE_VAL);
  return pop();
}

Obj *getInterned(Hash *hash, ObjType type, const char *bytes, int length) {
  *hash = hashBytes(bytes, length);
  return tableFindObj(&vm.interned, type, bytes, length, *hash);
}
