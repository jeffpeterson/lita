#ifndef sol_debug_h
#define sol_debug_h

#include "chunk.h"

void disassembleChunk(Chunk *chunk, const char *name);
int disassembleInstruction(Chunk *chunk, int offset);

void debugExecution();
void debugStack();
void debugTokens();

#endif
