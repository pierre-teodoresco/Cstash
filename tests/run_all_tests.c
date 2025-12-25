#include "test_framework.h"

// ==================== VECTOR TESTS ====================
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

// ==================== LINKEDLIST TESTS ====================
// Création et destruction
void test_linkedlist_create_destroy(void);
void test_linkedlist_create_with_zero_size(void);
void test_linkedlist_create_with_different_types(void);
void test_linkedlist_destroy_null(void);

// is_empty et size
void test_linkedlist_is_empty_on_new_list(void);
void test_linkedlist_is_empty_after_push(void);
void test_linkedlist_is_empty_null(void);
void test_linkedlist_size_empty(void);
void test_linkedlist_size_after_operations(void);
void test_linkedlist_size_null(void);

// push_front
void test_linkedlist_push_front_single(void);
void test_linkedlist_push_front_multiple(void);
void test_linkedlist_push_front_null_list(void);
void test_linkedlist_push_front_null_element(void);

// push_back
void test_linkedlist_push_back_single(void);
void test_linkedlist_push_back_multiple(void);
void test_linkedlist_push_back_null_list(void);
void test_linkedlist_push_back_null_element(void);

// insert_at
void test_linkedlist_insert_at_beginning(void);
void test_linkedlist_insert_at_end(void);
void test_linkedlist_insert_at_middle(void);
void test_linkedlist_insert_at_out_of_bounds(void);
void test_linkedlist_insert_at_null_list(void);
void test_linkedlist_insert_at_null_element(void);

// pop_front
void test_linkedlist_pop_front_single(void);
void test_linkedlist_pop_front_multiple(void);
void test_linkedlist_pop_front_empty(void);
void test_linkedlist_pop_front_null(void);

// pop_back
void test_linkedlist_pop_back_single(void);
void test_linkedlist_pop_back_multiple(void);
void test_linkedlist_pop_back_empty(void);
void test_linkedlist_pop_back_null(void);

// front, back et get
void test_linkedlist_front_single(void);
void test_linkedlist_front_empty(void);
void test_linkedlist_front_null(void);
void test_linkedlist_back_single(void);
void test_linkedlist_back_empty(void);
void test_linkedlist_back_null(void);
void test_linkedlist_get_valid_indices(void);
void test_linkedlist_get_out_of_bounds(void);
void test_linkedlist_get_null_list(void);
void test_linkedlist_get_bidirectional_optimization(void);

// remove_at
void test_linkedlist_remove_at_beginning(void);
void test_linkedlist_remove_at_end(void);
void test_linkedlist_remove_at_middle(void);
void test_linkedlist_remove_at_single_element(void);
void test_linkedlist_remove_at_out_of_bounds(void);
void test_linkedlist_remove_at_null_list(void);

// clear
void test_linkedlist_clear_empty(void);
void test_linkedlist_clear_with_data(void);
void test_linkedlist_clear_null(void);

// Types complexes
void test_linkedlist_with_structs(void);

// Stress tests
void test_linkedlist_large_list(void);
void test_linkedlist_push_pop_cycle(void);
void test_linkedlist_alternating_push(void);
void test_linkedlist_memory_leak_remove_at(void);

int main(void) {
    TEST_INIT();

    printf("\n" COLOR_MAGENTA "########## VECTOR TESTS ##########" COLOR_RESET "\n");

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
