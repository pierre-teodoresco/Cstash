#include "cstash/hashmap.h"
#include "test_framework.h"
#include <string.h>

// ========================================
// Tests de création et destruction
// ========================================

void test_hashmap_create_destroy(void) {
    CsHashMap* map = cs_hashmap_create(sizeof(int));
    ASSERT_NOT_NULL(map);
    ASSERT_EQ(map->size, 0);
    ASSERT_EQ(map->capacity, HASHMAP_DEFAULT_CAPACITY);
    ASSERT_EQ(map->value_size, sizeof(int));
    ASSERT_NOT_NULL(map->buckets);
    cs_hashmap_destroy(map);
}

void test_hashmap_create_with_zero_size(void) {
    CsHashMap* map = cs_hashmap_create(0);
    ASSERT_NULL(map);
}

void test_hashmap_create_with_different_types(void) {
    // Test avec double
    CsHashMap* map_double = cs_hashmap_create(sizeof(double));
    ASSERT_NOT_NULL(map_double);
    ASSERT_EQ(map_double->value_size, sizeof(double));
    cs_hashmap_destroy(map_double);

    // Test avec char
    CsHashMap* map_char = cs_hashmap_create(sizeof(char));
    ASSERT_NOT_NULL(map_char);
    ASSERT_EQ(map_char->value_size, sizeof(char));
    cs_hashmap_destroy(map_char);

    // Test avec struct
    typedef struct {
        int x;
        int y;
    } Point;
    CsHashMap* map_point = cs_hashmap_create(sizeof(Point));
    ASSERT_NOT_NULL(map_point);
    ASSERT_EQ(map_point->value_size, sizeof(Point));
    cs_hashmap_destroy(map_point);
}

void test_hashmap_destroy_null(void) {
    // Ne devrait pas crash
    cs_hashmap_destroy(NULL);
}

// ========================================
// Tests de insert
// ========================================

void test_hashmap_insert_single(void) {
    CsHashMap* map = cs_hashmap_create(sizeof(int));
    int value = 42;

    CsResult result = cs_hashmap_insert(map, "key1", &value);
    ASSERT_EQ(result, CS_SUCCESS);
    ASSERT_EQ(map->size, 1);

    int* retrieved = (int*)cs_hashmap_get(map, "key1");
    ASSERT_NOT_NULL(retrieved);
    ASSERT_EQ(*retrieved, 42);

    cs_hashmap_destroy(map);
}

void test_hashmap_insert_multiple(void) {
    CsHashMap* map = cs_hashmap_create(sizeof(int));

    for (int i = 0; i < 10; i++) {
        char key[16];
        snprintf(key, sizeof(key), "key%d", i);
        CsResult result = cs_hashmap_insert(map, key, &i);
        ASSERT_EQ(result, CS_SUCCESS);
        ASSERT_EQ(map->size, (size_t)(i + 1));
    }

    // Vérifier toutes les valeurs
    for (int i = 0; i < 10; i++) {
        char key[16];
        snprintf(key, sizeof(key), "key%d", i);
        int* value = (int*)cs_hashmap_get(map, key);
        ASSERT_NOT_NULL(value);
        ASSERT_EQ(*value, i);
    }

    cs_hashmap_destroy(map);
}

void test_hashmap_insert_duplicate_key(void) {
    CsHashMap* map = cs_hashmap_create(sizeof(int));
    int value1 = 42;
    int value2 = 99;

    cs_hashmap_insert(map, "key", &value1);
    CsResult result = cs_hashmap_insert(map, "key", &value2);

    ASSERT_EQ(result, CS_CONFLICT);
    ASSERT_EQ(map->size, 1);

    // La valeur d'origine doit être préservée
    int* retrieved = (int*)cs_hashmap_get(map, "key");
    ASSERT_EQ(*retrieved, 42);

    cs_hashmap_destroy(map);
}

void test_hashmap_insert_null_hashmap(void) {
    int value = 42;
    CsResult result = cs_hashmap_insert(NULL, "key", &value);
    ASSERT_EQ(result, CS_NULL_POINTER);
}

void test_hashmap_insert_null_key(void) {
    CsHashMap* map = cs_hashmap_create(sizeof(int));
    int value = 42;
    CsResult result = cs_hashmap_insert(map, NULL, &value);
    ASSERT_EQ(result, CS_NULL_POINTER);
    cs_hashmap_destroy(map);
}

