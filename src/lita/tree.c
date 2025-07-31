#include "tree.h"
#include "memory.h"

ObjTree *newTree() {
  ObjTree *tree = allocate(Tree);
  tree->count = 0;
  tree->root = NULL;
  return tree;
}

static ObjTreeNode *newNode(Value value) {
  ObjTreeNode *node = allocate(TreeNode);
  node->value = value;
  return node;
}

static ObjTreeNode *findTreeNode(ObjTree *tree, Value key) {
  ObjTreeNode *node = tree->root;

  while (node) {
    int cmp = cmpValues(key, node->value);
    if (cmp == 0) return node;
    else if (cmp < 0) node = node->left;
    else node = node->right;
  }

  return NULL;
}

bool treeHas(ObjTree *tree, Value value) {
  return findTreeNode(tree, value) != NULL;
}

Value treeGet(ObjTree *tree, Value key) {
  ObjTreeNode *node = findTreeNode(tree, key);
  return node ? node->value : VOID;
}

static bool nodeAdd(ObjTreeNode **node_p, Value key) {
  ObjTreeNode *node = *node_p;
  if (!node) {
    *node_p = newNode(key);
    return true;
  }

  int cmp = cmpValues(key, node->value);
  if (cmp == 0) return false;
  return nodeAdd(cmp < 0 ? &node->left : &node->right, key);
}

bool treeAdd(ObjTree *tree, Value key) {
  bool isNewValue = nodeAdd(&tree->root, key);
  if (isNewValue) tree->count++;
  return isNewValue;
}

static void markNode(Obj *obj) {
  ObjTreeNode *node = (ObjTreeNode *)obj;
  markObject((Obj *)node->left);
  markValue(node->value);
  markObject((Obj *)node->right);
}
static int inspectNode(Obj *obj, FILE *io, int depth) {
  ObjTreeNode *node = (ObjTreeNode *)obj;
  if (!node) return 0;

  return inspectNode((Obj *)node->left, io, depth + 1) +
         fprintf(io, "\n%*s", depth, "") +
         inspectValue(io, node->value, depth) +
         inspectNode((Obj *)node->right, io, depth + 1);
}

REGISTER_OBJECT_DEF(TreeNode);
const ObjDef TreeNode = {
    .className = "TreeNode",
    .size = sizeof(ObjTreeNode),
    .mark = markNode,
    .inspect = inspectNode,
    // .length = nodeLength,
};

static void markTree(Obj *obj) {
  ObjTree *tree = (ObjTree *)obj;
  markObject((Obj *)tree->root);
}

static int treeLength(Obj *obj) {
  ObjTree *tree = (ObjTree *)obj;
  return tree->count;
}

static int inspectTree(Obj *obj, FILE *io, int depth) {
  ObjTree *tree = (ObjTree *)obj;
  if (!tree->root) return fprintf(io, "Tree {}");
  return fprintf(io, "Tree {") + inspectNode((Obj *)tree->root, io, depth) +
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
