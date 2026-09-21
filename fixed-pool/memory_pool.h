#ifndef MEMORY_POOL_H
#define MEMORY_POOL_H

#include <stddef.h>

struct memory{
  char *mem;
  size_t slot_size;
  size_t total_element;
};

struct free_list{
  free_list *next;
  size_t offset = 0;
};

char *free_slot(struct slot *mem,struct free_list *list);

char *alloc_slot(struct slot *mem,struct free_list *list);

void init_free_list(struct slot *mem,struct free_list *list,char *memory){
}


#endif
