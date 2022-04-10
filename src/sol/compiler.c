#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "common.h"
#include "compiler.h"
#include "memory.h"
#include "scanner.h"
#include "string.h"

#if defined(DEBUG_PRINT_CODE) || defined(DEBUG_TOKENS)
#include "debug.h"
#endif

typedef struct {
  Token current;
  Token previous;
  bool hadError;
  bool panicMode;
} Parser;

typedef enum {
  PREC_NONE,
  PREC_SEMI,       // ; NEWLINE
  PREC_COMMA,      // ,
  PREC_ASSIGNMENT, // = += -= /= *=
  PREC_OR,         // or
  PREC_AND,        // and
  PREC_EQUALITY,   // == !=
  PREC_COMPARISON, // < > <= >=
  PREC_TERM,       // + -
  PREC_FACTOR,     // * /
  PREC_RANGE,      // ..
  PREC_PREFIX,     // ! - ++ -- aka PREC_UNARY
  PREC_POSTFIX,    // ++ --
  PREC_CALL,       // . ()
  PREC_PRIMARY
} Precedence;

typedef void (*ParseFn)(bool canAssign);

typedef struct {
  ParseFn prefix;
  ParseFn infix; // AKA "postfix"
  Precedence precedence;
} ParseRule;

/** A variable defined deeper than the global scope. */
typedef struct {
  Token name;      /** Name of the local variable. */
  int depth;       /** How many scopes deep this local is. -1 until defined. */
  bool isCaptured; /** Has a closure captured this local? */
} Local;

/** A local variable that has been closed over by a function. */
typedef struct {
  uint8_t index; /** The local slot being closed over. */
  bool isLocal;  /** Local slot or enclosing upvalue? */
} Upvalue;

typedef enum FunType {
  TYPE_CLASS,
  TYPE_FUNCTION,
  TYPE_INIT,
  TYPE_METHOD,
  TYPE_SCRIPT
} FunType;

/**
 * Every function gets its own Compiler.
 * The root compiler gets an anonymous function with name "".
 */
typedef struct Compiler {
  struct Compiler *enclosing; /** Compiler of the scope enclosing this one. */
  ObjFun *fun;                /** The function being compiled. */
  FunType type; /** Regular function or a script (root-level anon function). */

  /**
   * Stack of local variables.
   *
   * During runtime, local variables are all that stays on the stack.
   * So, the vm's stack will have the same indexes as these locals,
   * and we can share offsets directly.
   */
  Local locals[UINT8_COUNT];
  int localCount;                /** Number of locals currently in scope. */
  Upvalue upvalues[UINT8_COUNT]; /** Variables this compiler has closed over. */
  int scopeDepth; /** How many times beginScope() has been called. */
} Compiler;

/** The current, innermost class being compiled. */
typedef struct ClassCompiler {
  struct ClassCompiler *enclosing;
  Table fields;
} ClassCompiler;

Parser parser;
Compiler *current = NULL;
ClassCompiler *currentClass = NULL;
Chunk *compilingChunk;

static void pushClassCompiler(ClassCompiler *comp) {
  comp->enclosing = currentClass;
  initTable(&comp->fields);
  currentClass = comp;
}

static void popClassCompiler() {
  freeTable(&currentClass->fields);
  currentClass = currentClass->enclosing;
}

static Chunk *currentChunk() { return &current->fun->chunk; }

static Value identifierValue(Token *name) {
  return OBJ_VAL(copyString(name->start, name->length));
}

static void errorAt(Token *token, const char *message) {
  if (parser.panicMode)
    return;

  parser.panicMode = true;
  fprintf(stderr, "[line %d] Error", token->line);

  if (token->type == TOKEN_EOF) {
    fprintf(stderr, " at end");
  } else if (token->type == TOKEN_ERROR) {
    // Nothing.
  } else {
    fprintf(stderr, " at '%.*s'", token->length, token->start);
  }

  fprintf(stderr, ": %s\n", message);
  parser.hadError = true;
}

static void error(const char *message) { errorAt(&parser.previous, message); }

static void errorAtCurrent(const char *message) {
  errorAt(&parser.current, message);
}

static void advance() {
  parser.previous = parser.current;
  for (;;) {
    parser.current = scanToken();
    if (parser.current.type != TOKEN_ERROR)
      break;

    errorAtCurrent(parser.current.start);
  }
}

/** Is this the type of the previous token? */
static bool check(TokenType type) { return parser.current.type == type; }

/** Check the previous token and consume if it matches. */
static bool match(TokenType type) {
  if (!check(type))
    return false;

  advance();
  return true;
}

/** The previous token must be this type, otherwise error. */
static void consume(TokenType type, const char *message) {
  if (parser.current.type == type) {
    advance();
    return;
  }

  errorAtCurrent(message);
}

