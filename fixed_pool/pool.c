#include "fixed_allocator.h"

char *alloc_slot(struct memory_pool *mem,char *stack){

  if(mem->flag){

    char *memory = (mem->memory + mem->slot_size * mem->v_off);
    ((mem->v_off += 1) == mem->total_element) ? (mem->flag = 0) : (0);

    return memory;
  }

  if(mem->st_offset == 0){
    return 0;
  }

  char *memory = (
     mem->memory    +
     mem->slot_size *
     get_offset(stack,(size_t)(mem->st_offset -= 1))
  );

  return memory;
}

void free_slot(struct memory_pool *mem,char *stack,char *memory){
  size_t offset = (memory - mem->memory) / mem->slot_size;
  memcpy((stack + sizeof(size_t) * mem->st_offset),&offset,sizeof(size_t));
  mem->st_offset += 1;
}
