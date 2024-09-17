// clang-format off
// lita -c src/lita/lib/core.lita
#include "lita/chunk.h"
#include "lita/common.h"
#include "lita/lib.h"
#include "lita/memory.h"
#include "lita/string.h"
#include "lita/vm.h"

#if ENABLE_REGEX
#include "lita/regex.h"
#endif

             // !=
static Value fn__not__eq__1() {
  ObjFunction *f = newFunction();
  f->arity = 1;
  f->upvalueCount = 0;
  f->name = newString("!=");

  Chunk *c = &f->chunk;
  initChunk(c);
  c->count = c->capacity = 9;
  c->version = 1;
  u8 code[] = {
    OP_GET_LOCAL, 0,
    OP_GET_LOCAL, 1,
    OP_EQUAL,
    OP_NOT,
    OP_RETURN,
    OP_NIL,
    OP_RETURN,
  };
  int lines[] = { 2, 2, 2, 2, 2, 2, 2, 2, 2,};
  c->code = cloneMemory(code, sizeof(code));
  c->lines = cloneMemory(lines, sizeof(lines));

  c->constants.count = c->constants.capacity = 0;
  Value values[] = {
  };
  c->constants.values = cloneMemory(values, sizeof(values));
  return obj(f);
}

             // string
static Value fn_string_2() {
  ObjFunction *f = newFunction();
  f->arity = 0;
  f->upvalueCount = 0;
  f->name = newString("string");

  Chunk *c = &f->chunk;
  initChunk(c);
  c->count = c->capacity = 5;
  c->version = 1;
  u8 code[] = {
    OP_CONSTANT, 0,
    OP_RETURN,
    OP_NIL,
    OP_RETURN,
  };
  int lines[] = { 5, 5, 5, 5, 5,};
  c->code = cloneMemory(code, sizeof(code));
  c->lines = cloneMemory(lines, sizeof(lines));

  c->constants.count = c->constants.capacity = 1;
  Value values[] = {
    string(""),
  };
  c->constants.values = cloneMemory(values, sizeof(values));
  return obj(f);
}

             // dump
static Value fn_dump_3() {
  ObjFunction *f = newFunction();
  f->arity = 0;
  f->upvalueCount = 0;
  f->name = newString("dump");

  Chunk *c = &f->chunk;
  initChunk(c);
  c->count = c->capacity = 5;
  c->version = 1;
  u8 code[] = {
    OP_CONSTANT, 0,
    OP_RETURN,
    OP_NIL,
    OP_RETURN,
  };
  int lines[] = { 6, 6, 6, 6, 6,};
  c->code = cloneMemory(code, sizeof(code));
  c->lines = cloneMemory(lines, sizeof(lines));

  c->constants.count = c->constants.capacity = 1;
  Value values[] = {
    string("nil"),
  };
  c->constants.values = cloneMemory(values, sizeof(values));
  return obj(f);
}

             // dump
static Value fn_dump_4() {
  ObjFunction *f = newFunction();
  f->arity = 0;
  f->upvalueCount = 0;
  f->name = newString("dump");

  Chunk *c = &f->chunk;
  initChunk(c);
  c->count = c->capacity = 25;
  c->version = 1;
  u8 code[] = {
    OP_CONSTANT, 0,
    OP_GET_LOCAL, 0,
    OP_GET_VAR, 1,
    OP_CALL, 1,
    OP_CONSTANT, 2,
    OP_CALL, 1,
    OP_GET_LOCAL, 0,
    OP_GET_VAR, 3,
    OP_CALL, 1,
    OP_CONSTANT, 4,
    OP_CALL, 1,
    OP_RETURN,
    OP_NIL,
    OP_RETURN,
  };
  int lines[] = { 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18,};
  c->code = cloneMemory(code, sizeof(code));
  c->lines = cloneMemory(lines, sizeof(lines));

  c->constants.count = c->constants.capacity = 5;
  Value values[] = {
    string("/*"),
    string("name"),
    string("*/fn"),
    string("id"),
    string("()"),
  };
  c->constants.values = cloneMemory(values, sizeof(values));
  return obj(f);
}

             // dump_global
