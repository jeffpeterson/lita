#ifndef lita_string_h
#define lita_string_h

#include "buffer.h"
#include "common.h"
#include "object.h"

#define is_string(val) is_obj_def(val, &String)
#define AS_STRING(val) ((ObjString *)AS_OBJ(val))

const ObjDef String;

Value string(const char *str);

ObjString *as_string(let x);

ObjString *newString(const char *chars);

/**
 * Reuse some existing allocated (null-terminated) chars
 * as a String Obj.
 *
 * [length] should not include the null byte.
 */
ObjString *take_string(char *chars, int length);

/**
 * Copy existing chars into a newly allocated Obj.
 */
ObjString *copyString(const char *chars, usize length);
ObjString *concat_strings(ObjString *a, ObjString *b);
ObjString *buffer_to_string(Buffer *buf);

ObjString *stringf(const char *fmt, ...);
ObjString *string_to_c_ident(ObjString *str);

ObjString *escape_string(ObjString *str);
ObjString *unescapeString(ObjString *str);

ObjString *vstring_format(const char *fmt, va_list args);
ObjString *string_format(const char *fmt, ...);

int vfstring_format(FILE *io, const char *fmt, va_list args);
int fstring_format(FILE *io, const char *fmt, ...);

#endif
