#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "array.h"
#include "common.h"
#include "compiler.h"
#include "debug.h"
#include "io.h"
#include "iterator.h"
#include "lib.h"
#include "memory.h"
#include "native.h"
#include "object.h"
#include "range.h"
#include "regex.h"
#include "string.h"
#include "system.h"
#include "term.h"
#include "tuple.h"
#include "vm.h"

VM vm;
InterpretResult ok = INTERPRET_OK;

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
    inspect_function(stderr, "ObjFun", fun);
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

Value global_class(const char *name) {
  let vname = string(name);
  let klass = global(vname);
  if (is_class(klass)) return klass;
  return setGlobal(vname, class(vname));
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

  vm.str.init = new_string("init");

  // inspect_table(stderr, &vm.globals);
  // pp(global(str("hash")));
  // pp(global(str("Any")));
  // pp(global(str("Object")));
  // pp(global(str("Number")));

  /** Start collecting after 1MB is allocated. */
  vm.nextGC = 1024 * 1024;
}

static void register_def(const ObjDef *def) {
  if (!def->class_name) error("def must have a class_name");

  let klass = global_class(def->class_name);

  if (def->natives) def->natives(klass);
}

InterpretResult bootVM() {
  InterpretResult result = defineNatives();

  register_def(&Iterator);
  register_def(&String);
  register_def(&array_def);
  register_def(&io_def);
  register_def(&range_def);
  register_def(&Regex);
  register_def(&tuple_def);

  setGlobal(str("stdin"), io(stdin, UNOWNED));
  setGlobal(str("stdout"), io(stdout, UNOWNED));
  setGlobal(str("stderr"), io(stderr, UNOWNED));

  return result;
}

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

// invoke the method on this
Value send(Value this, Value method_name, int argc, ...) {
  push(this);
  va_list args;

  va_start(args, argc);
  for (int i = 0; i < argc; i++) push(va_arg(args, Value));
  va_end(args);

  vm_invoke(method_name, argc);
  return pop();
}

void vm_swap(u8 a, u8 b) {
  Value aa = peek(a);
  vm.stackTop[-1 - a] = peek(b);
  vm.stackTop[-1 - b] = aa;
}

/**
 * Move the instruction pointer (ip) to a new a closure along with arguments on
 * the stack.
 *
 * Returns whether or not the call was successful.
 */
static bool move_into_closure(ObjClosure *closure, int argCount) {
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
   * Account for args and the receiver if method, else the callee.
   * stack: [..., this, arg1, arg2]
   *     receiver-^               ^-stackTop
   */
  frame->slots = vm.stackTop - argCount - 1;
  return true;
}

ObjClass *valueClass(Value v) {
  const char *name = NULL;

  if (is_obj(v)) {
    Obj *obj = AS_OBJ(v);

    if (obj->klass) return obj->klass;
    if (obj->def && obj->def->class_name) name = obj->def->class_name;
    else name = objInfo[obj->type].className;
  } else {
    name = is_nil(v)    ? "Nil"
           : is_num(v)  ? "Number"
           : is_bool(v) ? "Bool"
                        : "Any";
  }

  if (name) {
    Value klass = global(string(name));

    if (is_class(klass)) return AS_CLASS(klass);
  }

  return NULL;
}

/**
 * Invoke some Value as a function.
 *
 * Returns whether or not the call was successful.
 */
