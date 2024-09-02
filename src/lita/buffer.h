#ifndef lita_buffer_h
#define lita_buffer_h

#include "common.h"
#include "ecs.h"

typedef struct {
  usize count;
  usize capacity;
  union {
    u8 *bytes;
    char *chars;
  };
} Buffer;

Buffer new_buffer(usize capacity);
void init_buffer(Buffer *buf);
void free_buffer(Buffer *buf);

void resize_buffer(Buffer *buf, usize capacity);
void grow_buffer(Buffer *buf, usize min_size);
usize read_buffer(Buffer *buf, usize offset, u8 *bytes, usize count);
usize write_buffer(Buffer *buf, usize offset, u8 *bytes, usize count);
usize append_buffer(Buffer *buf, u8 *bytes, usize count);
usize append_char_to_buffer(Buffer *buf, char ch);
usize append_str_to_buffer(Buffer *buf, char *str, usize length);

extern ECS_COMPONENT_DECLARE(Buffer);

void BuffersImport(World *world);

#endif
