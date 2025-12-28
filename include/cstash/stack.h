#ifndef STACK_H
#define STACK_H

#include "result.h"
#include <stdbool.h>
#include <stdlib.h>

typedef struct cs_stack_node {
    struct cs_stack_node* next;
    char data[];
} CsStackNode;

typedef struct {
    CsStackNode* top;
    size_t size;
    size_t element_size;
} CsStack;

/**
 * Creates a new stack (takes ownership)
 * @param element_size Size in bytes of each element of the new stack
 * @return
 *  the newly created stack
 *  | NULL if it failed
 */
CsStack* cs_stack_create(size_t element_size);

/**
 * Destroy the given stack
 * @param stack Stack to destroy
 */
void cs_stack_destroy(CsStack* stack);

/**
 * Pop the top element (takes ownership)
 * @param stack Stack to pop from
 * @return
 *  a pointer to the popped element
 *  | NULL if stack is empty
 */
void* cs_stack_pop(CsStack* stack);

/**
 * Push an element to the top
 * @param stack Stack to push the new element to
 * @param element New element to push to the stack
 * @return
 *  CS_SUCCESS
 *  | CS_NULL_POINTER
 *  | CS_ALLOCATION_FAILED
 */
CsResult cs_stack_push(CsStack* stack, const void* element);

/**
 * Check if the stack is empty
 * @param stack Stack to check
 * @return
 *  true if stack is empty or NULL
 *  | false otherwise
 */
bool cs_stack_is_empty(const CsStack* stack);

/**
 * Clear the stack
 * @param stack Stack to clear
 */
void cs_stack_clear(CsStack* stack);

#endif // STACK_H
