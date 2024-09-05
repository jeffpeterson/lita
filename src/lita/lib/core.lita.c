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

             // string
static Value fn_string_1() {
  ObjFunction *f = newFunction();
  f->arity = 0;
  f->upvalueCount = 0;
  f->name = newString("string");

  Chunk *c = &f->chunk;
  initChunk(c);
  c->count = c->capacity = 5;
  u8 code[] = {
    OP_CONSTANT, 0,
    OP_RETURN,
    OP_NIL,
    OP_RETURN,
  };
  int lines[] = { 2, 2, 2, 3, 3,};
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
static Value fn_dump_2() {
  ObjFunction *f = newFunction();
  f->arity = 0;
  f->upvalueCount = 0;
  f->name = newString("dump");

  Chunk *c = &f->chunk;
  initChunk(c);
  c->count = c->capacity = 5;
  u8 code[] = {
    OP_CONSTANT, 0,
    OP_RETURN,
    OP_NIL,
    OP_RETURN,
  };
  int lines[] = { 3, 3, 3, 3, 3,};
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
static Value fn_dump_3() {
  ObjFunction *f = newFunction();
  f->arity = 0;
  f->upvalueCount = 0;
  f->name = newString("dump");

  Chunk *c = &f->chunk;
  initChunk(c);
  c->count = c->capacity = 25;
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
  int lines[] = { 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 16, 16,};
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
static Value fn_dump_global_4() {
  ObjFunction *f = newFunction();
  f->arity = 0;
  f->upvalueCount = 0;
  f->name = newString("dump_global");

  Chunk *c = &f->chunk;
  initChunk(c);
  c->count = c->capacity = 53;
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
  int lines[] = { 17, 17, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 20, 20, 20, 20, 21, 21, 21, 21, 22, 22, 22, 22, 22, 22, 22, 22, 23, 23, 23, 23, 23, 23, 23,};
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
static Value fn_string_5() {
  ObjFunction *f = newFunction();
  f->arity = 0;
  f->upvalueCount = 0;
  f->name = newString("string");

  Chunk *c = &f->chunk;
  initChunk(c);
  c->count = c->capacity = 17;
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
  int lines[] = { 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 31, 31,};
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
static Value fn_print_6() {
  ObjFunction *f = newFunction();
  f->arity = 1;
  f->upvalueCount = 0;
  f->name = newString("print");

  Chunk *c = &f->chunk;
  initChunk(c);
  c->count = c->capacity = 12;
  u8 code[] = {
    OP_GET_LOCAL, 1,
    OP_GET_LOCAL, 0,
    OP_GET_VAR, 1,
    OP_INVOKE, 0, 1,
    OP_RETURN,
    OP_NIL,
    OP_RETURN,
  };
  int lines[] = { 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 32, 32,};
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
static Value fn_dump_7() {
  ObjFunction *f = newFunction();
  f->arity = 0;
  f->upvalueCount = 0;
  f->name = newString("dump");

  Chunk *c = &f->chunk;
  initChunk(c);
  c->count = c->capacity = 17;
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
  int lines[] = { 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32,};
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

             // dump
static Value fn_dump_8() {
  ObjFunction *f = newFunction();
  f->arity = 0;
  f->upvalueCount = 0;
  f->name = newString("dump");

  Chunk *c = &f->chunk;
  initChunk(c);
  c->count = c->capacity = 15;
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
  int lines[] = { 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 36, 36,};
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
static Value fn_print_9() {
  ObjFunction *f = newFunction();
  f->arity = 1;
  f->upvalueCount = 0;
  f->name = newString("print");

  Chunk *c = &f->chunk;
  initChunk(c);
  c->count = c->capacity = 12;
  u8 code[] = {
    OP_GET_LOCAL, 1,
    OP_GET_LOCAL, 0,
    OP_GET_VAR, 1,
    OP_INVOKE, 0, 1,
    OP_RETURN,
    OP_NIL,
    OP_RETURN,
  };
  int lines[] = { 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 37, 37,};
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
static Value fn__dot__10() {
  ObjFunction *f = newFunction();
  f->arity = 1;
  f->upvalueCount = 0;
  f->name = newString(".");

  Chunk *c = &f->chunk;
  initChunk(c);
  c->count = c->capacity = 8;
  u8 code[] = {
    OP_GET_LOCAL, 0,
    OP_GET_LOCAL, 1,
    OP_MULTIPLY,
    OP_RETURN,
    OP_NIL,
    OP_RETURN,
  };
  int lines[] = { 37, 37, 37, 37, 37, 37, 37, 37,};
  c->code = cloneMemory(code, sizeof(code));
  c->lines = cloneMemory(lines, sizeof(lines));

  c->constants.count = c->constants.capacity = 0;
  Value values[] = {
  };
  c->constants.values = cloneMemory(values, sizeof(values));
  return obj(f);
}

             // inspect
static Value fn_inspect_11() {
  ObjFunction *f = newFunction();
  f->arity = 0;
  f->upvalueCount = 0;
  f->name = newString("inspect");

  Chunk *c = &f->chunk;
  initChunk(c);
  c->count = c->capacity = 5;
  u8 code[] = {
    OP_CONSTANT, 0,
    OP_RETURN,
    OP_NIL,
    OP_RETURN,
  };
  int lines[] = { 40, 40, 40, 40, 40,};
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
static Value fn_init_12() {
  ObjFunction *f = newFunction();
  f->arity = 3;
  f->upvalueCount = 0;
  f->name = newString("init");

  Chunk *c = &f->chunk;
  initChunk(c);
  c->count = c->capacity = 24;
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
  int lines[] = { 42, 42, 42, 42, 42, 42, 42, 42, 42, 42, 42, 42, 42, 42, 42, 42, 42, 42, 42, 42, 42, 42, 42, 42,};
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
  c->count = c->capacity = 178;
  u8 code[] = {
    OP_CLASS, 0, 0,
    OP_GET_LOCAL, 0,
    OP_GET_VAR, 1,
    OP_INHERIT,
    OP_SWAP, 1,
    OP_CLOSURE, 3,
    OP_METHOD, 2,
    OP_CLOSURE, 5,
    OP_METHOD, 4,
    OP_POP,
    OP_POP,
    OP_CLASS, 6, 0,
    OP_GET_LOCAL, 0,
    OP_GET_VAR, 1,
    OP_INHERIT,
    OP_SWAP, 1,
    OP_POP,
    OP_POP,
    OP_CONSTANT, 8,
    OP_DEFINE_GLOBAL, 7,
    OP_CLASS, 9, 0,
    OP_GET_LOCAL, 0,
    OP_GET_VAR, 6,
    OP_INHERIT,
    OP_SWAP, 1,
    OP_CLOSURE, 10,
    OP_METHOD, 4,
    OP_CLOSURE, 12,
    OP_METHOD, 11,
    OP_POP,
    OP_POP,
    OP_CLASS, 13, 0,
    OP_GET_LOCAL, 0,
    OP_GET_VAR, 9,
    OP_INHERIT,
    OP_SWAP, 1,
    OP_POP,
    OP_POP,
    OP_CLASS, 14, 0,
    OP_GET_LOCAL, 0,
    OP_GET_VAR, 9,
    OP_INHERIT,
    OP_SWAP, 1,
    OP_POP,
    OP_POP,
    OP_CLASS, 15, 0,
    OP_GET_LOCAL, 0,
    OP_GET_VAR, 9,
    OP_INHERIT,
    OP_SWAP, 1,
    OP_POP,
    OP_POP,
    OP_CLASS, 16, 0,
    OP_GET_LOCAL, 0,
    OP_GET_VAR, 6,
    OP_INHERIT,
    OP_SWAP, 1,
    OP_CLOSURE, 17,
    OP_METHOD, 2,
    OP_CLOSURE, 19,
    OP_METHOD, 18,
    OP_CLOSURE, 20,
    OP_METHOD, 4,
    OP_POP,
    OP_POP,
    OP_CLASS, 21, 0,
    OP_GET_LOCAL, 0,
    OP_GET_VAR, 6,
    OP_INHERIT,
    OP_SWAP, 1,
    OP_CLOSURE, 22,
    OP_METHOD, 4,
    OP_CLOSURE, 23,
    OP_METHOD, 18,
    OP_CLOSURE, 25,
    OP_METHOD, 24,
    OP_POP,
    OP_POP,
    OP_CLASS, 26, 0,
    OP_GET_LOCAL, 0,
    OP_GET_VAR, 6,
    OP_INHERIT,
    OP_SWAP, 1,
    OP_CLOSURE, 28,
    OP_METHOD, 27,
    OP_POP,
    OP_POP,
    OP_CLASS, 29, 0,
    OP_CLOSURE, 30,
    OP_METHOD, 31,
    OP_GET_LOCAL, 0,
    OP_GET_VAR, 6,
    OP_INHERIT,
    OP_SWAP, 1,
    OP_POP,
    OP_POP,
    OP_GET_GLOBAL, 29,
    OP_ASSERT_STACK, 32, 2,
    OP_RETURN,
  };
  int lines[] = { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3, 3, 3, 3, 3, 3, 3, 3, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 12, 12, 12, 12, 12, 12, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 16, 16, 16, 16, 23, 23, 23, 23, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 31, 31, 31, 31, 32, 32, 32, 32, 32, 32, 32, 32, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 36, 36, 36, 36, 37, 37, 37, 37, 37, 37, 37, 37, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 40, 40, 40, 40, 42, 42, 42, 42, 42, 42, 42, 42, 42, 42, 42, 42, 42, 42, 42, 42, 43, 43, 43, 43, 43, 43, 43, 43,};
  c->code = cloneMemory(code, sizeof(code));
  c->lines = cloneMemory(lines, sizeof(lines));

  c->constants.count = c->constants.capacity = 33;
  Value values[] = {
    string("Nil"),
    string("Any"),
    string("string"),
    fn_string_1(),
    string("dump"),
    fn_dump_2(),
    string("Object"),
    string("fn_id"),
    NUMBER_VAL(0.000000),
    string("Function"),
    fn_dump_3(),
    string("dump_global"),
    fn_dump_global_4(),
    string("Method"),
    string("NativeFunction"),
    string("Class"),
    string("Bool"),
    fn_string_5(),
    string("print"),
    fn_print_6(),
    fn_dump_7(),
    string("Number"),
    fn_dump_8(),
    fn_print_9(),
    string(""),
    fn__dot__10(),
    string("Table"),
    string("inspect"),
    fn_inspect_11(),
    string("Atom"),
    fn_init_12(),
    string("init"),
    string("script return value"),
  };
  c->constants.values = cloneMemory(values, sizeof(values));
  return obj(f);
}

ObjFunction *core_lita() {
  return asFunction(fn_src_slash_lita_slash_lib_slash_core_dot_lita_0());
}
