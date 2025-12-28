#include "bench_framework.h"
#include "cstash/linkedlist.h"

// ============================================================================
// BENCHMARKS: cs_linkedlist_create
// ============================================================================

void bench_linkedlist_create_bench(BenchContext* ctx) {
    for (size_t i = 0; i < ctx->ops_per_iteration; i++) {
        CsLinkedList* list = cs_linkedlist_create(sizeof(int));
        cs_linkedlist_destroy(list);
    }
}

// ============================================================================
// BENCHMARKS: cs_linkedlist_push_front
// ============================================================================

void bench_linkedlist_push_front_setup(BenchContext* ctx) {
    ctx->data = cs_linkedlist_create(sizeof(int));
}

void bench_linkedlist_push_front_bench(BenchContext* ctx) {
    CsLinkedList* list = (CsLinkedList*)ctx->data;
    int value = 42;
    for (size_t i = 0; i < ctx->ops_per_iteration; i++) {
        cs_linkedlist_push_front(list, &value);
    }
}

void bench_linkedlist_push_front_teardown(BenchContext* ctx) {
    cs_linkedlist_destroy((CsLinkedList*)ctx->data);
}

// ============================================================================
// BENCHMARKS: cs_linkedlist_push_back
// ============================================================================

void bench_linkedlist_push_back_setup(BenchContext* ctx) {
    ctx->data = cs_linkedlist_create(sizeof(int));
}

void bench_linkedlist_push_back_bench(BenchContext* ctx) {
    CsLinkedList* list = (CsLinkedList*)ctx->data;
    int value = 42;
    for (size_t i = 0; i < ctx->ops_per_iteration; i++) {
        cs_linkedlist_push_back(list, &value);
    }
}

void bench_linkedlist_push_back_teardown(BenchContext* ctx) {
    cs_linkedlist_destroy((CsLinkedList*)ctx->data);
}

// ============================================================================
// BENCHMARKS: cs_linkedlist_insert_at (middle)
// ============================================================================

void bench_linkedlist_insert_at_setup(BenchContext* ctx) {
    CsLinkedList* list = cs_linkedlist_create(sizeof(int));
    // Pré-remplir avec 100 éléments
    for (int i = 0; i < 100; i++) {
        cs_linkedlist_push_back(list, &i);
    }
    ctx->data = list;
}

void bench_linkedlist_insert_at_bench(BenchContext* ctx) {
    CsLinkedList* list = (CsLinkedList*)ctx->data;
    int value = 42;
    for (size_t i = 0; i < ctx->ops_per_iteration; i++) {
        cs_linkedlist_insert_at(list, &value, 50); // Milieu
    }
}

void bench_linkedlist_insert_at_teardown(BenchContext* ctx) {
    cs_linkedlist_destroy((CsLinkedList*)ctx->data);
}

// ============================================================================
// BENCHMARKS: cs_linkedlist_get (front)
// ============================================================================

void bench_linkedlist_get_front_setup(BenchContext* ctx) {
    CsLinkedList* list = cs_linkedlist_create(sizeof(int));
    for (int i = 0; i < 100; i++) {
        cs_linkedlist_push_back(list, &i);
    }
    ctx->data = list;
}

void bench_linkedlist_get_front_bench(BenchContext* ctx) {
    CsLinkedList* list = (CsLinkedList*)ctx->data;
    for (size_t i = 0; i < ctx->ops_per_iteration; i++) {
        volatile int* value = (int*)cs_linkedlist_get(list, 0);
        (void)value;
    }
}

void bench_linkedlist_get_front_teardown(BenchContext* ctx) {
    cs_linkedlist_destroy((CsLinkedList*)ctx->data);
}

// ============================================================================
// BENCHMARKS: cs_linkedlist_get (middle)
// ============================================================================

void bench_linkedlist_get_middle_setup(BenchContext* ctx) {
    CsLinkedList* list = cs_linkedlist_create(sizeof(int));
    for (int i = 0; i < 100; i++) {
        cs_linkedlist_push_back(list, &i);
    }
    ctx->data = list;
}

void bench_linkedlist_get_middle_bench(BenchContext* ctx) {
    CsLinkedList* list = (CsLinkedList*)ctx->data;
    for (size_t i = 0; i < ctx->ops_per_iteration; i++) {
        volatile int* value = (int*)cs_linkedlist_get(list, 50);
        (void)value;
    }
}

void bench_linkedlist_get_middle_teardown(BenchContext* ctx) {
    cs_linkedlist_destroy((CsLinkedList*)ctx->data);
}

// ============================================================================
// BENCHMARKS: cs_linkedlist_front
// ============================================================================

void bench_linkedlist_front_setup(BenchContext* ctx) {
    CsLinkedList* list = cs_linkedlist_create(sizeof(int));
    for (int i = 0; i < 100; i++) {
        cs_linkedlist_push_back(list, &i);
    }
    ctx->data = list;
}