void test_hashmap_insert_null_value(void) {
    CsHashMap* map = cs_hashmap_create(sizeof(int));
    CsResult result = cs_hashmap_insert(map, "key", NULL);
    ASSERT_EQ(result, CS_NULL_POINTER);
    cs_hashmap_destroy(map);
}

void test_hashmap_insert_with_auto_resize(void) {
    CsHashMap* map = cs_hashmap_create(sizeof(int));
    size_t initial_capacity = map->capacity;

    // Insérer suffisamment d'éléments pour déclencher un resize
    // (load_factor > 0.75)
    int num_elements = (int)(initial_capacity * 0.75) + 2;

    for (int i = 0; i < num_elements; i++) {
        char key[16];
        snprintf(key, sizeof(key), "key%d", i);
        cs_hashmap_insert(map, key, &i);
    }

    ASSERT_TRUE(map->capacity > initial_capacity);
    ASSERT_EQ(map->size, (size_t)num_elements);

    // Vérifier que toutes les données sont encore accessibles
    for (int i = 0; i < num_elements; i++) {
        char key[16];
        snprintf(key, sizeof(key), "key%d", i);
        int* value = (int*)cs_hashmap_get(map, key);
        ASSERT_NOT_NULL(value);
        ASSERT_EQ(*value, i);
    }

    cs_hashmap_destroy(map);
}

// ========================================
// Tests de get et has
// ========================================

void test_hashmap_get_existing_key(void) {
    CsHashMap* map = cs_hashmap_create(sizeof(int));
    int value = 42;
    cs_hashmap_insert(map, "test", &value);

    int* retrieved = (int*)cs_hashmap_get(map, "test");
    ASSERT_NOT_NULL(retrieved);
    ASSERT_EQ(*retrieved, 42);

    cs_hashmap_destroy(map);
}

void test_hashmap_get_non_existing_key(void) {
    CsHashMap* map = cs_hashmap_create(sizeof(int));
    int value = 42;
    cs_hashmap_insert(map, "key1", &value);

    void* retrieved = cs_hashmap_get(map, "key2");
    ASSERT_NULL(retrieved);

    cs_hashmap_destroy(map);
}

void test_hashmap_get_null_hashmap(void) {
    void* retrieved = cs_hashmap_get(NULL, "key");
    ASSERT_NULL(retrieved);
}

void test_hashmap_get_null_key(void) {
    CsHashMap* map = cs_hashmap_create(sizeof(int));
    void* retrieved = cs_hashmap_get(map, NULL);
    ASSERT_NULL(retrieved);
    cs_hashmap_destroy(map);
}

void test_hashmap_has_existing_key(void) {
    CsHashMap* map = cs_hashmap_create(sizeof(int));
    int value = 42;
    cs_hashmap_insert(map, "test", &value);

    ASSERT_TRUE(cs_hashmap_has(map, "test"));

    cs_hashmap_destroy(map);
}

void test_hashmap_has_non_existing_key(void) {
    CsHashMap* map = cs_hashmap_create(sizeof(int));
    int value = 42;
    cs_hashmap_insert(map, "key1", &value);

    ASSERT_FALSE(cs_hashmap_has(map, "key2"));

    cs_hashmap_destroy(map);
}

void test_hashmap_has_null_hashmap(void) {
    ASSERT_FALSE(cs_hashmap_has(NULL, "key"));
}

void test_hashmap_has_null_key(void) {
    CsHashMap* map = cs_hashmap_create(sizeof(int));
    ASSERT_FALSE(cs_hashmap_has(map, NULL));
    cs_hashmap_destroy(map);
}

// ========================================
// Tests de remove
// ========================================

void test_hashmap_remove_existing_key(void) {
    CsHashMap* map = cs_hashmap_create(sizeof(int));
    int value = 42;
    cs_hashmap_insert(map, "test", &value);

    ASSERT_EQ(map->size, 1);
    CsResult result = cs_hashmap_remove(map, "test");
    ASSERT_EQ(result, CS_SUCCESS);
    ASSERT_EQ(map->size, 0);

    ASSERT_FALSE(cs_hashmap_has(map, "test"));
    ASSERT_NULL(cs_hashmap_get(map, "test"));

    cs_hashmap_destroy(map);
}

