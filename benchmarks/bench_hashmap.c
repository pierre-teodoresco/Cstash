#include "bench_framework.h"
#include "cstash/hashmap.h"
#include <stdio.h>

// Helper pour générer des clés uniques
static void generate_key(char* buffer, size_t index) {
    snprintf(buffer, 32, "key_%zu", index);
}

// ============================================================================
// BENCHMARKS: cs_hashmap_create
// ============================================================================

void bench_hashmap_create_bench(BenchContext* ctx) {
    for (size_t i = 0; i < ctx->ops_per_iteration; i++) {
        CsHashMap* map = cs_hashmap_create(sizeof(int));
        cs_hashmap_destroy(map);
    }
}

// ============================================================================
// BENCHMARKS: cs_hashmap_insert (no collision)
// ============================================================================

void bench_hashmap_insert_setup(BenchContext* ctx) {
    ctx->data = cs_hashmap_create(sizeof(int));
}

void bench_hashmap_insert_bench(BenchContext* ctx) {
    CsHashMap* map = (CsHashMap*)ctx->data;
    char key[32];
    int value = 42;

    for (size_t i = 0; i < ctx->ops_per_iteration; i++) {
        generate_key(key, i);
        cs_hashmap_insert(map, key, &value);
    }
}

void bench_hashmap_insert_teardown(BenchContext* ctx) {
    cs_hashmap_destroy((CsHashMap*)ctx->data);
}

// ============================================================================
// BENCHMARKS: cs_hashmap_insert (with resize)
// ============================================================================

void bench_hashmap_insert_resize_bench(BenchContext* ctx) {
    for (size_t i = 0; i < ctx->ops_per_iteration; i++) {
        CsHashMap* map = cs_hashmap_create(sizeof(int));
        char key[32];
        int value = 42;

        // Insérer jusqu'à déclencher un resize (> 75% load factor)
        // Capacité par défaut = 8, donc 7 insertions déclenchent resize
        for (int j = 0; j < 10; j++) {
            generate_key(key, j);
            cs_hashmap_insert(map, key, &value);
        }

        cs_hashmap_destroy(map);
    }
}

// ============================================================================
// BENCHMARKS: cs_hashmap_get (hit)
// ============================================================================

void bench_hashmap_get_hit_setup(BenchContext* ctx) {
    CsHashMap* map = cs_hashmap_create(sizeof(int));
    char key[32];

    // Pré-remplir avec 100 entrées
    for (int i = 0; i < 100; i++) {
        generate_key(key, i);
        cs_hashmap_insert(map, key, &i);
    }

    ctx->data = map;
}

void bench_hashmap_get_hit_bench(BenchContext* ctx) {
    CsHashMap* map = (CsHashMap*)ctx->data;
    char key[32];

    for (size_t i = 0; i < ctx->ops_per_iteration; i++) {
        generate_key(key, 50); // Clé existante
        volatile int* value = (int*)cs_hashmap_get(map, key);
        (void)value;
    }
}

void bench_hashmap_get_hit_teardown(BenchContext* ctx) {
    cs_hashmap_destroy((CsHashMap*)ctx->data);
}

// ============================================================================
// BENCHMARKS: cs_hashmap_get (miss)
// ============================================================================

void bench_hashmap_get_miss_setup(BenchContext* ctx) {
    CsHashMap* map = cs_hashmap_create(sizeof(int));
    char key[32];

    // Pré-remplir avec 100 entrées
    for (int i = 0; i < 100; i++) {
        generate_key(key, i);
        cs_hashmap_insert(map, key, &i);
    }

    ctx->data = map;
}

void bench_hashmap_get_miss_bench(BenchContext* ctx) {
    CsHashMap* map = (CsHashMap*)ctx->data;
    char key[32];

    for (size_t i = 0; i < ctx->ops_per_iteration; i++) {
        generate_key(key, 9999); // Clé inexistante
        volatile int* value = (int*)cs_hashmap_get(map, key);
        (void)value;
    }
}

void bench_hashmap_get_miss_teardown(BenchContext* ctx) {
    cs_hashmap_destroy((CsHashMap*)ctx->data);
}

// ============================================================================
// BENCHMARKS: cs_hashmap_has (hit)
// ============================================================================

void bench_hashmap_has_hit_setup(BenchContext* ctx) {
    CsHashMap* map = cs_hashmap_create(sizeof(int));
    char key[32];

    for (int i = 0; i < 100; i++) {
        generate_key(key, i);
        cs_hashmap_insert(map, key, &i);
    }

    ctx->data = map;
}

void bench_hashmap_has_hit_bench(BenchContext* ctx) {
    CsHashMap* map = (CsHashMap*)ctx->data;
    char key[32];

    for (size_t i = 0; i < ctx->ops_per_iteration; i++) {
        generate_key(key, 50);
        volatile bool exists = cs_hashmap_has(map, key);
        (void)exists;
    }
}

void bench_hashmap_has_hit_teardown(BenchContext* ctx) {
    cs_hashmap_destroy((CsHashMap*)ctx->data);
}

// ============================================================================
// BENCHMARKS: cs_hashmap_remove
// ============================================================================

void bench_hashmap_remove_setup(BenchContext* ctx) {
    CsHashMap** maps = malloc(sizeof(CsHashMap*) * ctx->ops_per_iteration);

    for (size_t i = 0; i < ctx->ops_per_iteration; i++) {
        maps[i] = cs_hashmap_create(sizeof(int));
        char key[32];

        for (int j = 0; j < 100; j++) {
            generate_key(key, j);
            cs_hashmap_insert(maps[i], key, &j);
        }
    }

    ctx->data = maps;
}

