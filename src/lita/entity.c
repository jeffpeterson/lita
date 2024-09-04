#include <assert.h>

#include "dump.h"
#include "entity.h"
#include "iterator.h"
#include "lib.h"
#include "memory.h"
#include "native.h"
#include "vm.h"

/**
 * Allocate an ObjEntity for a series of values.
 */
static ObjEntity *makeEntity(Value *vals, int length, Hash hash) {
  ObjEntity *entity = allocateEntity();
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
  ObjEntity *interned = (ObjEntity *)getInterned(&hash, (char *)values, size);

  if (interned != NULL) return interned;

  Value *heapVals = ALLOCATE(Value, length);
  memcpy(heapVals, values, size);

  return makeEntity(heapVals, length, hash);
}

ObjEntity *take_entity(Value *values, uint8_t length) {
  Hash hash;
  Obj *interned = getInterned(&hash, (char *)values, length * sizeof(Entry));

  if (interned != NULL) {
    FREE_ARRAY(Value, values, length);
    return (ObjEntity *)interned;
  }

  return makeEntity(values, length, hash);
}

// # Natives

NATIVE_METHOD(Entity, get, 1) {
  ObjEntity *entity = asEntity(this);
  let val;
  tableGet(entity->values, args[0], &val);
  return val;
}

static void freeEntity(Obj *obj) {
  ObjEntity *entity = (ObjEntity *)obj;
  freeTable(entity->values);
}

static void markEntity(Obj *obj) {
  ObjEntity *entity = (ObjEntity *)obj;
  markTable(entity->values);
}

static const char *entityBytes(Obj *obj, int length) {
  ObjEntity *entity = (ObjEntity *)obj;
  if (length != entity->values->len * sizeof(Value)) return NULL;
  return (char *)entity->values;
}

static int entityLength(Obj *obj) {
  ObjEntity *entity = (ObjEntity *)obj;
  return entity->values->len;
}

static int inspectEntity(Obj *obj, FILE *io) {
  ObjEntity *entity = (ObjEntity *)obj;
  return fprintf(io, "{") + inspect_table(io, entity->values) +
         fprintf(io, "}");
}

static int dumpEntity(Obj *obj, FILE *io) {
  ObjEntity *entity = (ObjEntity *)obj;
  ObjIterator *iter = iterate_table(entity->values);
  int len = entityLength((Obj *)entity);
  int tot = fprintf(io, "ent(%d", len);

  while (iterateNext(iter)) {
    tot += fprintf(io, ", ");
    dumpValue(io, iter->current[1]);
  }

  tot += fputs(")", io);
  return tot;
}

const ObjDef Entity = {
    .class_name = "Entity",
    .size = sizeof(ObjEntity),
    .free = freeEntity,
    .mark = markEntity,
    .bytes = entityBytes,
    .inspect = inspectEntity,
    .dump = dumpEntity,
    .length = entityLength,
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
