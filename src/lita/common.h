#ifndef lita_common_h
#define lita_common_h

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

// "Cram all Value types into 64-bits."
#define NAN_BOXING 1

// "Enable regex support."
#define ENABLE_REGEX 1

// "Log extra debug information on error."
#define DEBUG_ERRORS 1

// "Log assert calls."
#define DEBUG_ASSERTS 0

// "Log assert source."
#define DEBUG_ASSERT_CODE 0

// "Log tokens for each file."
#define DEBUG_TOKENS 0

// "Log each token as it is consumed by the compiler."
#define DEBUG_PRINT_EACH_TOKEN 0

// "Log each chunk to stderr after it is compiled."
#define DEBUG_PRINT_CODE 0

// "Log each instruction as it is executed by the VM."
#define DEBUG_TRACE_EXECUTION 0

// "Log all frames during execution tracing."
#define DEBUG_TRACE_FRAMES 0

// "Enable memory (de)allocation logging."
#define DEBUG_LOG_MEM 0

// "Enable garbage collection logging."
#define DEBUG_LOG_GC 0

// "Causes GC to be run as often as possible."
#define DEBUG_STRESS_GC 0

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
  u8 debug;
} Config;

extern Config config;

#define STRINGIFY_(x) #x
#define STRINGIFY(x) STRINGIFY_(x)
#define DEPRECATED(msg) __attribute__((deprecated(msg)))

#if defined(__APPLE__)

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

#else
#define SECTION(name) __attribute__((used, section(#name)))
#define SECTION_START(name) __start_##name
#define SECTION_STOP(name) __stop_##name

#define section_foreach_entry(section_name, type_t, elem)                      \
  for (type_t *elem = &__start_##section_name; elem < &__stop_##section_name;  \
       elem++)
#endif

#endif
