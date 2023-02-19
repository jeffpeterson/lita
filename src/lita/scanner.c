#include <stdio.h>
#include <string.h>

#include "scanner.h"

Scanner scanner;

static bool skipShebang();
static bool skipWhitespace();

void initScanner(const char *source) {
  scanner.source = source;
  scanner.start = source;
  scanner.current = source;
  scanner.line = 1;

  scanner.indent.prev = 0;
  scanner.indent.cur = 0;
  scanner.indent.indenting = true;

  scanner.data = NULL;
  scanner.dataLength = 0;

  skipShebang();
  skipWhitespace();
}

void resetScanner() { initScanner(scanner.source); }

static u8 utfBytes(const char *str) {
  const u8 *s = (u8 *)str;
  if (s[0] < 0x80) return s[0] ? 1 : 0;
  if (s[1] < 0x80) return 0;
  if (s[0] < 0xE0) return 2;
  if (s[2] < 0x80) return 0;
  if (s[0] < 0xF0) return 3;
  if (s[3] < 0xF0) return 0;
  return 4;
}

static u32 codePoint(const char *str) {
  switch (utfBytes(str)) {
  case 1: return str[0];
  case 2: return ((str[0] & 0x1F) << 6) | (str[1] & 0x3F);
  case 3:
    return ((str[0] & 0x0F) << 12) | ((str[1] & 0x3F) << 6) | (str[2] & 0x3F);
  case 4:
    return ((str[0] & 0x07) << 18) | ((str[1] & 0x3F) << 12) |
           ((str[2] & 0x3F) << 6) | (str[3] & 0x3F);
  default: return 0;
  }
}

static bool isAtEnd() { return *scanner.current == '\0'; }
static bool isAlpha(u32 c) {
  return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_';
}
static bool isDigit(u32 c) { return c >= '0' && c <= '9'; }

static bool isSubscript(u32 c) { return c >= 0x2080 && c <= 0x2089; }
// static bool isSuperscript(u32 c) {
//   return c == 0x00B2 || c == 0x00B3 || // 2,3
//          c == 0x2070 || c == 0x00B9 || // 0,1
//          (c >= 0x2074 && c <= 0x2079); // 4-9
// }

static u32 advance() {
  u32 c = codePoint(scanner.current);
  scanner.current += utfBytes(scanner.current);
  return c;
}

static u32 peek() { return codePoint(scanner.current); }

static u32 peekNext() {
  if (isAtEnd()) return '\0';
  return scanner.current[1];
}

static bool match(u32 expected) {
  if (isAtEnd()) return false;
  if (*scanner.current != expected) return false;
  scanner.current++;
  return true;
}

static int matchStr(const char *str) {
  const char *cur = scanner.current;
  int i = 0;
  for (;;) {
    if (str[i] == '\0') return scanner.current += i, i;
    if (cur[i] == '\0') return 0;
    if (str[i] != cur[i]) return 0;
    i++;
  }
}

Token syntheticToken(const char *text) {
  Token token;
  token.start = text;
  token.length = (int)strlen(text);
  return token;
}

static Token makeToken(TokenType type) {
  Token token;
  token.type = type;
  token.escaped = false;
  token.start = scanner.start;
  token.length = (int)(scanner.current - scanner.start);
  token.line = scanner.line;
  return token;
}

static Token errorToken(const char *message) {
  Token token;
  token.type = TOKEN_ERROR;
  token.start = message;
  token.length = (int)strlen(message);
  token.line = scanner.line;
  return token;
}

// Returns whether shebang was skipped
static bool skipShebang() {
  if (!matchStr("#!")) return false;
  while (peek() != '\n' && !isAtEnd()) advance();
  return true;
}

