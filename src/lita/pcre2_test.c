#define PCRE2_CODE_UNIT_WIDTH 8

#include <assert.h>
#include <pcre2.h>

#include "debug.h"

void pcre2_test() {
  // https://www.pcre.org/current/doc/html/pcre2demo.html

  char pattern[] = "(a.c)";
  int error_code;
  PCRE2_SIZE error_offset;
  pcre2_code *regex =
      pcre2_compile((PCRE2_SPTR)pattern, sizeof(pattern),
                    /*options*/ 0, &error_code, &error_offset, NULL);

  assert(regex != NULL);

  pcre2_match_data *match_data =
      pcre2_match_data_create_from_pattern(regex, NULL);

  char subject[] = "abc";
  int rc = pcre2_match(regex, (PCRE2_SPTR)subject, sizeof(subject),
                       /*offset*/ 0, /*options*/ 0, match_data, NULL);

  assert(rc == 2);
  PCRE2_SIZE *ovector = pcre2_get_ovector_pointer(match_data);

  assert(ovector[0] == 0);
  assert(ovector[1] == 4);

  pcre2_match_data_free(match_data);
  pcre2_code_free(regex);
}
