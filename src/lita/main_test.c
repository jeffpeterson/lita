#include <stdio.h>

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

int main(int argc, char *argv[]) {
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
