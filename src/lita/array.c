#include <assert.h>

#include "array.h"
#include "memory.h"
#include "native.h"

ObjArray *copyArray(Value *values, u32 length) {
  ObjArray *arr = allocateArray();
  resize_array(arr, length);
  write_array(arr, 0, values, length);
  return arr;
}

void resize_array(ObjArray *arr, u32 capacity) {
  arr->values = GROW_ARRAY(Value, arr->values, arr->capacity, capacity);
  arr->capacity = capacity;
}

void grow_array(ObjArray *arr, u32 minCapacity) {
  u32 capacity = arr->capacity || 1;
  while (capacity < minCapacity) capacity *= 2;
  if (capacity > arr->capacity) resize_array(arr, capacity);
}

void write_array(ObjArray *arr, u32 index, Value *values, u32 length) {
  u32 minLength = index + length;
  if (arr->capacity <= minLength) grow_array(arr, minLength);
  memcpy(arr->values + index, values, length * sizeof(Value));
  for (int i = arr->length; i < index; i++) arr->values[i] = nil;
  if (minLength > arr->length) arr->length = minLength;
}

void append_array(ObjArray *arr, Value value) {
  write_array(arr, arr->length, &value, 1);
}

Value read_array(ObjArray *arr, u32 index) {
  if (index >= arr->length) return nil;
  return arr->values[index];
}

static void allocArray(Obj *obj) {
  ObjArray *arr = (ObjArray *)obj;
  arr->length = 0;
  arr->capacity = 0;
  arr->values = NULL;
}

static void freeArray(Obj *obj) {
  ObjArray *array = (ObjArray *)obj;
  FREE_ARRAY(Value, array->values, array->capacity);
}

static void markArray(Obj *obj) {
  ObjArray *arr = (ObjArray *)obj;
  for (int i = 0; i < arr->length; i++) markValue(arr->values[i]);
}

static int arrayLength(Obj *obj) { return ((ObjArray *)obj)->length; }

static int inspectArray(Obj *obj, FILE *io) {
  ObjArray *arr = (ObjArray *)obj;
  int tot = fprintf(io, "[");
  for (int i = 0; i < arr->length; i++) {
    if (i > 0) tot += fprintf(io, ", ");
    tot += inspectValue(io, arr->values[i]);
  }
  return fprintf(io, "]") + tot;
}

// NATIVE_METHOD(Array, init, 0) {
//   ObjArray *arr = asArray(this);
//   for (int i = 0; i < argc; i++) append_array(arr, args[i]);
//   return this;
// }
NATIVE_METHOD(Array, get, 1) {
  ObjArray *arr = asArray(this);
  u32 idx = as_num(args[0]);
  if (idx >= arr->length) return nil;

  return arr->values[idx];
}
NATIVE_GETTER(Array, length, NUMBER_VAL);
NATIVE_METHOD_NAMED(Array, plus, "+", 1) {
  ObjArray *a = asArray(this);
  ObjArray *b = asArray(args[0]);
  ObjArray *out = allocateArray();
  resize_array(out, a->length + b->length);
  write_array(out, 0, a->values, a->length);
  write_array(out, a->length, b->values, b->length);
  return OBJ_VAL(out);
}
NATIVE_METHOD(Array, push, 0) {
  ObjArray *arr = asArray(this);
  for (int i = 0; i < argc; i++) append_array(arr, args[i]);
  return this;
}
NATIVE_METHOD(Array, slice, 0) {
  ObjArray *arr = asArray(this);
  int start = argc > 0 ? as_num(args[0]) : 0;
  int len = argc > 1 ? as_num(args[1]) : arr->length - start;
  return OBJ_VAL(copyArray(arr->values + start, len));
}

COMPILED_SOURCE(array);
REGISTER_OBJECT_DEF(Array);
const ObjDef Array = {
    .className = "Array",
    .size = sizeof(ObjArray),
    .interned = false,
    .alloc = allocArray,
    .free = freeArray,
    .mark = markArray,
    .inspect = inspectArray,
    // .dump = dump_array,
    .length = arrayLength,
};
