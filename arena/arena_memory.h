#ifndef ARENA_MEMORY_H
#define ARENA_MEMORY_H

#include <stddef.h>

struct memory_pool{
  char *memory;
  uint64_t size;
  uint64_t offset;
};

char *alloc(struct memory_pool *mem,uint64_t size);

#endif