static void skipTerminators() {
  while (match(TOKEN_NEWLINE) || match(TOKEN_SEMICOLON)) {
  }
}

static void consumeAtLeast(TokenType type, const char *message) {
  if (parser.current.type >= type) {
    advance();
    return;
  }

  errorAtCurrent(message);
}

static Value consumeIdent(const char *message) {
  consumeAtLeast(TOKEN_IDENTIFIER, message);
  return identifierValue(&parser.previous);
}

static void consumeTerminator(const char *message) {
  if (!match(TOKEN_NEWLINE))
    consume(TOKEN_SEMICOLON, message);

  skipTerminators();
}

static void emitByte(uint8_t byte) {
  writeChunk(currentChunk(), byte, parser.previous.line);
}

static void emitBytes(uint8_t byte1, uint8_t byte2) {
  emitByte(byte1);
  emitByte(byte2);
}

static void emitLoop(int loopStart) {
  emitByte(OP_LOOP);
  int offset = currentChunk()->count - loopStart + 2;
  if (offset > UINT16_MAX)
    error("Loop body too large.");

  emitBytes((offset >> 8) & 0xff, offset & 0xff);
}

static void patchByte(uint8_t byte, int offset) {
  currentChunk()->code[offset] = byte;
}

static void patchBytes(uint8_t byte1, uint8_t byte2, int offset) {
  patchByte(byte1, offset);
  patchByte(byte2, offset + 1);
}

/**
 * Emits the given JUMP command with a temp `short` operand.
 * Returns the offset pointing to the start of the `short`.
 */
static int emitJump(uint8_t instruction) {
  emitByte(instruction);
  emitBytes(0xff, 0xff);
  return currentChunk()->count - 2;
}

static void emitSwap(uint8_t a, uint8_t b) {
  emitBytes(OP_SWAP, (a << 4) | (b & 0x0f));
}

static void emitReturn() {
  switch (current->type) {
  case TYPE_INIT:
  case TYPE_CLASS:
    emitBytes(OP_GET_LOCAL, 0); // init() methods always return self.
    break;
  default:
    emitByte(OP_NIL);
  }

  emitByte(OP_RETURN);
}

/** Puts the given value in the constant table and returns its index. */
static uint8_t makeConstant(Value value) {
  int constant = addConstant(currentChunk(), value);
  if (constant > UINT8_MAX) {
    error("Too many constants in one chunk.");
    return 0;
  }

  return (uint8_t)constant;
}

/**
 * Puts the given value in the constant table and writes an instruction
 * to push it onto the VM stack.
 */
static void emitConstant(Value value) {
  emitBytes(OP_CONSTANT, makeConstant(value));
}

static void emitDefault(Value value) {
  emitBytes(OP_DEFAULT, makeConstant(value));
}

/**
 * Patches a previously emitted JUMP instruction at the given offset.
 * The new jump operand will point to the next instruction that is
 * emitted after this call to `patchJump`.
 */
static void patchJump(int offset) {
  // -2 to adjust for the jump offset itself.
  int jump = currentChunk()->count - offset - 2;

  if (jump > UINT16_MAX) {
    // Todo: JUMP_*_32
    error("Too much code to jump over.");
  }

  patchBytes((jump >> 8) & 0xff, jump & 0xff, offset);
}

static void initCompiler(Compiler *compiler, FunType type) {
  compiler->fun = NULL;
  compiler->fun = newFunction();
  compiler->type = type;
  compiler->localCount = 0;
  compiler->scopeDepth = 0;
  compiler->enclosing = current;
  current = compiler;

  current->fun->name =
      // Todo: Pass in name
      type == TYPE_SCRIPT ? newString("_script_")
      : type == TYPE_CLASS
          ? newString("init")
          : copyString(parser.previous.start, parser.previous.length);

  // Reserve first local for `this`.
  Local *self = &current->locals[current->localCount++];
  self->depth = 0;
  self->isCaptured = false;

  if (type != TYPE_FUNCTION) {
    self->name.start = "this";
    self->name.length = 4;
  } else {
    self->name.start = "";
    self->name.length = 0;
  }
}

static ObjFun *endCompiler() {
  emitReturn();
  ObjFun *fun = current->fun;

#ifdef DEBUG_PRINT_CODE
  if (!parser.hadError) {
    disassembleChunk(currentChunk(),
                     fun->name != NULL ? fun->name->chars : "<script>");
  }
#endif

  current = current->enclosing;
  return fun;
}

static void beginScope() { current->scopeDepth++; }
static void endScope() {
  current->scopeDepth--;

  // Count all locals below our new scopeDepth.
  while (current->localCount > 0 &&
         current->locals[current->localCount - 1].depth > current->scopeDepth) {
    if (current->locals[current->localCount - 1].isCaptured)
      emitByte(OP_CLOSE_UPVALUE);
    else
      emitByte(OP_POP);
    current->localCount--;
  }
}

