#include "test_framework.h"

// Déclarations externes - Création et destruction
void test_create_destroy(void);
void test_create_with_zero_capacity(void);
void test_create_with_different_types(void);
void test_destroy_null(void);

// Push, pop et get
void test_push_single(void);
void test_push_multiple(void);
void test_push_with_reallocation(void);
void test_push_null_vector(void);
void test_push_null_element(void);
void test_pop_single(void);
void test_pop_multiple(void);
void test_pop_empty_vector(void);
void test_pop_null_vector(void);
void test_get_valid_index(void);
void test_get_out_of_bounds(void);
void test_get_null_vector(void);

// Reserve
void test_reserve_increase(void);
void test_reserve_with_data(void);
void test_reserve_decrease(void);
void test_reserve_null_vector(void);

// Clear
void test_clear_empty_vector(void);
void test_clear_with_data(void);
void test_clear_null_vector(void);

// Shrink to fit
void test_shrink_to_fit_basic(void);
void test_shrink_to_fit_empty(void);
void test_shrink_to_fit_null_vector(void);

// Clone
void test_clone_empty_vector(void);
void test_clone_with_data(void);
void test_clone_null_vector(void);
void test_clone_independence(void);

// Types complexes
void test_vector_with_structs(void);

// Stress tests
void test_large_vector(void);
void test_push_pop_cycle(void);

int main(void) {
    TEST_INIT();

    printf("\n" COLOR_BLUE "========== CREATION & DESTRUCTION ==========" COLOR_RESET "\n");
    RUN_TEST(test_create_destroy);
    RUN_TEST(test_create_with_zero_capacity);
    RUN_TEST(test_create_with_different_types);
    RUN_TEST(test_destroy_null);

    printf("\n" COLOR_BLUE "========== PUSH, POP & GET ==========" COLOR_RESET "\n");
    RUN_TEST(test_push_single);
    RUN_TEST(test_push_multiple);
    RUN_TEST(test_push_with_reallocation);
    RUN_TEST(test_push_null_vector);
    RUN_TEST(test_push_null_element);
    RUN_TEST(test_pop_single);
    RUN_TEST(test_pop_multiple);
    RUN_TEST(test_pop_empty_vector);
    RUN_TEST(test_pop_null_vector);
    RUN_TEST(test_get_valid_index);
    RUN_TEST(test_get_out_of_bounds);
    RUN_TEST(test_get_null_vector);

    printf("\n" COLOR_BLUE "========== RESERVE ==========" COLOR_RESET "\n");
    RUN_TEST(test_reserve_increase);
    RUN_TEST(test_reserve_with_data);
    RUN_TEST(test_reserve_decrease);
    RUN_TEST(test_reserve_null_vector);

    printf("\n" COLOR_BLUE "========== CLEAR ==========" COLOR_RESET "\n");
    RUN_TEST(test_clear_empty_vector);
    RUN_TEST(test_clear_with_data);
    RUN_TEST(test_clear_null_vector);

    printf("\n" COLOR_BLUE "========== SHRINK TO FIT ==========" COLOR_RESET "\n");
    RUN_TEST(test_shrink_to_fit_basic);
    RUN_TEST(test_shrink_to_fit_empty);
    RUN_TEST(test_shrink_to_fit_null_vector);

    printf("\n" COLOR_BLUE "========== CLONE ==========" COLOR_RESET "\n");
    RUN_TEST(test_clone_empty_vector);
    RUN_TEST(test_clone_with_data);
    RUN_TEST(test_clone_null_vector);
    RUN_TEST(test_clone_independence);

    printf("\n" COLOR_BLUE "========== COMPLEX TYPES ==========" COLOR_RESET "\n");
    RUN_TEST(test_vector_with_structs);

    printf("\n" COLOR_BLUE "========== STRESS TESTS ==========" COLOR_RESET "\n");
    RUN_TEST(test_large_vector);
    RUN_TEST(test_push_pop_cycle);

    TEST_SUMMARY();

    return tests_failed > 0 ? 1 : 0;
}
