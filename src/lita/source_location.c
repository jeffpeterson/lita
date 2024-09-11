#include <assert.h>

#include "memory.h"
#include "native.h"
#include "source_location.h"
#include "string.h"
#include "term.h"
#include "vm.h"

Value sourceLocation(const char *path, int line, int column) {
  return obj(newSourceLocation(newString(path), line, column));
}

ObjSourceLocation *newSourceLocation(ObjString *path, int line, int column) {
  ObjSourceLocation *sourceLocation = allocateSourceLocation();
  sourceLocation->path = path;
  sourceLocation->line = line;
  sourceLocation->column = column;
  return sourceLocation;
}

static void markSourceLocation(Obj *obj) {
  ObjSourceLocation *sourceLocation = (ObjSourceLocation *)obj;
  markObject((Obj *)sourceLocation->path);
}

static int inspectSourceLocation(Obj *obj, FILE *io) {
  ObjSourceLocation *sourceLocation = (ObjSourceLocation *)obj;
  return fprintf(io, UNDERLINE "%s:%d:%d" NO_UNDERLINE,
                 sourceLocation->path->chars, sourceLocation->line,
                 sourceLocation->column) -
         sizeof(UNDERLINE) - sizeof(NO_UNDERLINE);
}

NATIVE_GETTER(SourceLocation, path, OBJ_VAL);

DEFINE_OBJECT_TYPE(SourceLocation, .mark = markSourceLocation,
                   .inspect = inspectSourceLocation);
