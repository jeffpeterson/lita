#include <assert.h>

#include "debug.h"
#include "scanner.h"

static Token log(Token token) {
  // printf("Token[%2d]: \"%.*s\"\n", token.type, token.length, token.start);
  return token;
}

#define expect(token) assert(log(scanToken()).type == token)

void scanner_test() {
  initScanner("");
  expect(TOKEN_EOF);

  initScanner("let x = 1");
  expect(TOKEN_LET);
  expect(TOKEN_IDENTIFIER);
  expect(TOKEN_EQUAL);
  expect(TOKEN_NUMBER);
  expect(TOKEN_EOF);

  initScanner("while true\n"
              "\tfoo()\n");
  expect(TOKEN_WHILE);
  expect(TOKEN_TRUE);
  expect(TOKEN_INDENT);
  expect(TOKEN_IDENTIFIER);
  expect(TOKEN_LEFT_PAREN);
  expect(TOKEN_RIGHT_PAREN);
  expect(TOKEN_DEDENT);
  expect(TOKEN_EOF);

  initScanner("\n"
              "\n"
              "foo()\n");
  expect(TOKEN_IDENTIFIER);
  expect(TOKEN_LEFT_PAREN);
  expect(TOKEN_RIGHT_PAREN);
  expect(TOKEN_NEWLINE);
  expect(TOKEN_EOF);

  initScanner("class Foo\n"
              "\tbar");
  expect(TOKEN_CLASS);
  expect(TOKEN_IDENTIFIER);
  expect(TOKEN_INDENT);
  expect(TOKEN_IDENTIFIER);
  expect(TOKEN_DEDENT);
  expect(TOKEN_EOF);

  initScanner("class Foo\n"
              "\t\n"
              "\tbar");
  expect(TOKEN_CLASS);
  expect(TOKEN_IDENTIFIER);
  expect(TOKEN_INDENT);
  expect(TOKEN_IDENTIFIER);
  expect(TOKEN_DEDENT);
  expect(TOKEN_EOF);

  initScanner("// comment\n"
              "\t// comment\n");
  expect(TOKEN_EOF);

  initScanner("class Foo\n"
              "\n"
              "\tbar");
  expect(TOKEN_CLASS);
  expect(TOKEN_IDENTIFIER);
  expect(TOKEN_INDENT);
  expect(TOKEN_IDENTIFIER);
  expect(TOKEN_DEDENT);
  expect(TOKEN_EOF);

  initScanner("class Foo\n"
              "\t// comment\n"
              "\tbar");
  expect(TOKEN_CLASS);
  expect(TOKEN_IDENTIFIER);
  expect(TOKEN_INDENT);
  expect(TOKEN_IDENTIFIER);
  expect(TOKEN_DEDENT);
  expect(TOKEN_EOF);

  initScanner("class Foo\t// comment line 1\n"
              "\t\t\t// comment line 2\n"
              "\t\t// comment line 3\n"
              "\tbar");
  expect(TOKEN_CLASS);
  expect(TOKEN_IDENTIFIER);
  expect(TOKEN_INDENT);
  expect(TOKEN_IDENTIFIER);
  expect(TOKEN_DEDENT);
  expect(TOKEN_EOF);

  initScanner("class Foo\n"
              "\t\n"
              "\tfn bar(x)\n"
              "\t\treturn x\n"
              "let x = 1");
  expect(TOKEN_CLASS);
  expect(TOKEN_IDENTIFIER);
  expect(TOKEN_INDENT);
  expect(TOKEN_FN);
  expect(TOKEN_IDENTIFIER);
  expect(TOKEN_LEFT_PAREN);
  expect(TOKEN_IDENTIFIER);
  expect(TOKEN_RIGHT_PAREN);
  expect(TOKEN_INDENT);
  expect(TOKEN_RETURN);
  expect(TOKEN_IDENTIFIER);
  expect(TOKEN_DEDENT);
  expect(TOKEN_DEDENT);
  expect(TOKEN_LET);
  expect(TOKEN_IDENTIFIER);
  expect(TOKEN_EQUAL);
  expect(TOKEN_NUMBER);
  expect(TOKEN_EOF);
}
