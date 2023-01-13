#ifndef sol_object_h
#define sol_object_h

#include <stdarg.h>

typedef enum ObjType ObjType;

#include "chunk.h"
#include "common.h"
#include "table.h"
#include "value.h"

// Todo: stuff ObjType into VAL_OBJ pointer.
#define obj_type(val) (AS_OBJ(val)->type)

#define is_bound(val) is_obj_type(val, OBJ_BOUND)
#define is_class(val) is_obj_type(val, OBJ_CLASS)
#define is_closure(val) is_obj_type(val, OBJ_CLOSURE)
#define is_err(val) is_obj_type(val, OBJ_ERR)
#define is_fun(val) is_obj_type(val, OBJ_FUN)
#define is_instance(val) is_obj_type(val, OBJ_INSTANCE)
#define is_native(val) is_obj_type(val, OBJ_NATIVE)
#define is_range(val) is_obj_type(val, OBJ_RANGE)
#define is_string(val) is_obj_type(val, OBJ_STRING)
#define is_tuple(val) is_obj_type(val, OBJ_TUPLE)
#define is_upvalue(val) is_obj_type(val, OBJ_UPVALUE)

#define AS_BOUND(val) ((ObjBound *)AS_OBJ(val))
#define AS_CLASS(val) ((ObjClass *)AS_OBJ(val))
#define AS_CLOSURE(val) ((ObjClosure *)AS_OBJ(val))
#define AS_ERR(val) ((ObjErr *)AS_OBJ(val))
#define AS_FUN(val) ((ObjFun *)AS_OBJ(val))
#define AS_INSTANCE(val) ((ObjInstance *)AS_OBJ(val))
#define AS_NATIVE(val) ((ObjNative *)AS_OBJ(val))
#define AS_RANGE(val) ((ObjRange *)AS_OBJ(val))
#define AS_STRING(val) ((ObjString *)AS_OBJ(val))
#define AS_TUPLE(val) ((ObjTuple *)AS_OBJ(val))
#define AS_UPVALUE(val) ((ObjUpvalue *)AS_OBJ(val))

#define AS_NATIVE_FN(val) (AS_NATIVE(val)->fun)
#define AS_CSTRING(val) (AS_STRING(val)->chars)

#define ALLOCATE_OBJ(type, objectType)                                         \
  (type *)allocateObject(sizeof(type), objectType)

enum ObjType {
  OBJ_ARRAY,
  OBJ_BOUND,
  OBJ_CLASS,
  OBJ_CLOSURE,
  OBJ_ERR,
  OBJ_FUN,
  OBJ_INSTANCE,
  OBJ_NATIVE,
  OBJ_UPVALUE,

  // Interned objects must be last:
  OBJ_RANGE,
  OBJ_STRING,
  OBJ_TUPLE,
};

/** First ObjType enum that is interned. */
#define OBJ_INTERNED OBJ_RANGE

struct Obj {
  ObjType type;
  bool isMarked;    /** Is marked by GC in the current mark cycle. */
  struct Obj *next; /** Linked list of objects used for GC. */
  Hash hash;        /** All objects have a static hash value. */
};

/**
 * Tracks a closed-over variable by keeping a pointer to its
 * location in memory.
 *
 * "Open" upvalues point to values on the VM's stack.
 *
 * Todo: rename to ObjRef?
 */
typedef struct ObjUpvalue {
  Obj obj;
  Value closed;    /** Stores this upvalue's Value once it has been "closed". */
  Value *location; /** Pointer to this upvalue's Value. */
  struct ObjUpvalue *next; /** Linked list of all upvalues tracked by VM. */
} ObjUpvalue;

typedef struct ObjArray {
  Obj obj;
  int capacity;
  int length;
  Value *values;
} ObjArray;

typedef struct ObjErr {
  Obj obj;
  ObjString *msg;
} ObjErr;

typedef struct ObjFun {
  Obj obj;
  int arity;
  ObjString *name;
  int upvalueCount;
  Chunk chunk;
} ObjFun;

/**
 * upvalueCount is duplicated from ObjFun because we need it during GC and the
 * ObjFun might get GC'd first.
 */
typedef struct ObjClosure {
  Obj obj;
  ObjFun *fun;
  int upvalueCount;      /** Number of closed-over upvalues. */
  ObjUpvalue **upvalues; /** Array of upvalue pointers being closed-over. */
} ObjClosure;

typedef struct ObjClass {
  Obj obj;
  ObjString *name;
  struct ObjClass *parent;
  // ValueArray children; /** Classes of child values. */
  Table methods;
} ObjClass;

typedef struct ObjInstance {
  Obj obj;
  ObjClass *klass;
  // Value *children; /** Child values. */
  Table fields; /** Fields assigned to this instance. */
} ObjInstance;

/** A closure bound to a receiver.  */
typedef struct ObjBound {
  Obj obj;
  Value receiver; /** Bound `this` value. */
  Value method;   /** Method being bound. */
} ObjBound;

typedef Value NativeFn(Value self, int argCount, Value *args);

typedef struct ObjNative {
  Obj obj;
  int arity;
  ObjString *name;
  NativeFn *fun;
} ObjNative;

typedef struct ObjRange {
  Obj obj;
  Value start;
  Value end;
} ObjRange;

struct ObjString {
  Obj obj;
  int length;
  char *chars;
};

typedef struct ObjTuple {
  Obj obj;
  uint8_t length;
  Value *values;
} ObjTuple;

typedef struct ObjInfo {
  const char *inspect;
  const char *className;
} ObjInfo;

const ObjInfo objInfo[12];

Obj *allocateObject(size_t size, ObjType type);

ObjBound *newBound(Value receiver, Value method);
ObjClass *newClass(ObjString *name);
ObjClosure *newClosure(ObjFun *fun);
ObjErr *newError(ObjString *msg);

ObjFun *newFunction();
int fprintFunction(FILE *io, const char *kind, ObjFun *fun);

ObjInstance *newInstance(ObjClass *klass);
ObjNative *newNative(ObjString *name, int arity, NativeFn fun);

ObjRange *makeRange(Value start, Value end);

ObjUpvalue *newUpvalue(Value *slot);

const char *objectBytes(Obj *obj, int length);

int fprintObjType(FILE *io, ObjType type);
int fprintObject(FILE *io, Obj *obj);

int cmpObjects(Obj *a, Obj *b);
static inline bool is_obj_type(Value value, ObjType type) {
  return IS_OBJ(value) && AS_OBJ(value)->type == type;
}

static inline bool is_interned(Value val) {
  return IS_OBJ(val) && AS_OBJ(val)->type >= OBJ_INTERNED;
}

#endif
