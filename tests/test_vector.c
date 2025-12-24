#include "cstash/vector.h"
#include "test_framework.h"
#include <string.h>

// ========================================
// Tests de création et destruction
// ========================================

void test_create_destroy(void) {
    CsVector* vec = vector_create(sizeof(int), 8);
    ASSERT_NOT_NULL(vec);
    ASSERT_EQ(vec->size, 0);
    ASSERT_EQ(vec->capacity, 8);
    ASSERT_EQ(vec->element_size, sizeof(int));
    ASSERT_NOT_NULL(vec->data);
    vector_destroy(vec);
}

void test_create_with_zero_capacity(void) {
    CsVector* vec = vector_create(sizeof(int), 0);
    ASSERT_NOT_NULL(vec);
    ASSERT_EQ(vec->capacity, VECTOR_DEFAULT_CAPACITY);
    ASSERT_EQ(vec->size, 0);
    vector_destroy(vec);
}

void test_create_with_different_types(void) {
    // Test avec double
    CsVector* vec_double = vector_create(sizeof(double), 4);
    ASSERT_NOT_NULL(vec_double);
    ASSERT_EQ(vec_double->element_size, sizeof(double));
    vector_destroy(vec_double);

    // Test avec char
    CsVector* vec_char = vector_create(sizeof(char), 16);
    ASSERT_NOT_NULL(vec_char);
    ASSERT_EQ(vec_char->element_size, sizeof(char));
    vector_destroy(vec_char);

    // Test avec struct
    typedef struct {
        int x;
        int y;
    } Point;
    CsVector* vec_point = vector_create(sizeof(Point), 10);
    ASSERT_NOT_NULL(vec_point);
    ASSERT_EQ(vec_point->element_size, sizeof(Point));
    vector_destroy(vec_point);
}

void test_destroy_null(void) {
    // Ne devrait pas crash
    vector_destroy(NULL);
}

// ========================================
// Tests de push, pop et get
// ========================================

void test_push_single(void) {
    CsVector* vec = vector_create(sizeof(int), 4);
    int value = 42;

    CsResult result = vector_push(vec, &value);
    ASSERT_EQ(result, CS_SUCCESS);
    ASSERT_EQ(vec->size, 1);

    int* retrieved = (int*)vector_get(vec, 0);
    ASSERT_NOT_NULL(retrieved);
    ASSERT_EQ(*retrieved, 42);

    vector_destroy(vec);
}

void test_push_multiple(void) {
    CsVector* vec = vector_create(sizeof(int), 4);

    for (int i = 0; i < 10; i++) {
        CsResult result = vector_push(vec, &i);
        ASSERT_EQ(result, CS_SUCCESS);
        ASSERT_EQ(vec->size, (size_t)(i + 1));
    }

    for (int i = 0; i < 10; i++) {
        int* value = (int*)vector_get(vec, i);
        ASSERT_NOT_NULL(value);
        ASSERT_EQ(*value, i);
    }

    vector_destroy(vec);
}

void test_push_with_reallocation(void) {
    CsVector* vec = vector_create(sizeof(int), 2);
    ASSERT_EQ(vec->capacity, 2);

    // Push au-delà de la capacité initiale
    for (int i = 0; i < 5; i++) {
        vector_push(vec, &i);
    }

    ASSERT_EQ(vec->size, 5);
    ASSERT_TRUE(vec->capacity >= 5);

    // Vérifier que les données sont intactes
    for (int i = 0; i < 5; i++) {
        int* value = (int*)vector_get(vec, i);
        ASSERT_EQ(*value, i);
    }

    vector_destroy(vec);
}

void test_push_null_vector(void) {
    int value = 42;
    CsResult result = vector_push(NULL, &value);
    ASSERT_EQ(result, CS_NULL_POINTER);
}

void test_push_null_element(void) {
    CsVector* vec = vector_create(sizeof(int), 4);
    CsResult result = vector_push(vec, NULL);
    ASSERT_EQ(result, CS_NULL_POINTER);
    vector_destroy(vec);
}

void test_pop_single(void) {
    CsVector* vec = vector_create(sizeof(int), 4);
    int value = 99;
    vector_push(vec, &value);

    int* popped = (int*)vector_pop(vec);
    ASSERT_NOT_NULL(popped);
    ASSERT_EQ(*popped, 99);
    ASSERT_EQ(vec->size, 0);

    vector_destroy(vec);
}

void test_pop_multiple(void) {
    CsVector* vec = vector_create(sizeof(int), 4);

    // Push 5 éléments
    for (int i = 0; i < 5; i++) {
        vector_push(vec, &i);
    }

    // Pop dans l'ordre inverse
    for (int i = 4; i >= 0; i--) {
        int* popped = (int*)vector_pop(vec);
        ASSERT_NOT_NULL(popped);
        ASSERT_EQ(*popped, i);
        ASSERT_EQ(vec->size, (size_t)i);
    }

    vector_destroy(vec);
}

