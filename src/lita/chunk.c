#include <stdlib.h>

#include "buffer.h"
#include "chunk.h"
#include "memory.h"
#include "vm.h"

// 50 7B 53 4f 4c 0a ; P{SOL\n -> SOL B(inary)
// 71 1A 4c 49 54 41 0a ; q.LITA\n -> LITA
void initChunk(Chunk *chunk) {
  chunk->version = 0;
  chunk->count = 0;
  chunk->capacity = 0;
  chunk->code = NULL;
  chunk->lines = NULL;
  chunk->comments = NULL;

  initValueArray(&chunk->constants);
}

void resizeChunk(Chunk *chunk, int capacity) {
  if (chunk->capacity < capacity) {
    chunk->code = GROW_ARRAY(u8, chunk->code, chunk->capacity, capacity);
    chunk->lines = GROW_ARRAY(int, chunk->lines, chunk->capacity, capacity);
    chunk->comments =
        GROW_ARRAY(Value, chunk->comments, chunk->capacity, capacity);
    chunk->capacity = capacity;
  }
}

void growChunk(Chunk *chunk, int minCapacity) {
  if (chunk->capacity >= minCapacity) return;
  u32 capacity = chunk->capacity;
  if (capacity < 8) capacity = 8;
  while (capacity < minCapacity) capacity *= 2;
  resizeChunk(chunk, capacity);
}

void markChunk(Chunk *chunk) {
  markValueArray(&chunk->constants);
  if (chunk->comments)
    for (int i = 0; i < chunk->capacity; i++) markValue(chunk->comments[i]);
}

void freeChunk(Chunk *chunk) {
  FREE_ARRAY(u8, chunk->code, chunk->capacity);
  FREE_ARRAY(int, chunk->lines, chunk->capacity);
  if (chunk->comments) FREE_ARRAY(Value, chunk->comments, chunk->capacity);
  freeValueArray(&chunk->constants);
  initChunk(chunk);
}

void writeChunk(Chunk *chunk, u8 byte, int line, Value comment) {
  growChunk(chunk, chunk->count + 1);

  chunk->code[chunk->count] = byte;
  chunk->lines[chunk->count] = line;
  if (chunk->comments) chunk->comments[chunk->count] = comment;
  chunk->count++;
}

