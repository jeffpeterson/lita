#include <assert.h>

#include "tree.h"

void tree_test() {
  Value v;
  Tree a;
  initTree(&a);

  assert(a.count == 0);

  assert(!treeGet(&a, number(5), &v));

  assert(treeSet(&a, number(5), number(55)));
  assert(treeGet(&a, number(5), &v));
  assert(as_num(v) == 55);
  assert(a.count == 1);

  assert(!treeSet(&a, number(5), number(555)));
  assert(treeGet(&a, number(5), &v));
  assert(as_num(v) == 555);
  assert(a.count == 1);

  // assert(treeSet(&a, num(6), num(66)));
  // assert(treeGet(&a, num(6), &v));
  // assert(v == num(66));
  // assert(a.count == 2);
}
