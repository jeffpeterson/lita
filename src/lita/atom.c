#include "atom.h"
#include "dump.h"
#include "iterator.h"
#include "lib.h"
#include "memory.h"
#include "native.h"

ObjAtom *takeAtom(Value *values, int length) {
  ObjAtom *atom = copyAtom(values, length);
  FREE_ARRAY(Value, values, length);
  return atom;
}

ObjAtom *copyAtom(Value *values, int length) {
  ObjAtom *atom = allocateAtom();
  initTable(&atom->values);
  for (int i = 0; i < length; i++)
    tableSet(&atom->values, classOf(values[i]), values[i]);
  internObject((Obj **)&atom);
  return atom;
}

NATIVE_METHOD(Atom, get, 1) {
  ObjAtom *atom = asAtom(this);
  let val;
  tableGet(&atom->values, args[0], &val);
  return val;
}

static void freeAtom(Obj *obj) {
  ObjAtom *atom = (ObjAtom *)obj;
  freeTable(&atom->values);
}

static void markAtom(Obj *obj) {
  ObjAtom *atom = (ObjAtom *)obj;
  markTable(&atom->values);
}

static int inspectAtom(Obj *obj, FILE *io) {
  ObjAtom *atom = (ObjAtom *)obj;
  return fprintf(io, "{") + inspectTable(io, &atom->values) + fprintf(io, "}");
}

static int dumpAtom(Obj *obj, FILE *io) {
  ObjAtom *atom = (ObjAtom *)obj;
  ObjIterator *iter = iterateTable(&atom->values);
  int len = atom->values.len;
  int tot = fprintf(io, "atom(%d", len);

  while (iterateNext(iter)) {
    tot += fprintf(io, ", ");
    dumpValue(io, iter->current[1]);
  }

  tot += fputs(")", io);
  return tot;
}

const ObjDef Atom = {
    .className = "Atom",
    .size = sizeof(ObjAtom),
    .free = freeAtom,
    .mark = markAtom,
    .inspect = inspectAtom,
    .dump = dumpAtom,
};

let atom(int len, let *values) { return obj(copyAtom(values, len)); }

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
