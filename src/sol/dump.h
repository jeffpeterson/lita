#ifndef sol_dump_h
#define sol_dump_h

#include <stdio.h>

#include "chunk.h"
#include "common.h"
#include "object.h"
#include "value.h"

void dumpChunk(FILE *io, ObjString *name, Chunk *chunk);
void dumpModule(FILE *io, ObjString *name, ObjFun *fun);

#endif
