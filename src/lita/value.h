#ifndef lita_value_h
#define lita_value_h

#include <stdio.h>
#include <string.h>

#include "common.h"

typedef struct Obj Obj;
typedef struct ObjString ObjString;

typedef enum {
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
#define QNAN ((uint64_t)0x7ffc000000000000)

/** Set only for objects. */
#define SIGN_BIT ((uint64_t)0x8000000000000000)
#define SPARE_BIT_1 ((uint64_t)0x800000000000)
#define SPARE_BIT_2 ((uint64_t)0x400000000000)

#define TAG_PTR SIGN_BIT
#define TAG_OBJ (TAG_PTR | SPARE_BIT_1)

#define TAG_VOID 1   // 01.
#define TAG_UNUSED 2 // 10.
// true must be odd and false+1
#define TAG_FALSE 4 // 100.
#define TAG_TRUE 5  // 101.

typedef uint64_t Value;

#define AS_BOOL(val) ((val) == TRUE_VAL)
#define AS_NUMBER(val) valueToNum(val)
#define AS_OBJ(val) ((Obj *)(uintptr_t)((val) & ~(TAG_OBJ | QNAN)))

#define BOOL_VAL(b) ((b) ? TRUE_VAL : FALSE_VAL)
#define FALSE_VAL ((Value)(uint64_t)(QNAN | TAG_FALSE))
#define TRUE_VAL ((Value)(uint64_t)(QNAN | TAG_TRUE))
#define NIL_VAL OBJ_VAL(NULL)
/** Used internally. Not accessible from language. */
#define VOID_VAL ((Value)(uint64_t)(QNAN | TAG_VOID))
#define NUMBER_VAL(num) doubleToValue(num)
#define OBJ_VAL(obj) (Value)(TAG_OBJ | QNAN | (uint64_t)(uintptr_t)(obj))

#define isBool(val) (((val) | 1) == TRUE_VAL)
#define isTrue(val) ((val) == TRUE_VAL)
#define isFalse(val) ((val) == FALSE_VAL)
#define isNil(val) ((val) == NIL_VAL)
#define isVoid(val) ((val) == VOID_VAL)
#define isNumber(val) (((val)&QNAN) != QNAN)
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

bool valuesEqual(Value a, Value b);
int cmpValues(Value a, Value b);
void copyValues(Value *source, Value *dest, usize count);

void initValueArray(ValueArray *array);
void writeValueArray(ValueArray *array, Value value);
void freeValueArray(ValueArray *array);

int inspectValue(FILE *io, Value value);
int trace(const char *label, Value value);

let inspect(let val);
const char *inspectc(let val);
let pp(let val);

typedef u64 Hash;

Hash hashBytes(const char *key, usize length);
Hash hashValue(Value val);
Hash hashValues(Value *vals, usize length);

double as_num(Value x);
static inline int asInt(Value x) { return AS_NUMBER(x); }
static inline bool isInt(Value x) {
  return isNumber(x) && asInt(x) == AS_NUMBER(x);
}

#endif
