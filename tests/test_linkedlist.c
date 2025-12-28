#include "cstash/linkedlist.h"
#include "test_framework.h"
#include <string.h>

// ========================================
// Tests de création et destruction
// ========================================

void test_linkedlist_create_destroy(void) {
    CsLinkedList* list = cs_linkedlist_create(sizeof(int));
    ASSERT_NOT_NULL(list);
    ASSERT_EQ(list->size, 0);
    ASSERT_EQ(list->element_size, sizeof(int));
    ASSERT_NULL(list->head);
    ASSERT_NULL(list->tail);
    cs_linkedlist_destroy(list);
}

void test_linkedlist_create_with_zero_size(void) {
    CsLinkedList* list = cs_linkedlist_create(0);
    ASSERT_NULL(list);
}

void test_linkedlist_create_with_different_types(void) {
    // Test avec double
    CsLinkedList* list_double = cs_linkedlist_create(sizeof(double));
    ASSERT_NOT_NULL(list_double);
    ASSERT_EQ(list_double->element_size, sizeof(double));
    cs_linkedlist_destroy(list_double);

    // Test avec char
    CsLinkedList* list_char = cs_linkedlist_create(sizeof(char));
    ASSERT_NOT_NULL(list_char);
    ASSERT_EQ(list_char->element_size, sizeof(char));
    cs_linkedlist_destroy(list_char);

    // Test avec struct
    typedef struct {
        int x;
        int y;
    } Point;
    CsLinkedList* list_point = cs_linkedlist_create(sizeof(Point));
    ASSERT_NOT_NULL(list_point);
    ASSERT_EQ(list_point->element_size, sizeof(Point));
    cs_linkedlist_destroy(list_point);
}

void test_linkedlist_destroy_null(void) {
    // Ne devrait pas crash
    cs_linkedlist_destroy(NULL);
}

// ========================================
// Tests de is_empty et size
// ========================================

void test_linkedlist_is_empty_on_new_list(void) {
    CsLinkedList* list = cs_linkedlist_create(sizeof(int));
    ASSERT_TRUE(cs_linkedlist_is_empty(list));
    cs_linkedlist_destroy(list);
}

void test_linkedlist_is_empty_after_push(void) {
    CsLinkedList* list = cs_linkedlist_create(sizeof(int));
    int value = 42;
    cs_linkedlist_push_front(list, &value);
    ASSERT_FALSE(cs_linkedlist_is_empty(list));
    cs_linkedlist_destroy(list);
}

void test_linkedlist_is_empty_null(void) {
    ASSERT_TRUE(cs_linkedlist_is_empty(NULL));
}

void test_linkedlist_size_empty(void) {
    CsLinkedList* list = cs_linkedlist_create(sizeof(int));
    ASSERT_EQ(cs_linkedlist_size(list), 0);
    cs_linkedlist_destroy(list);
}

void test_linkedlist_size_after_operations(void) {
    CsLinkedList* list = cs_linkedlist_create(sizeof(int));

    for (int i = 0; i < 5; i++) {
        cs_linkedlist_push_back(list, &i);
        ASSERT_EQ(cs_linkedlist_size(list), (size_t)(i + 1));
    }

    cs_linkedlist_destroy(list);
}

void test_linkedlist_size_null(void) {
    ASSERT_EQ(cs_linkedlist_size(NULL), 0);
}

// ========================================
// Tests de push_front
// ========================================

void test_linkedlist_push_front_single(void) {
    CsLinkedList* list = cs_linkedlist_create(sizeof(int));
    int value = 42;

    CsResult result = cs_linkedlist_push_front(list, &value);
    ASSERT_EQ(result, CS_SUCCESS);
    ASSERT_EQ(list->size, 1);
    ASSERT_NOT_NULL(list->head);
    ASSERT_NOT_NULL(list->tail);
    ASSERT_EQ(list->head, list->tail);

    int* retrieved = (int*)cs_linkedlist_front(list);
    ASSERT_EQ(*retrieved, 42);

    cs_linkedlist_destroy(list);
}

