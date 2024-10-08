#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "common.h"
#include "compiler.h"
#include "debug.h"
#include "memory.h"
#include "scanner.h"
#include "string.h"
#include "term.h"

#if ENABLE_REGEX
#include "regex.h"
#endif

typedef struct Parser {
  Token current;
  Token previous;

  ObjString *path;

  int indebt;
  bool hadError;
  bool panicMode;
} Parser;

/**
 * 1 == 1 -> 1
 * 1 == 2 -> nil
 * 1 != 2 -> 2
 * 1 == 0 -> nil
 * 1 == 0 == nil
 * a < b == b
 * (1 < 2) < 3 == 3
 * 3 > 2 > 1 == 1
 */

// pp x == 1
// 3x == 12

// 3x³ + 4x = 0

/** Higher precedence means tighter binding. */
typedef enum Precedence {
  PREC_NONE,       // Lower precedence
  PREC_NEWLINE,    // NEWLINE
  PREC_SEMI,       // ; ?
  PREC_ARROW,      // ->
  PREC_COMMA,      // ,
  PREC_OR,         // or
  PREC_AND,        // and
  PREC_ASSIGNMENT, // = += -= /= *=
  PREC_EQUALITY,   // == !=
  PREC_COMPARISON, // < > <= >= << >>
  PREC_SPACESHIP,  // <=>
  PREC_TERM,       // + -
  PREC_ADJOINING,  // (x y z)
  PREC_FACTOR,     // * /
  PREC_RANGE,      // .. ...
  PREC_PREFIX,     // - ++ -- !
  PREC_DOT,        // .
  PREC_TOUCHING,   // 3x
  PREC_CALL,       // () []
  PREC_PRIMARY     //
} Precedence;      // Higher Precedence

typedef struct Ctx {
  Precedence precedence; // The current precedence.
  bool canAssign;        // If we can parse assignments.
} Ctx;

typedef void ParseFn(Ctx *ctx);

typedef struct ParseRule {
  ParseFn *prefix;
  ParseFn *infix;        // AKA "postfix"
  Precedence precedence; // Higher precedence means tighter binding.
} ParseRule;

ParseRule rules[];

/** A variable defined deeper than the global scope. */
typedef struct Local {
  Token name;      // Name of the local variable.
  int depth;       // How many scopes deep this local is. -1 until defined.
  bool isCaptured; // Has a closure captured this local?
} Local;

/** A local variable that has been closed over by a function. */
typedef struct ClosedUpvalue {
  u8 index;     // The local slot being closed over.
  bool isLocal; // Local slot or enclosing upvalue?
} ClosedUpvalue;

typedef enum FunType {
  TYPE_CLASS,
  TYPE_FUNCTION,
  TYPE_INIT,
  TYPE_METHOD,
  TYPE_GETTER, // let foo = expr
  TYPE_SCRIPT
} FunType;

/**
 * Every function gets its own Compiler.
 * The root compiler gets an anonymous function with name "".
 */
typedef struct Compiler {
  struct Compiler *enclosing; // Compiler of the scope enclosing this one.
  ObjFunction *fun;           // The function being compiled.
  FunType type; // Regular function or a script (root-level anon function).

  /**
   * Stack of local variables.
   *
   * During runtime, local variables are all that stays on the stack.
   * So, the vm's stack will have the same indexes as these locals,
   * and we can share offsets directly.
   */
  Local locals[UINT8_COUNT];
  int localCount;            // Number of locals currently in scope.
  ClosedUpvalue              // Variables this compiler has closed over.
      upvalues[UINT8_COUNT]; // How many times beginScope() has been called.
  int scopeDepth;
} Compiler;

/** The current, innermost class being compiled. */
typedef struct ClassCompiler {
  struct ClassCompiler *enclosing;
  Table fields;
} ClassCompiler;

Parser parser;
Compiler *current = NULL;
ClassCompiler *currentClass = NULL;

static Ctx newCtx() {
  return (Ctx){.precedence = PREC_NONE, .canAssign = false};
}

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

static ObjString *sourceOver(Token *start, Token *end) {
  return copyString(start->start, end->start + end->length - start->start);
}

static ObjString *sourceSince(Token *start) {
  return sourceOver(start, &parser.previous);
}

static void verrorAt(Token *token, const char *message, va_list args) {
  if (parser.panicMode) return;

  parser.panicMode = true;

  if (config.debug || DEBUG_ERRORS || DEBUG_PRINT_CODE) {
    disassembleChunk(currentChunk(), stringChars(current->fun->name), -1);
    fprintf(stderr, "Compilation failed. Current chunk above ^^^\n\n");
  }

  fprintf(stderr,
          "[line " FG_BLUE "%d" FG_DEFAULT "] " FG_RED "ERROR" FG_DEFAULT,
          token->line);

  if (token->type == TOKEN_EOF) {
    fprintf(stderr, " at end");
  } else if (token->type == TOKEN_ERROR) {
    // Nothing.
  } else {
    fprintf(stderr, " at '%.*s'", token->length, token->start);
  }

  fprintf(stderr, ": ");
  vfprintf(stderr, message, args);
  fprintf(stderr, "\n\n");
  parser.hadError = true;
  exit(1);
}

static void errorAt(Token *token, const char *message, ...) {
  va_list args;
  va_start(args, message);
  verrorAt(token, message, args);
  va_end(args);
}

static void error(const char *message, ...) {
  va_list args;
  va_start(args, message);
  verrorAt(&parser.previous, message, args);
  va_end(args);
}

static void errorAtCurrent(const char *message, ...) {
  va_list args;
  va_start(args, message);
  verrorAt(&parser.current, message, args);
  va_end(args);
}

/** Puts the given value in the constant table and returns its index. */
static Long makeConstant(Value value) {
  int constant = addConstant(currentChunk(), value);
  if (constant > UINT32_MAX) {
    error("Too many constants in one chunk.");
    return 0;
  }

  return constant;
}

static void advance() {
  parser.previous = parser.current;

  if (DEBUG_PRINT_EACH_TOKEN) {
    fprintf(stderr, "Token: %.*s\n", parser.previous.length,
            parser.previous.start);
  }

  while (true) {
    parser.current = scanToken();
    if (parser.current.type != TOKEN_ERROR) break;
    errorAtCurrent(parser.current.start);
  }
}

/** Was the current token touching the previous token? */
static bool isTouching() { return !parser.current.hadGap; }

/** Is this the type of the current token? */
static bool check(TokenType type) { return parser.current.type == type; }

/** Check the current token and consume if it matches. */
static bool match(TokenType type) {
  if (!check(type)) return false;

  advance();
  return true;
}

