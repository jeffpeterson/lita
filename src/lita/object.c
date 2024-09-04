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
  usize size = def && def->size ? def->size : sizeof(Obj);
  Obj *obj = (Obj *)reallocate(NULL, 0, size);
  obj->def = def;
  obj->klass =
      asClass(global_class(def->class_name ? def->class_name : "Object"));
  obj->isMarked = false;
  obj->eid = ecs_new(vm.world);
  // Todo: Only hash for non-interned objects.
  Value val = OBJ_VAL(obj);
  obj->hash = hash_bytes((char *)&val, sizeof(Value));
  obj->next = vm.objects;
  vm.objects = obj;
  initTable(&obj->fields);

  if (def->alloc) def->alloc(obj);

#if DEBUG_LOG_MEM
  fprintf(stderr, "%p allocate %zub for ", (void *)obj, size);
  // inspect_obj_type(stderr, type);
  fprintf(stderr, "\n");
#endif
  return obj;
}

Obj *asObjDef(const ObjDef *def, Value val) {
  assert(is_obj_def(val, def));
  return AS_OBJ(val);
}
Obj *as_obj(Value x) {
  assert(is_obj(x));
  return AS_OBJ(x);
}

Obj *new_instance(ObjClass *klass) {
  Obj *obj = allocateObject(NULL);
  obj->klass = klass;
  return obj;
}

const char *objectBytes(Obj *obj, int length) {
  if (obj->def && obj->def->bytes) return obj->def->bytes(obj, length);

  if (length != obj->def->size) return NULL;
  return (char *)&obj->hash;
}

int inspect_obj(FILE *io, Obj *obj) {
  if (obj->def && obj->def->inspect) return obj->def->inspect(obj, io);
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

//   Value init = findMethod(klass, str("init"));
//   if (is_nil(init)) return obj;

//   return call(init, obj, argc, args);
// }
