#include "test.h"
#include "value.h"

void value_test() {
  assert(nil == nil);
  assert(nil == NIL_VAL);
  assert(number(42) == number(42));
}
