#include "bench_framework.h"
#include "cstash/stack.h"

// ============================================================================
// BENCHMARKS: cs_stack_create
// ============================================================================

void bench_stack_create_bench(BenchContext* ctx) {
    for (size_t i = 0; i < ctx->ops_per_iteration; i++) {
        CsStack* stack = cs_stack_create(sizeof(int));
        cs_stack_destroy(stack);
    }
}

// ============================================================================
// BENCHMARKS: cs_stack_push
// ============================================================================

void bench_stack_push_setup(BenchContext* ctx) {
    ctx->data = cs_stack_create(sizeof(int));
}

void bench_stack_push_bench(BenchContext* ctx) {
    CsStack* stack = (CsStack*)ctx->data;
    int value = 42;
    for (size_t i = 0; i < ctx->ops_per_iteration; i++) {
        cs_stack_push(stack, &value);
    }
}

void bench_stack_push_teardown(BenchContext* ctx) {
    cs_stack_destroy((CsStack*)ctx->data);
}

// ============================================================================
// BENCHMARKS: cs_stack_pop
// ============================================================================

void bench_stack_pop_setup(BenchContext* ctx) {
    CsStack** stacks = malloc(sizeof(CsStack*) * ctx->ops_per_iteration);
    for (size_t i = 0; i < ctx->ops_per_iteration; i++) {
        stacks[i] = cs_stack_create(sizeof(int));
        for (int j = 0; j < 100; j++) {
            cs_stack_push(stacks[i], &j);
        }
    }
    ctx->data = stacks;
}

void bench_stack_pop_bench(BenchContext* ctx) {
    CsStack** stacks = (CsStack**)ctx->data;
    for (size_t i = 0; i < ctx->ops_per_iteration; i++) {
        void* elem = cs_stack_pop(stacks[i]);
        free(elem);
    }
}

void bench_stack_pop_teardown(BenchContext* ctx) {
    CsStack** stacks = (CsStack**)ctx->data;
    for (size_t i = 0; i < ctx->ops_per_iteration; i++) {
        cs_stack_destroy(stacks[i]);
    }
    free(stacks);
}

// ============================================================================
// BENCHMARKS: cs_stack_clear
// ============================================================================

void bench_stack_clear_setup(BenchContext* ctx) {
    CsStack** stacks = malloc(sizeof(CsStack*) * ctx->ops_per_iteration);
    for (size_t i = 0; i < ctx->ops_per_iteration; i++) {
        stacks[i] = cs_stack_create(sizeof(int));
        for (int j = 0; j < 100; j++) {
            cs_stack_push(stacks[i], &j);
        }
    }
    ctx->data = stacks;
}

void bench_stack_clear_bench(BenchContext* ctx) {
    CsStack** stacks = (CsStack**)ctx->data;
    for (size_t i = 0; i < ctx->ops_per_iteration; i++) {
        cs_stack_clear(stacks[i]);
    }
}

void bench_stack_clear_teardown(BenchContext* ctx) {
    CsStack** stacks = (CsStack**)ctx->data;
    for (size_t i = 0; i < ctx->ops_per_iteration; i++) {
        cs_stack_destroy(stacks[i]);
    }
    free(stacks);
}

// ============================================================================
// MAIN
// ============================================================================

int main(void) {
    BENCH_INIT();

    BenchDef benchmarks[] = {
        {"cs_stack_create", NULL, bench_stack_create_bench, NULL, BENCH_DEFAULT_ITERATIONS,
         BENCH_DEFAULT_OPS_PER_ITERATION, 0},

        {"cs_stack_push", bench_stack_push_setup, bench_stack_push_bench, bench_stack_push_teardown,
         BENCH_DEFAULT_ITERATIONS, BENCH_DEFAULT_OPS_PER_ITERATION, 100},

        {"cs_stack_pop", bench_stack_pop_setup, bench_stack_pop_bench, bench_stack_pop_teardown,
         BENCH_DEFAULT_ITERATIONS, BENCH_DEFAULT_OPS_PER_ITERATION, 100},

        {"cs_stack_clear", bench_stack_clear_setup, bench_stack_clear_bench, bench_stack_clear_teardown,
         BENCH_DEFAULT_ITERATIONS, BENCH_DEFAULT_OPS_PER_ITERATION, 100},
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