static void expression();
static void statement();
static void declaration();
static ParseRule *getRule(TokenType type);
static void parsePrecedence(Precedence precedence);

/** Adds the token to the constants table. */
static uint8_t identifierConstant(Token *name) {
  return makeConstant(identifierValue(name));
}

/** Do these tokens have the same source string? */
static bool identifiersEqual(Token *a, Token *b) {
  if (a->length != b->length)
    return false;

  return memcmp(a->start, b->start, a->length) == 0;
}

/** Turns a Token name into a local slot index. */
static int resolveLocal(Compiler *compiler, Token *name) {
  for (int i = compiler->localCount - 1; i >= 0; i--) {
    Local *local = &compiler->locals[i];
    if (identifiersEqual(name, &local->name)) {
      if (local->depth == -1)
        error("Can't read local variable in its own initializer.");

      return i;
    }
  }

  // The variable with this name must be global.
  return -1;
}

/**
 * Add a new upvalue to the compiler's array of upvalues.
 *
 * @param index Slot index of the local variable we are closing over.
 */
static int addUpvalue(Compiler *compiler, uint8_t index, bool isLocal) {
  int upvalueCount = compiler->fun->upvalueCount;

  // Re-use existing upvalues referring to the same slot index.
  for (int i = 0; i < upvalueCount; i++) {
    Upvalue *upvalue = &compiler->upvalues[i];
    if (upvalue->index == index && upvalue->isLocal == isLocal)
      return i;
  }

  if (upvalueCount == UINT8_COUNT) {
    error("Too many closure variables in function.");
    return 0;
  }

  compiler->upvalues[upvalueCount].isLocal = isLocal;
  compiler->upvalues[upvalueCount].index = index;

  // Increment the current function's upvalueCount.
  return compiler->fun->upvalueCount++;
}

/**
 * Returns an "upvalue index" for the upvalue with the given name.
 * Returns -1 if not found.
 */
static int resolveUpvalue(Compiler *compiler, Token *name) {
  // Root compiler has no locals or upvalues. Exit.
  if (compiler->enclosing == NULL)
    return -1;

  // Close over a local variable in the enclosing scope.
  int local = resolveLocal(compiler->enclosing, name);
  if (local != -1) {
    compiler->enclosing->locals[local].isCaptured = true;
    return addUpvalue(compiler, (uint8_t)local, true);
  }

  // Close over an upvalue in the enclosing scope.
  int upvalue = resolveUpvalue(compiler->enclosing, name);
  if (upvalue != -1)
    return addUpvalue(compiler, (uint8_t)upvalue, false);

  // Not found, must be global.
  return -1;
}

/** Adds a local variable with the given name to the current compiler scope. */
static void addLocal(Token name) {
  if (current->localCount == UINT8_COUNT) {
    error("Too many local variables in function.");
    return;
  }

  Local *local = &current->locals[current->localCount++];
  local->name = name;
  local->depth = -1; // Set properly when initialized.
  local->isCaptured = false;
}

/**
 * Creates a local variable named by the previous token.
 * Errors if the name shadows an existing local variable.
 *
 * Returns false if the variable is global.
 */
static bool declareVariable() {
  if (current->scopeDepth == 0)
    return false; // We're in the global scope.

  Token *name = &parser.previous;

  for (int i = current->localCount - 1; i >= 0; i--) {
    Local *local = &current->locals[i];
    if (local->depth != -1 && local->depth < current->scopeDepth)
      break;

    if (identifiersEqual(name, &local->name)) {
      error("Already a variable with this name in this scope.");
    }
  }

  addLocal(*name);
  return true;
}

/**
 * Parse a variable name and _declare_ it.
 *
 * _Declaring_ a local variable reserves its slot in the compiler, but
 * referencing it before it is _defined_ is an error.
 */
static uint8_t parseVariable(const char *errorMessage) {
  consume(TOKEN_IDENTIFIER, errorMessage);

  declareVariable();
  if (current->scopeDepth > 0)
    return 0;

  return identifierConstant(&parser.previous);
}

/**
 * Mark the most recently _declared_ local variable as _defined_.
 * Global variables are _defined_ at runtime via OP_DEFINE_GLOBAL.
 *
 * Undefined locals have a depth of -1.
 */
static void markDefined() {
  if (current->scopeDepth == 0)
    return;

  current->locals[current->localCount - 1].depth = current->scopeDepth;
}

/**
 * _Defines_ a variable using the most recent stack value.
 *
 * In the global scope, define the global identified by the given constant id.
 * Otherwise, define the most recently declared local.
 *
 * At runtime, local variables point to that value on the stack, and global
 * variables pop the value and put in the the globals table.
 */
static void defineVariable(uint8_t global) {
  if (current->scopeDepth > 0) {
    markDefined();
    return;
  }
  emitBytes(OP_DEFINE_GLOBAL, global);
}

