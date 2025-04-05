#include "clist.h"
#include <assert.h>
#include <stdlib.h>

void init_list(intrusive_list_t* list) {
    list->head = malloc(sizeof(intrusive_node_t));
    assert(list->head != NULL);
    list->head->next = NULL;
    list->head->prev = NULL;
}

void add_node(intrusive_list_t* list, intrusive_node_t* node) {
	assert(node != NULL);
    node->next = list->head->next;
    if (list->head->next != NULL) {
        list->head->next->prev = node;
    }
    list->head->next = node;
    node->prev = list->head;
}

void remove_node(intrusive_node_t* node) {
    intrusive_node_t* node_prev = node->prev;
    intrusive_node_t* node_next = node->next;	

    if (node->next != NULL) {
        node_prev->next = node_next;
        node_next->prev = node_prev;
    } 
    else {
        node_prev->next = NULL;
    }
    node->prev = NULL;
    node->next = NULL;	
}

void apply(intrusive_list_t *list, void (*op)(intrusive_node_t *node, void *data), void *data){
    intrusive_node_t* list_head = list->head;
    while (list_head->next != NULL) {
        list_head = list_head->next;
    }
    while (list_head->prev != NULL) {
        op(list_head, data);
        list_head = list_head->prev;
    }
}
