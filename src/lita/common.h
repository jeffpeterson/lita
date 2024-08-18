#ifndef lita_common_h
#define lita_common_h

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#define NAN_BOXING "Cram all Value types into 64-bits."

#define ENABLE_REGEX "Enable regex support."

#define DEBUG_ERRORS "Log extra debug information on error."

#define DEBUG_TRACE "Log trace calls."

#define DEBUG_ASSERTS "Log assert calls."

// #define DEBUG_ASSERT_CODE "Log assert source."

// #define DEBUG_TOKENS "Log tokens."

// #define DEBUG_PRINT_CODE "Log each chunk to stderr after it is compiled."

// #define DEBUG_TRACE_EXECUTION                                                  \
//   "Log each instruction as it is executed by the VM."

// #define DEBUG_TRACE_FRAMES "Log all frames during execution tracing."

// #define DEBUG_LOG_MEM "Enable memory (de)allocation logging."

// #define DEBUG_LOG_GC "Enable garbage collection logging."

// #define DEBUG_STRESS_GC "Causes GC to be run as often as possible."

#define UINT8_COUNT (UINT8_MAX + 1)

typedef int8_t i8;
typedef int16_t i16;
typedef int32_t i32;
typedef int64_t i64;
typedef __int128_t i128;

typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;
typedef __uint128_t u128;
typedef size_t usize;

typedef struct Config {
  bool tracing;
} Config;

extern Config config;

#define DEPRECATED(msg) __attribute__((deprecated(msg)))
#define SECTION(name) __attribute__((used, section("__DATA," #name)))
#define SECTION_START(name) __asm("section$start$__DATA$" #name)
#define SECTION_STOP(name) __asm("section$end$__DATA$" #name)

#define section_foreach_entry(section_name, type_t, elem)                      \
  for (type_t *elem = ({                                                       \
         extern type_t __start_##section_name SECTION_START(section_name);     \
         &__start_##section_name;                                              \
       });                                                                     \
       elem < ({                                                               \
         extern type_t __stop_##section_name SECTION_STOP(section_name);       \
         &__stop_##section_name;                                               \
       });                                                                     \
       elem++)

#endif
