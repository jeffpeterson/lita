#include <assert.h>

#include "dump.h"
#include "lib.h"
#include "memory.h"
#include "native.h"
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
    tot += inspect_value(io, tuple->values[i]);
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
static ObjTuple *allocate_tuple(Value *vals, int length, Hash hash) {
  ObjTuple *tuple = (ObjTuple *)new_object(&Tuple);
  tuple->length = length;
  tuple->values = vals;
  tuple->obj.hash = hash;
  intern(OBJ_VAL(tuple));
  return tuple;
}

ObjTuple *copy_tuple(Value *values, uint8_t length) {
  int size = length * sizeof(Value);
  Hash hash;
  ObjTuple *interned =
      (ObjTuple *)getInterned(&hash, OBJ_CUSTOM, (char *)values, size);

  if (interned != NULL) return interned;

  Value *heapVals = ALLOCATE(Value, length);
  memcpy(heapVals, values, size);

  return allocate_tuple(heapVals, length, hash);
}

ObjTuple *take_tuple(Value *values, uint8_t length) {
  Hash hash;
  Obj *interned =
      getInterned(&hash, OBJ_CUSTOM, (char *)values, length * sizeof(Value));

  if (interned != NULL) {
    FREE_ARRAY(Value, values, length);
    return (ObjTuple *)interned;
  }

  return allocate_tuple(values, length, hash);
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

// # Natives

NATIVE_METHOD_NAMED(Tuple, add, "+", 1) {
  return obj(zip_tuples(as_tuple(this), as_tuple(args[0]), add));
}

NATIVE_METHOD(Tuple, get, 1) {
  ObjTuple *tuple = AS_TUPLE(this);
  u32 idx = as_num(args[0]);
  if (idx >= tuple->length) return nil;
  return tuple->values[idx];
}

// NATIVE_METHOD(Tuple, map, 1) {
//   ObjTuple *tuple = AS_TUPLE(this);
//   let fun = args[0];

//   for (u8 i = 0; i < tuple->length; i++) {
//     push(fun);
//     push(tuple->values[i]);
//     vm_call(1);
//   }
//   vm_tuple(tuple->length);
//   return pop();
// }

// NATIVE_METHOD_NAMED(Tuple, star, "*", 1) {
//   if (is_tuple(args[0]))
//     return obj(zip_tuples(as_tuple(this), as_tuple(args[0]), multiply));
//   else return Tuple_map(this, argc, args);
// }

COMPILED_SOURCE(tuple);

REGISTER_OBJECT_DEF(Tuple);
const ObjDef Tuple = {
    .class_name = "Tuple",
    .size = sizeof(ObjTuple),
    .interned = true,
    .free = free_tuple,
    .mark = mark_tuple,
    .bytes = tuple_bytes,
    .inspect = inspect_tuple,
    .dump = dump_tuple,
    .length = tuple_length,
};

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