void bench_linkedlist_front_bench(BenchContext* ctx) {
    CsLinkedList* list = (CsLinkedList*)ctx->data;
    for (size_t i = 0; i < ctx->ops_per_iteration; i++) {
        volatile int* value = (int*)cs_linkedlist_front(list);
        (void)value;
    }
}

void bench_linkedlist_front_teardown(BenchContext* ctx) {
    cs_linkedlist_destroy((CsLinkedList*)ctx->data);
}

// ============================================================================
// BENCHMARKS: cs_linkedlist_back
// ============================================================================

void bench_linkedlist_back_setup(BenchContext* ctx) {
    CsLinkedList* list = cs_linkedlist_create(sizeof(int));
    for (int i = 0; i < 100; i++) {
        cs_linkedlist_push_back(list, &i);
    }
    ctx->data = list;
}

void bench_linkedlist_back_bench(BenchContext* ctx) {
    CsLinkedList* list = (CsLinkedList*)ctx->data;
    for (size_t i = 0; i < ctx->ops_per_iteration; i++) {
        volatile int* value = (int*)cs_linkedlist_back(list);
        (void)value;
    }
}

void bench_linkedlist_back_teardown(BenchContext* ctx) {
    cs_linkedlist_destroy((CsLinkedList*)ctx->data);
}

// ============================================================================
// BENCHMARKS: cs_linkedlist_pop_front
// ============================================================================

void bench_linkedlist_pop_front_setup(BenchContext* ctx) {
    CsLinkedList** lists = malloc(sizeof(CsLinkedList*) * ctx->ops_per_iteration);
    for (size_t i = 0; i < ctx->ops_per_iteration; i++) {
        lists[i] = cs_linkedlist_create(sizeof(int));
        for (int j = 0; j < 100; j++) {
            cs_linkedlist_push_back(lists[i], &j);
        }
    }
    ctx->data = lists;
}

void bench_linkedlist_pop_front_bench(BenchContext* ctx) {
    CsLinkedList** lists = (CsLinkedList**)ctx->data;
    for (size_t i = 0; i < ctx->ops_per_iteration; i++) {
        void* elem = cs_linkedlist_pop_front(lists[i]);
        free(elem);
    }
}

void bench_linkedlist_pop_front_teardown(BenchContext* ctx) {
    CsLinkedList** lists = (CsLinkedList**)ctx->data;
    for (size_t i = 0; i < ctx->ops_per_iteration; i++) {
        cs_linkedlist_destroy(lists[i]);
    }
    free(lists);
}

// ============================================================================
// BENCHMARKS: cs_linkedlist_pop_back
// ============================================================================

void bench_linkedlist_pop_back_setup(BenchContext* ctx) {
    CsLinkedList** lists = malloc(sizeof(CsLinkedList*) * ctx->ops_per_iteration);
    for (size_t i = 0; i < ctx->ops_per_iteration; i++) {
        lists[i] = cs_linkedlist_create(sizeof(int));
        for (int j = 0; j < 100; j++) {
            cs_linkedlist_push_back(lists[i], &j);
        }
    }
    ctx->data = lists;
}

void bench_linkedlist_pop_back_bench(BenchContext* ctx) {
    CsLinkedList** lists = (CsLinkedList**)ctx->data;
    for (size_t i = 0; i < ctx->ops_per_iteration; i++) {
        void* elem = cs_linkedlist_pop_back(lists[i]);
        free(elem);
    }
}

void bench_linkedlist_pop_back_teardown(BenchContext* ctx) {
    CsLinkedList** lists = (CsLinkedList**)ctx->data;
    for (size_t i = 0; i < ctx->ops_per_iteration; i++) {
        cs_linkedlist_destroy(lists[i]);
    }
    free(lists);
}

// ============================================================================
// BENCHMARKS: cs_linkedlist_remove_at (middle)
// ============================================================================

void bench_linkedlist_remove_at_setup(BenchContext* ctx) {
    CsLinkedList** lists = malloc(sizeof(CsLinkedList*) * ctx->ops_per_iteration);
    for (size_t i = 0; i < ctx->ops_per_iteration; i++) {
        lists[i] = cs_linkedlist_create(sizeof(int));
        for (int j = 0; j < 100; j++) {
            cs_linkedlist_push_back(lists[i], &j);
        }
    }
    ctx->data = lists;
}

void bench_linkedlist_remove_at_bench(BenchContext* ctx) {
    CsLinkedList** lists = (CsLinkedList**)ctx->data;
    for (size_t i = 0; i < ctx->ops_per_iteration; i++) {
        cs_linkedlist_remove_at(lists[i], 50); // Milieu
    }
}

void bench_linkedlist_remove_at_teardown(BenchContext* ctx) {
    CsLinkedList** lists = (CsLinkedList**)ctx->data;
    for (size_t i = 0; i < ctx->ops_per_iteration; i++) {
        cs_linkedlist_destroy(lists[i]);
    }
    free(lists);
}

// ============================================================================
// BENCHMARKS: cs_linkedlist_clear
// ============================================================================

