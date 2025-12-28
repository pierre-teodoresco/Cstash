#include "cstash/stack.h"
#include "test_framework.h"
#include <string.h>

// ========================================
// Tests de création et destruction
// ========================================

void test_stack_create_destroy(void) {
    CsStack* stack = cs_stack_create(sizeof(int));
    ASSERT_NOT_NULL(stack);
    ASSERT_EQ(stack->size, 0);
    ASSERT_EQ(stack->element_size, sizeof(int));
    ASSERT_NULL(stack->top);
    cs_stack_destroy(stack);
}

void test_stack_create_with_different_types(void) {
    // Test avec double
    CsStack* stack_double = cs_stack_create(sizeof(double));
    ASSERT_NOT_NULL(stack_double);
    ASSERT_EQ(stack_double->element_size, sizeof(double));
    cs_stack_destroy(stack_double);

    // Test avec char
    CsStack* stack_char = cs_stack_create(sizeof(char));
    ASSERT_NOT_NULL(stack_char);
    ASSERT_EQ(stack_char->element_size, sizeof(char));
    cs_stack_destroy(stack_char);

    // Test avec struct
    typedef struct {
        int x;
        int y;
    } Point;
    CsStack* stack_point = cs_stack_create(sizeof(Point));
    ASSERT_NOT_NULL(stack_point);
    ASSERT_EQ(stack_point->element_size, sizeof(Point));
    cs_stack_destroy(stack_point);
}

void test_stack_destroy_null(void) {
    // Ne devrait pas crash
    cs_stack_destroy(NULL);
}

// ========================================
// Tests de is_empty
// ========================================

void test_stack_is_empty_on_creation(void) {
    CsStack* stack = cs_stack_create(sizeof(int));
    ASSERT_TRUE(cs_stack_is_empty(stack));
    cs_stack_destroy(stack);
}

void test_stack_is_empty_after_push(void) {
    CsStack* stack = cs_stack_create(sizeof(int));
    int value = 42;
    cs_stack_push(stack, &value);
    ASSERT_FALSE(cs_stack_is_empty(stack));
    cs_stack_destroy(stack);
}

void test_stack_is_empty_after_push_pop(void) {
    CsStack* stack = cs_stack_create(sizeof(int));
    int value = 42;
    cs_stack_push(stack, &value);
    void* popped = cs_stack_pop(stack);
    free(popped);
    ASSERT_TRUE(cs_stack_is_empty(stack));
    cs_stack_destroy(stack);
}

void test_stack_is_empty_null_stack(void) {
    ASSERT_TRUE(cs_stack_is_empty(NULL));
}

// ========================================
// Tests de push et pop
// ========================================

void test_stack_push_single(void) {
    CsStack* stack = cs_stack_create(sizeof(int));
    int value = 42;

    CsResult result = cs_stack_push(stack, &value);
    ASSERT_EQ(result, CS_SUCCESS);
    ASSERT_EQ(stack->size, 1);
    ASSERT_NOT_NULL(stack->top);

    cs_stack_destroy(stack);
}

void test_stack_push_multiple(void) {
    CsStack* stack = cs_stack_create(sizeof(int));

    for (int i = 0; i < 10; i++) {
        CsResult result = cs_stack_push(stack, &i);
        ASSERT_EQ(result, CS_SUCCESS);
        ASSERT_EQ(stack->size, (size_t)(i + 1));
    }

    ASSERT_EQ(stack->size, 10);
    cs_stack_destroy(stack);
}

void test_stack_push_null_stack(void) {
    int value = 42;
    CsResult result = cs_stack_push(NULL, &value);
    ASSERT_EQ(result, CS_NULL_POINTER);
}

void test_stack_push_null_element(void) {
    CsStack* stack = cs_stack_create(sizeof(int));
    CsResult result = cs_stack_push(stack, NULL);
    ASSERT_EQ(result, CS_NULL_POINTER);
    cs_stack_destroy(stack);
}

void test_stack_pop_single(void) {
    CsStack* stack = cs_stack_create(sizeof(int));
    int value = 99;
    cs_stack_push(stack, &value);

    int* popped = (int*)cs_stack_pop(stack);
    ASSERT_NOT_NULL(popped);
    ASSERT_EQ(*popped, 99);
    free(popped);
    ASSERT_EQ(stack->size, 0);
    ASSERT_NULL(stack->top);

    cs_stack_destroy(stack);
}

