#ifndef SLAB_ALLOCATOR
#define SLAB_ALLOCATOR

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

struct memory_slab{
   char *memory;
   char slab_config;
   uint64_t total_size_class;

   struct memory_fixed *free_list1;
   struct memory_fixed free_list2[64];
};

struct memory_object{
  char *memory;
  uint64_t size;
};

void lookup(uint64_t num);

void init_slab(struct memory_slab *mem_slab);

char *alloc_fixed(struct memory_fixed *mem);
void free_fixed(struct memory_fixed *fixed,char *memory);

void alloc_slab(struct memory_slab *mem_slab,
                 struct memory_object *mem);

void free_slab(struct memory_fixed *mem_fixed,
                struct memory_slab *mem_slab,
                struct memory_object *mem);

#endif
