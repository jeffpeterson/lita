#ifndef lita_tuple_h
#define lita_tuple_h

#include "common.h"
#include "object.h"

#define allocateTuple() ALLOCATE_OBJ(Tuple)
#define isTuple(val) isObjDef(val, &Tuple)
#define asTuple(val) as(Tuple, val)

typedef struct ObjTuple {
  Obj obj;
  u8 length;
  Value *values;
} ObjTuple;

extern const ObjDef Tuple;

ObjTuple *copyTuple(Value *values, u8 length);
ObjTuple *takeTuple(Value *values, u8 length);
ObjTuple *zipTuples(ObjTuple *a, ObjTuple *b, Value (*fn)(Value, Value));

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
