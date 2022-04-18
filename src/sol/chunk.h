#ifndef sol_chunk_h
#define sol_chunk_h

#include "common.h"
#include "value.h"

typedef enum OpCode {
  OP_CONSTANT,      /** (x) [] -> [0 x] */
                    /**/
  OP_NIL,           /** [] -> [0 nil] */
  OP_TRUE,          /** [] -> [0 true] */
  OP_FALSE,         /** [] -> [0 false] */
                    /**/
  OP_RANGE,         /** [1 start][0 end] -> [0 Range] */
  OP_TUPLE,         /** (n) [n ...args][0 arg] -> [0 tuple] */
                    /**/
  OP_PEEK,          /** (n) [...] -> [...][0 peek(n)] */
  OP_POP,           /** [0 x] -> [] */
  OP_POPN,          /** [n x][...] -> [] */
  OP_SWAP,          /** (ab) [a x][b y] -> [a y][b x] */
  OP_DEFAULT,       /** (x) [] -> [0 x] */
                    /**/
  OP_DEFINE_GLOBAL, /** (name) [0 value] -> [] */
  OP_GET_GLOBAL,    /** (name) [] -> [0 value] */
  OP_SET_GLOBAL,    /** (name) [0 value] -> [0 value] */
                    /**/
  OP_GET_LOCAL,     /** (slot) [] -> [0 value] */
  OP_SET_LOCAL,     /** (slot) [0 value] -> [0 value] */
                    /**/
  OP_GET_PROPERTY,  /** (name) [0 self] -> [0 value] */
  OP_SET_PROPERTY,  /** (name) [1 self][0 value] -> [0 value] */
                    /**/
  OP_GET_UPVALUE,   /** (n) [] -> [0 value] */
  OP_SET_UPVALUE,   /** (n) [0 value] -> [0 value] */
                    /**/
  OP_GET_SUPER,     /** (name) [0 super] -> [0 method] */
                    /**/
  OP_EQUAL,         /** [1 a][0 b] -> [0 Bool] */
  OP_GREATER,       /** [1 a][0 b] -> [0 Bool] */
  OP_LESS,          /** [1 a][0 b] -> [0 Bool] */
                    /**/
  OP_ADD,           /** [1 a][0 b] -> [0 a+b] */
  OP_SUBTRACT,      /** [1 a][0 b] -> [0 a-b] */
  OP_MULTIPLY,      /** [1 a][0 b] -> [0 a*b] */
  OP_DIVIDE,        /** [1 a][0 b] -> [0 a/b] */
                    /**/
  OP_NOT,           /** [0 x] -> [0 !x] */
  OP_NEGATE,        /** [0 x] -> [0 -x] */
                    /**/
  OP_JUMP,          /** (2n) [] -> [] */
  OP_JUMP_IF_FALSE, /** (2n) [0 x] -> [0 x] */
  OP_LOOP,          /** (2n) [] -> [] */

  OP_CALL,          /** (argc) [] -> [] */
  OP_CLASS,         /** (name) [] -> [0 class] */
  OP_INHERIT,       /** [1 class][0 super] */
  OP_METHOD,        /** (name) [1 class][0 closure] -> [0 class] */
  OP_CLOSURE,       /** (fn) [] -> [0 closure] */
  OP_CLOSE_UPVALUE, /** [0 upvalue] -> [] */
  OP_PRINT,         /** [0 x] -> [] */
  OP_RETURN,        /** [0 x] -> [] */
                    /**/
  OP_INVOKE,        /** (name, n) [n self][0 ...args] -> [] */
  OP_SUPER_INVOKE,  /** (name, n) [n+1 self][1 ...args][0 super] -> [] */
  OP_ASSERT,        /** [0 value] -> [] */
                    /**/
  OP_GET_VAR,       /** (name) [0 self] -> [0 value] */
  OP_SET_VAR,       /** (name) [1 self][0 value] -> [0 value] */
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
int addConstant(Chunk *chunk, Value value);

#endif
