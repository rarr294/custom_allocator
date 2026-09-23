#include <stddef.h>
#include "memory.h"

char *slot_alloc(struct slot *ptr){

  if(ptr->offset == ptr->memory_size){
    return 0;
  }

  char *memory = (ptr->memory + ptr->offset);
  ptr->offset = (ptr->offset + ptr->slot_size);

  return memory;
}
