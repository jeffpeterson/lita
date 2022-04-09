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
  assertOkResult(interpret(source->chars));
}

void compileFile(ObjString *path) {
  ObjString *source = readFile(path);
  ObjFun *fun = compile(source->chars);

  if (fun == NULL)
    exit(65);

  ObjString *dst = concatStrings(path, newString(".c"));
  FILE *io = openFile(dst, "w");
  dumpModule(io, path, fun);
  fclose(io);
}