static Value fn_dump_global_5() {
  ObjFunction *f = newFunction();
  f->arity = 0;
  f->upvalueCount = 0;
  f->name = newString("dump_global");

  Chunk *c = &f->chunk;
  initChunk(c);
  c->count = c->capacity = 53;
  c->version = 1;
  u8 code[] = {
    OP_CONSTANT, 0,
    OP_CONSTANT, 1,
    OP_CALL, 1,
    OP_GET_LOCAL, 0,
    OP_GET_VAR, 2,
    OP_CALL, 1,
    OP_CONSTANT, 0,
    OP_CALL, 1,
    OP_CONSTANT, 3,
    OP_CALL, 1,
    OP_GET_LOCAL, 0,
    OP_GET_VAR, 4,
    OP_CALL, 1,
    OP_CONSTANT, 5,
    OP_CALL, 1,
    OP_CONSTANT, 6,
    OP_CALL, 1,
    OP_CONSTANT, 7,
    OP_CALL, 1,
    OP_CONSTANT, 8,
    OP_CALL, 1,
    OP_CONSTANT, 9,
    OP_CALL, 1,
    OP_CONSTANT, 10,
    OP_CALL, 1,
    OP_RETURN,
    OP_NIL,
    OP_RETURN,
  };
  int lines[] = { 20, 20, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 23, 23, 23, 23, 24, 24, 24, 24, 25, 25, 25, 25, 25, 25, 25, 25, 26, 26, 26, 26, 26, 26, 26,};
  c->code = cloneMemory(code, sizeof(code));
  c->lines = cloneMemory(lines, sizeof(lines));

  c->constants.count = c->constants.capacity = 11;
  Value values[] = {
    string("\n"),
    string("// "),
    string("name"),
    string("static ValueArray constants"),
    string("id"),
    string("() {\n"),
    string("  ValueArray vals;\n"),
    string("  initValueArray(&vals);\n"),
    string("  vals.count = vals.capacity = "),
    string(";\n"),
    string("  Value values[] = {"),
  };
  c->constants.values = cloneMemory(values, sizeof(values));
  return obj(f);
}

             // string
static Value fn_string_6() {
  ObjFunction *f = newFunction();
  f->arity = 0;
  f->upvalueCount = 0;
  f->name = newString("string");

  Chunk *c = &f->chunk;
  initChunk(c);
  c->count = c->capacity = 17;
  c->version = 1;
  u8 code[] = {
    OP_GET_LOCAL, 0,
    OP_JUMP_IF_FALSE, 0, 6,
    OP_POP,
    OP_CONSTANT, 0,
    OP_JUMP, 0, 3,
    OP_POP,
    OP_CONSTANT, 1,
    OP_RETURN,
    OP_NIL,
    OP_RETURN,
  };
  int lines[] = { 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33,};
  c->code = cloneMemory(code, sizeof(code));
  c->lines = cloneMemory(lines, sizeof(lines));

  c->constants.count = c->constants.capacity = 2;
  Value values[] = {
    string("true"),
    string("false"),
  };
  c->constants.values = cloneMemory(values, sizeof(values));
  return obj(f);
}

             // print
static Value fn_print_7() {
  ObjFunction *f = newFunction();
  f->arity = 1;
  f->upvalueCount = 0;
  f->name = newString("print");

  Chunk *c = &f->chunk;
  initChunk(c);
  c->count = c->capacity = 12;
  c->version = 1;
  u8 code[] = {
    OP_GET_LOCAL, 1,
    OP_GET_LOCAL, 0,
    OP_GET_VAR, 1,
    OP_INVOKE, 0, 1,
    OP_RETURN,
    OP_NIL,
    OP_RETURN,
  };
  int lines[] = { 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34,};
  c->code = cloneMemory(code, sizeof(code));
  c->lines = cloneMemory(lines, sizeof(lines));

  c->constants.count = c->constants.capacity = 2;
  Value values[] = {
    string("write"),
    string("string"),
  };
  c->constants.values = cloneMemory(values, sizeof(values));
  return obj(f);
}

             // dump
static Value fn_dump_8() {
  ObjFunction *f = newFunction();
  f->arity = 0;
  f->upvalueCount = 0;
  f->name = newString("dump");

  Chunk *c = &f->chunk;
  initChunk(c);
  c->count = c->capacity = 17;
  c->version = 1;
  u8 code[] = {
    OP_GET_LOCAL, 0,
    OP_JUMP_IF_FALSE, 0, 6,
    OP_POP,
    OP_CONSTANT, 0,
    OP_JUMP, 0, 3,
    OP_POP,
    OP_CONSTANT, 1,
    OP_RETURN,
    OP_NIL,
    OP_RETURN,
  };
  int lines[] = { 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35,};
  c->code = cloneMemory(code, sizeof(code));
  c->lines = cloneMemory(lines, sizeof(lines));

  c->constants.count = c->constants.capacity = 2;
  Value values[] = {
    string("TRUE_VAL"),
    string("FALSE_VAL"),
  };
  c->constants.values = cloneMemory(values, sizeof(values));
  return obj(f);
}

             // inc