void test_hashmap_remove_non_existing_key(void) {
    CsHashMap* map = cs_hashmap_create(sizeof(int));
    int value = 42;
    cs_hashmap_insert(map, "key1", &value);

    CsResult result = cs_hashmap_remove(map, "key2");
    ASSERT_EQ(result, CS_NOT_FOUND);
    ASSERT_EQ(map->size, 1);

    cs_hashmap_destroy(map);
}

void test_hashmap_remove_from_bucket_chain(void) {
    CsHashMap* map = cs_hashmap_create(sizeof(int));

    // Insérer plusieurs éléments
    for (int i = 0; i < 5; i++) {
        char key[16];
        snprintf(key, sizeof(key), "key%d", i);
        cs_hashmap_insert(map, key, &i);
    }

    // Supprimer un élément du milieu
    cs_hashmap_remove(map, "key2");
    ASSERT_EQ(map->size, 4);
    ASSERT_FALSE(cs_hashmap_has(map, "key2"));

    // Vérifier que les autres éléments sont toujours là
    for (int i = 0; i < 5; i++) {
        if (i == 2) continue;
        char key[16];
        snprintf(key, sizeof(key), "key%d", i);
        ASSERT_TRUE(cs_hashmap_has(map, key));
    }

    cs_hashmap_destroy(map);
}

void test_hashmap_remove_null_hashmap(void) {
    CsResult result = cs_hashmap_remove(NULL, "key");
    ASSERT_EQ(result, CS_NULL_POINTER);
}

void test_hashmap_remove_null_key(void) {
    CsHashMap* map = cs_hashmap_create(sizeof(int));
    CsResult result = cs_hashmap_remove(map, NULL);
    ASSERT_EQ(result, CS_NULL_POINTER);
    cs_hashmap_destroy(map);
}

// ========================================
// Tests de clear
// ========================================

void test_hashmap_clear_empty(void) {
    CsHashMap* map = cs_hashmap_create(sizeof(int));
    size_t capacity_before = map->capacity;

    cs_hashmap_clear(map);
    ASSERT_EQ(map->size, 0);
    ASSERT_EQ(map->capacity, capacity_before);

    cs_hashmap_destroy(map);
}

void test_hashmap_clear_with_data(void) {
    CsHashMap* map = cs_hashmap_create(sizeof(int));

    // Ajouter des données
    for (int i = 0; i < 10; i++) {
        char key[16];
        snprintf(key, sizeof(key), "key%d", i);
        cs_hashmap_insert(map, key, &i);
    }

    size_t capacity_before = map->capacity;
    cs_hashmap_clear(map);

    ASSERT_EQ(map->size, 0);
    ASSERT_EQ(map->capacity, capacity_before);

    // Vérifier que toutes les clés ont été supprimées
    for (int i = 0; i < 10; i++) {
        char key[16];
        snprintf(key, sizeof(key), "key%d", i);
        ASSERT_FALSE(cs_hashmap_has(map, key));
    }

    // On peut re-insérer après clear
    int value = 99;
    cs_hashmap_insert(map, "new_key", &value);
    int* retrieved = (int*)cs_hashmap_get(map, "new_key");
    ASSERT_EQ(*retrieved, 99);

    cs_hashmap_destroy(map);
}

void test_hashmap_clear_null(void) {
    // Ne devrait pas crash
    cs_hashmap_clear(NULL);
}

// ========================================
// Tests de resize
// ========================================

void test_hashmap_resize_increase(void) {
    CsHashMap* map = cs_hashmap_create(sizeof(int));

    // Ajouter quelques éléments
    for (int i = 0; i < 5; i++) {
        char key[16];
        snprintf(key, sizeof(key), "key%d", i);
        cs_hashmap_insert(map, key, &i);
    }

    size_t old_capacity = map->capacity;
    CsResult result = cs_hashmap_resize(map, old_capacity * 2);

    ASSERT_EQ(result, CS_SUCCESS);
    ASSERT_EQ(map->capacity, old_capacity * 2);
    ASSERT_EQ(map->size, 5);

    // Vérifier que toutes les données sont encore accessibles
    for (int i = 0; i < 5; i++) {
        char key[16];
        snprintf(key, sizeof(key), "key%d", i);
        int* value = (int*)cs_hashmap_get(map, key);
        ASSERT_NOT_NULL(value);
        ASSERT_EQ(*value, i);
    }

    cs_hashmap_destroy(map);
}

