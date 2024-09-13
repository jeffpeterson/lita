#ifndef lita_string_h
#define lita_string_h

#include "buffer.h"
#include "common.h"
#include "object.h"

#define str string

#define allocateString() ALLOCATE_OBJ(String)
#define isString(val) isObjDef(val, &String)
#define asString(val) as(String, val)
#define asChars(val) (asString(val)->chars)

struct ObjString {
  Obj obj;
  int length;
  char *chars;
};

extern const ObjDef String;

Value string(const char *str);

ObjString *newString(const char *chars);

/**
 * Reuse some existing allocated (null-terminated) chars
 * as a String Obj.
 *
 * [length] should not include the null byte.
 */
ObjString *takeString(char *chars, int length);

/**
 * Copy existing chars into a newly allocated Obj.
 */
ObjString *copyString(const char *chars, usize length);
ObjString *concatStrings(ObjString *a, ObjString *b);
ObjString *bufferToString(Buffer *buf);

ObjString *stringf(const char *fmt, ...);
ObjString *stringToCIdent(ObjString *str);

ObjString *escapeString(ObjString *str);
ObjString *unescapeString(ObjString *str);

ObjString *vstringFormat(const char *fmt, va_list args);
ObjString *stringFormat(const char *fmt, ...);

int vfstringFormat(FILE *io, const char *fmt, va_list args);
int fstringFormat(FILE *io, const char *fmt, ...);

#endif
