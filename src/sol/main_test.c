#include <stdio.h>

#define run(test)                                                              \
  {                                                                            \
    printf("Test: %s\n", #test);                                               \
    test();                                                                    \
  }

void table_test();
void tree_test();
void scanner_test();

int main(int argc, const char *argv[]) {
  printf("\n\n");
  run(table_test);
  run(tree_test);
  run(scanner_test);
  printf("\nTests passed.\n\n");
  return 0;
}
