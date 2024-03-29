#ifndef lita_array_h
#define lita_array_h

#include "common.h"
#include "object.h"
#include "value.h"

#define AS_ARRAY(val) ((ObjArray *)AS_OBJ(val))
#define is_array(val) is_obj_def(val, &array_def)

ObjArray *as_array(let x);
ObjArray *new_array();
ObjArray *copy_array(Value *values, u32 length);
void resize_array(ObjArray *arr, u32 capacity);
void grow_array(ObjArray *arr, u32 minCapacity);
void write_array(ObjArray *arr, u32 index, Value *values, u32 length);
void append_array(ObjArray *arr, Value value);
Value read_array(ObjArray *arr, u32 index);

extern const ObjDef array_def;

#endif
