#ifndef sol_scanner_h
#define sol_scanner_h

#include "common.h"

typedef enum {
  TOKEN_ERROR,
  TOKEN_EOF,

  TOKEN_NEWLINE,
  TOKEN_INDENT,
  TOKEN_DEDENT,

  // Single-character tokens.
  TOKEN_LEFT_PAREN,
  TOKEN_RIGHT_PAREN,
  TOKEN_LEFT_BRACE,
  TOKEN_RIGHT_BRACE,
  TOKEN_COLON,
  TOKEN_COMMA,
  TOKEN_DOT,
  TOKEN_DOT_DOT,
  TOKEN_SEMICOLON,
  TOKEN_QUESTION,

  TOKEN_ARROW,     // ->
  TOKEN_FAT_ARROW, // =>

  TOKEN_MINUS_EQUAL,
  TOKEN_PLUS_EQUAL,
  TOKEN_SLASH_EQUAL,
  TOKEN_STAR_EQUAL,

  // One or two character tokens.
  TOKEN_BANG,
  TOKEN_BANG_EQUAL,
  TOKEN_EQUAL,
  TOKEN_EQUAL_EQUAL,
  TOKEN_GREATER,
  TOKEN_GREATER_EQUAL,
  TOKEN_LESS,
  TOKEN_LESS_EQUAL,

  // All tokens below IDENTIFIER are valid field names.
  TOKEN_IDENTIFIER,

  // Literals.
  TOKEN_NUMBER,
  TOKEN_STRING,
  TOKEN_SYMBOL,

  TOKEN_MINUS,
  TOKEN_PLUS,
  TOKEN_SLASH,
  TOKEN_STAR,
  TOKEN_MINUS_MINUS,
  TOKEN_PLUS_PLUS,

  // Keywords.
  TOKEN_AND,
  TOKEN_CLASS,
  TOKEN_ELSE,
  TOKEN_FALSE,
  TOKEN_FOR,
  TOKEN_FN,
  TOKEN_IF,
  TOKEN_IN,
  TOKEN_NIL,
  TOKEN_OR,
  TOKEN_PRINT,
  TOKEN_RETURN,
  TOKEN_SUPER,
  TOKEN_THIS,
  TOKEN_TRUE,
  TOKEN_LET,
  TOKEN_WHILE,
} TokenType;

typedef struct {
  TokenType type;
  bool escape;
  const char *start;
  int length;
  int line;
} Token;

typedef struct Indent {
  int prev;       /** The previous indent level at which text was parsed. */
  int cur;        /** The current number of indents we have parsed. */
  bool indenting; /** When within a series of indents following a newline. */
} Indent;

typedef struct {
  const char *source;  /** Start of current source. */
  const char *start;   /** Start of the current token. */
  const char *current; /** Current char being scanned. */
  int line;            /** Current line number. */
  Indent indent;       /** Indent status. */
  const char *data;
  unsigned int dataLength;
} Scanner;

Scanner scanner;
void initScanner(const char *source);
void resetScanner();
Token scanToken();

#endif
