#include "test.h"
#include "vm.h"

#define PATH stringf("%s:L%d", __FILE__, __LINE__)
#define assertOK(code) assert(interpret(code, PATH) == INTERPRET_OK)

void vm_test() {
  assertOK("1 + 2");
  assertEqual(vm.result, number(3));

  assertOK("8 + 9\n");
  assertEqual(vm.result, number(17));

  assertOK("fn xx = 7");
  assertOK("xx()");
  assertEqual(vm.result, number(7));

  assertOK("if true: 1");
  assertOK("if false: 1 else 2");
  assertOK("if true: 1 else 2");
}
