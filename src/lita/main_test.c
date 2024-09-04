#include <stdio.h>

#include "term.h"
#include "vm.h"

#define run(test)                                                              \
  {                                                                            \
    printf("Test: %s\n", #test);                                               \
    test();                                                                    \
  }

void pcre2_test();
void xxhash_test();

void buffer_test();
void ecs_test();
void string_test();
void table_test();
void tree_test();
void scanner_test();

int main(int argc, char *argv[]) {
  World *world = ecs_init_w_args(argc, argv);

  initVM(world);
  bootVM();
  printf("\n");
  run(pcre2_test);
  run(xxhash_test);

  run(buffer_test);
  run(ecs_test);
  run(string_test);
  run(table_test);
  run(tree_test);
  run(scanner_test);
  printf(FG_GREEN "\nTests passed.\n\n" FG_DEFAULT);
  freeVM();
  ecs_fini(world);
  return 0;
}
