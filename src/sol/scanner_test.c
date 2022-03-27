#include <assert.h>

#include "debug.h"
#include "lib.h"
#include "scanner.h"

#define expect(token) assert(scanToken().type == token)

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
  expect(TOKEN_NEWLINE);
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
  expect(TOKEN_INDENT);
  expect(TOKEN_DEDENT);
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
}
