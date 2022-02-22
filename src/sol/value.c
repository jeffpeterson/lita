#include <string.h>

#include "memory.h"
#include "object.h"
#include "term.h"
#include "value.h"

Value nil = NIL_VAL;

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
  return IS_BOOL(val) ? fprintf(io, FG_YELLOW "%s" FG_DEFAULT,
                                AS_BOOL(val) ? "true" : "false") -
                            10
         : IS_NIL(val) ? fprintf(io, FG_MAGENTA "%s" FG_DEFAULT, "nil") - 10
         : IS_NUMBER(val)
             ? fprintf(io, FG_BLUE "%g" FG_DEFAULT, AS_NUMBER(val)) - 10
         : IS_OBJ(val) ? fprintObject(io, AS_OBJ(val))
                       : 0;
}

bool valuesEqual(Value a, Value b) {
#ifdef NAN_BOXING
  if (IS_NUMBER(a) && IS_NUMBER(b))
    return AS_NUMBER(a) == AS_NUMBER(b);

  return a == b;
#else
  if (a.type != b.type)
    return false;

  switch (a.type) {
  case VAL_BOOL:
    return AS_BOOL(a) == AS_BOOL(b);
  case VAL_NIL:
    return true;
  case VAL_NUMBER:
    return AS_NUMBER(a) == AS_NUMBER(b);
  case VAL_OBJ:
    return AS_OBJ(a) == AS_OBJ(b);
  default:
    return false;
  }
#endif
}

// OBJ > NUMBER > BOOL > NIL > VOID
int cmpValues(Value a, Value b) {
  if (IS_OBJ(a)) {
    return IS_OBJ(b) ? cmpObjects(AS_OBJ(a), AS_OBJ(b)) : -1;
  } else if (IS_NUMBER(a)) {
    if (IS_NUMBER(b)) {
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
  for (int i = 0; i < length; i++)
    hash = appendHash(hash, bytes[i]);
  return hash;
}

Hash hashNumber(uint32_t x) { return appendHash(2166136261u, x); }

Hash hashValue(Value val) {
  return IS_OBJ(val) ? AS_OBJ(val)->hash
                     : hashBytes((char *)&val, sizeof(Value));
}

Hash hashValues(Value *vals, int length) {
  return hashBytes((char *)vals, length * sizeof(Value));
}
