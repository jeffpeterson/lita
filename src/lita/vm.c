#define Function ReadlineFunction
#include <readline/history.h>
#include <readline/readline.h>
#undef Function

#include <assert.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "array.h"
#include "bound.h"
#include "class.h"
#include "common.h"
#include "compiler.h"
#include "debug.h"
#include "io.h"
#include "iterator.h"
#include "lib.h"
#include "memory.h"
#include "object.h"
#include "range.h"
#include "string.h"
#include "system.h"
#include "term.h"
#include "tuple.h"
#include "vm.h"

#if ENABLE_REGEX
#include "regex.h"
#endif

VM vm;
InterpretResult ok = INTERPRET_OK;

static void resetStack() {
  vm.stackTop = vm.stack;
  vm.frameCount = 0;
  vm.openUpvalues = NULL;
}

static InterpretResult vruntimeError(const char *format, va_list args) {
  fprintf(stderr, "\n%d frames:\n", vm.frameCount);
  for (int i = 0; i < vm.frameCount; i++) {
    CallFrame *frame = &vm.frames[i];

    if (frame->closure) {
      ObjFunction *fun = frame->closure->function;
      size_t instruction = frame->ip - fun->chunk.code - 1;
      int line = fun->chunk.lines[instruction];

      if (DEBUG_ERRORS || config.debug)
        disassembleChunk(&fun->chunk, fun->name->chars, instruction + 1);

      fprintf(stderr, "[line %d] in ", line);
      inspect_obj(stderr, (Obj *)fun);
      fprintf(stderr, "\n");
    } else if (frame->native) {
      inspect_obj(stderr, (Obj *)frame->native);
    }
  }

  fprintf(stderr, "\nStack:\t");
  debugStack();

  fputs(FG_RED "\n\nRUNTIME ERROR: " FG_DEFAULT, stderr);
  vfprintf(stderr, format, args);
  fputs("\n\n", stderr);

  resetStack();

  return INTERPRET_RUNTIME_ERROR;
}

InterpretResult runtimeError(const char *format, ...) {
  va_list args;
  va_start(args, format);
  InterpretResult result = vruntimeError(format, args);
  va_end(args);
  return result;
}

void assertOkResult(InterpretResult result) {
  if (result == INTERPRET_COMPILE_ERROR) exit(65);

  if (result == INTERPRET_RUNTIME_ERROR) exit(70);
}

