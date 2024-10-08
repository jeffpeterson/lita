#include <string.h>

#include "memory.h"
#include "object.h"
#include "string.h"
#include "term.h"
#include "value.h"
#include "vm.h"

bool isFalsey(Value value) { return isNil(value) || isFalse(value); }

double asNumber(Value v) {
  ASSERT(isNumber(v));
  return AS_NUMBER(v);
}

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

void copyValues(Value *source, Value *dest, usize count) {
  memcpy(dest, source, count * sizeof(Value));
}

int inspectHash(FILE *io, Value value) {
  return inspectValue(io, value) + fprintf(io, " %llx\n", valueHash(value));
}

int inspectValue(FILE *io, Value val) {
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

  if (isNumber(val))
    return fprintf(io, FG_BLUE "%g" FG_DEFAULT, AS_NUMBER(val)) - FG_SIZE * 2;

  if (isObject(val)) return inspectObject(io, AS_OBJ(val));
  return 0;
}

const char *inspectc(let val) { return asChars(inspect(val)); }

let inspect(let val) {
  char *str = NULL;
  size_t len = 0;
  FILE *io = open_memstream(&str, &len);
  inspectValue(io, val);
  fclose(io);
  return OBJ_VAL(takeString(str, len));
}

int trace(const char *label, Value value) {
  if (config.tracing)
    return fprintf(stderr, "[TRACE] %s: ", label) +
           inspectValue(stderr, value) + fprintf(stderr, "\n");
  else return 0;
}

let pp(let val) {
  inspectValue(stderr, val);
  fputc('\n', stderr);
  return val;
}

bool valuesEqual(Value a, Value b) {
#if NAN_BOXING
  if (isNumber(a)) return isNumber(b) && AS_NUMBER(a) == AS_NUMBER(b);
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
  if (isObject(a)) {
    return isObject(b) ? cmpObjects(AS_OBJ(a), AS_OBJ(b)) : -1;
  } else if (isNumber(a)) {
    if (isNumber(b)) {
      double aa = AS_NUMBER(a);
      double bb = AS_NUMBER(b);
      return aa > bb ? 1 : bb > aa ? -1 : 0;
    }
  }

  // return a > b ? 1 : b > a ? -1 : 0;
  return AS_NUMBER(a) - AS_NUMBER(b);
}

Hash hashBytes(const void *data, usize length) {
  return XXH64(data, length, 0);
}

HashState *startHash() { return XXH64_createState(); }

void updateHash(HashState *state, const void *data, usize length) {
  if (!data || !length) return;
  assert(!XXH64_update(state, data, length));
}

Hash endHash(HashState *state) {
  Hash hash = XXH64_digest(state);
  XXH64_freeState(state);
  return hash;
}

void hashPointer(const void *ptr, HashState *state) {
  if (!ptr) return;
  updateHash(state, &ptr, sizeof(ptr));
}

void hashValue(Value value, HashState *state) {
  updateHash(state, &value, sizeof(Value));
}

Hash valueHash(Value value) {
  if (isObject(value)) {
    Hash hash = AS_OBJ(value)->hash;
    return ASSERT_MSG(hash, inspectc(value));
  }
  HashState *state = startHash();
  hashValue(value, state);
  return endHash(state);
}
