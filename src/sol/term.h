#ifndef sol_term_h
#define sol_term_h

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

typedef enum Style {
  RESET,
  BOLD,
  DIM,
  ITALIC,
  UNDERLINE,
  SLOW_BLINK,
  RAPID_BLINK,
  INVERT,
  HIDE,
  STRIKE,
  DEFAULT_FONT,
  // Skip 11-20
  NO_BOLD = 21,
  NO_DIM,
  NO_ITALIC,
  NO_UNDERLINE,
  NO_BLINK,
  NO_INVERT = 27,
  NO_HIDE,
  NO_STRIKE,

  FG_BLACK,
  FG_RED,
  FG_GREEN,
  FG_YELLOW,
  FG_BLUE,
  FG_MAGENTA,
  FG_CYAN,
  FG_WHITE,
  FG_SET,
  FG_DEFAULT,

  BG_BLACK,
  BG_RED,
  BG_GREEN,
  BG_YELLOW,
  BG_BLUE,
  BG_MAGENTA,
  BG_CYAN,
  BG_WHITE,
  BG_SET,
  BG_DEFAULT,
} Style;

void fg(Color color);
void bg(Color color);
void style(Style style);

#endif
