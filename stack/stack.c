#include "stack_allocator.h"

char *alloc(struct memory_pool *mem,uint64_t size){

  if(size > ((mem->size - 1) - mem->mem_off + 1)){
    return 0;
  }

  *(mem->stack + (mem->st_off++)) = mem->mem_off;

  char *memory = (mem->memory + mem->mem_off);
  mem->mem_off += size;

  return memory;
}

void free_memory(struct memory_pool *mem){
  mem->mem_off = *(mem->stack + (--mem->st_off));
}


