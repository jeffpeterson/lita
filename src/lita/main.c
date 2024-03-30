#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "chunk.h"
#include "common.h"
#include "debug.h"
#include "string.h"
#include "system.h"
#include "vm.h"

static void repl() {
  ObjString *name = new_string("REPL");
  char line[1024];
  for (;;) {
    printf("> ");

    if (!fgets(line, sizeof(line), stdin)) {
      printf("\n");
      break;
    }

    interpret(line, name);
  }
}

int main(int argc, char *argv[]) {
  initVM();

  int opt;
  bool startRepl = false;
  enum { COMPILE, INTERPRET } mode = INTERPRET;

  while ((opt = getopt(argc, argv, "cire:")) != -1) {
    switch (opt) {
    case 'c': mode = COMPILE; break;
    case 'i': mode = INTERPRET; break;
    case 'r': startRepl = true; break;
    case 'e': assertOkResult(interpret(optarg, new_string("eval flag"))); break;
    case '?': exit(1);
    }
  }

  bool noFiles = optind >= argc;

  if (mode == INTERPRET) assertOkResult(bootVM());

  for (int i = optind; i < argc; i++) {
    ObjString *path = new_string(argv[i]);

    if (mode == INTERPRET) {
      runFile(path);
    }

    if (mode == COMPILE) compileFile(path);
  }

  if (startRepl || noFiles) repl();

  freeVM();
  return 0;
}