void test_pop_empty_vector(void) {
    CsVector* vec = vector_create(sizeof(int), 4);
    void* popped = vector_pop(vec);
    ASSERT_NULL(popped);
    vector_destroy(vec);
}

void test_pop_null_vector(void) {
    void* popped = vector_pop(NULL);
    ASSERT_NULL(popped);
}

void test_get_valid_index(void) {
    CsVector* vec = vector_create(sizeof(int), 4);

    for (int i = 0; i < 3; i++) {
        vector_push(vec, &i);
    }

    int* val0 = (int*)vector_get(vec, 0);
    int* val1 = (int*)vector_get(vec, 1);
    int* val2 = (int*)vector_get(vec, 2);

    ASSERT_NOT_NULL(val0);
    ASSERT_NOT_NULL(val1);
    ASSERT_NOT_NULL(val2);
    ASSERT_EQ(*val0, 0);
    ASSERT_EQ(*val1, 1);
    ASSERT_EQ(*val2, 2);

    vector_destroy(vec);
}

void test_get_out_of_bounds(void) {
    CsVector* vec = vector_create(sizeof(int), 4);
    int value = 42;
    vector_push(vec, &value);

    void* result = vector_get(vec, 1);
    ASSERT_NULL(result);

    result = vector_get(vec, 100);
    ASSERT_NULL(result);

    vector_destroy(vec);
}

void test_get_null_vector(void) {
    void* result = vector_get(NULL, 0);
    ASSERT_NULL(result);
}

// ========================================
// Tests de reserve
// ========================================

void test_reserve_increase(void) {
    CsVector* vec = vector_create(sizeof(int), 4);
    ASSERT_EQ(vec->capacity, 4);

    CsResult result = vector_reserve(vec, 20);
    ASSERT_EQ(result, CS_SUCCESS);
    ASSERT_EQ(vec->capacity, 20);
    ASSERT_EQ(vec->size, 0);

    vector_destroy(vec);
}

void test_reserve_with_data(void) {
    CsVector* vec = vector_create(sizeof(int), 4);

    // Ajouter des données
    for (int i = 0; i < 3; i++) {
        vector_push(vec, &i);
    }

    // Reserve plus de capacité
    vector_reserve(vec, 10);
    ASSERT_EQ(vec->capacity, 10);
    ASSERT_EQ(vec->size, 3);

    // Vérifier que les données sont intactes
    for (int i = 0; i < 3; i++) {
        int* value = (int*)vector_get(vec, i);
        ASSERT_EQ(*value, i);
    }

    vector_destroy(vec);
}

void test_reserve_decrease(void) {
    CsVector* vec = vector_create(sizeof(int), 10);

    for (int i = 0; i < 8; i++) {
        vector_push(vec, &i);
    }

    // Reserve moins que size (données perdues)
    vector_reserve(vec, 5);
    ASSERT_EQ(vec->capacity, 5);
    ASSERT_EQ(vec->size, 5);

    // Vérifier les données restantes
    for (int i = 0; i < 5; i++) {
        int* value = (int*)vector_get(vec, i);
        ASSERT_EQ(*value, i);
    }

    vector_destroy(vec);
}

void test_reserve_null_vector(void) {
    CsResult result = vector_reserve(NULL, 10);
    ASSERT_EQ(result, CS_NULL_POINTER);
}

// ========================================
// Tests de clear
// ========================================

void test_clear_empty_vector(void) {
    CsVector* vec = vector_create(sizeof(int), 4);
    size_t original_capacity = vec->capacity;

    vector_clear(vec);
    ASSERT_EQ(vec->size, 0);
    ASSERT_EQ(vec->capacity, original_capacity);

    vector_destroy(vec);
}

void test_clear_with_data(void) {
    CsVector* vec = vector_create(sizeof(int), 4);

    for (int i = 0; i < 10; i++) {
        vector_push(vec, &i);
    }

    size_t capacity_before = vec->capacity;
    vector_clear(vec);

    ASSERT_EQ(vec->size, 0);
    ASSERT_EQ(vec->capacity, capacity_before);

    // On peut re-push après clear
    int value = 99;
    vector_push(vec, &value);
    int* retrieved = (int*)vector_get(vec, 0);
    ASSERT_EQ(*retrieved, 99);

    vector_destroy(vec);
}

void test_clear_null_vector(void) {
    // Ne devrait pas crash
    vector_clear(NULL);
}

// ========================================
// Tests de shrink_to_fit
// ========================================

void test_shrink_to_fit_basic(void) {
    CsVector* vec = vector_create(sizeof(int), 20);

    for (int i = 0; i < 5; i++) {
        vector_push(vec, &i);
    }

    ASSERT_TRUE(vec->capacity > vec->size);

    CsResult result = vector_shrink_to_fit(vec);
    ASSERT_EQ(result, CS_SUCCESS);
    ASSERT_EQ(vec->capacity, vec->size);
    ASSERT_EQ(vec->size, 5);

    // Vérifier que les données sont intactes
    for (int i = 0; i < 5; i++) {
        int* value = (int*)vector_get(vec, i);
        ASSERT_EQ(*value, i);
    }

    vector_destroy(vec);
}