void test_linkedlist_push_front_multiple(void) {
    CsLinkedList* list = cs_linkedlist_create(sizeof(int));

    for (int i = 0; i < 5; i++) {
        cs_linkedlist_push_front(list, &i);
    }

    ASSERT_EQ(list->size, 5);

    // Les éléments doivent être dans l'ordre inverse
    for (int i = 0; i < 5; i++) {
        int* value = (int*)cs_linkedlist_get(list, i);
        ASSERT_EQ(*value, 4 - i);
    }

    cs_linkedlist_destroy(list);
}

void test_linkedlist_push_front_null_list(void) {
    int value = 42;
    CsResult result = cs_linkedlist_push_front(NULL, &value);
    ASSERT_EQ(result, CS_NULL_POINTER);
}

void test_linkedlist_push_front_null_element(void) {
    CsLinkedList* list = cs_linkedlist_create(sizeof(int));
    CsResult result = cs_linkedlist_push_front(list, NULL);
    ASSERT_EQ(result, CS_NULL_POINTER);
    cs_linkedlist_destroy(list);
}

// ========================================
// Tests de push_back
// ========================================

void test_linkedlist_push_back_single(void) {
    CsLinkedList* list = cs_linkedlist_create(sizeof(int));
    int value = 42;

    CsResult result = cs_linkedlist_push_back(list, &value);
    ASSERT_EQ(result, CS_SUCCESS);
    ASSERT_EQ(list->size, 1);
    ASSERT_NOT_NULL(list->head);
    ASSERT_NOT_NULL(list->tail);
    ASSERT_EQ(list->head, list->tail);

    int* retrieved = (int*)cs_linkedlist_back(list);
    ASSERT_EQ(*retrieved, 42);

    cs_linkedlist_destroy(list);
}

void test_linkedlist_push_back_multiple(void) {
    CsLinkedList* list = cs_linkedlist_create(sizeof(int));

    for (int i = 0; i < 5; i++) {
        cs_linkedlist_push_back(list, &i);
    }

    ASSERT_EQ(list->size, 5);

    // Les éléments doivent être dans l'ordre
    for (int i = 0; i < 5; i++) {
        int* value = (int*)cs_linkedlist_get(list, i);
        ASSERT_EQ(*value, i);
    }

    cs_linkedlist_destroy(list);
}

void test_linkedlist_push_back_null_list(void) {
    int value = 42;
    CsResult result = cs_linkedlist_push_back(NULL, &value);
    ASSERT_EQ(result, CS_NULL_POINTER);
}

void test_linkedlist_push_back_null_element(void) {
    CsLinkedList* list = cs_linkedlist_create(sizeof(int));
    CsResult result = cs_linkedlist_push_back(list, NULL);
    ASSERT_EQ(result, CS_NULL_POINTER);
    cs_linkedlist_destroy(list);
}

// ========================================
// Tests de insert_at
// ========================================

void test_linkedlist_insert_at_beginning(void) {
    CsLinkedList* list = cs_linkedlist_create(sizeof(int));

    int val1 = 1, val2 = 2, val0 = 0;
    cs_linkedlist_push_back(list, &val1);
    cs_linkedlist_push_back(list, &val2);

    CsResult result = cs_linkedlist_insert_at(list, &val0, 0);
    ASSERT_EQ(result, CS_SUCCESS);
    ASSERT_EQ(list->size, 3);

    int* retrieved = (int*)cs_linkedlist_get(list, 0);
    ASSERT_EQ(*retrieved, 0);

    cs_linkedlist_destroy(list);
}

void test_linkedlist_insert_at_end(void) {
    CsLinkedList* list = cs_linkedlist_create(sizeof(int));

    int val0 = 0, val1 = 1, val2 = 2;
    cs_linkedlist_push_back(list, &val0);
    cs_linkedlist_push_back(list, &val1);

    CsResult result = cs_linkedlist_insert_at(list, &val2, 2);
    ASSERT_EQ(result, CS_SUCCESS);
    ASSERT_EQ(list->size, 3);

    int* retrieved = (int*)cs_linkedlist_get(list, 2);
    ASSERT_EQ(*retrieved, 2);

    cs_linkedlist_destroy(list);
}

void test_linkedlist_insert_at_middle(void) {
    CsLinkedList* list = cs_linkedlist_create(sizeof(int));

    int val0 = 0, val2 = 2, val1 = 1;
    cs_linkedlist_push_back(list, &val0);
    cs_linkedlist_push_back(list, &val2);

    CsResult result = cs_linkedlist_insert_at(list, &val1, 1);
    ASSERT_EQ(result, CS_SUCCESS);
    ASSERT_EQ(list->size, 3);

    int* retrieved = (int*)cs_linkedlist_get(list, 1);
    ASSERT_EQ(*retrieved, 1);

    cs_linkedlist_destroy(list);
}

