#ifndef lita_debug_h
#define lita_debug_h

#include "chunk.h"

void disassembleChunk(Chunk *chunk, const char *name, int until);
int disassembleInstruction(Chunk *chunk, int offset);

void debugFrames();
void debugExecution();
void debugStack();
void debugTokens();

#endif
