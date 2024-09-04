#ifndef lita_class_h
#define lita_class_h

#include "common.h"
#include "object.h"
#include "value.h"

#define isClass(val) is_obj_def(val, &Class)
#define asClass(val) as(Class, val)
#define allocateClass() ALLOCATE_OBJ(Class)

typedef struct ObjClass {
  Obj obj;
  ObjString *name;
  struct ObjClass *parent;
  ObjDef *instance_def;
  Table methods;
} ObjClass;

ObjDef Class;

ObjClass *newClass(ObjString *name);
Value class(const char *name);

#endif
