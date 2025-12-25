#include "cstash/vector.h"
#include "cstash/result.h"

#include <stdlib.h>
#include <string.h>

CsVector* cs_vector_create(size_t element_size, size_t capacity) {
    CsVector* vector = malloc(sizeof(CsVector));
    if (!vector) return NULL;

    vector->capacity = capacity == 0 ? VECTOR_DEFAULT_CAPACITY : capacity;
    vector->size = 0;
    vector->element_size = element_size;
    vector->data = malloc(element_size * vector->capacity);
    if (!vector->data) {
        free(vector);
        return NULL;
    }

    return vector;
}

void cs_vector_destroy(CsVector* vector) {
    if (!vector) return;
    free(vector->data);
    free(vector);
}

CsResult cs_vector_reserve(CsVector* vector, size_t capacity) {
    if (!vector) return CS_NULL_POINTER;

    if (capacity < vector->size) vector->size = capacity;
    void* new_data = realloc(vector->data, vector->element_size * capacity);
    if (!new_data) return CS_ALLOCATION_FAILED;

    vector->data = new_data;
    vector->capacity = capacity;
    return CS_SUCCESS;
}

void cs_vector_clear(CsVector* vector) {
    if (!vector) return;
    vector->size = 0;
}

CsResult cs_vector_shrink_to_fit(CsVector* vector) {
    if (!vector) return CS_NULL_POINTER;

    size_t new_capacity = vector->size == 0 ? 1 : vector->size;
    void* new_data = realloc(vector->data, vector->element_size * new_capacity);
    if (!new_data) return CS_ALLOCATION_FAILED;

    vector->data = new_data;
    vector->capacity = new_capacity;
    return CS_SUCCESS;
}

void* cs_vector_get(const CsVector* vector, size_t index) {
    if (!vector || index >= vector->size) return NULL;
    return (unsigned char*)vector->data + vector->element_size * index;
}

CsResult cs_vector_push(CsVector* vector, const void* element) {
    if (!vector || !element) return CS_NULL_POINTER;

    if (vector->size >= vector->capacity) {
        if (vector->capacity == 0) vector->capacity = 1;
        void* new_data = realloc(vector->data, vector->element_size * vector->capacity * 2);
        if (!new_data) return CS_ALLOCATION_FAILED;
        vector->data = new_data;
        vector->capacity *= 2;
    }

    void* tail = (unsigned char*)vector->data + vector->element_size * vector->size;
    memcpy(tail, element, vector->element_size);

    vector->size++;
    return CS_SUCCESS;
}

void* cs_vector_pop(CsVector* vector) {
    if (!vector || vector->size == 0) return NULL;
    vector->size--;
    return (unsigned char*)vector->data + vector->element_size * vector->size;
}

CsVector* cs_vector_clone(const CsVector* vector) {
    if (!vector) return NULL;

    CsVector* copy = cs_vector_create(vector->element_size, vector->capacity);
    if (!copy) return NULL;

    memcpy(copy->data, vector->data, vector->element_size * vector->size);
    copy->size = vector->size;
    return copy;
}
