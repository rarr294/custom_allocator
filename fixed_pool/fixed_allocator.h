#ifndef MEMORY_POOL_H
#define MEMORY_POOL_H

#include <stddef.h>
#include <stdint.h>
#include <string.h>

struct memory_pool{
  char *memory;
  size_t st_offset;
  size_t slot_size;
  size_t total_element;

  size_t flag;
  size_t v_off;
};

char *alloc_slot(struct memory_pool *mem,char *stack);
void free_slot(struct memory_pool *mem,char *stack,char *memory);

size_t get_offset(char *stack,size_t offset){
  size_t value;
  memcpy(&value,(stack + sizeof(size_t) * offset),sizeof(size_t));
  return value;
}

#endif
