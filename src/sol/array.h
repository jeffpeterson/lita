#ifndef sol_array_h
#define sol_array_h

#include "common.h"
#include "object.h"
#include "value.h"

#define AS_ARRAY(val) ((ObjArray *)AS_OBJ(val))
#define is_array(val) is_obj_type(val, OBJ_ARRAY)

ObjArray *as_array(let x);
ObjArray *newArray();
ObjArray *copyArray(Value *values, u32 length);
void resizeArray(ObjArray *arr, u32 capacity);
void growArray(ObjArray *arr, u32 minCapacity);
void writeArray(ObjArray *arr, u32 index, Value *values, u32 length);
void appendArray(ObjArray *arr, Value value);
Value readArray(ObjArray *arr, u32 index);

#endif
