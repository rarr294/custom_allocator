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
     *(uint64_t*)(stack + 8 * (mem->st_offset -= 1))
  );

  return memory;
}

void free_slot(struct memory_pool *mem,char *stack,char *memoqry){
  uint64_t offset = (memory - mem->memory) / mem->slot_size;

  *(uint64_t*)(stack + 8 * mem->st_offset) = offset;
  mem->st_offset += 1;
}
