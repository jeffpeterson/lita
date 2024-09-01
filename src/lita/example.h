#ifndef lita_example_h
#define lita_example_h

#include "common.h"
#include "object.h"
#include "value.h"

#define AS_EXAMPLE(val) ((ObjExample *)AS_OBJ(val))
#define isExample(val) is_obj_def(val, &Example)
#define allocateExample() ((ObjExample *)new_object(&Example))

typedef struct ObjExample {
  Obj obj;
  ObjString *comment;
} ObjExample;

ObjDef Example;

ObjExample *asExample(let val);
ObjExample *newExample(ObjString *comment);
let example(const char *comment);

#endif