void test_hashmap_resize_decrease(void) {
    CsHashMap* map = cs_hashmap_create(sizeof(int));

    // Augmenter d'abord la capacité
    cs_hashmap_resize(map, 32);

    // Ajouter quelques éléments
    for (int i = 0; i < 5; i++) {
        char key[16];
        snprintf(key, sizeof(key), "key%d", i);
        cs_hashmap_insert(map, key, &i);
    }

    // Réduire la capacité
    CsResult result = cs_hashmap_resize(map, 8);

    ASSERT_EQ(result, CS_SUCCESS);
    ASSERT_EQ(map->capacity, 8);
    ASSERT_EQ(map->size, 5);

    // Vérifier que toutes les données sont encore accessibles
    for (int i = 0; i < 5; i++) {
        char key[16];
        snprintf(key, sizeof(key), "key%d", i);
        int* value = (int*)cs_hashmap_get(map, key);
        ASSERT_NOT_NULL(value);
        ASSERT_EQ(*value, i);
    }

    cs_hashmap_destroy(map);
}

void test_hashmap_resize_same_capacity(void) {
    CsHashMap* map = cs_hashmap_create(sizeof(int));
    size_t capacity = map->capacity;

    CsResult result = cs_hashmap_resize(map, capacity);
    ASSERT_EQ(result, CS_SUCCESS);
    ASSERT_EQ(map->capacity, capacity);

    cs_hashmap_destroy(map);
}

void test_hashmap_resize_null_hashmap(void) {
    CsResult result = cs_hashmap_resize(NULL, 16);
    ASSERT_EQ(result, CS_NULL_POINTER);
}

// ========================================
// Tests de types complexes
// ========================================

void test_hashmap_with_structs(void) {
    typedef struct {
        int id;
        double value;
        char name[16];
    } Record;

    CsHashMap* map = cs_hashmap_create(sizeof(Record));

    Record r1 = {1, 3.14, "first"};
    Record r2 = {2, 2.71, "second"};
    Record r3 = {3, 1.41, "third"};

    cs_hashmap_insert(map, "rec1", &r1);
    cs_hashmap_insert(map, "rec2", &r2);
    cs_hashmap_insert(map, "rec3", &r3);

    Record* retrieved1 = (Record*)cs_hashmap_get(map, "rec1");
    Record* retrieved2 = (Record*)cs_hashmap_get(map, "rec2");
    Record* retrieved3 = (Record*)cs_hashmap_get(map, "rec3");

    ASSERT_EQ(retrieved1->id, 1);
    ASSERT_EQ(retrieved2->id, 2);
    ASSERT_EQ(retrieved3->id, 3);
    ASSERT_STR_EQ(retrieved1->name, "first");
    ASSERT_STR_EQ(retrieved2->name, "second");
    ASSERT_STR_EQ(retrieved3->name, "third");

    cs_hashmap_destroy(map);
}

void test_hashmap_with_string_values(void) {
    CsHashMap* map = cs_hashmap_create(sizeof(char*));

    char* str1 = "Hello";
    char* str2 = "World";
    char* str3 = "HashMap";

    cs_hashmap_insert(map, "greeting", &str1);
    cs_hashmap_insert(map, "noun", &str2);
    cs_hashmap_insert(map, "datastructure", &str3);

    char** retrieved1 = (char**)cs_hashmap_get(map, "greeting");
    char** retrieved2 = (char**)cs_hashmap_get(map, "noun");
    char** retrieved3 = (char**)cs_hashmap_get(map, "datastructure");

    ASSERT_STR_EQ(*retrieved1, "Hello");
    ASSERT_STR_EQ(*retrieved2, "World");
    ASSERT_STR_EQ(*retrieved3, "HashMap");

    cs_hashmap_destroy(map);
}

// ========================================
// Tests de collisions
// ========================================

void test_hashmap_collision_handling(void) {
    CsHashMap* map = cs_hashmap_create(sizeof(int));

    // Forcer une petite capacité pour augmenter les collisions
    cs_hashmap_resize(map, 4);

    // Insérer plusieurs éléments qui pourraient causer des collisions
    for (int i = 0; i < 20; i++) {
        char key[16];
        snprintf(key, sizeof(key), "key%d", i);
        CsResult result = cs_hashmap_insert(map, key, &i);
        ASSERT_EQ(result, CS_SUCCESS);
    }

    ASSERT_EQ(map->size, 20);

    // Vérifier que tous les éléments sont accessibles
    for (int i = 0; i < 20; i++) {
        char key[16];
        snprintf(key, sizeof(key), "key%d", i);
        int* value = (int*)cs_hashmap_get(map, key);
        ASSERT_NOT_NULL(value);
        ASSERT_EQ(*value, i);
    }

    cs_hashmap_destroy(map);
}

