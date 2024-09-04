#include <libgen.h>

#include "dump.h"
#include "lib.h"
#include "object.h"
#include "scanner.h"
#include "string.h"

int currentId = 0;
Table ids;

void dumpValue(FILE *io, Value v) {
  if (is_nil(v)) {
    fputs("nil", io);
    return;
  }

  if (is_bool(v)) {
    fputs(AS_BOOL(v) ? "TRUE_VAL" : "FALSE_VAL", io);
    return;
  }

  if (is_num(v)) {
    fprintf(io, "NUMBER_VAL(%f)", AS_NUMBER(v));
    return;
  }

  // if (!is_obj(v)) {
  //   fprintf(io, "%#llx", AS_NUMBER(v));
  //   return;
  // }

  Obj *obj = AS_OBJ(v);

  if (obj->def && obj->def->dump) {
    obj->def->dump(obj, io);
    return;
  }

  fprintf(io, "crash(\"object without dump: %s\")", obj->def->class_name);
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
      if (obj->def && obj->def->dump_global) obj->def->dump_global(obj, io);
      else if (isFunction(v)) dumpFn(io, asFunction(v));
    }
  }

  fprintf(io,
          "\n"
          "static ValueArray constants_%s_%d() {\n"
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
          "static Chunk chunk_%s_%d() {\n"
          "  Chunk c;\n"
          "  initChunk(&c);\n"
          "  c.count = %d;\n"
          "  c.capacity = %d;\n"
          "  u8 code[] = {\n"
          "",
          name->chars, id, chunk.count, chunk.count);

  u8 *ip = chunk.code;
  while (ip < chunk.code + chunk.count) {
    fprintf(io, "    %s,", op_info[*ip].name);
    u8 size = instructionSize(*ip++);
    for (int i = 1; i < size; i++) {
      fprintf(io, " %d,", *ip++);
    }
    fprintf(io, "\n");
  }

  fprintf(io, "  };\n"
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
          "  c.constants = constants_%s_%d();\n"
          "\n"
          "  return c;\n"
          "};\n",
          name->chars, id);

  fprintf(io,
          "\n"
          "             // %s\n"
          "static Value fn_%s_%d() {\n"
          "  ObjFunction *f = newFunction();"
          "  f->arity = %d;\n"
          "  f->upvalueCount = %d;\n"
          "  f->name = newString(\"%s\");\n"
          "  f->chunk = chunk_%s_%d();\n"
          "  return obj(f);\n"
          "}\n",
          fun->name->chars, name->chars, id, fun->arity, fun->upvalueCount,
          fun->name->chars, name->chars, id);

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
