// clang-format off
// lita -c src/lita/array.lita
#include "lita/chunk.h"
#include "lita/common.h"
#include "lita/lib.h"
#include "lita/memory.h"
#include "lita/string.h"
#include "lita/vm.h"

#if ENABLE_REGEX
#include "lita/regex.h"
#endif

static ValueArray constants__lt__lt__1() {
  ValueArray vals;
  initValueArray(&vals);
  vals.count = vals.capacity = 1;
  Value values[] = {
    str("push"),
  };
  vals.values = cloneMemory(values, sizeof(values));
  return vals;
}

static Chunk chunk__lt__lt__1() {
  Chunk c;
  initChunk(&c);
  c.count = 10;
  c.capacity = 10;
  u8 code[] = {
    14, 0, 14, 1, 41, 0, 1, 40, 1, 40,
  };
  int lines[] = {
    2, 2, 2, 2, 2, 2, 2, 2, 4, 4,
  };
  c.code = cloneMemory(code, sizeof(code));
  c.lines = cloneMemory(lines, sizeof(lines));
  c.constants = constants__lt__lt__1();

  return c;
};

             // <<
static Value fn__lt__lt__1() {
  ObjFun *f = newFunction();  f->arity = 1;
  f->upvalueCount = 0;
  f->name = newString("<<");
  f->chunk = chunk__lt__lt__1();
  return obj(f);
}

static ValueArray constants__eq__eq__2() {
  ValueArray vals;
  initValueArray(&vals);
  vals.count = vals.capacity = 8;
  Value values[] = {
    str("length"), str("At src/lita/compiler.c:1306"), str("object_id"), NUMBER_VAL(0.000000), str("At src/lita/compiler.c:1391"), str("get"), NUMBER_VAL(1.000000), str("At src/lita/compiler.c:1403"),
  };
  vals.values = cloneMemory(values, sizeof(values));
  return vals;
}

static Chunk chunk__eq__eq__2() {
  Chunk c;
  initChunk(&c);
  c.count = 116;
  c.capacity = 116;
  u8 code[] = {
    14, 0, 44, 0, 14, 1, 16, 0, 21, 28, 49, 1, 3, 31, 0, 7, 7, 3, 40, 7, 30, 0, 1, 7, 14, 0, 44, 2, 14, 1, 16, 2, 21, 49, 1, 3, 31, 0, 7, 7, 2, 40, 7, 30, 0, 1, 7, 0, 3, 14, 2, 14, 0, 44, 0, 23, 49, 4, 4, 31, 0, 45, 7, 14, 0, 44, 5, 14, 2, 33, 1, 14, 1, 14, 2, 10, 3, 6, 0, 0, 6, 24, 15, 2, 7, 41, 5, 1, 21, 28, 49, 1, 4, 31, 0, 7, 7, 3, 40, 7, 30, 0, 1, 7, 32, 0, 58, 7, 49, 7, 3, 2, 40, 7, 1, 40,
  };
  int lines[] = {
    5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 7, 7, 7, 7, 7, 7, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 12, 12,
  };
  c.code = cloneMemory(code, sizeof(code));
  c.lines = cloneMemory(lines, sizeof(lines));
  c.constants = constants__eq__eq__2();

  return c;
};

             // ==
static Value fn__eq__eq__2() {
  ObjFun *f = newFunction();  f->arity = 1;
  f->upvalueCount = 0;
  f->name = newString("==");
  f->chunk = chunk__eq__eq__2();
  return obj(f);
}

static ValueArray constants_each_3() {
  ValueArray vals;
  initValueArray(&vals);
  vals.count = vals.capacity = 6;
  Value values[] = {
    NUMBER_VAL(0.000000), str("length"), str("At src/lita/compiler.c:1391"), str("get"), NUMBER_VAL(1.000000), str("At src/lita/compiler.c:1403"),
  };
  vals.values = cloneMemory(values, sizeof(values));
  return vals;
}

static Chunk chunk_each_3() {
  Chunk c;
  initChunk(&c);
  c.count = 48;
  c.capacity = 48;
  u8 code[] = {
    0, 0, 14, 2, 14, 0, 44, 1, 23, 49, 2, 4, 31, 0, 27, 7, 14, 1, 14, 0, 44, 3, 14, 2, 10, 0, 6, 0, 0, 4, 24, 15, 2, 7, 33, 1, 33, 1, 7, 32, 0, 40, 7, 49, 5, 3, 1, 40,
  };
  int lines[] = {
    13, 13, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 17, 17, 17, 17, 17, 17, 17, 17, 17,
  };
  c.code = cloneMemory(code, sizeof(code));
  c.lines = cloneMemory(lines, sizeof(lines));
  c.constants = constants_each_3();

  return c;
};

             // each
static Value fn_each_3() {
  ObjFun *f = newFunction();  f->arity = 1;
  f->upvalueCount = 0;
  f->name = newString("each");
  f->chunk = chunk_each_3();
  return obj(f);
}

static ValueArray constants_map_4() {
  ValueArray vals;
  initValueArray(&vals);
  vals.count = vals.capacity = 7;
  Value values[] = {
    NUMBER_VAL(0.000000), str("length"), str("At src/lita/compiler.c:1391"), str("get"), NUMBER_VAL(1.000000), str("<<"), str("At src/lita/compiler.c:1403"),
  };
  vals.values = cloneMemory(values, sizeof(values));
  return vals;
}