/** Parse arguments being passed to a function. */
static uint8_t argumentList() {
  uint8_t argCount = 0;
  if (!check(TOKEN_RIGHT_PAREN)) {
    do {
      parsePrecedence(PREC_ASSIGNMENT);
      if (argCount == 255)
        error("Can't have more than 255 arguments.");
      argCount++;
    } while (match(TOKEN_COMMA));
  }
  consume(TOKEN_RIGHT_PAREN, "Expect ')' after arguments.");
  return argCount;
}

static void and_(bool canAssign) {
  int endJump = emitJump(OP_JUMP_IF_FALSE);
  emitByte(OP_POP);
  parsePrecedence(PREC_AND);
  patchJump(endJump);
}

/**
 * `binary` means the setOp and getOp require the current value
 * on the stack to function properly.
 */
static bool assignment(OpCode getOp, OpCode setOp, uint8_t arg, bool binary) {
  TokenType type = parser.current.type;

  switch (type) {
  case TOKEN_EQUAL:
    advance();
    expression();
    emitBytes(setOp, arg);
    return true;

  case TOKEN_PLUS_PLUS:
  case TOKEN_MINUS_MINUS:
    advance();

    // We need the last stack value to call get/set
    // Todo: implement assignment via ObjUpvalue?
    //       push the upvalue/value onto the stack. call OP_GET/OP_SET
    if (binary) {                 // [<inst>]
      emitBytes(OP_PEEK, 0);      // [<inst>][<inst>]
      emitBytes(getOp, arg);      // [<inst>][value]
      emitDefault(NUMBER_VAL(0)); // [<inst>][value ?? 0]
      emitSwap(0, 1);             // [value][<inst>]
      emitBytes(OP_PEEK, 1);      // [value][<inst>][value]
    } else {
      emitBytes(getOp, arg);      // [value]
      emitDefault(NUMBER_VAL(0)); // [value ?? 0]
      emitBytes(OP_PEEK, 0);      // [value][value]
    }

    emitConstant(NUMBER_VAL(1));
    emitByte(type == TOKEN_PLUS_PLUS ? OP_ADD : OP_SUBTRACT);
    emitBytes(setOp, arg);
    emitByte(OP_POP);
    return true;

  case TOKEN_PLUS_EQUAL:
  case TOKEN_MINUS_EQUAL:
  case TOKEN_SLASH_EQUAL:
  case TOKEN_STAR_EQUAL:
    advance();

    if (binary)
      emitBytes(OP_PEEK, 0);

    emitBytes(getOp, arg);
    emitDefault(NUMBER_VAL(0));
    expression();

    emitByte(type == TOKEN_PLUS_EQUAL    ? OP_ADD
             : type == TOKEN_MINUS_EQUAL ? OP_SUBTRACT
             : type == TOKEN_SLASH_EQUAL ? OP_DIVIDE
                                         : OP_MULTIPLY);

    emitBytes(setOp, arg);
    return true;

  default:
    break;
  }

  // Could not assign.
  return false;
}

static void binary(bool canAssign) {
  TokenType operatorType = parser.previous.type;
  ParseRule *rule = getRule(operatorType);
  parsePrecedence((Precedence)(rule->precedence + 1));

  switch (operatorType) {
  case TOKEN_DOT_DOT:
    emitByte(OP_RANGE);
    break;

  case TOKEN_BANG_EQUAL:
    emitBytes(OP_EQUAL, OP_NOT);
    break;
  case TOKEN_EQUAL_EQUAL:
    emitByte(OP_EQUAL);
    break;

  case TOKEN_GREATER:
    emitByte(OP_GREATER);
    break;
  case TOKEN_GREATER_EQUAL:
    emitBytes(OP_LESS, OP_NOT);
    break;

  case TOKEN_LESS:
    emitByte(OP_LESS);
    break;
  case TOKEN_LESS_EQUAL:
    emitBytes(OP_GREATER, OP_NOT);
    break;

  case TOKEN_PLUS:
    emitByte(OP_ADD);
    break;
  case TOKEN_MINUS:
    emitByte(OP_SUBTRACT);
    break;
  case TOKEN_STAR:
    emitByte(OP_MULTIPLY);
    break;
  case TOKEN_SLASH:
    emitByte(OP_DIVIDE);
    break;
  default:
    return;
  }
}

static void call(bool canAssign) {
  uint8_t argCount = argumentList();
  emitBytes(OP_CALL, argCount);
}

static void comma(bool canAssign) {
  uint8_t length = 1;
  do {
    parsePrecedence(PREC_ASSIGNMENT);
    length++;
  } while (match(TOKEN_COMMA));

  emitBytes(OP_TUPLE, length);
}

