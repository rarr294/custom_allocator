#ifndef MEMORY_H
#define MEMORY_H

#include <stddef.h>

struct slot{
  char *memory;
  size_t slot_size;
  size_t offset = 0;
  size_t memory_size;
};

typedef unsigned long long uint64t;

char *slot_alloc(struct slot *ptr);
#endif
