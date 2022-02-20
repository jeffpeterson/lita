#ifndef sol_vm_h
#define sol_vm_h

#include "object.h"
#include "table.h"
#include "value.h"

#define FRAMES_MAX 64
#define STACK_MAX (FRAMES_MAX * UINT8_COUNT)

typedef struct CallFrame {
  ObjClosure *closure;

  /** Current instruction pointer. */
  uint8_t *ip;

  /** Points into the VM's value stack. */
  Value *slots;
} CallFrame;

typedef struct VM {
  /** Our function call stack. */
  CallFrame frames[FRAMES_MAX];

  /** Current depth of the function call stack. */
  int frameCount;

  /** The stack of values referenced by our call frames. */
  Value stack[STACK_MAX];

  /** Pointer to the top of the value stack. */
  Value *stackTop;

  /** Global variables hashed by name. */
  Table globals;

  /** Interned object table. */
  Table interned;

  /** Static strings. */
  struct str {
    ObjString *init;
  } str;

  ObjUpvalue *openUpvalues;

  /** A chain of allocated objects. */
  Obj *objects;

  /** Total memory we have allocated. */
  size_t bytesAllocated;

  /** Threshold to trigger the next garbage collection. */
  size_t nextGC;

  /** Number of entries in `grayStack`. */
  int grayCount;

  /** Capacity allocated for `grayStack`. */
  int grayCapacity;

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
} VM;

typedef enum InterpretResult {
  INTERPRET_OK,
  INTERPRET_COMPILE_ERROR,
  INTERPRET_RUNTIME_ERROR
} InterpretResult;

extern VM vm;

void initVM();
void freeVM();
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
ObjClass *classOf(Value v);

void runtimeError(const char *format, ...);

#endif
