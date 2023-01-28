#ifndef lita_buffer_h
#define lita_buffer_h

#include "common.h"

typedef struct {
  u32 count;
  u32 capacity;
  u8 *bytes;
} Buffer;

Buffer newBuffer(int capacity);
void initBuffer(Buffer *buf);
void freeBuffer(Buffer *buf);

void growBuffer(Buffer *buf, u32 capacity);
u32 readBuffer(Buffer *buf, u32 offset, u8 *bytes, u32 count);
u32 writeBuffer(Buffer *buf, u32 offset, u8 *bytes, u32 count);
u32 appendBuffer(Buffer *buf, u8 *bytes, u32 count);
u32 appendCharToBuffer(Buffer *buf, char ch);
u32 appendStrToBuffer(Buffer *buf, char *str);

#endif
