#include <stdlib.h>

#include "buffer.h"
#include "memory.h"

Buffer newBuffer(int len) {
  Buffer buf;
  initBuffer(&buf);
  growBuffer(&buf, len);
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
  int oldCapacity = buf->capacity;
  buf->capacity = capacity;
  buf->bytes = GROW_ARRAY(u8, buf->bytes, oldCapacity, buf->capacity);
}

u32 readBuffer(Buffer *buf, u32 offset, u8 *bytes, u32 count) {
  memcpy(bytes, buf->bytes + offset, count);
  return offset + count;
}

u32 writeBuffer(Buffer *buf, u32 offset, u8 *bytes, u32 count) {
  u32 minSize = offset + count;
  if (minSize > buf->capacity)
    growBuffer(buf, minSize);

  memcpy(buf->bytes + offset, bytes, count);
  return offset + count;
}

u32 appendBuffer(Buffer *buf, u8 *bytes, u32 count) {
  return writeBuffer(buf, buf->count, bytes, count);
}
