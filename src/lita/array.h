#ifndef lita_array_h
#define lita_array_h

#include "common.h"
#include "object.h"
#include "value.h"

typedef struct ObjArray {
  Obj obj;
  int capacity;
  int length;
  Value *values;
} ObjArray;

#define isArray(val) isObjDef(val, &Array)
#define asArray(val) as(Array, val)
#define allocateArray() ALLOCATE_OBJ(Array)

ObjArray *copyArray(Value *values, u32 length);
void resizeArray(ObjArray *arr, u32 capacity);
void growArray(ObjArray *arr, u32 minCapacity);
void writeArray(ObjArray *arr, u32 index, Value *values, u32 length);
void appendArray(ObjArray *arr, Value value);
Value readArray(ObjArray *arr, u32 index);

extern const ObjDef Array;

#endif
