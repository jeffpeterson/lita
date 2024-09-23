#include "class.h"
#include "memory.h"
#include "native.h"
#include "string.h"
#include "term.h"
#include "vm.h"

let class(const char *name) { return obj(newClass(newString(name))); }

ObjClass *newClass(ObjString *name) {
  ObjClass *klass = allocateClass();
  klass->name = name;
  return klass;
}

static void allocClass(Obj *obj) {
  ObjClass *klass = (ObjClass *)obj;
  klass->parent = NULL;
  initTable(&klass->methods);
}

static int classLength(Obj *obj) {
  // ObjClass *klass = (ObjClass *)obj;
  return 0; // klass->length;
}

static void markClass(Obj *obj) {
  ObjClass *klass = (ObjClass *)obj;
  markObject((Obj *)klass->name);
  markObject((Obj *)klass->parent);
  markTable(&klass->methods);
}

static void freeClass(Obj *obj) {
  ObjClass *klass = (ObjClass *)obj;
  freeTable(&klass->methods);
}

static int inspectClass(Obj *obj, FILE *io) {
  ObjClass *klass = (ObjClass *)obj;
  return fprintf(io, FG_MAGENTA "%s" FG_DEFAULT, stringChars(klass->name)) -
         FG_SIZE * 2;
}

static InterpretResult callClass(Obj *obj, int argc) {
  ObjClass *klass = (ObjClass *)obj;
  // Replace the class with a new instance.
  vm.stackTop[-argc - 1] = OBJ_VAL(newInstance(klass));
  return vmInvoke(OBJ_VAL(string("init")), argc);
}

NATIVE_GETTER(Class, name, OBJ_VAL);
NATIVE_GETTER(Class, parent, OBJ_VAL);

REGISTER_OBJECT_DEF(Class);
const ObjDef Class = {
    .className = "Class",
    .size = sizeof(ObjClass),
    .alloc = allocClass,
    .free = freeClass,
    .mark = markClass,
    .inspect = inspectClass,
    .length = classLength,
    .call = callClass,
};