void test_stack_pop_lifo_order(void) {
    CsStack* stack = cs_stack_create(sizeof(int));

    // Push 5 éléments
    for (int i = 0; i < 5; i++) {
        cs_stack_push(stack, &i);
    }

    // Pop dans l'ordre LIFO (Last In First Out)
    for (int i = 4; i >= 0; i--) {
        int* popped = (int*)cs_stack_pop(stack);
        ASSERT_NOT_NULL(popped);
        ASSERT_EQ(*popped, i);
        free(popped);
        ASSERT_EQ(stack->size, (size_t)i);
    }

    ASSERT_TRUE(cs_stack_is_empty(stack));
    cs_stack_destroy(stack);
}

void test_stack_pop_empty_stack(void) {
    CsStack* stack = cs_stack_create(sizeof(int));
    void* popped = cs_stack_pop(stack);
    ASSERT_NULL(popped);
    cs_stack_destroy(stack);
}

void test_stack_pop_null_stack(void) {
    void* popped = cs_stack_pop(NULL);
    ASSERT_NULL(popped);
}

// ========================================
// Tests de clear
// ========================================

void test_stack_clear_empty(void) {
    CsStack* stack = cs_stack_create(sizeof(int));
    cs_stack_clear(stack);
    ASSERT_EQ(stack->size, 0);
    ASSERT_NULL(stack->top);
    cs_stack_destroy(stack);
}

void test_linkedlist_clear_with_data(void) {
    CsStack* stack = cs_stack_create(sizeof(int));

    for (int i = 0; i < 10; i++) {
        cs_stack_push(stack, &i);
    }

    cs_stack_clear(stack);
    ASSERT_EQ(stack->size, 0);
    ASSERT_NULL(stack->top);

    // On peut re-push après clear
    int value = 99;
    cs_stack_push(stack, &value);
    int* retrieved = (int*)cs_stack_pop(stack);
    ASSERT_EQ(*retrieved, 99);

    cs_stack_destroy(stack);
}

void test_stack_clear_null(void) {
    // Ne devrait pas crash
    cs_stack_clear(NULL);
}

// ========================================
// Tests de types complexes
// ========================================

void test_stack_stack_with_structs(void) {
    typedef struct {
        int id;
        double value;
        char name[16];
    } Record;

    CsStack* stack = cs_stack_create(sizeof(Record));

    Record r1 = {1, 3.14, "first"};
    Record r2 = {2, 2.71, "second"};
    Record r3 = {3, 1.41, "third"};

    cs_stack_push(stack, &r1);
    cs_stack_push(stack, &r2);
    cs_stack_push(stack, &r3);

    // Pop dans l'ordre inverse
    Record* popped3 = (Record*)cs_stack_pop(stack);
    ASSERT_NOT_NULL(popped3);
    ASSERT_EQ(popped3->id, 3);
    ASSERT_STR_EQ(popped3->name, "third");
    free(popped3);

    Record* popped2 = (Record*)cs_stack_pop(stack);
    ASSERT_NOT_NULL(popped2);
    ASSERT_EQ(popped2->id, 2);
    ASSERT_STR_EQ(popped2->name, "second");
    free(popped2);

    Record* popped1 = (Record*)cs_stack_pop(stack);
    ASSERT_NOT_NULL(popped1);
    ASSERT_EQ(popped1->id, 1);
    ASSERT_STR_EQ(popped1->name, "first");
    free(popped1);

    ASSERT_TRUE(cs_stack_is_empty(stack));
    cs_stack_destroy(stack);
}

void test_stack_stack_with_strings(void) {
    CsStack* stack = cs_stack_create(sizeof(char*));

    char* str1 = "hello";
    char* str2 = "world";
    char* str3 = "stack";

    cs_stack_push(stack, &str1);
    cs_stack_push(stack, &str2);
    cs_stack_push(stack, &str3);

    char** popped3 = (char**)cs_stack_pop(stack);
    ASSERT_STR_EQ(*popped3, "stack");
    free(popped3);

    char** popped2 = (char**)cs_stack_pop(stack);
    ASSERT_STR_EQ(*popped2, "world");
    free(popped2);

    char** popped1 = (char**)cs_stack_pop(stack);
    ASSERT_STR_EQ(*popped1, "hello");
    free(popped1);

    cs_stack_destroy(stack);
}

