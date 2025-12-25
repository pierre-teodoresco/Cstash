#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include "cstash/result.h"

#include <stdlib.h>

typedef struct cs_node {
    struct cs_node* prev;
    struct cs_node* next;
    void* data;
} CsNode;

typedef struct {
    CsNode* head;
    CsNode* tail;
    size_t size;
    size_t element_size;
} CsLinkedList;

/**
 * Creates a new linked list
 * Destroy it with linkedlist_destroy()
 * @return
 *  CsLinkedList*
 *  | NULL if it failed
 */
CsLinkedList* cs_linkedlist_create(size_t element_size);

/**
 * Destroy a given linkedlist
 * @param linkedlist Linked list to destroy, trying to use it after will result in a seg fault
 */
void cs_linkedlist_destroy(CsLinkedList* linkedlist);

/**
 * Insert a new element at the start
 * @param linkedlist Targeted linked list
 * @param element Element to insert
 * @return
 *  CS_SUCCESS
 *  | CS_NULL_POINTER
 */
CsResult cs_linkedlist_push_front(CsLinkedList* linkedlist, const void* element);

#endif // LINKEDLIST_H
