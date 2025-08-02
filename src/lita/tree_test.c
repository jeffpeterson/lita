#include <assert.h>

#include "debug.h"
#include "string.h"
#include "tree.h"

void tree_test() {
  ObjTree *t = newTree(VOID);

  assert(t->count == 0);

  assert(!treeHas(t, number(5)));

  assert(treeAdd(t, number(5)));
  assert(t->count == 1);

  assert(treeAdd(t, number(4)));
  assert(treeAdd(t, number(0. / 0.)));  // NaN
  assert(treeAdd(t, number(1. / 0.)));  // inf
  assert(treeAdd(t, number(-1. / 0.))); // -inf
  assert(treeAdd(t, True));
  assert(treeAdd(t, False));
  assert(treeAdd(t, nil));
  assert(!treeAdd(t, VOID));
  assert(treeAdd(t, string("5")));
  assert(treeAdd(t, number(1)));

  // debugValue(obj(t));
  assert(treeGet(t, number(5)) == number(5));
}
