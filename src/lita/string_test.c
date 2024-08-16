#include <assert.h>

#include "lib.h"
#include "string.h"
#include "term.h"

#define assert_equal(a, b) assert(valuesEqual(a, b))
#define inspected(s) FG_GREEN #s FG_DEFAULT

void string_test() {
  assert_equal(OBJ_VAL(concat_strings(new_string("abc"), new_string("def"))),
               string("abcdef"));

  assert_equal(obj(string_format("abc{{}")), string("abc{}"));

  assert_equal(obj(string_format("hi {}", string("there"))),
               string("hi " inspected("there")));

  assert_equal(
      obj(string_format("Hi there {} and {}.", string("Bob"), string("Alice"))),
      string("Hi there " inspected("Bob") " and " inspected("Alice") "."));
}
