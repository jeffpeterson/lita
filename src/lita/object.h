#ifndef lita_object_h
#define lita_object_h

typedef struct ObjDef ObjDef;
typedef struct ObjIterator ObjIterator;

#include "common.h"
#include "table.h"
#include "value.h"

#define getDef(val) (as_obj(val)->def)
#define as(def, val) ((Obj##def *)asObjDef(&def, val))
#define ALLOCATE_OBJ(def) ((Obj##def *)allocateObject(&def))
#define asObject(val) ((Obj *)asObjDef(&Object, val))

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
typedef int ObjIOFn(Obj *obj, FILE *io);
typedef InterpretResult ObjVMFn(Obj *obj, int argCount);
typedef ObjIterator *ObjIterateFn(Obj *obj);
typedef void ObjHashFn(Obj *obj, HashState *state);

typedef struct ObjDef {
  const char *className;
  const usize size;
  ObjIntFn *length;
  ObjFn *alloc;
  ObjFn *free;
  ObjFn *mark;
  ObjHashFn *hash;
  // ObjWalkFn *walk;
  ObjVMFn *call;
  ObjIterateFn *iterate;
  ObjIOFn *inspect;
  ObjIOFn *dump;
  ObjIOFn *dumpGlobal;
} ObjDef;

extern const ObjDef Object;

typedef struct ObjClass ObjClass;

struct Obj {
  EntityId eid;
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
void hashObject(void *obj, HashState *state);
Obj *asObjDef(const ObjDef *def, Value val);
Obj *newInstance(ObjClass *klass);
int inspectObject(FILE *io, Obj *obj);
int cmpObjects(Obj *a, Obj *b);

static inline bool isObjDef(Value value, const ObjDef *def) {
  return isObject(value) && AS_OBJ(value)->def == def;
}

typedef struct ObjComponent {
  Obj *obj;
} ObjComponent;

extern ECS_COMPONENT_DECLARE(ObjComponent);
// ECS_SYSTEM_DECLARE(MarkRelationships);

void ObjectsImport(World *world);

#endif