static void dot(bool canAssign) {
  uint8_t name = makeConstant(consumeIdent("Expect property name after '.'."));

  if (canAssign && assignment(OP_GET_PROPERTY, OP_SET_PROPERTY, name, true))
    return;

  else if (match(TOKEN_LEFT_PAREN)) {
    uint8_t argCount = argumentList();
    emitBytes(OP_INVOKE, name);
    emitByte(argCount);
  } else
    emitBytes(OP_GET_PROPERTY, name);
}

static void literal(bool canAssign) {
  switch (parser.previous.type) {
  case TOKEN_FALSE:
    emitByte(OP_FALSE);
    break;
  case TOKEN_NIL:
    emitByte(OP_NIL);
    break;
  case TOKEN_TRUE:
    emitByte(OP_TRUE);
    break;
  default: // Unreachable.
    return;
  }
}

static void grouping(bool canAssign) {
  expression();
  consume(TOKEN_RIGHT_PAREN, "Expect ')' after expression.");
}

static void number(bool canAssign) {
  double value = strtod(parser.previous.start, NULL);
  emitConstant(NUMBER_VAL(value));
}

static void or_(bool canAssign) {
  int elseJump = emitJump(OP_JUMP_IF_FALSE);
  int endJump = emitJump(OP_JUMP);

  patchJump(elseJump);
  emitByte(OP_POP);
  parsePrecedence(PREC_OR);
  patchJump(endJump);
}

static void string(bool canAssign) {
  // Todo: translate escape sequences (\n ...)
  emitConstant(OBJ_VAL(
      copyString(parser.previous.start + 1, parser.previous.length - 2)));
}

static void symbol(bool canAssign) {
  emitConstant(OBJ_VAL(
      copyString(parser.previous.start + 1, parser.previous.length - 1)));
}

/**
 * Emits bytecode to read the variable with the given Token name from the
 * current scope.
 *
 * Will also parse any following assignment operators if canAssign is true.
 */
static void namedVariable(Token name, bool canAssign) {
  uint8_t getOp, setOp;
  int arg = resolveLocal(current, &name);

  if (arg != -1) {
    getOp = OP_GET_LOCAL;
    setOp = OP_SET_LOCAL;
  } else if ((arg = resolveUpvalue(current, &name)) != -1) {
    getOp = OP_GET_UPVALUE;
    setOp = OP_SET_UPVALUE;
  } else {
    arg = identifierConstant(&name);
    getOp = OP_GET_GLOBAL;
    setOp = OP_SET_GLOBAL;
  }

  if (canAssign && assignment(getOp, setOp, arg, false))
    return;

  emitBytes(getOp, arg);
}

static void variable(bool canAssign) {
  namedVariable(parser.previous, canAssign);
}

static Token syntheticToken(const char *text) {
  Token token;
  token.start = text;
  token.length = (int)strlen(text);
  return token;
}

static void super_(bool canAssign) {
  if (currentClass == NULL) {
    error("Can't use 'super' outside of a class.");
  }

  // Todo: super() calls the current method.
  consume(TOKEN_DOT, "Expect '.' after 'super'.");
  consume(TOKEN_IDENTIFIER, "Expect superclass method name.");
  uint8_t name = identifierConstant(&parser.previous);

  namedVariable(syntheticToken("this"), false);

  if (match(TOKEN_LEFT_PAREN)) {
    uint8_t argCount = argumentList();
    namedVariable(syntheticToken("super"), false);
    emitBytes(OP_SUPER_INVOKE, name);
    emitByte(argCount);
  } else {
    namedVariable(syntheticToken("super"), false);
    emitBytes(OP_GET_SUPER, name);
  }
}

static void this_(bool canAssign) {
  if (currentClass == NULL) {
    error("Can't use 'this' outside of a class.");
    return;
  }
  variable(false);
}

// aka unary()
static void prefix(bool canAssign) {
  TokenType operatorType = parser.previous.type;

  // Compile the operand.
  parsePrecedence(PREC_PREFIX);

  // Emit the operator instruction.
  switch (operatorType) {
  case TOKEN_BANG:
    emitByte(OP_NOT);
    break;
  case TOKEN_MINUS:
    emitByte(OP_NEGATE);
    break;
  default:
    return; // Unreachable.
  }
}

static void postfix(bool canAssign) {
  TokenType operatorType = parser.previous.type;

  switch (operatorType) {
  // case TOKEN_BANG:
  // case TOKEN_QUEST:
  default:
    return;
  }
}

