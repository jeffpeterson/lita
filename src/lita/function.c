#include <assert.h>

#include "dump.h"
#include "function.h"
#include "memory.h"
#include "native.h"
#include "term.h"
#include "vm.h"

ObjFunction *newFunction() { return allocateFunction(); }

void allocFunction(Obj *obj) {
  ObjFunction *function = (ObjFunction *)obj;
  function->arity = 0;
  function->upvalueCount = 0;
  function->name = NULL;
  initChunk(&function->chunk);
}

static int functionLength(Obj *obj) {
  ObjFunction *function = (ObjFunction *)obj;
  return function->arity;
}

static void markFunction(Obj *obj) {
  ObjFunction *function = (ObjFunction *)obj;
  markObject((Obj *)function->name);
  markChunk(&function->chunk);
}

static void freeFunction(Obj *obj) {
  ObjFunction *function = (ObjFunction *)obj;
  freeChunk(&function->chunk);
}

static int inspectFunction(Obj *obj, FILE *io) {
  ObjFunction *function = (ObjFunction *)obj;
  return fprintf(io,
                 FG_MAGENTA "<function %s" FG_DEFAULT "/" FG_MAGENTA
                            "%d>" FG_DEFAULT,
                 function->name->chars, function->arity) -
         FG_SIZE * 4;
}

static int dumpFunction(Obj *obj, FILE *io) {
  ObjFunction *fun = (ObjFunction *)obj;
  Value id;

  if (tableGet(&ids, OBJ_VAL(obj), &id))
    return fprintf(io, "fn_%s_%g()", string_to_c_ident(fun->name)->chars,
                   as_num(id));
  else return fprintf(io, "crash(\"Could not find fn %s\")", fun->name->chars);
}

NATIVE_GETTER(Function, arity, NUMBER_VAL);
NATIVE_GETTER(Function, variadic, BOOL_VAL);
NATIVE_GETTER(Function, name, OBJ_VAL);

REGISTER_OBJECT_DEF(Function);
ObjDef Function = {
    .class_name = "Function",
    .size = sizeof(ObjFunction),
    .mark = markFunction,
    .free = freeFunction,
    .inspect = inspectFunction,
    .length = functionLength,
};
