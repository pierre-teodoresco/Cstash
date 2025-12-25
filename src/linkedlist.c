#include "cstash/linkedlist.h"
#include "cstash/result.h"

#include <stdlib.h>

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
        next = NULL;
    }

    free(linkedlist);
}

CsResult cs_linkedlist_push_front(CsLinkedList* linkedlist, const void* element) {
    if (!linkedlist) return CS_NULL_POINTER;

    if (!linkedlist->head) {
    }

    return CS_SUCCESS;
}
