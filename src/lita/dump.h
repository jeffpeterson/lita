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
void dumpValue(FILE *io, Value v);
bool id_for(let v, int *id);

#endif
