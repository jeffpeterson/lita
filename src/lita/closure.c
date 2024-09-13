#include <assert.h>

#include "closure.h"
#include "memory.h"
#include "native.h"
#include "string.h"
#include "term.h"
#include "vm.h"

ObjClosure *newClosure(ObjFunction *function) {
  ObjUpvalue **upvalues = ALLOCATE(ObjUpvalue *, function->upvalueCount);
  for (int i = 0; i < function->upvalueCount; i++) upvalues[i] = NULL;

  ObjClosure *closure = allocateClosure();
  closure->function = function;
  closure->upvalues = upvalues;
  closure->upvalueCount = function->upvalueCount;
  return closure;
}

static int closureLength(Obj *obj) {
  ObjClosure *closure = (ObjClosure *)obj;
  return closure->function->arity;
}

static void markClosure(Obj *obj) {
  ObjClosure *closure = (ObjClosure *)obj;
  markObject((Obj *)closure->function);
  for (int i = 0; i < closure->upvalueCount; i++) {
    markObject((Obj *)closure->upvalues[i]);
  }
}

static void freeClosure(Obj *obj) {
  ObjClosure *closure = (ObjClosure *)obj;
  FREE_ARRAY(ObjUpvalue *, closure->upvalues, closure->upvalueCount);
}

static int inspectClosure(Obj *obj, FILE *io) {
  ObjClosure *closure = (ObjClosure *)obj;
  return fprintf(io,
                 FG_MAGENTA "<closure %s" FG_DEFAULT "/" FG_MAGENTA
                            "%d>" FG_DEFAULT,
                 closure->function->name->chars, closure->function->arity) -
         FG_SIZE * 4;
}

/**
 * Move the instruction pointer (ip) to a new a closure along with arguments on
 * the stack.
 *
 * Returns whether or not the call was successful.
 */
static InterpretResult callClosure(Obj *obj, int argCount) {
  ObjClosure *closure = (ObjClosure *)obj;
  ObjFunction *fun = closure->function;

  if (argCount < fun->arity)
    return runtimeError("Expected %d arguments but got %d.", fun->arity,
                        argCount);

  if (fun->variadic) {
    vmArray(argCount - fun->arity);
    argCount = fun->arity + 1;
  }

  CallFrame *existing_frame = &vm.frames[vm.frameCount - 1];

  if (existing_frame->obj == obj && *(existing_frame->ip) == OP_RETURN) {
    // Tail-call optimization.
    copyValues(vm.stackTop - argCount, existing_frame->slots + 1, argCount);
    vm.stackTop = existing_frame->slots + argCount + 1;
    existing_frame->ip = fun->chunk.code;
    existing_frame->prevIp = NULL;
    return INTERPRET_OK;
  }

  if (vm.frameCount == FRAMES_MAX) return runtimeError("Call stack overflow.");

  CallFrame *frame = newFrame(obj, argCount + 1);
  if (!frame) return runtimeError("Call stack overflow.");
  frame->ip = fun->chunk.code;

  return INTERPRET_OK;
}

NATIVE_GETTER(Closure, function, OBJ_VAL);
NATIVE_DELEGATE(Closure, name, function);
NATIVE_DELEGATE(Closure, arity, function);
NATIVE_DELEGATE(Closure, bytes, function);
NATIVE_DELEGATE(Closure, byteCount, function);

REGISTER_OBJECT_DEF(Closure);
const ObjDef Closure = {
    .className = "Closure",
    .size = sizeof(ObjClosure),
    .mark = markClosure,
    .free = freeClosure,
    .call = callClosure,
    .inspect = inspectClosure,
    .length = closureLength,
};
