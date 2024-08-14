#ifndef lita_example_h
#define lita_example_h

#include "common.h"
#include "object.h"
#include "value.h"

#define AS_EXAMPLE(val) ((ObjExample *)AS_OBJ(val))
#define is_example(val) is_obj_def(val, &Example)
#define allocate_example() ((ObjExample *)new_object(&Example))

typedef struct ObjExample {
  Obj obj;
  ObjString *comment;
} ObjExample;

ObjDef Example;

ObjExample *new_example(ObjString *comment);
Value example(const char *comment);

#endif
