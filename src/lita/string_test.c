#include <assert.h>

#include "lib.h"
#include "string.h"

#define assert_equal(a, b) assert(valuesEqual(a, b))

void string_test() {
  ObjString *abc = new_string("abc");
  ObjString *def = new_string("def");

  assert_equal(OBJ_VAL(concat_strings(abc, def)), string("abcdef"));

  assert_equal(obj(string_format("abc{{}")), string("abc{}"));

  assert_equal(obj(string_format("ab{}", string("c"))), string("abc"));

  assert_equal(
      obj(string_format("Hi there {} and {}.", string("Bob"), string("Alice"))),
      string("Hi there Bob and Alice."));
}
