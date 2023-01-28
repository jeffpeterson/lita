#ifndef lita_tree_h
#define lita_tree_h

#include "common.h"
#include "value.h"

typedef struct Tree {
  int count;
  Value key;
  Value value;
  struct Tree *left;
  struct Tree *right;
} Tree;

void initTree(Tree *tree);
bool treeGet(Tree *tree, Value key, Value *value);

/** Returns whether key is new. */
bool treeSet(Tree *tree, Value key, Value value);
// bool treeDelete(Tree *tree, Value key);
// void treeAddAll(Tree *from, Tree *to);
// void treeRemoveWhite(Tree *tree);
// void markTree(Tree *tree);
// void fprintTree(FILE *io, Tree *tree);

#endif
