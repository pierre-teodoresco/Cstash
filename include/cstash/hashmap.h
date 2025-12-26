#ifndef HASHMAP_H
#define HASHMAP_H

#include "result.h"

#include <stdbool.h>
#include <stdlib.h>

#define HASHMAP_DEFAULT_CAPACITY 8
#define HASHMAP_MAX_LOAD_FACTOR 0.75

typedef struct cs_hashmap_entry {
    struct cs_hashmap_entry* next;
    char* key;
    char data[];
} CsHashMapEntry;

typedef struct {
    size_t capacity;
    size_t size;
    size_t value_size;
    CsHashMapEntry** buckets;
} CsHashMap;

/**
 * Creates a new HashMap (takes ownership)
 * @param value_size Size in bytes of each value that will be stored in the HashMap
 * @return
 *  the newly created HashMap
 *  | NULL if value_size == 0 or if it failed
 */
CsHashMap* cs_hashmap_create(size_t value_size);

/**
 * Destroy the given HashMap
 * @param hashmap HashMap to destroy
 */
void cs_hashmap_destroy(CsHashMap* hashmap);

/**
 * Get a value using the given key
 * @param hashmap Hashmap to retrieve the value from
 * @param key Associated key
 * @return
 *  the value associated to the given key
 *  | NULL if the tuple <key, value> does not exists
 */
void* cs_hashmap_get(const CsHashMap* hashmap, const char* key);

/**
 * Check if a key exists
 * @param hashmap Hashmap to check
 * @param key Key to look for
 * @return
 *  true if the key exists
 *  | false otherwise
 */
bool cs_hashmap_has(const CsHashMap* hashmap, const char* key);

/**
 * Insert a value
 * @param hashmap Hashmap to insert to
 * @param key String key
 * @param value The value associated to the given key
 * return
 *  CS_SUCCESS
 *  | CS_NULL_POINTER
 *  | CS_ALLOCATION_FAILED
 *  | CS_CONFLICT
 */
CsResult cs_hashmap_insert(CsHashMap* hashmap, const char* key, const void* value);

/**
 * Remove a value associated to a given key
 * @param hashmap Targeted Hashmap
 * @param key String key associated to the value to remove
 * @return
 *  CS_SUCCESS
 *  | CS_NULL_POINTER
 *  | CS_NOT_FOUND
 */
CsResult cs_hashmap_remove(CsHashMap* hashmap, const char* key);

/**
 * Clear all tuples <key, value>
 * @param hashmap Hashmap to clear
 */
void cs_hashmap_clear(CsHashMap* hashmap);

/**
 * Resize the hashmap
 * @param hashmap Hashmap to resize
 * @param new_capacity New capacity (number of buckets)
 * @return
 *  CS_SUCCESS
 *  | CS_NULL_POINTER
 *  | CS_ALLOCATION_FAILED
 */
CsResult cs_hashmap_resize(CsHashMap* hashmap, size_t new_capacity);

#endif // HASHMAP_H
