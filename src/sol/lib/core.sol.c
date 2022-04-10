// clang-format off
// sol -c lib/core.sol
#include "sol/chunk.h"
#include "sol/common.h"
#include "sol/lib.h"
#include "sol/memory.h"
#include "sol/string.h"

static ValueArray initConstants1() {
  ValueArray vals;
  initValueArray(&vals);
  vals.count = vals.capacity = 2;
  Value values[] = {
    str("start"), str("end"),
  };
  vals.values = cloneMemory(values, sizeof(values));
  return vals;
}

static Chunk initChunk1() {
  Chunk c;
  initChunk(&c);
  c.count = 17;
  c.capacity = 17;
  u8 code[] = {
    14, 0, 14, 1, 17, 0, 7, 14, 0, 14, 2, 17, 1, 7, 14, 0, 40,
  };
  int lines[] = {
    18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18,
  };
  c.code = cloneMemory(code, sizeof(code));
  c.lines = cloneMemory(lines, sizeof(lines));
  c.constants = initConstants1();

  return c;
};

static Value initFn1() {
  ObjFun *f = newFunction();  f->arity = 2;
  f->upvalueCount = 0;
  f->name = newString("init");
  f->chunk = initChunk1();
  return obj(f);
}

static ValueArray inspectConstants2() {
  ValueArray vals;
  initValueArray(&vals);
  vals.count = vals.capacity = 4;
  Value values[] = {
    str("start"), str("inspect"), str(".."), str("end"),
  };
  vals.values = cloneMemory(values, sizeof(values));
  return vals;
}

static Chunk inspectChunk2() {
  Chunk c;
  initChunk(&c);
  c.count = 19;
  c.capacity = 19;
  u8 code[] = {
    14, 0, 16, 0, 16, 1, 0, 2, 24, 14, 0, 16, 3, 16, 1, 24, 40, 1, 40,
  };
  int lines[] = {
    20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 22, 22, 22,
  };
  c.code = cloneMemory(code, sizeof(code));
  c.lines = cloneMemory(lines, sizeof(lines));
  c.constants = inspectConstants2();

  return c;
};

static Value inspectFn2() {
  ObjFun *f = newFunction();  f->arity = 0;
  f->upvalueCount = 0;
  f->name = newString("inspect");
  f->chunk = inspectChunk2();
  return obj(f);
}

static ValueArray stringConstants3() {
  ValueArray vals;
  initValueArray(&vals);
  vals.count = vals.capacity = 4;
  Value values[] = {
    str("start"), str("string"), str(".."), str("end"),
  };
  vals.values = cloneMemory(values, sizeof(values));
  return vals;
}

static Chunk stringChunk3() {
  Chunk c;
  initChunk(&c);
  c.count = 19;
  c.capacity = 19;
  u8 code[] = {
    14, 0, 16, 0, 16, 1, 0, 2, 24, 14, 0, 16, 3, 16, 1, 24, 40, 1, 40,
  };
  int lines[] = {
    23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 25, 25, 25,
  };
  c.code = cloneMemory(code, sizeof(code));
  c.lines = cloneMemory(lines, sizeof(lines));
  c.constants = stringConstants3();

  return c;
};

static Value stringFn3() {
  ObjFun *f = newFunction();  f->arity = 0;
  f->upvalueCount = 0;
  f->name = newString("string");
  f->chunk = stringChunk3();
  return obj(f);
}

static ValueArray boldConstants4() {
  ValueArray vals;
  initValueArray(&vals);
  vals.count = vals.capacity = 2;
  Value values[] = {
    str("[1m"), str("[21m"),
  };
  vals.values = cloneMemory(values, sizeof(values));
  return vals;
}

static Chunk boldChunk4() {
  Chunk c;
  initChunk(&c);
  c.count = 11;
  c.capacity = 11;
  u8 code[] = {
    0, 0, 14, 0, 24, 0, 1, 24, 40, 1, 40,
  };
  int lines[] = {
    26, 26, 26, 26, 26, 26, 26, 26, 26, 27, 27,
  };
  c.code = cloneMemory(code, sizeof(code));
  c.lines = cloneMemory(lines, sizeof(lines));
  c.constants = boldConstants4();

  return c;
};

