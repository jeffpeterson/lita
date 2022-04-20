#ifndef sol_value_h
#define sol_value_h

#include <stdio.h>
#include <string.h>

#include "common.h"

typedef struct Obj Obj;
typedef struct ObjString ObjString;

#ifdef NAN_BOXING

/** Set when a Value is not a number. */
#define QNAN ((uint64_t)0x7ffc000000000000)

/** Set only for objects. */
#define SIGN_BIT ((uint64_t)0x8000000000000000)

#define TAG_VOID 1   // 01.
#define TAG_UNUSED 2 // 10.
// true must be odd and false+1
#define TAG_FALSE 4 // 100.
#define TAG_TRUE 5  // 101.

typedef uint64_t Value;
typedef Value let;

#define IS_BOOL(val) (((val) | 1) == TRUE_VAL)
#define IS_NIL(val) ((val) == NIL_VAL)
#define IS_VOID(val) ((val) == VOID_VAL)
#define IS_NUMBER(val) (((val)&QNAN) != QNAN)
#define IS_OBJ(val) valueIsObj(val)

#define AS_BOOL(val) ((val) == TRUE_VAL)
#define AS_NUMBER(val) valueToNum(val)
#define AS_OBJ(val) ((Obj *)(uintptr_t)((val) & ~(SIGN_BIT | QNAN)))

#define BOOL_VAL(b) ((b) ? TRUE_VAL : FALSE_VAL)
#define FALSE_VAL ((Value)(uint64_t)(QNAN | TAG_FALSE))
#define TRUE_VAL ((Value)(uint64_t)(QNAN | TAG_TRUE))
#define NIL_VAL OBJ_VAL(NULL)
/** Used internally. Not accessible from language. */
#define VOID_VAL ((Value)(uint64_t)(QNAN | TAG_VOID))
#define NUMBER_VAL(num) numToValue(num)
#define OBJ_VAL(obj) (Value)(SIGN_BIT | QNAN | (uint64_t)(uintptr_t)(obj))

static inline double valueToNum(Value value) {
  double num;
  memcpy(&num, &value, sizeof(Value));
  return num;
}

static inline Value numToValue(double num) {
  Value value;
  memcpy(&value, &num, sizeof(double));
  return value;
}

static inline bool valueIsObj(Value val) {
  return !IS_NIL(val) && (val & (QNAN | SIGN_BIT)) == (QNAN | SIGN_BIT);
}

#else // else if !NAN_BOXING

typedef enum {
  VAL_VOID,
  VAL_NIL,
  VAL_BOOL,
  VAL_NUMBER,
  VAL_OBJ,
} ValueType;

typedef struct {
  ValueType type;
  union {
    bool boolean;
    double number;
    Obj *obj;
  } as;
} Value;

// typedef struct {
//   ValueType type;
//   union {
//     bool boolean;
//     double number;
//     uint64_t objectId;
//   } as;
//   Obj *unit;
// } ValueWithUnit;

#define IS_BOOL(value) ((value).type == VAL_BOOL)
#define IS_NIL(value) ((value).type == VAL_NIL)
#define IS_NUMBER(value) ((value).type == VAL_NUMBER)
#define IS_OBJ(value) ((value).type == VAL_OBJ)

#define AS_BOOL(value) ((value).as.boolean)
#define AS_NUMBER(value) ((value).as.number)
#define AS_OBJ(value) ((value).as.obj)

#define BOOL_VAL(value) ((Value){VAL_BOOL, {.boolean = value}})
#define NIL_VAL ((Value){VAL_NIL, {.number = 0}})
#define NUMBER_VAL(value) ((Value){VAL_NUMBER, {.number = value}})
#define OBJ_VAL(object) ((Value){VAL_OBJ, {.obj = (Obj *)object}})

#endif

Value nil;
Value True;
Value False;

typedef struct {
  int capacity;
  int count;
  Value *values;
} ValueArray;

bool valuesEqual(Value a, Value b);
int cmpValues(Value a, Value b);

void initValueArray(ValueArray *array);
void writeValueArray(ValueArray *array, Value value);
void freeValueArray(ValueArray *array);
int fprintValue(FILE *io, Value value);
int trace(const char *label, Value value);

typedef uint32_t Hash;

Hash appendHash(Hash hash, uint32_t x);
Hash hashBytes(const char *key, int length);
Hash hashNumber(uint32_t x);
Hash hashValue(Value val);
Hash hashValues(Value *vals, int length);

#endif