static bool skipWhitespace() {
  Indent *in = &scanner.indent;
  bool newline = false;

  for (;;) {
    char c = peek();

    switch (c) {
    case ' ':
    case '\r':
      in->indenting = false;
      advance();
      break;

    case '\n':
      scanner.line++;
      if (in->indenting && in->cur > 0) {
        // Done indenting.
        in->prev = in->cur;
      } else {
        newline = true;
      }
      in->indenting = true;
      in->cur = 0;
      advance();
      break;

    case '\t':
      if (in->indenting) {
        // Consume indents up until the current level.
        if (in->cur >= in->prev)
          return false; // This indent is meaningful, return and ignore newline.

        in->cur++;
      } // else skip the tab like other whitespace

      advance();
      break;

    case '\\':
      if (peekNext() == '\n') {
        scanner.line++;
        advance();
        advance();
        break;
      } else {
        return newline;
      }

    case '/':
      if (peekNext() != '/') return newline;
    case '#':
      // A comment goes until the end of the line.
      while (peek() != '\n' && !isAtEnd()) advance();
      break;

    default: return newline;
    }
  }
}

static TokenType checkKeyword(int start, int length, const char *rest,
                              TokenType type) {
  if (scanner.current - scanner.start == start + length &&
      memcmp(scanner.start + start, rest, length) == 0) {
    return type;
  }

  return TOKEN_IDENTIFIER;
}

/**
 * Runs after the scanner has selected a token.
 */
static TokenType identifierType() {
  switch (scanner.start[0]) {
  case 'a':
    if (scanner.current - scanner.start > 1) {
      switch (scanner.start[1]) {
      case 'n': return checkKeyword(2, 1, "d", TOKEN_AND);
      case 's': return checkKeyword(2, 4, "sert", TOKEN_ASSERT);
      }
    }
    break;
  case 'c': return checkKeyword(1, 4, "lass", TOKEN_CLASS);
  case 'e': return checkKeyword(1, 3, "lse", TOKEN_ELSE);
  case 'f':
    if (scanner.current - scanner.start > 1) {
      switch (scanner.start[1]) {
      case 'a': return checkKeyword(2, 3, "lse", TOKEN_FALSE);
      case 'o': return checkKeyword(2, 1, "r", TOKEN_FOR);
      case 'n': return checkKeyword(2, 0, "", TOKEN_FN);
      }
    }
    break;
  case 'i':
    if (scanner.current - scanner.start > 1) {
      switch (scanner.start[1]) {
      case 'f': return checkKeyword(2, 0, "", TOKEN_IF);
      case 'n': return checkKeyword(2, 0, "", TOKEN_IN);
      }
    }
    break;
  case 'l': return checkKeyword(1, 2, "et", TOKEN_LET);
  case 'm': return checkKeyword(1, 4, "atch", TOKEN_MATCH);
  case 'n': return checkKeyword(1, 2, "il", TOKEN_NIL);
  case 'o': return checkKeyword(1, 1, "r", TOKEN_OR);
  case 'p': return checkKeyword(1, 4, "rint", TOKEN_PRINT);
  case 'r': return checkKeyword(1, 5, "eturn", TOKEN_RETURN);
  case 's': return checkKeyword(1, 4, "uper", TOKEN_SUPER);
  case 't':
    if (scanner.current - scanner.start > 1) {
      switch (scanner.start[1]) {
      case 'h': return checkKeyword(2, 2, "is", TOKEN_THIS);
      case 'r': return checkKeyword(2, 2, "ue", TOKEN_TRUE);
      }
    }
    break;
  case 'w': return checkKeyword(1, 4, "hile", TOKEN_WHILE);

  case '_': {
    TokenType type = checkKeyword(1, 6, "_END__", TOKEN_EOF);
    if (type == TOKEN_EOF) {
      scanner.data = scanner.current;
      while (!isAtEnd()) {
        advance();
        scanner.dataLength++;
      }
    }

    return type;
  }
  }

  return TOKEN_IDENTIFIER;
}

static Token identifier() {
  while (isAlpha(peek()) || isDigit(peek())) advance();
  while (isSubscript(peek())) advance();
  while (peek() == '\'') advance();
  return makeToken(identifierType());
}

static Token number() {
  while (isDigit(peek())) advance();

  // Look for the fractional part.
  if (peek() == '.' && isDigit(peekNext())) {
    // Consume the ".".
    advance();

    while (isDigit(peek())) advance();
  }

  return makeToken(TOKEN_NUMBER);
}