static Value boldFn4() {
  ObjFun *f = newFunction();  f->arity = 0;
  f->upvalueCount = 0;
  f->name = newString("bold");
  f->chunk = boldChunk4();
  return obj(f);
}

static ValueArray dimConstants5() {
  ValueArray vals;
  initValueArray(&vals);
  vals.count = vals.capacity = 2;
  Value values[] = {
    str("[2m"), str("[22m"),
  };
  vals.values = cloneMemory(values, sizeof(values));
  return vals;
}

static Chunk dimChunk5() {
  Chunk c;
  initChunk(&c);
  c.count = 11;
  c.capacity = 11;
  u8 code[] = {
    0, 0, 14, 0, 24, 0, 1, 24, 40, 1, 40,
  };
  int lines[] = {
    27, 27, 27, 27, 27, 27, 27, 27, 27, 28, 28,
  };
  c.code = cloneMemory(code, sizeof(code));
  c.lines = cloneMemory(lines, sizeof(lines));
  c.constants = dimConstants5();

  return c;
};

static Value dimFn5() {
  ObjFun *f = newFunction();  f->arity = 0;
  f->upvalueCount = 0;
  f->name = newString("dim");
  f->chunk = dimChunk5();
  return obj(f);
}

static ValueArray italicConstants6() {
  ValueArray vals;
  initValueArray(&vals);
  vals.count = vals.capacity = 2;
  Value values[] = {
    str("[3m"), str("[23m"),
  };
  vals.values = cloneMemory(values, sizeof(values));
  return vals;
}

static Chunk italicChunk6() {
  Chunk c;
  initChunk(&c);
  c.count = 11;
  c.capacity = 11;
  u8 code[] = {
    0, 0, 14, 0, 24, 0, 1, 24, 40, 1, 40,
  };
  int lines[] = {
    28, 28, 28, 28, 28, 28, 28, 28, 28, 29, 29,
  };
  c.code = cloneMemory(code, sizeof(code));
  c.lines = cloneMemory(lines, sizeof(lines));
  c.constants = italicConstants6();

  return c;
};

static Value italicFn6() {
  ObjFun *f = newFunction();  f->arity = 0;
  f->upvalueCount = 0;
  f->name = newString("italic");
  f->chunk = italicChunk6();
  return obj(f);
}

static ValueArray underlineConstants7() {
  ValueArray vals;
  initValueArray(&vals);
  vals.count = vals.capacity = 2;
  Value values[] = {
    str("[4m"), str("[24m"),
  };
  vals.values = cloneMemory(values, sizeof(values));
  return vals;
}

static Chunk underlineChunk7() {
  Chunk c;
  initChunk(&c);
  c.count = 11;
  c.capacity = 11;
  u8 code[] = {
    0, 0, 14, 0, 24, 0, 1, 24, 40, 1, 40,
  };
  int lines[] = {
    29, 29, 29, 29, 29, 29, 29, 29, 29, 30, 30,
  };
  c.code = cloneMemory(code, sizeof(code));
  c.lines = cloneMemory(lines, sizeof(lines));
  c.constants = underlineConstants7();

  return c;
};

static Value underlineFn7() {
  ObjFun *f = newFunction();  f->arity = 0;
  f->upvalueCount = 0;
  f->name = newString("underline");
  f->chunk = underlineChunk7();
  return obj(f);
}

static ValueArray invertConstants8() {
  ValueArray vals;
  initValueArray(&vals);
  vals.count = vals.capacity = 2;
  Value values[] = {
    str("[7m"), str("[27m"),
  };
  vals.values = cloneMemory(values, sizeof(values));
  return vals;
}

static Chunk invertChunk8() {
  Chunk c;
  initChunk(&c);
  c.count = 11;
  c.capacity = 11;
  u8 code[] = {
    0, 0, 14, 0, 24, 0, 1, 24, 40, 1, 40,
  };
  int lines[] = {
    30, 30, 30, 30, 30, 30, 30, 30, 30, 31, 31,
  };
  c.code = cloneMemory(code, sizeof(code));
  c.lines = cloneMemory(lines, sizeof(lines));
  c.constants = invertConstants8();

  return c;
};