bool call_value(Value callee, int argCount) {
  trace("callee", callee);

  if (is_obj(callee)) {
    switch (obj_type(callee)) {
    case OBJ_BOUND: {
      ObjBound *bound = AS_BOUND(callee);
      vm.stackTop[-argCount - 1] = bound->receiver;
      return call_value(bound->method, argCount);
    }

    case OBJ_CLASS: {
      vm.stackTop[-argCount - 1] = OBJ_VAL(new_instance(AS_CLASS(callee)));

      let init = findMethod(callee, obj(vm.str.init));

      if (not_nil(init)) {
        return move_into_closure(as_closure(init), argCount);
      } else if (argCount != 0) {
        return !runtimeError("Class expects no arguments but got %d.",
                             argCount);
      }

      return true;
    }

    case OBJ_CLOSURE: return move_into_closure(AS_CLOSURE(callee), argCount);

    case OBJ_NATIVE: {
      ObjNative *native = AS_NATIVE(callee);

      if (argCount < native->arity) {
        runtimeError("Expected %d arguments but got %d.", native->arity,
                     argCount);
        return false;
      }

      // TODO: This is broken. Native functions are called immediately, but
      // closures are simply moved into a call frame but remain uncalled until
      // we next return to the VM run() function. Instead, we should make a kind
      // of frame for native functions and use move_into_native(). Additionally,
      // we should stop returning Values from all helper functions. Everything
      // must communicate via the stack.
      Value result =
          native->fun(peek(argCount), argCount, vm.stackTop - argCount);
      popn(argCount + 1);
      push(result);
      return true;
    }

    default: break; // Non-callable object type.
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

  return call_value(method, argCount);
}

/** [argCount self][0 ...args] */
InterpretResult vm_invoke(Value name, int argCount) {
  Value receiver = peek(argCount);

  // Value value = find(receiver, name);

  if (is_obj(receiver)) {
    Obj *obj = AS_OBJ(receiver);

    Value value;
    if (tableGet(&obj->fields, name, &value)) {
      vm.stackTop[-argCount - 1] = value;
      return !call_value(value, argCount);
    }
  }

  ObjClass *klass = valueClass(receiver);

#ifdef DEBUG_TRACE_EXECUTION
  printf("invoke: %s.%s()\n", klass->name->chars, as_string(name)->chars);
#endif

  if (!invokeFromClass(klass, as_string(name), argCount)) {
    return runtimeError("Undefined property '%s' on %s.",
                        as_string(name)->chars, klass->name->chars);
  }

  return INTERPRET_OK;
}

static bool bindMethod(ObjClass *klass, ObjString *name) {
  Value method;
  if (!tableGet(&klass->methods, OBJ_VAL(name), &method)) {
    // Todo: store error in case of `!` postfix operator.
    return false;
  }

  push(bindFn(pop(), method));
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
  return is_nil(value) || (is_bool(value) && !AS_BOOL(value));
}

/** [1 a][0 b] -> [0 result] */
InterpretResult vm_add() {
  Value b = peek(0);
  Value a = peek(1);

  if (!is_num(a) || !is_num(b)) return vm_invoke(string("+"), 1);

  popn(2);
  push(num(AS_NUMBER(a) + AS_NUMBER(b)));
  return INTERPRET_OK;
}

/** [1 a][0 b] -> [0 result] */
InterpretResult vm_multiply() {
  Value b = peek(0);
  Value a = peek(1);

  if (!is_num(a) || !is_num(b)) return vm_invoke(string("*"), 1);

  popn(2);
  push(num(AS_NUMBER(a) * AS_NUMBER(b)));
  return INTERPRET_OK;
}

/** [length ...args][0 arg] -> [0 array] */
void vm_array(u32 length) {
  ObjArray *arr = copy_array(vm.stackTop - length, length);
  popn(length);
  push(OBJ_VAL(arr));
}

InterpretResult vm_assert(Value src) {
  let value = peek(0);
  let rhs = peek(-1);

#ifdef DEBUG_ASSERT_CODE
  inspect_value(stderr, src);
  fprintf(stderr, "\n");
#endif

  if (isFalsey(value)) {
    fprintf(stderr, "\n\n");
    fstring_format(stderr, "{} -> {}", src, value);
    inspect_value(stderr, rhs);
    fprintf(stderr, "\nStack:\t");
    debugStack();
    fprintf(stderr, "\n\n");

    return runtimeError(FG_RED "Assertion failed.\n" FG_DEFAULT);
  }

#ifdef DEBUG_ASSERTS
  fprintf(stderr, "%s", FG_GREEN "." FG_DEFAULT);
#endif

  return INTERPRET_OK;
}

// [argc fn][1 arg1][0 ...args ] -> [0 return]
InterpretResult vm_call(int argc) {
  return call_value(peek(argc), argc) ? INTERPRET_OK : INTERPRET_RUNTIME_ERROR;
}

/** [1 a][0 b] -> [0 result] */
InterpretResult vm_divide() {
  Value b = peek(0);
  Value a = peek(1);
  Value res = nil;

  if (is_num(a) && is_num(b)) res = num(AS_NUMBER(a) / AS_NUMBER(b));

  if (is_nil(res)) return vm_invoke(string("/"), 1);

  popn(2);
  push(res);
  return INTERPRET_OK;
}

// [] -> [0 value]
InterpretResult vm_get_global(Value name) {
  let value;

  if (!tableGet(&vm.globals, name, &value)) {
    if (is_nil(value = get_env(name)))
      return runtimeError("Cannot get undefined variable '%s'.",
                          as_string(name)->chars);
  }
  push(value);
  return INTERPRET_OK;
}

// [0 value] -> [0 value]
InterpretResult vm_set_global(Value name) {
  if (tableSet(&vm.globals, name, peek(0))) {
    // This is a new key and hasn't been defined.
    tableDelete(&vm.globals, name);
    return runtimeError("Cannot set undefined variable '%s'.",
                        AS_STRING(name)->chars);
  }
  return INTERPRET_OK;
}

// [0 self] -> [0 value]
InterpretResult vm_get_property(Value name) {
  return arity(push(get(pop(), name))) == 0 ? vm_call(0) : INTERPRET_OK;
}

// [1 self][0 value] -> [0 value]
InterpretResult vm_set_property(Value name) {
  if (!is_obj(peek(1))) {
    return runtimeError("Only objects have properties.");
  }

  Obj *obj = AS_OBJ(peek(1));

  // Keep on stack to prevent GC collection.
  Value value = peek(0);

  // Assigning 'nil' is deletion.
  if (is_nil(value)) tableDelete(&obj->fields, name);
  else tableSet(&obj->fields, name, value);

  popn(2);
  push(value);
  return INTERPRET_OK;
}

// [0 self] -> [0 value]
InterpretResult vm_get_var(Value name) {
  if (has(peek(0), name)) return vm_get_property(name);
  pop();
  return vm_get_global(name);
}

// [1 self][0 value] -> [0 value]
InterpretResult vm_set_var(Value name) {
  if (has(peek(0), name)) return vm_set_property(name);
  vm_swap(0, 1);
  pop();
  return vm_set_global(name);
}

Value vm_peek(int idx) { return peek(idx); }

/** [1 start][0 end] -> [0 range] */
void vm_range() {
  let b = pop();
  let a = pop();
  push(range(a, b));
}

/** [length ...args][0 arg] -> [0 tuple] */
void vm_tuple(u8 length) {
  ObjTuple *tuple = copy_tuple(vm.stackTop - length, length);
  popn(length);
  push(OBJ_VAL(tuple));
}

static InterpretResult vm_run() {
  int starting_frame_count = vm.frameCount - 1;
  register CallFrame *frame = &vm.frames[starting_frame_count];

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
    if (!is_num(peek(0)) || !is_num(peek(1))) {                                \
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
    case OP_NIL: push(NIL_VAL); break;
    case OP_TRUE: push(BOOL_VAL(true)); break;
    case OP_FALSE: push(BOOL_VAL(false)); break;

    case OP_PEEK: push(peek(READ_BYTE())); break;
    case OP_POP: pop(); break;
    case OP_POPN: popn(READ_BYTE()); break;
    case OP_SWAP: {
      uint8_t args = READ_BYTE();
      vm_swap(args & 0x0f, args >> 4);
      break;
    }
    case OP_DEFAULT:
      if (is_nil(peek(0))) {
        pop();
        push(READ_CONSTANT());
      } else {
        // Skip constant byte.
        frame->ip++;
      }
      break;

    case OP_RANGE: vm_range(); break;
    case OP_ARRAY: vm_array(AS_NUMBER(READ_CONSTANT())); break;
    case OP_TUPLE: vm_tuple(READ_BYTE()); break;

    case OP_DEFINE_GLOBAL: tableSet(&vm.globals, READ_CONSTANT(), pop()); break;

    case OP_GET_GLOBAL:
      if ((err = vm_get_global(READ_CONSTANT()))) return err;
      break;

    case OP_SET_GLOBAL:
      if ((err = vm_set_global(READ_CONSTANT()))) return err;
      break;

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

    case OP_GET_PROPERTY:
      if ((err = vm_get_property(READ_CONSTANT()))) return err;
      SYNC_FRAME();
      break;
    case OP_SET_PROPERTY:
      if ((err = vm_set_property(READ_CONSTANT()))) return err;
      SYNC_FRAME();
      break;

    case OP_GET_VAR:
      if ((err = vm_get_var(READ_CONSTANT()))) return err;
      SYNC_FRAME();
      break;
    case OP_SET_VAR: // [1 self][0 value] -> [0 value]
      if ((err = vm_set_var(READ_CONSTANT()))) return err;
      SYNC_FRAME();
      break;

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

    case OP_MATCH: // TODO: More sophisticated matching.
    case OP_EQUAL:
      vm_invoke(str("=="), 1);
      SYNC_FRAME();
      break;

    case OP_GREATER: BINARY_OP(BOOL_VAL, >); break;
    case OP_LESS: BINARY_OP(BOOL_VAL, <); break;

    case OP_ADD:
      if ((err = vm_add())) return err;
      SYNC_FRAME();
      break;
    case OP_DIVIDE:
      if ((err = vm_divide())) return err;
      SYNC_FRAME();
      break;
    case OP_SUBTRACT: BINARY_OP(NUMBER_VAL, -); break;
    case OP_MULTIPLY:
      if ((err = vm_multiply())) return err;
      SYNC_FRAME();
      break;
    case OP_NOT: push(BOOL_VAL(isFalsey(pop()))); break;
    case OP_NEGATE:
      if (!is_num(peek(0))) {
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

    case OP_CALL:
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
      if (!is_class(peek(0))) {
        return runtimeError("Superclass must be a class.");
      }

      ObjClass *superclass = AS_CLASS(peek(0));
      ObjClass *subclass = AS_CLASS(peek(1));
      subclass->parent = superclass;
      // tableMerge(&superclass->methods, &subclass->methods);
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
      inspect_value(stdout, peek(0));
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

      if (vm.frameCount == starting_frame_count) return INTERPRET_OK;

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

InterpretResult run_function(ObjFun *fun) {
  if (fun == NULL) return INTERPRET_COMPILE_ERROR;

  push(OBJ_VAL(fun));
  ObjClosure *closure = newClosure(fun);
  pop();
  return run_closure(closure);
}

InterpretResult run_closure(ObjClosure *closure) {
  push(OBJ_VAL(closure));
  move_into_closure(closure, 0);
  return vm_run();
}

InterpretResult interpret(const char *source, ObjString *name) {
  return run_function(compile(source, name));
}

Value intern(Value val) {
  push(val);
  tableSet(&vm.interned, val, TRUE_VAL);
  return pop();
}

Obj *getInterned(Hash *hash, ObjType type, const char *bytes, int length) {
  *hash = hash_bytes(bytes, length);
  return tableFindObj(&vm.interned, type, bytes, length, *hash);
}
