#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

#include "compiler.h"
#include "dump.h"
#include "lib.h"
#include "native.h"
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
  return take_string(buffer, bytesRead);
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
  fwrite(content->chars, sizeof(char), content->length, io);
  fclose(io);
  return true;
}

void runFile(ObjString *path) {
  ObjString *source = readFile(path);
  assertOkResult(interpret(source->chars, path));
}

void compileFileToC(ObjString *path) {
  ObjString *source = readFile(path);
  ObjFunction *fun = compile(source->chars, path);

  if (fun == NULL) exit(65);

  ObjString *dst = concat_strings(path, newString(".c"));
  FILE *io = openFile(dst, "w");
  dumpModule(io, path, fun);
  fclose(io);
}

Value getEnv(Value name) {
  char *chars = asChars(name);
  if (chars[0] == '$') chars++;
  return string(getenv(chars));
}

Value read(Value path) { return obj(readFile(as_string(path))); }

NATIVE_FUNCTION(shell, 1) {
  char *str = NULL;
  usize len = 0;
  FILE *io = open_memstream(&str, &len);

  fprintf(io, "%s", asChars(args[0]));
  for (int i = 1; i < argc; i++)
    fprintf(io, " %s", escape_string(as_string(args[i]))->chars);

  fclose(io);
  return number(system(take_string(str, len)->chars));
}
NATIVE_FUNCTION(mkdir, 1) { return mkdir(as_string(args[0])->chars, 0777); }
NATIVE_FUNCTION(read, 0) {
  return OBJ_VAL(readFile(argc ? as_string(args[0]) : newString("/dev/stdin")));
}
NATIVE_FUNCTION(write, 1) {
  let path = argc == 1 ? string("/dev/stdout") : args[0];
  let content = args[argc - 1];
  if (writeFile(as_string(path), as_string(content))) return content;
  else return crash("Could not write to file.");
}
NATIVE_FUNCTION(append, 1) {
  let path = argc == 1 ? string("/dev/stdout") : args[0];
  let content = args[argc - 1];
  if (appendFile(as_string(path), as_string(content))) return content;
  else return crash("Could not append to file.");
}
NATIVE_FUNCTION(repl, 0) {
  repl();
  return nil;
}
