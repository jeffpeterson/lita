#include <assert.h>

#include "memory.h"
#include "native.h"
#include "string.h"
#include "upvalue.h"
#include "vm.h"

ObjUpvalue *newUpvalue(Value *slot) {
  ObjUpvalue *upvalue = allocateUpvalue();
  upvalue->closed = NIL_VAL;
  upvalue->location = slot;
  upvalue->next = NULL;
  return upvalue;
}

static void markUpvalue(Obj *obj) { markValue(((ObjUpvalue *)obj)->closed); }

static int inspectUpvalue(Obj *obj, FILE *io) {
  ObjUpvalue *upvalue = (ObjUpvalue *)obj;
  return fprintf(io, "<upvalue(%s) -> ", upvalue->closed ? "closed" : "open") +
         inspectValue(io, *upvalue->location) + fprintf(io, ">");
}

NATIVE_GETTER(Upvalue, closed, OBJ_VAL);
NATIVE_GETTER(Upvalue, location, *);

REGISTER_OBJECT_DEF(Upvalue);
ObjDef Upvalue = {
    .className = "Upvalue",
    .size = sizeof(ObjUpvalue),
    .mark = markUpvalue,
    .inspect = inspectUpvalue,
};
