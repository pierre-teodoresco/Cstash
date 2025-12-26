#ifndef HASHMAP_H
#define HASHMAP_H

#include <stdlib.h>

#define HASHMAP_DEFAULT_CAPACITY 8

typedef struct cs_hashmap_entry {
    struct cs_hashmap_entry* next;
    char* key;
    char data[];
} CsHashMapEntry;

typedef struct {
    size_t capacity;
    size_t size;
    size_t element_size;
    CsHashMapEntry** buckets;
} CsHashMap;

/**
 * Creates a new HashMap (takes ownership)
 * @param element_size Size in bytes of each element that will be stored in the HashMap
 * @return
 *  the newly created HashMap
 *  | NULL if it failed
 */
CsHashMap* cs_hashmap_create(size_t element_size);

/**
 * Destroy the given HashMap
 * @param hashmap HashMap to destroy
 */
void cs_hashmap_destroy(CsHashMap* hashmap);

#endif // HASHMAP_H
