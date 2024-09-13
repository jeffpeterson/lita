#include <stdio.h>
#include <stdlib.h>

#include "readline.h"

#if NO_READLINE

int write_history(const char *path) { return 0; }
int read_history(const char *path) { return 0; }
void add_history(const char *line) { return; }

char *readline(const char *prompt) {
  printf("%s", prompt);
  fflush(stdout);

  usize lineSize;
  char *line = NULL;

  if (getline(&line, &lineSize, stdin) == -1) {
    free(line);
    return NULL;
  }

  return line;
}

#endif
