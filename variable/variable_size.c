#include "variable_size_allocator.h"

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

struct slot *alloc_variable(struct memory_fixed *mem_fixed,
                            struct memory_variable *mem_var,
                            uint64_t size){

  static char exe = 0;

  if(mem_var->offset != mem_var->size){

    if(size > ((mem_var->size - 1) - mem_var->offset + 1)){
      return 0;
    }

    struct slot *ptr = (struct slot*)alloc_fixed(mem_fixed);

    ptr->next = 0;
    ptr->size = size;
    ptr->memory = mem_var->memory + mem_var->offset;

    mem_var->offset += size;

    mem_var->headt->next = ptr;
    mem_var->headt = ptr;

    if(exe == 0){
      mem_var->head = ptr;
      exe = 1;
    }

    return ptr;
  }

  struct slot *head = mem_var->head;

  while(head){

    if(head->flag == 0){

      if(head->size == size){
        head->flag = 1;
        return head;
      }

      if(head->size > size){

        struct slot *ptr = alloc_fixed(memory_fixed);

        ptr->flag = 0;
        ptr->size = head->size - size;
        ptr->memory = head->memory + size;
        ptr->next = head->next;

        head->flag = 1;
        head->size = size;
        head->next = ptr;

        return head;
      }
    }

    head = head->next;
  }

  return 0;
}

void free_variable(struct memory_fixed *mem,struct slot *mem){
  struct slot *node = mem->next;

  while(node && node->flag == 0){
    mem->size += node->size;
    node = node->next;
  }
}
