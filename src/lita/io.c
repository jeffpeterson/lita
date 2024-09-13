#include <assert.h>

#include "io.h"
#include "lib.h"
#include "memory.h"
#include "native.h"
#include "vm.h"

ObjIO *makeIO(FILE *fp, Ownership ownership) {
  ObjIO *io = allocateIO();
  io->fp = fp;
  io->ownership = ownership;
  // TODO: Handle this with getInterned or something:
  io->obj.hash = hashBytes((char *)&io->fp, sizeof(&io->fp));
  return io;
}

let io(FILE *fp, Ownership ownership) { return obj(makeIO(fp, ownership)); }

const char *IOBytes(Obj *obj, int length) {
  ObjIO *io = (ObjIO *)obj;
  if (length != sizeof(&io->fp)) return NULL;
  return (char *)&io->fp;
}

static int inspectIO(Obj *obj, FILE *fp) {
  ObjIO *io = (ObjIO *)obj;
  return fprintf(fp, "<IO %p>", io->fp);
}

static void freeIO(Obj *obj) {
  ObjIO *io = (ObjIO *)obj;
  if (io->ownership) fclose(io->fp);
}

NATIVE_METHOD(IO, write, 1) {
  ObjIO *io = asIO(this);
  ObjString *str = asString(args[0]);
  fwrite(str->chars, sizeof(char), str->length, io->fp);
  return this;
}

REGISTER_OBJECT_DEF(IO);
const ObjDef IO = {
    .className = "IO",
    .size = sizeof(ObjIO),
    .free = freeIO,
    .interned = true,
    .bytes = IOBytes,
    .inspect = inspectIO,
};
