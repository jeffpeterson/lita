#include <assert.h>

#include "atom.h"
#include "dump.h"
#include "iterator.h"
#include "lib.h"
#include "memory.h"
#include "native.h"
#include "vm.h"

/**
 * Allocate an ObjAtom for a series of values.
 */
static ObjAtom *makeAtom(Value *vals, int length, Hash hash) {
  ObjAtom *atom = allocateAtom();
  initTable(atom->values);
  for (int i = 0; i < length; i++) {
    tableSet(atom->values, classOf(vals[i]), vals[i]);
  }
  atom->obj.hash = hash;
  intern(OBJ_VAL(atom));
  return atom;
}

ObjAtom *copy_atom(Value *values, uint8_t length) {
  int size = length * sizeof(Value);
  Hash hash;
  ObjAtom *interned = (ObjAtom *)getInterned(&hash, (char *)values, size);

  if (interned != NULL) return interned;

  Value *heapVals = ALLOCATE(Value, length);
  memcpy(heapVals, values, size);

  return makeAtom(heapVals, length, hash);
}

ObjAtom *take_atom(Value *values, uint8_t length) {
  Hash hash;
  Obj *interned = getInterned(&hash, (char *)values, length * sizeof(Entry));

  if (interned != NULL) {
    FREE_ARRAY(Value, values, length);
    return (ObjAtom *)interned;
  }

  return makeAtom(values, length, hash);
}

// # Natives

NATIVE_METHOD(Atom, get, 1) {
  ObjAtom *atom = asAtom(this);
  let val;
  tableGet(atom->values, args[0], &val);
  return val;
}

static void freeAtom(Obj *obj) {
  ObjAtom *atom = (ObjAtom *)obj;
  freeTable(atom->values);
}

static void markAtom(Obj *obj) {
  ObjAtom *atom = (ObjAtom *)obj;
  markTable(atom->values);
}

static const char *atomBytes(Obj *obj, int length) {
  ObjAtom *atom = (ObjAtom *)obj;
  if (length != atom->values->len * sizeof(Value)) return NULL;
  return (char *)atom->values;
}

static int atomLength(Obj *obj) {
  ObjAtom *atom = (ObjAtom *)obj;
  return atom->values->len;
}

static int inspectAtom(Obj *obj, FILE *io) {
  ObjAtom *atom = (ObjAtom *)obj;
  return fprintf(io, "{") + inspect_table(io, atom->values) + fprintf(io, "}");
}

static int dumpAtom(Obj *obj, FILE *io) {
  ObjAtom *atom = (ObjAtom *)obj;
  ObjIterator *iter = iterate_table(atom->values);
  int len = atomLength((Obj *)atom);
  int tot = fprintf(io, "atom(%d", len);

  while (iterateNext(iter)) {
    tot += fprintf(io, ", ");
    dumpValue(io, iter->current[1]);
  }

  tot += fputs(")", io);
  return tot;
}

const ObjDef Atom = {
    .class_name = "Atom",
    .size = sizeof(ObjAtom),
    .free = freeAtom,
    .mark = markAtom,
    .bytes = atomBytes,
    .inspect = inspectAtom,
    .dump = dumpAtom,
    .length = atomLength,
};

let atom(int len, let *vals) { return obj(copy_atom(vals, len)); }

let atom2(let a, let b) { return atom(2, (let[]){a, b}); }
let atom3(let a, let b, let c) { return atom(3, (let[]){a, b, c}); }
let atom4(let a, let b, let c, let d) { return atom(4, (let[]){a, b, c, d}); }
let atom5(let a, let b, let c, let d, let e) {
  return atom(5, (let[]){a, b, c, d, e});
}
let atom6(let a, let b, let c, let d, let e, let f) {
  return atom(6, (let[]){a, b, c, d, e, f});
}
let atom7(let a, let b, let c, let d, let e, let f, let g) {
  return atom(7, (let[]){a, b, c, d, e, f, g});
}
