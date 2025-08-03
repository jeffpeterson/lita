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

static void swapValues(Value *a, Value *b) {
  let temp = *a;
  *a = *b;
  *b = temp;
}

static u64 count(ObjTree *tree) { return tree ? tree->count : 0; }

static u64 recount(ObjTree *tree) {
  if (isVoid(tree->key)) return 0;
  return tree->count = count(tree->left) + 1 + count(tree->right);
}

static bool rotateLeft(ObjTree *root) {
  if (!root->right) return false;
  ObjTree *pivot = root->right;

  swapValues(&pivot->key, &root->key);

  root->right = pivot->right;
  pivot->right = pivot->left;
  pivot->left = root->left;
  root->left = pivot;
  recount(pivot);
  recount(root);
  return true;
}

static bool rotateRight(ObjTree *root) {
  if (!root->left) return false;
  ObjTree *pivot = root->left;

  swapValues(&pivot->key, &root->key);

  root->left = pivot->left;
  pivot->left = pivot->right;
  pivot->right = root->right;
  root->right = pivot;
  recount(pivot);
  recount(root);
  return true;
}

/** Returns true if balancing took place. */
static bool balance(ObjTree *tree) {
  u64 left = count(tree->left), right = count(tree->right);

  if (left > right + 1) return rotateRight(tree);
  else if (right > left + 1) return rotateLeft(tree);
  return false;
}

bool nodeAdd(ObjTree **node_p, Value key) {
  ObjTree *tree = *node_p;

  if (!tree) {
    *node_p = newTree(key);
    return true;
  }

  int cmp = cmpValues(key, tree->key);
  if (cmp == 0) return false;
  if (nodeAdd(cmp < 0 ? &tree->left : &tree->right, key)) {
    recount(tree);
    balance(tree);
    return true;
  }
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
         fprintf(io, "\n%*s(%" PRId64 ") ", depth, "", tree->count) +
         inspectValue(io, tree->key, depth) +
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
