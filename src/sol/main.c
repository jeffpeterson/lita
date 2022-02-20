#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "chunk.h"
#include "common.h"
#include "debug.h"
#include "string.h"
#include "system.h"
#include "vm.h"

static void repl() {
  char line[1024];
  for (;;) {
    printf("> ");

    if (!fgets(line, sizeof(line), stdin)) {
      printf("\n");
      break;
    }

    interpret(line);
  }
}

int main(int argc, char *argv[]) {
  initVM();

  int opt;
  bool noFiles = true;
  bool startRepl = false;
  enum { COMPILE, INTERPRET } mode = INTERPRET;

  while (optind < argc) {
    while ((opt = getopt(argc, argv, "cir")) != -1) {
      switch (opt) {
      case 'c':
        mode = COMPILE;
        break;
      case 'i':
        mode = INTERPRET;
        break;
      case 'r':
        startRepl = true;
        break;
      default:
        exit(1);
      }
    }

    noFiles = noFiles && optind >= argc;

    for (int i = optind; i < argc; i++) {
      if (argv[i][0] == '-') {
        optreset = 1;
        break;
      }

      optind = i + 1;

      ObjString *path = newString(argv[i]);

      if (mode == INTERPRET)
        runFile(path);

      if (mode == COMPILE)
        compileFile(path);
    }
  }

  if (startRepl || noFiles)
    repl();

  freeVM();
  return 0;
}
