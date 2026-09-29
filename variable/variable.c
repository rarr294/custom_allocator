#include <stdio.h>z
#include <sys/mman.h>
#include "variable_allocator.h"

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

  static char fflag = 0;

  if(mem_var->offset != mem_var->size){

    if(size > ((mem_var->size - 1) - mem_var->offset + 1)){
      return 0;
    }

    struct slot *ptr = (struct slot*)alloc_fixed(mem_fixed);

    ptr->next = 0;
    ptr->flag = 1;
    ptr->size = size;
    ptr->memory = mem_var->memory + mem_var->offset;
    mem_var->offset += size;

    (fflag == 0) ? (
      fflag = 1,
      ptr->prev = 0,
      mem_var->head = ptr
    ) : (
      ptr->prev = mem_var->headt,
      ptr->prev->next = ptr
    );

    mem_var->headt = ptr;
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

        struct slot *ptr = (struct slot*)alloc_fixed(mem_fixed);

        ptr->flag = 0;
        ptr->size = head->size - size;
        ptr->memory = head->memory + size;

        ptr->prev = head;
        ptr->next = head->next;

        head->flag = 1;
        head->size = size;

        head->next = ptr;

        (ptr->next != 0) ? (
          ptr->next->prev = ptr
        ) : (0);

        return head;
      }
    }

    head = head->next;
  }

  return 0;
}

void free_variable(struct memory_fixed *mem,struct slot *nodeL){

  char exeL = 0;
  char exeR = 0;

  uint64_t sum = 0;
  struct slot *nodeR = nodeL->next;

  while(nodeR && nodeR->flag == 0){
    exeR = 1;
    struct slot *tmp = nodeR;

    sum += nodeR->size;
    nodeR = nodeR->next;

    free_fixed(mem,(char*)tmp);
  }

  while(nodeL->prev && nodeL->prev->flag == 0){
     exeL = 1;
     struct slot *tmp = nodeL;

     sum += nodeL->size;
     nodeL = nodeL->prev;

     free_fixed(mem,(char*)tmp);
  }

  if(exeL == 0 && exeR == 0){
    nodeL->flag = 0;
    return;
  }

  nodeL->size += sum;
  nodeL->next = nodeR;

  (nodeR != 0) ? (
    nodeR->prev = nodeL
  ) : (0);
}
