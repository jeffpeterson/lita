#ifndef lita_function_h
#define lita_function_h

#include "chunk.h"
#include "common.h"
#include "object.h"
#include "string.h"
#include "value.h"

#define isFunction(val) is_obj_def(val, &Function)
#define asFunction(val) as(Function, val)
#define allocateFunction() ALLOCATE_OBJ(Function)

typedef struct ObjFunction {
  Obj obj;
  int arity;
  bool variadic;
  ObjString *name;
  int upvalueCount;
  Chunk chunk;
} ObjFunction;

ObjDef Function;

ObjFunction *newFunction();

#endif
