#ifndef lita_scanner_h
#define lita_scanner_h

#include "common.h"

bool in(u32 c, char start, char end);
bool isAlpha(u32 c);
bool isDigit(u32 c);
bool isHex(u32 c);
bool isSubscript(u32 c);

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
  TOKEN_LEFT_BRACKET,
  TOKEN_RIGHT_BRACKET,
  TOKEN_COLON,
  TOKEN_COMMA,
  TOKEN_DOT,
  TOKEN_DOT_DOT,
  TOKEN_ELLIPSIS,
  TOKEN_SEMICOLON,
  TOKEN_QUESTION,
  TOKEN_QUOTE,
  TOKEN_PIPE,

  TOKEN_ARROW,     // ->
  TOKEN_FAT_ARROW, // =>

  TOKEN_MINUS_EQUAL,
  TOKEN_PLUS_EQUAL,
  TOKEN_SLASH_EQUAL,
  TOKEN_STAR_EQUAL,

  // One or two character tokens.
  TOKEN_EQUAL,

  // All tokens below IDENTIFIER are valid field names.
  TOKEN_IDENTIFIER,

  TOKEN_BANG,
  TOKEN_BANG_EQUAL,
  TOKEN_EQUAL_EQUAL,
  TOKEN_GREATER,
  TOKEN_GREATER_GREATER,
  TOKEN_GREATER_EQUAL,
  TOKEN_LESS,
  TOKEN_LESS_LESS,
  TOKEN_LESS_EQUAL,

  // Literals.
  TOKEN_NUMBER,
  TOKEN_HEX,
  TOKEN_STRING,
  TOKEN_BACKTICK_STRING,

  TOKEN_MINUS,
  TOKEN_PLUS,
  TOKEN_SLASH,
  TOKEN_STAR,
  TOKEN_MINUS_MINUS,
  TOKEN_PLUS_PLUS,

  // Keywords.
  TOKEN_AND,
  TOKEN_ASSERT,
  TOKEN_CFN,
  TOKEN_CLASS,
  TOKEN_ELSE,
  TOKEN_FALSE,
  TOKEN_FOR,
  TOKEN_FN,
  TOKEN_IF,
  TOKEN_IN,
  TOKEN_MATCH,
  TOKEN_NIL,
  TOKEN_OR,
  TOKEN_PRINT,
  TOKEN_RETURN,
  TOKEN_SUPER,
  TOKEN_THIS,
  TOKEN_THROW,
  TOKEN_TRUE,
  TOKEN_LET,
  TOKEN_WHILE,
} TokenType;

typedef struct {
  TokenType type;
  bool escaped;
  bool hadGap;
  const char *start;
  int length;
  int line;
  int column;
} Token;

typedef struct Indent {
  int prev;    /** The previous indent level at which text was parsed. */
  int cur;     /** The current number of indents we have parsed. */
  bool inside; /** We are inside an indent. */
} Indent;

typedef struct {
  const char *source;  /** Start of current source. */
  const char *start;   /** Start of the current token. */
  const char *current; /** Current char being scanned. */
  int line;            /** Current line number. */
  int column;          /** Current column number. */
  Indent indent;       /** Indent status. */
  bool gap;            /** Space between this and the prior token? */
  const char *data;
  unsigned int dataLength;
} Scanner;

extern Scanner scanner;
void initScanner(const char *source);
void resetScanner();
Token scanToken();
Token syntheticToken(const char *text);

#endif