static Value fn_inc_9() {
  ObjFunction *f = newFunction();
  f->arity = 0;
  f->upvalueCount = 0;
  f->name = newString("inc");

  Chunk *c = &f->chunk;
  initChunk(c);
  c->count = c->capacity = 8;
  c->version = 1;
  u8 code[] = {
    OP_GET_LOCAL, 0,
    OP_CONSTANT, 0,
    OP_ADD,
    OP_RETURN,
    OP_NIL,
    OP_RETURN,
  };
  int lines[] = { 38, 38, 38, 38, 38, 38, 38, 38,};
  c->code = cloneMemory(code, sizeof(code));
  c->lines = cloneMemory(lines, sizeof(lines));

  c->constants.count = c->constants.capacity = 1;
  Value values[] = {
    NUMBER_VAL(1.000000),
  };
  c->constants.values = cloneMemory(values, sizeof(values));
  return obj(f);
}

             // dec
static Value fn_dec_10() {
  ObjFunction *f = newFunction();
  f->arity = 0;
  f->upvalueCount = 0;
  f->name = newString("dec");

  Chunk *c = &f->chunk;
  initChunk(c);
  c->count = c->capacity = 8;
  c->version = 1;
  u8 code[] = {
    OP_GET_LOCAL, 0,
    OP_CONSTANT, 0,
    OP_SUBTRACT,
    OP_RETURN,
    OP_NIL,
    OP_RETURN,
  };
  int lines[] = { 39, 39, 39, 39, 39, 39, 39, 39,};
  c->code = cloneMemory(code, sizeof(code));
  c->lines = cloneMemory(lines, sizeof(lines));

  c->constants.count = c->constants.capacity = 1;
  Value values[] = {
    NUMBER_VAL(1.000000),
  };
  c->constants.values = cloneMemory(values, sizeof(values));
  return obj(f);
}

             // dump
static Value fn_dump_11() {
  ObjFunction *f = newFunction();
  f->arity = 0;
  f->upvalueCount = 0;
  f->name = newString("dump");

  Chunk *c = &f->chunk;
  initChunk(c);
  c->count = c->capacity = 15;
  c->version = 1;
  u8 code[] = {
    OP_CONSTANT, 0,
    OP_GET_LOCAL, 0,
    OP_GET_VAR, 1,
    OP_CALL, 1,
    OP_CONSTANT, 2,
    OP_CALL, 1,
    OP_RETURN,
    OP_NIL,
    OP_RETURN,
  };
  int lines[] = { 40, 40, 40, 40, 40, 40, 40, 40, 40, 40, 40, 40, 40, 40, 40,};
  c->code = cloneMemory(code, sizeof(code));
  c->lines = cloneMemory(lines, sizeof(lines));

  c->constants.count = c->constants.capacity = 3;
  Value values[] = {
    string("NUMBER_VAL("),
    string("string"),
    string(")"),
  };
  c->constants.values = cloneMemory(values, sizeof(values));
  return obj(f);
}

             // print
static Value fn_print_12() {
  ObjFunction *f = newFunction();
  f->arity = 1;
  f->upvalueCount = 0;
  f->name = newString("print");

  Chunk *c = &f->chunk;
  initChunk(c);
  c->count = c->capacity = 12;
  c->version = 1;
  u8 code[] = {
    OP_GET_LOCAL, 1,
    OP_GET_LOCAL, 0,
    OP_GET_VAR, 1,
    OP_INVOKE, 0, 1,
    OP_RETURN,
    OP_NIL,
    OP_RETURN,
  };
  int lines[] = { 41, 41, 41, 41, 41, 41, 41, 41, 41, 41, 41, 41,};
  c->code = cloneMemory(code, sizeof(code));
  c->lines = cloneMemory(lines, sizeof(lines));

  c->constants.count = c->constants.capacity = 2;
  Value values[] = {
    string("write"),
    string("string"),
  };
  c->constants.values = cloneMemory(values, sizeof(values));
  return obj(f);
}

             // .
