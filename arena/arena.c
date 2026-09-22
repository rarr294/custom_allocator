#include "arena_memory.h"

char *alloc(struct memory_pool *mem,uint64_t size){

  if(size > mem->size - mem->offset){
    return 0;
  }

  char *memory = (mem->memory + mem->offset);
  mem->offset += size;
  return memory;
}
