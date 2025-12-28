#ifndef BENCH_FRAMEWORK_H
#define BENCH_FRAMEWORK_H

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Couleurs
#define BENCH_COLOR_CYAN "\x1b[36m"
#define BENCH_COLOR_GREEN "\x1b[32m"
#define BENCH_COLOR_YELLOW "\x1b[33m"
#define BENCH_COLOR_BLUE "\x1b[34m"
#define BENCH_COLOR_MAGENTA "\x1b[35m"
#define BENCH_COLOR_RESET "\x1b[0m"

#define BENCH_DEFAULT_ITERATIONS 1000
#define BENCH_DEFAULT_OPS_PER_ITERATION 100 // Nouvelles ! Faire 100 ops par mesure

// Context passé entre setup/bench/teardown
typedef struct {
    void* data;
    size_t data_size;
    size_t ops_per_iteration; // Nombre d'opérations à faire dans bench()
} BenchContext;

// Résultats d'un benchmark
typedef struct {
    const char* name;
    uint64_t min_ns;
    uint64_t max_ns;
    uint64_t avg_ns;
    uint64_t median_ns;
    size_t iterations;
    size_t data_size;
} BenchResult;

// Définition d'un benchmark
typedef struct {
    const char* name;
    void (*setup)(BenchContext* ctx);
    void (*bench)(BenchContext* ctx); // Doit exécuter ctx->ops_per_iteration fois l'opération
    void (*teardown)(BenchContext* ctx);
    size_t iterations;
    size_t ops_per_iteration; // Nombre d'ops à faire par mesure
    size_t data_size;
} BenchDef;

// Obtenir le temps en nanosecondes
static inline uint64_t bench_get_time_ns(void) {
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return (uint64_t)ts.tv_sec * 1000000000ULL + (uint64_t)ts.tv_nsec;
}

// Comparaison pour qsort (médiane)
static int compare_uint64(const void* a, const void* b) {
    uint64_t ua = *(const uint64_t*)a;
    uint64_t ub = *(const uint64_t*)b;
    return (ua > ub) - (ua < ub);
}

// Exécuter un benchmark
static inline BenchResult bench_run(const BenchDef* def) {
    BenchResult result = {0};
    result.name = def->name;
    result.iterations = def->iterations;
    result.data_size = def->data_size;
    result.min_ns = UINT64_MAX;
    result.max_ns = 0;

    uint64_t* times = malloc(sizeof(uint64_t) * def->iterations);
    if (!times) {
        fprintf(stderr, "Failed to allocate memory for benchmark times\n");
        return result;
    }

    uint64_t total_ns = 0;

    printf(BENCH_COLOR_YELLOW "[BENCH]" BENCH_COLOR_RESET " %s", def->name);
    if (def->data_size > 0) {
        printf(" (size: %zu)", def->data_size);
    }
    printf(" - %zu iterations × %zu ops\n", def->iterations, def->ops_per_iteration);

    for (size_t i = 0; i < def->iterations; i++) {
        BenchContext ctx = {0};
        ctx.ops_per_iteration = def->ops_per_iteration;

        // Setup
        if (def->setup) {
            def->setup(&ctx);
        }

        // Mesure (bench fait ops_per_iteration fois l'opération)
        uint64_t start = bench_get_time_ns();
        def->bench(&ctx);
        uint64_t end = bench_get_time_ns();

        // Teardown
        if (def->teardown) {
            def->teardown(&ctx);
        }

        // Diviser par le nombre d'opérations pour avoir le temps par op
        uint64_t elapsed = (end - start) / def->ops_per_iteration;
        times[i] = elapsed;
        total_ns += elapsed;

        if (elapsed < result.min_ns) result.min_ns = elapsed;
        if (elapsed > result.max_ns) result.max_ns = elapsed;
    }

    result.avg_ns = total_ns / def->iterations;

    // Calcul de la médiane
    qsort(times, def->iterations, sizeof(uint64_t), compare_uint64);
    result.median_ns = times[def->iterations / 2];

    free(times);
    return result;
}

// Affichage d'un résultat
static inline void bench_print_result(const BenchResult* result) {
    printf(BENCH_COLOR_GREEN "  ✓ " BENCH_COLOR_RESET);
    printf("%-40s ", result->name);

    // Convertir en unité appropriée
    const char* unit;
    double min_val, avg_val, max_val, median_val;

    if (result->avg_ns < 1000) {
        unit = "ns";
        min_val = result->min_ns;
        avg_val = result->avg_ns;
        max_val = result->max_ns;
        median_val = result->median_ns;
    } else if (result->avg_ns < 1000000) {
        unit = "μs";
        min_val = result->min_ns / 1000.0;
        avg_val = result->avg_ns / 1000.0;
        max_val = result->max_ns / 1000.0;
        median_val = result->median_ns / 1000.0;
    } else if (result->avg_ns < 1000000000) {
        unit = "ms";
        min_val = result->min_ns / 1000000.0;
        avg_val = result->avg_ns / 1000000.0;
        max_val = result->max_ns / 1000000.0;
        median_val = result->median_ns / 1000000.0;
    } else {
        unit = "s";
        min_val = result->min_ns / 1000000000.0;
        avg_val = result->avg_ns / 1000000000.0;
        max_val = result->max_ns / 1000000000.0;
        median_val = result->median_ns / 1000000000.0;
    }

    printf("avg: " BENCH_COLOR_CYAN "%.2f%s" BENCH_COLOR_RESET " | ", avg_val, unit);
    printf("med: %.2f%s | ", median_val, unit);
    printf("min: %.2f%s | ", min_val, unit);
    printf("max: %.2f%s\n", max_val, unit);
}

// Initialisation
#define BENCH_INIT()                                                                                                   \
    printf(BENCH_COLOR_BLUE                                                                                            \
           "\n═══════════════════════════════════════════════════════════════════════\n" BENCH_COLOR_RESET);           \
    printf(BENCH_COLOR_BLUE "                         BENCHMARK SUITE\n" BENCH_COLOR_RESET);                           \
    printf(BENCH_COLOR_BLUE                                                                                            \
           "═══════════════════════════════════════════════════════════════════════\n" BENCH_COLOR_RESET)

// Résumé
#define BENCH_SUMMARY()                                                                                                \
    printf(BENCH_COLOR_BLUE                                                                                            \
           "═══════════════════════════════════════════════════════════════════════\n" BENCH_COLOR_RESET);             \
    printf(BENCH_COLOR_GREEN "                    BENCHMARK COMPLETE\n" BENCH_COLOR_RESET);                            \
    printf(BENCH_COLOR_BLUE                                                                                            \
           "═══════════════════════════════════════════════════════════════════════\n" BENCH_COLOR_RESET)

#endif // BENCH_FRAMEWORK_H
