#include "tuple.h"
#include "memory.h"
#include "vm.h"

static void free_tuple(ObjTuple *tuple) {
  FREE_ARRAY(Value, tuple->values, tuple->length);
}

static void mark_tuple(ObjTuple *tuple) {
  for (int i = 0; i < tuple->length; i++) markValue(tuple->values[i]);
}

const ObjDef tuple_def = {
    .class_name = "Tuple",
    .size = sizeof(ObjTuple),
    .free = (ObjFn *)free_tuple,
    .mark = (ObjFn *)mark_tuple,
};

/**
 * Allocate an ObjTuple for a series of values.
 */
static ObjTuple *allocateTuple(Value *vals, int length, Hash hash) {
  ObjTuple *tuple = ALLOCATE_OBJ(ObjTuple, OBJ_TUPLE);
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
      (ObjTuple *)getInterned(&hash, OBJ_TUPLE, (char *)values, size);

  if (interned != NULL) return interned;

  Value *heapVals = ALLOCATE(Value, length);
  memcpy(heapVals, values, size);

  return allocateTuple(heapVals, length, hash);
}

ObjTuple *takeTuple(Value *values, uint8_t length) {
  Hash hash;
  Obj *interned =
      getInterned(&hash, OBJ_TUPLE, (char *)values, length * sizeof(Value));

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
