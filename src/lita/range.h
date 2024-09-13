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

#define allocateRange() ALLOCATE_OBJ(Range)
#define isRange(val) isObjDef(val, &Range)
#define asRange(val) as(Range, val)

ObjRange *newRange(Value start, Value end);
Value range(Value start, Value end);

extern const ObjDef Range;

#endif
