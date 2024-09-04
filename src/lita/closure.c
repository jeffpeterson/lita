#include <assert.h>

#include "closure.h"
#include "memory.h"
#include "native.h"
#include "string.h"
#include "term.h"
#include "vm.h"

ObjClosure *newClosure(ObjFunction *function) {
  ObjUpvalue **upvalues = ALLOCATE(ObjUpvalue *, function->upvalueCount);
  for (int i = 0; i < function->upvalueCount; i++) upvalues[i] = NULL;

  ObjClosure *closure = allocateClosure();
  closure->function = function;
  closure->upvalues = upvalues;
  closure->upvalueCount = function->upvalueCount;
  return closure;
}

static int closureLength(Obj *obj) {
  ObjClosure *closure = (ObjClosure *)obj;
  return closure->function->arity;
}

static void markClosure(Obj *obj) {
  ObjClosure *closure = (ObjClosure *)obj;
  markObject((Obj *)closure->function);
  for (int i = 0; i < closure->upvalueCount; i++) {
    markObject((Obj *)closure->upvalues[i]);
  }
}

static void freeClosure(Obj *obj) {
  ObjClosure *closure = (ObjClosure *)obj;
  FREE_ARRAY(ObjUpvalue *, closure->upvalues, closure->upvalueCount);
}

static int inspectClosure(Obj *obj, FILE *io) {
  ObjClosure *closure = (ObjClosure *)obj;
  return fprintf(io,
                 FG_MAGENTA "<closure %s" FG_DEFAULT "/" FG_MAGENTA
                            "%d>" FG_DEFAULT,
                 closure->function->name->chars, closure->function->arity) -
         FG_SIZE * 4;
}

NATIVE_GETTER(Closure, function, OBJ_VAL);
NATIVE_DELEGATE_TO(Closure, name, function);
NATIVE_DELEGATE_TO(Closure, arity, function);
NATIVE_DELEGATE_TO(Closure, bytes, function);
NATIVE_DELEGATE_TO(Closure, byteCount, function);

REGISTER_OBJECT_DEF(Closure);
ObjDef Closure = {
    .class_name = "Closure",
    .size = sizeof(ObjClosure),
    .mark = markClosure,
    .free = freeClosure,
    .inspect = inspectClosure,
    .length = closureLength,
};
