#include <libgen.h>

#include "dump.h"
#include "lib.h"
#include "object.h"
#include "scanner.h"
#include "string.h"

int currentId = 0;
Table ids;

int dumpValue(FILE *io, Value v) {
  if (is_nil(v)) return fputs("nil", io);
  if (is_bool(v)) return fputs(AS_BOOL(v) ? "TRUE_VAL" : "FALSE_VAL", io);
  if (is_num(v)) return fprintf(io, "NUMBER_VAL(%f)", AS_NUMBER(v));
  if (is_obj(v)) return dumpObject(io, AS_OBJ(v));

  return fprintf(io, "crash(\"Value without dump: %s\")", inspectc(v));
}

int dumpObject(FILE *io, Obj *obj) {
  if (obj->def->dump) return obj->def->dump(obj, io);
  return fprintf(io, "crash(\"object without dump: %s\")",
                 inspectc(OBJ_VAL(obj)));
}

bool id_for(let v, int *id) {
  let vid;
  if (tableGet(&ids, v, &vid)) {
    *id = as_int(vid);
    return true;
  }

  *id = currentId++;
  tableSet(&ids, v, num(*id));
  return false;
}

static int dumpFn(FILE *io, ObjFunction *fun) {
  int id;
  if (id_for(obj(fun), &id)) return id;

  ObjString *name = string_to_c_ident(fun->name);
  Chunk chunk = fun->chunk;
  ValueArray values = chunk.constants;

  for (int i = 0; i < values.count; i++) {
    Value v = values.values[i];

    if (is_obj(v)) {
      Obj *obj = AS_OBJ(v);
      if (obj->def->dump_global) obj->def->dump_global(obj, io);
      else if (isFunction(v)) dumpFn(io, asFunction(v));
    }
  }

  fprintf(io,
          "\n"
          "             // %s\n"
          "static Value fn_%s_%d() {\n"
          "  ObjFunction *f = newFunction();\n"
          "  f->arity = %d;\n"
          "  f->upvalueCount = %d;\n"
          "  f->name = newString(\"%s\");\n",
          fun->name->chars, name->chars, id, fun->arity, fun->upvalueCount,
          fun->name->chars);

  fprintf(io,
          "\n"
          "  Chunk *c = &f->chunk;\n"
          "  initChunk(c);\n"
          "  c->count = c->capacity = %d;\n"
          "  u8 code[] = {\n",
          chunk.count);

  u8 *ip = chunk.code;
  while (ip < chunk.code + chunk.count) {
    fprintf(io, "    %s,", op_info[*ip].name);
    u8 size = instructionSize(*ip++);
    for (int i = 1; i < size; i++) fprintf(io, " %d,", *ip++);
    fprintf(io, "\n");
  }

  fprintf(io, "  };\n"
              "  int lines[] = {");
  for (int i = 0; i < chunk.count; i++) fprintf(io, " %d,", chunk.lines[i]);
  fprintf(io, "};\n"
              "  c->code = cloneMemory(code, sizeof(code));\n"
              "  c->lines = cloneMemory(lines, sizeof(lines));\n");

  fprintf(io,
          "\n"
          "  c->constants.count = c->constants.capacity = %d;\n"
          "  Value values[] = {\n",
          values.count);

  for (int i = 0; i < values.count; i++) {
    fputs("    ", io);
    dumpValue(io, values.values[i]);
    fputs(",\n", io);
  }

  fprintf(io, "  };\n"
              "  c->constants.values = cloneMemory(values, sizeof(values));\n");

  fprintf(io, "  return obj(f);\n"
              "}\n");

  return id;
}

static char *parameterize(char *str) {
  for (int i = 0; str[i] != '\0'; i++) {
    char c = str[i];
    if (isAlpha(c) || isDigit(c)) {
    } else str[i] = '_';
  }

  return str;
}

void dumpModule(FILE *io, ObjString *path, ObjFunction *fun) {
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
          "#include \"lita/vm.h\"\n"
          "\n"
          "#if ENABLE_REGEX\n"
          "#include \"lita/regex.h\"\n"
          "#endif\n"
          "",
          path->chars);

  int id = dumpFn(io, fun);

  fprintf(io,
          "\n"
          "ObjFunction *%s() {\n"
          "  return asFunction(fn_%s_%d());\n"
          "}\n",
          name->chars, string_to_c_ident(fun->name)->chars, id);

  freeTable(&ids);
}
