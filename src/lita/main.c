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

static void usage(int argc, char *argv[]) {
  printf(
      "Usage:\n"
      "  %s [options] [file] [...args]\n"
      "\n"
      "Options:\n"
      "  -i \t\tInterpret the source file.\n"
      "  -r \t\tStart the REPL.\n"
      "  -t \t\tEnable some tracing logs.\n"
      "  -e <code> \tEvaluate the given code.\n"
      "  -d \t\tEnable debug output on errors.\n"
      "  -dd \t\tShow VM stack between REPL lines.\n"
      "  -ddd \t\tShow VM state between each executed op-code.\n"
      "  -dddd \tShow debug info as each token is parsed.\n"
      "  -c \t\tCompile the source file to C. Used to bootstrap compilation.\n"
      "  -h \t\tPrint this help.\n",
      argv[0]);
}

int main(int argc, char *argv[]) {
  World *world = ecs_init_w_args(argc, argv);

  initVM(world);
  assertOkResult(bootVM());

  // ECS_IMPORT(world, FlecsRest);
  // ecs_set(world, EcsWorld, EcsRest, {.ipaddr = "127.0.0.1"});

  // return ecs_app_run(world, &(ecs_app_desc_t){
  //                               .enable_stats = true,
  //                               .target_fps = 240,
  //                           });

  int opt;
  bool start_repl = false;
  enum { COMPILE, INTERPRET } mode = INTERPRET;

  while ((opt = getopt(argc, argv, "hcirtde:")) != -1) {
    switch (opt) {
    case 'c': mode = COMPILE; break;
    case 'i': mode = INTERPRET; break;
    case 'r': start_repl = true; break;
    case 't': config.tracing = true; break;
    case 'd': config.debug++; break;
    case 'e': assertOkResult(interpret(optarg, newString("-e"))); break;
    case 'h': usage(argc, argv); exit(0);
    case '?': usage(argc, argv); exit(1);
    }
  }

  ObjArray *args = new_array();
  ObjString *path = NULL;

  switch (mode) {
  case COMPILE:
    for (int i = optind; i < argc; i++) compileFile(newString(argv[i]));
    break;

  case INTERPRET: {
    if (optind < argc) {
      path = newString(argv[optind]);

      for (int i = optind + 1; i < argc; i++) {
        let arg = string(argv[i]);
        append_array(args, arg);
        setGlobal(OBJ_VAL(stringf("$%d", i - optind)), arg);
      }

      setGlobal(string("$0"), OBJ_VAL(path));
      setGlobal(string("ARGV"), OBJ_VAL(args));

      runFile(path);
    } else repl();
  }
  }

  if (start_repl) repl();

  freeVM();
  return 0;
}
