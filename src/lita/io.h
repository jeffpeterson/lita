#ifndef lita_io_h
#define lita_io_h

#include "object.h"
#include "value.h"

typedef struct ObjIO {
  Obj obj;
  FILE *fp;
  Ownership ownership;
} ObjIO;

#define isIO(val) isObjDef(val, &IO)
#define asIO(val) as(IO, val)
#define allocateIO() ALLOCATE_OBJ(IO)

ObjIO *makeIO(FILE *fp, Ownership ownership);
Value io(FILE *fp, Ownership ownership);

extern const ObjDef IO;

#endif
