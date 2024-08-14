#ifndef lita_tuple_h
#define lita_tuple_h

#include "common.h"
#include "object.h"

#define AS_TUPLE(val) ((ObjTuple *)AS_OBJ(val))
#define is_tuple(val) is_obj_def(val, &Tuple)

typedef struct ObjTuple {
  Obj obj;
  uint8_t length;
  Value *values;
} ObjTuple;

const ObjDef Tuple;

ObjTuple *as_tuple(Value val);
ObjTuple *copy_tuple(Value *values, uint8_t length);
ObjTuple *take_tuple(Value *values, uint8_t length);
ObjTuple *zip_tuples(ObjTuple *a, ObjTuple *b, Value (*fn)(Value, Value));

let t(int len, let *vals);
let t2(let a, let b);
let t3(let a, let b, let c);
let t4(let a, let b, let c, let d);
let t5(let a, let b, let c, let d, let e);
let t6(let a, let b, let c, let d, let e, let f);
let t7(let a, let b, let c, let d, let e, let f, let g);

// Tuple: (1, 2)
// Table: {x: 2}
// List: [1, 2]
// Set: {1, 2}
// Map: {1: 2}
// Range: 1..2
// String: "hello"

#endif
