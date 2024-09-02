#include <stdlib.h>

#include "buffer.h"
#include "memory.h"
#include "string.h"

Buffer new_buffer(usize capacity) {
  Buffer buf;
  init_buffer(&buf);
  resize_buffer(&buf, capacity);
  return buf;
}

void init_buffer(Buffer *buf) {
  buf->count = 0;
  buf->capacity = 0;
  buf->bytes = NULL;
}

void free_buffer(Buffer *buf) { resize_buffer(buf, 0); }

void resize_buffer(Buffer *buf, usize capacity) {
  if (capacity == buf->capacity) return;
  buf->bytes = GROW_ARRAY(u8, buf->bytes, buf->capacity, capacity);
  buf->capacity = capacity;
  if (capacity < buf->count) buf->count = capacity;
}

void grow_buffer(Buffer *buf, usize min_size) {
  if (min_size <= buf->capacity) return;
  usize capacity = buf->capacity || 1;
  while (capacity < min_size) capacity *= 2;
  resize_buffer(buf, capacity);
}

usize read_buffer(Buffer *buf, usize offset, u8 *bytes, usize count) {
  memcpy(bytes, buf->bytes + offset, count);
  return offset + count;
}

usize write_buffer(Buffer *buf, usize offset, u8 *bytes, usize count) {
  usize min_size = offset + count;
  grow_buffer(buf, min_size);
  if (min_size > buf->count) buf->count = min_size;

  memcpy(buf->bytes + offset, bytes, count);
  return offset + count;
}

usize append_buffer(Buffer *buf, u8 *bytes, usize count) {
  return write_buffer(buf, buf->count, bytes, count);
}

usize append_char_to_buffer(Buffer *buf, char ch) {
  return append_buffer(buf, (u8 *)&ch, 1);
}

usize append_str_to_buffer(Buffer *buf, char *str, usize length) {
  return append_buffer(buf, (u8 *)str, length);
}

ECS_COMPONENT_DECLARE(Buffer);

void BuffersImport(World *world) {
  ECS_MODULE(world, Buffers);

  ECS_COMPONENT_DEFINE(world, Buffer);
}