ParseRule rules[] = {
    [TOKEN_LEFT_PAREN] = {grouping, call, PREC_CALL},
    [TOKEN_RIGHT_PAREN] = {NULL, NULL, PREC_NONE},
    [TOKEN_LEFT_BRACE] = {NULL, NULL, PREC_NONE},
    [TOKEN_RIGHT_BRACE] = {NULL, NULL, PREC_NONE},
    [TOKEN_COMMA] = {NULL, comma, PREC_COMMA},
    [TOKEN_DOT] = {NULL, dot, PREC_CALL},
    [TOKEN_DOT_DOT] = {NULL, binary, PREC_RANGE},
    [TOKEN_SEMICOLON] = {NULL, NULL, PREC_NONE},

    [TOKEN_MINUS] = {prefix, binary, PREC_TERM},
    [TOKEN_MINUS_EQUAL] = {NULL, NULL, PREC_ASSIGNMENT},
    [TOKEN_PLUS] = {NULL, binary, PREC_TERM},
    [TOKEN_PLUS_EQUAL] = {NULL, NULL, PREC_ASSIGNMENT},
    [TOKEN_SLASH] = {NULL, binary, PREC_FACTOR},
    [TOKEN_SLASH_EQUAL] = {NULL, NULL, PREC_ASSIGNMENT},
    [TOKEN_STAR] = {NULL, binary, PREC_FACTOR},
    [TOKEN_STAR_EQUAL] = {NULL, NULL, PREC_ASSIGNMENT},

    [TOKEN_PLUS_PLUS] = {prefix, postfix, PREC_NONE},
    [TOKEN_MINUS_MINUS] = {prefix, postfix, PREC_NONE},

    [TOKEN_BANG] = {prefix, NULL, PREC_NONE},
    [TOKEN_BANG_EQUAL] = {NULL, binary, PREC_EQUALITY},
    [TOKEN_EQUAL] = {NULL, NULL, PREC_NONE},
    [TOKEN_EQUAL_EQUAL] = {NULL, binary, PREC_EQUALITY},
    [TOKEN_GREATER] = {NULL, binary, PREC_COMPARISON},
    [TOKEN_GREATER_EQUAL] = {NULL, binary, PREC_COMPARISON},
    [TOKEN_LESS] = {NULL, binary, PREC_COMPARISON},
    [TOKEN_LESS_EQUAL] = {NULL, binary, PREC_COMPARISON},

    [TOKEN_IDENTIFIER] = {variable, NULL, PREC_NONE},
    [TOKEN_STRING] = {string, NULL, PREC_NONE},
    [TOKEN_SYMBOL] = {symbol, NULL, PREC_NONE},
    [TOKEN_NUMBER] = {number, NULL, PREC_NONE},

    [TOKEN_AND] = {NULL, and_, PREC_AND},
    [TOKEN_CLASS] = {NULL, NULL, PREC_NONE},
    [TOKEN_ELSE] = {NULL, NULL, PREC_NONE},
    [TOKEN_FALSE] = {literal, NULL, PREC_NONE},
    [TOKEN_FOR] = {NULL, NULL, PREC_NONE},
    [TOKEN_FN] = {NULL, NULL, PREC_NONE},
    [TOKEN_IF] = {NULL, NULL, PREC_NONE},
    [TOKEN_NIL] = {literal, NULL, PREC_NONE},
    [TOKEN_OR] = {NULL, or_, PREC_OR},
    [TOKEN_PRINT] = {NULL, NULL, PREC_NONE},
    [TOKEN_RETURN] = {NULL, NULL, PREC_NONE},
    [TOKEN_SUPER] = {super_, NULL, PREC_NONE},
    [TOKEN_THIS] = {this_, NULL, PREC_NONE},
    [TOKEN_TRUE] = {literal, NULL, PREC_NONE},
    [TOKEN_LET] = {NULL, NULL, PREC_NONE},
    [TOKEN_WHILE] = {NULL, NULL, PREC_NONE},

    [TOKEN_ERROR] = {NULL, NULL, PREC_NONE},
    [TOKEN_EOF] = {NULL, NULL, PREC_NONE},
};

static void parsePrecedence(Precedence precedence) {
  advance();
  ParseRule *rule = getRule(parser.previous.type);
  ParseFn prefix = rule->prefix;
  if (prefix == NULL) {
    error("Expect expression.");
    return;
  }

  // Todo: Get rid of `canAssign`.
  bool canAssign = precedence <= PREC_ASSIGNMENT;
  prefix(canAssign);

  while (precedence <= getRule(parser.current.type)->precedence) {
    advance();
    ParseFn infix = getRule(parser.previous.type)->infix;
    infix(canAssign);
  }

  if (canAssign && match(TOKEN_EQUAL)) {
    error("Invalid assignment target.");
  }
}

static ParseRule *getRule(TokenType type) { return &rules[type]; }

static void expression() { parsePrecedence(PREC_COMMA); }

// Todo: Block-as-expression + yield/break keyword
static void block() {
  while (!check(TOKEN_DEDENT) && !check(TOKEN_EOF)) {
    declaration();
  }

  consume(TOKEN_DEDENT, "Expect dedent after block.");
}

