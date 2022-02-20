#ifndef sol_scanner_h
#define sol_scanner_h

typedef enum {
  TOKEN_ERROR,
  TOKEN_EOF,

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

  TOKEN_MINUS,
  TOKEN_MINUS_EQUAL,
  TOKEN_PLUS,
  TOKEN_PLUS_EQUAL,
  TOKEN_SLASH,
  TOKEN_SLASH_EQUAL,
  TOKEN_STAR,
  TOKEN_STAR_EQUAL,

  TOKEN_MINUS_MINUS,
  TOKEN_PLUS_PLUS,

  // One or two character tokens.
  TOKEN_BANG,
  TOKEN_BANG_EQUAL,
  TOKEN_EQUAL,
  TOKEN_EQUAL_EQUAL,
  TOKEN_GREATER,
  TOKEN_GREATER_EQUAL,
  TOKEN_LESS,
  TOKEN_LESS_EQUAL,

  // Literals.
  TOKEN_NUMBER,
  TOKEN_STRING,
  TOKEN_SYMBOL,

  // All tokens below IDENTIFIER are valid field names.
  TOKEN_IDENTIFIER,

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
  const char *start;
  int length;
  int line;
} Token;

void initScanner(const char *source);
Token scanToken();

#endif
