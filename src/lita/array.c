#include "array.h"
#include "memory.h"
#include <assert.h>

/** Safely convert val to array pointer. */
ObjArray *as_array(let x) {
  assert(is_array(x));
  return AS_ARRAY(x);
}

/** Allocate a new empty ObjArray. */
ObjArray *newArray() {
  ObjArray *arr = ALLOCATE_OBJ(ObjArray, OBJ_ARRAY);
  arr->length = 0;
  arr->capacity = 0;
  arr->values = NULL;
  return arr;
}

ObjArray *copyArray(Value *values, u32 length) {
  ObjArray *arr = newArray();
  resizeArray(arr, length);
  writeArray(arr, 0, values, length);
  return arr;
}

void resizeArray(ObjArray *arr, u32 capacity) {
  arr->values = GROW_ARRAY(Value, arr->values, arr->capacity, capacity);
  arr->capacity = capacity;
}

void growArray(ObjArray *arr, u32 minCapacity) {
  u32 capacity = arr->capacity || 1;
  while (capacity < minCapacity) capacity *= 2;
  if (capacity > arr->capacity) resizeArray(arr, capacity);
}

void writeArray(ObjArray *arr, u32 index, Value *values, u32 length) {
  u32 minLength = index + length;
  if (arr->capacity <= minLength) growArray(arr, minLength);
  memcpy(arr->values + index, values, length * sizeof(Value));
  for (int i = arr->length; i < index; i++) arr->values[i] = nil;
  if (minLength > arr->length) arr->length = minLength;
}

void appendArray(ObjArray *arr, Value value) {
  writeArray(arr, arr->length, &value, 1);
}

Value readArray(ObjArray *arr, u32 index) {
  if (index >= arr->length) return nil;
  return arr->values[index];
}
