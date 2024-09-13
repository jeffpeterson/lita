#include <stdio.h>
#include <stdlib.h>

#include "readline.h"

#if !READLINE

int write_history(const char *path) { return 0; }
int read_history(const char *path) { return 0; }
void add_history(const char *line) { return; }

char *readline(const char *prompt) {
  printf("%s", prompt);
  fflush(stdout);

  size_t line_size = 128;
  char *line = (char *)malloc(line_size);
  if (line == NULL) return NULL;

  getline(&line, &line_size, stdin);

  return line;
}

#endif
