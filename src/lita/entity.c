#include <assert.h>

#include "dump.h"
#include "entity.h"
#include "iterator.h"
#include "lib.h"
#include "memory.h"
#include "vm.h"

static void free_entity(Obj *obj) {
  ObjEntity *entity = (ObjEntity *)obj;
  freeTable(entity->values);
}

static void mark_entity(Obj *obj) {
  ObjEntity *entity = (ObjEntity *)obj;
  markTable(entity->values);
}

static const char *entity_bytes(Obj *obj, int length) {
  ObjEntity *entity = (ObjEntity *)obj;
  if (length != entity->values->len * sizeof(Value)) return NULL;
  return (char *)entity->values;
}

static int entity_length(Obj *obj) { return ((ObjEntity *)obj)->values->len; }

static int inspect_entity(Obj *obj, FILE *io) {
  ObjEntity *entity = (ObjEntity *)obj;
  return fprintf(io, "{") + inspect_table(io, entity->values) +
         fprintf(io, "}");
}

static int dump_entity(Obj *obj, FILE *io) {
  ObjEntity *entity = (ObjEntity *)obj;
  ObjIterator *iter = iterate_table(entity->values);
  int len = entity_length(obj);
  int tot = fprintf(io, "ent(%d", len);

  while (iterate_next(iter)) {
    tot += fprintf(io, ", ");
    dumpValue(io, iter->current[1]);
  }

  tot += fputs(")", io);
  return tot;
}

ObjEntity *as_entity(Value x) {
  assert(is_entity(x));
  return AS_ENTITY(x);
}

/**
 * Allocate an ObjEntity for a series of values.
 */
static ObjEntity *allocate_entity(Value *vals, int length, Hash hash) {
  ObjEntity *entity = new_entity();
  initTable(entity->values);
  for (int i = 0; i < length; i++) {
    tableSet(entity->values, classOf(vals[i]), vals[i]);
  }
  entity->obj.hash = hash;
  intern(OBJ_VAL(entity));
  return entity;
}

ObjEntity *copy_entity(Value *values, uint8_t length) {
  int size = length * sizeof(Value);
  Hash hash;
  ObjEntity *interned =
      (ObjEntity *)getInterned(&hash, OBJ_CUSTOM, (char *)values, size);

  if (interned != NULL) return interned;

  Value *heapVals = ALLOCATE(Value, length);
  memcpy(heapVals, values, size);

  return allocate_entity(heapVals, length, hash);
}

ObjEntity *take_entity(Value *values, uint8_t length) {
  Hash hash;
  Obj *interned =
      getInterned(&hash, OBJ_CUSTOM, (char *)values, length * sizeof(Entry));

  if (interned != NULL) {
    FREE_ARRAY(Value, values, length);
    return (ObjEntity *)interned;
  }

  return allocate_entity(values, length, hash);
}

// # Natives

static Value Entity_get(let this, int argc, let *args) {
  ObjEntity *entity = AS_ENTITY(this);
  let val;
  tableGet(entity->values, args[0], &val);
  return val;
}

// ObjFun *entity_lita();

static void entity_natives(let Entity) {
  // runFun(entity_lita());
  method(Entity, fn("get", 1, Entity_get));
}

const ObjDef Entity = {
    .class_name = "Entity",
    .size = sizeof(ObjEntity),
    .free = free_entity,
    .mark = mark_entity,
    .bytes = entity_bytes,
    .inspect = inspect_entity,
    .dump = dump_entity,
    .length = entity_length,
    .natives = entity_natives,
};

let ent(int len, let *vals) { return obj(copy_entity(vals, len)); }

let ent2(let a, let b) { return ent(2, (let[]){a, b}); }
let ent3(let a, let b, let c) { return ent(3, (let[]){a, b, c}); }
let ent4(let a, let b, let c, let d) { return ent(4, (let[]){a, b, c, d}); }
let ent5(let a, let b, let c, let d, let e) {
  return ent(5, (let[]){a, b, c, d, e});
}
let ent6(let a, let b, let c, let d, let e, let f) {
  return ent(6, (let[]){a, b, c, d, e, f});
}
let ent7(let a, let b, let c, let d, let e, let f, let g) {
  return ent(7, (let[]){a, b, c, d, e, f, g});
}
