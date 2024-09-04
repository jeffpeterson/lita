#include <assert.h>

#include "lib.h"
#include "memory.h"
#include "native.h"
#include "range.h"
#include "vm.h"

Value range(Value start, Value end) { return obj(newRange(start, end)); }

ObjRange *newRange(Value start, Value end) {
  ObjRange *range = allocateRange();
  range->start = start;
  range->end = end;
  range->obj.hash = hash_bytes((char *)&range->start, sizeof(Value) * 2);
  return range;
}

static int rangeLength(Obj *obj) {
  ObjRange *range = (ObjRange *)obj;
  return as_int(subtract(range->end, range->start));
}

static void markRange(Obj *obj) {
  ObjRange *range = (ObjRange *)obj;
  markValue(range->start);
  markValue(range->end);
}

const char *rangeBytes(Obj *obj, int length) {
  ObjRange *range = (ObjRange *)obj;
  if (length != sizeof(Value) * 2) return NULL;
  return (char *)&range->start;
}

static int inspectRange(Obj *obj, FILE *io) {
  ObjRange *range = (ObjRange *)obj;
  return inspect_value(io, range->start) + fprintf(io, "..") +
         inspect_value(io, range->end);
}

COMPILED_SOURCE(range);
NATIVE_GETTER(Range, start, );
NATIVE_GETTER(Range, end, );
NATIVE_METHOD(Range, init, 2) {
  ObjRange *range = asRange(this);
  range->start = args[0];
  range->end = args[1];
  return this;
}

REGISTER_OBJECT_DEF(Range);
const ObjDef Range = {
    .class_name = "Range",
    .size = sizeof(ObjRange),
    .interned = true,
    .bytes = rangeBytes,
    .mark = markRange,
    .inspect = inspectRange,
    .length = rangeLength,
};
