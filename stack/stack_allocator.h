#ifndef STACK_ALLOCATOR_H
#define STACK_ALLOCATOR_H

#include <stddef.h>
#include <stdint.h>

struct memory_pool{

  char *memory;
  uint64_t *stack;

  uint64_t size;

  uint64_t st_off;
  uint64_t mem_off;

};

char *alloc(struct memory_pool *mem,uint64_t size);

void free_memory(struct memory_pool *mem);

#endif
