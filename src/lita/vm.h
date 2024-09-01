#ifndef lita_vm_h
#define lita_vm_h

#include "ecs.h"
#include "object.h"
#include "table.h"
#include "value.h"

#define FRAMES_MAX 64
#define STACK_MAX (FRAMES_MAX * UINT8_COUNT)
#define CURRENT_FRAME &vm.frames[vm.frameCount - 1]

typedef struct CallFrame {
  ObjNative *native;   /** Native function being executed. */
  ObjClosure *closure; /** Fn containing the code. */
  u8 *ip;              /** Current instruction pointer. */
  Value *slots;        /** Points into the VM's value stack. */

  u8 *prev_ip;       /** Pointer to last instruction. */
  Value *prev_stack; /** Slots prior to last instruction. */
} CallFrame;

typedef struct VM {
  CallFrame frames[FRAMES_MAX]; /** Our function call stack. */
  int frameCount;               /** Current depth of the function call stack. */

  Value stack[STACK_MAX]; /** Stack of values referenced by our call frames. */
  Value *stackTop;        /** Pointer to the top of the value stack. */
  Value *stackHigh;    /** The highest point the stack has been this cycle. */
  Value *stackSinceGC; /** The highest point the stack has been since GC. */

  Value result;   /** Result of the last script. */
  Table globals;  /** Global variables hashed by name. */
  Table interned; /** Interned object table. */
  Table keep;     /** Exempt objects from GC. */

  ecs_world_t *world; /** ECS world. */

  ObjUpvalue *openUpvalues; /** Unclosed upvalues. */
  Obj *objects;             /** A chain of allocated objects. */

  /**
   * Stack of objects marked "gray".
   *
   * Implementation of "tricolor abstraction".
   *
   * Objects start out "white".
   * During GC marking, we mark each visited object "gray".
   * Once an object's children are marked gray, we mark that object "black".
   * Garbage collect all remaining white objects.
   */
  Obj **grayStack;
  int grayCount;         /** Number of entries in `grayStack`. */
  int grayCapacity;      /** Capacity allocated for `grayStack`. */
  size_t bytesAllocated; /** Total memory we have allocated. */
  size_t nextGC;         /** Threshold to trigger the next GC. */

  struct str { /** Static strings. */
    ObjString *init;
  } str;
} VM;

typedef enum InterpretResult {
  INTERPRET_OK,
  INTERPRET_RUNTIME_ERROR,
  INTERPRET_COMPILE_ERROR,
} InterpretResult;

extern VM vm;

void initVM();
void freeVM();
InterpretResult bootVM();
InterpretResult run_function(ObjFun *fun);
InterpretResult run_closure(ObjClosure *closure);
InterpretResult interpret(const char *source, ObjString *name);

/** Push a value onto the stack and return it. */
Value push(Value value);

/** Pop a value off the stack and return it. */
Value pop();

/** pop() but returns the given value. */
Value pope(Value val);

/** pop() n values off the stack. */
Value *popn(uint8_t n);

InterpretResult send(Value this, Value method_name, int argc, ...);

Value global(Value name);
Value setGlobal(Value name, Value val);

Value global_class(const char *name);

Value intern(Value val);
Obj *getInterned(Hash *hash, ObjType type, const char *bytes, int length);

Value getThis();
ObjClass *valueClass(Value v);

InterpretResult runtimeError(const char *format, ...);
void assertOkResult(InterpretResult result);

/** Something went wrong. Stop the VM and exit. */
let crash(const char *fmt, ...);

/**
 * Something went terribly wrong.
 * Memory is unsafe. Exit the process now.
 */
void panic(const char *str);

bool call_value(Value callee, int argCount);

Value vm_peek(int i);
InterpretResult vm_add();
InterpretResult vm_multiply();
InterpretResult vm_assert(Value src);
InterpretResult vm_call(int argc);
InterpretResult vm_invoke(Value name, int argCount);
InterpretResult vm_get_global(Value name);
InterpretResult vm_get_property(Value name);
InterpretResult vm_set_property(Value name);
InterpretResult vm_get_var(Value name);
InterpretResult vm_set_var(Value name);
void vm_range();
void vm_swap(u8 a, u8 b);
void vm_array(u32 length);
void vm_tuple(u8 length);

void repl();

#endif
