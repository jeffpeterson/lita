#include "term.h"

int fg(FILE *io, Color color) { return fprintf(io, "\e[3%dm", color); }
int bg(FILE *io, Color color) { return fprintf(io, "\e[4%dm", color); }
