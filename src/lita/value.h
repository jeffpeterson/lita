#ifndef lita_value_h
#define lita_value_h

#include <stdio.h>
#include <string.h>

#include "common.h"

typedef struct Obj Obj;
typedef struct ObjString ObjString;

#ifdef NAN_BOXING

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

#define is_bool(val) (((val) | 1) == TRUE_VAL)
#define is_nil(val) ((val) == NIL_VAL)
#define is_void(val) ((val) == VOID_VAL)
#define is_num(val) (((val) & QNAN) != QNAN)
#define is_obj(val) valueIsObj(val)

#define AS_BOOL(val) ((val) == TRUE_VAL)
#define AS_NUMBER(val) valueToNum(val)
#define AS_OBJ(val) ((Obj *)(uintptr_t)((val) & ~(TAG_OBJ | QNAN)))

#define BOOL_VAL(b) ((b) ? TRUE_VAL : FALSE_VAL)
#define FALSE_VAL ((Value)(uint64_t)(QNAN | TAG_FALSE))
#define TRUE_VAL ((Value)(uint64_t)(QNAN | TAG_TRUE))
#define NIL_VAL OBJ_VAL(NULL)
/** Used internally. Not accessible from language. */
#define VOID_VAL ((Value)(uint64_t)(QNAN | TAG_VOID))
#define NUMBER_VAL(num) numToValue(num)
#define OBJ_VAL(obj) (Value)(TAG_OBJ | QNAN | (uint64_t)(uintptr_t)(obj))
#define obj(o) OBJ_VAL(o)

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
  return !is_nil(val) && (val & (QNAN | TAG_OBJ)) == (QNAN | TAG_OBJ);
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

#define is_bool(value) ((value).type == VAL_BOOL)
#define is_void(value) ((value).type == VAL_VOID)
#define is_nil(value) ((value).type == VAL_NIL)
#define is_num(value) ((value).type == VAL_NUMBER)
#define is_obj(value) ((value).type == VAL_OBJ)

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

#define nil NIL_VAL
#define True TRUE_VAL
#define False FALSE_VAL

#define not_nil(val) (!is_nil(val))

typedef Value let;

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

int inspect_value(FILE *io, Value value);
int trace(const char *label, Value value);

typedef u32 Hash;

Hash hash_bytes(const char *key, usize length);
Hash hash_value(Value val);
Hash hash_values(Value *vals, usize length);

static inline int as_int(Value x) { return AS_NUMBER(x); }

static inline bool is_int(Value x) {
  return is_num(x) && as_int(x) == AS_NUMBER(x);
}

#endif
