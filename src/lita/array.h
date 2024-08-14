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

#define AS_ARRAY(val) ((ObjArray *)AS_OBJ(val))
#define is_array(val) is_obj_def(val, &Array)
#define new_array() ((ObjArray *)new_object(&Array))

ObjArray *as_array(let x);
ObjArray *copy_array(Value *values, u32 length);
void resize_array(ObjArray *arr, u32 capacity);
void grow_array(ObjArray *arr, u32 minCapacity);
void write_array(ObjArray *arr, u32 index, Value *values, u32 length);
void append_array(ObjArray *arr, Value value);
Value read_array(ObjArray *arr, u32 index);

const ObjDef Array;

#endif
