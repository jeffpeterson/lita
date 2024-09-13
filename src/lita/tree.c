#include "tree.h"
#include "memory.h"

void initTree(Tree *tree) {
  tree->count = 0;
  tree->key = VOID_VAL;
  tree->value = NIL_VAL;
  tree->left = NULL;
  tree->right = NULL;
}

bool treeGet(Tree *tree, Value key, Value *value) {
  if (tree == NULL) return false;

  if (isVoid(tree->key)) return false;

  int cmp = cmpValues(key, tree->key);

  if (cmp == 0) {
    *value = tree->value;
    return true;
  }

  return treeGet(cmp < 0 ? tree->left : tree->right, key, value);
}

bool treeSet(Tree *tree, Value key, Value value) {
  if (isVoid(tree->key)) {
    tree->key = key;
    tree->value = value;
    tree->count++;
    return true; // A new key!
  }

  int cmp = cmpValues(key, tree->key);

  if (cmp == 0) {
    tree->value = value;
    return false; // Not a new key.
  }

  Tree **branch = cmp < 0 ? &tree->left : &tree->right;

  if (*branch == NULL) {
    *branch = ALLOCATE(Tree, 1);
    initTree(*branch);
  }

  if (treeSet(*branch, key, value)) {
    tree->count++;
    return true;
  } else return false;
}
