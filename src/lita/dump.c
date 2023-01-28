#include <libgen.h>

#include "dump.h"
#include "lib.h"
#include "object.h"
#include "string.h"
#include "value.h"

int currentId = 0;
Table ids;

static void dumpValue(FILE *io, Value v) {
  if (is_nil(v)) {
    fputs("nil", io);
    return;
  }

  if (is_bool(v)) {
    fputs(AS_BOOL(v) ? "TRUE_VAL" : "FALSE_VAL", io);
    return;
  }

  if (!is_obj(v)) {
    fprintf(io, "%#llx", v);
    return;
  }

  Obj *obj = AS_OBJ(v);

  switch (obj->type) {
  case OBJ_FUN: {
    Value id;
    ObjFun *fun = AS_FUN(v);

    if (tableGet(&ids, v, &id)) {
      fprintf(io, "/*%s*/fn%g()", fun->name->chars, asNum(id));
    } else {
      fprintf(io, "error(\"Could not find fn %s\")", fun->name->chars);
    }
    return;
  }

  case OBJ_STRING: {
    ObjString *str = escapeString(AS_STRING(v));
    fprintf(io, "str(%.*s)", str->length, str->chars);
    return;
  }

  case OBJ_TUPLE: {
    ObjTuple *tup = AS_TUPLE(v);
    fprintf(io, "t(%d", tup->length);
    for (int i = 0; i < tup->length; i++) {
      fprintf(io, ", ");
      dumpValue(io, tup->values[i]);
    }
    fputs(")", io);
    return;
  }

  default:
    fprintf(io, "error(\"unknown obj type: %s\")", objInfo[obj->type].inspect);
    break;
  }
}

static int dumpFn(FILE *io, ObjFun *fun) {
  Value vid;
  if (tableGet(&ids, obj(fun), &vid)) {
    return as_int(vid);
  }
  int id = currentId++;
  vid = num(id);
  tableSet(&ids, obj(fun), vid);

  ObjString *name = fun->name;
  Chunk chunk = fun->chunk;
  ValueArray values = chunk.constants;

  for (int i = 0; i < values.count; i++) {
    Value v = values.values[i];
    if (is_fun(v)) dumpFn(io, AS_FUN(v));
  }

  fprintf(io,
          "\n"
          "// %s\n"
          "static ValueArray constants%d() {\n"
          "  ValueArray vals;\n"
          "  initValueArray(&vals);\n"
          "  vals.count = vals.capacity = %d;\n"
          "  Value values[] = {",
          name->chars, id, values.count);

  if (values.count > 0) {
    fputs("\n   ", io);

    for (int i = 0; i < values.count; i++) {
      fputs(" ", io);
      dumpValue(io, values.values[i]);
      fputs(",", io);
    }
    fputs("\n  ", io);
  }

  fprintf(io, "};\n"
              "  vals.values = cloneMemory(values, sizeof(values));\n"
              "  return vals;\n"
              "}\n");

  fprintf(io,
          "\n"
          "// %s\n"
          "static Chunk chunk%d() {\n"
          "  Chunk c;\n"
          "  initChunk(&c);\n"
          "  c.count = %d;\n"
          "  c.capacity = %d;\n"
          "  u8 code[] = {\n"
          "   ",
          name->chars, id, chunk.count, chunk.count);

  for (int i = 0; i < chunk.count; i++) {
    fprintf(io, " %d,", chunk.code[i]);
  }

  fprintf(io, "\n"
              "  };\n"
              "  int lines[] = {\n"
              "   ");

  for (int i = 0; i < chunk.count; i++) {
    fprintf(io, " %d,", chunk.lines[i]);
  }

  fprintf(io,
          "\n"
          "  };\n"
          "  c.code = cloneMemory(code, sizeof(code));\n"
          "  c.lines = cloneMemory(lines, sizeof(lines));\n"
          "                // %s\n"
          "  c.constants = constants%d();\n"
          "\n"
          "  return c;\n"
          "};\n",
          name->chars, id);

  fprintf(io,
          "\n"
          "// %s\n"
          "static Value fn%d() {\n"
          "  ObjFun *f = newFunction();"
          "  f->arity = %d;\n"
          "  f->upvalueCount = %d;\n"
          "  f->name = newString(\"%s\");\n"
          "             // %s\n"
          "  f->chunk = chunk%d();\n"
          "  return obj(f);\n"
          "}\n",
          name->chars, id, fun->arity, fun->upvalueCount, name->chars,
          name->chars, id);

  return id;
}

static char *parameterize(char *str) {
  for (int i = 0; str[i] != '\0'; i++) {
    char c = str[i];
    if ((c >= '0' && c <= '9') || (c >= 'a' && c <= 'z') ||
        (c >= 'A' && c <= 'Z') || c == '_') {
    } else str[i] = '_';
  }

  return str;
}

void dumpModule(FILE *io, ObjString *path, ObjFun *fun) {
  initTable(&ids);

  ObjString *name = newString(parameterize(basename(path->chars)));

  fprintf(io,
          "// clang-format off\n"
          "// lita -c %s\n"
          "#include \"lita/chunk.h\"\n"
          "#include \"lita/common.h\"\n"
          "#include \"lita/lib.h\"\n"
          "#include \"lita/memory.h\"\n"
          "#include \"lita/string.h\"\n"
          "",
          path->chars);

  int id = dumpFn(io, fun);

  fprintf(io,
          "\n"
          "ObjFun *%s() {\n"
          "                //%s\n"
          "  return AS_FUN(fn%d());\n"
          "}\n",
          name->chars, fun->name->chars, id);

  freeTable(&ids);
}
