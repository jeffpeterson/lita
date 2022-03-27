#include <assert.h>

#include "debug.h"
#include "lib.h"
#include "scanner.h"

static void assertToken(TokenType type) { assert(scanToken().type == type); }

static void assertTokens(TokenType *types) {
  do {
    assertToken(*types);
  } while (*(types++) != TOKEN_EOF);
}

void scanner_test() {
  initScanner("");
  assertTokens((TokenType[]){TOKEN_EOF});

  initScanner("let x = 1");
  assertTokens((TokenType[]){TOKEN_LET, TOKEN_IDENTIFIER, TOKEN_EQUAL,
                             TOKEN_NUMBER, TOKEN_EOF});

  initScanner("while true\n\tfoo()\n");
  assertTokens((TokenType[]){
      TOKEN_WHILE, TOKEN_TRUE, TOKEN_INDENT, TOKEN_IDENTIFIER, TOKEN_LEFT_PAREN,
      TOKEN_RIGHT_PAREN, TOKEN_NEWLINE, TOKEN_DEDENT, TOKEN_EOF});

  initScanner("\n\nfoo()\n");
  assertTokens((TokenType[]){TOKEN_IDENTIFIER, TOKEN_LEFT_PAREN,
                             TOKEN_RIGHT_PAREN, TOKEN_NEWLINE, TOKEN_EOF});
}
