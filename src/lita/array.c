#include "array.h"
#include "lib.h"
#include "memory.h"
#include "vm.h"
#include <assert.h>

/** Safely convert val to array pointer. */
ObjArray *as_array(let x) {
  assert(is_array(x));
  return AS_ARRAY(x);
}

/** Allocate a new empty ObjArray. */
ObjArray *new_array() {
  ObjArray *arr = ALLOCATE_OBJ(ObjArray, OBJ_CUSTOM);
  arr->obj.def = &array_def;
  arr->length = 0;
  arr->capacity = 0;
  arr->values = NULL;
  return arr;
}

ObjArray *copy_array(Value *values, u32 length) {
  ObjArray *arr = new_array();
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

static void free_array(Obj *obj) {
  ObjArray *array = (ObjArray *)obj;
  FREE_ARRAY(Value, array->values, array->capacity);
}

static void mark_array(Obj *obj) {
  ObjArray *arr = (ObjArray *)obj;
  for (int i = 0; i < arr->length; i++) markValue(arr->values[i]);
}

static int array_length(Obj *obj) { return ((ObjArray *)obj)->length; }

static int inspect_array(Obj *obj, FILE *io) {
  ObjArray *arr = (ObjArray *)obj;
  int tot = fprintf(io, "[");
  for (int i = 0; i < arr->length; i++) {
    if (i > 0) tot += fprintf(io, ", ");
    tot += inspect_value(io, arr->values[i]);
  }
  return fprintf(io, "]") + tot;
}

// static Value Array_init(let this, int argc, let *args) {
//   ObjArray *arr = AS_ARRAY(this);
//   for (int i = 0; i < argc; i++) append_array(arr, args[i]);
//   return this;
// }

static Value Array_get(let this, int argc, let *args) {
  ObjArray *arr = AS_ARRAY(this);
  u32 idx = as_num(args[0]);
  if (idx >= arr->length) return nil;

  return arr->values[idx];
}

static Value Array_length(let this, int argc, let *args) {
  return NUMBER_VAL(AS_ARRAY(this)->length);
}

static Value Array_plus(let this, int argc, let *args) {
  ObjArray *a = AS_ARRAY(this);
  ObjArray *b = as_array(args[0]);
  ObjArray *out = new_array();
  resize_array(out, a->length + b->length);
  write_array(out, 0, a->values, a->length);
  write_array(out, a->length, b->values, b->length);
  return OBJ_VAL(out);
}

static Value Array_push(let this, int argc, let *args) {
  ObjArray *arr = AS_ARRAY(this);
  for (int i = 0; i < argc; i++) append_array(arr, args[i]);
  return this;
}

static Value Array_slice(let this, int argc, let *args) {
  ObjArray *arr = AS_ARRAY(this);
  int start = argc > 0 ? as_num(args[0]) : 0;
  int len = argc > 1 ? as_num(args[1]) : arr->length - start;
  return OBJ_VAL(copy_array(arr->values + start, len));
}

ObjFun *array_lita();

static void array_natives(let Array) {
  runFun(array_lita());
  // method(Array, fn("init", 0, Array_init));
  method(Array, fn("get", 1, Array_get));
  method(Array, fn("length", 0, Array_length));
  method(Array, fn("push", 0, Array_push));
  method(Array, fn("slice", 0, Array_slice));
  method(Array, fn("+", 1, Array_plus));
}

const ObjDef array_def = {
    .class_name = "Array",
    .size = sizeof(ObjArray),
    .interned = false,
    .free = free_array,
    .mark = mark_array,
    .inspect = inspect_array,
    // .dump = dump_array,
    .length = array_length,
    .natives = array_natives,
};
