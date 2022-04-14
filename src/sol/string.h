#ifndef sol_string_h
#define sol_string_h

#include "common.h"
#include "object.h"

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
ObjString *copyString(const char *chars, int length);
ObjString *concatStrings(ObjString *a, ObjString *b);
ObjString *stringf(const char *fmt, ...);
ObjString *escapeString(ObjString *str);
ObjString *stringToCIdent(ObjString *str);

ObjString *vstringFormat(const char *fmt, va_list args);
ObjString *stringFormat(const char *fmt, ...);
int fstringFormat(FILE *io, const char *fmt, ...);

#endif