let crash(const char *fmt, ...) {
  va_list args;
  va_start(args, fmt);
  vruntimeError(fmt, args);
  va_end(args);
  freeVM();
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

Value globalClass(const char *name) {
  let vname = string(name);
  let klass = global(vname);
  if (isClass(klass)) return klass;
  return setGlobal(vname, class(name));
}

void initVM(World *world) {
  resetStack();

  vm.world = world;
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

  /** Start collecting after 1MB is allocated. */
  vm.nextGC = 1024 * 1024;
}

static void registerDef(ObjDef *def) {
  if (!def->class_name) crash("def must have a class_name");
  if (!def->size) crash("def must have a size");

  let klass = globalClass(def->class_name);
  asClass(klass)->instance_def = def;
}

ObjFunction *core_lita();

static InterpretResult defineNatives() {
  foreach_native(native) {
    let fun = fn(native->name, native->arity, native->fun);
    trace(native->class_name, fun);

    if (native->class_name) {
      let klass = globalClass(native->class_name);
      if (native->is_static) static_method(klass, fun);
      else method(klass, fun);

    } else setGlobal(string(native->name), fun);
  }

  run_function(core_lita());

  foreach_boot_function(boot) {
    ObjFunction *fun = boot->fun();
    trace("Booting", OBJ_VAL(fun));
    if (fun) {
      InterpretResult result = run_function(fun);
      if (result) return result;
    }
  }

  return INTERPRET_OK;
}

InterpretResult bootVM() {
  InterpretResult result = defineNatives();

  foreach_obj_def(def) registerDef(*def);

  setGlobal(string("stdin"), io(stdin, UNOWNED));
  setGlobal(string("stdout"), io(stdout, UNOWNED));
  setGlobal(string("stderr"), io(stderr, UNOWNED));

  ECS_IMPORT(vm.world, Lita);

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
  if (vm.stackTop > vm.stackSinceGC) vm.stackSinceGC = vm.stackTop;

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

Value *popn(u8 n) { return vm.stackTop -= n; }

void vm_swap(u8 a, u8 b) {
  Value aa = peek(a);
  vm.stackTop[-1 - a] = peek(b);
  vm.stackTop[-1 - b] = aa;
}

static CallFrame *newFrame(usize slots) {
  CallFrame *frame = &vm.frames[vm.frameCount++];

  frame->native = NULL;
  frame->reentries = 0;
  frame->closure = NULL;
  frame->ip = NULL;
  frame->slots = vm.stackTop - slots;
  frame->prev_stack = vm.stackTop;
  frame->prev_ip = NULL;
  return frame;
}

/**
 * Move the instruction pointer (ip) to a new a closure along with arguments on
 * the stack.
 *
 * Returns whether or not the call was successful.
 */
static InterpretResult moveIntoClosure(ObjClosure *closure, int argCount) {
  ObjFunction *fun = closure->function;

  if (argCount < fun->arity)
    return runtimeError("Expected %d arguments but got %d.", fun->arity,
                        argCount);

  if (fun->variadic) {
    vm_array(argCount - fun->arity);
    argCount = fun->arity + 1;
  }

  CallFrame *existing_frame = &vm.frames[vm.frameCount - 1];

  if (existing_frame->closure == closure &&
      *(existing_frame->ip) == OP_RETURN) {
    // Tail-call optimization.
    copy_values(vm.stackTop - argCount, existing_frame->slots + 1, argCount);
    vm.stackTop = existing_frame->slots + argCount + 1;
    existing_frame->ip = fun->chunk.code;
    existing_frame->prev_ip = NULL;
    return INTERPRET_OK;
  }

  if (vm.frameCount == FRAMES_MAX) return runtimeError("Call stack overflow.");

  /**
   * Account for args and the receiver if method, else the callee.
   * stack: [..., this, arg1, arg2]
   *     receiver-^               ^-stackTop
   */
  CallFrame *frame = newFrame(argCount + 1);
  frame->closure = closure;
  frame->ip = fun->chunk.code;

  return INTERPRET_OK;
}

static InterpretResult moveIntoNative(ObjNative *native, int argc) {
  if (argc < native->arity)
    return runtimeError("Expected %d arguments but got %d.", native->arity,
                        argc);

  if (vm.frameCount == FRAMES_MAX) return runtimeError("Call stack overflow.");

  /**
   * Account for args and the receiver if method, else the callee.
   * stack: [..., this, arg1, arg2]
   *     receiver-^               ^-stackTop
   */
  CallFrame *frame = newFrame(argc + 1);
  frame->native = native;

  return INTERPRET_OK;
}

ObjClass *valueClass(Value v) {
  if (is_obj(v)) {
    Obj *obj = AS_OBJ(v);
    if (!obj->klass) obj->klass = asClass(globalClass(obj->def->class_name));
    return obj->klass;
  }

  const char *name = is_nil(v)    ? "Nil"
                     : is_num(v)  ? "Number"
                     : is_bool(v) ? "Bool"
                                  : "Any";

  return asClass(globalClass(name));
}

/**
 * Invoke some Value as a function.
 *
 * Returns whether or not the call was successful.
 */
InterpretResult callValue(Value callee, int argCount) {
  trace("callValue", callee);

  if (is_obj(callee)) {
    if (isClosure(callee)) return moveIntoClosure(asClosure(callee), argCount);
    else if (isNative(callee))
      return moveIntoNative(AS_NATIVE(callee), argCount);
    else if (isClass(callee)) {
      // Replace the class with a new instance.
      vm.stackTop[-argCount - 1] = OBJ_VAL(new_instance(asClass(callee)));
      return vm_invoke(OBJ_VAL(vm.str.init), argCount);
    } else if (isBound(callee)) {
      ObjBound *bound = asBound(callee);
      vm.stackTop[-argCount - 1] = bound->receiver;
      return callValue(bound->method, argCount);
    }
  }

  if (argCount == 1) return vm_invoke(string(""), 1);
  return false;
}

static InterpretResult invokeFromClass(ObjClass *klass, ObjString *name,
                                       int argCount) {
  Value method;

  if (!tableGet(&klass->methods, OBJ_VAL(name), &method)) {
    if (!klass->parent) return false;

    return invokeFromClass(klass->parent, name, argCount);
  }

  return callValue(method, argCount);
}

/** [argCount self][0 ...args] */
InterpretResult vm_invoke(Value name, int argCount) {
  Value receiver = peek(argCount);

  // if (config.tracing) fstring_format(stderr, "[TRACE] invoke: {} on ", name);

  if (config.tracing) {
    fprintf(stderr, "[TRACE] vm_invoke(%s, %d) on: ", as_string(name)->chars,
            argCount),
        inspect_value(stderr, receiver), fprintf(stderr, "\n");
  }

  if (is_obj(receiver)) {
    Obj *obj = AS_OBJ(receiver);

    Value value;
    if (tableGet(&obj->fields, name, &value)) {
      vm.stackTop[-argCount - 1] = value;
      return callValue(value, argCount);
    }
  }

  ObjClass *klass = valueClass(receiver);

  if (config.tracing)
    fprintf(stderr, "[TRACE] invoking %s.%s()\n", klass->name->chars,
            asChars(name));

  if (invokeFromClass(klass, as_string(name), argCount)) {
    return runtimeError("Undefined method %s on %s.", asChars(inspect(name)),
                        asChars(inspect(OBJ_VAL(klass))));
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
  ObjClass *klass = asClass(peek(1));
  tableSet(&klass->methods, OBJ_VAL(name), method);
  pop();
}

static bool isFalsey(Value value) { return is_nil(value) || is_false(value); }

/** [length ...args][0 arg] -> [0 array] */
void vm_array(u32 length) {
  ObjArray *arr = copy_array(vm.stackTop - length, length);
  popn(length);
  push(OBJ_VAL(arr));
}

InterpretResult vm_assert(Value src) {
  let value = peek(0);

#if DEBUG_ASSERT_CODE
  inspect_value(stderr, src);
  fprintf(stderr, "\n");
#endif

  if (isFalsey(value)) {
    fstring_format(stderr, "\n\n{} -> {}\n\n", src, value);

    return runtimeError(FG_CYAN "%s" FG_DEFAULT " -> %s", asChars(src),
                        inspectc(value));
  }

#if DEBUG_ASSERTS
  fprintf(stderr, "%s", FG_GREEN "." FG_DEFAULT);
#endif

  return INTERPRET_OK;
}

// [argc fn][1 arg1][0 ...args ] -> [0 return]
InterpretResult vm_call(int argc) { return callValue(peek(argc), argc); }

// [] -> [0 value]
InterpretResult vm_get_global(Value name) {
  let value;

  if (!tableGet(&vm.globals, name, &value)) {
    if (is_nil(value = get_env(name)))
      if (!isString(name) || *as_string(name)->chars != '$')
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
                        asString(name)->chars);
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

static void vm_return() {
  CallFrame *frame = CURRENT_FRAME;
  Value result = pop(); // Pop return value off stack.
  closeUpvalues(frame->slots);
  vm.frameCount--;
  vm.stackTop = frame->slots; // Reset stack top to the last frame.
  push(result);
}

static InterpretResult vm_run() {
  if (vm.frameCount == 0) return runtimeError("No function to run.");
  if (vm.frameCount > 1) return runtimeError("VM already running.");

  register CallFrame *frame = CURRENT_FRAME;
  InterpretResult err;

#define READ_BYTE() (*frame->ip++)
/** Update the cached frame variable. Idempotent. */
#define SYNC_FRAME() (frame = CURRENT_FRAME)
#define READ_SHORT()                                                           \
  (frame->ip += 2, (uint16_t)((frame->ip[-2] << 8) | frame->ip[-1]))
#define READ_CONSTANT()                                                        \
  (frame->closure->function->chunk.constants.values[READ_BYTE()])
#define READ_STRING() asString(READ_CONSTANT())
#define BINARY_OP(valueType, op)                                               \
  do {                                                                         \
    if (is_num(peek(0)) && is_num(peek(1))) {                                  \
      double b = AS_NUMBER(pop());                                             \
      double a = AS_NUMBER(pop());                                             \
      push(valueType(a op b));                                                 \
    } else {                                                                   \
      if ((err = vm_invoke(string(#op), 1))) return err;                       \
      SYNC_FRAME();                                                            \
    }                                                                          \
  } while (false)

  for (;;) {
    if (DEBUG_TRACE_EXECUTION || config.debug >= 3) debugExecution();

    vm.stackHigh = vm.stackTop;

    // TODO: move this to SYNC_FRAME or similar? Only need to check if the
    // frame has changed.
    if (frame->native) {
      int argc = vm.stackTop - frame->slots - 1;
      if (config.tracing)
        fprintf(stderr, "[TRACE] Calling native %s with %d args\n",
                frame->native->name->chars, argc);
      let result = frame->native->fun(peek(argc), argc, frame->slots + 1);
      frame->reentries++;

      if (not_void(result)) {
        push(result);
        vm_return();
      }

      if (vm.frameCount == 0) {
        resetStack();
        return INTERPRET_OK;
      }

      SYNC_FRAME();
      continue;
    }

    if (frame->prev_ip) {
      int actual = vm.stackTop - frame->prev_stack;
      int expected =
          input_output_delta(&frame->closure->function->chunk, frame->prev_ip);

      if (actual != expected) {
        OpInfo op = op_info[*frame->prev_ip];
        return runtimeError(
            "Stack size mismatch after %s: Expected %+d and got %+d.", op.name,
            expected, actual);
      }
    }

    frame->prev_stack = vm.stackTop;
    frame->prev_ip = frame->ip;

    u8 instruction = READ_BYTE();

    switch (instruction) {
    case OP_CONSTANT: push(READ_CONSTANT()); break;

    case OP_NIL: push(NIL_VAL); break;
    case OP_TRUE: push(BOOL_VAL(true)); break;
    case OP_FALSE: push(BOOL_VAL(false)); break;

    case OP_PEEK: push(peek(READ_BYTE())); break;
    case OP_POP: pop(); break;
    case OP_POPN: popn(READ_BYTE()); break;
    case OP_SWAP: {
      u8 args = READ_BYTE();
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
    case OP_ARRAY: vm_array(as_num(READ_CONSTANT())); break;
    case OP_TUPLE: vm_tuple(READ_BYTE()); break;

    case OP_DEFINE_GLOBAL: tableSet(&vm.globals, READ_CONSTANT(), pop()); break;

    case OP_GET_GLOBAL:
      if ((err = vm_get_global(READ_CONSTANT()))) return err;
      break;
    case OP_SET_GLOBAL:
      if ((err = vm_set_global(READ_CONSTANT()))) return err;
      break;

    case OP_GET_LOCAL: {
      u8 slot = READ_BYTE();
      push(frame->slots[slot]);
      break;
    }
    case OP_SET_LOCAL: {
      u8 slot = READ_BYTE();
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
      u8 slot = READ_BYTE();
      push(*frame->closure->upvalues[slot]->location);
      break;
    }

    case OP_SET_UPVALUE: {
      u8 slot = READ_BYTE();
      *frame->closure->upvalues[slot]->location = peek(0);
      break;
    }

    case OP_EQUAL: BINARY_OP(BOOL_VAL, ==); break;
    case OP_GREATER: BINARY_OP(BOOL_VAL, >); break;
    case OP_LESS: BINARY_OP(BOOL_VAL, <); break;
    case OP_ADD: BINARY_OP(NUMBER_VAL, +); break;
    case OP_DIVIDE: BINARY_OP(NUMBER_VAL, /); break;
    case OP_SUBTRACT: BINARY_OP(NUMBER_VAL, -); break;
    case OP_MULTIPLY: BINARY_OP(NUMBER_VAL, *); break;
    case OP_NOT: push(BOOL_VAL(isFalsey(pop()))); break;
    case OP_NEGATE:
      if (!is_num(peek(0))) {
        runtimeError("Operand must be a number.");
        return INTERPRET_RUNTIME_ERROR;
      }
      push(NUMBER_VAL(-AS_NUMBER(pop())));
      break;

    case OP_JUMP: {
      u16 offset = READ_SHORT();
      frame->ip += offset;
      break;
    }
    case OP_JUMP_IF_FALSE: {
      u16 offset = READ_SHORT();
      if (isFalsey(peek(0))) frame->ip += offset;
      break;
    }
    case OP_LOOP: {
      u16 offset = READ_SHORT();
      frame->ip -= offset;
      break;
    }

    case OP_CALL:
      if ((err = vm_call(READ_BYTE()))) return err;
      SYNC_FRAME();
      break;

    case OP_CLASS: { // []
      let name = READ_CONSTANT();
      bool isLocal = (bool)READ_BYTE();

      if (isLocal) push(OBJ_VAL(newClass(as_string(name))));
      else push(globalClass(asChars(name)));

      break;
    }

    case OP_INHERIT: { // [1 class][0 super]
      if (!isClass(peek(0))) {
        return runtimeError("Superclass must be a class.");
      }

      ObjClass *superclass = asClass(peek(0));
      ObjClass *subclass = asClass(peek(1));
      subclass->parent = superclass;
      subclass->instance_def = superclass->instance_def;
      // tableMerge(&superclass->methods, &subclass->methods);
      break;
    }

    case OP_GET_SUPER: {
      ObjString *name = READ_STRING();
      ObjClass *superclass = asClass(pop());

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
      ObjClass *superclass = asClass(pop());

      if (!invokeFromClass(superclass, READ_STRING(), READ_BYTE()))
        return INTERPRET_RUNTIME_ERROR;

      SYNC_FRAME();
      break;
    }

    case OP_CLOSURE: {
      ObjFunction *fun = asFunction(READ_CONSTANT());
      ObjClosure *closure = newClosure(fun);
      push(OBJ_VAL(closure));

      for (int i = 0; i < closure->upvalueCount; i++) {
        u8 isLocal = READ_BYTE();
        u8 index = READ_BYTE();

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
      vm_get_global(string("stdout"));
      if ((err = vm_invoke(string("print"), 1))) return err;
      // printf("\n");
      SYNC_FRAME();
      break;

    case OP_RETURN: {
      vm_return();

      if (!vm.frameCount) {
        vm.result = pop();
        resetStack(); // Pop <script> function off stack.
        return INTERPRET_OK;
      }

      SYNC_FRAME();
      break;
    }

    case OP_DEBUG_STACK: {
      let tag = READ_CONSTANT();
      fprintf(stderr, "[DEBUG] %s: ", as_string(tag)->chars);
      debugStack();
      fprintf(stderr, "\n");
      break;
    }

    case OP_ASSERT_STACK: {
      let comment = READ_CONSTANT();
      u8 size = READ_BYTE();
      if (size != vm.stackTop - frame->slots) {
        return runtimeError(
            "Stack size mismatch: Expected " FG_BLUE "%d" FG_DEFAULT
            " and got " FG_BLUE "%d" FG_DEFAULT ". %s",
            size, vm.stackTop - frame->slots, as_string(comment)->chars);
      }
      break;
    }

    default:
      return runtimeError("Error: Instruction not implemented: 0x%02x.",
                          instruction);
    }
  }

#undef READ_BYTE
#undef READ_SHORT
#undef READ_CONSTANT
#undef READ_STRING
#undef BINARY_OP
#undef SYNC_FRAME
}

InterpretResult run_function(ObjFunction *fun) {
  if (fun == NULL) return INTERPRET_COMPILE_ERROR;

  push(OBJ_VAL(fun));
  ObjClosure *closure = newClosure(fun);
  pop();
  return run_closure(closure);
}

InterpretResult run_closure(ObjClosure *closure) {
  push(OBJ_VAL(closure));
  return moveIntoClosure(closure, 0) || vm_run();
}

InterpretResult interpret(const char *source, ObjString *name) {
  return run_function(compile(source, name));
}

Value intern(Value val) {
  push(val);
  tableSet(&vm.interned, val, TRUE_VAL);
  return pop();
}

Obj *getInterned(Hash *hash, const char *bytes, int length) {
  *hash = hash_bytes(bytes, length);
  return tableFindObj(&vm.interned, bytes, length, *hash);
}

void repl() {
  // ecs_singleton_set(vm.world, EcsRest, {0});

  ObjString *name = newString("REPL");
  ObjString *history =
      concat_strings(newString(getenv("HOME")), newString("/.lita_history"));

  setGlobal(string("REPL"), OBJ_VAL(name));
  setGlobal(string("HISTORY_LOCATION"), OBJ_VAL(history));

  read_history(history->chars);
  char *line;

  while ((line = readline("lita> "))) {
    add_history(line);
    write_history(history->chars);
    // TODO: Enqueue this as a request
    interpret(line, name);
    free(line);
    inspect_value(stderr, vm.result);
    fprintf(stderr, "\n");

    if (config.debug >= 2) {
      debugStack();
      fprintf(stderr, "\n");
    }

    // ecs_progress(vm.world, 0);
  }

  printf("\n");
}

ECS_COMPONENT_DECLARE(VM);

void LitaImport(World *world) {
  ECS_MODULE(world, Lita);
  ECS_IMPORT(world, Buffers);
  ECS_IMPORT(world, Tables);

  ECS_COMPONENT_DEFINE(world, VM);
}
