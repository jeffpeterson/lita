// clang-format off
// sol -c lib/core.sol
#include "../chunk.h"
#include "../common.h"
#include "../lib.h"
#include "../memory.h"
#include "../string.h"

static ValueArray eqlConstants1() {
  ValueArray vals;
  initValueArray(&vals);
  vals.count = vals.capacity = 5;
  Value values[] = {
    str("length"), str("objectId"), 0, 0x3ff0000000000000, str("get"),
  };
  vals.values = cloneMemory(values, sizeof(values));
  return vals;
}

static Chunk eqlChunk1() {
  Chunk c;
  initChunk(&c);
  c.count = 107;
  c.capacity = 107;
  u8 code[] = {
    14, 0, 44, 0, 14, 1, 16, 0, 21, 28, 31, 0, 6, 7, 3, 40, 30, 0, 1, 7, 14, 0, 44, 1, 14, 1, 16, 1, 21, 31, 0, 6, 7, 2, 40, 30, 0, 1, 7, 0, 2, 14, 2, 14, 0, 44, 0, 23, 31, 0, 50, 7, 30, 0, 16, 14, 2, 10, 2, 6, 0, 0, 3, 24, 15, 2, 7, 7, 32, 0, 30, 14, 0, 44, 4, 14, 2, 33, 1, 14, 1, 14, 2, 41, 4, 1, 21, 28, 31, 0, 6, 7, 3, 40, 30, 0, 1, 7, 32, 0, 46, 7, 7, 2, 40, 1, 40,
  };
  int lines[] = {
    16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 22, 22, 22,
  };
  c.code = cloneMemory(code, sizeof(code));
  c.lines = cloneMemory(lines, sizeof(lines));
  c.constants = eqlConstants1();

  return c;
};

static Value eqlFn1() {
  ObjFun *f = newFunction();  f->arity = 1;
  f->upvalueCount = 0;
  f->name = newString("eql");
  f->chunk = eqlChunk1();
  return obj(f);
}

static ValueArray initConstants2() {
  ValueArray vals;
  initValueArray(&vals);
  vals.count = vals.capacity = 2;
  Value values[] = {
    str("start"), str("end"),
  };
  vals.values = cloneMemory(values, sizeof(values));
  return vals;
}

static Chunk initChunk2() {
  Chunk c;
  initChunk(&c);
  c.count = 17;
  c.capacity = 17;
  u8 code[] = {
    14, 0, 14, 1, 17, 0, 7, 14, 0, 14, 2, 17, 1, 7, 14, 0, 40,
  };
  int lines[] = {
    26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26,
  };
  c.code = cloneMemory(code, sizeof(code));
  c.lines = cloneMemory(lines, sizeof(lines));
  c.constants = initConstants2();

  return c;
};

static Value initFn2() {
  ObjFun *f = newFunction();  f->arity = 2;
  f->upvalueCount = 0;
  f->name = newString("init");
  f->chunk = initChunk2();
  return obj(f);
}

static ValueArray inspectConstants3() {
  ValueArray vals;
  initValueArray(&vals);
  vals.count = vals.capacity = 4;
  Value values[] = {
    str("start"), str("inspect"), str(".."), str("end"),
  };
  vals.values = cloneMemory(values, sizeof(values));
  return vals;
}

static Chunk inspectChunk3() {
  Chunk c;
  initChunk(&c);
  c.count = 19;
  c.capacity = 19;
  u8 code[] = {
    14, 0, 44, 0, 16, 1, 0, 2, 24, 14, 0, 44, 3, 16, 1, 24, 40, 1, 40,
  };
  int lines[] = {
    27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 28, 28,
  };
  c.code = cloneMemory(code, sizeof(code));
  c.lines = cloneMemory(lines, sizeof(lines));
  c.constants = inspectConstants3();

  return c;
};

static Value inspectFn3() {
  ObjFun *f = newFunction();  f->arity = 0;
  f->upvalueCount = 0;
  f->name = newString("inspect");
  f->chunk = inspectChunk3();
  return obj(f);
}

static ValueArray stringConstants4() {
  ValueArray vals;
  initValueArray(&vals);
  vals.count = vals.capacity = 4;
  Value values[] = {
    str("start"), str("string"), str(".."), str("end"),
  };
  vals.values = cloneMemory(values, sizeof(values));
  return vals;
}

