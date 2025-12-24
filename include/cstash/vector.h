#ifndef VECTOR_H
#define VECTOR_H

#include "result.h"

#include <stdlib.h>

#define VECTOR_DEFAULT_CAPACITY 8

typedef struct {
    size_t capacity;
    size_t size;
    size_t element_size;
    void* data;
} CsVector;

/**
 * Creates a new dynamic vector, gives ownership.
 * Destroy it with vector_destroy
 * @param element_size Size in bytes of each element of the new vector
 * @param capacity Capacity of the new vector
 * @return
 *  the newly created vector
 *  | NULL if it failed
 */
CsVector* vector_create(size_t element_size, size_t capacity);

/**
 * Destroy the given vector
 * @param vector Vector to destroy
 */
void vector_destroy(CsVector* vector);

/**
 * Reserve capacity
 * If capacity < size, data will be lost
 * @param vector Targetted vector
 * @param capacity New vector capacity
 * @return
 *  CS_SUCCESS
 *  | CS_NULL_POINTER
 *  | CS_ALLOCATION_FAILED
 */
CsResult vector_reserve(CsVector* vector, size_t capacity);

/**
 * Clear all elements, keep capacity
 * @param vector Vector to clear
 */
void vector_clear(CsVector* vector);

/**
 * Shrink vector's capacity to match the size
 * @param vector Vector to shrink
 * @return
 *  CS_SUCCESS
 *  | CS_NULL_POINTER
 *  | CS_ALLOCATION FAILED
 */
CsResult vector_shrink_to_fit(CsVector* vector);

/**
 * Get an element at a given index
 * @param vector Vector to fetch the element from
 * @param index Index of the returned element
 * @return
 *  the element at the given index
 *  | NULL if index out of bounds
 */
void* vector_get(const CsVector* vector, size_t index);

/**
 * Push an element at the end, do not take ownership of the element
 * @param vector Vector to push the new element to
 * @param element New element to push to the vector
 * @return
 *  CS_SUCCESS
 *  | CS_NULL_POINTER
 *  | CS_ALLOCATION_FAILED
 */
CsResult vector_push(CsVector* vector, const void* element);

/**
 * Pop the last element
 * @param vector Vector to pop to
 * @return
 *  a volatile pointer to the popped element, will be overwritten at next push
 *  | NULL if vector is empty
 */
void* vector_pop(CsVector* vector);

/**
 * Copy the given vector
 * @param vector Vector to copy
 * @return
 *  copied vector
 *  | NULL if the given vector is null or an error occured
 */
CsVector* vector_clone(const CsVector* vector);

#endif // VECTOR_H
