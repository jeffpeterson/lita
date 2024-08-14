#ifndef lita_range_h
#define lita_range_h

#include "common.h"
#include "object.h"
#include "value.h"

typedef struct ObjRange {
  Obj obj;
  Value start;
  Value end;
} ObjRange;

#define AS_RANGE(val) ((ObjRange *)AS_OBJ(val))
#define is_range(val) is_obj_def(val, &Range)

ObjRange *make_range(Value start, Value end);
Value range(Value start, Value end);

extern const ObjDef Range;

#endif
