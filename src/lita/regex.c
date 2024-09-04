#include <assert.h>

#include "lib.h"
#include "memory.h"
#include "native.h"
#include "regex.h"
#include "vm.h"

Value regex(const char *source) { return obj(makeRegex(newString(source))); }

ObjRegex *makeRegex(ObjString *source) {
  ObjRegex *regex = allocateRegex();
  regex->obj.def = &Regex;
  regex->source = source;
  regex->re = pcre2_compile((PCRE2_SPTR)source->chars, source->length, 0,
                            &regex->error_code, &regex->error_offset,
                            NULL); // TODO: pcre2_compile() options

  if (regex->re == NULL) {
    pcre2_get_error_message(regex->error_code, regex->error_message,
                            sizeof(regex->error_message));
    crash("pcre2_compile: %s", (char *)regex->error_message);
  }
  return regex;
}

static int regexLength(Obj *obj) {
  ObjRegex *regex = (ObjRegex *)obj;
  return regex->source->length;
}

static void markRegex(Obj *obj) {
  ObjRegex *regex = (ObjRegex *)obj;
  markObject((Obj *)regex->source);
}

static int inspectRegex(Obj *obj, FILE *io) {
  ObjRegex *regex = (ObjRegex *)obj;
  return fprintf(io, "`") + fputs(regex->source->chars, io) + fprintf(io, "`");
}

static int dumpRegex(Obj *obj, FILE *io) {
  ObjRegex *regex = (ObjRegex *)obj;
  ObjString *source = escape_string(regex->source);
  return fprintf(io, "regex(%.*s)", source->length, source->chars);
}

ObjString *replaceRegex(ObjString *subject, ObjRegex *regex,
                        ObjString *replacement) {
  uint32_t options = PCRE2_SUBSTITUTE_GLOBAL | PCRE2_SUBSTITUTE_EXTENDED |
                     PCRE2_SUBSTITUTE_OVERFLOW_LENGTH;
  Buffer output = new_buffer(subject->length * 2);
  output.count = output.capacity;

  int result;

substitute:
  result =
      pcre2_substitute(regex->re, (PCRE2_SPTR)subject->chars, subject->length,
                       0, options, NULL, NULL, (PCRE2_SPTR)replacement->chars,
                       replacement->length, output.bytes, &output.count);

  if (result == PCRE2_ERROR_NOMEMORY) {
    resize_buffer(&output, output.count);
    goto substitute;
  } else if (result < 0) {
    PCRE2_UCHAR8 error_message[256];
    pcre2_get_error_message(result, error_message, sizeof(error_message));
    crash("pcre2_substitute(%d): %s", result, (char *)error_message);
  }

  return buffer_to_string(&output);
}

NATIVE_GETTER(Regex, source, OBJ_VAL);

REGISTER_OBJECT_DEF(Regex);
const ObjDef Regex = {
    .class_name = "Regex",
    .size = sizeof(ObjRegex),
    .mark = markRegex,
    .inspect = inspectRegex,
    .dump = dumpRegex,
    .length = regexLength,
};
