
#include "function.h"
#include "dump.h"
#include "lib.h"
#include "memory.h"
#include "native.h"
#include "term.h"
#include "vm.h"

ObjFunction *newFunction() { return allocateFunction(); }

static void allocFunction(Obj *obj) {
  ObjFunction *function = (ObjFunction *)obj;
  function->arity = 0;
  function->variadic = false;
  function->upvalueCount = 0;
  function->name = NULL;
  function->location = NULL;
  initChunk(&function->chunk);
}

static int functionLength(Obj *obj) {
  ObjFunction *function = (ObjFunction *)obj;
  return function->arity;
}

static void markFunction(Obj *obj) {
  ObjFunction *function = (ObjFunction *)obj;
  markObject((Obj *)function->name);
  markObject((Obj *)function->location);
  markChunk(&function->chunk);
}

static void freeFunction(Obj *obj) {
  ObjFunction *function = (ObjFunction *)obj;
  freeChunk(&function->chunk);
}

static int inspectFunction(Obj *obj, FILE *io, int depth) {
  ObjFunction *function = (ObjFunction *)obj;
  return fprintf(io, FG_MAGENTA "<function %s/%d (" FG_DEFAULT,
                 stringChars(function->name), function->arity) +
         inspectObject(io, (Obj *)function->location, depth + 1) +
         fprintf(io, FG_MAGENTA ")>" FG_DEFAULT) - FG_SIZE * 7;
}

static int dumpFunction(Obj *obj, FILE *io) {
  ObjFunction *fun = (ObjFunction *)obj;
  Value id;

  if (tableGet(&ids, OBJ_VAL(obj), &id))
    return fprintf(io, "fn_%s_%g()", stringToCIdent(fun->name)->chars,
                   as_num(id));
  else return fprintf(io, "crash(\"Could not find fn %s\")", fun->name->chars);
}

static InterpretResult callFunction(Obj *obj, int argc) {
  ObjFunction *fun = (ObjFunction *)obj;

  if (argc < fun->arity)
    return runtimeError("Expected %d arguments but got %d.", fun->arity, argc);

  if (fun->variadic) {
    vmArray(argc - fun->arity);
    argc = fun->arity + 1;
  }

  CallFrame *frame = newFrame(obj, argc + 1);
  if (!frame) return runtimeError("Call stack overflow.");
  frame->ip = fun->chunk.code;

  return INTERPRET_OK;
}

NATIVE_GETTER(Function, arity, NUMBER_VAL);
NATIVE_GETTER(Function, variadic, BOOL_VAL);
NATIVE_GETTER(Function, name, OBJ_VAL);
NATIVE_METHOD(Function, bytes, 0) {
  ObjFunction *fun = asFunction(this);
  return memory(fun->chunk.code, fun->chunk.count);
}
NATIVE_METHOD(Function, byteCount, 0) {
  ObjFunction *fn = asFunction(this);
  return number(fn->chunk.count);
}

REGISTER_OBJECT_DEF(Function);
const ObjDef Function = {
    .className = "Function",
    .size = sizeof(ObjFunction),
    .alloc = allocFunction,
    .mark = markFunction,
    .free = freeFunction,
    .inspect = inspectFunction,
    .length = functionLength,
    .dump = dumpFunction,
    .call = callFunction,
};
