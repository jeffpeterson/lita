#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "class.h"
#include "memory.h"
#include "object.h"
#include "table.h"
#include "vm.h"

Obj *allocateObject(const ObjDef *def) {
  Obj *obj = (Obj *)reallocate(NULL, 0, def->size);
  obj->def = def;
  obj->klass = NULL;
  obj->isMarked = false;
  obj->hash = 0;
  obj->next = vm.objects;
  vm.objects = obj;
  initTable(&obj->fields);

  obj->eid = ecs_insert(vm.world, ecs_value(ObjComponent, {obj}));

  if (def->alloc) def->alloc(obj);
  if (!def->hash) obj->hash = hashBytes(obj, def->size);

#if DEBUG_LOG_MEM
  fprintf(stderr, "%p allocate %zub for ", (void *)obj, size);
  // inspect_obj_type(stderr, type);
  fprintf(stderr, "\n");
#endif
  return obj;
}

Obj *internObject(Obj **objp) {
  Obj *obj = *objp;
  const ObjDef *def = obj->def;

  ASSERT_MSG(def->hash, def->className);

  HashState *state = startHash();
  hashPointer(obj->def, state);
  hashPointer(obj->klass, state);
  hashTable(state, &obj->fields);

  def->hash(obj, state);
  obj->hash = endHash(state);

  Obj *existing = tableFindObj(&vm.interned, obj->hash);
  if (existing) obj = *objp = existing;
  else tableSet(&vm.interned, OBJ_VAL(obj), True);

  return obj;
}

void hashObjectDefault(Obj *obj, HashState *state) {
  updateHash(state, obj + 1, obj->def->size - sizeof(Obj));
}

void hashObject(void *obj, HashState *state) {
  updateHash(state, &obj, sizeof(Obj *));
}

Obj *asObjDef(const ObjDef *def, Value val) {
  ASSERT_MSG(isObjDef(val, def), def->className);
  return AS_OBJ(val);
}

Obj *newInstance(ObjClass *klass) {
  Obj *obj = allocateObject(&Object);
  obj->klass = klass;
  return obj;
}

int inspectObject(FILE *io, Obj *obj) {
  if (!obj) return fprintf(io, "nil");
  if (obj->def->inspect) return obj->def->inspect(obj, io);
  return fprintf(io, "%s(", obj->klass->name->chars) +
         inspectTable(io, &obj->fields) + fprintf(io, ")");
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

const ObjDef Object = {
    .className = "Object",
    .size = sizeof(Obj),
};

ECS_COMPONENT_DECLARE(ObjComponent);

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

// void walkValue(Value val, WalkState *state) {
//   if (isObject(val)) walkObject(AS_OBJ(val), state);
//   else walkBytes(&val, sizeof(Value), state);
// }

// void walkTable(Table *table, WalkState *state) {
//   for (int i = 0; i < table->capacity; i++) {
//     Entry *entry = &table->entries[i];
//     if (entry->key) {
//       walkValue(entry->key, state);
//       walkValue(entry->value, state);
//     }
//   }
// }

// void walkObject(Obj *obj, WalkState *state) {
//   if (obj->def->walk) obj->def->walk(obj, state);
//   else walkTable(&obj->fields, state);
// }

// void hashObject(HashState *state, Obj *obj) {
//   Walk walk = {
//       .state = state,
//       .value = walkValue,
//       .object = walkObject,
//       .table = hashTable,
//       .bytes = hashBytes,
//   };
//   walkObject(&walk, obj);
// }