static Value invertFn8() {
  ObjFun *f = newFunction();  f->arity = 0;
  f->upvalueCount = 0;
  f->name = newString("invert");
  f->chunk = invertChunk8();
  return obj(f);
}

static ValueArray hideConstants9() {
  ValueArray vals;
  initValueArray(&vals);
  vals.count = vals.capacity = 2;
  Value values[] = {
    str("[8m"), str("[28m"),
  };
  vals.values = cloneMemory(values, sizeof(values));
  return vals;
}

static Chunk hideChunk9() {
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
  c.constants = hideConstants9();

  return c;
};

static Value hideFn9() {
  ObjFun *f = newFunction();  f->arity = 0;
  f->upvalueCount = 0;
  f->name = newString("hide");
  f->chunk = hideChunk9();
  return obj(f);
}

static ValueArray strikeConstants10() {
  ValueArray vals;
  initValueArray(&vals);
  vals.count = vals.capacity = 2;
  Value values[] = {
    str("[9m"), str("[29m"),
  };
  vals.values = cloneMemory(values, sizeof(values));
  return vals;
}

static Chunk strikeChunk10() {
  Chunk c;
  initChunk(&c);
  c.count = 11;
  c.capacity = 11;
  u8 code[] = {
    0, 0, 14, 0, 24, 0, 1, 24, 40, 1, 40,
  };
  int lines[] = {
    32, 32, 32, 32, 32, 32, 32, 32, 32, 34, 34,
  };
  c.code = cloneMemory(code, sizeof(code));
  c.lines = cloneMemory(lines, sizeof(lines));
  c.constants = strikeConstants10();

  return c;
};

static Value strikeFn10() {
  ObjFun *f = newFunction();  f->arity = 0;
  f->upvalueCount = 0;
  f->name = newString("strike");
  f->chunk = strikeChunk10();
  return obj(f);
}

static ValueArray blackConstants11() {
  ValueArray vals;
  initValueArray(&vals);
  vals.count = vals.capacity = 2;
  Value values[] = {
    str("[30m"), str("[39m"),
  };
  vals.values = cloneMemory(values, sizeof(values));
  return vals;
}

static Chunk blackChunk11() {
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
  c.constants = blackConstants11();

  return c;
};

static Value blackFn11() {
  ObjFun *f = newFunction();  f->arity = 0;
  f->upvalueCount = 0;
  f->name = newString("black");
  f->chunk = blackChunk11();
  return obj(f);
}

static ValueArray redConstants12() {
  ValueArray vals;
  initValueArray(&vals);
  vals.count = vals.capacity = 2;
  Value values[] = {
    str("[31m"), str("[39m"),
  };
  vals.values = cloneMemory(values, sizeof(values));
  return vals;
}

static Chunk redChunk12() {
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
  c.constants = redConstants12();

  return c;
};

static Value redFn12() {
  ObjFun *f = newFunction();  f->arity = 0;
  f->upvalueCount = 0;
  f->name = newString("red");
  f->chunk = redChunk12();
  return obj(f);
}

static ValueArray greenConstants13() {
  ValueArray vals;
  initValueArray(&vals);
  vals.count = vals.capacity = 2;
  Value values[] = {
    str("[32m"), str("[39m"),
  };
  vals.values = cloneMemory(values, sizeof(values));
  return vals;
}

static Chunk greenChunk13() {
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
  c.constants = greenConstants13();

  return c;
};

static Value greenFn13() {
  ObjFun *f = newFunction();  f->arity = 0;
  f->upvalueCount = 0;
  f->name = newString("green");
  f->chunk = greenChunk13();
  return obj(f);
}

static ValueArray yellowConstants14() {
  ValueArray vals;
  initValueArray(&vals);
  vals.count = vals.capacity = 2;
  Value values[] = {
    str("[33m"), str("[39m"),
  };
  vals.values = cloneMemory(values, sizeof(values));
  return vals;
}

