#include "cstash/linkedlist.h"
#include "cstash/result.h"

#include <stdlib.h>
#include <string.h>

CsLinkedList* cs_linkedlist_create(size_t element_size) {
    if (element_size == 0) return NULL;

    CsLinkedList* linkedlist = malloc(sizeof(CsLinkedList));
    if (!linkedlist) return NULL;

    linkedlist->head = NULL;
    linkedlist->tail = NULL;
    linkedlist->size = 0;
    linkedlist->element_size = element_size;

    return linkedlist;
}

void cs_linkedlist_destroy(CsLinkedList* linkedlist) {
    if (!linkedlist) return;

    CsNode* it = linkedlist->head;
    while (it) {
        CsNode* next = it->next;
        free(it);
        it = next;
    }
    free(linkedlist);
}

bool cs_linkedlist_is_empty(const CsLinkedList* linkedlist) {
    return linkedlist->size == 0;
}

size_t cs_linkedlist_size(const CsLinkedList* linkedlist) {
    if (!linkedlist) return 0;
    return linkedlist->size;
}

void cs_linkedlist_clear(CsLinkedList* linkedlist) {
    if (!linkedlist) return;

    CsNode* it = linkedlist->head;
    while (it) {
        CsNode* next = it->next;
        free(it);
        it = next;
    }
    linkedlist->size = 0;
    linkedlist->head = NULL;
    linkedlist->tail = NULL;
}

void* cs_linkedlist_front(const CsLinkedList* linkedlist) {
    if (!linkedlist || linkedlist->size == 0) return NULL;
    return linkedlist->head->data;
}

void* cs_linkedlist_back(const CsLinkedList* linkedlist) {
    if (!linkedlist || linkedlist->size == 0) return NULL;
    return linkedlist->tail->data;
}

void* cs_linkedlist_get(const CsLinkedList* linkedlist, size_t index) {
    if (!linkedlist || index >= linkedlist->size) return NULL;

    if (index == 0) return linkedlist->head->data;
    CsNode* it = linkedlist->head;
    for (size_t i = 0; i < index; i++) {
        it = it->next;
    }
    if (!it) return NULL;
    return it->data;
}

CsResult cs_linkedlist_push_front(CsLinkedList* linkedlist, const void* element) {
    if (!linkedlist || !element) return CS_NULL_POINTER;

    CsNode* new_node = malloc(sizeof(CsNode) + linkedlist->element_size);
    if (!new_node) return CS_ALLOCATION_FAILED;
    new_node->prev = NULL;
    new_node->next = linkedlist->head;
    memcpy(new_node->data, element, linkedlist->element_size);

    if (!linkedlist->head) {
        linkedlist->tail = linkedlist->head = new_node;
    } else {
        linkedlist->head->prev = new_node;
        linkedlist->head = new_node;
    }
    linkedlist->size++;
    return CS_SUCCESS;
}

CsResult cs_linkedlist_push_back(CsLinkedList* linkedlist, const void* element) {
    if (!linkedlist || !element) return CS_NULL_POINTER;

    CsNode* new_node = malloc(sizeof(CsNode) + linkedlist->element_size);
    if (!new_node) return CS_ALLOCATION_FAILED;
    new_node->prev = linkedlist->tail;
    new_node->next = NULL;
    memcpy(new_node->data, element, linkedlist->element_size);

    if (!linkedlist->head) {
        linkedlist->head = linkedlist->tail = new_node;
    } else {
        linkedlist->tail->next = new_node;
        linkedlist->tail = new_node;
    }
    linkedlist->size++;
    return CS_SUCCESS;
}

CsResult cs_linkedlist_insert_at(CsLinkedList* linkedlist, const void* element, size_t index) {
    if (!linkedlist || !element) return CS_NULL_POINTER;
    if (index > linkedlist->size) return CS_OUT_OF_BOUNDS;

    if (index == 0) return cs_linkedlist_push_front(linkedlist, element);
    if (index == linkedlist->size) return cs_linkedlist_push_back(linkedlist, element);

    CsNode* it = linkedlist->head;
    for (size_t i = 0; i < index; i++) {
        it = it->next;
    }

    CsNode* new_node = malloc(sizeof(CsNode) + linkedlist->element_size);
    if (!new_node) return CS_ALLOCATION_FAILED;

    new_node->prev = it->prev;
    new_node->next = it;
    memcpy(new_node->data, element, linkedlist->element_size);

    it->prev->next = new_node;
    it->prev = new_node;

    linkedlist->size++;
    return CS_SUCCESS;
}
