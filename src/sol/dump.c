#include "dump.h"
#include "lib.h"
#include "object.h"
#include "string.h"
#include "value.h"

static int currentId = 0;
Table ids;

static void dumpValue(FILE *io, Value v) {
  if (IS_NUMBER(v)) {
    fprintf(io, "num(%g)", AS_NUMBER(v));
    return;
  }

  if (IS_NIL(v)) {
    fputs("nil", io);
    return;
  }

  if (IS_VOID(v)) {
    // Not reachable.
    fputs("nil", io);
    return;
  }

  if (IS_BOOL(v)) {
    fputs(AS_BOOL(v) ? "TRUE_VAL" : "FALSE_VAL", io);
    return;
  }

  if (!IS_OBJ(v)) {
    fputs("error(\"value should be obj\")", io);
    return;
  }

  Obj *obj = AS_OBJ(v);

  switch (obj->type) {
  case OBJ_FUN: {
    Value id;
    tableGet(&ids, v, &id);
    ObjFun *fun = AS_FUN(v);
    fprintf(io, "%sFn%d()", fun->name->chars, asInt(id));
    return;
  }

  case OBJ_STRING:
    fprintf(io, "str(\"%.*s\")", AS_STRING(v)->length, AS_STRING(v)->chars);
    return;

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
  int id = currentId++;
  tableSet(&ids, obj(fun), num(id));
  ObjString *name = fun->name;
  Chunk chunk = fun->chunk;

  ValueArray values = chunk.constants;

  for (int i = 0; i < values.count; i++) {
    Value v = values.values[i];
    if (IS_FUN(v))
      dumpFn(io, AS_FUN(v));
  }

  fprintf(io,
          "static ValueArray %sConstants%d() {\n"
          "  ValueArray vals;\n"
          "  initValueArray(&vals);\n"
          "  vals.count = vals.capacity = %d;\n"
          "  vals.values = (Value[]){\n"
          "    ",
          name->chars, id, values.count);

  for (int i = 0; i < values.count; i++) {
    dumpValue(io, values.values[i]);
    fprintf(io, ", ");
  }

  fprintf(io, "  };\n"
              "  return vals;\n"
              "}\n\n");

  fprintf(io,
          "static Chunk %sChunk%d() {\n"
          "  Chunk c;\n"
          "  initChunk(&c);\n"
          "  c.count = %d;\n"
          "  c.capacity = %d;\n"
          "  c.code = (u8[]){\n"
          "    ",
          name->chars, id, chunk.count, chunk.count);

  for (int i = 0; i < chunk.count; i++) {
    fprintf(io, "%d, ", chunk.code[i]);
  }

  fprintf(io, "\n"
              "  };\n"
              "  c.lines = (int[]){\n"
              "    ");

  for (int i = 0; i < chunk.count; i++) {
    fprintf(io, "%d, ", chunk.lines[i]);
  }

  fprintf(io,
          "\n"
          "  };\n"
          "  c.constants = %sConstants%d();\n"
          "\n"
          "  return c;\n"
          "};\n\n",
          name->chars, id);

  fprintf(io,
          "static Value %sFn%d() {\n"
          "  ObjFun *f = newFunction();"
          "  f->arity = %d;\n"
          "  f->upvalueCount = %d;\n"
          "  f->name = newString(\"%s\");\n"
          "  f->chunk = %sChunk%d();\n"
          "  return obj(f);\n"
          "}\n\n",
          name->chars, id, fun->arity, fun->upvalueCount, name->chars,
          name->chars, id);

  return id;
}

void dumpModule(FILE *io, ObjString *name, ObjFun *fun) {
  initTable(&ids);

  fprintf(io, "#include \"sol/chunk.h\"\n"
              "#include \"sol/common.h\"\n"
              "#include \"sol/lib.h\"\n"
              "#include \"sol/string.h\"\n"
              "\n");

  int id = dumpFn(io, fun);

  fprintf(io,
          "ObjFun *%s() {\n"
          "  return AS_FUN(%sFn%d());\n"
          "}\n\n",
          name->chars, fun->name->chars, id);

  freeTable(&ids);
}
