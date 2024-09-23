#include "test.h"
#include "value.h"

void hash_test() {
  // XXH3_64bits: 0xa3a2113ccff4e730
  assert(valueHash(number(42)) == 0x2abe9a9a9d56af92);
  assert(valueHash(number(0)) == valueHash(number(0)));
  assert(valueHash(nil) == valueHash(nil));
}