static Chunk stringChunk4() {
  Chunk c;
  initChunk(&c);
  c.count = 19;
  c.capacity = 19;
  u8 code[] = {
    14, 0, 44, 0, 16, 1, 0, 2, 24, 14, 0, 44, 3, 16, 1, 24, 40, 1, 40,
  };
  int lines[] = {
    28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 30, 30,
  };
  c.code = cloneMemory(code, sizeof(code));
  c.lines = cloneMemory(lines, sizeof(lines));
  c.constants = stringConstants4();

  return c;
};

static Value stringFn4() {
  ObjFun *f = newFunction();  f->arity = 0;
  f->upvalueCount = 0;
  f->name = newString("string");
  f->chunk = stringChunk4();
  return obj(f);
}

static ValueArray boldConstants5() {
  ValueArray vals;
  initValueArray(&vals);
  vals.count = vals.capacity = 2;
  Value values[] = {
    str("[1m"), str("[21m"),
  };
  vals.values = cloneMemory(values, sizeof(values));
  return vals;
}

static Chunk boldChunk5() {
  Chunk c;
  initChunk(&c);
  c.count = 11;
  c.capacity = 11;
  u8 code[] = {
    0, 0, 14, 0, 24, 0, 1, 24, 40, 1, 40,
  };
  int lines[] = {
    31, 31, 31, 31, 31, 31, 31, 31, 31, 32, 32,
  };
  c.code = cloneMemory(code, sizeof(code));
  c.lines = cloneMemory(lines, sizeof(lines));
  c.constants = boldConstants5();

  return c;
};

static Value boldFn5() {
  ObjFun *f = newFunction();  f->arity = 0;
  f->upvalueCount = 0;
  f->name = newString("bold");
  f->chunk = boldChunk5();
  return obj(f);
}

static ValueArray dimConstants6() {
  ValueArray vals;
  initValueArray(&vals);
  vals.count = vals.capacity = 2;
  Value values[] = {
    str("[2m"), str("[22m"),
  };
  vals.values = cloneMemory(values, sizeof(values));
  return vals;
}

static Chunk dimChunk6() {
  Chunk c;
  initChunk(&c);
  c.count = 11;
  c.capacity = 11;
  u8 code[] = {
    0, 0, 14, 0, 24, 0, 1, 24, 40, 1, 40,
  };
  int lines[] = {
    32, 32, 32, 32, 32, 32, 32, 32, 32, 33, 33,
  };
  c.code = cloneMemory(code, sizeof(code));
  c.lines = cloneMemory(lines, sizeof(lines));
  c.constants = dimConstants6();

  return c;
};

static Value dimFn6() {
  ObjFun *f = newFunction();  f->arity = 0;
  f->upvalueCount = 0;
  f->name = newString("dim");
  f->chunk = dimChunk6();
  return obj(f);
}

static ValueArray italicConstants7() {
  ValueArray vals;
  initValueArray(&vals);
  vals.count = vals.capacity = 2;
  Value values[] = {
    str("[3m"), str("[23m"),
  };
  vals.values = cloneMemory(values, sizeof(values));
  return vals;
}

static Chunk italicChunk7() {
  Chunk c;
  initChunk(&c);
  c.count = 11;
  c.capacity = 11;
  u8 code[] = {
    0, 0, 14, 0, 24, 0, 1, 24, 40, 1, 40,
  };
  int lines[] = {
    33, 33, 33, 33, 33, 33, 33, 33, 33, 34, 34,
  };
  c.code = cloneMemory(code, sizeof(code));
  c.lines = cloneMemory(lines, sizeof(lines));
  c.constants = italicConstants7();

  return c;
};

static Value italicFn7() {
  ObjFun *f = newFunction();  f->arity = 0;
  f->upvalueCount = 0;
  f->name = newString("italic");
  f->chunk = italicChunk7();
  return obj(f);
}

static ValueArray underlineConstants8() {
  ValueArray vals;
  initValueArray(&vals);
  vals.count = vals.capacity = 2;
  Value values[] = {
    str("[4m"), str("[24m"),
  };
  vals.values = cloneMemory(values, sizeof(values));
  return vals;
}

static Chunk underlineChunk8() {
  Chunk c;
  initChunk(&c);
  c.count = 11;
  c.capacity = 11;
  u8 code[] = {
    0, 0, 14, 0, 24, 0, 1, 24, 40, 1, 40,
  };
  int lines[] = {
    34, 34, 34, 34, 34, 34, 34, 34, 34, 35, 35,
  };
  c.code = cloneMemory(code, sizeof(code));
  c.lines = cloneMemory(lines, sizeof(lines));
  c.constants = underlineConstants8();

  return c;
};