void test_linkedlist_insert_at_out_of_bounds(void) {
    CsLinkedList* list = cs_linkedlist_create(sizeof(int));
    int value = 42;

    CsResult result = cs_linkedlist_insert_at(list, &value, 10);
    ASSERT_EQ(result, CS_OUT_OF_BOUNDS);

    cs_linkedlist_destroy(list);
}

void test_linkedlist_insert_at_null_list(void) {
    int value = 42;
    CsResult result = cs_linkedlist_insert_at(NULL, &value, 0);
    ASSERT_EQ(result, CS_NULL_POINTER);
}

void test_linkedlist_insert_at_null_element(void) {
    CsLinkedList* list = cs_linkedlist_create(sizeof(int));
    CsResult result = cs_linkedlist_insert_at(list, NULL, 0);
    ASSERT_EQ(result, CS_NULL_POINTER);
    cs_linkedlist_destroy(list);
}

// ========================================
// Tests de pop_front
// ========================================

void test_linkedlist_pop_front_single(void) {
    CsLinkedList* list = cs_linkedlist_create(sizeof(int));
    int value = 99;
    cs_linkedlist_push_front(list, &value);

    int* popped = (int*)cs_linkedlist_pop_front(list);
    ASSERT_NOT_NULL(popped);
    ASSERT_EQ(*popped, 99);
    ASSERT_EQ(list->size, 0);
    ASSERT_NULL(list->head);
    ASSERT_NULL(list->tail);

    free(popped);
    cs_linkedlist_destroy(list);
}

void test_linkedlist_pop_front_multiple(void) {
    CsLinkedList* list = cs_linkedlist_create(sizeof(int));

    for (int i = 0; i < 5; i++) {
        cs_linkedlist_push_back(list, &i);
    }

    for (int i = 0; i < 5; i++) {
        int* popped = (int*)cs_linkedlist_pop_front(list);
        ASSERT_NOT_NULL(popped);
        ASSERT_EQ(*popped, i);
        ASSERT_EQ(list->size, (size_t)(4 - i));
        free(popped);
    }

    ASSERT_NULL(list->head);
    ASSERT_NULL(list->tail);
    cs_linkedlist_destroy(list);
}

void test_linkedlist_pop_front_empty(void) {
    CsLinkedList* list = cs_linkedlist_create(sizeof(int));
    void* popped = cs_linkedlist_pop_front(list);
    ASSERT_NULL(popped);
    cs_linkedlist_destroy(list);
}

void test_linkedlist_pop_front_null(void) {
    void* popped = cs_linkedlist_pop_front(NULL);
    ASSERT_NULL(popped);
}

// ========================================
// Tests de pop_back
// ========================================

void test_linkedlist_pop_back_single(void) {
    CsLinkedList* list = cs_linkedlist_create(sizeof(int));
    int value = 99;
    cs_linkedlist_push_back(list, &value);

    int* popped = (int*)cs_linkedlist_pop_back(list);
    ASSERT_NOT_NULL(popped);
    ASSERT_EQ(*popped, 99);
    ASSERT_EQ(list->size, 0);
    ASSERT_NULL(list->head);
    ASSERT_NULL(list->tail);

    free(popped);
    cs_linkedlist_destroy(list);
}

void test_linkedlist_pop_back_multiple(void) {
    CsLinkedList* list = cs_linkedlist_create(sizeof(int));

    for (int i = 0; i < 5; i++) {
        cs_linkedlist_push_back(list, &i);
    }

    for (int i = 4; i >= 0; i--) {
        int* popped = (int*)cs_linkedlist_pop_back(list);
        ASSERT_NOT_NULL(popped);
        ASSERT_EQ(*popped, i);
        ASSERT_EQ(list->size, (size_t)i);
        free(popped);
    }

    ASSERT_NULL(list->head);
    ASSERT_NULL(list->tail);
    cs_linkedlist_destroy(list);
}

