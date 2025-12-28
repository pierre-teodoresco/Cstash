#include "cstash/stack.h"
#include "cstash/result.h"

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

CsStack* cs_stack_create(size_t element_size) {
    if (element_size <= 0) return NULL;

    CsStack* stack = malloc(sizeof(CsStack));
    if (!stack) return NULL;

    stack->top = NULL;
    stack->size = 0;
    stack->element_size = element_size;

    return stack;
}

void cs_stack_destroy(CsStack* stack) {
    if (!stack) return;

    while (stack->top) {
        CsStackNode* next = stack->top->next;
        free(stack->top);
        stack->top = next;
    }

    free(stack);
}

void* cs_stack_pop(CsStack* stack) {
    if (!stack || stack->size == 0) return NULL;

    CsStackNode* top = stack->top;
    stack->top = top->next;
    stack->size--;

    void* data = malloc(stack->element_size);
    memcpy(data, top->data, stack->element_size);
    free(top);
    return data;
}

CsResult cs_stack_push(CsStack* stack, const void* element) {
    if (!stack || !element) return CS_NULL_POINTER;

    if (!stack->top) {
        stack->top = malloc(sizeof(CsStackNode) + stack->element_size);
        if (!stack->top) return CS_ALLOCATION_FAILED;
        stack->top->next = NULL;
    } else {
        CsStackNode* top = malloc(sizeof(CsStackNode) + stack->element_size);
        if (!top) return CS_ALLOCATION_FAILED;
        top->next = stack->top;
        stack->top = top;
    }
    memcpy(stack->top->data, element, stack->element_size);
    stack->size++;
    return CS_SUCCESS;
}

bool cs_stack_is_empty(const CsStack* stack) {
    return !stack || stack->size == 0;
}

void cs_stack_clear(CsStack* stack) {
    if (!stack) return;

    while (stack->top) {
        CsStackNode* next = stack->top->next;
        free(stack->top);
        stack->top = next;
    }
    stack->size = 0;
    stack->top = NULL;
}