static Chunk yellowChunk14() {
  Chunk c;
  initChunk(&c);
  c.count = 11;
  c.capacity = 11;
  u8 code[] = {
    0, 0, 14, 0, 24, 0, 1, 24, 40, 1, 40,
  };
  int lines[] = {
    37, 37, 37, 37, 37, 37, 37, 37, 37, 38, 38,
  };
  c.code = cloneMemory(code, sizeof(code));
  c.lines = cloneMemory(lines, sizeof(lines));
  c.constants = yellowConstants14();

  return c;
};

static Value yellowFn14() {
  ObjFun *f = newFunction();  f->arity = 0;
  f->upvalueCount = 0;
  f->name = newString("yellow");
  f->chunk = yellowChunk14();
  return obj(f);
}

static ValueArray blueConstants15() {
  ValueArray vals;
  initValueArray(&vals);
  vals.count = vals.capacity = 2;
  Value values[] = {
    str("[34m"), str("[39m"),
  };
  vals.values = cloneMemory(values, sizeof(values));
  return vals;
}

static Chunk blueChunk15() {
  Chunk c;
  initChunk(&c);
  c.count = 11;
  c.capacity = 11;
  u8 code[] = {
    0, 0, 14, 0, 24, 0, 1, 24, 40, 1, 40,
  };
  int lines[] = {
    38, 38, 38, 38, 38, 38, 38, 38, 38, 39, 39,
  };
  c.code = cloneMemory(code, sizeof(code));
  c.lines = cloneMemory(lines, sizeof(lines));
  c.constants = blueConstants15();

  return c;
};

static Value blueFn15() {
  ObjFun *f = newFunction();  f->arity = 0;
  f->upvalueCount = 0;
  f->name = newString("blue");
  f->chunk = blueChunk15();
  return obj(f);
}

static ValueArray magentaConstants16() {
  ValueArray vals;
  initValueArray(&vals);
  vals.count = vals.capacity = 2;
  Value values[] = {
    str("[35m"), str("[39m"),
  };
  vals.values = cloneMemory(values, sizeof(values));
  return vals;
}

static Chunk magentaChunk16() {
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
  c.constants = magentaConstants16();

  return c;
};

static Value magentaFn16() {
  ObjFun *f = newFunction();  f->arity = 0;
  f->upvalueCount = 0;
  f->name = newString("magenta");
  f->chunk = magentaChunk16();
  return obj(f);
}

static ValueArray cyanConstants17() {
  ValueArray vals;
  initValueArray(&vals);
  vals.count = vals.capacity = 2;
  Value values[] = {
    str("[36m"), str("[39m"),
  };
  vals.values = cloneMemory(values, sizeof(values));
  return vals;
}

static Chunk cyanChunk17() {
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
  c.constants = cyanConstants17();

  return c;
};

static Value cyanFn17() {
  ObjFun *f = newFunction();  f->arity = 0;
  f->upvalueCount = 0;
  f->name = newString("cyan");
  f->chunk = cyanChunk17();
  return obj(f);
}

static ValueArray whiteConstants18() {
  ValueArray vals;
  initValueArray(&vals);
  vals.count = vals.capacity = 2;
  Value values[] = {
    str("[37m"), str("[39m"),
  };
  vals.values = cloneMemory(values, sizeof(values));
  return vals;
}

static Chunk whiteChunk18() {
  Chunk c;
  initChunk(&c);
  c.count = 11;
  c.capacity = 11;
  u8 code[] = {
    0, 0, 14, 0, 24, 0, 1, 24, 40, 1, 40,
  };
  int lines[] = {
    41, 41, 41, 41, 41, 41, 41, 41, 41, 43, 43,
  };
  c.code = cloneMemory(code, sizeof(code));
  c.lines = cloneMemory(lines, sizeof(lines));
  c.constants = whiteConstants18();

  return c;
};

static Value whiteFn18() {
  ObjFun *f = newFunction();  f->arity = 0;
  f->upvalueCount = 0;
  f->name = newString("white");
  f->chunk = whiteChunk18();
  return obj(f);
}

