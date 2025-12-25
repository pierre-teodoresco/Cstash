#ifndef TEST_FRAMEWORK_H
#define TEST_FRAMEWORK_H

#include <stdio.h>
#include <string.h>

// Couleurs ANSI (optionnel, fonctionne sur Linux/Mac/Windows 10+)
#define COLOR_RED "\x1b[31m"
#define COLOR_GREEN "\x1b[32m"
#define COLOR_YELLOW "\x1b[33m"
#define COLOR_BLUE "\x1b[34m"
#define COLOR_MAGENTA "\033[35m"
#define COLOR_RESET "\x1b[0m"

// Compteurs globaux
static int tests_run = 0;
static int tests_passed = 0;
static int tests_failed = 0;
static int assertions_passed = 0;
static int assertions_failed = 0;

// Initialisation
#define TEST_INIT()                                                                                                    \
    do {                                                                                                               \
        tests_run = 0;                                                                                                 \
        tests_passed = 0;                                                                                              \
        tests_failed = 0;                                                                                              \
        assertions_passed = 0;                                                                                         \
        assertions_failed = 0;                                                                                         \
    } while (0)

// Résumé final
#define TEST_SUMMARY()                                                                                                 \
    do {                                                                                                               \
        printf("\n" COLOR_BLUE "===================" COLOR_RESET "\n");                                                \
        printf("Tests: %d run, " COLOR_GREEN "%d passed" COLOR_RESET ", ", tests_run, tests_passed);                   \
        if (tests_failed > 0) {                                                                                        \
            printf(COLOR_RED "%d failed" COLOR_RESET "\n", tests_failed);                                              \
        } else {                                                                                                       \
            printf("%d failed\n", tests_failed);                                                                       \
        }                                                                                                              \
        printf("Assertions: %d passed, %d failed\n", assertions_passed, assertions_failed);                            \
        printf(COLOR_BLUE "===================" COLOR_RESET "\n");                                                     \
    } while (0)

// Exécuter un test
#define RUN_TEST(test_func)                                                                                            \
    do {                                                                                                               \
        int before_failed = assertions_failed;                                                                         \
        printf("\n" COLOR_YELLOW "[RUN]" COLOR_RESET " %s\n", #test_func);                                             \
        tests_run++;                                                                                                   \
        test_func();                                                                                                   \
        if (assertions_failed == before_failed) {                                                                      \
            printf(COLOR_GREEN "[PASS]" COLOR_RESET " %s\n", #test_func);                                              \
            tests_passed++;                                                                                            \
        } else {                                                                                                       \
            printf(COLOR_RED "[FAIL]" COLOR_RESET " %s\n", #test_func);                                                \
            tests_failed++;                                                                                            \
        }                                                                                                              \
    } while (0)

// Assertions
#define ASSERT_TRUE(condition)                                                                                         \
    do {                                                                                                               \
        if (condition) {                                                                                               \
            printf("  " COLOR_GREEN "✓" COLOR_RESET " %s\n", #condition);                                              \
            assertions_passed++;                                                                                       \
        } else {                                                                                                       \
            printf("  " COLOR_RED "✗ %s" COLOR_RESET " (%s:%d)\n", #condition, __FILE__, __LINE__);                    \
            assertions_failed++;                                                                                       \
        }                                                                                                              \
    } while (0)

#define ASSERT_FALSE(condition)                                                                                        \
    do {                                                                                                               \
        if (!(condition)) {                                                                                            \
            printf("  " COLOR_GREEN "✓" COLOR_RESET " !(%s)\n", #condition);                                           \
            assertions_passed++;                                                                                       \
        } else {                                                                                                       \
            printf("  " COLOR_RED "✗ !(%s)" COLOR_RESET " (%s:%d)\n", #condition, __FILE__, __LINE__);                 \
            assertions_failed++;                                                                                       \
        }                                                                                                              \
    } while (0)

#define ASSERT_EQ(actual, expected)                                                                                    \
    do {                                                                                                               \
        if ((actual) == (expected)) {                                                                                  \
            printf("  " COLOR_GREEN "✓" COLOR_RESET " %s == %s\n", #actual, #expected);                                \
            assertions_passed++;                                                                                       \
        } else {                                                                                                       \
            printf("  " COLOR_RED "✗ %s == %s" COLOR_RESET " (expected %ld, got %ld) (%s:%d)\n", #actual, #expected,   \
                   (long)(expected), (long)(actual), __FILE__, __LINE__);                                              \
            assertions_failed++;                                                                                       \
        }                                                                                                              \
    } while (0)

#define ASSERT_NEQ(actual, expected)                                                                                   \
    do {                                                                                                               \
        if ((actual) != (expected)) {                                                                                  \
            printf("  " COLOR_GREEN "✓" COLOR_RESET " %s != %s\n", #actual, #expected);                                \
            assertions_passed++;                                                                                       \
        } else {                                                                                                       \
            printf("  " COLOR_RED "✗ %s != %s" COLOR_RESET " (both are %ld) (%s:%d)\n", #actual, #expected,            \
                   (long)(actual), __FILE__, __LINE__);                                                                \
            assertions_failed++;                                                                                       \
        }                                                                                                              \
    } while (0)

#define ASSERT_NULL(ptr)                                                                                               \
    do {                                                                                                               \
        if ((ptr) == NULL) {                                                                                           \
            printf("  " COLOR_GREEN "✓" COLOR_RESET " %s is NULL\n", #ptr);                                            \
            assertions_passed++;                                                                                       \
        } else {                                                                                                       \
            printf("  " COLOR_RED "✗ %s is NULL" COLOR_RESET " (got %p) (%s:%d)\n", #ptr, (void*)(ptr), __FILE__,      \
                   __LINE__);                                                                                          \
            assertions_failed++;                                                                                       \
        }                                                                                                              \
    } while (0)

#define ASSERT_NOT_NULL(ptr)                                                                                           \
    do {                                                                                                               \
        if ((ptr) != NULL) {                                                                                           \
            printf("  " COLOR_GREEN "✓" COLOR_RESET " %s is not NULL\n", #ptr);                                        \
            assertions_passed++;                                                                                       \
        } else {                                                                                                       \
            printf("  " COLOR_RED "✗ %s is not NULL" COLOR_RESET " (%s:%d)\n", #ptr, __FILE__, __LINE__);              \
            assertions_failed++;                                                                                       \
        }                                                                                                              \
    } while (0)

#define ASSERT_STR_EQ(actual, expected)                                                                                \
    do {                                                                                                               \
        if (strcmp((actual), (expected)) == 0) {                                                                       \
            printf("  " COLOR_GREEN "✓" COLOR_RESET " %s == %s\n", #actual, #expected);                                \
            assertions_passed++;                                                                                       \
        } else {                                                                                                       \
            printf("  " COLOR_RED "✗ %s == %s" COLOR_RESET " (expected \"%s\", got \"%s\") (%s:%d)\n", #actual,        \
                   #expected, (expected), (actual), __FILE__, __LINE__);                                               \
            assertions_failed++;                                                                                       \
        }                                                                                                              \
    } while (0)

#endif // TEST_FRAMEWORK_H
