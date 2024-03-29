#include <assert.h>

#include "dump.h"
#include "lib.h"
#include "memory.h"
#include "tuple.h"
#include "vm.h"

static void free_tuple(Obj *obj) {
  ObjTuple *tuple = (ObjTuple *)obj;
  FREE_ARRAY(Value, tuple->values, tuple->length);
}

static void mark_tuple(Obj *obj) {
  ObjTuple *tuple = (ObjTuple *)obj;
  for (int i = 0; i < tuple->length; i++) markValue(tuple->values[i]);
}

static const char *tuple_bytes(Obj *obj, int length) {
  ObjTuple *tuple = (ObjTuple *)obj;
  if (length != tuple->length * sizeof(Value)) return NULL;
  return (char *)tuple->values;
}

static int tuple_length(Obj *obj) { return ((ObjTuple *)obj)->length; }

static int inspect_tuple(Obj *obj, FILE *io) {
  ObjTuple *tuple = (ObjTuple *)obj;
  int tot = fprintf(io, "(");
  for (int i = 0; i < tuple->length; i++) {
    if (i > 0) tot += fprintf(io, ", ");
    tot += inspect_value(tuple->values[i], io);
  }
  return fprintf(io, ")") + tot;
}

static int dump_tuple(Obj *obj, FILE *io) {
  ObjTuple *tup = (ObjTuple *)obj;
  int tot = fprintf(io, "t(%d", tup->length);

  for (int i = 0; i < tup->length; i++) {
    tot += fprintf(io, ", ");
    dumpValue(io, tup->values[i]);
  }

  tot += fputs(")", io);
  return tot;
}

ObjTuple *as_tuple(Value x) {
  assert(is_tuple(x));
  return AS_TUPLE(x);
}

/**
 * Allocate an ObjTuple for a series of values.
 */
static ObjTuple *allocateTuple(Value *vals, int length, Hash hash) {
  ObjTuple *tuple = ALLOCATE_OBJ(ObjTuple, OBJ_CUSTOM);
  tuple->obj.def = &tuple_def;
  tuple->length = length;
  tuple->values = vals;
  tuple->obj.hash = hash;
  intern(OBJ_VAL(tuple));
  return tuple;
}

ObjTuple *copyTuple(Value *values, uint8_t length) {
  int size = length * sizeof(Value);
  Hash hash;
  ObjTuple *interned =
      (ObjTuple *)getInterned(&hash, OBJ_CUSTOM, (char *)values, size);

  if (interned != NULL) return interned;

  Value *heapVals = ALLOCATE(Value, length);
  memcpy(heapVals, values, size);

  return allocateTuple(heapVals, length, hash);
}

ObjTuple *takeTuple(Value *values, uint8_t length) {
  Hash hash;
  Obj *interned =
      getInterned(&hash, OBJ_CUSTOM, (char *)values, length * sizeof(Value));

  if (interned != NULL) {
    FREE_ARRAY(Value, values, length);
    return (ObjTuple *)interned;
  }

  return allocateTuple(values, length, hash);
}

ObjTuple *zipTuples(ObjTuple *a, ObjTuple *b, Value (*fn)(Value, Value)) {
  if (a->length != b->length) {
    runtimeError("Tuples must be same size.");
    return NULL;
  }

  uint8_t length = a->length;
  Value *values = ALLOCATE(Value, length);

  for (uint8_t i = 0; i < length; i++) {
    values[i] = fn(a->values[i], b->values[i]);
  }

  return takeTuple(values, length);
}

/// Native
static let Tuple_map(let this, int argc, let *args) {
  if (!argc) return error("map() requires a callable argument");
  ObjTuple *tuple = AS_TUPLE(this);
  let fun = args[0];

  for (u8 i = 0; i < tuple->length; i++) {
    push(fun);
    push(tuple->values[i]);
    vm_call(1);
  }
  vm_tuple(tuple->length);
  return pop();
}

static void tuple_natives(let klass) { method(klass, fn("map", 1, Tuple_map)); }

const ObjDef tuple_def = {
    .class_name = "Tuple",
    .size = sizeof(ObjTuple),
    .interned = true,
    .free = free_tuple,
    .mark = mark_tuple,
    .bytes = tuple_bytes,
    .inspect = inspect_tuple,
    .dump = dump_tuple,
    .length = tuple_length,
    .natives = tuple_natives,
};
