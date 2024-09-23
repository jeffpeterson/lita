#include "tuple.h"
#include "dump.h"
#include "lib.h"
#include "memory.h"
#include "native.h"
#include "vm.h"

let t(int len, let *values) { return obj(copyTuple(values, len)); }

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

ObjTuple *takeTuple(Value *values, u8 length) {
  ObjTuple *tuple = allocateTuple();
  tuple->length = length;
  tuple->values = values;
  internObject((Obj **)&tuple);
  return tuple;
}

ObjTuple *copyTuple(Value *values, u8 length) {
  Value *heapVals = ALLOCATE(Value, length);
  copyValues(values, heapVals, length);
  return takeTuple(heapVals, length);
}

ObjTuple *zipTuples(ObjTuple *a, ObjTuple *b, Value (*fn)(Value, Value)) {
  if (a->length != b->length) {
    runtimeError("Tuples must be same size.");
    return NULL;
  }

  u8 length = a->length;
  Value *values = ALLOCATE(Value, length);

  for (u8 i = 0; i < length; i++) {
    values[i] = fn(a->values[i], b->values[i]);
  }

  return takeTuple(values, length);
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
      vmCall(2);
    } else vmCall(1);
    return VOID;
  } else {
    vmTuple(tuple->length);
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

static void hashTuple(Obj *obj, HashState *state) {
  ObjTuple *tuple = (ObjTuple *)obj;
  updateHash(state, tuple->values, tuple->length * sizeof(Value));
}

static int tupleLength(Obj *obj) { return ((ObjTuple *)obj)->length; }

static int inspectTuple(Obj *obj, FILE *io) {
  ObjTuple *tuple = (ObjTuple *)obj;
  int tot = fprintf(io, "(");
  for (int i = 0; i < tuple->length; i++) {
    if (i > 0) tot += fprintf(io, ", ");
    tot += inspectValue(io, tuple->values[i]);
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
    .className = "Tuple",
    .size = sizeof(ObjTuple),
    .hash = hashTuple,
    .free = freeTuple,
    .mark = markTuple,
    .inspect = inspectTuple,
    .dump = dumpTuple,
    .length = tupleLength,
};
