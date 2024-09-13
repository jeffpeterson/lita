#ifndef lita_atom_h
#define lita_atom_h

#include "common.h"
#include "object.h"
#include "table.h"

#define isAtom(val) isObjDef(val, &Atom)
#define asAtom(val) as(Atom, val)
#define allocateAtom() ALLOCATE_OBJ(Atom)

typedef struct ObjAtom {
  Obj obj;
  Table *values;
} ObjAtom;

extern const ObjDef Atom;

ObjAtom *copy_atom(Value *values, uint8_t length);
ObjAtom *take_atom(Value *values, uint8_t length);

let atom(int len, let *vals);
let atom2(let a, let b);
let atom3(let a, let b, let c);
let atom4(let a, let b, let c, let d);
let atom5(let a, let b, let c, let d, let e);
let atom6(let a, let b, let c, let d, let e, let f);
let atom7(let a, let b, let c, let d, let e, let f, let g);

#endif
