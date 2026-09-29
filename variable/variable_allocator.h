#ifndef VARIABLE_SIZE_H
#define VARIABLE_SIZE_H

#include <stdint.h>

struct slot{
  char flag;
  char *memory;
  uint64_t size;
  struct slot *prev;
  struct slot *next;
};

struct memory_variable{
  char *memory;
  uint64_t size;
  uint64_t offset;

  struct slot *head;
  struct slot *headt;
};

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


struct slot *alloc_variable(struct memory_fixed *mem_fixed,
                            struct memory_variable *mem_var,
                            uint64_t size);

void free_variable(struct memory_fixed *mem,struct slot *mem);

#endif
