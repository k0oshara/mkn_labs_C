#include "clist.h"
#include "point_list.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <math.h>

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

void print_point(intrusive_node_t *node, void *data){
	point_t* p = container_of(node, point_t, node);

	printf((char*) data, p->x, p->y);
}

void print(intrusive_list_t* list, char* s){
	apply(list, print_point, (void*) s);
  printf("\n");
}

void count_point(intrusive_node_t *node, void *data){
	(*(int*)data)++;
}

void count(intrusive_list_t* list){
	int k = 0;
	apply(list, count_point, &k);
	printf("%d\n", k);
}

void savetext(intrusive_list_t* list, FILE* f) {
  intrusive_node_t* list_head = list->head;
  while (list_head->next != NULL) {
        list_head = list_head->next;
  }
  while (list_head->prev != NULL) {
    point_t* point = container_of(list_head, point_t, node);

    int x = point->x, y = point->y;
    fprintf(f, "%d %d\n", x, y );   

    list_head = list_head->prev;
  }
}

void savebin(intrusive_list_t* list, FILE* f) {
  intrusive_node_t* list_head = list->head;
  while (list_head->next != NULL) {
        list_head = list_head->next;
  }
  while (list_head->prev != NULL) {
    point_t* point = container_of(list_head, point_t, node);

    int x = 0, y = 0; 
    if (point->x >= 0){
      x = point->x;
    }
    else{
      x = (int)pow(2,24) + point->x;
    }

    if (point->y >= 0){
      y = point->y;
    }
    else{
      y = (int)pow(2,24) + point->y;
    }

    fwrite(&x, 3, 1, f);
    fwrite(&y, 3, 1, f); 

    list_head = list_head->prev;
  }
}
