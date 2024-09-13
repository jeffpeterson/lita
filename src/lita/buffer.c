#include <stdlib.h>

#include "buffer.h"
#include "memory.h"

Buffer newBuffer(usize capacity) {
  Buffer buf;
  initBuffer(&buf);
  resizeBuffer(&buf, capacity);
  return buf;
}

void initBuffer(Buffer *buf) {
  buf->count = 0;
  buf->capacity = 0;
  buf->bytes = NULL;
}

void freeBuffer(Buffer *buf) { resizeBuffer(buf, 0); }

void resizeBuffer(Buffer *buf, usize capacity) {
  if (capacity == buf->capacity) return;
  buf->bytes = GROW_ARRAY(u8, buf->bytes, buf->capacity, capacity);
  buf->capacity = capacity;
  if (capacity < buf->count) buf->count = capacity;
}

void growBuffer(Buffer *buf, usize min_size) {
  if (min_size <= buf->capacity) return;
  usize capacity = buf->capacity || 1;
  while (capacity < min_size) capacity *= 2;
  resizeBuffer(buf, capacity);
}

usize readBuffer(Buffer *buf, usize offset, u8 *bytes, usize count) {
  memcpy(bytes, buf->bytes + offset, count);
  return offset + count;
}

usize writeBuffer(Buffer *buf, usize offset, u8 *bytes, usize count) {
  usize min_size = offset + count;
  growBuffer(buf, min_size);
  if (min_size > buf->count) buf->count = min_size;

  memcpy(buf->bytes + offset, bytes, count);
  return offset + count;
}

usize appendBuffer(Buffer *buf, u8 *bytes, usize count) {
  return writeBuffer(buf, buf->count, bytes, count);
}

usize appendCharToBuffer(Buffer *buf, char ch) {
  return appendBuffer(buf, (u8 *)&ch, 1);
}

usize appendStrToBuffer(Buffer *buf, char *str, usize length) {
  return appendBuffer(buf, (u8 *)str, length);
}

ECS_COMPONENT_DECLARE(Buffer);

void BuffersImport(World *world) {
  ECS_MODULE(world, Buffers);

  ECS_COMPONENT_DEFINE(world, Buffer);
}
