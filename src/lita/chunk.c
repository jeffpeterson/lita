#include <stdlib.h>

#include "buffer.h"
#include "chunk.h"
#include "memory.h"
#include "vm.h"

// 50 7B 53 4f 4c 0a ; P{SOL\n -> SOL B(inary)
// 71 1A 4c 49 54 41 0a ; q.LITA\n -> LITA
void initChunk(Chunk *chunk) {
  chunk->count = 0;
  chunk->capacity = 0;
  chunk->code = NULL;
  chunk->lines = NULL;
  chunk->comments = NULL;

  initValueArray(&chunk->constants);
}

void growChunk(Chunk *chunk, int capacity) {
  if (chunk->capacity < capacity) {
    chunk->code = GROW_ARRAY(u8, chunk->code, chunk->capacity, capacity);
    chunk->lines = GROW_ARRAY(int, chunk->lines, chunk->capacity, capacity);
    chunk->comments =
        GROW_ARRAY(Value, chunk->comments, chunk->capacity, capacity);
    chunk->capacity = capacity;
  }
}

void markChunk(Chunk *chunk) {
  markArray(&chunk->constants);
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
  if (chunk->capacity < chunk->count + 1)
    growChunk(chunk, GROW_CAPACITY(chunk->capacity));

  chunk->code[chunk->count] = byte;
  chunk->lines[chunk->count] = line;
  if (chunk->comments) chunk->comments[chunk->count] = comment;
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

Value get_constant(Chunk *chunk, int id) { return chunk->constants.values[id]; }

OpInfo op_info[] = {
    [OP_NIL] = {"OP_NIL", SIMPLE, 0, 1},
    [OP_TRUE] = {"OP_TRUE", SIMPLE, 0, 1},
    [OP_FALSE] = {"OP_FALSE", SIMPLE, 0, 1},

    [OP_ASSERT] = {"OP_ASSERT", CONSTANT, 1, 1},
    [OP_NOT] = {"OP_NOT", SIMPLE, 1, 1},
    [OP_NEGATE] = {"OP_NEGATE", SIMPLE, 1, 1},
    [OP_PRINT] = {"OP_PRINT", SIMPLE, 1, 1},
    [OP_RETURN] = {"OP_RETURN", SIMPLE, 1, 1},

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

int input_count(Chunk *chunk, u8 *ip) {
  OpInfo op = op_info[*ip];
  switch (*ip) {
  case OP_CALL: return ip[1] + 1;
  case OP_SUPER_INVOKE:
  case OP_INVOKE: return ip[2] + 1;
  case OP_POPN:
  case OP_TUPLE: return ip[1];
  case OP_ARRAY: return as_num(get_constant(chunk, ip[1]));
  default: return op.inputs;
  }
}

int output_count(Chunk *chunk, u8 *ip) {
  OpInfo op = op_info[*ip];
  return op.outputs;
}

int input_output_delta(Chunk *chunk, u8 *ip) {
  return output_count(chunk, ip) - input_count(chunk, ip);
}
