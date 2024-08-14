#include <assert.h>

#include "lib.h"
#include "memory.h"
#include "native.h"
#include "range.h"
#include "vm.h"

/** Safely convert val to range pointer. */
ObjRange *as_range(Value x) {
  assert(is_range(x));
  return AS_RANGE(x);
}

ObjRange *make_range(Value start, Value end) {
  ObjRange *range = ALLOCATE_OBJ(ObjRange, OBJ_CUSTOM);
  range->obj.def = &range_def;
  range->start = start;
  range->end = end;
  range->obj.hash = hash_bytes((char *)&range->start, sizeof(Value) * 2);
  return range;
}

static int range_length(Obj *obj) {
  ObjRange *range = (ObjRange *)obj;
  return as_int(subtract(range->end, range->start));
}

static void mark_range(Obj *obj) {
  ObjRange *range = (ObjRange *)obj;
  markValue(range->start);
  markValue(range->end);
}

const char *range_bytes(Obj *obj, int length) {
  if (length != sizeof(Value) * 2) return NULL;
  ObjRange *range = (ObjRange *)obj;
  return (char *)&range->start;
}

static int inspect_range(Obj *obj, FILE *io) {
  ObjRange *range = (ObjRange *)obj;
  return inspect_value(io, range->start) + fprintf(io, "..") +
         inspect_value(io, range->end);
}

COMPILED_SOURCE(range);
NATIVE_GETTER(Range, start, );
NATIVE_GETTER(Range, end, );
NATIVE_METHOD(Range, init, 2) {
  ObjRange *range = as_range(this);
  range->start = args[0];
  range->end = args[1];
  return this;
}

const ObjDef range_def = {
    .class_name = "Range",
    .size = sizeof(ObjRange),
    .interned = true,
    .bytes = range_bytes,
    .mark = mark_range,
    .inspect = inspect_range,
    .length = range_length,
};

Value range(Value start, Value end) { return obj(make_range(start, end)); }