static ValueArray bg_blackConstants19() {
  ValueArray vals;
  initValueArray(&vals);
  vals.count = vals.capacity = 2;
  Value values[] = {
    str("[40m"), str("[39m"),
  };
  vals.values = cloneMemory(values, sizeof(values));
  return vals;
}

static Chunk bg_blackChunk19() {
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
  c.constants = bg_blackConstants19();

  return c;
};

static Value bg_blackFn19() {
  ObjFun *f = newFunction();  f->arity = 0;
  f->upvalueCount = 0;
  f->name = newString("bg_black");
  f->chunk = bg_blackChunk19();
  return obj(f);
}

static ValueArray bg_redConstants20() {
  ValueArray vals;
  initValueArray(&vals);
  vals.count = vals.capacity = 2;
  Value values[] = {
    str("[41m"), str("[39m"),
  };
  vals.values = cloneMemory(values, sizeof(values));
  return vals;
}

static Chunk bg_redChunk20() {
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
  c.constants = bg_redConstants20();

  return c;
};

static Value bg_redFn20() {
  ObjFun *f = newFunction();  f->arity = 0;
  f->upvalueCount = 0;
  f->name = newString("bg_red");
  f->chunk = bg_redChunk20();
  return obj(f);
}

static ValueArray bg_greenConstants21() {
  ValueArray vals;
  initValueArray(&vals);
  vals.count = vals.capacity = 2;
  Value values[] = {
    str("[42m"), str("[39m"),
  };
  vals.values = cloneMemory(values, sizeof(values));
  return vals;
}

static Chunk bg_greenChunk21() {
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
  c.constants = bg_greenConstants21();

  return c;
};

static Value bg_greenFn21() {
  ObjFun *f = newFunction();  f->arity = 0;
  f->upvalueCount = 0;
  f->name = newString("bg_green");
  f->chunk = bg_greenChunk21();
  return obj(f);
}

static ValueArray bg_yellowConstants22() {
  ValueArray vals;
  initValueArray(&vals);
  vals.count = vals.capacity = 2;
  Value values[] = {
    str("[43m"), str("[39m"),
  };
  vals.values = cloneMemory(values, sizeof(values));
  return vals;
}

static Chunk bg_yellowChunk22() {
  Chunk c;
  initChunk(&c);
  c.count = 11;
  c.capacity = 11;
  u8 code[] = {
    0, 0, 14, 0, 24, 0, 1, 24, 40, 1, 40,
  };
  int lines[] = {
    46, 46, 46, 46, 46, 46, 46, 46, 46, 47, 47,
  };
  c.code = cloneMemory(code, sizeof(code));
  c.lines = cloneMemory(lines, sizeof(lines));
  c.constants = bg_yellowConstants22();

  return c;
};

static Value bg_yellowFn22() {
  ObjFun *f = newFunction();  f->arity = 0;
  f->upvalueCount = 0;
  f->name = newString("bg_yellow");
  f->chunk = bg_yellowChunk22();
  return obj(f);
}

static ValueArray bg_blueConstants23() {
  ValueArray vals;
  initValueArray(&vals);
  vals.count = vals.capacity = 2;
  Value values[] = {
    str("[44m"), str("[39m"),
  };
  vals.values = cloneMemory(values, sizeof(values));
  return vals;
}

static Chunk bg_blueChunk23() {
  Chunk c;
  initChunk(&c);
  c.count = 11;
  c.capacity = 11;
  u8 code[] = {
    0, 0, 14, 0, 24, 0, 1, 24, 40, 1, 40,
  };
  int lines[] = {
    47, 47, 47, 47, 47, 47, 47, 47, 47, 48, 48,
  };
  c.code = cloneMemory(code, sizeof(code));
  c.lines = cloneMemory(lines, sizeof(lines));
  c.constants = bg_blueConstants23();

  return c;
};

static Value bg_blueFn23() {
  ObjFun *f = newFunction();  f->arity = 0;
  f->upvalueCount = 0;
  f->name = newString("bg_blue");
  f->chunk = bg_blueChunk23();
  return obj(f);
}

