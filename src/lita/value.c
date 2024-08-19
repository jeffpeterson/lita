#include <string.h>

#include "memory.h"
#include "object.h"
#include "string.h"
#include "term.h"
#include "value.h"
#include "xxhash.h"

void initValueArray(ValueArray *array) {
  array->values = NULL;
  array->capacity = 0;
  array->count = 0;
}

void writeValueArray(ValueArray *array, Value value) {
  if (array->capacity < array->count + 1) {
    int oldCapacity = array->capacity;
    array->capacity = GROW_CAPACITY(oldCapacity);
    array->values =
        GROW_ARRAY(Value, array->values, oldCapacity, array->capacity);
  }

  array->values[array->count] = value;
  array->count++;
}

void freeValueArray(ValueArray *array) {
  FREE_ARRAY(Value, array->values, array->capacity);
  initValueArray(array);
}

void copy_values(Value *source, Value *dest, usize count) {
  memcpy(dest, source, count * sizeof(Value));
}

int print_value(FILE *io, Value val) {
  if (is_nil(val)) return 0;
  if (is_bool(val)) return fputs(AS_BOOL(val) ? "true" : "false", io);
  if (is_num(val)) return fprintf(io, "%g", AS_NUMBER(val));
  if (is_obj(val)) return print_object(io, AS_OBJ(val));
  return 0;
}

int inspect_value(FILE *io, Value val) {
  switch (val) {
  case True:
  case False:
    return fprintf(io, FG_YELLOW "%s" FG_DEFAULT,
                   AS_BOOL(val) ? "true" : "false") -
           FG_SIZE * 2;
  case VOID: return fputs(FG_RED "void" FG_DEFAULT, io) - FG_SIZE * 2;
  case nil: return fputs(FG_MAGENTA "nil" FG_DEFAULT, io) - FG_SIZE * 2;
  default: break;
  }

  if (is_num(val))
    return fprintf(io, FG_BLUE "%g" FG_DEFAULT, AS_NUMBER(val)) - FG_SIZE * 2;

  if (is_obj(val)) return inspect_obj(io, AS_OBJ(val));
  return 0;
}

let show(let val) {
  char *str = NULL;
  size_t len = 0;
  FILE *io = open_memstream(&str, &len);
  print_value(io, val);
  fclose(io);
  return OBJ_VAL(take_string(str, len));
}

const char *inspectc(let val) { return as_string(inspect(val))->chars; }

let inspect(let val) {
  char *str = NULL;
  size_t len = 0;
  FILE *io = open_memstream(&str, &len);
  inspect_value(io, val);
  fclose(io);
  return OBJ_VAL(take_string(str, len));
}

int trace(const char *label, Value value) {
  if (config.tracing)
    return fprintf(stderr, "[TRACE] %s: ", label) +
           inspect_value(stderr, value) + fprintf(stderr, "\n");
  else return 0;
}

let pp(let val) {
  inspect_value(stderr, val);
  fputc('\n', stderr);
  return val;
}

bool valuesEqual(Value a, Value b) {
#if NAN_BOXING
  if (is_num(a)) return is_num(b) && AS_NUMBER(a) == AS_NUMBER(b);
  return a == b;
#else
  if (a.type != b.type) return false;

  switch (a.type) {
  case VAL_BOOL: return AS_BOOL(a) == AS_BOOL(b);
  case VAL_NIL: return true;
  case VAL_NUMBER: return AS_NUMBER(a) == AS_NUMBER(b);
  case VAL_OBJ: return AS_OBJ(a) == AS_OBJ(b);
  default: return false;
  }
#endif
}

// OBJ > NUMBER > BOOL > NIL > VOID
int cmpValues(Value a, Value b) {
  if (is_obj(a)) {
    return is_obj(b) ? cmpObjects(AS_OBJ(a), AS_OBJ(b)) : -1;
  } else if (is_num(a)) {
    if (is_num(b)) {
      double aa = AS_NUMBER(a);
      double bb = AS_NUMBER(b);
      return aa > bb ? 1 : bb > aa ? -1 : 0;
    }
  }

  // return a > b ? 1 : b > a ? -1 : 0;
  return AS_NUMBER(a) - AS_NUMBER(b);
}

Hash hash_bytes(const char *bytes, usize length) {
  return XXH3_64bits(bytes, length);
}

Hash hash_value(Value val) {
  return is_obj(val) ? AS_OBJ(val)->hash
                     : hash_bytes((char *)&val, sizeof(Value));
}

Hash hash_values(Value *vals, usize length) {
  return hash_bytes((char *)vals, length * sizeof(Value));
}