/** The current token must be this type, otherwise error. */
static bool consume(TokenType type, const char *message) {
  if (parser.current.type == type) {
    advance();
    return true;
  }

  errorAtCurrent(message);
  return false;
}

static bool skipNewline() { return match(TOKEN_NEWLINE); }

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

/**
 * Whether the stack should have the last expression removed.
 * The last expression of a script is left for the repl.
 */
static bool shouldCleanStack() { return !check(TOKEN_EOF); }

#define emitLong(size) emitLong_(size, "At " __FILE__ ":" STRINGIFY(__LINE__))
static void emitLong_(Long value, const char *comment) {
  Token token = parser.previous;
  ObjString *str = stringf("(%.*s) %s", token.length, token.start, comment);

  writeChunkLong(currentChunk(), value, token.line, OBJ_VAL(str));
}

#define emitByte(size) emitByte_(size, "At " __FILE__ ":" STRINGIFY(__LINE__))
static void emitByte_(u8 byte, const char *comment) {
  Token token = parser.previous;
  ObjString *str = stringf("(%.*s) %s", token.length, token.start, comment);

  writeChunk(currentChunk(), byte, token.line, OBJ_VAL(str));
}

#define emitBytes(a, b) emitBytes_(a, b, "At " __FILE__ ":" STRINGIFY(__LINE__))
static void emitBytes_(u8 byte1, u8 byte2, const char *comment) {
  emitByte_(byte1, comment);
  emitByte_(byte2, comment);
}

#define emit3Bytes(a, b, c)                                                    \
  emit3Bytes_(a, b, c, "At " __FILE__ ":" STRINGIFY(__LINE__))
static void emit3Bytes_(u8 a, u8 b, u8 c, const char *comment) {
  emitBytes_(a, b, comment);
  emitByte_(c, comment);
}

#define emitLoop(start) emitLoop_(start, "At " __FILE__ ":" STRINGIFY(__LINE__))
static void emitLoop_(int loopStart, const char *comment) {
  emitByte_(OP_LOOP, comment);
  int offset = currentChunk()->count - loopStart + 2;
  if (offset > UINT16_MAX) error("Loop body too large.");

  emitBytes_((offset >> 8) & 0xff, offset & 0xff, comment);
}

#define patchByte(byte, offset)                                                \
  patchByte_(byte, offset, "At " __FILE__ ":" STRINGIFY(__LINE__))
static void patchByte_(u8 byte, int offset, const char *comment) {
  Chunk *chunk = currentChunk();
  chunk->code[offset] = byte;
  if (chunk->comments) chunk->comments[offset] = string(comment);
}

#define patchBytes(byte1, byte2, offset)                                       \
  patchBytes_(byte1, byte2, offset, "At " __FILE__ ":" STRINGIFY(__LINE__))
static void patchBytes_(u8 byte1, u8 byte2, int offset, const char *comment) {
  patchByte_(byte1, offset, comment);
  patchByte_(byte2, offset + 1, comment);
}

#define emitSwap(a, b) emitSwap_(a, b, "At " __FILE__ ":" STRINGIFY(__LINE__))
static void emitSwap_(u8 a, u8 b, const char *comment) {
  emitBytes_(OP_SWAP, (a << 4) | (b & 0x0f), comment);
}

#define emitDebugStack(tag)                                                    \
  emitDebugStack_(tag, "At " __FILE__ ":" STRINGIFY(__LINE__))
static void emitDebugStack_(const char *tag, const char *comment) {
  emitByte_(OP_DEBUG_STACK, comment);
  emitLong_(makeConstant(OBJ_VAL(string(tag))), comment);
}

#define assertStackSize(size, explain)                                         \
  assertStackSize_(size, explain, "At " __FILE__ ":" STRINGIFY(__LINE__))
static void assertStackSize_(u8 size, const char *explain,
                             const char *comment) {
  Long explainv = makeConstant(string(explain));
  emitByte_(OP_ASSERT_STACK, comment);
  emitLong_(explainv, comment);
  emitByte_(size + current->localCount, comment);
}

/**
 * Puts the given value in the constant table and writes an instruction
 * to push it onto the VM stack.
 */
#define emitConstant(value)                                                    \
  emitConstant_(value, "At " __FILE__ ":" STRINGIFY(__LINE__))
static void emitConstant_(Value value, const char *comment) {
  emitByte_(OP_CONSTANT, comment);
  emitLong_(makeConstant(value), comment);
}

#define emitDefault(value)                                                     \
  emitDefault_(value, "At " __FILE__ ":" STRINGIFY(__LINE__))
static void emitDefault_(Value value, const char *comment) {
  emitByte_(OP_DEFAULT, comment);
  emitLong_(makeConstant(value), comment);
}

#define emit(value) emit_(value, "At " __FILE__ ":" STRINGIFY(__LINE__))
static void emit_(Value val, const char *comment) {
  if (isNil(val)) return emitByte_(OP_NIL, comment);
  if (isBool(val)) return emitByte_(AS_BOOL(val) ? OP_TRUE : OP_FALSE, comment);
  return emitConstant_(val, comment);
}

/**
 * Emits the given JUMP command with a temp `short` operand.
 * Returns the offset pointing to the start of the instruction.
 */
#define emitJump(op) emitJump_(op, "At " __FILE__ ":" STRINGIFY(__LINE__))
static int emitJump_(u8 instruction, const char *comment) {
  emit3Bytes_(instruction, 0xff, 0xff, comment);
  return currentChunk()->count - 3;
}

/**
 * Specify that a jump should land here.
 *
 * Patches a previously emitted JUMP instruction at the given offset.
 * The new jump operand will point to the next instruction that is
 * emitted after this call to `landJump`.
 */
#define landJump(offset)                                                       \
  landJump_(offset, "At " __FILE__ ":" STRINGIFY(__LINE__))
static void landJump_(int offset, const char *comment) {
  offset++; // +1 to skip the instruction.
  // -2 to account for the jump offset itself.
  int jump = currentChunk()->count - offset - 2;

  if (jump > UINT16_MAX) {
    // Todo: JUMP_*_32
    error("Too much code to jump over.");
  }

  // The jump expects a two-byte number representing the number of bytes
  // to jump over in the current chunk. The offset we were given is the offset
  // from the beginning of the chunk.
  patchBytes_((jump >> 8) & 0xff, jump & 0xff, offset, comment);
}

#define emitReturn() emitReturn_("At " __FILE__ ":" STRINGIFY(__LINE__))
static void emitReturn_(char *comment) {
  switch (current->type) {
  case TYPE_INIT:
  case TYPE_CLASS:
    emitBytes_(OP_GET_LOCAL, 0, comment); // init() methods always return self.
    break;
  default: emitByte_(OP_NIL, comment);
  }

  emitByte_(OP_RETURN, comment);
}