static ValueArray bg_magentaConstants24() {
  ValueArray vals;
  initValueArray(&vals);
  vals.count = vals.capacity = 2;
  Value values[] = {
    str("[45m"), str("[39m"),
  };
  vals.values = cloneMemory(values, sizeof(values));
  return vals;
}

static Chunk bg_magentaChunk24() {
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
  c.constants = bg_magentaConstants24();

  return c;
};

static Value bg_magentaFn24() {
  ObjFun *f = newFunction();  f->arity = 0;
  f->upvalueCount = 0;
  f->name = newString("bg_magenta");
  f->chunk = bg_magentaChunk24();
  return obj(f);
}

static ValueArray bg_cyanConstants25() {
  ValueArray vals;
  initValueArray(&vals);
  vals.count = vals.capacity = 2;
  Value values[] = {
    str("[46m"), str("[39m"),
  };
  vals.values = cloneMemory(values, sizeof(values));
  return vals;
}

static Chunk bg_cyanChunk25() {
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
  c.constants = bg_cyanConstants25();

  return c;
};

static Value bg_cyanFn25() {
  ObjFun *f = newFunction();  f->arity = 0;
  f->upvalueCount = 0;
  f->name = newString("bg_cyan");
  f->chunk = bg_cyanChunk25();
  return obj(f);
}

static ValueArray bg_whiteConstants26() {
  ValueArray vals;
  initValueArray(&vals);
  vals.count = vals.capacity = 2;
  Value values[] = {
    str("[47m"), str("[39m"),
  };
  vals.values = cloneMemory(values, sizeof(values));
  return vals;
}

static Chunk bg_whiteChunk26() {
  Chunk c;
  initChunk(&c);
  c.count = 11;
  c.capacity = 11;
  u8 code[] = {
    0, 0, 14, 0, 24, 0, 1, 24, 40, 1, 40,
  };
  int lines[] = {
    50, 50, 50, 50, 50, 50, 50, 50, 50, 52, 52,
  };
  c.code = cloneMemory(code, sizeof(code));
  c.lines = cloneMemory(lines, sizeof(lines));
  c.constants = bg_whiteConstants26();

  return c;
};

static Value bg_whiteFn26() {
  ObjFun *f = newFunction();  f->arity = 0;
  f->upvalueCount = 0;
  f->name = newString("bg_white");
  f->chunk = bg_whiteChunk26();
  return obj(f);
}

static ValueArray inspectConstants27() {
  ValueArray vals;
  initValueArray(&vals);
  vals.count = vals.capacity = 2;
  Value values[] = {
    str("{"), str("}"),
  };
  vals.values = cloneMemory(values, sizeof(values));
  return vals;
}

static Chunk inspectChunk27() {
  Chunk c;
  initChunk(&c);
  c.count = 8;
  c.capacity = 8;
  u8 code[] = {
    0, 0, 0, 1, 24, 40, 1, 40,
  };
  int lines[] = {
    54, 54, 54, 54, 54, 56, 56, 56,
  };
  c.code = cloneMemory(code, sizeof(code));
  c.lines = cloneMemory(lines, sizeof(lines));
  c.constants = inspectConstants27();

  return c;
};

static Value inspectFn27() {
  ObjFun *f = newFunction();  f->arity = 0;
  f->upvalueCount = 0;
  f->name = newString("inspect");
  f->chunk = inspectChunk27();
  return obj(f);
}

static ValueArray _script_Constants0() {
  ValueArray vals;
  initValueArray(&vals);
  vals.count = vals.capacity = 67;
  Value values[] = {
    str("Nil"), str("Any"), str("Object"), str("Function"), str("Method"), str("NativeFunction"), str("Class"), str("Bool"), str("Error"), str("Number"), str("Range"), initFn1(), str("init"), str("inspect"), inspectFn2(), str("string"), stringFn3(), str("String"), str("bold"), boldFn4(), str("dim"), dimFn5(), str("italic"), italicFn6(), str("underline"), underlineFn7(), str("invert"), invertFn8(), str("hide"), hideFn9(), str("strike"), strikeFn10(), str("black"), blackFn11(), str("red"), redFn12(), str("green"), greenFn13(), str("yellow"), yellowFn14(), str("blue"), blueFn15(), str("magenta"), magentaFn16(), str("cyan"), cyanFn17(), str("white"), whiteFn18(), str("bg_black"), bg_blackFn19(), str("bg_red"), bg_redFn20(), str("bg_green"), bg_greenFn21(), str("bg_yellow"), bg_yellowFn22(), str("bg_blue"), bg_blueFn23(), str("bg_magenta"), bg_magentaFn24(), str("bg_cyan"), bg_cyanFn25(), str("bg_white"), bg_whiteFn26(), str("Table"), inspectFn27(), str("Tuple"),
  };
  vals.values = cloneMemory(values, sizeof(values));
  return vals;
}

