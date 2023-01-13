#include <string.h>

#include "memory.h"
#include "object.h"
#include "term.h"
#include "value.h"

Value nil = NIL_VAL;
Value True = TRUE_VAL;
Value False = FALSE_VAL;

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

int fprintValue(FILE *io, Value val) {
  return is_bool(val) ? fprintf(io, FG_YELLOW "%s" FG_DEFAULT,
                                AS_BOOL(val) ? "true" : "false") -
                            10
         : is_nil(val) ? fprintf(io, FG_MAGENTA "%s" FG_DEFAULT, "nil") - 10
         : is_num(val)
             ? fprintf(io, FG_BLUE "%g" FG_DEFAULT, AS_NUMBER(val)) - 10
         : is_obj(val) ? fprintObject(io, AS_OBJ(val))
         : is_ptr(val) ? fprintf(io, FG_RED "%p" FG_DEFAULT, AS_PTR(val))
                       : 0;
}

int trace(const char *label, Value value) {
#ifdef DEBUG_TRACE
  return fprintf(stderr, "%s: ", label) + fprintValue(stderr, value) +
         fprintf(stderr, "\n");
#else
  return 0;
#endif
}

bool valuesEqual(Value a, Value b) {
#ifdef NAN_BOXING
  if (is_num(a)) return is_num(b) && AS_NUMBER(a) == AS_NUMBER(b);
  if (!is_obj(a) || is_interned(b)) return a == b;

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
  return a - b;
}

Hash appendHash(Hash hash, uint32_t x) {
  hash ^= x;
  hash *= 16777619;
  return hash;
}

Hash hashBytes(const char *bytes, int length) {
  Hash hash = 2166136261u;
  for (int i = 0; i < length; i++) hash = appendHash(hash, bytes[i]);
  return hash;
}

Hash hashNumber(uint32_t x) { return appendHash(2166136261u, x); }

Hash hashValue(Value val) {
  return is_obj(val) ? AS_OBJ(val)->hash
                     : hashBytes((char *)&val, sizeof(Value));
}

Hash hashValues(Value *vals, int length) {
  return hashBytes((char *)vals, length * sizeof(Value));
}