static void function(FunType type) {
  Compiler compiler;
  initCompiler(&compiler, type);
  beginScope();

  if (match(TOKEN_LEFT_PAREN)) {
    if (!check(TOKEN_RIGHT_PAREN)) {
      do {
        current->fun->arity++;
        if (current->fun->arity > 255)
          errorAtCurrent("Can't have more than 255 parameters.");

        uint8_t constant = parseVariable("Expect parameter name.");
        defineVariable(constant);
        trace("parameter", NUMBER_VAL(constant));

      } while (match(TOKEN_COMMA));
    }

    consume(TOKEN_RIGHT_PAREN, "Expect ')' after parameters.");
  }

  if (type == TYPE_CLASS) {
    trace("TYPE_CLASS", TRUE_VAL);
    trace("localCount", NUMBER_VAL(current->localCount));
    // Inline init
    for (int i = 1; i < current->localCount; i++) {

      Value name = identifierValue(&current->locals[i].name);
      trace("local", name);
      u8 constant = makeConstant(name);
      tableSet(&currentClass->fields, name, TRUE_VAL);
      emitBytes(OP_GET_LOCAL, 0); // self
      emitBytes(OP_GET_LOCAL, i); // value
      emitBytes(OP_SET_PROPERTY, constant);
      emitByte(OP_POP); // Pop the value
    }
  } else if (match(TOKEN_FAT_ARROW)) {
    expression();
    emitByte(OP_RETURN);
    consumeTerminator("Expect newline or ';' after arrow function.");
  } else if (match(TOKEN_INDENT)) {
    block();
  }

  // no endScope(). Compiler will be deallocated.
  ObjFun *fun = endCompiler();
  emitBytes(OP_CLOSURE, makeConstant(OBJ_VAL(fun)));

  for (int i = 0; i < fun->upvalueCount; i++) {
    emitByte(compiler.upvalues[i].isLocal ? 1 : 0);
    emitByte(compiler.upvalues[i].index);
  }
}

static void method() {
  consumeIdent("Expect method name.");

  uint8_t constant = identifierConstant(&parser.previous);
  FunType type = TYPE_METHOD;
  if (parser.previous.length == 4 &&
      memcmp(parser.previous.start, "init", 4) == 0) {
    type = TYPE_INIT;
  }

  function(type);
  emitBytes(OP_METHOD, constant);
}

static void classDeclaration() {
  Value name = consumeIdent("Expect class name.");
  Token className = parser.previous;
  uint8_t nameConstant = makeConstant(name);

  bool isLocal = declareVariable();
  emitBytes(OP_CLASS, nameConstant);
  emitByte(isLocal);

  if (isLocal)
    markDefined();

  ClassCompiler classCompiler;
  pushClassCompiler(&classCompiler);

  // Parse inline init
  if (check(TOKEN_LEFT_PAREN)) {
    function(TYPE_CLASS);
    Value init = OBJ_VAL(newString("init"));
    emitBytes(OP_METHOD, makeConstant(init));
  }

  if (match(TOKEN_LESS)) {
    // expression();
    consume(TOKEN_IDENTIFIER, "Expect superclass name.");
    variable(false);

    if (identifiersEqual(&className, &parser.previous)) {
      error("A class can't inherit from itself.");
    }
  } else {
    namedVariable(syntheticToken("Object"), false);
  }

  beginScope();
  addLocal(syntheticToken("super"));
  defineVariable(0);

  emitByte(OP_INHERIT);
  emitSwap(0, 1); // [1 class][0 super] -> [1 super][0 class]

  if (match(TOKEN_INDENT)) {
    while (!check(TOKEN_DEDENT) && !check(TOKEN_EOF))
      method();

    consume(TOKEN_DEDENT, "Expect dedent after class body.");
  } else {
    skipTerminators();
  }

  emitByte(OP_POP); // Pop the class
  endScope();       // Pops local vars, including "super"
  popClassCompiler();
}

static void funDeclaration() {
  uint8_t global = parseVariable("Expect function name.");
  markDefined();
  function(TYPE_FUNCTION);
  defineVariable(global);
}

static void varDeclaration() {
  uint8_t global = parseVariable("Expect variable name.");

  if (match(TOKEN_EQUAL)) {
    expression();
  } else {
    emitByte(OP_NIL);
  }

  consumeTerminator("Expect newline or ';' after variable declaration.");

  defineVariable(global);
}

static void expressionStatement() {
  expression();

  consumeTerminator("Expect newline or ';' after expression");
  // // Better in the REPL.
  // emitByte(match(TOKEN_SEMICOLON) ? OP_POP : OP_PRINT);
}

