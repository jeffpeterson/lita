#include <assert.h>

#include "string.h"
#include "table.h"

#define assertGetSet(key, value)                                               \
  {                                                                            \
    Value v;                                                                   \
    tableSet(&table, key, value);                                              \
    assert(tableGet(&table, key, &v));                                         \
    assert(valuesEqual(v, value));                                             \
  }

void table_test() {
  Table table;
  initTable(&table);

  assert(table.len == 0);

  assertGetSet(number(5), number(55));
  assertGetSet(number(5), number(555));
  assert(table.len == 1);

  assertGetSet(number(5), string("55"));
  assert(table.len == 1);

  assertGetSet(string("foo"), string("bar"));
  assert(table.len == 2);
}
