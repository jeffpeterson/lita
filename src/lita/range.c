#include "range.h"
#include "memory.h"
#include "native.h"

Value range(Value start, Value end) { return obj(newRange(start, end)); }

ObjRange *newRange(Value start, Value end) {
  ObjRange *range = allocateRange();
  range->start = start;
  range->end = end;
  internObject((Obj **)&range);
  return range;
}

static int rangeLength(Obj *obj) {
  ObjRange *range = (ObjRange *)obj;
  return asInt(range->end) - asInt(range->start);
}

static void markRange(Obj *obj) {
  ObjRange *range = (ObjRange *)obj;
  markValue(range->start);
  markValue(range->end);
}

static int inspectRange(Obj *obj, FILE *io) {
  ObjRange *range = (ObjRange *)obj;
  return inspectValue(io, range->start) + fprintf(io, "..") +
         inspectValue(io, range->end);
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
    .className = "Range",
    .size = sizeof(ObjRange),
    .hash = hashObjectDefault,
    .mark = markRange,
    .inspect = inspectRange,
    .length = rangeLength,
};
