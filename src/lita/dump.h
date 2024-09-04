#ifndef lita_dump_h
#define lita_dump_h

#include <stdio.h>

#include "chunk.h"
#include "common.h"
#include "function.h"
#include "object.h"
#include "value.h"

Table ids;

void dumpModule(FILE *io, ObjString *name, ObjFunction *fun);
int dumpValue(FILE *io, Value v);
int dumpObject(FILE *io, Obj *obj);
bool id_for(let v, int *id);

#endif
