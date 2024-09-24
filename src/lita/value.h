#ifndef lita_value_h
#define lita_value_h

#include <stdio.h>
#include <string.h>

#include "common.h"
#include "xxhash.h"

typedef struct Obj Obj;

typedef enum ValueType {
  VAL_VOID,
  VAL_NIL,
  VAL_BOOL,
  VAL_NUMBER,
  VAL_OBJ,
} ValueType;

#if NAN_BOXING

//      quiet -v v- 50 mantisa bits -v
// ?11111111111xx????????????...??????
// ^- sign bit  ^- Intel FP Indef.

/** Set when a Value is not a number. */
#define QNAN ((u64)0x7ffc000000000000)

/** Set only for objects. */
#define SIGN_BIT ((u64)0x8000000000000000)
#define SPARE_BIT_1 ((u64)0x800000000000)
#define SPARE_BIT_2 ((u64)0x400000000000)

#define TAG_PTR SIGN_BIT
#define TAG_OBJ (TAG_PTR | SPARE_BIT_1)

#define TAG_VOID 1   // 01.
#define TAG_UNUSED 2 // 10.
// true must be odd and false+1
#define TAG_FALSE 4 // 100.
#define TAG_TRUE 5  // 101.

typedef u64 Value;

#define AS_BOOL(val) ((val) == TRUE_VAL)
#define AS_NUMBER(val) valueToNum(val)
#define AS_OBJ(val) ((Obj *)(uptr)((val) & ~(TAG_OBJ | QNAN)))

#define BOOL_VAL(b) ((b) ? TRUE_VAL : FALSE_VAL)
#define FALSE_VAL ((Value)(u64)(QNAN | TAG_FALSE))
#define TRUE_VAL ((Value)(u64)(QNAN | TAG_TRUE))
#define NIL_VAL OBJ_VAL(NULL)
/** Used internally. Not accessible from language. */
#define VOID_VAL ((Value)(u64)(QNAN | TAG_VOID))
#define NUMBER_VAL(num) doubleToValue(num)
#define OBJ_VAL(obj) (Value)(TAG_OBJ | QNAN | (u64)(uptr)(obj))

#define isBool(val) (((val) | 1) == TRUE_VAL)
#define isTrue(val) ((val) == TRUE_VAL)
#define isFalse(val) ((val) == FALSE_VAL)
#define isNil(val) ((val) == NIL_VAL)
#define isVoid(val) ((val) == VOID_VAL)
#define isNumber(val) (((val) & QNAN) != QNAN)
#define isObject(val) valueIsObject(val)

static inline double valueToNum(Value value) {
  double num;
  memcpy(&num, &value, sizeof(Value));
  return num;
}

static inline Value doubleToValue(double num) {
  Value value;
  memcpy(&value, &num, sizeof(double));
  return value;
}

static inline bool valueIsObject(Value val) {
  return !isNil(val) && (val & (QNAN | TAG_OBJ)) == (QNAN | TAG_OBJ);
}

#else // else if !NAN_BOXING

typedef struct {
  ValueType type;
  union {
    bool boolean;
    double number;
    Obj *obj;
  } as;
} Value;

#define isBool(value) ((value).type == VAL_BOOL)
#define isVoid(value) ((value).type == VAL_VOID)
#define isNil(value) ((value).type == VAL_NIL)
#define isNumber(value) ((value).type == VAL_NUMBER)
#define isObject(value) ((value).type == VAL_OBJ)

#define AS_BOOL(value) ((value).as.boolean)
#define AS_NUMBER(value) ((value).as.number)
#define AS_OBJ(value) ((value).as.obj)

#define BOOL_VAL(value) ((Value){VAL_BOOL, {.boolean = value}})
#define NIL_VAL ((Value){VAL_NIL, {.number = 0}})
#define VOID_VAL ((Value){VAL_VOID, {.number = 0}})
#define NUMBER_VAL(value) ((Value){VAL_NUMBER, {.number = value}})
#define OBJ_VAL(object) ((Value){VAL_OBJ, {.obj = (Obj *)object}})

#define TRUE_VAL BOOL_VAL(true)
#define FALSE_VAL BOOL_VAL(false)

#endif

#define VOID VOID_VAL
#define nil NIL_VAL
#define True TRUE_VAL
#define False FALSE_VAL

#define obj(o) OBJ_VAL(o)
#define number(n) NUMBER_VAL(n)

#define notNil(val) (!isNil(val))
#define notVoid(val) (!isVoid(val))

typedef Value let;

typedef struct {
  int capacity;
  int count;
  Value *values;
} ValueArray;

bool isFalsey(Value value);
bool valuesEqual(Value a, Value b);
int cmpValues(Value a, Value b);
void copyValues(Value *source, Value *dest, usize count);

void initValueArray(ValueArray *array);
void writeValueArray(ValueArray *array, Value value);
void freeValueArray(ValueArray *array);

int inspectValue(FILE *io, Value value);
int inspectHash(FILE *io, Value value);
int trace(const char *label, Value value);

let inspect(let val);
const char *inspectc(let val);
let pp(let val);

typedef u64 Hash;
typedef XXH64_state_t HashState;

Hash hashBytes(const void *data, usize length);
HashState *startHash();
void updateHash(HashState *state, const void *data, usize length);
Hash endHash(HashState *state);
void hashPointer(const void *ptr, HashState *state);
void hashValue(Value value, HashState *state);
Hash valueHash(Value value);

#define as_num(v) asNumber(v)
double asNumber(Value v);
static inline int asInt(Value v) { return AS_NUMBER(v); }
static inline bool isInt(Value v) {
  return isNumber(v) && asInt(v) == AS_NUMBER(v);
}

#endif
