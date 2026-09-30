#ifndef MEMORY_POOL_H
#define MEMORY_POOL_H

#include <stdint.h>

struct memory_fixed{
  char *stack;                                                                 
  char *memory;

  uint64_t st_offset;
  uint64_t slot_size;
  uint64_t total_element;

  uint64_t flag;
  uint64_t v_off;
};

char *alloc_fixed(struct memory_fixed *mem);
void free_fixed(struct memory_fixed *fixed,char *memory);

#endif
