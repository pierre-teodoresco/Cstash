#include "cstash/hashmap.h"
#include "cstash/result.h"

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

CsHashMap* cs_hashmap_create(size_t value_size) {
    if (value_size == 0) return NULL;

    CsHashMap* hashmap = malloc(sizeof(CsHashMap));
    if (!hashmap) return NULL;

    hashmap->value_size = value_size;
    hashmap->capacity = HASHMAP_DEFAULT_CAPACITY;
    hashmap->size = 0;
    hashmap->buckets = calloc(hashmap->capacity, sizeof(CsHashMapEntry*));
    if (!hashmap->buckets) {
        free(hashmap);
        return NULL;
    }

    return hashmap;
}

void cs_hashmap_destroy(CsHashMap* hashmap) {
    if (!hashmap) return;

    for (size_t i = 0; i < hashmap->capacity; i++) {
        CsHashMapEntry* current = hashmap->buckets[i];
        while (current) {
            CsHashMapEntry* next = current->next;
            free(current->key);
            free(current);
            current = next;
        }
    }
    free(hashmap->buckets);
    free(hashmap);
}

uint64_t cs_hash_fnv1a(const char* key) {
    uint64_t hash = 0xcbf29ce484222325ULL;
    while (*key) {
        hash ^= (uint8_t)(*key++);
        hash *= 0x100000001b3ULL;
    }
    return hash;
}

void* cs_hashmap_get(const CsHashMap* hashmap, const char* key) {
    if (!hashmap || !key) return NULL;

    size_t index = cs_hash_fnv1a(key) % hashmap->capacity;
    CsHashMapEntry* bucket = hashmap->buckets[index];

    while (bucket) {
        if (strcmp(bucket->key, key) == 0) return bucket->data;
        bucket = bucket->next;
    }
    return NULL;
}

bool cs_hashmap_has(const CsHashMap* hashmap, const char* key) {
    if (!hashmap || !key) return false;

    size_t index = cs_hash_fnv1a(key) % hashmap->capacity;
    CsHashMapEntry* bucket = hashmap->buckets[index];

    while (bucket) {
        if (strcmp(bucket->key, key) == 0) return true;
        bucket = bucket->next;
    }
    return false;
}

CsHashMapEntry* cs_hashmap_new_entry(const char* key, const void* value, size_t value_size) {
    CsHashMapEntry* entry = malloc(sizeof(CsHashMapEntry) + value_size);
    if (!entry) return NULL;

    entry->key = strdup(key);
    if (!entry->key) {
        free(entry);
        return NULL;
    }

    entry->next = NULL;
    memcpy(entry->data, value, value_size);
    return entry;
}

CsResult cs_hashmap_insert(CsHashMap* hashmap, const char* key, const void* value) {
    if (!hashmap || !key || !value) return CS_NULL_POINTER;

    size_t index = cs_hash_fnv1a(key) % hashmap->capacity;
    CsHashMapEntry* bucket = hashmap->buckets[index];

    if (!bucket) {
        hashmap->buckets[index] = cs_hashmap_new_entry(key, value, hashmap->value_size);
        if (!hashmap->buckets[index]) return CS_ALLOCATION_FAILED;
        hashmap->size++;
    } else {
        while (bucket) {
            if (strcmp(bucket->key, key) == 0) {
                return CS_CONFLICT;
            }
            if (!bucket->next) break;
            bucket = bucket->next;
        }

        bucket->next = cs_hashmap_new_entry(key, value, hashmap->value_size);
        if (!bucket->next) return CS_ALLOCATION_FAILED;
        hashmap->size++;
    }

    // Vérifier le load factor après TOUTE insertion
    float load_factor = (float)hashmap->size / hashmap->capacity;
    if (load_factor > HASHMAP_MAX_LOAD_FACTOR) {
        cs_hashmap_resize(hashmap, hashmap->capacity * 2);
    }

    return CS_SUCCESS;
}

CsResult cs_hashmap_remove(CsHashMap* hashmap, const char* key) {
    if (!hashmap || !key) return CS_NULL_POINTER;

    size_t index = cs_hash_fnv1a(key) % hashmap->capacity;
    CsHashMapEntry* current = hashmap->buckets[index];
    CsHashMapEntry* prev = NULL;

    while (current) {
        if (strcmp(current->key, key) == 0) {
            // we found the key, we can remove the entry
            if (!prev) {
                // current is the first entry of the bucket
                hashmap->buckets[index] = current->next;
            } else {
                prev->next = current->next;
            }
            free(current->key);
            free(current);
            hashmap->size--;
            return CS_SUCCESS;
        }
        prev = current;
        current = current->next;
    }
    return CS_NOT_FOUND;
}

void cs_hashmap_clear(CsHashMap* hashmap) {
    if (!hashmap || hashmap->size == 0) return;

    for (size_t i = 0; i < hashmap->capacity; i++) {
        CsHashMapEntry* bucket = hashmap->buckets[i];
        while (bucket) {
            CsHashMapEntry* next = bucket->next;
            free(bucket->key);
            free(bucket);
            bucket = next;
        }
        hashmap->buckets[i] = NULL;
    }
    hashmap->size = 0;
}

CsResult cs_hashmap_resize(CsHashMap* hashmap, size_t new_capacity) {
    if (!hashmap) return CS_NULL_POINTER;

    if (new_capacity < 0) new_capacity = HASHMAP_DEFAULT_CAPACITY;
    if (new_capacity == hashmap->capacity) return CS_SUCCESS;

    CsHashMapEntry** old_buckets = hashmap->buckets;
    size_t old_capacity = hashmap->capacity;

    hashmap->buckets = calloc(new_capacity, sizeof(CsHashMapEntry*));
    if (!hashmap->buckets) {
        hashmap->buckets = old_buckets;
        return CS_ALLOCATION_FAILED;
    }

    hashmap->capacity = new_capacity;
    hashmap->size = 0;

    for (size_t i = 0; i < old_capacity; i++) {
        CsHashMapEntry* current = old_buckets[i];
        while (current) {
            CsHashMapEntry* next = current->next;

            size_t new_index = cs_hash_fnv1a(current->key) % new_capacity;
            current->next = hashmap->buckets[new_index];
            hashmap->buckets[new_index] = current;
            hashmap->size++;

            current = next;
        }
    }

    free(old_buckets);
    return CS_SUCCESS;
}
