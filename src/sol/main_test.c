#include <stdio.h>

#include "vm.h"

#define run(test)                                                              \
  {                                                                            \
    printf("Test: %s\n", #test);                                               \
    test();                                                                    \
  }

void buffer_test();
void table_test();
void tree_test();
void scanner_test();

int main(int argc, const char *argv[]) {
  initVM();
  bootVM();
  printf("\n\n");
  run(buffer_test);
  run(table_test);
  run(tree_test);
  run(scanner_test);
  printf("\nTests passed.\n\n");
  freeVM();
  return 0;
}
