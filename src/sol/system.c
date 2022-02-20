#include <libgen.h>
#include <stdio.h>
#include <stdlib.h>

#include "compiler.h"
#include "dump.h"
#include "string.h"
#include "system.h"
#include "vm.h"

static FILE *openFile(ObjString *path, const char *mode) {
  FILE *io = fopen(path->chars, mode);
  if (io == NULL) {
    fprintf(stderr, "Could not open file \"%s\".\n", path->chars);
    exit(74);
  }

  return io;
}

ObjString *readFile(ObjString *path) {
  FILE *io = openFile(path, "r");
  fseek(io, 0L, SEEK_END);
  size_t size = ftell(io);
  rewind(io);

  char *buffer = (char *)malloc(size + 1);
  if (buffer == NULL) {
    fprintf(stderr, "Not enough memory to read \"%s\".\n", path->chars);
    exit(74);
  }

  size_t bytesRead = fread(buffer, sizeof(char), size, io);

  if (bytesRead < size) {
    fprintf(stderr, "Could not read file \"%s\".\n", path->chars);
    exit(74);
  }

  buffer[bytesRead] = '\0';

  fclose(io);
  return newString(buffer);
}

bool writeFile(ObjString *path, ObjString *content) {
  FILE *io = openFile(path, "w");
  fprintf(io, "%s", content->chars);
  fclose(io);
  return true;
  // usize len = fwrite(content, sizeof(char), content->length, io);
  // return len == content->length;
}

bool appendFile(ObjString *path, ObjString *content) {
  FILE *io = openFile(path, "a");
  // usize len = fwrite(content, sizeof(char), content->length, io);
  // return len == content->length;
  fprintf(io, "%s", content->chars);
  fclose(io);
  return true;
}

void runFile(ObjString *path) {
  ObjString *source = readFile(path);
  InterpretResult result = interpret(source->chars);

  if (result == INTERPRET_COMPILE_ERROR)
    exit(65);

  if (result == INTERPRET_RUNTIME_ERROR)
    exit(70);
}

static char *parameterize(char *str) {
  for (int i = 0; str[i] != '\0'; i++) {
    char c = str[i];
    if ((c >= '0' && c <= '9') || (c >= 'a' && c <= 'z') ||
        (c >= 'A' && c <= 'Z') || c == '_') {
    } else
      str[i] = '_';
  }

  return str;
}

void compileFile(ObjString *path) {
  ObjString *source = readFile(path);
  ObjFun *fun = compile(source->chars);

  if (fun == NULL)
    exit(65);

  ObjString *name = newString(parameterize(basename(path->chars)));
  ObjString *dst = concatStrings(path, newString(".c"));
  FILE *io = openFile(dst, "w");
  dumpModule(io, name, fun);
  fclose(io);
}
