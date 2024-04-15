#include <assert.h>

#include "lib.h"
#include "table.h"

void string_test() {
  assert(valuesEqual(
      obj(string_format("Hi there {} and {}.", string("Bob"), string("Alice"))),
      string("Hi there Bob and Alice.")));
}
