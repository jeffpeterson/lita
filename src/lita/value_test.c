#include "test.h"
#include "value.h"

void value_test() {
  assert(nil == nil);
  assert(nil == NIL_VAL);
  assert(NULL == AS_OBJ(OBJ_VAL(NULL)));
  assert(nil == OBJ_VAL(NULL));
  assert(number(42) == number(42));
}
