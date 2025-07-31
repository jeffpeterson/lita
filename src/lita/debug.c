#include <inttypes.h>
#include <stdio.h>

#include "debug.h"
#include "object.h"
#include "scanner.h"
#include "string.h"
#include "term.h"
#include "value.h"
#include "vm.h"

static Color color(OpType type) {
  switch (type) {
  case SIMPLE: return BLUE;
  case BYTE: return YELLOW;
  case CONSTANT: return GREEN;
  case INVOKE: return MAGENTA;
  case JUMP: return RED;
  case CONSTANT_BYTE: return CYAN;
  }
}

void disassembleChunk(Chunk *chunk, const char *name, int until) {
  if (until < 0 || until > chunk->count) until = chunk->count;

  fprintf(stderr, "╔═════════════════════════════════════════╗\r");
  fprintf(stderr, "╔═ " FG_MAGENTA "%s" FG_BLUE " v%d" FG_DEFAULT " \n", name,
          chunk->version);
  fprintf(stderr, "║ Byte Line OpCode               Operands ║\n");
  fprintf(stderr, "╟───── ──── ──────────────────── ─────────╢\n");

  if (until > 50)
    fprintf(stderr, "║ …         …                    …        ║\n");

  for (int offset = 0; offset < until;) {
    offset = disassembleInstruction(chunk, offset);
    if (until - offset > 50) fprintf(stderr, "\r\033[A\033[K");
  }
  if (until < chunk->count)
    fprintf(stderr, "║ …         …                    …        ║\n"
                    "╙┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄╜\n");
  else fprintf(stderr, "╚═════════════════════════════════════════╝\n");
}

static void byte(u8 arg) { fprintf(stderr, " %02x", arg); }
static void longHex(Long arg) {
  if (arg > LONG_BYTE_MAX) fprintf(stderr, FG_YELLOW);
  fprintf(stderr, " %02x", arg);
  fprintf(stderr, FG_DEFAULT);
}
static void arrow() { fputs("\t\e[2m->\e[22m ", stderr); }
static void newline() { fputs("\n", stderr); }

int disassembleInstruction(Chunk *chunk, int offset) {
  u8 *code = chunk->code;
  fprintf(stderr, RESET "║ %04x ", offset);

  if (offset > 0 && chunk->lines[offset] == chunk->lines[offset - 1])
    fprintf(stderr, DIM "   │ " NO_DIM);
  else fprintf(stderr, FG_CYAN "%4d " FG_DEFAULT, chunk->lines[offset]);

  u8 instruction = code[offset++];
  OpInfo info = opInfo[instruction];
  Long constant;

  fprintf(stderr, "%02x" DIM "->" NO_DIM, instruction);
  if (info.name == NULL) {
    fprintf(stderr, "Unknown opcode %02x\n", instruction);
    return offset;
  }

  fprintf(stderr,
          "\e[3%dm"
          "%-16s" FG_DEFAULT,
          color(info.type), info.name);

  switch (info.type) {
  case SIMPLE: break;

  case BYTE: byte(code[offset++]); break;

  case CONSTANT: {
    if (chunk->version < 1) constant = code[offset++];
    else offset += decodeLong(&constant, code + offset);
    longHex(constant);
    arrow();
    inspectValue(stderr, chunk->constants.values[constant], 1);
    break;
  }

  case CONSTANT_BYTE: {
    if (chunk->version < 1) constant = code[offset++];
    else offset += decodeLong(&constant, code + offset);
    longHex(constant);
    byte(code[offset++]);
    arrow();
    inspectValue(stderr, chunk->constants.values[constant], 1);
    break;
  }

  case INVOKE: {
    offset += decodeLong(&constant, code + offset);
    u8 argCount = code[offset++];
    longHex(constant);
    byte(argCount);
    arrow();
    inspectValue(stderr, chunk->constants.values[constant], 1);
    fprintf(stderr, " (%d args)", argCount);
    break;
  }

  case JUMP: {
    int sign = instruction == OP_LOOP ? -1 : 1;

    byte(code[offset]);
    byte(code[offset + 1]);
    arrow();

    uint16_t jump = (uint16_t)(code[offset++] << 8);
    jump |= code[offset++];
    fprintf(stderr, UNDERLINE "%04x" NO_UNDERLINE, offset + sign * jump);
    break;
  }
  }

  switch (instruction) {
  case OP_CLOSURE: {
    ObjFunction *fun = asFunction(chunk->constants.values[constant]);

    for (int j = 0; j < fun->upvalueCount; j++) {
      int isLocal = code[offset++];
      int index = code[offset++];
      fprintf(stderr, "\n%04d      │->                  ", offset - 2);
      byte(isLocal);
      byte(index);
      arrow();
      fprintf(stderr, "%s %d", isLocal ? "local" : "upvalue", index);
    }
    break;
  }

  case OP_SWAP: {
    u8 args = code[offset - 1];
    arrow();
    fprintf(stderr, "%x %x", args >> 4, args & 0x0f);
    break;
  }
  default:;
  }

  if (chunk->comments && chunk->comments[offset - 1]) {
    fprintf(stderr, DIM "\t\t// ");
    inspectValue(stderr, chunk->comments[offset - 1], 1);
    fprintf(stderr, NO_DIM);
  }

  newline();
  return offset;
}