void test_linkedlist_pop_back_empty(void) {
    CsLinkedList* list = cs_linkedlist_create(sizeof(int));
    void* popped = cs_linkedlist_pop_back(list);
    ASSERT_NULL(popped);
    cs_linkedlist_destroy(list);
}

void test_linkedlist_pop_back_null(void) {
    void* popped = cs_linkedlist_pop_back(NULL);
    ASSERT_NULL(popped);
}

// ========================================
// Tests de front, back et get
// ========================================

void test_linkedlist_front_single(void) {
    CsLinkedList* list = cs_linkedlist_create(sizeof(int));
    int value = 42;
    cs_linkedlist_push_front(list, &value);

    int* front = (int*)cs_linkedlist_front(list);
    ASSERT_NOT_NULL(front);
    ASSERT_EQ(*front, 42);

    cs_linkedlist_destroy(list);
}

void test_linkedlist_front_empty(void) {
    CsLinkedList* list = cs_linkedlist_create(sizeof(int));
    void* front = cs_linkedlist_front(list);
    ASSERT_NULL(front);
    cs_linkedlist_destroy(list);
}

void test_linkedlist_front_null(void) {
    void* front = cs_linkedlist_front(NULL);
    ASSERT_NULL(front);
}

void test_linkedlist_back_single(void) {
    CsLinkedList* list = cs_linkedlist_create(sizeof(int));
    int value = 42;
    cs_linkedlist_push_back(list, &value);

    int* back = (int*)cs_linkedlist_back(list);
    ASSERT_NOT_NULL(back);
    ASSERT_EQ(*back, 42);

    cs_linkedlist_destroy(list);
}

void test_linkedlist_back_empty(void) {
    CsLinkedList* list = cs_linkedlist_create(sizeof(int));
    void* back = cs_linkedlist_back(list);
    ASSERT_NULL(back);
    cs_linkedlist_destroy(list);
}

void test_linkedlist_back_null(void) {
    void* back = cs_linkedlist_back(NULL);
    ASSERT_NULL(back);
}

void test_linkedlist_get_valid_indices(void) {
    CsLinkedList* list = cs_linkedlist_create(sizeof(int));

    for (int i = 0; i < 5; i++) {
        cs_linkedlist_push_back(list, &i);
    }

    for (int i = 0; i < 5; i++) {
        int* value = (int*)cs_linkedlist_get(list, i);
        ASSERT_NOT_NULL(value);
        ASSERT_EQ(*value, i);
    }

    cs_linkedlist_destroy(list);
}

void test_linkedlist_get_out_of_bounds(void) {
    CsLinkedList* list = cs_linkedlist_create(sizeof(int));
    int value = 42;
    cs_linkedlist_push_back(list, &value);

    void* result = cs_linkedlist_get(list, 1);
    ASSERT_NULL(result);

    result = cs_linkedlist_get(list, 100);
    ASSERT_NULL(result);

    cs_linkedlist_destroy(list);
}

void test_linkedlist_get_null_list(void) {
    void* result = cs_linkedlist_get(NULL, 0);
    ASSERT_NULL(result);
}

void test_linkedlist_get_bidirectional_optimization(void) {
    CsLinkedList* list = cs_linkedlist_create(sizeof(int));

    // Ajouter 10 éléments
    for (int i = 0; i < 10; i++) {
        cs_linkedlist_push_back(list, &i);
    }

    // Accéder au début (devrait utiliser forward)
    int* val0 = (int*)cs_linkedlist_get(list, 0);
    ASSERT_EQ(*val0, 0);

    // Accéder à la fin (devrait utiliser backward)
    int* val9 = (int*)cs_linkedlist_get(list, 9);
    ASSERT_EQ(*val9, 9);

    // Accéder au milieu
    int* val5 = (int*)cs_linkedlist_get(list, 5);
    ASSERT_EQ(*val5, 5);

    cs_linkedlist_destroy(list);
}

// ========================================
// Tests de remove_at
// ========================================

void test_linkedlist_remove_at_beginning(void) {
    CsLinkedList* list = cs_linkedlist_create(sizeof(int));

    for (int i = 0; i < 5; i++) {
        cs_linkedlist_push_back(list, &i);
    }

    CsResult result = cs_linkedlist_remove_at(list, 0);
    ASSERT_EQ(result, CS_SUCCESS);
    ASSERT_EQ(list->size, 4);

    int* first = (int*)cs_linkedlist_get(list, 0);
    ASSERT_EQ(*first, 1);

    cs_linkedlist_destroy(list);
}

