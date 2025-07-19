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

static int inspectClass(Obj *obj, FILE *io, int depth) {
  ObjClass *klass = (ObjClass *)obj;
  int sum = 0;
  sum += fprintf(io, FG_MAGENTA "%s" FG_DEFAULT, stringChars(klass->name)) -
         FG_SIZE * 2;

  if (!depth) {
    sum += fprintf(io, " {\n\t");
    sum += inspectTable(io, &klass->methods, depth);
    sum += fprintf(io, "\n}");
  }

  return sum;
}

static InterpretResult callClass(Obj *obj, int argc) {
  ObjClass *klass = (ObjClass *)obj;
  // Replace the class with a new instance.
  vm.stackTop[-argc - 1] = OBJ_VAL(newInstance(klass));
  return vmInvoke(string("init"), argc);
}

Value get_method(ObjClass *klass, ObjString *name) {
  Value method;
  if (tableGet(&klass->methods, OBJ_VAL(name), &method)) return method;

  if (klass->parent) return get_method(klass->parent, name);

  return NIL_VAL;
}

NATIVE_GETTER(Class, name, OBJ_VAL);
NATIVE_GETTER(Class, parent, OBJ_VAL);

NATIVE_METHOD(Class, method, 1) {
  return get_method(asClass(this), asString(args[0]));
}

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