// ========================================
// Tests de stress
// ========================================

void test_hashmap_large_dataset(void) {
    CsHashMap* map = cs_hashmap_create(sizeof(int));

    // Insérer 1000 éléments
    for (int i = 0; i < 1000; i++) {
        char key[16];
        snprintf(key, sizeof(key), "key%d", i);
        CsResult result = cs_hashmap_insert(map, key, &i);
        ASSERT_EQ(result, CS_SUCCESS);
    }

    ASSERT_EQ(map->size, 1000);

    // Vérifier quelques valeurs
    int* val0 = (int*)cs_hashmap_get(map, "key0");
    int* val500 = (int*)cs_hashmap_get(map, "key500");
    int* val999 = (int*)cs_hashmap_get(map, "key999");

    ASSERT_EQ(*val0, 0);
    ASSERT_EQ(*val500, 500);
    ASSERT_EQ(*val999, 999);

    cs_hashmap_destroy(map);
}

void test_hashmap_insert_remove_cycle(void) {
    CsHashMap* map = cs_hashmap_create(sizeof(int));

    // Cycle d'insertion/suppression
    for (int cycle = 0; cycle < 100; cycle++) {
        char key[16];
        snprintf(key, sizeof(key), "key%d", cycle);

        cs_hashmap_insert(map, key, &cycle);
        ASSERT_TRUE(cs_hashmap_has(map, key));

        cs_hashmap_remove(map, key);
        ASSERT_FALSE(cs_hashmap_has(map, key));
    }

    ASSERT_EQ(map->size, 0);
    cs_hashmap_destroy(map);
}

void test_hashmap_key_variations(void) {
    CsHashMap* map = cs_hashmap_create(sizeof(int));

    // Tester différents types de clés
    int v1 = 1, v2 = 2, v3 = 3, v4 = 4, v5 = 5;

    cs_hashmap_insert(map, "simple", &v1);
    cs_hashmap_insert(map, "key_with_underscores", &v2);
    cs_hashmap_insert(map, "key-with-dashes", &v3);
    cs_hashmap_insert(map, "KeyWithCamelCase", &v4);
    cs_hashmap_insert(map, "key.with.dots", &v5);

    ASSERT_EQ(*(int*)cs_hashmap_get(map, "simple"), 1);
    ASSERT_EQ(*(int*)cs_hashmap_get(map, "key_with_underscores"), 2);
    ASSERT_EQ(*(int*)cs_hashmap_get(map, "key-with-dashes"), 3);
    ASSERT_EQ(*(int*)cs_hashmap_get(map, "KeyWithCamelCase"), 4);
    ASSERT_EQ(*(int*)cs_hashmap_get(map, "key.with.dots"), 5);

    cs_hashmap_destroy(map);
}

void test_hashmap_empty_string_key(void) {
    CsHashMap* map = cs_hashmap_create(sizeof(int));
    int value = 42;

    CsResult result = cs_hashmap_insert(map, "", &value);
    ASSERT_EQ(result, CS_SUCCESS);

    ASSERT_TRUE(cs_hashmap_has(map, ""));
    int* retrieved = (int*)cs_hashmap_get(map, "");
    ASSERT_NOT_NULL(retrieved);
    ASSERT_EQ(*retrieved, 42);

    cs_hashmap_destroy(map);
}

void test_hashmap_long_key(void) {
    CsHashMap* map = cs_hashmap_create(sizeof(int));
    int value = 42;

    char long_key[256];
    memset(long_key, 'a', 255);
    long_key[255] = '\0';

    CsResult result = cs_hashmap_insert(map, long_key, &value);
    ASSERT_EQ(result, CS_SUCCESS);

    ASSERT_TRUE(cs_hashmap_has(map, long_key));
    int* retrieved = (int*)cs_hashmap_get(map, long_key);
    ASSERT_NOT_NULL(retrieved);
    ASSERT_EQ(*retrieved, 42);

    cs_hashmap_destroy(map);
}