void test_linkedlist_remove_at_end(void) {
    CsLinkedList* list = cs_linkedlist_create(sizeof(int));

    for (int i = 0; i < 5; i++) {
        cs_linkedlist_push_back(list, &i);
    }

    CsResult result = cs_linkedlist_remove_at(list, 4);
    ASSERT_EQ(result, CS_SUCCESS);
    ASSERT_EQ(list->size, 4);

    int* last = (int*)cs_linkedlist_get(list, 3);
    ASSERT_EQ(*last, 3);

    cs_linkedlist_destroy(list);
}

void test_linkedlist_remove_at_middle(void) {
    CsLinkedList* list = cs_linkedlist_create(sizeof(int));

    for (int i = 0; i < 5; i++) {
        cs_linkedlist_push_back(list, &i);
    }

    CsResult result = cs_linkedlist_remove_at(list, 2);
    ASSERT_EQ(result, CS_SUCCESS);
    ASSERT_EQ(list->size, 4);

    int* val = (int*)cs_linkedlist_get(list, 2);
    ASSERT_EQ(*val, 3);

    cs_linkedlist_destroy(list);
}

void test_linkedlist_remove_at_single_element(void) {
    CsLinkedList* list = cs_linkedlist_create(sizeof(int));
    int value = 42;
    cs_linkedlist_push_back(list, &value);

    CsResult result = cs_linkedlist_remove_at(list, 0);
    ASSERT_EQ(result, CS_SUCCESS);
    ASSERT_EQ(list->size, 0);
    ASSERT_NULL(list->head);
    ASSERT_NULL(list->tail);

    cs_linkedlist_destroy(list);
}

void test_linkedlist_remove_at_out_of_bounds(void) {
    CsLinkedList* list = cs_linkedlist_create(sizeof(int));
    int value = 42;
    cs_linkedlist_push_back(list, &value);

    CsResult result = cs_linkedlist_remove_at(list, 10);
    ASSERT_EQ(result, CS_OUT_OF_BOUNDS);

    cs_linkedlist_destroy(list);
}

void test_linkedlist_remove_at_null_list(void) {
    CsResult result = cs_linkedlist_remove_at(NULL, 0);
    ASSERT_EQ(result, CS_NULL_POINTER);
}

// ========================================
// Tests de clear
// ========================================

void test_linkedlist_clear_empty(void) {
    CsLinkedList* list = cs_linkedlist_create(sizeof(int));
    cs_linkedlist_clear(list);
    ASSERT_EQ(list->size, 0);
    ASSERT_NULL(list->head);
    ASSERT_NULL(list->tail);
    cs_linkedlist_destroy(list);
}

void test_linkedlist_clear_with_data(void) {
    CsLinkedList* list = cs_linkedlist_create(sizeof(int));

    for (int i = 0; i < 10; i++) {
        cs_linkedlist_push_back(list, &i);
    }

    cs_linkedlist_clear(list);
    ASSERT_EQ(list->size, 0);
    ASSERT_NULL(list->head);
    ASSERT_NULL(list->tail);

    // On peut re-push après clear
    int value = 99;
    cs_linkedlist_push_back(list, &value);
    int* retrieved = (int*)cs_linkedlist_front(list);
    ASSERT_EQ(*retrieved, 99);

    cs_linkedlist_destroy(list);
}

void test_linkedlist_clear_null(void) {
    // Ne devrait pas crash
    cs_linkedlist_clear(NULL);
}

// ========================================
// Tests de types complexes
// ========================================

void test_linkedlist_with_structs(void) {
    typedef struct {
        int id;
        double value;
        char name[16];
    } Record;

    CsLinkedList* list = cs_linkedlist_create(sizeof(Record));

    Record r1 = {1, 3.14, "first"};
    Record r2 = {2, 2.71, "second"};
    Record r3 = {3, 1.41, "third"};

    cs_linkedlist_push_back(list, &r1);
    cs_linkedlist_push_back(list, &r2);
    cs_linkedlist_push_back(list, &r3);

    Record* retrieved1 = (Record*)cs_linkedlist_get(list, 0);
    Record* retrieved2 = (Record*)cs_linkedlist_get(list, 1);
    Record* retrieved3 = (Record*)cs_linkedlist_get(list, 2);

    ASSERT_EQ(retrieved1->id, 1);
    ASSERT_EQ(retrieved2->id, 2);
    ASSERT_EQ(retrieved3->id, 3);
    ASSERT_STR_EQ(retrieved1->name, "first");
    ASSERT_STR_EQ(retrieved2->name, "second");
    ASSERT_STR_EQ(retrieved3->name, "third");

    cs_linkedlist_destroy(list);
}

