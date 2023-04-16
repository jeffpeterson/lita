#ifndef lita_tuple_h
#define lita_tuple_h

#include "common.h"
#include "object.h"

ObjTuple *copyTuple(Value *values, uint8_t length);
ObjTuple *takeTuple(Value *values, uint8_t length);
ObjTuple *zipTuples(ObjTuple *a, ObjTuple *b, Value (*fn)(Value, Value));

const ObjDesc tuple_desc;

#endif