static Value fn__dot__13() {
  ObjFunction *f = newFunction();
  f->arity = 1;
  f->upvalueCount = 0;
  f->name = newString(".");

  Chunk *c = &f->chunk;
  initChunk(c);
  c->count = c->capacity = 8;
  c->version = 1;
  u8 code[] = {
    OP_GET_LOCAL, 0,
    OP_GET_LOCAL, 1,
    OP_MULTIPLY,
    OP_RETURN,
    OP_NIL,
    OP_RETURN,
  };
  int lines[] = { 42, 42, 42, 42, 42, 42, 42, 42,};
  c->code = cloneMemory(code, sizeof(code));
  c->lines = cloneMemory(lines, sizeof(lines));

  c->constants.count = c->constants.capacity = 0;
  Value values[] = {
  };
  c->constants.values = cloneMemory(values, sizeof(values));
  return obj(f);
}

             // inspect
static Value fn_inspect_14() {
  ObjFunction *f = newFunction();
  f->arity = 0;
  f->upvalueCount = 0;
  f->name = newString("inspect");

  Chunk *c = &f->chunk;
  initChunk(c);
  c->count = c->capacity = 5;
  c->version = 1;
  u8 code[] = {
    OP_CONSTANT, 0,
    OP_RETURN,
    OP_NIL,
    OP_RETURN,
  };
  int lines[] = { 45, 45, 45, 45, 45,};
  c->code = cloneMemory(code, sizeof(code));
  c->lines = cloneMemory(lines, sizeof(lines));

  c->constants.count = c->constants.capacity = 1;
  Value values[] = {
    string("{}"),
  };
  c->constants.values = cloneMemory(values, sizeof(values));
  return obj(f);
}

             // init
static Value fn_init_15() {
  ObjFunction *f = newFunction();
  f->arity = 3;
  f->upvalueCount = 0;
  f->name = newString("init");

  Chunk *c = &f->chunk;
  initChunk(c);
  c->count = c->capacity = 24;
  c->version = 1;
  u8 code[] = {
    OP_GET_LOCAL, 0,
    OP_GET_LOCAL, 1,
    OP_SET_PROPERTY, 0,
    OP_POP,
    OP_GET_LOCAL, 0,
    OP_GET_LOCAL, 2,
    OP_SET_PROPERTY, 1,
    OP_POP,
    OP_GET_LOCAL, 0,
    OP_GET_LOCAL, 3,
    OP_SET_PROPERTY, 2,
    OP_POP,
    OP_GET_LOCAL, 0,
    OP_RETURN,
  };
  int lines[] = { 47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 47,};
  c->code = cloneMemory(code, sizeof(code));
  c->lines = cloneMemory(lines, sizeof(lines));

  c->constants.count = c->constants.capacity = 3;
  Value values[] = {
    string("type"),
    string("value"),
    string("targets"),
  };
  c->constants.values = cloneMemory(values, sizeof(values));
  return obj(f);
}

             // src/lita/lib/core.lita
