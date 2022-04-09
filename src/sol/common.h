#ifndef sol_common_h
#define sol_common_h

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#define NAN_BOXING "Cram all Value types into 64-bits."

#define DEBUG_TRACE "Log trace calls."

// #define DEBUG_TOKENS "Log tokens."

// #define DEBUG_PRINT_CODE "Log each chunk to stderr after it is compiled."

#define DEBUG_TRACE_EXECUTION                                                  \
  "Log each instruction as it is executed by the VM."

// #define DEBUG_TRACE_FRAMES "Log all frames during execution tracing."

// #define DEBUG_LOG_MEM "Enable memory (de)allocation logging."

// #define DEBUG_LOG_GC "Enable garbage collection logging."

// #define DEBUG_STRESS_GC "Causes GC to be run as often as possible."

#define UINT8_COUNT (UINT8_MAX + 1)

typedef int8_t i8;
typedef int16_t i16;
typedef int32_t i32;
typedef int64_t i64;

typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;
typedef size_t usize;

#endif