// ========================================
// Tests de stress et edge cases
// ========================================

void test_linkedlist_large_list(void) {
    CsLinkedList* list = cs_linkedlist_create(sizeof(int));

    // Push 1000 éléments
    for (int i = 0; i < 1000; i++) {
        CsResult result = cs_linkedlist_push_back(list, &i);
        ASSERT_EQ(result, CS_SUCCESS);
    }

    ASSERT_EQ(list->size, 1000);

    // Vérifier quelques valeurs
    int* val0 = (int*)cs_linkedlist_get(list, 0);
    int* val500 = (int*)cs_linkedlist_get(list, 500);
    int* val999 = (int*)cs_linkedlist_get(list, 999);

    ASSERT_EQ(*val0, 0);
    ASSERT_EQ(*val500, 500);
    ASSERT_EQ(*val999, 999);

    cs_linkedlist_destroy(list);
}

void test_linkedlist_push_pop_cycle(void) {
    CsLinkedList* list = cs_linkedlist_create(sizeof(int));

    // Cycle de push_back/pop_back
    for (int cycle = 0; cycle < 100; cycle++) {
        cs_linkedlist_push_back(list, &cycle);
        int* popped = (int*)cs_linkedlist_pop_back(list);
        ASSERT_EQ(*popped, cycle);
        free(popped);
    }

    ASSERT_EQ(list->size, 0);
    cs_linkedlist_destroy(list);
}

void test_linkedlist_alternating_push(void) {
    CsLinkedList* list = cs_linkedlist_create(sizeof(int));

    // Alterner push_front et push_back
    for (int i = 0; i < 5; i++) {
        cs_linkedlist_push_front(list, &i);
        int next = i + 100;
        cs_linkedlist_push_back(list, &next);
    }

    ASSERT_EQ(list->size, 10);

    // Vérifier l'ordre: 4,3,2,1,0,100,101,102,103,104
    int* front = (int*)cs_linkedlist_front(list);
    int* back = (int*)cs_linkedlist_back(list);
    ASSERT_EQ(*front, 4);
    ASSERT_EQ(*back, 104);

    cs_linkedlist_destroy(list);
}

void test_linkedlist_memory_leak_remove_at(void) {
    CsLinkedList* list = cs_linkedlist_create(sizeof(int));

    for (int i = 0; i < 10; i++) {
        cs_linkedlist_push_back(list, &i);
    }

    // Test le bug de fuite mémoire avec remove_at à l'index 0
    cs_linkedlist_remove_at(list, 0);
    ASSERT_EQ(list->size, 9);

    // Test le bug de fuite mémoire avec remove_at au dernier index
    cs_linkedlist_remove_at(list, 8);
    ASSERT_EQ(list->size, 8);

    cs_linkedlist_destroy(list);
}

// ========================================
// Main
// ========================================

