#ifndef sol_vm_h
#define sol_vm_h

#include "object.h"
#include "table.h"
#include "value.h"

#define FRAMES_MAX 64
#define STACK_MAX (FRAMES_MAX * UINT8_COUNT)

typedef struct CallFrame {
  ObjClosure *closure; /** Fn containing the code. */
  uint8_t *ip;         /** Current instruction pointer. */
  Value *slots;        /** Points into the VM's value stack. */
} CallFrame;

typedef struct VM {
  CallFrame frames[FRAMES_MAX]; /** Our function call stack. */
  int frameCount;               /** Current depth of the function call stack. */

  Value stack[STACK_MAX]; /** Stack of values referenced by our call frames. */
  Value *stackTop;        /** Pointer to the top of the value stack. */
  Value *stackHigh;       /** The highest point the stack has been this tick. */

  Table globals;  /** Global variables hashed by name. */
  Table interned; /** Interned object table. */
  Table keep;     /** Exempt objects from GC. */

  struct str { /** Static strings. */
    ObjString *init;
  } str;

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

} VM;

typedef enum InterpretResult {
  INTERPRET_OK,
  INTERPRET_COMPILE_ERROR,
  INTERPRET_RUNTIME_ERROR
} InterpretResult;

extern VM vm;

void initVM();
void freeVM();

InterpretResult runFun(ObjFun *fun);
InterpretResult interpret(const char *source);

/** Push a value onto the stack. */
Value push(Value value);

/** Pop a value off the stack. */
Value pop();

/** pop() but returns the given value. */
Value pope(Value val);

/** pop() n values off the stack. */
Value *popn(uint8_t n);

Value global(Value name);
Value setGlobal(Value name, Value val);

Value intern(Value val);
Obj *getInterned(Hash *hash, ObjType type, const char *bytes, int length);

Value getThis();
ObjClass *valueClass(Value v);

InterpretResult runtimeError(const char *format, ...);

/** Something went wrong. Stop the VM and exit. */
void crash(const char *str);

/**
 * Something went terribly wrong.
 * Memory is unsafe. Exit the process now.
 */
void panic(const char *str);

#endif