void bench_linkedlist_clear_setup(BenchContext* ctx) {
    CsLinkedList** lists = malloc(sizeof(CsLinkedList*) * ctx->ops_per_iteration);
    for (size_t i = 0; i < ctx->ops_per_iteration; i++) {
        lists[i] = cs_linkedlist_create(sizeof(int));
        for (int j = 0; j < 100; j++) {
            cs_linkedlist_push_back(lists[i], &j);
        }
    }
    ctx->data = lists;
}

void bench_linkedlist_clear_bench(BenchContext* ctx) {
    CsLinkedList** lists = (CsLinkedList**)ctx->data;
    for (size_t i = 0; i < ctx->ops_per_iteration; i++) {
        cs_linkedlist_clear(lists[i]);
    }
}

void bench_linkedlist_clear_teardown(BenchContext* ctx) {
    CsLinkedList** lists = (CsLinkedList**)ctx->data;
    for (size_t i = 0; i < ctx->ops_per_iteration; i++) {
        cs_linkedlist_destroy(lists[i]);
    }
    free(lists);
}

// ============================================================================
// MAIN
// ============================================================================

int main(void) {
    BENCH_INIT();

    BenchDef benchmarks[] = {
        {"cs_linkedlist_create", NULL, bench_linkedlist_create_bench, NULL, BENCH_DEFAULT_ITERATIONS,
         BENCH_DEFAULT_OPS_PER_ITERATION, 0},

        {"cs_linkedlist_push_front", bench_linkedlist_push_front_setup, bench_linkedlist_push_front_bench,
         bench_linkedlist_push_front_teardown, BENCH_DEFAULT_ITERATIONS, BENCH_DEFAULT_OPS_PER_ITERATION, 0},

        {"cs_linkedlist_push_back", bench_linkedlist_push_back_setup, bench_linkedlist_push_back_bench,
         bench_linkedlist_push_back_teardown, BENCH_DEFAULT_ITERATIONS, BENCH_DEFAULT_OPS_PER_ITERATION, 0},

        {"cs_linkedlist_insert_at (middle)", bench_linkedlist_insert_at_setup, bench_linkedlist_insert_at_bench,
         bench_linkedlist_insert_at_teardown, BENCH_DEFAULT_ITERATIONS, BENCH_DEFAULT_OPS_PER_ITERATION, 100},

        {"cs_linkedlist_get (front)", bench_linkedlist_get_front_setup, bench_linkedlist_get_front_bench,
         bench_linkedlist_get_front_teardown, BENCH_DEFAULT_ITERATIONS, BENCH_DEFAULT_OPS_PER_ITERATION, 100},

        {"cs_linkedlist_get (middle)", bench_linkedlist_get_middle_setup, bench_linkedlist_get_middle_bench,
         bench_linkedlist_get_middle_teardown, BENCH_DEFAULT_ITERATIONS, BENCH_DEFAULT_OPS_PER_ITERATION, 100},

        {"cs_linkedlist_front", bench_linkedlist_front_setup, bench_linkedlist_front_bench,
         bench_linkedlist_front_teardown, BENCH_DEFAULT_ITERATIONS, BENCH_DEFAULT_OPS_PER_ITERATION, 100},

        {"cs_linkedlist_back", bench_linkedlist_back_setup, bench_linkedlist_back_bench, bench_linkedlist_back_teardown,
         BENCH_DEFAULT_ITERATIONS, BENCH_DEFAULT_OPS_PER_ITERATION, 100},

        {"cs_linkedlist_pop_front", bench_linkedlist_pop_front_setup, bench_linkedlist_pop_front_bench,
         bench_linkedlist_pop_front_teardown, BENCH_DEFAULT_ITERATIONS, BENCH_DEFAULT_OPS_PER_ITERATION, 100},

        {"cs_linkedlist_pop_back", bench_linkedlist_pop_back_setup, bench_linkedlist_pop_back_bench,
         bench_linkedlist_pop_back_teardown, BENCH_DEFAULT_ITERATIONS, BENCH_DEFAULT_OPS_PER_ITERATION, 100},

        {"cs_linkedlist_remove_at (middle)", bench_linkedlist_remove_at_setup, bench_linkedlist_remove_at_bench,
         bench_linkedlist_remove_at_teardown, BENCH_DEFAULT_ITERATIONS, BENCH_DEFAULT_OPS_PER_ITERATION, 100},

        {"cs_linkedlist_clear", bench_linkedlist_clear_setup, bench_linkedlist_clear_bench,
         bench_linkedlist_clear_teardown, BENCH_DEFAULT_ITERATIONS, BENCH_DEFAULT_OPS_PER_ITERATION, 100},
    };

    size_t num_benchmarks = sizeof(benchmarks) / sizeof(benchmarks[0]);

    printf("\n");
    for (size_t i = 0; i < num_benchmarks; i++) {
        BenchResult result = bench_run(&benchmarks[i]);
        bench_print_result(&result);
        printf("\n");
    }

    BENCH_SUMMARY();

    return 0;
}