int main(void) {
    TEST_INIT();

    printf("\n" COLOR_MAGENTA "########## LINKEDLIST TESTS ##########" COLOR_RESET "\n");

    printf("\n" COLOR_BLUE "========== CREATION & DESTRUCTION ==========" COLOR_RESET "\n");
    RUN_TEST(test_linkedlist_create_destroy);
    RUN_TEST(test_linkedlist_create_with_zero_size);
    RUN_TEST(test_linkedlist_create_with_different_types);
    RUN_TEST(test_linkedlist_destroy_null);

    printf("\n" COLOR_BLUE "========== IS_EMPTY & SIZE ==========" COLOR_RESET "\n");
    RUN_TEST(test_linkedlist_is_empty_on_new_list);
    RUN_TEST(test_linkedlist_is_empty_after_push);
    RUN_TEST(test_linkedlist_is_empty_null);
    RUN_TEST(test_linkedlist_size_empty);
    RUN_TEST(test_linkedlist_size_after_operations);
    RUN_TEST(test_linkedlist_size_null);

    printf("\n" COLOR_BLUE "========== PUSH FRONT ==========" COLOR_RESET "\n");
    RUN_TEST(test_linkedlist_push_front_single);
    RUN_TEST(test_linkedlist_push_front_multiple);
    RUN_TEST(test_linkedlist_push_front_null_list);
    RUN_TEST(test_linkedlist_push_front_null_element);

    printf("\n" COLOR_BLUE "========== PUSH BACK ==========" COLOR_RESET "\n");
    RUN_TEST(test_linkedlist_push_back_single);
    RUN_TEST(test_linkedlist_push_back_multiple);
    RUN_TEST(test_linkedlist_push_back_null_list);
    RUN_TEST(test_linkedlist_push_back_null_element);

    printf("\n" COLOR_BLUE "========== INSERT AT ==========" COLOR_RESET "\n");
    RUN_TEST(test_linkedlist_insert_at_beginning);
    RUN_TEST(test_linkedlist_insert_at_end);
    RUN_TEST(test_linkedlist_insert_at_middle);
    RUN_TEST(test_linkedlist_insert_at_out_of_bounds);
    RUN_TEST(test_linkedlist_insert_at_null_list);
    RUN_TEST(test_linkedlist_insert_at_null_element);

    printf("\n" COLOR_BLUE "========== POP FRONT ==========" COLOR_RESET "\n");
    RUN_TEST(test_linkedlist_pop_front_single);
    RUN_TEST(test_linkedlist_pop_front_multiple);
    RUN_TEST(test_linkedlist_pop_front_empty);
    RUN_TEST(test_linkedlist_pop_front_null);

    printf("\n" COLOR_BLUE "========== POP BACK ==========" COLOR_RESET "\n");
    RUN_TEST(test_linkedlist_pop_back_single);
    RUN_TEST(test_linkedlist_pop_back_multiple);
    RUN_TEST(test_linkedlist_pop_back_empty);
    RUN_TEST(test_linkedlist_pop_back_null);

    printf("\n" COLOR_BLUE "========== FRONT, BACK & GET ==========" COLOR_RESET "\n");
    RUN_TEST(test_linkedlist_front_single);
    RUN_TEST(test_linkedlist_front_empty);
    RUN_TEST(test_linkedlist_front_null);
    RUN_TEST(test_linkedlist_back_single);
    RUN_TEST(test_linkedlist_back_empty);
    RUN_TEST(test_linkedlist_back_null);
    RUN_TEST(test_linkedlist_get_valid_indices);
    RUN_TEST(test_linkedlist_get_out_of_bounds);
    RUN_TEST(test_linkedlist_get_null_list);
    RUN_TEST(test_linkedlist_get_bidirectional_optimization);

    printf("\n" COLOR_BLUE "========== REMOVE AT ==========" COLOR_RESET "\n");
    RUN_TEST(test_linkedlist_remove_at_beginning);
    RUN_TEST(test_linkedlist_remove_at_end);
    RUN_TEST(test_linkedlist_remove_at_middle);
    RUN_TEST(test_linkedlist_remove_at_single_element);
    RUN_TEST(test_linkedlist_remove_at_out_of_bounds);
    RUN_TEST(test_linkedlist_remove_at_null_list);

    printf("\n" COLOR_BLUE "========== CLEAR ==========" COLOR_RESET "\n");
    RUN_TEST(test_linkedlist_clear_empty);
    RUN_TEST(test_linkedlist_clear_with_data);
    RUN_TEST(test_linkedlist_clear_null);

    printf("\n" COLOR_BLUE "========== COMPLEX TYPES ==========" COLOR_RESET "\n");
    RUN_TEST(test_linkedlist_with_structs);

    printf("\n" COLOR_BLUE "========== STRESS TESTS ==========" COLOR_RESET "\n");
    RUN_TEST(test_linkedlist_large_list);
    RUN_TEST(test_linkedlist_push_pop_cycle);
    RUN_TEST(test_linkedlist_alternating_push);
    RUN_TEST(test_linkedlist_memory_leak_remove_at);

    TEST_SUMMARY();

    return tests_failed > 0 ? 1 : 0;
}
