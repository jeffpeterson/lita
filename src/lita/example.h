#ifndef lita_example_h
#define lita_example_h

#include "object.h"
#include "string.h"
#include "value.h"

#define isExample(val) isObjDef(val, &Example)
#define asExample(val) as(Example, val)

typedef struct ObjExample {
  Obj obj;
  ObjString *comment;
} ObjExample;

ObjExample *newExample(ObjString *comment);
Value example(const char *comment);

extern const ObjDef Example;

#endif