// ========================================
// Tests de stress
// ========================================

void test_stack_large_stack(void) {
    CsStack* stack = cs_stack_create(sizeof(int));

    // Push 1000 éléments
    for (int i = 0; i < 1000; i++) {
        CsResult result = cs_stack_push(stack, &i);
        ASSERT_EQ(result, CS_SUCCESS);
    }

    ASSERT_EQ(stack->size, 1000);

    // Pop tous les éléments et vérifier l'ordre LIFO
    for (int i = 999; i >= 0; i--) {
        int* popped = (int*)cs_stack_pop(stack);
        ASSERT_NOT_NULL(popped);
        ASSERT_EQ(*popped, i);
        free(popped);
    }

    ASSERT_TRUE(cs_stack_is_empty(stack));
    cs_stack_destroy(stack);
}

void test_stack_push_pop_cycle(void) {
    CsStack* stack = cs_stack_create(sizeof(int));

    // Cycle de push/pop
    for (int cycle = 0; cycle < 100; cycle++) {
        int value = cycle;
        cs_stack_push(stack, &value);
        int* popped = (int*)cs_stack_pop(stack);
        ASSERT_EQ(*popped, cycle);
        free(popped);
        ASSERT_TRUE(cs_stack_is_empty(stack));
    }

    cs_stack_destroy(stack);
}

void test_stack_alternating_push_pop(void) {
    CsStack* stack = cs_stack_create(sizeof(int));

    // Push 2, pop 1, push 2, pop 1, etc.
    for (int i = 0; i < 50; i++) {
        int val1 = i * 2;
        int val2 = i * 2 + 1;

        cs_stack_push(stack, &val1);
        cs_stack_push(stack, &val2);

        int* popped = (int*)cs_stack_pop(stack);
        ASSERT_EQ(*popped, val2);
        free(popped);

        ASSERT_EQ(stack->size, (size_t)(i + 1));
    }

    // Stack devrait contenir 50 éléments
    ASSERT_EQ(stack->size, 50);

    cs_stack_destroy(stack);
}

// ========================================
// Main
// ========================================

int main(void) {
    TEST_INIT();

    printf("\n" COLOR_MAGENTA "########## HASHMAP TESTS ##########" COLOR_RESET "\n");

    printf("\n" COLOR_BLUE "========== CREATION & DESTRUCTION ==========" COLOR_RESET "\n");
    RUN_TEST(test_stack_create_destroy);
    RUN_TEST(test_stack_create_with_different_types);
    RUN_TEST(test_stack_destroy_null);

    printf("\n" COLOR_BLUE "========== IS EMPTY ==========" COLOR_RESET "\n");
    RUN_TEST(test_stack_is_empty_on_creation);
    RUN_TEST(test_stack_is_empty_after_push);
    RUN_TEST(test_stack_is_empty_after_push_pop);
    RUN_TEST(test_stack_is_empty_null_stack);

    printf("\n" COLOR_BLUE "========== PUSH & POP ==========" COLOR_RESET "\n");
    RUN_TEST(test_stack_push_single);
    RUN_TEST(test_stack_push_multiple);
    RUN_TEST(test_stack_push_null_stack);
    RUN_TEST(test_stack_push_null_element);
    RUN_TEST(test_stack_pop_single);
    RUN_TEST(test_stack_pop_lifo_order);
    RUN_TEST(test_stack_pop_empty_stack);
    RUN_TEST(test_stack_pop_null_stack);

    printf("\n" COLOR_BLUE "========== CLEAR ==========" COLOR_RESET "\n");
    RUN_TEST(test_stack_clear_empty);
    RUN_TEST(test_stack_push_pop_cycle);
    RUN_TEST(test_stack_clear_null);

    printf("\n" COLOR_BLUE "========== COMPLEX TYPES ==========" COLOR_RESET "\n");
    RUN_TEST(test_stack_stack_with_structs);
    RUN_TEST(test_stack_stack_with_strings);

    printf("\n" COLOR_BLUE "========== STRESS TESTS ==========" COLOR_RESET "\n");
    RUN_TEST(test_stack_large_stack);
    RUN_TEST(test_stack_push_pop_cycle);
    RUN_TEST(test_stack_alternating_push_pop);

    TEST_SUMMARY();

    return tests_failed > 0 ? 1 : 0;
}
