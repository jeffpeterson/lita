#ifndef lita_readline_h
#define lita_readline_h

#include "common.h"

// #define Function ReadlineFunction
// #include <readline/history.h>
// #include <readline/readline.h>
// #undef Function

extern char *readline(const char *prompt);
extern int read_history(const char *path);
extern void add_history(const char *line);
extern int write_history(const char *line);

#endif