static void printIndents(int indent) {
  for (int i = 0; i < indent; i++) {
    fputs("\t", stderr);
  }
}

void debugTokens() {
  Token token;
  Color color = RED;
  int indent = 0;

  fprintf(stderr, "\n");

  do {
    color %= CYAN;
    color += 1;
    token = scanToken();

    if (token.type == TOKEN_INDENT) {
      fprintf(stderr, "\n[ind]\t");
      while ((token = scanToken()).type == TOKEN_INDENT) {
        indent++;
        fprintf(stderr, "[ind]\t");
      }
      printIndents(indent++);
    }

    switch (token.type) {
    case TOKEN_NEWLINE:
      fg(stderr, color);
      fprintf(stderr, "[newline]\n");
      printIndents(indent);
      break;
    case TOKEN_DEDENT:
      fg(stderr, color);
      fputs("[dedent]\n", stderr);
      printIndents(--indent);
      break;
    case TOKEN_ERROR:
      fg(stderr, color);
      fprintf(stderr, "[error: %.*s]\n", token.length, token.start);
      printIndents(indent);
      break;
    case TOKEN_EOF: fputs("[EOF]\n", stderr); break;
    default:
      fg(stderr, color);
      fprintf(stderr, "%.*s ", token.length, token.start);
    }

  } while (token.type != TOKEN_EOF);
  fprintf(stderr, FG_DEFAULT);
  resetScanner();
}

static void debugValues(Value *start, int length) {
  int offsets[length];
  CallFrame *frame = vm.frames;
  for (int i = 0; i < length; i++) {
    while (frame < vm.frames + vm.frameCount && frame->slots < start + i)
      frame++;

    offsets[i] = 0;
    if (vm.frameCount && frame->slots == start + i)
      offsets[i] += fprintf(stderr, "‸");
    offsets[i] += fprintf(stderr, "[ ");
    offsets[i] += inspectValue(stderr, start[i], 1);
    offsets[i] += fprintf(stderr, " ]");
  }
}

void debugStack() {
  fputs(BG_WHITE, stderr);
  debugValues(vm.stack, vm.stackTop - vm.stack);
  fputs(DIM, stderr);
  debugValues(vm.stackTop, vm.stackHigh - vm.stackTop);
  fputs(NO_DIM BG_DEFAULT, stderr);
}

static CallFrame *prev_frame;

void debugFrames() {
  for (int i = 0; i < vm.frameCount; i++) {
    CallFrame *frame = &vm.frames[i];
    fprintf(stderr, "[ ");
    inspectObject(stderr, frame->obj, 1);
    fprintf(stderr, " ]");
  }
}

