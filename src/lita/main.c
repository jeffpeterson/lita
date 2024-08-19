#include <getopt.h>
#include <readline/history.h>
#include <readline/readline.h>
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
  ObjString *history =
      concat_strings(new_string(getenv("HOME")), new_string("/.lita_history"));

  push(obj(history));
  push(obj(name));

  read_history(history->chars);
  char *line;

  while ((line = readline("lita> "))) {
    add_history(line);
    write_history(history->chars);
    interpret(line, name);
  }
  printf("\n");
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
  ObjString *path = NULL;

  switch (mode) {
  case COMPILE:
    for (int i = optind; i < argc; i++) compileFile(new_string(argv[i]));
    break;

  case INTERPRET: {
    if (optind < argc) {
      path = new_string(argv[optind]);

      for (int i = optind + 1; i < argc; i++) {
        let arg = string(argv[i]);
        append_array(args, arg);
        setGlobal(OBJ_VAL(stringf("$%d", i - optind)), arg);
      }

      setGlobal(string("$0"), OBJ_VAL(path));
      setGlobal(string("ARGV"), OBJ_VAL(args));

      runFile(path);
    }
  }
  }

  if (start_repl || !path) repl();

  freeVM();
  return 0;
}
