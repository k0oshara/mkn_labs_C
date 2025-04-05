#include "clist.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

typedef struct point {
  int x, y;
  intrusive_node_t node;
} point_t;

void add_point(intrusive_list_t* list, int x, int y) {
  point_t* point = (point_t*)malloc(sizeof(point_t));
  assert(point != NULL);
  point->x = x;
  point->y = y;
  add_node(list, &(point->node));
}

void remove_point(intrusive_list_t* list, int x, int y) {
  intrusive_node_t* list_head = list->head;

  while (list_head->next != NULL) {
    point_t* point = container_of(list_head->next, point_t, node);

    if (point->x == x && point->y == y) {
      intrusive_node_t* next = list_head->next->next;
      remove_node(list_head->next);
      free(point);
      list_head->next = next;
    } 
    else {
      list_head = list_head->next;
    }
  }
}

void show_all_points(intrusive_list_t* list) {
  intrusive_node_t* list_head = list->head;
  
  while (list_head->next != NULL) {
    point_t* point = container_of(list_head->next, point_t, node);

    if (list_head->next->next != NULL){
      printf("(%d %d) ", point->x, point->y );
    }
    else{
      printf("(%d %d)", point->x, point->y );
    }

    list_head = list_head->next;
  }
  printf("%c", '\n');
}

void remove_all_points(intrusive_list_t* list) {  
  intrusive_node_t* list_head = list->head;
  while (list_head->next != NULL) {
    intrusive_node_t* list_head = list->head;
    point_t* point = container_of(list_head->next, point_t, node);
    intrusive_node_t* list_head_next = list_head->next->next;
    remove_node(&(point->node));
    free(point);
    list_head->next = list_head_next;
  }
}

int main() {
   // //usage

   //   intrusive_list_t l;
   //   init_list(&l);

   //   add_point(&l, 10, 10);
   //   add_point(&l, 20, 20);

   //   show_all_points(&l);
   //   //free(l.head);

   //   return 0;
  intrusive_list_t list;
  init_list(&list);
  char s[239];
  
  while (1){
    scanf("%239s", s);

    if (strcmp(s,"exit") == 0){
      break;
    }

    else if (strcmp(s,"add") == 0){
      int x,y;
      scanf("%d %d", &x, &y);
      add_point(&list, x, y);
    }

    else if (strcmp(s,"rm") == 0){
      int x,y;
      scanf("%d %d", &x, &y);
      remove_point(&list, x, y);
    }

    else if (strcmp(s,"print") == 0){
      show_all_points(&list);
    }

    else if (strcmp(s,"rma") == 0){
      remove_all_points(&list);
    }

    else if (strcmp(s,"len") == 0){
      int k = get_length(&list);
      printf("%d\n",k);
    }
    else{
      printf("Unknown command\n");
    }
  }

  remove_all_points(&list);
  free(list.head);
  return 0;
}