static Token string() {
  bool escaped = false;

  while (!isAtEnd()) {
    char ch = peek();

    if (ch == '"' && scanner.current[-1] != '\\') break;

    if (ch == '\n') scanner.line++;
    if (ch == '\\') escaped = true;

    advance();
  }

  if (isAtEnd()) return errorToken("Unterminated string.");

  // The closing quote.
  advance();

  Token token = makeToken(TOKEN_STRING);
  token.escaped = escaped;
  return token;
}

static Token symbol() { return makeToken(TOKEN_QUOTE); }

Token scanToken() {
  scanner.start = scanner.current;
  if (skipWhitespace()) {
    return makeToken(TOKEN_NEWLINE);
  }

  scanner.start = scanner.current;
  Indent *in = &scanner.indent;

  if (isAtEnd()) {
    if (in->prev > 0) {
      in->prev--;
      return makeToken(TOKEN_DEDENT);
    }
    return makeToken(TOKEN_EOF);
  }

  char c = advance();

  if (in->indenting) {
    // skipWhitespace() ensures (in->cur <= in->prev)
    if (c == '\t') {
      // Consume indents
      in->cur++;
      return makeToken(TOKEN_INDENT);
    } else if (in->cur < in->prev) {
      // An indent has ended early.
      in->prev--;
      scanner.current--; // Undo the advance().
      return makeToken(TOKEN_DEDENT);
    }
    // Done indenting.
    in->indenting = false;
    in->prev = in->cur;
  }

  if (isAlpha(c)) return identifier();

  if (isDigit(c)) return number();

  switch (c) {
  case '(': return makeToken(TOKEN_LEFT_PAREN);
  case ')': return makeToken(TOKEN_RIGHT_PAREN);
  case '{': return makeToken(TOKEN_LEFT_BRACE);
  case '}': return makeToken(TOKEN_RIGHT_BRACE);
  case '[': return makeToken(TOKEN_LEFT_BRACKET);
  case ']': return makeToken(TOKEN_RIGHT_BRACKET);
  case ';': return makeToken(TOKEN_SEMICOLON);
  case ':': return makeToken(TOKEN_COLON);
  case ',': return makeToken(TOKEN_COMMA);
  case '?': return makeToken(TOKEN_QUESTION);
  case '$': return identifier();
  case '.':
    return makeToken(match('.') ? (match('.') ? TOKEN_ELLIPSIS : TOKEN_DOT_DOT)
                                : TOKEN_DOT);
  case '-':
    return makeToken(match('>')   ? TOKEN_ARROW
                     : match('=') ? TOKEN_MINUS_EQUAL
                     : match('-') ? TOKEN_MINUS_MINUS

                                  : TOKEN_MINUS);
  case '+':
    return makeToken(match('=')   ? TOKEN_PLUS_EQUAL
                     : match('+') ? TOKEN_PLUS_PLUS
                                  : TOKEN_PLUS);
  case '/': return makeToken(match('=') ? TOKEN_SLASH_EQUAL : TOKEN_SLASH);
  case '*': return makeToken(match('=') ? TOKEN_STAR_EQUAL : TOKEN_STAR);
  case '!': return makeToken(match('=') ? TOKEN_BANG_EQUAL : TOKEN_BANG);
  case '=':
    return makeToken(match('>')   ? TOKEN_FAT_ARROW
                     : match('=') ? TOKEN_EQUAL_EQUAL
                                  : TOKEN_EQUAL);
  case '<':
    return makeToken(match('=')   ? TOKEN_LESS_EQUAL
                     : match('<') ? TOKEN_LESS_LESS
                                  : TOKEN_LESS);
  case '>':
    return makeToken(match('=')   ? TOKEN_GREATER_EQUAL
                     : match('>') ? TOKEN_GREATER_GREATER
                                  : TOKEN_GREATER);
  case '\'': return symbol();
  case '"': return string();
  }

  return errorToken("Unexpected character.");
}
