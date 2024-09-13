#ifndef lita_example_h
#define lita_example_h

#include "common.h"
#include "object.h"
#include "value.h"

#define allocateExample() ALLOCATE_OBJ(Example)
#define isExample(val) isObjDef(val, &Example)
#define asExample(val) as(Example, val)

typedef struct ObjExample {
  Obj obj;
  ObjString *comment;
} ObjExample;

ObjDef Example;

ObjExample *newExample(ObjString *comment);
Value example(const char *comment);

#endif