static Value underlineFn8() {
  ObjFun *f = newFunction();  f->arity = 0;
  f->upvalueCount = 0;
  f->name = newString("underline");
  f->chunk = underlineChunk8();
  return obj(f);
}

static ValueArray invertConstants9() {
  ValueArray vals;
  initValueArray(&vals);
  vals.count = vals.capacity = 2;
  Value values[] = {
    str("[7m"), str("[27m"),
  };
  vals.values = cloneMemory(values, sizeof(values));
  return vals;
}

static Chunk invertChunk9() {
  Chunk c;
  initChunk(&c);
  c.count = 11;
  c.capacity = 11;
  u8 code[] = {
    0, 0, 14, 0, 24, 0, 1, 24, 40, 1, 40,
  };
  int lines[] = {
    35, 35, 35, 35, 35, 35, 35, 35, 35, 36, 36,
  };
  c.code = cloneMemory(code, sizeof(code));
  c.lines = cloneMemory(lines, sizeof(lines));
  c.constants = invertConstants9();

  return c;
};

static Value invertFn9() {
  ObjFun *f = newFunction();  f->arity = 0;
  f->upvalueCount = 0;
  f->name = newString("invert");
  f->chunk = invertChunk9();
  return obj(f);
}

static ValueArray hideConstants10() {
  ValueArray vals;
  initValueArray(&vals);
  vals.count = vals.capacity = 2;
  Value values[] = {
    str("[8m"), str("[28m"),
  };
  vals.values = cloneMemory(values, sizeof(values));
  return vals;
}

static Chunk hideChunk10() {
  Chunk c;
  initChunk(&c);
  c.count = 11;
  c.capacity = 11;
  u8 code[] = {
    0, 0, 14, 0, 24, 0, 1, 24, 40, 1, 40,
  };
  int lines[] = {
    36, 36, 36, 36, 36, 36, 36, 36, 36, 37, 37,
  };
  c.code = cloneMemory(code, sizeof(code));
  c.lines = cloneMemory(lines, sizeof(lines));
  c.constants = hideConstants10();

  return c;
};

static Value hideFn10() {
  ObjFun *f = newFunction();  f->arity = 0;
  f->upvalueCount = 0;
  f->name = newString("hide");
  f->chunk = hideChunk10();
  return obj(f);
}

static ValueArray strikeConstants11() {
  ValueArray vals;
  initValueArray(&vals);
  vals.count = vals.capacity = 2;
  Value values[] = {
    str("[9m"), str("[29m"),
  };
  vals.values = cloneMemory(values, sizeof(values));
  return vals;
}

static Chunk strikeChunk11() {
  Chunk c;
  initChunk(&c);
  c.count = 11;
  c.capacity = 11;
  u8 code[] = {
    0, 0, 14, 0, 24, 0, 1, 24, 40, 1, 40,
  };
  int lines[] = {
    37, 37, 37, 37, 37, 37, 37, 37, 37, 39, 39,
  };
  c.code = cloneMemory(code, sizeof(code));
  c.lines = cloneMemory(lines, sizeof(lines));
  c.constants = strikeConstants11();

  return c;
};

static Value strikeFn11() {
  ObjFun *f = newFunction();  f->arity = 0;
  f->upvalueCount = 0;
  f->name = newString("strike");
  f->chunk = strikeChunk11();
  return obj(f);
}

static ValueArray blackConstants12() {
  ValueArray vals;
  initValueArray(&vals);
  vals.count = vals.capacity = 2;
  Value values[] = {
    str("[30m"), str("[39m"),
  };
  vals.values = cloneMemory(values, sizeof(values));
  return vals;
}

static Chunk blackChunk12() {
  Chunk c;
  initChunk(&c);
  c.count = 11;
  c.capacity = 11;
  u8 code[] = {
    0, 0, 14, 0, 24, 0, 1, 24, 40, 1, 40,
  };
  int lines[] = {
    39, 39, 39, 39, 39, 39, 39, 39, 39, 40, 40,
  };
  c.code = cloneMemory(code, sizeof(code));
  c.lines = cloneMemory(lines, sizeof(lines));
  c.constants = blackConstants12();

  return c;
};

static Value blackFn12() {
  ObjFun *f = newFunction();  f->arity = 0;
  f->upvalueCount = 0;
  f->name = newString("black");
  f->chunk = blackChunk12();
  return obj(f);
}