void test_shrink_to_fit_empty(void) {
    CsVector* vec = vector_create(sizeof(int), 10);

    CsResult result = vector_shrink_to_fit(vec);
    ASSERT_EQ(result, CS_SUCCESS);
    ASSERT_EQ(vec->size, 0);

    vector_destroy(vec);
}

void test_shrink_to_fit_null_vector(void) {
    CsResult result = vector_shrink_to_fit(NULL);
    ASSERT_EQ(result, CS_NULL_POINTER);
}

// ========================================
// Tests de clone
// ========================================

void test_clone_empty_vector(void) {
    CsVector* vec = vector_create(sizeof(int), 8);
    CsVector* clone = vector_clone(vec);

    ASSERT_NOT_NULL(clone);
    ASSERT_EQ(clone->size, vec->size);
    ASSERT_EQ(clone->capacity, vec->capacity);
    ASSERT_EQ(clone->element_size, vec->element_size);
    ASSERT_NEQ(clone->data, vec->data); // Différents pointeurs

    vector_destroy(vec);
    vector_destroy(clone);
}

void test_clone_with_data(void) {
    CsVector* vec = vector_create(sizeof(int), 4);

    for (int i = 0; i < 5; i++) {
        vector_push(vec, &i);
    }

    CsVector* clone = vector_clone(vec);

    ASSERT_NOT_NULL(clone);
    ASSERT_EQ(clone->size, vec->size);
    ASSERT_EQ(clone->capacity, vec->capacity);
    ASSERT_NEQ(clone->data, vec->data);

    // Vérifier que les données sont identiques
    for (size_t i = 0; i < vec->size; i++) {
        int* orig_val = (int*)vector_get(vec, i);
        int* clone_val = (int*)vector_get(clone, i);
        ASSERT_EQ(*orig_val, *clone_val);
    }

    // Modifier le clone ne doit pas affecter l'original
    int new_value = 999;
    vector_push(clone, &new_value);
    ASSERT_NEQ(clone->size, vec->size);

    vector_destroy(vec);
    vector_destroy(clone);
}

void test_clone_null_vector(void) {
    CsVector* clone = vector_clone(NULL);
    ASSERT_NULL(clone);
}

void test_clone_independence(void) {
    CsVector* vec = vector_create(sizeof(int), 4);
    int value = 42;
    vector_push(vec, &value);

    CsVector* clone = vector_clone(vec);

    // Modifier l'original
    int new_value = 100;
    vector_push(vec, &new_value);

    // Le clone ne doit pas être affecté
    ASSERT_EQ(clone->size, 1);
    int* clone_val = (int*)vector_get(clone, 0);
    ASSERT_EQ(*clone_val, 42);

    vector_destroy(vec);
    vector_destroy(clone);
}

// ========================================
// Tests de types complexes
// ========================================

void test_vector_with_structs(void) {
    typedef struct {
        int id;
        double value;
        char name[16];
    } Record;

    CsVector* vec = vector_create(sizeof(Record), 4);

    Record r1 = {1, 3.14, "first"};
    Record r2 = {2, 2.71, "second"};

    vector_push(vec, &r1);
    vector_push(vec, &r2);

    Record* retrieved1 = (Record*)vector_get(vec, 0);
    Record* retrieved2 = (Record*)vector_get(vec, 1);

    ASSERT_EQ(retrieved1->id, 1);
    ASSERT_EQ(retrieved2->id, 2);
    ASSERT_STR_EQ(retrieved1->name, "first");
    ASSERT_STR_EQ(retrieved2->name, "second");

    vector_destroy(vec);
}

// ========================================
// Tests de stress
// ========================================

void test_large_vector(void) {
    CsVector* vec = vector_create(sizeof(int), 4);

    // Push 1000 éléments
    for (int i = 0; i < 1000; i++) {
        CsResult result = vector_push(vec, &i);
        ASSERT_EQ(result, CS_SUCCESS);
    }

    ASSERT_EQ(vec->size, 1000);

    // Vérifier quelques valeurs
    int* val0 = (int*)vector_get(vec, 0);
    int* val500 = (int*)vector_get(vec, 500);
    int* val999 = (int*)vector_get(vec, 999);

    ASSERT_EQ(*val0, 0);
    ASSERT_EQ(*val500, 500);
    ASSERT_EQ(*val999, 999);

    vector_destroy(vec);
}

void test_push_pop_cycle(void) {
    CsVector* vec = vector_create(sizeof(int), 2);

    // Cycle de push/pop
    for (int cycle = 0; cycle < 100; cycle++) {
        int value = cycle;
        vector_push(vec, &value);
        int* popped = (int*)vector_pop(vec);
        ASSERT_EQ(*popped, cycle);
    }

    ASSERT_EQ(vec->size, 0);
    vector_destroy(vec);
}