int writeChunkLong(Chunk *chunk, u32 c, int line, Value comment) {
  u8 bytes[5];
  int count = encodeLong(c, bytes);
  for (int i = 0; i < count; i++) writeChunk(chunk, bytes[i], line, comment);
  return count;
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

Value getConstant(Chunk *chunk, u32 id) { return chunk->constants.values[id]; }

Value readConstant(Chunk *chunk, u8 **ip) {
  if (chunk->version < 1) return getConstant(chunk, *(*ip)++);
  u32 id;
  (*ip) += decodeLong(&id, *ip);
  return getConstant(chunk, id);
}

OpInfo opInfo[] = {
    [OP_NIL] = {"OP_NIL", SIMPLE, 0, 1},
    [OP_TRUE] = {"OP_TRUE", SIMPLE, 0, 1},
    [OP_FALSE] = {"OP_FALSE", SIMPLE, 0, 1},

    [OP_ASSERT] = {"OP_ASSERT", CONSTANT, 1, 1},
    [OP_NOT] = {"OP_NOT", SIMPLE, 1, 1},
    [OP_NEGATE] = {"OP_NEGATE", SIMPLE, 1, 1},
    [OP_PRINT] = {"OP_PRINT", SIMPLE, 1, 1},
    [OP_RETURN] = {"OP_RETURN", SIMPLE, 1, 1},
    [OP_THROW] = {"OP_THROW", CONSTANT, 1, 0},

    [OP_ADD] = {"OP_ADD", SIMPLE, 2, 1},
    [OP_SUBTRACT] = {"OP_SUBTRACT", SIMPLE, 2, 1},
    [OP_MULTIPLY] = {"OP_MULTIPLY", SIMPLE, 2, 1},
    [OP_DIVIDE] = {"OP_DIVIDE", SIMPLE, 2, 1},

    [OP_EQUAL] = {"OP_EQUAL", SIMPLE, 2, 1},
    [OP_GREATER] = {"OP_GREATER", SIMPLE, 2, 1},
    [OP_LESS] = {"OP_LESS", SIMPLE, 2, 1},

    [OP_RANGE] = {"OP_RANGE", SIMPLE, 2, 1},
    [OP_INHERIT] = {"OP_INHERIT", SIMPLE, 2, 2},

    [OP_POP] = {"OP_POP", SIMPLE, 1, 0},
    [OP_POPN] = {"OP_POPN", BYTE, -1, 0},
    [OP_CLOSE_UPVALUE] = {"OP_CLOSE_UPVALUE", SIMPLE, 1, 0},

    [OP_SWAP] = {"OP_SWAP", BYTE, 0, 0},
    [OP_TUPLE] = {"OP_TUPLE", BYTE, -1, 1},
    [OP_PEEK] = {"OP_PEEK", BYTE, 0, 1},
    [OP_CALL] = {"OP_CALL", BYTE, -1, 1},

    [OP_GET_LOCAL] = {"OP_GET_LOCAL", BYTE, 0, 1},
    [OP_SET_LOCAL] = {"OP_SET_LOCAL", BYTE, 1, 1},

    [OP_DEFINE_GLOBAL] = {"OP_DEFINE_GLOBAL", CONSTANT, 1, 0},
    [OP_GET_GLOBAL] = {"OP_GET_GLOBAL", CONSTANT, 0, 1},
    [OP_SET_GLOBAL] = {"OP_SET_GLOBAL", CONSTANT, 1, 1},

    [OP_GET_PROPERTY] = {"OP_GET_PROPERTY", CONSTANT, 1, 1},
    [OP_SET_PROPERTY] = {"OP_SET_PROPERTY", CONSTANT, 2, 1},

    [OP_GET_VAR] = {"OP_GET_VAR", CONSTANT, 1, 1},
    [OP_SET_VAR] = {"OP_SET_VAR", CONSTANT, 2, 1},

    [OP_GET_UPVALUE] = {"OP_GET_UPVALUE", BYTE, 0, 1},
    [OP_SET_UPVALUE] = {"OP_SET_UPVALUE", BYTE, 1, 1},

    [OP_GET_SUPER] = {"OP_GET_SUPER", CONSTANT, 1, 1},
    [OP_CLASS] = {"OP_CLASS", CONSTANT_BYTE, 0, 1},
    [OP_CONSTANT] = {"OP_CONSTANT", CONSTANT, 0, 1},
    [OP_DEFAULT] = {"OP_DEFAULT", CONSTANT, 1, 1},
    [OP_METHOD] = {"OP_METHOD", CONSTANT, 2, 1},

    [OP_JUMP] = {"OP_JUMP", JUMP, 0, 0},
    [OP_JUMP_IF_FALSE] = {"OP_JUMP_IF_FALSE", JUMP, 1, 1},
    [OP_LOOP] = {"OP_LOOP", JUMP, 0, 0},

    [OP_CLOSURE] = {"OP_CLOSURE", CONSTANT, 0, 1},

    [OP_INVOKE] = {"OP_INVOKE", INVOKE, -1, 1},
    [OP_SUPER_INVOKE] = {"OP_SUPER_INVOKE", INVOKE, -1, 1},

    [OP_ARRAY] = {"OP_ARRAY", CONSTANT, -1, 1},
    [OP_DEBUG_STACK] = {"OP_DEBUG_STACK", CONSTANT, 0, 0},
    [OP_ASSERT_STACK] = {"OP_ASSERT_STACK", CONSTANT_BYTE, 0, 0},
};

u8 instructionSize(Chunk *chunk, u8 *ip) {
  switch (opInfo[*ip].type) {
  case SIMPLE: return 1;
  case BYTE: return 2;
  case CONSTANT:
    if (chunk->version < 1) return 2;
    return 1 + decodeLong(NULL, ip);
  case CONSTANT_BYTE:
    if (chunk->version < 1) return 3;
    return 2 + decodeLong(NULL, ip);
  case JUMP:
  case INVOKE: return 3;
  }
}

int inputCount(Chunk *chunk, u8 *ip) {
  OpInfo op = opInfo[*ip];
  switch (*ip) {
  case OP_CALL: return ip[1] + 1;
  case OP_SUPER_INVOKE:
  case OP_INVOKE: return ip[2] + 1;
  case OP_POPN:
  case OP_TUPLE: return ip[1];
  case OP_ARRAY: return as_num(getConstant(chunk, ip[1]));
  default: return op.inputs;
  }
}

int outputCount(Chunk *chunk, u8 *ip) {
  OpInfo op = opInfo[*ip];
  return op.outputs;
}

int inputOutputDelta(Chunk *chunk, u8 *ip) {
  return outputCount(chunk, ip) - inputCount(chunk, ip);
}

/**
 * The long is encoded in 7-bit chunks, with the most significant bit of each
 * byte set to indicate that there are more bytes to follow. The bytes are
 * written to the code array in reverse order with the least significant byte
 * first.
 */
int decodeLong(u32 *cp, u8 *bytes) {
  int i = 0, c = 0;
  do {
    c |= (bytes[i] & 0x7F) << (7 * i);
  } while (bytes[i++] & 0x80);
  if (cp) *cp = c;
  return i;
}

/**
 * The long is encoded in 7-bit chunks, with the most significant bit of each
 * byte set to indicate that there are more bytes to follow. The bytes are
 * written to the code array in reverse order with the least significant byte
 * first.
 */
int encodeLong(u32 c, u8 *bytes) {
  int i = 0;
  do {
    bytes[i] = c & 0x7F;
    c >>= 7;
    if (c > 0) bytes[i] |= 0x80;
    i++;
  } while (c > 0);
  return i;
}
