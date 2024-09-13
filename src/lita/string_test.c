#include <assert.h>

#include "string.h"
#include "term.h"

#define assert_equal(a, b) assert(valuesEqual(a, b))
#define inspected(s) FG_GREEN #s FG_DEFAULT

void string_test() {
  assert_equal(OBJ_VAL(concatStrings(newString("abc"), newString("def"))),
               string("abcdef"));

  assert_equal(obj(stringFormat("abc{{}")), string("abc{}"));

  assert_equal(obj(stringFormat("hi {}", string("there"))),
               string("hi " inspected("there")));

  assert_equal(
      obj(stringFormat("Hi there {} and {}.", string("Bob"), string("Alice"))),
      string("Hi there " inspected("Bob") " and " inspected("Alice") "."));
}