static Chunk chunk_map_4() {
  Chunk c;
  initChunk(&c);
  c.count = 59;
  c.capacity = 59;
  u8 code[] = {
    46, 0, 0, 0, 14, 3, 14, 0, 44, 1, 23, 49, 2, 5, 31, 0, 32, 7, 14, 2, 14, 1, 14, 0, 44, 3, 14, 3, 10, 0, 6, 0, 0, 4, 24, 15, 3, 7, 33, 1, 33, 1, 41, 5, 1, 7, 32, 0, 45, 7, 49, 6, 4, 14, 2, 40, 7, 1, 40,
  };
  int lines[] = {
    18, 18, 19, 19, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 24, 24,
  };
  c.code = cloneMemory(code, sizeof(code));
  c.lines = cloneMemory(lines, sizeof(lines));
  c.constants = constants_map_4();

  return c;
};

             // map
static Value fn_map_4() {
  ObjFun *f = newFunction();  f->arity = 1;
  f->upvalueCount = 0;
  f->name = newString("map");
  f->chunk = chunk_map_4();
  return obj(f);
}

static ValueArray constants__dot_print_6() {
  ValueArray vals;
  initValueArray(&vals);
  vals.count = vals.capacity = 1;
  Value values[] = {
    str("print"),
  };
  vals.values = cloneMemory(values, sizeof(values));
  return vals;
}

static Chunk chunk__dot_print_6() {
  Chunk c;
  initChunk(&c);
  c.count = 10;
  c.capacity = 10;
  u8 code[] = {
    14, 1, 18, 0, 41, 0, 1, 40, 1, 40,
  };
  int lines[] = {
    25, 25, 25, 25, 25, 25, 25, 25, 25, 25,
  };
  c.code = cloneMemory(code, sizeof(code));
  c.lines = cloneMemory(lines, sizeof(lines));
  c.constants = constants__dot_print_6();

  return c;
};

             // .print
static Value fn__dot_print_6() {
  ObjFun *f = newFunction();  f->arity = 1;
  f->upvalueCount = 1;
  f->name = newString(".print");
  f->chunk = chunk__dot_print_6();
  return obj(f);
}

static ValueArray constants_print_5() {
  ValueArray vals;
  initValueArray(&vals);
  vals.count = vals.capacity = 2;
  Value values[] = {
    str("each"), fn__dot_print_6(),
  };
  vals.values = cloneMemory(values, sizeof(values));
  return vals;
}

static Chunk chunk_print_5() {
  Chunk c;
  initChunk(&c);
  c.count = 11;
  c.capacity = 11;
  u8 code[] = {
    14, 0, 44, 0, 37, 1, 33, 1, 7, 1, 40,
  };
  int lines[] = {
    25, 25, 25, 25, 25, 25, 25, 25, 25, 26, 26,
  };
  c.code = cloneMemory(code, sizeof(code));
  c.lines = cloneMemory(lines, sizeof(lines));
  c.constants = constants_print_5();

  return c;
};

             // print
static Value fn_print_5() {
  ObjFun *f = newFunction();  f->arity = 1;
  f->upvalueCount = 0;
  f->name = newString("print");
  f->chunk = chunk_print_5();
  return obj(f);
}

static ValueArray constants_src_slash_lita_slash_array_dot_lita_0() {
  ValueArray vals;
  initValueArray(&vals);
  vals.count = vals.capacity = 12;
  Value values[] = {
    str("Array"), str("Object"), str("<<"), fn__lt__lt__1(), str("=="), fn__eq__eq__2(), str("each"), fn_each_3(), str("map"), fn_map_4(), str("print"), fn_print_5(),
  };
  vals.values = cloneMemory(values, sizeof(values));
  return vals;
}

static Chunk chunk_src_slash_lita_slash_array_dot_lita_0() {
  Chunk c;
  initChunk(&c);
  c.count = 34;
  c.capacity = 34;
  u8 code[] = {
    34, 0, 0, 14, 0, 44, 1, 35, 9, 1, 37, 3, 36, 2, 37, 5, 36, 4, 37, 7, 36, 6, 37, 9, 36, 8, 37, 11, 36, 10, 7, 7, 1, 40,
  };
  int lines[] = {
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 4, 4, 4, 4, 12, 12, 12, 12, 17, 17, 17, 17, 24, 24, 24, 24, 26, 26, 26, 26, 26, 26, 26, 26,
  };
  c.code = cloneMemory(code, sizeof(code));
  c.lines = cloneMemory(lines, sizeof(lines));
  c.constants = constants_src_slash_lita_slash_array_dot_lita_0();

  return c;
};

             // src/lita/array.lita
static Value fn_src_slash_lita_slash_array_dot_lita_0() {
  ObjFun *f = newFunction();  f->arity = 0;
  f->upvalueCount = 0;
  f->name = newString("src/lita/array.lita");
  f->chunk = chunk_src_slash_lita_slash_array_dot_lita_0();
  return obj(f);
}

ObjFun *array_lita() {
  return AS_FUN(fn_src_slash_lita_slash_array_dot_lita_0());
}