static ValueArray redConstants13() {
  ValueArray vals;
  initValueArray(&vals);
  vals.count = vals.capacity = 2;
  Value values[] = {
    str("[31m"), str("[39m"),
  };
  vals.values = cloneMemory(values, sizeof(values));
  return vals;
}

static Chunk redChunk13() {
  Chunk c;
  initChunk(&c);
  c.count = 11;
  c.capacity = 11;
  u8 code[] = {
    0, 0, 14, 0, 24, 0, 1, 24, 40, 1, 40,
  };
  int lines[] = {
    40, 40, 40, 40, 40, 40, 40, 40, 40, 41, 41,
  };
  c.code = cloneMemory(code, sizeof(code));
  c.lines = cloneMemory(lines, sizeof(lines));
  c.constants = redConstants13();

  return c;
};

static Value redFn13() {
  ObjFun *f = newFunction();  f->arity = 0;
  f->upvalueCount = 0;
  f->name = newString("red");
  f->chunk = redChunk13();
  return obj(f);
}

static ValueArray greenConstants14() {
  ValueArray vals;
  initValueArray(&vals);
  vals.count = vals.capacity = 2;
  Value values[] = {
    str("[32m"), str("[39m"),
  };
  vals.values = cloneMemory(values, sizeof(values));
  return vals;
}

static Chunk greenChunk14() {
  Chunk c;
  initChunk(&c);
  c.count = 11;
  c.capacity = 11;
  u8 code[] = {
    0, 0, 14, 0, 24, 0, 1, 24, 40, 1, 40,
  };
  int lines[] = {
    41, 41, 41, 41, 41, 41, 41, 41, 41, 42, 42,
  };
  c.code = cloneMemory(code, sizeof(code));
  c.lines = cloneMemory(lines, sizeof(lines));
  c.constants = greenConstants14();

  return c;
};

static Value greenFn14() {
  ObjFun *f = newFunction();  f->arity = 0;
  f->upvalueCount = 0;
  f->name = newString("green");
  f->chunk = greenChunk14();
  return obj(f);
}

static ValueArray yellowConstants15() {
  ValueArray vals;
  initValueArray(&vals);
  vals.count = vals.capacity = 2;
  Value values[] = {
    str("[33m"), str("[39m"),
  };
  vals.values = cloneMemory(values, sizeof(values));
  return vals;
}

static Chunk yellowChunk15() {
  Chunk c;
  initChunk(&c);
  c.count = 11;
  c.capacity = 11;
  u8 code[] = {
    0, 0, 14, 0, 24, 0, 1, 24, 40, 1, 40,
  };
  int lines[] = {
    42, 42, 42, 42, 42, 42, 42, 42, 42, 43, 43,
  };
  c.code = cloneMemory(code, sizeof(code));
  c.lines = cloneMemory(lines, sizeof(lines));
  c.constants = yellowConstants15();

  return c;
};

static Value yellowFn15() {
  ObjFun *f = newFunction();  f->arity = 0;
  f->upvalueCount = 0;
  f->name = newString("yellow");
  f->chunk = yellowChunk15();
  return obj(f);
}

static ValueArray blueConstants16() {
  ValueArray vals;
  initValueArray(&vals);
  vals.count = vals.capacity = 2;
  Value values[] = {
    str("[34m"), str("[39m"),
  };
  vals.values = cloneMemory(values, sizeof(values));
  return vals;
}

static Chunk blueChunk16() {
  Chunk c;
  initChunk(&c);
  c.count = 11;
  c.capacity = 11;
  u8 code[] = {
    0, 0, 14, 0, 24, 0, 1, 24, 40, 1, 40,
  };
  int lines[] = {
    43, 43, 43, 43, 43, 43, 43, 43, 43, 44, 44,
  };
  c.code = cloneMemory(code, sizeof(code));
  c.lines = cloneMemory(lines, sizeof(lines));
  c.constants = blueConstants16();

  return c;
};

static Value blueFn16() {
  ObjFun *f = newFunction();  f->arity = 0;
  f->upvalueCount = 0;
  f->name = newString("blue");
  f->chunk = blueChunk16();
  return obj(f);
}

static ValueArray magentaConstants17() {
  ValueArray vals;
  initValueArray(&vals);
  vals.count = vals.capacity = 2;
  Value values[] = {
    str("[35m"), str("[39m"),
  };
  vals.values = cloneMemory(values, sizeof(values));
  return vals;
}

