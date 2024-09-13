#include <assert.h>

#include "table.h"

void table_test() {
  Value v;
  Table a;
  initTable(&a);

  assert(a.len == 0);

  assert(!tableGet(&a, number(5), &v));
  assert(tableSet(&a, number(5), number(55)));
  assert(tableGet(&a, number(5), &v));
  assert(tableHas(&a, number(5)));

  assert(as_num(v) == 55);
  assert(a.len == 1);

  assert(!tableSet(&a, number(5), number(555)));
  assert(tableGet(&a, number(5), &v));
  assert(as_num(v) == 555);
  assert(a.len == 1);

  assert(tableSet(&a, number(6), number(66)));
  assert(tableGet(&a, number(6), &v));
  assert(tableHas(&a, number(6)));
  assert(as_num(v) == 66);
  assert(a.len == 2);
}
