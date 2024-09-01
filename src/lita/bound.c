#include <assert.h>

#include "bound.h"
#include "lib.h"
#include "memory.h"
#include "native.h"
#include "string.h"
#include "vm.h"

ObjBound *asBound(let val) {
  assert(isBound(val));
  return AS_BOUND(val);
}

let bound(let receiver, let method) { return obj(newBound(receiver, method)); }

ObjBound *newBound(let receiver, let method) {
  ObjBound *bound = allocateBound();
  bound->receiver = receiver;
  bound->method = method;
  return bound;
}

static int boundLength(Obj *obj) {
  ObjBound *bound = (ObjBound *)obj;
  return len(bound->method);
}

static void markBound(Obj *obj) {
  ObjBound *bound = (ObjBound *)obj;
  markValue(bound->receiver);
  markValue(bound->method);
}

static int inspectBound(Obj *obj, FILE *io) {
  ObjBound *bound = (ObjBound *)obj;

  return fstring_format(io, "Bound({}, {})", bound->receiver, bound->method);
}

NATIVE_GETTER(Bound, receiver, OBJ_VAL);
NATIVE_GETTER(Bound, method, OBJ_VAL);

REGISTER_OBJECT_DEF(Bound);
ObjDef Bound = {
    .class_name = "Bound",
    .size = sizeof(ObjBound),
    .mark = markBound,
    .inspect = inspectBound,
    .length = boundLength,
};
