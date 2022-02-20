#ifndef sol_chunk_h
#define sol_chunk_h

#include "common.h"
#include "value.h"

typedef enum OpCode {
  OP_CONSTANT,

  OP_NIL,
  OP_TRUE,
  OP_FALSE,

  OP_RANGE,
  OP_TUPLE,

  OP_PEEK,
  OP_POP,
  OP_POPN,
  OP_SWAP,
  OP_DEFAULT,

  OP_DEFINE_GLOBAL,
  OP_GET_GLOBAL,
  OP_SET_GLOBAL,

  OP_GET_LOCAL,
  OP_SET_LOCAL,

  OP_GET_PROPERTY,
  OP_SET_PROPERTY,

  OP_GET_UPVALUE,
  OP_SET_UPVALUE,

  OP_GET_SUPER,

  OP_EQUAL,
  OP_GREATER,
  OP_LESS,

  OP_ADD,
  OP_SUBTRACT,
  OP_MULTIPLY,
  OP_DIVIDE,

  OP_NOT,
  OP_NEGATE,

  OP_JUMP,
  OP_JUMP_IF_FALSE,
  OP_LOOP,

  OP_CALL,
  OP_CLASS,
  OP_INHERIT,
  OP_METHOD,
  OP_CLOSURE,
  OP_CLOSE_UPVALUE,
  OP_PRINT,
  OP_RETURN,

  OP_INVOKE,
  OP_SUPER_INVOKE,
} OpCode;

typedef struct {
  int count;
  int capacity;
  u8 *code;
  int *lines;
  ValueArray constants;
} Chunk;

void initChunk(Chunk *chunk);
void freeChunk(Chunk *chunk);
void growChunk(Chunk *chunk, int capacity);
void writeChunk(Chunk *chunk, u8 byte, int line);
void dumpChunk(FILE *io, const char *name, Chunk *chunk);
int addConstant(Chunk *chunk, Value value);

#endif
