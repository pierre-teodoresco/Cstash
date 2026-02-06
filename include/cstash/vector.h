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
    void (*destructor)(void*);
} CsVector;

/**
 * Creates a new dynamic vector
 * @param element_size Size in bytes of each element of the new vector
 * @param capacity Capacity of the new vector
 * @param destructor Optional destructor that will be called on each element when the vector is destroyed.
 * If NULL no cleanup is done on data
 * @return
 *  the newly created vector
 *  | NULL if it failed
 *
 */
CsVector* cs_vector_create(size_t element_size, size_t capacity, void (*destructor)(void*));

/**
 * Destroy the given vector
 * @param vector Vector to destroy
 */
void cs_vector_destroy(CsVector* vector);

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
CsResult cs_vector_reserve(CsVector* vector, size_t capacity);

/**
 * Clear all elements, keep capacity
 * @param vector Vector to clear
 */
void cs_vector_clear(CsVector* vector);

/**
 * Shrink vector's capacity to match the size
 * @param vector Vector to shrink
 * @return
 *  CS_SUCCESS
 *  | CS_NULL_POINTER
 *  | CS_ALLOCATION FAILED
 */
CsResult cs_vector_shrink_to_fit(CsVector* vector);

/**
 * Get an element at a given index (borrow)
 * @param vector Vector to fetch the element from
 * @param index Index of the returned element
 * @return
 *  the element at the given index
 *  | NULL if index out of bounds
 */
void* cs_vector_get(const CsVector* vector, size_t index);

/**
 * Push an element at the end
 * @param vector Vector to push the new element to
 * If a destructor is set, it copies the element. If not it just reference it
 * @param element New element to push to the vector
 * @return
 *  CS_SUCCESS
 *  | CS_NULL_POINTER
 *  | CS_ALLOCATION_FAILED
 */
CsResult cs_vector_push(CsVector* vector, const void* element);

/**
 * Pop the last element
 * @param vector Vector to pop to
 * @return
 *  a volatile pointer to the popped element, will be overwritten at next push
 *  | NULL if vector is empty
 */
void* cs_vector_pop(CsVector* vector);

/**
 * Copy the given vector
 * @param vector Vector to copy
 * @return
 *  copied vector
 *  | NULL if the given vector is null or an error occured
 */
CsVector* cs_vector_clone(const CsVector* vector);

#endif // VECTOR_H
