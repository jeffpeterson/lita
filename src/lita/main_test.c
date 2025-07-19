#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>

#include "term.h"
#include "vm.h"

#define checkmark() fprintf(stderr, FG_GREEN "\r✔\n" FG_DEFAULT)

#define run(test)                                                              \
  {                                                                            \
    fprintf(stderr, "  %s", #test);                                            \
    test();                                                                    \
    checkmark();                                                               \
  }

void pcre2_test();
void xxhash_test();

void buffer_test();
void chunk_test();
void hash_test();
void string_test();
void table_test();
void tree_test();
void scanner_test();
void value_test();
void vm_test();

static void usage(int argc, char *argv[]) {
  printf("Usage:\n"
         "  %s [options]\n"
         "\n"
         "Options:\n"
         "  -G \t\tCollect garbage on every allocation.\n"
         "  -d \t\tEnable debug output on errors.\n"
         "  -dd \t\tShow VM stack between REPL lines.\n"
         "  -ddd \t\tShow VM state between each executed op-code.\n"
         "  -dddd \tShow debug info as each token is parsed.\n"
         "  -t \t\tEnable some tracing logs.\n"
         "  -h \t\tPrint this help.\n",
         argv[0]);
}

int main(int argc, char *argv[]) {
  int opt;
  while ((opt = getopt(argc, argv, "Gdth")) != -1) {
    switch (opt) {
    case 'G': config.stress_gc = true; break;
    case 'd': config.debug++; break;
    case 't': config.tracing = true; break;
    case 'h': usage(argc, argv); exit(0);
    case '?': usage(argc, argv); exit(1);
    }
  }

  initVM();

  fprintf(stderr, "\n");
  run(pcre2_test);
  run(xxhash_test);

  run(value_test);
  run(scanner_test);
  run(chunk_test);
  run(hash_test);

  fprintf(stderr, "  bootVM");
  bootVM();
  checkmark();

  run(buffer_test);
  run(string_test);
  run(table_test);
  run(tree_test);
  run(vm_test);
  freeVM();
  fprintf(stderr, FG_GREEN "\nTests passed.\n\n" FG_DEFAULT);
  return 0;
}