static Chunk magentaChunk17() {
  Chunk c;
  initChunk(&c);
  c.count = 11;
  c.capacity = 11;
  u8 code[] = {
    0, 0, 14, 0, 24, 0, 1, 24, 40, 1, 40,
  };
  int lines[] = {
    44, 44, 44, 44, 44, 44, 44, 44, 44, 45, 45,
  };
  c.code = cloneMemory(code, sizeof(code));
  c.lines = cloneMemory(lines, sizeof(lines));
  c.constants = magentaConstants17();

  return c;
};

static Value magentaFn17() {
  ObjFun *f = newFunction();  f->arity = 0;
  f->upvalueCount = 0;
  f->name = newString("magenta");
  f->chunk = magentaChunk17();
  return obj(f);
}

static ValueArray cyanConstants18() {
  ValueArray vals;
  initValueArray(&vals);
  vals.count = vals.capacity = 2;
  Value values[] = {
    str("[36m"), str("[39m"),
  };
  vals.values = cloneMemory(values, sizeof(values));
  return vals;
}

static Chunk cyanChunk18() {
  Chunk c;
  initChunk(&c);
  c.count = 11;
  c.capacity = 11;
  u8 code[] = {
    0, 0, 14, 0, 24, 0, 1, 24, 40, 1, 40,
  };
  int lines[] = {
    45, 45, 45, 45, 45, 45, 45, 45, 45, 46, 46,
  };
  c.code = cloneMemory(code, sizeof(code));
  c.lines = cloneMemory(lines, sizeof(lines));
  c.constants = cyanConstants18();

  return c;
};

static Value cyanFn18() {
  ObjFun *f = newFunction();  f->arity = 0;
  f->upvalueCount = 0;
  f->name = newString("cyan");
  f->chunk = cyanChunk18();
  return obj(f);
}

static ValueArray whiteConstants19() {
  ValueArray vals;
  initValueArray(&vals);
  vals.count = vals.capacity = 2;
  Value values[] = {
    str("[37m"), str("[39m"),
  };
  vals.values = cloneMemory(values, sizeof(values));
  return vals;
}

static Chunk whiteChunk19() {
  Chunk c;
  initChunk(&c);
  c.count = 11;
  c.capacity = 11;
  u8 code[] = {
    0, 0, 14, 0, 24, 0, 1, 24, 40, 1, 40,
  };
  int lines[] = {
    46, 46, 46, 46, 46, 46, 46, 46, 46, 48, 48,
  };
  c.code = cloneMemory(code, sizeof(code));
  c.lines = cloneMemory(lines, sizeof(lines));
  c.constants = whiteConstants19();

  return c;
};

static Value whiteFn19() {
  ObjFun *f = newFunction();  f->arity = 0;
  f->upvalueCount = 0;
  f->name = newString("white");
  f->chunk = whiteChunk19();
  return obj(f);
}

static ValueArray bg_blackConstants20() {
  ValueArray vals;
  initValueArray(&vals);
  vals.count = vals.capacity = 2;
  Value values[] = {
    str("[40m"), str("[39m"),
  };
  vals.values = cloneMemory(values, sizeof(values));
  return vals;
}

static Chunk bg_blackChunk20() {
  Chunk c;
  initChunk(&c);
  c.count = 11;
  c.capacity = 11;
  u8 code[] = {
    0, 0, 14, 0, 24, 0, 1, 24, 40, 1, 40,
  };
  int lines[] = {
    48, 48, 48, 48, 48, 48, 48, 48, 48, 49, 49,
  };
  c.code = cloneMemory(code, sizeof(code));
  c.lines = cloneMemory(lines, sizeof(lines));
  c.constants = bg_blackConstants20();

  return c;
};

static Value bg_blackFn20() {
  ObjFun *f = newFunction();  f->arity = 0;
  f->upvalueCount = 0;
  f->name = newString("bg_black");
  f->chunk = bg_blackChunk20();
  return obj(f);
}

static ValueArray bg_redConstants21() {
  ValueArray vals;
  initValueArray(&vals);
  vals.count = vals.capacity = 2;
  Value values[] = {
    str("[41m"), str("[39m"),
  };
  vals.values = cloneMemory(values, sizeof(values));
  return vals;
}

