#ifndef lita_dump_h
#define lita_dump_h

#include <stdio.h>

#include "chunk.h"
#include "common.h"
#include "object.h"
#include "value.h"

void dumpModule(FILE *io, ObjString *name, ObjFun *fun);

#endif
