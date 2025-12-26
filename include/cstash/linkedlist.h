#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include "cstash/result.h"

#include <stdbool.h>
#include <stdlib.h>

typedef struct cs_node {
    struct cs_node* prev;
    struct cs_node* next;
    char data[];
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
 * Check if empty
 * @param linkedlist Given linked list
 * @return
 *  true if linked list is empty
 *  | false otherwise
 */
bool cs_linkedlist_is_empty(const CsLinkedList* linkedlist);

/**
 * Return the size
 * @param linkedlist Given linkedlist
 * @return size of the list
 */
size_t cs_linkedlist_size(const CsLinkedList* linkedlist);

/**
 * Clear the list
 * @param linkedlist List to clear
 */
void cs_linkedlist_clear(CsLinkedList* linkedlist);

/**
 * Get the first element
 * @param linkedlist The linkedlist to retrieve the element from
 * @return
 *  first element of the list
 *  | NULL if linkedlist is empty
 */
void* cs_linkedlist_front(const CsLinkedList* linkedlist);

/**
 * Get the last element
 * @param linkedlist The linkedlist to retrieve the element from
 * @return
 *  last element of the list
 *  | NULL if linkedlist is empty
 */
void* cs_linkedlist_back(const CsLinkedList* linkedlist);

/**
 * Get an element at a given index
 * @param linkedlist The linkedlist to retrieve the element from
 * @param index Position of the data to retrieve
 * @return
 *  element at index
 *  | NULL if linkedlist is empty or index out of bounds
 */
void* cs_linkedlist_get(const CsLinkedList* linkedlist, size_t index);

/**
 * Insert a new element at the start
 * @param linkedlist Targeted linked list
 * @param element Element to insert, should not be NULL
 * @return
 *  CS_SUCCESS
 *  | CS_NULL_POINTER
 *  | CS_ALLOCATION_FAILED
 */
CsResult cs_linkedlist_push_front(CsLinkedList* linkedlist, const void* element);

/**
 * Insert a new element at the end
 * @param linkedlist Targeted linked list
 * @param element Element to insert, should not be NULL
 * @return
 *  CS_SUCCESS
 *  | CS_NULL_POINTER
 *  | CS_ALLOCATION_FAILED
 */
CsResult cs_linkedlist_push_back(CsLinkedList* linkedlist, const void* element);

/**
 * Insert a new element at a given index
 * @param linkedlist Targeted linked list
 * @param element Element to insert, should not be NULL
 * @param index Insert at this index
 * @return
 *  CS_SUCCESS
 *  | CS_NULL_POINTER
 *  | CS_ALLOCATION_FAILED
 *  | CS_OUT_OF_BOUNDS
 */
CsResult cs_linkedlist_insert_at(CsLinkedList* linkedlist, const void* element, size_t index);

/**
 * Pop first element (takes owernship)
 * @param linkedlist Targeted list
 * @return
 *  first element
 *  | NULL if linkedlist is empty
 */
void* cs_linkedlist_pop_front(CsLinkedList* linkedlist);

/**
 * Pop last element (takes owernship)
 * @param linkedlist Targeted list
 * @return
 *  last element
 *  | NULL if linkedlist is empty
 */
void* cs_linkedlist_pop_back(CsLinkedList* linkedlist);

/**
 * Remove element at index
 * @param linkedlist Targeted list
 * @param index Index of element to remove
 */
CsResult cs_linkedlist_remove_at(CsLinkedList* linkedlist, size_t index);

#endif // LINKEDLIST_H
