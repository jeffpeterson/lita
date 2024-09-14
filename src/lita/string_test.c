
#include "string.h"
#include "test.h"

#define inspected(s) green(#s)

void string_test() {
  assertEqual(OBJ_VAL(concatStrings(newString("abc"), newString("def"))),
              string("abcdef"));

  assertEqual(obj(stringFormat("abc{{}")), string("abc{}"));

  assertEqual(obj(stringFormat("hi {}", string("there"))),
              string("hi " inspected("there")));

  assertEqual(
      obj(stringFormat("Hi there {} and {}.", string("Bob"), string("Alice"))),
      string("Hi there " inspected("Bob") " and " inspected("Alice") "."));
}
