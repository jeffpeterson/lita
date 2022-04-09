#include <assert.h>

#include "lib.h"
#include "table.h"

void table_test() {
  Value v;
  Table a;
  initTable(&a);

  assert(a.len == 0);

  assert(!tableGet(&a, num(5), &v));
  assert(tableSet(&a, num(5), num(55)));
  assert(tableGet(&a, num(5), &v));
  assert(tableHas(&a, num(5)));

  assert(v == num(55));
  assert(a.len == 1);

  assert(!tableSet(&a, num(5), num(555)));
  assert(tableGet(&a, num(5), &v));
  assert(v == num(555));
  assert(a.len == 1);

  assert(tableSet(&a, num(6), num(66)));
  assert(tableGet(&a, num(6), &v));
  assert(tableHas(&a, num(6)));
  assert(v == num(66));
  assert(a.len == 2);
}
