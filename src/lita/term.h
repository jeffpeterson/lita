#ifndef lita_term_h
#define lita_term_h

#define RESET "\e[0m"
#define BOLD "\e[1m"
#define DIM "\e[2m"
#define ITALIC "\e[3m"
#define UNDERLINE "\e[4m"
#define SLOW_BLINK "\e[5m"
#define RAPID_BLINK "\e[6m"
#define INVERT "\e[7m"
#define HIDE "\e[8m"
#define STRIKE "\e[9m"
#define DEFAULT_FONT "\e[10m"

#define NO_BOLD "\e[21m"
#define NO_DIM "\e[22m"
#define NO_ITALIC "\e[23m"
#define NO_UNDERLINE "\e[24m"
#define NO_BLINK "\e[25m"

#define NO_INVERT "\e[27m"
#define NO_HIDE "\e[28m"
#define NO_STRIKE "\e[29m"

#define FG_BLACK "\e[30m"
#define FG_RED "\e[31m"
#define FG_GREEN "\e[32m"
#define FG_YELLOW "\e[33m"
#define FG_BLUE "\e[34m"
#define FG_MAGENTA "\e[35m"
#define FG_CYAN "\e[36m"
#define FG_WHITE "\e[37m"
#define FG_SET "\e[38m"
#define FG_DEFAULT "\e[39m"
#define FG_SIZE sizeof(FG_DEFAULT)

#define BG_BLACK "\e[40m"
#define BG_RED "\e[41m"
#define BG_GREEN "\e[42m"
#define BG_YELLOW "\e[43m"
#define BG_BLUE "\e[44m"
#define BG_MAGENTA "\e[45m"
#define BG_CYAN "\e[46m"
#define BG_WHITE "\e[47m"
#define BG_SET "\e[48m"
#define BG_DEFAULT "\e[49m"

#define LINK(name, url) "\e]8;;" url "\e\\" name "\e]8;;\e\\"

/**
 * Prefix with '3' for foreground. And with '4' for background.
 */
typedef enum Color {
  BLACK,
  RED,
  GREEN,
  YELLOW,
  BLUE,
  MAGENTA,
  CYAN,
  WHITE,
  DEFAULT
} Color;

void fg(Color color);
void bg(Color color);

#endif