void debugExecution() {
  fprintf(stderr, RESET "║" DIM "      -->" NO_DIM); // ►
  debugStack();
  // int frameSizes[vm.frameCount];

  // for (int i = 0; i <= vm.frameCount - 1; i++) {
  //   int frameSize = vm.frames[i + 1].slots - vm.frames[i].slots;
  //   fprintf(stderr, "[ Frame %-*d ]", frameSize *, i);
  // }

  // frameSizes[vm.frameCount - 1] =
  //     vm.stackTop - vm.frames[vm.frameCount - 1].slots;

  // fprintf(stderr, "\n            ");
  // for (int i = 0; i < stackSize; i++) {
  //   fprintf(stderr, "[ %-*d ]", offsets[i] - 4, i);
  // }

  CallFrame *frame = vm.frames + vm.frameCount - 1;

  if (frame != prev_frame) {
    fprintf(stderr, "\n");
    debugFrames();
  }

  fprintf(stderr, DIM "\n");
  if (frame->ip)
    disassembleInstruction(
        &toFunction(frame->obj)->chunk,
        (int)(frame->ip - toFunction(frame->obj)->chunk.code));
  fprintf(stderr, NO_DIM);
  prev_frame = frame;
}

int debugValue(Value value) {
  int sum = 0;

  sum += fprintf(stderr, "Value(");

  if (isNumber(value)) sum += fprintf(stderr, "number");
  if (isBool(value))
    sum += fprintf(stderr, "bool: %s", AS_BOOL(value) ? "true" : "false");
  if (isNil(value)) sum += fprintf(stderr, "nil");
  if (isVoid(value)) sum += fprintf(stderr, "VOID");
  if (isObject(value)) sum += fprintf(stderr, "obj: %p", asObject(value));

  sum += fprintf(stderr, ", int: %" PRId64 ", float: %g, ", value,
                 valueToNum(value));
  sum += fprintf(stderr, "hash: %" PRIx64 ", ", valueHash(value));

  if (isObject(value)) {
    sum += debugObject(asObject(value));
  } else inspectValue(stderr, value, 0);
  sum += fprintf(stderr, ")");
  return sum;
}

int debugObject(Obj *obj) {
  int sum = 0;
  sum += fprintf(stderr, "Obj(def: %p", obj->def);
  sum += fprintf(stderr, ", className: %s) ", obj->def->className);
  sum += inspectObject(stderr, obj, 0);
  return sum;
}

int debugTable(Table *table) {
  int out = 0;

  out += fprintf(stderr, "Table(capacity: %d, len: %d)\n", table->capacity,
                 table->length);
  out += fprintf(stderr, "Entries:\n");

  for (int i = 0; i < table->capacity; i++) {
    Entry *entry = &table->entries[i];
    out += fprintf(stderr, "[%d] ", i);
    out += inspectValue(stderr, entry->key, 1);
    out += fprintf(stderr, " => ");
    out += inspectValue(stderr, entry->value, 1);

    if (isVoid(entry->key)) {
      if (isNil(entry->value)) out += fprintf(stderr, " (empty)");
      else out += fprintf(stderr, " (tombstone)");
    }

    out += fprintf(stderr, "\n");
  }

  return out;
}

int debugValueTable() {
  return fprintf(stderr,
                 "VOID_VAL  =  %" PRId64 "\n"
                 "FALSE_VAL =  %" PRId64 "\n"
                 "TRUE_VAL  =  %" PRId64 "\n"
                 "NIL_VAL   = %" PRId64 "\n"
                 "OBJ_VAL   | %" PRId64 "\n"
                 "AS_OBJ    &  %" PRId64 "\n",
                 VOID_VAL, FALSE_VAL, TRUE_VAL, NIL_VAL, TAG_OBJ | QNAN,
                 ~(TAG_OBJ | QNAN));
}
