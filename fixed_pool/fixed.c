#include "fixed_allocator.h"

char *alloc_fixed(struct memory_fixed *mem){

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
     *(uint64_t*)(mem->stack + 8 * (mem->st_offset -= 1))
  );

  return memory;
}

void free_fixed(struct memory_fixed *mem,char *memory){
  uint64_t offset = (memory - mem->memory) / mem->slot_size;

  *(uint64_t*)(mem->stack + 8 * mem->st_offset) = offset;
  mem->st_offset += 1;
}