static Chunk bg_redChunk21() {
  Chunk c;
  initChunk(&c);
  c.count = 11;
  c.capacity = 11;
  u8 code[] = {
    0, 0, 14, 0, 24, 0, 1, 24, 40, 1, 40,
  };
  int lines[] = {
    49, 49, 49, 49, 49, 49, 49, 49, 49, 50, 50,
  };
  c.code = cloneMemory(code, sizeof(code));
  c.lines = cloneMemory(lines, sizeof(lines));
  c.constants = bg_redConstants21();

  return c;
};

static Value bg_redFn21() {
  ObjFun *f = newFunction();  f->arity = 0;
  f->upvalueCount = 0;
  f->name = newString("bg_red");
  f->chunk = bg_redChunk21();
  return obj(f);
}

static ValueArray bg_greenConstants22() {
  ValueArray vals;
  initValueArray(&vals);
  vals.count = vals.capacity = 2;
  Value values[] = {
    str("[42m"), str("[39m"),
  };
  vals.values = cloneMemory(values, sizeof(values));
  return vals;
}

static Chunk bg_greenChunk22() {
  Chunk c;
  initChunk(&c);
  c.count = 11;
  c.capacity = 11;
  u8 code[] = {
    0, 0, 14, 0, 24, 0, 1, 24, 40, 1, 40,
  };
  int lines[] = {
    50, 50, 50, 50, 50, 50, 50, 50, 50, 51, 51,
  };
  c.code = cloneMemory(code, sizeof(code));
  c.lines = cloneMemory(lines, sizeof(lines));
  c.constants = bg_greenConstants22();

  return c;
};

static Value bg_greenFn22() {
  ObjFun *f = newFunction();  f->arity = 0;
  f->upvalueCount = 0;
  f->name = newString("bg_green");
  f->chunk = bg_greenChunk22();
  return obj(f);
}

static ValueArray bg_yellowConstants23() {
  ValueArray vals;
  initValueArray(&vals);
  vals.count = vals.capacity = 2;
  Value values[] = {
    str("[43m"), str("[39m"),
  };
  vals.values = cloneMemory(values, sizeof(values));
  return vals;
}

static Chunk bg_yellowChunk23() {
  Chunk c;
  initChunk(&c);
  c.count = 11;
  c.capacity = 11;
  u8 code[] = {
    0, 0, 14, 0, 24, 0, 1, 24, 40, 1, 40,
  };
  int lines[] = {
    51, 51, 51, 51, 51, 51, 51, 51, 51, 52, 52,
  };
  c.code = cloneMemory(code, sizeof(code));
  c.lines = cloneMemory(lines, sizeof(lines));
  c.constants = bg_yellowConstants23();

  return c;
};

static Value bg_yellowFn23() {
  ObjFun *f = newFunction();  f->arity = 0;
  f->upvalueCount = 0;
  f->name = newString("bg_yellow");
  f->chunk = bg_yellowChunk23();
  return obj(f);
}

static ValueArray bg_blueConstants24() {
  ValueArray vals;
  initValueArray(&vals);
  vals.count = vals.capacity = 2;
  Value values[] = {
    str("[44m"), str("[39m"),
  };
  vals.values = cloneMemory(values, sizeof(values));
  return vals;
}

static Chunk bg_blueChunk24() {
  Chunk c;
  initChunk(&c);
  c.count = 11;
  c.capacity = 11;
  u8 code[] = {
    0, 0, 14, 0, 24, 0, 1, 24, 40, 1, 40,
  };
  int lines[] = {
    52, 52, 52, 52, 52, 52, 52, 52, 52, 53, 53,
  };
  c.code = cloneMemory(code, sizeof(code));
  c.lines = cloneMemory(lines, sizeof(lines));
  c.constants = bg_blueConstants24();

  return c;
};

static Value bg_blueFn24() {
  ObjFun *f = newFunction();  f->arity = 0;
  f->upvalueCount = 0;
  f->name = newString("bg_blue");
  f->chunk = bg_blueChunk24();
  return obj(f);
}

static ValueArray bg_magentaConstants25() {
  ValueArray vals;
  initValueArray(&vals);
  vals.count = vals.capacity = 2;
  Value values[] = {
    str("[45m"), str("[39m"),
  };
  vals.values = cloneMemory(values, sizeof(values));
  return vals;
}

static Chunk bg_magentaChunk25() {
  Chunk c;
  initChunk(&c);
  c.count = 11;
  c.capacity = 11;
  u8 code[] = {
    0, 0, 14, 0, 24, 0, 1, 24, 40, 1, 40,
  };
  int lines[] = {
    53, 53, 53, 53, 53, 53, 53, 53, 53, 54, 54,
  };
  c.code = cloneMemory(code, sizeof(code));
  c.lines = cloneMemory(lines, sizeof(lines));
  c.constants = bg_magentaConstants25();

  return c;
};