#define emitClosure(compiler)                                                  \
  emitClosure_(compiler, "At " __FILE__ ":" STRINGIFY(__LINE__))
static void emitClosure_(Compiler *compiler, const char *comment) {
  ObjFunction *fun = compiler->fun;

  if (!fun->upvalueCount) return emitConstant_(OBJ_VAL(fun), comment);

  emitByte_(OP_CLOSURE, comment);
  emitLong_(makeConstant(OBJ_VAL(fun)), comment);

  for (int i = 0; i < fun->upvalueCount; i++) {
    emitByte_(compiler->upvalues[i].isLocal, comment);
    emitByte_(compiler->upvalues[i].index, comment);
  }
}

static ObjSourceLocation *getSourceLocation() {
  int line = parser.previous.line;
  int column = parser.previous.column;
  if (!line) line = 1, column = 1;
  return newSourceLocation(parser.path, line, column);
}

static void initCompiler(Compiler *compiler, FunType type, ObjString *name) {
  compiler->fun = NULL;
  compiler->fun = newFunction();
  compiler->fun->name = name;
  compiler->fun->location = getSourceLocation();
  compiler->type = type;
  compiler->localCount = 0;
  compiler->scopeDepth = 0;
  compiler->enclosing = current;
  current = compiler;

  // Reserve first local for `this`.
  Local *this = &current->locals[current->localCount++];
  this->depth = 0;
  this->isCaptured = false;

  if (type != TYPE_FUNCTION) {
    this->name.start = "this";
    this->name.length = 4;
  } else {
    this->name.start = "";
    this->name.length = 0;
  }
}

/** Note: implies endScope(); */
static ObjFunction *endCompiler() {
  ObjFunction *fun = current->fun;

  if (!parser.hadError && (config.debug || DEBUG_PRINT_CODE))
    disassembleChunk(currentChunk(), stringChars(fun->name), -1);

  current = current->enclosing;
  return fun;
}

/** Adds a local variable with the given name to the current compiler scope. */
static int addLocal(Token name) {
  if (current->localCount == LONG_BYTE_MAX) {
    error("Too many local variables in function.");
    return -1;
  }
  int i = current->localCount++;
  Local *local = &current->locals[i];
  local->name = name;
  local->depth = -1; // Set properly when initialized.
  local->isCaptured = false;
  return i;
}

/**
 * Mark the most recently _declared_ local variable as _defined_.
 * Global variables are _defined_ at runtime via OP_DEFINE_GLOBAL.
 *
 * Undefined locals have a depth of -1.
 *
 * Returns the slot of the defined local variable, -1 for global.
 */
static int markDefined() {
  if (current->scopeDepth == 0) return -1;
  int local = current->localCount - 1;
  current->locals[local].depth = current->scopeDepth;
  return local;
}

static void beginScope() {
  // addLocal(syntheticToken("@block"));
  // markDefined();
  current->scopeDepth++;
}

static void endScope() {
  current->scopeDepth--;

  // Count all locals below our new scopeDepth.
  while (current->localCount > 0 &&
         current->locals[current->localCount - 1].depth > current->scopeDepth) {
    if (current->locals[current->localCount - 1].isCaptured)
      emitByte(OP_CLOSE_UPVALUE);
    else emitByte(OP_POP); // It wasn't closed over, discard it.
    current->localCount--;
  }
}

/** Adds the token to the constants table. */
static Long identifierConstant(Token *name) {
  return makeConstant(identifierValue(name));
}

static Long consumeIdentConstant(const char *message) {
  return makeConstant(consumeIdent(message));
}

