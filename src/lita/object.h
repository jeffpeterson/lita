#ifndef lita_object_h
#define lita_object_h

typedef struct ObjDef ObjDef;
typedef struct ObjIterator ObjIterator;

#include <assert.h>

#include "common.h"
#include "table.h"
#include "value.h"

#define getDef(val) (as_obj(val)->def)
#define as(def, val) ((Obj##def *)asObjDef(&def, val))
#define ALLOCATE_OBJ(def) ((Obj##def *)allocateObject(&def))
#define allocate ALLOCATE_OBJ

#define foreach_obj_def(var) section_foreach_entry(defs, ObjDef *, var)
#define REGISTER_OBJECT_DEF(def) const SECTION(defs) ObjDef *def##_def = &def;
#define DEFINE_OBJECT_TYPE(def, ...)                                           \
  REGISTER_OBJECT_DEF(def);                                                    \
  const ObjDef def = {.className = #def, .size = sizeof(def), __VA_ARGS__}

#define DEF_MARK(type, var, ...) DEF_OBJ_FN(type, mark, var, __VA_ARGS__)
#define DEF_ALLOC(type, var, ...) DEF_OBJ_FN(type, alloc, var, __VA_ARGS__)
#define DEF_FREE(type, var, ...) DEF_OBJ_FN(type, free, var, __VA_ARGS__)

#define DEF_OBJ_FN(type, name, var, ...)                                       \
  void name##type(Obj *obj) {                                                  \
    Obj##type *var = (Obj##type *)obj;                                         \
    __VA_ARGS__;                                                               \
  }

typedef enum Ownership { UNOWNED, OWNED } Ownership;

// typedef struct Walk {
//   void *state;
//   void (*value)(struct Walk *walk, Value val);
//   void (*object)(struct Walk *walk, Obj *obj);
//   void (*bytes)(struct Walk *walk, void *bytes, usize size);
//   void (*table)(struct Walk *walk, Table *table);
// } Walk;

// void walkObject(Walk *walk, Obj *obj);
// typedef void ObjWalkFn(Walk *walk, Obj *obj);

typedef void ObjFn(Obj *obj);
typedef int ObjIntFn(Obj *obj);
typedef int ObjCmpFn(Obj *a, Obj *b);
typedef int ObjIOFn(Obj *obj, FILE *io);
typedef int ObjInspectFn(Obj *obj, FILE *io, int depth);
typedef InterpretResult ObjVMFn(Obj *obj, int argCount);
typedef ObjIterator *ObjIterateFn(Obj *obj);
typedef void ObjHashFn(Obj *obj, HashState *state);

typedef struct ObjDef {
  const char *className; // Name of global class backing this object.
  const usize size;      // Size in bytes.
  ObjIntFn *length;      // Length of collections. Or arity.
  ObjCmpFn *cmp;         // Compare two objects.
  ObjFn *alloc;          // Allocate extra memory during construction.
  ObjFn *free;           // Free extra allocated memory.
  ObjFn *mark;           // Mark child objects during gc.
  ObjHashFn *hash;       // Defaults to hashing the pointer.
  ObjVMFn *call;         // Implement calling.
  ObjIterateFn *iterate; // Iterate over collections.
  ObjInspectFn *inspect; // Inspect this object.
  ObjIOFn *dump;         // Dump this object as a C expression.
  ObjIOFn *dumpGlobal;   // Dump top-level C statements for this object.
  // ObjWalkFn *walk;       // Visit the object and its children.
} ObjDef;

extern const ObjDef Object;

typedef struct ObjClass ObjClass;

struct Obj {
  const ObjDef *def;
  bool isMarked;    // Is marked by GC in the current mark cycle.
  struct Obj *next; // Linked list of objects used for GC.
  Hash hash;        // All objects have a hash value.
  ObjClass *klass;  //
  Table fields;     // Fields assigned to this instance.
};

// TODO: Use this for yield keyword?
// typedef struct ObjContinuation {
//   Obj obj;
//   ObjClosure *closure;
//   CallFrame frame; // must be moved; can't require vm.h
// } ObjContinuation;

Obj *allocateObject(const ObjDef *def);
Obj *internObject(Obj **objp);
void hashObjectDefault(Obj *obj, HashState *state);
Obj *asObjDef(const ObjDef *def, Value val);
Obj *newInstance(ObjClass *klass);
int inspectObject(FILE *io, Obj *obj, int depth);
int cmpObjects(Obj *a, Obj *b);

static inline Obj *asObject(Value val) {
  assert(isObject(val));
  return AS_OBJ(val);
}

static inline bool isObjDef(Value value, const ObjDef *def) {
  return isObject(value) && AS_OBJ(value)->def == def;
}

typedef struct ObjComponent {
  Obj *obj;
} ObjComponent;

#endif
