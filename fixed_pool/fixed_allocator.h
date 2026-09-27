#ifndef MEMORY_POOL_H
#define MEMORY_POOL_H

#include <stddef.h>
#include <stdint.h>
#include <string.h>

struct memory_pool{
  char *memory;
  uint64_t st_offset;
  uint64_t slot_size;
  uint64_t total_element;

  uint64_t flag;
  uint64_t v_off;
};

char *alloc_slot(struct memory_pool *mem,char *stack);
void free_slot(struct memory_pool *mem,char *stack,char *memory);


#endif