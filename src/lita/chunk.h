#ifndef lita_chunk_h
#define lita_chunk_h

#include "common.h"
#include "value.h"

typedef enum OpCode {
  /** (inline args) [stack] */
  OP_CONSTANT,      // (x) [] -> [x]
                    //
  OP_NIL,           // [] -> [nil]
  OP_TRUE,          // [] -> [true]
  OP_FALSE,         // [] -> [false]
                    //
  OP_RANGE,         // [start, end] -> [Range]
  OP_TUPLE,         // (argc) [...args] -> [tuple]
                    //
  OP_PEEK,          // (n) [...] -> [..., peek(n)]
  OP_POP,           // [v] -> []
  OP_POPN,          // [v, ...] -> []
  OP_SWAP,          // (ab) [x, y, ...] -> [y, x, ...]
  OP_DEFAULT,       // (v) [nil] -> [v]
                    //
  OP_DEFINE_GLOBAL, // (name) [value] -> []
  OP_GET_GLOBAL,    // (name) [] -> [value]
  OP_SET_GLOBAL,    // (name) [value] -> [value]
                    //
  OP_GET_LOCAL,     // (slot) [] -> [value]
  OP_SET_LOCAL,     // (slot) [value] -> [value]
                    //
  OP_GET_PROPERTY,  // (name) [self] -> [value]
  OP_SET_PROPERTY,  // (name) [self, value] -> [value]
                    //
  OP_GET_UPVALUE,   // (n) [] -> [value]
  OP_SET_UPVALUE,   // (n) [value] -> [value]
                    //
  OP_GET_SUPER,     // (name) [super] -> [method]
                    //
  OP_EQUAL,         // [a, b] -> [Bool]
  OP_GREATER,       // [a, b] -> [Bool]
  OP_LESS,          // [a, b] -> [Bool]
                    //
  OP_ADD,           // [a, b] -> [a+b]
  OP_SUBTRACT,      // [a, b] -> [a-b]
  OP_MULTIPLY,      // [a, b] -> [a*b]
  OP_DIVIDE,        // [a, b] -> [a/b]
                    //
  OP_NOT,           // [v] -> [!v]
  OP_NEGATE,        // [v] -> [-v]
                    //
  OP_JUMP,          // (2n) [] -> []
  OP_JUMP_IF_FALSE, // (2n) [cond] -> [cond]
  OP_LOOP,          // (2n) [] -> []
                    //
  OP_CALL,          // (argc) [] -> []
  OP_CLASS,         // (name) [] -> [class]
  OP_INHERIT,       // [super, class]
  OP_METHOD,        // (name) [closure, class] -> [class]
  OP_CLOSURE,       // (fn) [] -> [closure]
  OP_CLOSE_UPVALUE, // [upvalue] -> []
  OP_PRINT,         // [value] -> [value]
  OP_RETURN,        // [value] -> []
                    //
  OP_INVOKE,        // (name, argc) [self, ...args] -> [return]
  OP_SUPER_INVOKE,  // (name, argc) [self, ...args, super] -> [return]
  OP_ASSERT,        // (source_code) [value] -> [value]
                    //
  OP_GET_VAR,       // (name) [self] -> [value]
  OP_SET_VAR,       // (name) [self, value] -> [value]
                    //
  OP_ARRAY,         // (argc) [...args] -> [array]
  _OP_MATCH,        // UNUSED
  OP_DEBUG_STACK,   // (tag) Logs the stack.
  OP_ASSERT_STACK,  // (size) Asserts the stack is the expected size.
  OP_THROW,         // (source_location) [value] -> []

  OP_LAST,
} OpCode;

typedef struct {
  int version;
  int count;
  int capacity;
  u8 *code;
  int *lines;
  Value *comments;
  ValueArray constants;
} Chunk;

typedef enum OpType {
  SIMPLE,
  BYTE,
  CONSTANT,
  INVOKE,
  JUMP,
  CONSTANT_BYTE,
} OpType;

typedef struct OpInfo {
  const char *name;
  OpType type;
  i8 inputs;
  i8 outputs;
} OpInfo;

typedef u32 Long;
#define LONG_BYTE_MAX 0x7f

void initChunk(Chunk *chunk);
void markChunk(Chunk *chunk);
void freeChunk(Chunk *chunk);
void growChunk(Chunk *chunk, int capacity);
void writeChunk(Chunk *chunk, u8 byte, int line, Value comment);
int writeChunkLong(Chunk *chunk, Long c, int line, Value comment);
int addConstant(Chunk *chunk, Value value);
Value getConstant(Chunk *chunk, Long id);
Value readConstant(Chunk *chunk, u8 **ip);

extern OpInfo opInfo[];

u8 instructionSize(Chunk *chunk, u8 *ip);

int inputCount(Chunk *chunk, u8 *ip);
int outputCount(Chunk *chunk, u8 *ip);
int inputOutputDelta(Chunk *chunk, u8 *ip);

int encodeLong(Long c, u8 *bytes);
int decodeLong(Long *c, u8 *bytes);
#endif
