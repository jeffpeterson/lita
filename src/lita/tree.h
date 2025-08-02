#ifndef lita_tree_h
#define lita_tree_h

#include "common.h"
#include "object.h"
#include "value.h"

typedef struct ObjTree {
  Obj obj;
  Value key;
  u64 count;
  struct ObjTree *left;
  struct ObjTree *right;
} ObjTree;

ObjTree *newTree(Value key);

bool treeHas(ObjTree *tree, Value key);
Value treeGet(ObjTree *tree, Value key);
bool treeAdd(ObjTree *tree, Value key);

/** Returns whether key is new. */
// bool treeDelete(ObjTree *tree, Value key);
// void treeAddAll(ObjTree *from, ObjTree *to);
// void treeRemoveWhite(ObjTree *tree);
// void markObjTree(ObjTree *tree);
// void fprintObjTree(FILE *io, ObjTree *tree);

extern const ObjDef Tree;

#endif