static Chunk _script_Chunk0() {
  Chunk c;
  initChunk(&c);
  c.count = 240;
  c.capacity = 240;
  u8 code[] = {
    34, 0, 0, 12, 1, 35, 9, 1, 7, 7, 34, 2, 0, 12, 1, 35, 9, 1, 7, 7, 34, 3, 0, 12, 2, 35, 9, 1, 7, 7, 34, 4, 0, 12, 3, 35, 9, 1, 7, 7, 34, 5, 0, 12, 3, 35, 9, 1, 7, 7, 34, 6, 0, 12, 3, 35, 9, 1, 7, 7, 34, 7, 0, 12, 2, 35, 9, 1, 7, 7, 34, 8, 0, 12, 2, 35, 9, 1, 7, 7, 34, 9, 0, 12, 2, 35, 9, 1, 7, 7, 34, 10, 0, 37, 11, 36, 12, 12, 2, 35, 9, 1, 37, 14, 36, 13, 37, 16, 36, 15, 7, 7, 34, 17, 0, 12, 2, 35, 9, 1, 37, 19, 36, 18, 37, 21, 36, 20, 37, 23, 36, 22, 37, 25, 36, 24, 37, 27, 36, 26, 37, 29, 36, 28, 37, 31, 36, 30, 37, 33, 36, 32, 37, 35, 36, 34, 37, 37, 36, 36, 37, 39, 36, 38, 37, 41, 36, 40, 37, 43, 36, 42, 37, 45, 36, 44, 37, 47, 36, 46, 37, 49, 36, 48, 37, 51, 36, 50, 37, 53, 36, 52, 37, 55, 36, 54, 37, 57, 36, 56, 37, 59, 36, 58, 37, 61, 36, 60, 37, 63, 36, 62, 7, 7, 34, 64, 0, 12, 2, 35, 9, 1, 37, 65, 36, 13, 7, 7, 34, 66, 0, 12, 2, 35, 9, 1, 7, 7, 1, 40,
  };
  int lines[] = {
    1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 22, 22, 22, 22, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 27, 27, 27, 27, 28, 28, 28, 28, 29, 29, 29, 29, 30, 30, 30, 30, 31, 31, 31, 31, 32, 32, 32, 32, 34, 34, 34, 34, 35, 35, 35, 35, 36, 36, 36, 36, 37, 37, 37, 37, 38, 38, 38, 38, 39, 39, 39, 39, 40, 40, 40, 40, 41, 41, 41, 41, 43, 43, 43, 43, 44, 44, 44, 44, 45, 45, 45, 45, 46, 46, 46, 46, 47, 47, 47, 47, 48, 48, 48, 48, 49, 49, 49, 49, 50, 50, 50, 50, 52, 52, 52, 52, 52, 52, 52, 52, 52, 52, 52, 52, 52, 52, 56, 56, 56, 56, 56, 56, 56, 56, 56, 56, 56, 56, 56, 56, 57, 57, 57, 57,
  };
  c.code = cloneMemory(code, sizeof(code));
  c.lines = cloneMemory(lines, sizeof(lines));
  c.constants = _script_Constants0();

  return c;
};

static Value _script_Fn0() {
  ObjFun *f = newFunction();  f->arity = 0;
  f->upvalueCount = 0;
  f->name = newString("_script_");
  f->chunk = _script_Chunk0();
  return obj(f);
}

ObjFun *core_sol() {
  return AS_FUN(_script_Fn0());
}
