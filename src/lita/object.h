#ifndef lita_object_h
#define lita_object_h

#include <stdarg.h>

typedef enum ObjType ObjType;
typedef struct ObjDef ObjDef;

#include "chunk.h"
#include "common.h"
#include "table.h"
#include "value.h"

#define getDef(val) (as_obj(val)->def)
#define as(def, val) ((Obj##def *)asObjDef(&def, val))
#define ALLOCATE_OBJ(def) ((Obj##def *)allocateObject(&def))
#define REGISTER_OBJECT_DEF(def) const SECTION(defs) ObjDef *def##_def = &def;
#define foreach_obj_def(var) section_foreach_entry(defs, ObjDef *, var)

typedef enum Ownership { UNOWNED, OWNED } Ownership;

typedef void ObjFn(Obj *obj);
typedef int ObjLengthFn(Obj *obj);
typedef int ObjIOFn(Obj *obj, FILE *io);
typedef const char *ObjBytesFn(Obj *obj, int length);

typedef struct ObjDef {
  const char *class_name;
  const usize size;
  const bool interned;
  ObjLengthFn *length;
  ObjFn *alloc;
  ObjFn *free;
  ObjFn *mark;
  ObjIOFn *inspect; /** NOTE: Why can't we invoke .inspect? */
  ObjIOFn *dump;
  ObjIOFn *dump_global;
  ObjBytesFn *bytes;
} ObjDef;

typedef struct ObjClass ObjClass;

struct Obj {
  EntityId eid;
  const ObjDef *def;
  bool isMarked;    /** Is marked by GC in the current mark cycle. */
  struct Obj *next; /** Linked list of objects used for GC. */
  Hash hash;        /** All objects have a hash value. */
  ObjClass *klass;
  Table fields; /** Fields assigned to this instance. */
};

// TODO: Use this for yield keyword?
// typedef struct ObjContinuation {
//   Obj obj;
//   ObjClosure *closure;
//   CallFrame frame; // must be moved; can't require vm.h
// } ObjContinuation;

Obj *allocateObject(const ObjDef *def);
Obj *asObjDef(const ObjDef *def, Value val);
Obj *as_obj(Value x);
Obj *new_instance(ObjClass *klass);
const char *objectBytes(Obj *obj, int length);
int inspect_obj(FILE *io, Obj *obj);
int cmpObjects(Obj *a, Obj *b);

// Value init_obj(Value klass, int argc, Value *args);

static inline bool is_obj_def(Value value, const ObjDef *def) {
  return is_obj(value) && AS_OBJ(value)->def == def;
}

static inline bool is_interned(Value val) {
  if (!is_obj(val)) return true;
  Obj *obj = AS_OBJ(val);
  return obj->def && obj->def->interned;
}

#endif
