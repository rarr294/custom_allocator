#include "slab_allocator.h"

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

void lookup(uint64_t num){
  char n = 1;
  char idx = 63;

  while((num & (n << idx)) == 0){
    idx--;
  }

  return idx + 1;
}

void alloc_slab(struct memory_slab *mem_slab,
                struct memory_object *mem){

  if(mem_slab->slab_config == 2){
     mem->memory = alloc_fixed(&free_list2[lookup(mem->size)]);
     return;
  }
}

void free_slab(struct memory_fixed *mem_fixed,
               struct memory_slab *mem_slab,
               struct memory_object *mem){
  
  if(mem_slab->slab_config == 2){
     free_fixed(&free_list2[lookup(mem->size)],mem->memory);
     return;
  }
}
