#include "bench_framework.h"
#include "cstash/vector.h"

// ============================================================================
// BENCHMARKS: cs_vector_create
// ============================================================================

void bench_vector_create_bench(BenchContext* ctx) {
    for (size_t i = 0; i < ctx->ops_per_iteration; i++) {
        CsVector* vec = cs_vector_create(sizeof(int), VECTOR_DEFAULT_CAPACITY, NULL);
        cs_vector_destroy(vec);
    }
}

// ============================================================================
// BENCHMARKS: cs_vector_push (avec vecteur vide)
// ============================================================================

void bench_vector_push_setup(BenchContext* ctx) {
    ctx->data = cs_vector_create(sizeof(int), VECTOR_DEFAULT_CAPACITY, NULL);
}

void bench_vector_push_bench(BenchContext* ctx) {
    CsVector* vec = (CsVector*)ctx->data;
    int value = 42;
    for (size_t i = 0; i < ctx->ops_per_iteration; i++) {
        cs_vector_push(vec, &value);
    }
}

void bench_vector_push_teardown(BenchContext* ctx) {
    cs_vector_destroy((CsVector*)ctx->data);
}

// ============================================================================
// BENCHMARKS: cs_vector_push (avec réallocation forcée)
// ============================================================================

void bench_vector_push_realloc_setup(BenchContext* ctx) {
    // On va créer un vecteur de capacité 1 à chaque itération dans le bench
    // pour forcer la réallocation
    (void)ctx; // unused param
}

void bench_vector_push_realloc_bench(BenchContext* ctx) {
    for (size_t i = 0; i < ctx->ops_per_iteration; i++) {
        CsVector* vec = cs_vector_create(sizeof(int), 1, NULL);
        int val = 1;
        cs_vector_push(vec, &val); // OK
        cs_vector_push(vec, &val); // Force reallocation
        cs_vector_destroy(vec);
    }
}

// ============================================================================
// BENCHMARKS: cs_vector_get
// ============================================================================

void bench_vector_get_setup(BenchContext* ctx) {
    CsVector* vec = cs_vector_create(sizeof(int), 100, NULL);
    for (int i = 0; i < 100; i++) {
        cs_vector_push(vec, &i);
    }
    ctx->data = vec;
}

void bench_vector_get_bench(BenchContext* ctx) {
    CsVector* vec = (CsVector*)ctx->data;
    for (size_t i = 0; i < ctx->ops_per_iteration; i++) {
        volatile int* value = (int*)cs_vector_get(vec, 50);
        (void)value;
    }
}

void bench_vector_get_teardown(BenchContext* ctx) {
    cs_vector_destroy((CsVector*)ctx->data);
}

// ============================================================================
// BENCHMARKS: cs_vector_pop
// ============================================================================

void bench_vector_pop_setup(BenchContext* ctx) {
    // Pré-créer tous les vecteurs avec suffisamment d'éléments
    CsVector** vectors = malloc(sizeof(CsVector*) * ctx->ops_per_iteration);
    for (size_t i = 0; i < ctx->ops_per_iteration; i++) {
        vectors[i] = cs_vector_create(sizeof(int), 100, NULL);
        for (int j = 0; j < 100; j++) {
            cs_vector_push(vectors[i], &j);
        }
    }
    ctx->data = vectors;
}

void bench_vector_pop_bench(BenchContext* ctx) {
    CsVector** vectors = (CsVector**)ctx->data;
    for (size_t i = 0; i < ctx->ops_per_iteration; i++) {
        cs_vector_pop(vectors[i]); // Pop une fois sur chaque vecteur
    }
}

void bench_vector_pop_teardown(BenchContext* ctx) {
    CsVector** vectors = (CsVector**)ctx->data;
    for (size_t i = 0; i < ctx->ops_per_iteration; i++) {
        cs_vector_destroy(vectors[i]);
    }
    free(vectors);
}

// ============================================================================
// BENCHMARKS: cs_vector_reserve
// ============================================================================

void bench_vector_reserve_setup(BenchContext* ctx) {
    // Créer un tableau de vecteurs pour forcer la réallocation à chaque fois
    CsVector** vectors = malloc(sizeof(CsVector*) * ctx->ops_per_iteration);
    for (size_t i = 0; i < ctx->ops_per_iteration; i++) {
        vectors[i] = cs_vector_create(sizeof(int), VECTOR_DEFAULT_CAPACITY, NULL);
    }
    ctx->data = vectors;
}

