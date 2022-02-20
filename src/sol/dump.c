#include "dump.h"
#include "object.h"
#include "value.h"

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
    fputs("error(\"not obj\")", io);
    return;
  }

  Obj *obj = AS_OBJ(v);

  switch (obj->type) {
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
    fprintf(io, "<unknown obj type: %s>", objInfo[obj->type].inspect);
    break;
  }
}

static void dumpValues(FILE *io, const char *name, ValueArray values) {
  fprintf(io,
          "ValueArray %sConstants() {\n"
          "  ValueArray vals;\n"
          "  initValueArray(&vals);\n"
          "  vals.count = vals.capacity = %d;\n"
          "  vals.values = (Value[]){\n"
          "    ",
          name, values.count);

  for (int i = 0; i < values.count; i++) {
    dumpValue(io, values.values[i]);
    fprintf(io, ", ");
  }

  fprintf(io, "  };\n"
              "  return vals;\n"
              "}\n"
              "\n");
}

void dumpChunk(FILE *io, const char *name, Chunk *chunk) {

  fprintf(io, "#include \"lib.h\"\n"
              "#include \"chunk.h\"\n"
              "#include \"common.h\"\n"
              "\n");

  dumpValues(io, name, chunk->constants);

  fprintf(io,
          "Chunk %sChunk() {\n"
          "  Chunk c;\n"
          "  c.count = %d;\n"
          "  c.capacity = %d;\n"
          "  c.code = (u8 *){\n"
          "    ",
          name, chunk->count, chunk->count);

  for (int i = 0; i < chunk->count; i++) {
    fprintf(io, "%d, ", chunk->code[i]);
  }

  fprintf(io, "\n"
              "  };\n"
              "  c.lines = (int *){\n"
              "    ");

  for (int i = 0; i < chunk->count; i++) {
    fprintf(io, "%d, ", chunk->lines[i]);
  }

  fprintf(io,
          "\n"
          "  };\n"
          "  c.constants = %sConstants();\n"
          "\n"
          "  return c;\n"
          "};\n\n",
          name);
}