/** Do these tokens have the same source string? */
static bool identifiersEqual(Token *a, Token *b) {
  if (a->length != b->length) return false;

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
static int addUpvalue(Compiler *compiler, u8 index, bool isLocal) {
  int upvalueCount = compiler->fun->upvalueCount;

  // Re-use existing upvalues referring to the same slot index.
  for (int i = 0; i < upvalueCount; i++) {
    ClosedUpvalue *upvalue = &compiler->upvalues[i];
    if (upvalue->index == index && upvalue->isLocal == isLocal) return i;
  }

  if (upvalueCount == LONG_BYTE_MAX) {
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
  if (compiler->enclosing == NULL) return -1;

  // Close over a local variable in the enclosing scope.
  int local = resolveLocal(compiler->enclosing, name);
  if (local != -1) {
    compiler->enclosing->locals[local].isCaptured = true;
    return addUpvalue(compiler, (u8)local, true);
  }

  // Close over an upvalue in the enclosing scope.
  int upvalue = resolveUpvalue(compiler->enclosing, name);
  if (upvalue != -1) return addUpvalue(compiler, (u8)upvalue, false);

  // Not found, must be global.
  return -1;
}

/**
 * Creates a local variable named by the previous token.
 * Errors if the name shadows an existing local variable.
 *
 * Returns false if the variable is global.
 */
static bool declareVariable() {
  if (current->scopeDepth == 0) return false; // We're in the global scope.

  Token *name = &parser.previous;

  for (int i = current->localCount - 1; i >= 0; i--) {
    Local *local = &current->locals[i];
    if (local->depth != -1 && local->depth < current->scopeDepth) break;

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
 *
 * Returns the constant id if the variable is global, 0 otherwise.
 */
static Long parseVariable(const char *errorMessage) {
  consume(TOKEN_IDENTIFIER, errorMessage);

  declareVariable();
  if (current->scopeDepth > 0) return 0;

  return identifierConstant(&parser.previous);
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
static void defineVariable(Long global) {
  if (current->scopeDepth > 0) {
    markDefined();
    return;
  }
  emitByte(OP_DEFINE_GLOBAL);
  emitLong(global);
}

static ParseRule *getRule(TokenType type) { return &rules[type]; }

static bool parseAbove(Precedence precedence);

static bool parseInfix(Ctx ctx) {
  ParseRule *rule;
  while ((rule = getRule(parser.current.type))) {
    if (rule->precedence <= ctx.precedence)
      break; // We are the LHS to the next token.

    // if (rule->precedence >= PREC_TOUCHING && !isTouching()) break;

    advance();
    ParseFn *infix = rule->infix;
    if (infix == NULL) {
      error("Missing infix operator. Set precedence to PREC_NONE if this is "
            "intentional.");
      return false;
    }
    infix(&ctx);
  }

  if (ctx.canAssign && match(TOKEN_EQUAL)) {
    error("Invalid assignment target.");
    return false;
  }

  if (ctx.precedence <= PREC_ADJOINING && parser.previous.type != TOKEN_DEDENT)
    while (parseAbove(PREC_ADJOINING)) emitBytes(OP_CALL, 1);

  return false;
}

/**
 * Parse at this precedence or above.
 *
 * Usually used for right-associative (grouped right-to-left) or for prefix
 * operators.
 *
 * Returns true if successful.
 */
static bool parseAt(Precedence precedence) {
  if (precedence <= PREC_NONE) {
    error("Cannot parse at PREC_NONE. PREC_NONE tokens have no infix. "
          "parseAbove(PREC_NONE) instead.");
    return false;
  }

  ParseRule *rule = getRule(parser.current.type);
  ParseFn *prefix = rule->prefix;
  if (prefix == NULL) return false;

  advance();

  Ctx ctx;
  ctx.precedence = precedence;
  ctx.canAssign = precedence <= PREC_ASSIGNMENT;
  prefix(&ctx);
  parseInfix(ctx);
  return true;
}

/**
 * Parse one or more above the given precedence.
 * Usually used for left-associative (grouped left-to-right) operators.
 */
static bool parseAbove(Precedence precedence) {
  return parseAt(precedence + 1);
}

static bool expression(const char *message) {
  bool success = parseAbove(PREC_NONE);
  if (message && !success) error(message);
  return success;
}

static bool indentedExpression() {
  if (!match(TOKEN_INDENT)) return false;
  expression("Expect expression after indent.");
  consume(TOKEN_DEDENT, "Expect dedent after indent.");
  return true;
}

static void statement();
static void declaration();

/** Parse arguments being passed to a function. */
static u8 argumentList() {
  u8 argCount = 0;
  if (!check(TOKEN_RIGHT_PAREN)) {
    do {
      if (!parseAbove(PREC_COMMA)) emit(nil);
      if (argCount == 255) error("Can't have more than 255 arguments.");
      argCount++;
    } while (match(TOKEN_COMMA));
  }
  consume(TOKEN_RIGHT_PAREN, "Expect ')' after arguments.");
  return argCount;
}

static bool selfRequired(OpCode op) {
  switch (op) {
  case OP_SET_PROPERTY:
  case OP_GET_PROPERTY:
  case OP_GET_VAR:
  case OP_SET_VAR: return true;
  default: return false;
  }
}

/**
 * `binary` means the setOp and getOp require the current value
 * on the stack to function properly.
 */
static bool assignment(Ctx *ctx, OpCode getOp, OpCode setOp, Long arg) {
  if (!ctx->canAssign) return false;

  TokenType type = parser.current.type;

  switch (type) {
  case TOKEN_EQUAL:
    advance();
    expression("Expect expression after '='.");
    emitBytes(setOp, arg);
    return true;

  case TOKEN_PLUS_PLUS:
  case TOKEN_MINUS_MINUS:
    advance();

    // We need the last stack value to call get/set
    // Todo: implement assignment via ObjUpvalue?
    //       push the upvalue/value onto the stack. call OP_GET/OP_SET
    if (selfRequired(getOp)) { // [inst]
      emitBytes(OP_PEEK, 0);   // [inst, inst]
      emitByte(getOp);
      emitLong(arg);
      emitDefault(NUMBER_VAL(0)); // [inst, value ?? 0]
      emitSwap(0, 1);             // [value, inst]
      emitBytes(OP_PEEK, 1);      // [value, inst, value]
    } else {
      emitByte(getOp);
      emitLong(arg);
      emitDefault(NUMBER_VAL(0)); // [value ?? 0]
      emitBytes(OP_PEEK, 0);      // [value, value]
    }

    emitConstant(NUMBER_VAL(1));
    emitByte(type == TOKEN_PLUS_PLUS ? OP_ADD : OP_SUBTRACT);
    emitByte(setOp);
    emitLong(arg);
    emitByte(OP_POP);
    return true;

  case TOKEN_PLUS_EQUAL:
  case TOKEN_MINUS_EQUAL:
  case TOKEN_SLASH_EQUAL:
  case TOKEN_STAR_EQUAL:
    advance();

    if (selfRequired(getOp)) emitBytes(OP_PEEK, 0);

    emitByte(getOp);
    emitLong(arg);
    emitDefault(NUMBER_VAL(0));
    expression("Expect expression after assignment.");

    emitByte(type == TOKEN_PLUS_EQUAL    ? OP_ADD
             : type == TOKEN_MINUS_EQUAL ? OP_SUBTRACT
             : type == TOKEN_SLASH_EQUAL ? OP_DIVIDE
                                         : OP_MULTIPLY);

    emitByte(setOp);
    emitLong(arg);
    return true;

  default: break;
  }

  // Did not assign.
  return false;
}

/**
 * Left-associative, but parsed in reverse.
 */
static void and_(Ctx *ctx) {
  int endJump = emitJump(OP_JUMP_IF_FALSE);
  emitByte(OP_POP);
  parseAt(PREC_AND);
  landJump(endJump);
}

static void array(Ctx *ctx) {
  u32 length = 0;
  if (!check(TOKEN_RIGHT_BRACKET)) do {
      parseAbove(PREC_COMMA);
      length++;
    } while (match(TOKEN_COMMA));

  emitByte(OP_ARRAY);
  emitLong(makeConstant(NUMBER_VAL(length)));
  consume(TOKEN_RIGHT_BRACKET, "Expect ']' after array.");
}

/**
 * Left-associative.
 */
static void binary(Ctx *ctx) {
  Token operator= parser.previous;
  ParseRule *rule = getRule(operator.type);
  parseAbove(rule->precedence);

  switch (operator.type) {
  case TOKEN_DOT_DOT: emitByte(OP_RANGE); break;
  case TOKEN_BANG_EQUAL: emitBytes(OP_EQUAL, OP_NOT); break;
  case TOKEN_EQUAL_EQUAL: emitByte(OP_EQUAL); break;
  case TOKEN_GREATER: emitByte(OP_GREATER); break;
  case TOKEN_GREATER_EQUAL: emitBytes(OP_LESS, OP_NOT); break;

  case TOKEN_LESS: emitByte(OP_LESS); break;
  case TOKEN_LESS_EQUAL: emitBytes(OP_GREATER, OP_NOT); break;

  case TOKEN_PLUS: emitByte(OP_ADD); break;
  case TOKEN_MINUS: emitByte(OP_SUBTRACT); break;
  case TOKEN_STAR: emitByte(OP_MULTIPLY); break;
  case TOKEN_SLASH: emitByte(OP_DIVIDE); break;
  default: {
    Long name =
        makeConstant(OBJ_VAL(copyString(operator.start, operator.length)));
    emitByte(OP_INVOKE);
    emitLong(name);
    emitByte(1); // argc
  }
  }
}

static void call(Ctx *ctx) {
  u8 argCount = argumentList();
  emitBytes(OP_CALL, argCount);
}

/** Evaluates but discards the second argument. */
static void semi(Ctx *ctx) {
  parseAbove(PREC_SEMI);
  emitByte(OP_POP);
}

/** Left-associative. */
static void tuple(Ctx *ctx) {
  u8 length = 1;
  do {
    if (!parseAbove(PREC_COMMA)) emit(nil);
    length++;
  } while (match(TOKEN_COMMA));

  emitBytes(OP_TUPLE, length);
}

static void dot(Ctx *ctx) {
  Long name = makeConstant(consumeIdent("Expect property name after '.'"));

  if (match(TOKEN_LEFT_PAREN)) {
    u8 argCount = argumentList();
    emitByte(OP_INVOKE);
    emitLong(name);
    emitByte(argCount);
  } else if (assignment(ctx, OP_GET_PROPERTY, OP_SET_PROPERTY, name)) return;
  else {
    emitByte(OP_GET_PROPERTY);
    emitLong(name);
  }
}

static void dotSugar(Ctx *ctx) {
  Compiler compiler;
  Token self = syntheticToken("_");
  initCompiler(&compiler, TYPE_FUNCTION,
               sourceOver(&parser.previous, &parser.current));
  current->fun->arity++;

  beginScope();

  addLocal(self);
  markDefined();
  emitBytes(OP_GET_LOCAL, 1);
  dot(ctx);
  parseInfix((Ctx){.precedence = PREC_DOT - 1});
  emitByte(OP_RETURN);

  endCompiler();
  emitClosure(&compiler);
}

static void literal(Ctx *ctx) {
  switch (parser.previous.type) {
  case TOKEN_FALSE: emitByte(OP_FALSE); break;
  case TOKEN_NIL: emitByte(OP_NIL); break;
  case TOKEN_TRUE: emitByte(OP_TRUE); break;
  default: // Unreachable.
    return;
  }
}

static void grouping(Ctx *ctx) {
  if (!expression(NULL)) emit(nil);
  consume(TOKEN_RIGHT_PAREN, "Expect ')' after expression.");
}

static void newline(Ctx *ctx) {
  error("newline");
  if (check(TOKEN_EOF)) return;
  emitByte(OP_POP);
}

static void number_(Ctx *ctx) {
  double value = strtod(parser.previous.start, NULL);
  emitConstant(NUMBER_VAL(value));
}

static void hex(Ctx *ctx) {
  u32 value = strtoul(parser.previous.start, NULL, 0);
  emitConstant(NUMBER_VAL(value));
}

/**
 * Left-associative, but parsed in reverse.
 */
static void or_(Ctx *ctx) {
  int elseJump = emitJump(OP_JUMP_IF_FALSE);
  int endJump = emitJump(OP_JUMP);

  landJump(elseJump);
  emitByte(OP_POP);
  parseAt(PREC_OR);
  landJump(endJump);
}

static void print(Ctx *ctx) {
  expression("Expect expression after 'print'.");
  emitByte(OP_PRINT);
}

static void backticks(Ctx *ctx) {
  Token token = parser.previous;
  ObjString *source = copyString(token.start + 1, token.length - 2);

#if ENABLE_REGEX
  ObjRegex *reg = makeRegex(source);
  emitConstant(OBJ_VAL(reg));
#else
  error("Regex not enabled.");
#endif
}

static void string_(Ctx *ctx) {
  Token token = parser.previous;
  ObjString *str = copyString(token.start + 1, token.length - 2);
  if (token.escaped) str = unescapeString(str);
  emitConstant(OBJ_VAL(str));
}

static void symbol(Ctx *ctx) {
  advance();
  Token token = parser.previous;
  ObjString *str = copyString(token.start, token.length);
  if (token.escaped) str = unescapeString(str);
  emitConstant(OBJ_VAL(str));
}

/**
 * Emits bytecode to read the variable with the given Token name from the
 * current scope.
 *
 * Will also parse any following assignment operators if canAssign is true.
 */
static void namedVariable(Token name, Ctx *ctx) {
  u8 getOp, setOp;
  int arg = resolveLocal(current, &name);

  if (arg != -1) {
    getOp = OP_GET_LOCAL;
    setOp = OP_SET_LOCAL;
  } else if ((arg = resolveUpvalue(current, &name)) != -1) {
    getOp = OP_GET_UPVALUE;
    setOp = OP_SET_UPVALUE;
  } else if (currentClass) {
    arg = identifierConstant(&name);
    Token self = syntheticToken("this");
    emitByte(OP_GET_LOCAL);
    emitLong(resolveLocal(current, &self));
    getOp = OP_GET_VAR;
    setOp = OP_SET_VAR;
  } else {
    arg = identifierConstant(&name);
    getOp = OP_GET_GLOBAL;
    setOp = OP_SET_GLOBAL;
  }
  // canAssign:
  // printf("namedVariable: %.*s: %d\n", name.length, name.start,
  // ctx->canAssign);
  if (assignment(ctx, getOp, setOp, arg)) return;

  emitByte(getOp);
  emitLong(arg);
}

static void question(Ctx *ctx) {
  int thenJump = emitJump(OP_JUMP_IF_FALSE);

  if (!check(TOKEN_COLON)) {
    emitByte(OP_POP);
    if (!parseAbove(ctx->precedence)) error("Expected expression after '?'.");
  }

  int elseJump = emitJump(OP_JUMP);
  landJump(thenJump);

  if (match(TOKEN_COLON)) {
    emitByte(OP_POP);
    if (!parseAt(ctx->precedence)) error("Expect expression after ':'.");
  }

  landJump(elseJump);
}

static void variable(Ctx *ctx) { namedVariable(parser.previous, ctx); }

static void super_(Ctx *ctx) {
  if (currentClass == NULL) error("Can't use 'super' outside of a class.");

  // Todo: super() calls the current method.
  consume(TOKEN_DOT, "Expect '.' after 'super'.");
  Long name = consumeIdentConstant("Expect superclass method name.");

  namedVariable(syntheticToken("this"), ctx);

  if (match(TOKEN_LEFT_PAREN)) {
    u8 argCount = argumentList();
    namedVariable(syntheticToken("super"), ctx);
    emitByte(OP_SUPER_INVOKE);
    emitLong(name);
    emitByte(argCount);
  } else {
    namedVariable(syntheticToken("super"), ctx);
    emitByte(OP_GET_SUPER);
    emitLong(name);
  }
}

static void this_(Ctx *ctx) {
  if (currentClass == NULL) {
    error("Can't use 'this' outside of a class.");
    return;
  }
  variable(ctx);
}

/** Right-associative. */
static void prefix(Ctx *ctx) {
  TokenType operatorType = parser.previous.type;

  // Compile the operand.
  if (!parseAt(PREC_PREFIX)) error("Expect expression after prefix operator.");

  // Emit the operator instruction.
  switch (operatorType) {
  case TOKEN_BANG: emitByte(OP_NOT); break;
  case TOKEN_MINUS: emitByte(OP_NEGATE); break;
  default:
    error("Unknown prefix operator: %.*s.", parser.previous.length,
          parser.previous.start);
  }
}

static void postfix(Ctx *ctx) {
  TokenType operatorType = parser.previous.type;

  switch (operatorType) {
  // case TOKEN_BANG:
  // case TOKEN_QUEST:
  default: return;
  }
}

// Todo: Block-as-expression + yield/break keyword
static void block() {
  while (!check(TOKEN_DEDENT) && !check(TOKEN_EOF)) {
    declaration();
  }

  consume(TOKEN_DEDENT, "Expect dedent after block.");
}

static void function(FunType type) {
  Compiler compiler;
  ObjString *name = type == TYPE_CLASS ? newString("init")
                                       : copyString(parser.previous.start,
                                                    parser.previous.length);

  initCompiler(&compiler, type, name);
  beginScope();

  if (match(TOKEN_LEFT_PAREN)) {
    if (!check(TOKEN_RIGHT_PAREN)) {
      do {
        if (match(TOKEN_ELLIPSIS)) {
          compiler.fun->variadic = true;
          match(TOKEN_IDENTIFIER);
          declareVariable();
          markDefined();
          break;
        }

        current->fun->arity++;
        if (current->fun->arity > 255)
          errorAtCurrent("Can't have more than 255 parameters.");

        parseVariable("Expect parameter name.");
        markDefined();
      } while (match(TOKEN_COMMA));
    }

    consume(TOKEN_RIGHT_PAREN, "Expect ')' after parameters.");
  }

  if (type == TYPE_CLASS) {
    // Inline init
    for (int i = 1; i < current->localCount; i++) {

      Value name = identifierValue(&current->locals[i].name);
      Long constant = makeConstant(name);
      tableSet(&currentClass->fields, name, TRUE_VAL);
      emitBytes(OP_GET_LOCAL, 0); // self
      emitByte(OP_GET_LOCAL);     // value
      emitLong(i);
      emitByte(OP_SET_PROPERTY);
      emitLong(constant);
      emitByte(OP_POP); // Pop the value
    }
  } else if (match(TOKEN_EQUAL) || match(TOKEN_FAT_ARROW)) {
    expression("Expect expression as function body.");
    emitByte(OP_RETURN);
    skipNewline();
  } else if (match(TOKEN_INDENT)) {
    block();
  }

  emitReturn();
  // no endScope(). Compiler will be deallocated.
  endCompiler();
  emitClosure(&compiler);
}

static void getter() {
  let name = consumeIdent("Expect property name.");

  // TODO: Figure out what fields was meant to do.
  tableSet(&currentClass->fields, name, TRUE_VAL);

  if (match(TOKEN_EQUAL)) {
    Long nameConstant = makeConstant(name);
    Compiler compiler;

    initCompiler(&compiler, TYPE_METHOD, asString(name));
    beginScope();
    expression("Expect expression after `let ... =`.");
    emitByte(OP_SET_PROPERTY);
    emitLong(nameConstant);
    emitByte(OP_RETURN);

    endCompiler();
    emitClosure(&compiler);
    emitByte(OP_METHOD);
    emitLong(nameConstant);
  }

  skipNewline();
}

static void method() {
  if (match(TOKEN_LET)) return getter();

  match(TOKEN_CFN) || match(TOKEN_FN) || match(TOKEN_DOT); // optional

  Token name;
  if (check(TOKEN_LEFT_PAREN)) {
    name = syntheticToken("");
  } else {
    consumeIdent("Expect method name.");
    name = parser.previous;
  }

  Long constant = identifierConstant(&name);

  FunType type = TYPE_METHOD;
  if (name.length == 4 && memcmp(name.start, "init", 4) == 0) {
    type = TYPE_INIT;
  }

  function(type);
  emitByte(OP_METHOD);
  emitLong(constant);
}

// static void indent(Ctx *ctx) {
//   beginScope();
//   block();
//   endScope();
// }

static void classDeclaration(Ctx *ctx) {
  Value name = consumeIdent("Expect class name.");
  Token className = parser.previous;
  Long nameConstant = makeConstant(name);

  bool isLocal = declareVariable();
  emitByte(OP_CLASS);
  emitLong(nameConstant);
  emitByte(isLocal);

  if (isLocal) markDefined();

  ClassCompiler classCompiler;
  pushClassCompiler(&classCompiler);

  // Parse inline init
  if (check(TOKEN_LEFT_PAREN)) {
    function(TYPE_CLASS);
    Value init = OBJ_VAL(newString("init"));
    emitByte(OP_METHOD);
    emitLong(makeConstant(init));
  }

  if (match(TOKEN_LESS)) expression("Expect superclass.");
  else namedVariable(syntheticToken("Object"), ctx);

  beginScope();
  addLocal(syntheticToken("super"));
  markDefined();

  emitByte(OP_INHERIT);
  emitSwap(0, 1); // [class, super] -> [1 super][0 class]

  if (match(TOKEN_INDENT)) {
    while (!check(TOKEN_DEDENT) && !check(TOKEN_EOF))
      if (match(TOKEN_CLASS)) classDeclaration(ctx);
      else method();

    consume(TOKEN_DEDENT, "Expect dedent after class body.");
  } else {
    skipNewline();
  }

  emitByte(OP_POP); // Pop the class
  endScope();       // Pops local vars, including "super"
  popClassCompiler();
  // TODO: figure out a way to just use the popped class:
  if (!shouldCleanStack()) namedVariable(className, ctx);
}

static void funDeclaration() {
  Long global = parseVariable("Expect function name.");
  markDefined();
  function(TYPE_FUNCTION);
  if (!shouldCleanStack()) emitBytes(OP_PEEK, 0);
  defineVariable(global);
}

static void function_(Ctx *ctx) {
  match(TOKEN_IDENTIFIER);
  function(TYPE_FUNCTION);
}

static Long varDeclaration() {
  Long global = parseVariable("Expect variable name.");

  if (match(TOKEN_EQUAL)) parseAt(PREC_ASSIGNMENT);
  else emitByte(OP_NIL);

  if (!shouldCleanStack()) emitBytes(OP_PEEK, 0);

  defineVariable(global);
  return global;
}

static void assert_(Ctx *ctx) {
  Token start = parser.previous;

  // TODO: parse above ==, etc. and parse LHS and RHS separately
  // Then emitBytes(OP_ASSERT, OP_EQUAL)

  if (match(TOKEN_COLON)) expression("Expect expression after assert.");
  else if (!parseAt(ctx->precedence))
    return error("Expect expression after assert.");

  emitByte(OP_ASSERT);
  emitLong(makeConstant(obj(sourceSince(&start))));
}

// for ;;i++:
static void forStatement() {
  beginScope();
  // Todo: for-in loops
  // for x in 1..5:
  // u8 global = parseVariable("Expect variable after 'for'.");
  // consume(TOKEN_IN, "Expect 'in' after variable in for clause.");

  if (match(TOKEN_LET)) varDeclaration();           // [-1 local var][]
  else if (parseAbove(PREC_SEMI)) emitByte(OP_POP); // [] pop init

  consume(TOKEN_SEMICOLON, "Expect ';' after initializer.");

  int loopStart = currentChunk()->count; // []
  int exitJump = -1;

  if (parseAbove(PREC_SEMI)) {             // [0 cond]
    exitJump = emitJump(OP_JUMP_IF_FALSE); // Exit if condition is false, else
    emitByte(OP_POP);                      // [] pop the condition.
  }

  consume(TOKEN_SEMICOLON, "Expect ';' after loop condition.");

  if (check(TOKEN_INDENT) || match(TOKEN_COLON)) {
    // No increment.
  } else {
    int bodyJump = emitJump(OP_JUMP); // Jump over increment.

    // Runs after each loop.
    int incrementStart = currentChunk()->count; // []

    if (parseAbove(PREC_SEMI)) // [0 increment]
      emitByte(OP_POP);        // []

    if (!check(TOKEN_INDENT))
      consume(TOKEN_COLON, "Expect ':' or indentation after for clause.");

    emitLoop(loopStart);        // Loop back to condition.
    loopStart = incrementStart; // End loop with increment.
    landJump(bodyJump);         // Begin body.
  }

  statement();         // []
  emitLoop(loopStart); // Loop back to condition.

  if (exitJump != -1) { // If we had a condition,
    landJump(exitJump); // [0 cond]               begin exit.
    emitByte(OP_POP);   //  Pop condition.
  }

  endScope(); // []
}

static void ifStatement() {
  expression("Expect expression after 'if'"); // [0 cond]
  assertStackSize(1, "if condition");

  if (!check(TOKEN_INDENT))
    consume(TOKEN_COLON, "Expect ':' or block after condition.");

  int thenJump =
      emitJump(OP_JUMP_IF_FALSE); // Jump to else if condition is false.
  emitByte(OP_POP);               // [] pop condition
  statement();                    // Then branch.

  int elseJump = emitJump(OP_JUMP); // Jump over else branch.
  landJump(thenJump);               // End of then branch. Start of else branch.

  emitByte(OP_POP);                   // [] pop condition
  if (match(TOKEN_ELSE)) statement(); // Else branch.
  landJump(elseJump);                 // End of else branch.
}

static void match_() {
  Long matchFn = makeConstant(string("=="));
  expression("Expect expression after 'match'."); // [0 match expr]
  assertStackSize(1, "match expression");
  consume(TOKEN_INDENT, "Expect block after match expression.");

  int startJump = emitJump(OP_JUMP); // Jump over the exit jump.
  int exitJump = emitJump(OP_JUMP);  // Below, we use this to exit.
  landJump(startJump);

  // For each pattern in the match block:
  while (!check(TOKEN_DEDENT) && !check(TOKEN_EOF) && !check(TOKEN_ELSE)) {
    beginScope();

    // Duplicate the match value because OP_EQUAL pops the pattern.
    emitBytes(OP_PEEK, 0); // [match expr][match expr]

    // TODO: Handle multiple patterns.
    // do {...} while (parseAbove(PREC_COMMA)));
    if (parseAbove(PREC_ARROW)) { // [match expr][match expr][pattern]
      consume(TOKEN_ARROW, "Expect '->' after pattern.");
      emitByte(OP_INVOKE);
      emitLong(matchFn);
      emitByte(1);
      assertStackSize(2, "match expr, match result");

      int skipJump = emitJump(
          OP_JUMP_IF_FALSE); // Jump to next pattern if this one doesn't match.

      emitBytes(OP_POP, OP_POP); // [] pop match success and match expr
      expression("Expected expression after '->'."); // [expr]
      assertStackSize(1, "after-match expression");
      skipNewline();
      emitLoop(exitJump);

      landJump(skipJump);
      emitByte(OP_POP); // [match expr] Pop the match failure.
    } else {
      error("Expect pattern and then '->'.");
    }
    endScope();
  }

  if (match(TOKEN_ELSE)) {
    emitByte(OP_POP);                                // [] pop the match expr
    expression("Expected expression after 'else'."); // [expr]
  }

  landJump(exitJump);
  consume(TOKEN_DEDENT, "Expect dedent after match block.");
}

static void return_() {
  if (match(TOKEN_NEWLINE)) emitReturn();
  else {
    if (current->type == TYPE_INIT) {
      error("Can't return a value from init().");
    }

    if (!expression(NULL)) emitByte(OP_NIL);
    emitByte(OP_RETURN);
  }
}

static void throw_() {
  Value sourceLocation = OBJ_VAL(getSourceLocation());

  if (!expression(NULL)) emit(nil);
  emitByte(OP_THROW);
  emitLong(makeConstant(sourceLocation));
}

static void whileStatement() {
  beginScope();
  emit(True);
  int runElse = addLocal(syntheticToken("else"));
  defineVariable(0);

  int loopStart = currentChunk()->count;

  expression("Expect expression after 'while'."); // [0 condition]
  assertStackSize(1, "while condition");

  int exitJump = emitJump(OP_JUMP_IF_FALSE);
  emitByte(OP_POP);
  emit(False);
  emitByte(OP_SET_LOCAL);
  emitLong(runElse);
  emitByte(OP_POP);

  if (check(TOKEN_INDENT) || match(TOKEN_COLON)) statement();
  else skipNewline();
  emitLoop(loopStart); // Loop back to the condition.

  landJump(exitJump); // Exit the loop.
  assertStackSize(1, "falsey while condition");
  emitByte(OP_POP); // []

  int elseJump = emitJump(OP_JUMP_IF_FALSE);
  if (match(TOKEN_ELSE)) statement();
  landJump(elseJump);
  endScope();
}

static void synchronize() {
  parser.panicMode = false;

  while (parser.current.type != TOKEN_EOF) {
    if (parser.previous.type == TOKEN_SEMICOLON) return;

    if (parser.previous.type == TOKEN_NEWLINE) return;

    switch (parser.current.type) {
    case TOKEN_ASSERT:
    case TOKEN_CLASS:
    case TOKEN_DEDENT:
    case TOKEN_FN:
    case TOKEN_INDENT:
    case TOKEN_LET:
    case TOKEN_FOR:
    case TOKEN_IF:
    case TOKEN_WHILE:
    case TOKEN_PRINT:
    case TOKEN_RETURN: return;
    default:; // Do nothing.
    }

    advance();
  }
}

static void declaration() {
  Ctx ctx = newCtx();

  if (match(TOKEN_CLASS)) {
    classDeclaration(&ctx);
  } else if (match(TOKEN_FN)) {
    funDeclaration();
  } else if (match(TOKEN_LET)) {
    varDeclaration();
  } else {
    statement();
  }

  skipNewline();

  if (parser.panicMode) synchronize();
}

static void statement() {
  if (match(TOKEN_INDENT)) {
    beginScope();
    block();
    endScope();
  } else if (match(TOKEN_FOR)) {
    forStatement();
  } else if (match(TOKEN_IF)) {
    ifStatement();
  } else if (match(TOKEN_WHILE)) {
    whileStatement();
  } else {
    expression("Expected expression.");
    skipNewline();
    if (shouldCleanStack()) emitByte(OP_POP);
  }

  skipNewline();

  // Todo: switch statement
  // Todo: break statement
  // Todo: continue statement
}

ObjFunction *compile(const char *source, ObjString *path) {
  initScanner(source);

  if (DEBUG_TOKENS || config.debug >= 4) debugTokens();

  parser.path = path;
  parser.indebt = 0;
  parser.hadError = false;
  parser.panicMode = false;

  Compiler compiler;
  initCompiler(&compiler, TYPE_SCRIPT, path);

  advance();

  if (match(TOKEN_EOF)) emitByte(OP_NIL);
  while (!match(TOKEN_EOF)) declaration();

  assertStackSize(1, "script return value");
  emitByte(OP_RETURN);
  ObjFunction *fun = endCompiler();
  return parser.hadError ? NULL : fun;
}

void markCompilerRoots() {
  Compiler *compiler = current;

  while (compiler != NULL) {
    markObject((Obj *)compiler->fun);
    compiler = compiler->enclosing;
  }
}

ParseRule rules[] = {
    //                {prefix, infix, precedence}
    [TOKEN_IDENTIFIER] = {variable, NULL, PREC_NONE},
    [TOKEN_STRING] = {string_, NULL, PREC_NONE},
    [TOKEN_BACKTICK_STRING] = {backticks, NULL, PREC_NONE},
    [TOKEN_QUOTE] = {symbol, NULL, PREC_NONE},

    [TOKEN_FALSE] = {literal, NULL, PREC_NONE},
    [TOKEN_NIL] = {literal, NULL, PREC_NONE},
    [TOKEN_TRUE] = {literal, NULL, PREC_NONE},

    [TOKEN_NUMBER] = {number_, NULL, PREC_NONE},
    [TOKEN_HEX] = {hex, NULL, PREC_NONE},

    [TOKEN_LEFT_BRACKET] = {array, NULL, PREC_NONE},

    [TOKEN_BANG] = {prefix, NULL, PREC_NONE},

    [TOKEN_ASSERT] = {assert_, NULL, PREC_NONE},
    [TOKEN_SUPER] = {super_, NULL, PREC_NONE},
    [TOKEN_THIS] = {this_, NULL, PREC_NONE},

    [TOKEN_MATCH] = {match_, NULL, PREC_NONE},
    [TOKEN_PRINT] = {print, NULL, PREC_NONE},
    [TOKEN_RETURN] = {return_, NULL, PREC_NONE},
    [TOKEN_THROW] = {throw_, NULL, PREC_NONE},
    [TOKEN_FN] = {function_, NULL, PREC_NONE},

    [TOKEN_SEMICOLON] = {NULL, semi, PREC_SEMI},
    [TOKEN_QUESTION] = {NULL, question, PREC_SEMI},

    [TOKEN_COMMA] = {NULL, tuple, PREC_COMMA},

    [TOKEN_OR] = {NULL, or_, PREC_OR},

    [TOKEN_AND] = {NULL, and_, PREC_AND},

    [TOKEN_MINUS_EQUAL] = {NULL, NULL, PREC_ASSIGNMENT},
    [TOKEN_PLUS_EQUAL] = {NULL, NULL, PREC_ASSIGNMENT},
    [TOKEN_SLASH_EQUAL] = {NULL, NULL, PREC_ASSIGNMENT},
    [TOKEN_STAR_EQUAL] = {NULL, NULL, PREC_ASSIGNMENT},

    [TOKEN_BANG_EQUAL] = {NULL, binary, PREC_EQUALITY},
    [TOKEN_EQUAL_EQUAL] = {NULL, binary, PREC_EQUALITY},

    [TOKEN_LESS_LESS] = {NULL, binary, PREC_COMPARISON},
    [TOKEN_GREATER_GREATER] = {NULL, binary, PREC_COMPARISON},
    [TOKEN_GREATER] = {NULL, binary, PREC_COMPARISON},
    [TOKEN_GREATER_EQUAL] = {NULL, binary, PREC_COMPARISON},
    [TOKEN_LESS] = {NULL, binary, PREC_COMPARISON},
    [TOKEN_LESS_EQUAL] = {NULL, binary, PREC_COMPARISON},
    [TOKEN_SPACESHIP] = {NULL, binary, PREC_SPACESHIP},

    [TOKEN_MINUS] = {prefix, binary, PREC_TERM},
    [TOKEN_PLUS] = {NULL, binary, PREC_TERM},

    [TOKEN_SLASH] = {NULL, binary, PREC_FACTOR},
    [TOKEN_STAR] = {NULL, binary, PREC_FACTOR},

    [TOKEN_DOT_DOT] = {NULL, binary, PREC_RANGE},
    // [TOKEN_ELLIPSIS] = {ellipsis, NULL, PREC_RANGE},

    [TOKEN_PLUS_PLUS] = {prefix, NULL, PREC_PREFIX},
    [TOKEN_MINUS_MINUS] = {prefix, NULL, PREC_PREFIX},

    [TOKEN_DOT] = {dotSugar, dot, PREC_DOT},

    [TOKEN_LEFT_PAREN] = {grouping, call, PREC_CALL},
    [TOKEN_NEWLINE] = {NULL, newline, PREC_NEWLINE},
};
