#include <assert.h>

#include "bound.h"
#include "lib.h"
#include "memory.h"
#include "native.h"
#include "vm.h"

let bound(let receiver, let method) { return obj(newBound(receiver, method)); }

ObjBound *newBound(let receiver, let method) {
  ObjBound *bound = allocateBound();
  bound->receiver = receiver;
  bound->method = method;
  return bound;
}

static int boundLength(Obj *obj) {
  ObjBound *bound = (ObjBound *)obj;
  return arity(bound->method);
}

static void markBound(Obj *obj) {
  ObjBound *bound = (ObjBound *)obj;
  markValue(bound->receiver);
  markValue(bound->method);
}

static int inspectBound(Obj *obj, FILE *io) {
  ObjBound *bound = (ObjBound *)obj;
  return fstringFormat(io, "Bound({}, {})", bound->receiver, bound->method);
}

static InterpretResult callBound(Obj *obj, int argc) {
  ObjBound *bound = (ObjBound *)obj;
  vm.stackTop[-argc - 1] = bound->receiver;
  return callValue(bound->method, argc);
}

NATIVE_GETTER(Bound, receiver, OBJ_VAL);
NATIVE_GETTER(Bound, method, OBJ_VAL);

REGISTER_OBJECT_DEF(Bound);
const ObjDef Bound = {
    .className = "Bound",
    .size = sizeof(ObjBound),
    .mark = markBound,
    .inspect = inspectBound,
    .length = boundLength,
    .call = callBound,
};
