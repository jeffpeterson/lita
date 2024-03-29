#ifndef lita_tuple_h
#define lita_tuple_h

#include "common.h"
#include "object.h"

#define AS_TUPLE(val) ((ObjTuple *)AS_OBJ(val))
#define is_tuple(val) is_obj_def(val, &tuple_def)

typedef struct ObjTuple {
  Obj obj;
  uint8_t length;
  Value *values;
} ObjTuple;

// const ObjDef tuple_def;
extern const ObjDef tuple_def;

ObjTuple *as_tuple(Value val);
ObjTuple *copyTuple(Value *values, uint8_t length);
ObjTuple *takeTuple(Value *values, uint8_t length);
ObjTuple *zipTuples(ObjTuple *a, ObjTuple *b, Value (*fn)(Value, Value));

// Tuple: (1, 2)
// Table: {x: 2}
// List: [1, 2]
// Set: {1, 2}
// Map: {1: 2}
// Range: 1..2
// String: "hello"

#endif