static Value bg_magentaFn25() {
  ObjFun *f = newFunction();  f->arity = 0;
  f->upvalueCount = 0;
  f->name = newString("bg_magenta");
  f->chunk = bg_magentaChunk25();
  return obj(f);
}

static ValueArray bg_cyanConstants26() {
  ValueArray vals;
  initValueArray(&vals);
  vals.count = vals.capacity = 2;
  Value values[] = {
    str("[46m"), str("[39m"),
  };
  vals.values = cloneMemory(values, sizeof(values));
  return vals;
}

static Chunk bg_cyanChunk26() {
  Chunk c;
  initChunk(&c);
  c.count = 11;
  c.capacity = 11;
  u8 code[] = {
    0, 0, 14, 0, 24, 0, 1, 24, 40, 1, 40,
  };
  int lines[] = {
    54, 54, 54, 54, 54, 54, 54, 54, 54, 55, 55,
  };
  c.code = cloneMemory(code, sizeof(code));
  c.lines = cloneMemory(lines, sizeof(lines));
  c.constants = bg_cyanConstants26();

  return c;
};

static Value bg_cyanFn26() {
  ObjFun *f = newFunction();  f->arity = 0;
  f->upvalueCount = 0;
  f->name = newString("bg_cyan");
  f->chunk = bg_cyanChunk26();
  return obj(f);
}

static ValueArray bg_whiteConstants27() {
  ValueArray vals;
  initValueArray(&vals);
  vals.count = vals.capacity = 2;
  Value values[] = {
    str("[47m"), str("[39m"),
  };
  vals.values = cloneMemory(values, sizeof(values));
  return vals;
}

static Chunk bg_whiteChunk27() {
  Chunk c;
  initChunk(&c);
  c.count = 11;
  c.capacity = 11;
  u8 code[] = {
    0, 0, 14, 0, 24, 0, 1, 24, 40, 1, 40,
  };
  int lines[] = {
    55, 55, 55, 55, 55, 55, 55, 55, 55, 57, 57,
  };
  c.code = cloneMemory(code, sizeof(code));
  c.lines = cloneMemory(lines, sizeof(lines));
  c.constants = bg_whiteConstants27();

  return c;
};

static Value bg_whiteFn27() {
  ObjFun *f = newFunction();  f->arity = 0;
  f->upvalueCount = 0;
  f->name = newString("bg_white");
  f->chunk = bg_whiteChunk27();
  return obj(f);
}

static ValueArray inspectConstants28() {
  ValueArray vals;
  initValueArray(&vals);
  vals.count = vals.capacity = 2;
  Value values[] = {
    str("{"), str("}"),
  };
  vals.values = cloneMemory(values, sizeof(values));
  return vals;
}

static Chunk inspectChunk28() {
  Chunk c;
  initChunk(&c);
  c.count = 8;
  c.capacity = 8;
  u8 code[] = {
    0, 0, 0, 1, 24, 40, 1, 40,
  };
  int lines[] = {
    59, 59, 59, 59, 59, 61, 61, 61,
  };
  c.code = cloneMemory(code, sizeof(code));
  c.lines = cloneMemory(lines, sizeof(lines));
  c.constants = inspectConstants28();

  return c;
};

static Value inspectFn28() {
  ObjFun *f = newFunction();  f->arity = 0;
  f->upvalueCount = 0;
  f->name = newString("inspect");
  f->chunk = inspectChunk28();
  return obj(f);
}

static ValueArray lib_core_solConstants0() {
  ValueArray vals;
  initValueArray(&vals);
  vals.count = vals.capacity = 70;
  Value values[] = {
    str("Nil"), str("Any"), str("Object"), str("Function"), str("Method"), str("NativeFunction"), str("Class"), str("Array"), str("eql"), eqlFn1(), str("Bool"), str("Error"), str("Number"), str("Range"), initFn2(), str("init"), str("inspect"), inspectFn3(), str("string"), stringFn4(), str("String"), str("bold"), boldFn5(), str("dim"), dimFn6(), str("italic"), italicFn7(), str("underline"), underlineFn8(), str("invert"), invertFn9(), str("hide"), hideFn10(), str("strike"), strikeFn11(), str("black"), blackFn12(), str("red"), redFn13(), str("green"), greenFn14(), str("yellow"), yellowFn15(), str("blue"), blueFn16(), str("magenta"), magentaFn17(), str("cyan"), cyanFn18(), str("white"), whiteFn19(), str("bg_black"), bg_blackFn20(), str("bg_red"), bg_redFn21(), str("bg_green"), bg_greenFn22(), str("bg_yellow"), bg_yellowFn23(), str("bg_blue"), bg_blueFn24(), str("bg_magenta"), bg_magentaFn25(), str("bg_cyan"), bg_cyanFn26(), str("bg_white"), bg_whiteFn27(), str("Table"), inspectFn28(), str("Tuple"),
  };
  vals.values = cloneMemory(values, sizeof(values));
  return vals;
}