void test_hashmap_overwrite_protection(void) {
    CsHashMap* map = cs_hashmap_create(sizeof(int));

    int original = 100;
    int attempt = 200;

    cs_hashmap_insert(map, "protected", &original);
    CsResult result = cs_hashmap_insert(map, "protected", &attempt);

    ASSERT_EQ(result, CS_CONFLICT);

    int* value = (int*)cs_hashmap_get(map, "protected");
    ASSERT_EQ(*value, 100); // Valeur originale préservée

    cs_hashmap_destroy(map);
}

// ========================================
// Main
// ========================================

int main(void) {
    TEST_INIT();

    printf("\n" COLOR_MAGENTA "########## HASHMAP TESTS ##########" COLOR_RESET "\n");

    printf("\n" COLOR_BLUE "========== CREATION & DESTRUCTION ==========" COLOR_RESET "\n");
    RUN_TEST(test_hashmap_create_destroy);
    RUN_TEST(test_hashmap_create_with_zero_size);
    RUN_TEST(test_hashmap_create_with_different_types);
    RUN_TEST(test_hashmap_destroy_null);

    printf("\n" COLOR_BLUE "========== INSERT ==========" COLOR_RESET "\n");
    RUN_TEST(test_hashmap_insert_single);
    RUN_TEST(test_hashmap_insert_multiple);
    RUN_TEST(test_hashmap_insert_duplicate_key);
    RUN_TEST(test_hashmap_insert_null_hashmap);
    RUN_TEST(test_hashmap_insert_null_key);
    RUN_TEST(test_hashmap_insert_null_value);
    RUN_TEST(test_hashmap_insert_with_auto_resize);

    printf("\n" COLOR_BLUE "========== GET & HAS ==========" COLOR_RESET "\n");
    RUN_TEST(test_hashmap_get_existing_key);
    RUN_TEST(test_hashmap_get_non_existing_key);
    RUN_TEST(test_hashmap_get_null_hashmap);
    RUN_TEST(test_hashmap_get_null_key);
    RUN_TEST(test_hashmap_has_existing_key);
    RUN_TEST(test_hashmap_has_non_existing_key);
    RUN_TEST(test_hashmap_has_null_hashmap);
    RUN_TEST(test_hashmap_has_null_key);

    printf("\n" COLOR_BLUE "========== REMOVE ==========" COLOR_RESET "\n");
    RUN_TEST(test_hashmap_remove_existing_key);
    RUN_TEST(test_hashmap_remove_non_existing_key);
    RUN_TEST(test_hashmap_remove_from_bucket_chain);
    RUN_TEST(test_hashmap_remove_null_hashmap);
    RUN_TEST(test_hashmap_remove_null_key);

    printf("\n" COLOR_BLUE "========== CLEAR ==========" COLOR_RESET "\n");
    RUN_TEST(test_hashmap_clear_empty);
    RUN_TEST(test_hashmap_clear_with_data);
    RUN_TEST(test_hashmap_clear_null);

    printf("\n" COLOR_BLUE "========== RESIZE ==========" COLOR_RESET "\n");
    RUN_TEST(test_hashmap_resize_increase);
    RUN_TEST(test_hashmap_resize_decrease);
    RUN_TEST(test_hashmap_resize_same_capacity);
    RUN_TEST(test_hashmap_resize_null_hashmap);

    printf("\n" COLOR_BLUE "========== COMPLEX TYPES ==========" COLOR_RESET "\n");
    RUN_TEST(test_hashmap_with_structs);
    RUN_TEST(test_hashmap_with_string_values);

    printf("\n" COLOR_BLUE "========== COLLISIONS ==========" COLOR_RESET "\n");
    RUN_TEST(test_hashmap_collision_handling);

    printf("\n" COLOR_BLUE "========== STRESS TESTS ==========" COLOR_RESET "\n");
    RUN_TEST(test_hashmap_large_dataset);
    RUN_TEST(test_hashmap_insert_remove_cycle);
    RUN_TEST(test_hashmap_key_variations);
    RUN_TEST(test_hashmap_empty_string_key);
    RUN_TEST(test_hashmap_long_key);
    RUN_TEST(test_hashmap_overwrite_protection);

    TEST_SUMMARY();

    return tests_failed > 0 ? 1 : 0;
}
