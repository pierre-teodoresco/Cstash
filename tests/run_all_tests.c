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

// ==================== HASHMAP TESTS ====================
// Création et destruction
void test_hashmap_create_destroy(void);
void test_hashmap_create_with_zero_size(void);
void test_hashmap_create_with_different_types(void);
void test_hashmap_destroy_null(void);

// Insert
void test_hashmap_insert_single(void);
void test_hashmap_insert_multiple(void);
void test_hashmap_insert_duplicate_key(void);
void test_hashmap_insert_null_hashmap(void);
void test_hashmap_insert_null_key(void);
void test_hashmap_insert_null_value(void);
void test_hashmap_insert_with_auto_resize(void);

// Get et Has
void test_hashmap_get_existing_key(void);
void test_hashmap_get_non_existing_key(void);
void test_hashmap_get_null_hashmap(void);
void test_hashmap_get_null_key(void);
void test_hashmap_has_existing_key(void);
void test_hashmap_has_non_existing_key(void);
void test_hashmap_has_null_hashmap(void);
void test_hashmap_has_null_key(void);

// Remove
void test_hashmap_remove_existing_key(void);
void test_hashmap_remove_non_existing_key(void);
void test_hashmap_remove_from_bucket_chain(void);
void test_hashmap_remove_null_hashmap(void);
void test_hashmap_remove_null_key(void);

// Clear
void test_hashmap_clear_empty(void);
void test_hashmap_clear_with_data(void);
void test_hashmap_clear_null(void);

// Resize
void test_hashmap_resize_increase(void);
void test_hashmap_resize_decrease(void);
void test_hashmap_resize_same_capacity(void);
void test_hashmap_resize_null_hashmap(void);

// Types complexes
void test_hashmap_with_structs(void);
void test_hashmap_with_string_values(void);

// Collisions
void test_hashmap_collision_handling(void);

// Stress tests
void test_hashmap_large_dataset(void);
void test_hashmap_insert_remove_cycle(void);
void test_hashmap_key_variations(void);
void test_hashmap_empty_string_key(void);
void test_hashmap_long_key(void);
void test_hashmap_overwrite_protection(void);

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
