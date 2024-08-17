#ifndef lita_object_h
#define lita_object_h

#include <stdarg.h>

typedef enum ObjType ObjType;
typedef struct ObjDef ObjDef;

#include "chunk.h"
#include "common.h"
#include "table.h"
#include "value.h"

// Todo: stuff ObjType into VAL_OBJ pointer.
#define obj_type(val) (AS_OBJ(val)->type)

#define is_bound(val) is_obj_type(val, OBJ_BOUND)
#define is_class(val) is_obj_type(val, OBJ_CLASS)
#define is_closure(val) is_obj_type(val, OBJ_CLOSURE)
#define is_custom(val) is_obj_type(val, OBJ_CUSTOM)
#define is_fun(val) is_obj_type(val, OBJ_FUN)
#define is_native(val) is_obj_type(val, OBJ_NATIVE)
#define is_upvalue(val) is_obj_type(val, OBJ_UPVALUE)

#define AS_BOUND(val) ((ObjBound *)AS_OBJ(val))
#define AS_CLASS(val) ((ObjClass *)AS_OBJ(val))
#define AS_CLOSURE(val) ((ObjClosure *)AS_OBJ(val))
#define AS_ERR(val) ((ObjErr *)AS_OBJ(val))
#define AS_FUN(val) ((ObjFun *)AS_OBJ(val))
#define AS_NATIVE(val) ((ObjNative *)AS_OBJ(val))
#define AS_UPVALUE(val) ((ObjUpvalue *)AS_OBJ(val))

#define AS_NATIVE_FN(val) (AS_NATIVE(val)->fun)
#define AS_CSTRING(val) (AS_STRING(val)->chars)

#define ALLOCATE_OBJ(type, objectType)                                         \
  (type *)allocateObject(sizeof(type), objectType)

#define REGISTER_OBJECT_DEF(def) const SECTION(defs) ObjDef *def##_def = &def;

#define foreach_obj_def(var) section_foreach_entry(defs, ObjDef *, var)

typedef enum Ownership { UNOWNED, OWNED } Ownership;

enum ObjType {
  OBJ_BOUND,
  OBJ_CLASS,
  OBJ_CLOSURE,
  OBJ_CUSTOM,
  OBJ_FUN,
  OBJ_NATIVE,
  OBJ_UPVALUE,
};

typedef Value NativeFn(Value self, int argCount, Value *args);

typedef void ObjFn(Obj *obj);
typedef int ObjLengthFn(Obj *obj);
typedef void ObjNativesFn(Value klass);
typedef int ObjIOFn(Obj *obj, FILE *io);
typedef const char *ObjBytesFn(Obj *obj, int length);

typedef struct ObjDef {
  const char *class_name;
  const usize size;
  const bool interned;
  ObjLengthFn *length;
  Obj *(*alloc)();
  ObjFn *init;
  ObjFn *free;
  ObjFn *mark;
  ObjIOFn *inspect; /** NOTE: Why can't we invoke .inspect? */
  ObjIOFn *dump;
  ObjIOFn *dump_global;
  ObjBytesFn *bytes;
  ObjNativesFn *natives;
} ObjDef;

const ObjDef Bound;
const ObjDef Class;
const ObjDef Closure;
const ObjDef Function;
const ObjDef Native;
const ObjDef Upvalue;

typedef struct ObjClass ObjClass;

struct Obj {
  ObjType type;
  const ObjDef *def;
  bool isMarked;    /** Is marked by GC in the current mark cycle. */
  struct Obj *next; /** Linked list of objects used for GC. */
  Hash hash;        /** All objects have a static hash value. */
  ObjClass *klass;
  Table fields; /** Fields assigned to this instance. */
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

typedef struct ObjErr {
  Obj obj;
  ObjString *msg;
} ObjErr;

typedef struct ObjFun {
  Obj obj;
  int arity;
  bool variadic;
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
  ObjDef *instance_def;
  Table methods;
} ObjClass;

/** A closure bound to a receiver.  */
typedef struct ObjBound {
  Obj obj;
  Value receiver; /** Bound `this` value. */
  Value method;   /** Method being bound. */
} ObjBound;

typedef struct ObjNative {
  Obj obj;
  int arity;
  ObjString *name;
  NativeFn *fun;
} ObjNative;

struct ObjString {
  Obj obj;
  int length;
  char *chars;
};

typedef struct ObjInfo {
  const char *inspect;
  const char *className;
} ObjInfo;

extern const ObjInfo objInfo[7];

Obj *allocateObject(size_t size, ObjType type);

bool as_bool(Value x);
ObjClass *as_class(Value x);
ObjClosure *as_closure(Value x);
ObjBound *as_bound(Value x);
ObjNative *as_native(Value x);
double as_num(Value x);
Obj *as_obj(Value x);

Obj *new_object(const ObjDef *def);
Obj *new_instance(ObjClass *klass);
ObjBound *newBound(Value receiver, Value method);
ObjClass *newClass(ObjString *name);
ObjClosure *newClosure(ObjFun *fun);

ObjFun *newFunction();
int inspect_function(FILE *io, const char *kind, ObjFun *fun);

ObjNative *newNative(ObjString *name, int arity, NativeFn fun);

ObjUpvalue *newUpvalue(Value *slot);

const char *objectBytes(Obj *obj, int length);

int inspect_obj_type(FILE *io, ObjType type);
int inspect_obj(FILE *io, Obj *obj);
int print_object(FILE *io, Obj *obj);

int cmpObjects(Obj *a, Obj *b);

Value init_obj(Value klass, int argc, Value *args);

static inline bool is_obj_type(Value value, ObjType type) {
  return is_obj(value) && AS_OBJ(value)->type == type;
}

static inline bool is_obj_def(Value value, const ObjDef *def) {
  return is_obj(value) && AS_OBJ(value)->def == def;
}

static inline bool is_interned(Value val) {
  if (!is_obj(val)) return true;
  Obj *obj = AS_OBJ(val);
  return obj->def && obj->def->interned;
}

#endif
