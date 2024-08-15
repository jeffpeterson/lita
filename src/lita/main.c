#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "array.h"
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
  bool start_repl = false;
  enum { COMPILE, INTERPRET } mode = INTERPRET;

  while ((opt = getopt(argc, argv, "cirte:")) != -1) {
    switch (opt) {
    case 'c': mode = COMPILE; break;
    case 'i': mode = INTERPRET; break;
    case 'r': start_repl = true; break;
    case 't': config.tracing = true; break;
    case 'e': assertOkResult(interpret(optarg, new_string("eval flag"))); break;
    case '?': exit(1);
    }
  }

  assertOkResult(bootVM());

  ObjArray *args = new_array();
  ObjString *path;

  switch (mode) {
  case COMPILE:
    for (int i = optind; i < argc; i++) compileFile(new_string(argv[i]));
    break;

  case INTERPRET: {
    if (optind < argc) {
      path = new_string(argv[optind]);

      for (int i = optind + 1; i < argc; i++)
        append_array(args, string(argv[i]));

      setGlobal(string("ARGV"), OBJ_VAL(args));

      runFile(path);
    }
  }
  }

  if (start_repl || !path) repl();

  freeVM();
  return 0;
}
