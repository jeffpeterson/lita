#ifndef lita_debug_h
#define lita_debug_h

#include "chunk.h"
#include "table.h"

void disassembleChunk(Chunk *chunk, const char *name, int until);
int disassembleInstruction(Chunk *chunk, int offset);

void debugFrames();
void debugExecution();
void debugStack();
void debugTokens();
int debugValue(Value value);
int debugObject(Obj *obj);
int debugTable(Table *table);

int debugValueTable();

#endif
