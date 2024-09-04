#include <stdarg.h>
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
  fprintf(stderr, "╔═ " FG_MAGENTA "%s" FG_DEFAULT " \n", name);
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

static void byte(uint8_t arg) { fprintf(stderr, " %02x", arg); }
static void arrow() { fputs("\t\e[2m->\e[22m ", stderr); }
static void newline() { fputs("\n", stderr); }

int disassembleInstruction(Chunk *chunk, int offset) {
  uint8_t *code = chunk->code;
  fprintf(stderr, RESET "║ %04x ", offset);

  if (offset > 0 && chunk->lines[offset] == chunk->lines[offset - 1])
    fprintf(stderr, DIM "   │ " NO_DIM);
  else fprintf(stderr, FG_CYAN "%4d " FG_DEFAULT, chunk->lines[offset]);

  uint8_t instruction = code[offset++];
  OpInfo info = op_info[instruction];

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
    uint8_t arg = code[offset++];
    byte(arg);
    arrow();
    inspect_value(stderr, chunk->constants.values[arg]);
    break;
  }

  case CONSTANT_BYTE: {
    u8 cnst = code[offset++];
    byte(cnst);
    byte(code[offset++]);
    arrow();
    inspect_value(stderr, chunk->constants.values[cnst]);
    break;
  }

  case INVOKE: {
    uint8_t constant = code[offset++];
    uint8_t argCount = code[offset++];
    byte(constant);
    byte(argCount);
    arrow();
    inspect_value(stderr, chunk->constants.values[constant]);
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
    uint8_t constant = code[offset - 1];
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
    uint8_t args = code[offset - 1];
    arrow();
    fprintf(stderr, "%x %x", args >> 4, args & 0x0f);
    break;
  }
  default:;
  }

  if (chunk->comments && chunk->comments[offset - 1]) {
    fprintf(stderr, DIM "\t// ");
    inspect_value(stderr, chunk->comments[offset - 1]);
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
      fg(color);
      fprintf(stderr, "[newline]\n");
      printIndents(indent);
      break;
    case TOKEN_DEDENT:
      fg(color);
      fputs("[dedent]\n", stderr);
      printIndents(--indent);
      break;
    case TOKEN_ERROR:
      fg(color);
      fprintf(stderr, "[error: %.*s]\n", token.length, token.start);
      printIndents(indent);
      break;
    case TOKEN_EOF: fputs("[EOF]\n", stderr); break;
    default: fg(color); fprintf(stderr, "%.*s ", token.length, token.start);
    }

  } while (token.type != TOKEN_EOF);
  fprintf(stderr, FG_DEFAULT);
  resetScanner();
}

static void debugValues(Value *start, int length) {
  int offsets[length];
  // int frameIndex = 0;
  for (int i = 0; i < length; i++) {
    offsets[i] = fprintf(stderr, "[ ") + inspect_value(stderr, start[i]) +
                 fprintf(stderr, " ]");
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

void debugExecution() {
  fprintf(stderr, RESET "║" DIM "      -->" NO_DIM);
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
    for (int i = 0; i < vm.frameCount; i++)
      if (vm.frames[i].closure)
        fprintf(stderr, "[ Frame %s ]",
                vm.frames[i].closure->function->name->chars);
      else if (vm.frames[i].native)
        fprintf(stderr, "[ Native %s ]", vm.frames[i].native->name->chars);
      else fprintf(stderr, "[ Unknown frame ]");
  }

  fprintf(stderr, DIM "\n");
  if (frame->ip)
    disassembleInstruction(
        &frame->closure->function->chunk,
        (int)(frame->ip - frame->closure->function->chunk.code));
  fprintf(stderr, NO_DIM);
  prev_frame = frame;
}
