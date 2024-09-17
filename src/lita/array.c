#include "array.h"
#include "memory.h"
#include "native.h"

ObjArray *copyArray(Value *values, u32 length) {
  ObjArray *arr = allocateArray();
  resizeArray(arr, length);
  writeArray(arr, 0, values, length);
  return arr;
}

void resizeArray(ObjArray *arr, u32 capacity) {
  arr->values = GROW_ARRAY(Value, arr->values, arr->capacity, capacity);
  arr->capacity = capacity;
}

void growArray(ObjArray *arr, u32 minCapacity) {
  if (arr->capacity >= minCapacity) return;
  u32 capacity = arr->capacity;
  if (capacity < 8) capacity = 8;
  while (capacity < minCapacity) capacity *= 2;
  resizeArray(arr, capacity);
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
  resizeArray(out, a->length + b->length);
  writeArray(out, 0, a->values, a->length);
  writeArray(out, a->length, b->values, b->length);
  return OBJ_VAL(out);
}
NATIVE_METHOD(Array, push, 0) {
  ObjArray *arr = asArray(this);
  for (int i = 0; i < argc; i++) appendArray(arr, args[i]);
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
