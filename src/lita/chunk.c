#include <stdlib.h>

#include "buffer.h"
#include "chunk.h"
#include "memory.h"
#include "vm.h"

// 50 7B 53 4f 4c 0a ; P{SOL\n -> SOL B(inary)

void initChunk(Chunk *chunk) {
  chunk->count = 0;
  chunk->capacity = 0;
  chunk->code = NULL;
  chunk->lines = NULL;

  initValueArray(&chunk->constants);
}

void growChunk(Chunk *chunk, int capacity) {
  if (chunk->capacity < capacity) {
    chunk->code = GROW_ARRAY(u8, chunk->code, chunk->capacity, capacity);
    chunk->lines = GROW_ARRAY(int, chunk->lines, chunk->capacity, capacity);
    chunk->capacity = capacity;
  }
}

void freeChunk(Chunk *chunk) {
  FREE_ARRAY(u8, chunk->code, chunk->capacity);
  FREE_ARRAY(int, chunk->lines, chunk->capacity);
  freeValueArray(&chunk->constants);
  initChunk(chunk);
}

void writeChunk(Chunk *chunk, u8 byte, int line) {
  if (chunk->capacity < chunk->count + 1)
    growChunk(chunk, GROW_CAPACITY(chunk->capacity));

  chunk->code[chunk->count] = byte;
  chunk->lines[chunk->count] = line;
  chunk->count++;
}

int addConstant(Chunk *chunk, Value value) {
  for (int i = 0; i < chunk->constants.count; i++) {
    if (valuesEqual(value, chunk->constants.values[i])) return i;
  }

  push(value);
  writeValueArray(&chunk->constants, value);
  pop();
  return chunk->constants.count - 1;
}
