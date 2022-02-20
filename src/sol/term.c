#include <stdio.h>

#include "term.h"

void fg(Color color) { fprintf(stderr, "\e[3%dm", color); }
void bg(Color color) { fprintf(stderr, "\e[3%dm", color); }
void style(Style style) { fprintf(stderr, "\e[%dm", style); }