void bench_hashmap_remove_bench(BenchContext* ctx) {
    CsHashMap** maps = (CsHashMap**)ctx->data;
    char key[32];

    for (size_t i = 0; i < ctx->ops_per_iteration; i++) {
        generate_key(key, 50);
        cs_hashmap_remove(maps[i], key);
    }
}

void bench_hashmap_remove_teardown(BenchContext* ctx) {
    CsHashMap** maps = (CsHashMap**)ctx->data;
    for (size_t i = 0; i < ctx->ops_per_iteration; i++) {
        cs_hashmap_destroy(maps[i]);
    }
    free(maps);
}

// ============================================================================
// BENCHMARKS: cs_hashmap_clear
// ============================================================================

void bench_hashmap_clear_setup(BenchContext* ctx) {
    CsHashMap** maps = malloc(sizeof(CsHashMap*) * ctx->ops_per_iteration);

    for (size_t i = 0; i < ctx->ops_per_iteration; i++) {
        maps[i] = cs_hashmap_create(sizeof(int));
        char key[32];

        for (int j = 0; j < 100; j++) {
            generate_key(key, j);
            cs_hashmap_insert(maps[i], key, &j);
        }
    }

    ctx->data = maps;
}

void bench_hashmap_clear_bench(BenchContext* ctx) {
    CsHashMap** maps = (CsHashMap**)ctx->data;

    for (size_t i = 0; i < ctx->ops_per_iteration; i++) {
        cs_hashmap_clear(maps[i]);
    }
}

void bench_hashmap_clear_teardown(BenchContext* ctx) {
    CsHashMap** maps = (CsHashMap**)ctx->data;
    for (size_t i = 0; i < ctx->ops_per_iteration; i++) {
        cs_hashmap_destroy(maps[i]);
    }
    free(maps);
}

// ============================================================================
// BENCHMARKS: cs_hashmap_resize
// ============================================================================

void bench_hashmap_resize_setup(BenchContext* ctx) {
    CsHashMap** maps = malloc(sizeof(CsHashMap*) * ctx->ops_per_iteration);

    for (size_t i = 0; i < ctx->ops_per_iteration; i++) {
        maps[i] = cs_hashmap_create(sizeof(int));
        char key[32];

        for (int j = 0; j < 50; j++) {
            generate_key(key, j);
            cs_hashmap_insert(maps[i], key, &j);
        }
    }

    ctx->data = maps;
}

void bench_hashmap_resize_bench(BenchContext* ctx) {
    CsHashMap** maps = (CsHashMap**)ctx->data;

    for (size_t i = 0; i < ctx->ops_per_iteration; i++) {
        cs_hashmap_resize(maps[i], 1000); // Resize à 1000 buckets
    }
}

void bench_hashmap_resize_teardown(BenchContext* ctx) {
    CsHashMap** maps = (CsHashMap**)ctx->data;
    for (size_t i = 0; i < ctx->ops_per_iteration; i++) {
        cs_hashmap_destroy(maps[i]);
    }
    free(maps);
}

// ============================================================================
// MAIN
// ============================================================================

int main(void) {
    BENCH_INIT();

    BenchDef benchmarks[] = {
        {"cs_hashmap_create", NULL, bench_hashmap_create_bench, NULL, BENCH_DEFAULT_ITERATIONS,
         BENCH_DEFAULT_OPS_PER_ITERATION, 0},

        {"cs_hashmap_insert (no collision)", bench_hashmap_insert_setup, bench_hashmap_insert_bench,
         bench_hashmap_insert_teardown, BENCH_DEFAULT_ITERATIONS, BENCH_DEFAULT_OPS_PER_ITERATION, 0},

        {"cs_hashmap_insert (with resize)", NULL, bench_hashmap_insert_resize_bench, NULL, BENCH_DEFAULT_ITERATIONS,
         BENCH_DEFAULT_OPS_PER_ITERATION, 0},

        {"cs_hashmap_get (hit)", bench_hashmap_get_hit_setup, bench_hashmap_get_hit_bench,
         bench_hashmap_get_hit_teardown, BENCH_DEFAULT_ITERATIONS, BENCH_DEFAULT_OPS_PER_ITERATION, 100},

        {"cs_hashmap_get (miss)", bench_hashmap_get_miss_setup, bench_hashmap_get_miss_bench,
         bench_hashmap_get_miss_teardown, BENCH_DEFAULT_ITERATIONS, BENCH_DEFAULT_OPS_PER_ITERATION, 100},

        {"cs_hashmap_has (hit)", bench_hashmap_has_hit_setup, bench_hashmap_has_hit_bench,
         bench_hashmap_has_hit_teardown, BENCH_DEFAULT_ITERATIONS, BENCH_DEFAULT_OPS_PER_ITERATION, 100},

        {"cs_hashmap_remove", bench_hashmap_remove_setup, bench_hashmap_remove_bench, bench_hashmap_remove_teardown,
         BENCH_DEFAULT_ITERATIONS, BENCH_DEFAULT_OPS_PER_ITERATION, 100},

        {"cs_hashmap_clear", bench_hashmap_clear_setup, bench_hashmap_clear_bench, bench_hashmap_clear_teardown,
         BENCH_DEFAULT_ITERATIONS, BENCH_DEFAULT_OPS_PER_ITERATION, 100},

        {"cs_hashmap_resize", bench_hashmap_resize_setup, bench_hashmap_resize_bench, bench_hashmap_resize_teardown,
         BENCH_DEFAULT_ITERATIONS, BENCH_DEFAULT_OPS_PER_ITERATION, 50},
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
