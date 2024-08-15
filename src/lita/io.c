#include <assert.h>

#include "io.h"
#include "lib.h"
#include "memory.h"
#include "native.h"
#include "vm.h"

/** Safely convert val to io pointer. */
ObjIO *as_io(let x) {
  assert(is_io(x));
  return AS_IO(x);
}

ObjIO *make_io(FILE *fp, Ownership ownership) {
  ObjIO *io = (ObjIO *)new_object(&IO);
  io->fp = fp;
  io->ownership = ownership;
  // TODO: Handle this with getInterned or something:
  io->obj.hash = hash_bytes((char *)&io->fp, sizeof(&io->fp));
  return io;
}

let io(FILE *fp, Ownership ownership) { return obj(make_io(fp, ownership)); }

const char *io_bytes(Obj *obj, int length) {
  ObjIO *io = (ObjIO *)obj;
  if (length != sizeof(&io->fp)) return NULL;
  return (char *)&io->fp;
}

static int inspect_io(Obj *obj, FILE *fp) {
  ObjIO *io = (ObjIO *)obj;
  return fprintf(fp, "<IO %p>", io->fp);
}

static void free_io(Obj *obj) {
  ObjIO *io = (ObjIO *)obj;
  if (io->ownership) fclose(io->fp);
}

NATIVE_METHOD(IO, write, 1) {
  ObjIO *io = as_io(this);
  ObjString *str = as_string(to_string(args[0]));
  fwrite(str->chars, sizeof(char), str->length, io->fp);
  return this;
}

REGISTER_OBJECT_DEF(IO);
const ObjDef IO = {
    .class_name = "IO",
    .size = sizeof(ObjIO),
    .free = free_io,
    .interned = true,
    .bytes = io_bytes,
    .inspect = inspect_io,
};
