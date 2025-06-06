#ifndef CLIST_H_
#define CLIST_H_

#include <stddef.h>

#define container_of(ptr, type, member) (type*)((char*)(ptr) - offsetof(type, member))

typedef struct intrusive_node {
  struct intrusive_node* next;
  struct intrusive_node* prev;
} intrusive_node_t;

typedef struct intrusive_list {
  struct intrusive_node* head; //фиктивный элемент 
} intrusive_list_t;

void init_list(intrusive_list_t* list);
void add_node(intrusive_list_t* list, intrusive_node_t* node);
void remove_node(intrusive_node_t* node);

int get_length(intrusive_list_t* list);

#endif