static Value fn_src_slash_lita_slash_lib_slash_core_dot_lita_0() {
  ObjFunction *f = newFunction();
  f->arity = 0;
  f->upvalueCount = 0;
  f->name = newString("src/lita/lib/core.lita");

  Chunk *c = &f->chunk;
  initChunk(c);
  c->count = c->capacity = 199;
  c->version = 1;
  u8 code[] = {
    OP_CLASS, 0, 0,
    OP_NIL,
    OP_INHERIT,
    OP_SWAP, 1,
    OP_CONSTANT, 2,
    OP_METHOD, 1,
    OP_POP,
    OP_POP,
    OP_CLASS, 3, 0,
    OP_GET_LOCAL, 0,
    OP_GET_VAR, 0,
    OP_INHERIT,
    OP_SWAP, 1,
    OP_CONSTANT, 5,
    OP_METHOD, 4,
    OP_CONSTANT, 7,
    OP_METHOD, 6,
    OP_POP,
    OP_POP,
    OP_CLASS, 8, 0,
    OP_GET_LOCAL, 0,
    OP_GET_VAR, 0,
    OP_INHERIT,
    OP_SWAP, 1,
    OP_POP,
    OP_POP,
    OP_CONSTANT, 10,
    OP_DEFINE_GLOBAL, 9,
    OP_CLASS, 11, 0,
    OP_GET_LOCAL, 0,
    OP_GET_VAR, 8,
    OP_INHERIT,
    OP_SWAP, 1,
    OP_CONSTANT, 12,
    OP_METHOD, 6,
    OP_CONSTANT, 14,
    OP_METHOD, 13,
    OP_POP,
    OP_POP,
    OP_CLASS, 15, 0,
    OP_GET_LOCAL, 0,
    OP_GET_VAR, 11,
    OP_INHERIT,
    OP_SWAP, 1,
    OP_POP,
    OP_POP,
    OP_CLASS, 16, 0,
    OP_GET_LOCAL, 0,
    OP_GET_VAR, 11,
    OP_INHERIT,
    OP_SWAP, 1,
    OP_POP,
    OP_POP,
    OP_CLASS, 17, 0,
    OP_GET_LOCAL, 0,
    OP_GET_VAR, 11,
    OP_INHERIT,
    OP_SWAP, 1,
    OP_POP,
    OP_POP,
    OP_CLASS, 18, 0,
    OP_GET_LOCAL, 0,
    OP_GET_VAR, 8,
    OP_INHERIT,
    OP_SWAP, 1,
    OP_CONSTANT, 19,
    OP_METHOD, 4,
    OP_CONSTANT, 21,
    OP_METHOD, 20,
    OP_CONSTANT, 22,
    OP_METHOD, 6,
    OP_POP,
    OP_POP,
    OP_CLASS, 23, 0,
    OP_GET_LOCAL, 0,
    OP_GET_VAR, 8,
    OP_INHERIT,
    OP_SWAP, 1,
    OP_CONSTANT, 25,
    OP_METHOD, 24,
    OP_CONSTANT, 27,
    OP_METHOD, 26,
    OP_CONSTANT, 28,
    OP_METHOD, 6,
    OP_CONSTANT, 29,
    OP_METHOD, 20,
    OP_CONSTANT, 31,
    OP_METHOD, 30,
    OP_POP,
    OP_POP,
    OP_CLASS, 32, 0,
    OP_GET_LOCAL, 0,
    OP_GET_VAR, 8,
    OP_INHERIT,
    OP_SWAP, 1,
    OP_CONSTANT, 34,
    OP_METHOD, 33,
    OP_POP,
    OP_POP,
    OP_CLASS, 35, 0,
    OP_CONSTANT, 36,
    OP_METHOD, 37,
    OP_GET_LOCAL, 0,
    OP_GET_VAR, 8,
    OP_INHERIT,
    OP_SWAP, 1,
    OP_POP,
    OP_POP,
    OP_GET_GLOBAL, 35,
    OP_ASSERT_STACK, 38, 2,
    OP_RETURN,
  };
  int lines[] = { 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 5, 5, 5, 5, 6, 6, 6, 6, 6, 6, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 15, 15, 15, 15, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 18, 18, 18, 18, 26, 26, 26, 26, 26, 26, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 33, 33, 33, 33, 34, 34, 34, 34, 35, 35, 35, 35, 35, 35, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 38, 38, 38, 38, 39, 39, 39, 39, 40, 40, 40, 40, 41, 41, 41, 41, 42, 42, 42, 42, 42, 42, 44, 44, 44, 44, 44, 44, 44, 44, 44, 44, 45, 45, 45, 45, 45, 45, 47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 48, 48, 48, 48,};
  c->code = cloneMemory(code, sizeof(code));
  c->lines = cloneMemory(lines, sizeof(lines));

  c->constants.count = c->constants.capacity = 39;
  Value values[] = {
    string("Any"),
    string("!="),
    fn__not__eq__1(),
    string("Nil"),
    string("string"),
    fn_string_2(),
    string("dump"),
    fn_dump_3(),
    string("Object"),
    string("fn_id"),
    NUMBER_VAL(0.000000),
    string("Function"),
    fn_dump_4(),
    string("dump_global"),
    fn_dump_global_5(),
    string("Method"),
    string("NativeFunction"),
    string("Class"),
    string("Bool"),
    fn_string_6(),
    string("print"),
    fn_print_7(),
    fn_dump_8(),
    string("Number"),
    string("inc"),
    fn_inc_9(),
    string("dec"),
    fn_dec_10(),
    fn_dump_11(),
    fn_print_12(),
    string(""),
    fn__dot__13(),
    string("Table"),
    string("inspect"),
    fn_inspect_14(),
    string("Atom"),
    fn_init_15(),
    string("init"),
    string("script return value"),
  };
  c->constants.values = cloneMemory(values, sizeof(values));
  return obj(f);
}

ObjFunction *core_lita() {
  return asFunction(fn_src_slash_lita_slash_lib_slash_core_dot_lita_0());
}
