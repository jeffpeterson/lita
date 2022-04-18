#include <stdlib.h>

#include "buffer.h"
#include "memory.h"
#include "string.h"

Buffer newBuffer(int capacity) {
  Buffer buf;
  initBuffer(&buf);
  growBuffer(&buf, capacity);
  return buf;
}

void initBuffer(Buffer *buf) {
  buf->count = 0;
  buf->capacity = 0;
  buf->bytes = NULL;
}

void freeBuffer(Buffer *buf) {
  FREE_ARRAY(u8, buf->bytes, buf->capacity);
  initBuffer(buf);
}

void growBuffer(Buffer *buf, u32 capacity) {
  if (capacity == buf->capacity) return;
  buf->bytes = GROW_ARRAY(u8, buf->bytes, buf->capacity, capacity);
  buf->capacity = capacity;
}

u32 readBuffer(Buffer *buf, u32 offset, u8 *bytes, u32 count) {
  memcpy(bytes, buf->bytes + offset, count);
  return offset + count;
}

u32 writeBuffer(Buffer *buf, u32 offset, u8 *bytes, u32 count) {
  u32 minSize = offset + count;
  if (minSize > buf->capacity) growBuffer(buf, minSize);
  if (minSize > buf->count) buf->count = minSize;

  memcpy(buf->bytes + offset, bytes, count);
  return offset + count;
}

u32 appendBuffer(Buffer *buf, u8 *bytes, u32 count) {
  return writeBuffer(buf, buf->count, bytes, count);
}

u32 appendCharToBuffer(Buffer *buf, char ch) {
  return appendBuffer(buf, (u8 *)&ch, 1);
}

u32 appendStrToBuffer(Buffer *buf, char *str) {
  return appendBuffer(buf, (u8 *)str, strlen(str));
}
