#include "tree.h"
#include "memory.h"

ObjTree *newTree(Value key) {
  ObjTree *tree = allocate(Tree);
  tree->count = notVoid(key);
  tree->key = key;
  tree->left = NULL;
  tree->right = NULL;
  return tree;
}

static ObjTree *findNode(ObjTree *tree, Value key) {
  if (!tree) return NULL;
  int cmp = cmpValues(key, tree->key);
  if (cmp == 0) return tree;
  return findNode(cmp < 0 ? tree->left : tree->right, key);
}

bool treeHas(ObjTree *tree, Value key) { return findNode(tree, key) != NULL; }

Value treeGet(ObjTree *tree, Value key) {
  ObjTree *node = findNode(tree, key);
  return node ? node->key : VOID;
}

bool nodeAdd(ObjTree **node_p, Value key) {
  ObjTree *tree = *node_p;

  if (!tree) return *node_p = newTree(key);

  int cmp = cmpValues(key, tree->key);
  if (cmp == 0) return false;
  if (nodeAdd(cmp < 0 ? &tree->left : &tree->right, key)) return ++tree->count;
  return false;
}

bool treeAdd(ObjTree *tree, Value key) {
  if (isVoid(key)) return false;
  if (isVoid(tree->key)) {
    tree->key = key;
    tree->count++;
    return true;
  }
  return nodeAdd(&tree, key);
}

static void markTree(Obj *obj) {
  ObjTree *tree = (ObjTree *)obj;
  markObject((Obj *)tree->left);
  markValue(tree->key);
  markObject((Obj *)tree->right);
}

static int treeLength(Obj *obj) {
  ObjTree *tree = (ObjTree *)obj;
  return tree->count;
}

static int inspectNode(ObjTree *tree, FILE *io, int depth) {
  if (!tree) return 0;

  return inspectNode(tree->left, io, depth + 1) +
         fprintf(io, "\n%*s", depth, "") + inspectValue(io, tree->key, depth) +
         inspectNode(tree->right, io, depth + 1);
}

static int inspectTree(Obj *obj, FILE *io, int depth) {
  ObjTree *tree = (ObjTree *)obj;
  return fprintf(io, "Tree {") + inspectNode(tree, io, depth) +
         fprintf(io, "\n}");
}

REGISTER_OBJECT_DEF(Tree);
const ObjDef Tree = {
    .className = "Tree",
    .size = sizeof(ObjTree),
    .mark = markTree,
    .inspect = inspectTree,
    .length = treeLength,
};
