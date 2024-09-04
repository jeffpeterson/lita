#ifndef lita_regex_h
#define lita_regex_h

#define PCRE2_CODE_UNIT_WIDTH 8

#include <pcre2.h>

#include "common.h"
#include "object.h"
#include "string.h"
#include "value.h"

typedef struct ObjRegex {
  Obj obj;
  ObjString *source;
  pcre2_code *re;
  PCRE2_SIZE error_offset;
  int error_code;
  PCRE2_UCHAR8 error_message[256];
} ObjRegex;

#define allocateRegex() ALLOCATE_OBJ(Regex)
#define isRegex(val) is_obj_def(val, &Regex)
#define asRegex(val) as(Regex, val)

ObjRegex *makeRegex(ObjString *source);
Value regex(const char *source);
ObjString *replaceRegex(ObjString *subject, ObjRegex *regex,
                        ObjString *replacement);

const ObjDef Regex;

#endif