void bench_vector_reserve_bench(BenchContext* ctx) {
    CsVector** vectors = (CsVector**)ctx->data;
    for (size_t i = 0; i < ctx->ops_per_iteration; i++) {
        cs_vector_reserve(vectors[i], 1000); // Force reallocation
    }
}

void bench_vector_reserve_teardown(BenchContext* ctx) {
    CsVector** vectors = (CsVector**)ctx->data;
    for (size_t i = 0; i < ctx->ops_per_iteration; i++) {
        cs_vector_destroy(vectors[i]);
    }
    free(vectors);
}

// ============================================================================
// BENCHMARKS: cs_vector_clear
// ============================================================================

void bench_vector_clear_setup(BenchContext* ctx) {
    // Pré-créer tous les vecteurs nécessaires
    CsVector** vectors = malloc(sizeof(CsVector*) * ctx->ops_per_iteration);
    for (size_t i = 0; i < ctx->ops_per_iteration; i++) {
        vectors[i] = cs_vector_create(sizeof(int), 100, NULL);
        for (int j = 0; j < 100; j++) {
            cs_vector_push(vectors[i], &j);
        }
    }
    ctx->data = vectors;
}

void bench_vector_clear_bench(BenchContext* ctx) {
    CsVector** vectors = (CsVector**)ctx->data;
    for (size_t i = 0; i < ctx->ops_per_iteration; i++) {
        cs_vector_clear(vectors[i]);
    }
}

void bench_vector_clear_teardown(BenchContext* ctx) {
    CsVector** vectors = (CsVector**)ctx->data;
    for (size_t i = 0; i < ctx->ops_per_iteration; i++) {
        cs_vector_destroy(vectors[i]);
    }
    free(vectors);
}

// ============================================================================
// BENCHMARKS: cs_vector_clone
// ============================================================================

void bench_vector_clone_setup(BenchContext* ctx) {
    CsVector* vec = cs_vector_create(sizeof(int), 100, NULL);
    for (int i = 0; i < 100; i++) {
        cs_vector_push(vec, &i);
    }
    ctx->data = vec;
}

void bench_vector_clone_bench(BenchContext* ctx) {
    CsVector* vec = (CsVector*)ctx->data;
    for (size_t i = 0; i < ctx->ops_per_iteration; i++) {
        CsVector* clone = cs_vector_clone(vec);
        cs_vector_destroy(clone);
    }
}

void bench_vector_clone_teardown(BenchContext* ctx) {
    cs_vector_destroy((CsVector*)ctx->data);
}

// ============================================================================
// MAIN
// ============================================================================

int main(void) {
    BENCH_INIT();

    BenchDef benchmarks[] = {
        // name, setup, bench, teardown, iterations, ops_per_iteration, data_size
        {"cs_vector_create", NULL, bench_vector_create_bench, NULL, BENCH_DEFAULT_ITERATIONS,
         BENCH_DEFAULT_OPS_PER_ITERATION, 0},
        {"cs_vector_push (empty)", bench_vector_push_setup, bench_vector_push_bench, bench_vector_push_teardown,
         BENCH_DEFAULT_ITERATIONS, BENCH_DEFAULT_OPS_PER_ITERATION, 0},
        {"cs_vector_push (realloc)", NULL, bench_vector_push_realloc_bench, NULL, BENCH_DEFAULT_ITERATIONS,
         BENCH_DEFAULT_OPS_PER_ITERATION, 0},
        {"cs_vector_get (middle)", bench_vector_get_setup, bench_vector_get_bench, bench_vector_get_teardown,
         BENCH_DEFAULT_ITERATIONS, BENCH_DEFAULT_OPS_PER_ITERATION, 100},
        {"cs_vector_pop", bench_vector_pop_setup, bench_vector_pop_bench, bench_vector_pop_teardown,
         BENCH_DEFAULT_ITERATIONS, BENCH_DEFAULT_OPS_PER_ITERATION, 100},
        {"cs_vector_reserve", bench_vector_reserve_setup, bench_vector_reserve_bench, bench_vector_reserve_teardown,
         BENCH_DEFAULT_ITERATIONS, BENCH_DEFAULT_OPS_PER_ITERATION, 0},
        {"cs_vector_clear", bench_vector_clear_setup, bench_vector_clear_bench, bench_vector_clear_teardown,
         BENCH_DEFAULT_ITERATIONS, BENCH_DEFAULT_OPS_PER_ITERATION, 100},
        {"cs_vector_clone", bench_vector_clone_setup, bench_vector_clone_bench, bench_vector_clone_teardown,
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