static Chunk lib_core_solChunk0() {
  Chunk c;
  initChunk(&c);
  c.count = 282;
  c.capacity = 282;
  u8 code[] = {
    34, 0, 0, 14, 0, 44, 1, 35, 9, 1, 7, 7, 34, 2, 0, 14, 0, 44, 1, 35, 9, 1, 7, 7, 34, 3, 0, 14, 0, 44, 2, 35, 9, 1, 7, 7, 34, 4, 0, 14, 0, 44, 3, 35, 9, 1, 7, 7, 34, 5, 0, 14, 0, 44, 3, 35, 9, 1, 7, 7, 34, 6, 0, 14, 0, 44, 3, 35, 9, 1, 7, 7, 34, 7, 0, 14, 0, 44, 2, 35, 9, 1, 37, 9, 36, 8, 7, 7, 34, 10, 0, 14, 0, 44, 2, 35, 9, 1, 7, 7, 34, 11, 0, 14, 0, 44, 2, 35, 9, 1, 7, 7, 34, 12, 0, 14, 0, 44, 2, 35, 9, 1, 7, 7, 34, 13, 0, 37, 14, 36, 15, 14, 0, 44, 2, 35, 9, 1, 37, 17, 36, 16, 37, 19, 36, 18, 7, 7, 34, 20, 0, 14, 0, 44, 2, 35, 9, 1, 37, 22, 36, 21, 37, 24, 36, 23, 37, 26, 36, 25, 37, 28, 36, 27, 37, 30, 36, 29, 37, 32, 36, 31, 37, 34, 36, 33, 37, 36, 36, 35, 37, 38, 36, 37, 37, 40, 36, 39, 37, 42, 36, 41, 37, 44, 36, 43, 37, 46, 36, 45, 37, 48, 36, 47, 37, 50, 36, 49, 37, 52, 36, 51, 37, 54, 36, 53, 37, 56, 36, 55, 37, 58, 36, 57, 37, 60, 36, 59, 37, 62, 36, 61, 37, 64, 36, 63, 37, 66, 36, 65, 7, 7, 34, 67, 0, 14, 0, 44, 2, 35, 9, 1, 37, 68, 36, 16, 7, 7, 34, 69, 0, 14, 0, 44, 2, 35, 9, 1, 7, 7, 1, 40,
  };
  int lines[] = {
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 28, 28, 28, 28, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 32, 32, 32, 32, 33, 33, 33, 33, 34, 34, 34, 34, 35, 35, 35, 35, 36, 36, 36, 36, 37, 37, 37, 37, 39, 39, 39, 39, 40, 40, 40, 40, 41, 41, 41, 41, 42, 42, 42, 42, 43, 43, 43, 43, 44, 44, 44, 44, 45, 45, 45, 45, 46, 46, 46, 46, 48, 48, 48, 48, 49, 49, 49, 49, 50, 50, 50, 50, 51, 51, 51, 51, 52, 52, 52, 52, 53, 53, 53, 53, 54, 54, 54, 54, 55, 55, 55, 55, 57, 57, 57, 57, 57, 57, 57, 57, 57, 57, 57, 57, 57, 57, 57, 57, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 62, 62, 62, 62,
  };
  c.code = cloneMemory(code, sizeof(code));
  c.lines = cloneMemory(lines, sizeof(lines));
  c.constants = lib_core_solConstants0();

  return c;
};

static Value lib_core_solFn0() {
  ObjFun *f = newFunction();  f->arity = 0;
  f->upvalueCount = 0;
  f->name = newString("lib_core_sol");
  f->chunk = lib_core_solChunk0();
  return obj(f);
}

ObjFun *core_sol() {
  return AS_FUN(lib_core_solFn0());
}
