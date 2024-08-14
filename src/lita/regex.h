#ifndef lita_regex_h
#define lita_regex_h

#define PCRE2_CODE_UNIT_WIDTH 8

#include <pcre2.h>

#include "common.h"
#include "object.h"
#include "value.h"

typedef struct ObjRegex {
  Obj obj;
  ObjString *source;
  pcre2_code *re;
  PCRE2_SIZE error_offset;
  int error_code;
  PCRE2_UCHAR8 error_message[256];
} ObjRegex;

#define AS_REGEX(val) ((ObjRegex *)AS_OBJ(val))
#define is_regex(val) is_obj_def(val, &Regex)
#define new_regex() ((ObjRegex *)new_object(&Regex))

ObjRegex *make_regex(ObjString *source);
Value regex(const char *source);

const ObjDef Regex;

#endif
