#ifndef POINT_LIST_H
#define POINT_LIST_H

#include "clist.h"
#include <stdio.h>

void add_point(intrusive_list_t* list, int x, int y);
void remove_point(intrusive_list_t* list, int x, int y);
void remove_all_points(intrusive_list_t* list);
void print_point(intrusive_node_t *node, void *data);
void print(intrusive_list_t* list, char* s);
void count_point(intrusive_node_t *node, void *data);
void count(intrusive_list_t* list);
void savetext(intrusive_list_t* list, FILE* f);
void savebin(intrusive_list_t* list, FILE* f);

#endif
