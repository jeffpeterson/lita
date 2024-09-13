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

Buffer newBuffer(usize capacity);
void initBuffer(Buffer *buf);
void freeBuffer(Buffer *buf);

void resizeBuffer(Buffer *buf, usize capacity);
void growBuffer(Buffer *buf, usize min_size);
usize readBuffer(Buffer *buf, usize offset, u8 *bytes, usize count);
usize writeBuffer(Buffer *buf, usize offset, u8 *bytes, usize count);
usize appendBuffer(Buffer *buf, u8 *bytes, usize count);
usize appendCharToBuffer(Buffer *buf, char ch);
usize appendStrToBuffer(Buffer *buf, char *str, usize length);

extern ECS_COMPONENT_DECLARE(Buffer);

void BuffersImport(World *world);

#endif
