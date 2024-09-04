#include <assert.h>

#include "dump.h"
#include "lib.h"
#include "memory.h"
#include "native.h"
#include "tuple.h"
#include "vm.h"

let t(int len, let *vals) { return obj(copy_tuple(vals, len)); }

let t2(let a, let b) { return t(2, (let[]){a, b}); }
let t3(let a, let b, let c) { return t(3, (let[]){a, b, c}); }
let t4(let a, let b, let c, let d) { return t(4, (let[]){a, b, c, d}); }
let t5(let a, let b, let c, let d, let e) {
  return t(5, (let[]){a, b, c, d, e});
}
let t6(let a, let b, let c, let d, let e, let f) {
  return t(6, (let[]){a, b, c, d, e, f});
}
let t7(let a, let b, let c, let d, let e, let f, let g) {
  return t(7, (let[]){a, b, c, d, e, f, g});
}

/**
 * Allocate an ObjTuple for a series of values.
 */
static ObjTuple *newTuple(Value *vals, int length, Hash hash) {
  ObjTuple *tuple = allocateTuple();
  tuple->length = length;
  tuple->values = vals;
  tuple->obj.hash = hash;
  intern(OBJ_VAL(tuple));
  return tuple;
}

ObjTuple *copy_tuple(Value *values, uint8_t length) {
  int size = length * sizeof(Value);
  Hash hash;
  ObjTuple *interned = (ObjTuple *)getInterned(&hash, (char *)values, size);

  if (interned != NULL) return interned;

  Value *heapVals = ALLOCATE(Value, length);
  memcpy(heapVals, values, size);

  return newTuple(heapVals, length, hash);
}

ObjTuple *take_tuple(Value *values, uint8_t length) {
  Hash hash;
  Obj *interned = getInterned(&hash, (char *)values, length * sizeof(Value));

  if (interned != NULL) {
    FREE_ARRAY(Value, values, length);
    return (ObjTuple *)interned;
  }

  return newTuple(values, length, hash);
}

ObjTuple *zip_tuples(ObjTuple *a, ObjTuple *b, Value (*fn)(Value, Value)) {
  if (a->length != b->length) {
    runtimeError("Tuples must be same size.");
    return NULL;
  }

  uint8_t length = a->length;
  Value *values = ALLOCATE(Value, length);

  for (uint8_t i = 0; i < length; i++) {
    values[i] = fn(a->values[i], b->values[i]);
  }

  return take_tuple(values, length);
}

NATIVE_METHOD_NAMED(Tuple, add, "+", 1) {
  // return obj(zip_tuples(asTuple(this), asTuple(args[0]), add));
  return nil;
}

NATIVE_METHOD(Tuple, get, 1) {
  ObjTuple *tuple = asTuple(this);
  u32 idx = as_num(args[0]);
  if (idx >= tuple->length) return nil;
  return tuple->values[idx];
}

NATIVE_METHOD(Tuple, map, 1) {
  ObjTuple *tuple = asTuple(this);
  let fun = args[0];
  usize i = CURRENT_FRAME->reentries;

  if (i < tuple->length) {
    push(fun);
    push(tuple->values[i]);
    if (arity(fun) == 2) {
      push(number(i));
      vm_call(2);
    } else vm_call(1);
    return VOID;
  } else {
    vm_tuple(tuple->length);
    return pop();
  }
}

static void markTuple(Obj *obj) {
  ObjTuple *tuple = (ObjTuple *)obj;
  for (int i = 0; i < tuple->length; i++) markValue(tuple->values[i]);
}

static void freeTuple(Obj *obj) {
  ObjTuple *tuple = (ObjTuple *)obj;
  FREE_ARRAY(Value, tuple->values, tuple->length);
}

static const char *tupleBytes(Obj *obj, int length) {
  ObjTuple *tuple = (ObjTuple *)obj;
  if (length != tuple->length * sizeof(Value)) return NULL;
  return (char *)tuple->values;
}

static int tupleLength(Obj *obj) { return ((ObjTuple *)obj)->length; }

static int inspectTuple(Obj *obj, FILE *io) {
  ObjTuple *tuple = (ObjTuple *)obj;
  int tot = fprintf(io, "(");
  for (int i = 0; i < tuple->length; i++) {
    if (i > 0) tot += fprintf(io, ", ");
    tot += inspect_value(io, tuple->values[i]);
  }
  return fprintf(io, ")") + tot;
}

static int dumpTuple(Obj *obj, FILE *io) {
  ObjTuple *tuple = (ObjTuple *)obj;
  int tot = fprintf(io, "t(%d", tuple->length);

  for (int i = 0; i < tuple->length; i++) {
    tot += fprintf(io, ", ");
    dumpValue(io, tuple->values[i]);
  }

  tot += fputs(")", io);
  return tot;
}

COMPILED_SOURCE(tuple);

REGISTER_OBJECT_DEF(Tuple);
const ObjDef Tuple = {
    .class_name = "Tuple",
    .size = sizeof(ObjTuple),
    .interned = true,
    .free = freeTuple,
    .mark = markTuple,
    .bytes = tupleBytes,
    .inspect = inspectTuple,
    .dump = dumpTuple,
    .length = tupleLength,
};
