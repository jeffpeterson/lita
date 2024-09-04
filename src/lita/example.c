#include <assert.h>

#include "example.h"
#include "memory.h"
#include "native.h"
#include "string.h"
#include "vm.h"

Value example(const char *comment) {
  return obj(newExample(newString(comment)));
}

ObjExample *newExample(ObjString *comment) {
  ObjExample *example = allocateExample();
  example->comment = comment;
  return example;
}

static int exampleLength(Obj *obj) {
  ObjExample *example = (ObjExample *)obj;
  return example->comment->length;
}

static void markExample(Obj *obj) {
  ObjExample *example = (ObjExample *)obj;
  markObject((Obj *)example->comment);
}

static int inspectExample(Obj *obj, FILE *io) {
  ObjExample *example = (ObjExample *)obj;
  return fstring_format(io, "Example({})", obj(example->comment));
}

NATIVE_GETTER(Example, comment, OBJ_VAL);

REGISTER_OBJECT_DEF(Example);
ObjDef Example = {
    .class_name = "Example",
    .size = sizeof(ObjExample),
    .mark = markExample,
    .inspect = inspectExample,
    .length = exampleLength,
};