// for ;;i++:
static void forStatement() {
  beginScope();
  // Todo: for-in loops
  // for x in 1..5:
  // uint8_t global = parseVariable("Expect variable after 'for'.");
  // consume(TOKEN_IN, "Expect 'in' after variable in for clause.");

  if (match(TOKEN_SEMICOLON)) {
    // No initializer.
  } else if (match(TOKEN_LET)) {
    varDeclaration();
  } else {
    expressionStatement();
  }

  int loopStart = currentChunk()->count;
  int exitJump = -1;

  if (!match(TOKEN_SEMICOLON)) {
    expression();
    consume(TOKEN_SEMICOLON, "Expect ';' after loop condition.");

    // Jump out of the loop if condition is false.
    exitJump = emitJump(OP_JUMP_IF_FALSE);
    emitByte(OP_POP); // Condition.
  }

  if (check(TOKEN_INDENT) || match(TOKEN_COLON)) {
    // No increment.
  } else {
    int bodyJump = emitJump(OP_JUMP);
    int incrementStart = currentChunk()->count;

    expression();
    emitByte(OP_POP);

    if (!check(TOKEN_INDENT))
      consume(TOKEN_COLON, "Expect ':' or indentation after for clause.");

    emitLoop(loopStart);
    loopStart = incrementStart;
    patchJump(bodyJump);
  }

  statement();
  emitLoop(loopStart);

  if (exitJump != -1) {
    patchJump(exitJump);
    emitByte(OP_POP); // Condition.
  }

  endScope();
}

static void ifStatement() {
  expression();

  if (!check(TOKEN_INDENT))
    consume(TOKEN_COLON, "Expect ':' or block after condition.");

  int thenJump = emitJump(OP_JUMP_IF_FALSE);
  emitByte(OP_POP);
  statement();

  int elseJump = emitJump(OP_JUMP);
  patchJump(thenJump);
  emitByte(OP_POP);

  if (match(TOKEN_ELSE))
    statement();

  patchJump(elseJump);
}

static void printStatement() {
  expression();
  consumeTerminator("Expect newline or ';' after value.");
  emitByte(OP_PRINT);
}

static void returnStatement() {
  // Note: I like the idea of top-level returns to exit early.
  // if (current->type == TYPE_SCRIPT)
  //   error("Can't return from top-level code.");

  if (match(TOKEN_SEMICOLON) || match(TOKEN_NEWLINE))
    emitReturn();
  else {
    if (current->type == TYPE_INIT) {
      error("Can't return a value from init().");
    }

    expression();
    consumeTerminator("Expect newline or ';' after return value.");
    emitByte(OP_RETURN);
  }
}

static void whileStatement() {
  int loopStart = currentChunk()->count;
  expression();

  if (!check(TOKEN_INDENT))
    consume(TOKEN_COLON, "Expect ':' or block after condition.");

  int exitJump = emitJump(OP_JUMP_IF_FALSE);
  emitByte(OP_POP);
  statement();
  emitLoop(loopStart);
  patchJump(exitJump);
  emitByte(OP_POP);
}

static void synchronize() {
  parser.panicMode = false;

  while (parser.current.type != TOKEN_EOF) {
    if (parser.previous.type == TOKEN_SEMICOLON)
      return;

    if (parser.previous.type == TOKEN_NEWLINE)
      return;

    switch (parser.current.type) {
    case TOKEN_CLASS:
    case TOKEN_FN:
    case TOKEN_LET:
    case TOKEN_FOR:
    case TOKEN_IF:
    case TOKEN_WHILE:
    case TOKEN_PRINT:
    case TOKEN_RETURN:
      return;
    default:; // Do nothing.
    }

    advance();
  }
}

static void declaration() {
  if (match(TOKEN_CLASS)) {
    classDeclaration();
  } else if (match(TOKEN_FN)) {
    funDeclaration();
  } else if (match(TOKEN_LET)) {
    varDeclaration();
  } else {
    statement();
  }

  if (parser.panicMode)
    synchronize();
}

static void statement() {
  if (match(TOKEN_PRINT)) {
    printStatement();
  } else if (match(TOKEN_INDENT)) {
    beginScope();
    block();
    endScope();
  } else if (match(TOKEN_FOR)) {
    forStatement();
  } else if (match(TOKEN_IF)) {
    ifStatement();
  } else if (match(TOKEN_RETURN)) {
    returnStatement();
  } else if (match(TOKEN_WHILE)) {
    whileStatement();
  } else {
    expressionStatement();
  }
  // Todo: switch statement
  // Todo: break statement
  // Todo: continue statement
}

ObjFun *compile(const char *source) {
  initScanner(source);

#ifdef DEBUG_TOKENS
  debugTokens();
#endif

  Compiler compiler;
  initCompiler(&compiler, TYPE_SCRIPT);

  parser.hadError = false;
  parser.panicMode = false;

  advance();

  while (!match(TOKEN_EOF)) {
    declaration();
  }

  ObjFun *fun = endCompiler();
  return parser.hadError ? NULL : fun;
}

void markCompilerRoots() {
  Compiler *compiler = current;

  while (compiler != NULL) {
    markObject((Obj *)compiler->fun);
    compiler = compiler->enclosing;
  }
}
