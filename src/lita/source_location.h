#ifndef lita_sourceLocation_h
#define lita_sourceLocation_h

#include "object.h"
#include "string.h"
#include "value.h"

#define allocateSourceLocation() ALLOCATE_OBJ(SourceLocation)
#define isSourceLocation(val) isObjDef(val, &SourceLocation)
#define asSourceLocation(val) as(SourceLocation, val)

typedef struct ObjSourceLocation {
  Obj obj;
  ObjString *path;
  int line;
  int column;
} ObjSourceLocation;

extern const ObjDef SourceLocation;

ObjSourceLocation *newSourceLocation(ObjString *path, int line, int column);
Value sourceLocation(const char *path, int line, int column);

#endif
