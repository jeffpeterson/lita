#ifndef sol_dump_h
#define sol_dump_h

#include <stdio.h>

#include "chunk.h"
#include "common.h"
#include "value.h"

void dumpChunk(FILE *io, const char *name, Chunk *chunk);

#endif
