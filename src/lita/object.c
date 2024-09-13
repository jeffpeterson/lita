#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "class.h"
#include "lib.h"
#include "memory.h"
#include "object.h"
#include "table.h"
#include "term.h"
#include "vm.h"

Obj *allocateObject(const ObjDef *def) {
  usize size = def->size;
  Obj *obj = (Obj *)reallocate(NULL, 0, size);
  obj->def = def;
  obj->klass = NULL;
  obj->isMarked = false;
  // Todo: Only hash for non-interned objects.
  Value val = OBJ_VAL(obj);
  obj->hash = hashBytes((char *)&val, sizeof(Value));
  obj->next = vm.objects;
  vm.objects = obj;
  initTable(&obj->fields);

  obj->eid = ecs_insert(vm.world, ecs_value(ObjComponent, {obj}));

  if (def->alloc) def->alloc(obj);

#if DEBUG_LOG_MEM
  fprintf(stderr, "%p allocate %zub for ", (void *)obj, size);
  // inspect_obj_type(stderr, type);
  fprintf(stderr, "\n");
#endif
  return obj;
}

Obj *asObjDef(const ObjDef *def, Value val) {
  assert(isObjDef(val, def));
  return AS_OBJ(val);
}

Obj *newInstance(ObjClass *klass) {
  Obj *obj = allocateObject(&Object);
  obj->klass = klass;
  return obj;
}

const char *objectBytes(Obj *obj, int length) {
  if (obj->def->bytes) return obj->def->bytes(obj, length);

  if (length != obj->def->size) return NULL;
  return (char *)&obj->hash;
}

int inspectObject(FILE *io, Obj *obj) {
  if (!obj) return fprintf(io, "nil");
  if (obj->def->inspect) return obj->def->inspect(obj, io);
  return fprintf(io, "%s(", obj->klass->name->chars) +
         inspect_table(io, &obj->fields) + fprintf(io, ")");
}

int cmpObjects(Obj *a, Obj *b) {
  int td = a->def - b->def;

  if (td != 0) return td;

  if (a == b) return 0;

  // Todo: finish
  return a - b;
}

// Value init_obj(Value klass, int argc, Value *args) {
//   if (!isClass(klass)) return NIL_VAL;

//   ObjClass *class = AS_CLASS(klass);
//   Value obj = OBJ_VAL(newObject(class));

//   Value init = findMethod(klass, string("init"));
//   if (isNil(init)) return obj;

//   return call(init, obj, argc, args);
// }

ObjDef Object = {
    .className = "Object",
    .size = sizeof(Obj),
};

void markRelationships(World *world, EntityId eid){
    // ecs_query_t *q = ecs_query(
    //     world, {.terms = {{.first.id = EcsWildcard, .second.name =
    //     "$target"},
    //                       {ecs_id(ObjComponent), .src.name = "$target"}}});
};

void ObjectsImport(World *world) {
  ECS_MODULE(world, Objects);

  ECS_COMPONENT_DEFINE(world, ObjComponent);

  // ECS_SYSTEM(world, MarkRelationships, 0, ObjComponent, (*, ObjComponent));
}
