/*
 * Example usage:
 *
 * TEST(test_foo) {
 *     bool res = func_under_test();
 *     TEST_ASSERT(res);
 * }
 * 
 * TEST_SUITE(suite) {
 *     RUN_TEST(test_foo);
 * }
 * 
 * int main() {
 *     RUN_SUITE(suite);
 * }
 */

#ifndef TEST_H
#define TEST_H

#include "../ansi_colors/ansi_colors.h"

#include <stdbool.h>
#include <string.h>
#include <stdio.h>

enum TestStatus {
    TEST_STATUS_SUCCESS = 0,
    TEST_STATUS_FAILURE = 1,
};

typedef struct {
    const char *test_name;
    int line_num;
} FailedTestSummary;

static int num_failed_tests = 0;
static enum TestStatus test_status;

#define FAILED_TESTS_MAX 99
static FailedTestSummary failed_tests[FAILED_TESTS_MAX];

#define _TEST_FAIL() \
    do { \
        failed_tests[num_failed_tests].line_num = __LINE__; \
        failed_tests[num_failed_tests].test_name = __func__; \
        ++num_failed_tests; \
    } while (0)

#define TEST_ASSERT(predicate) \
    do { \
        if (!predicate) { \
            test_status = TEST_STATUS_FAILURE; \
            _TEST_FAIL(); \
        } \
    } while (0)

#define TEST_ASSERT_INT_EQ(expected, actual) \
    do { \
        if (expected != actual) { \
            test_status = TEST_STATUS_FAILURE; \
            _TEST_FAIL(); \
        } \
    } while (0)

#define TEST_EPSILON 0.001
#define TEST_ASSERT_DOUBLE_EQ(expected, actual) \
    do { \
        if (expected - actual > TEST_EPSILON) { \
            test_status = TEST_STATUS_FAILURE; \
            _TEST_FAIL(); \
        } \
    } while (0)

#define TEST(name) static void name(void)
#define TEST_SUITE(name) static void name(void)

#define RUN_SUITE(name) \
    do { \
        name(); \
        printf("\n"); \
        if (num_failed_tests) { \
            printf("\nfailed tests:\n"); \
            for (int i = 0; i < num_failed_tests; ++i) { \
                printf(RED_TXT "%s (%s: %d)\n" RST_COL, \
                       failed_tests[i].test_name, \
                       __FILE__, \
                       failed_tests[i].line_num); \
            } \
        } else { \
            printf(GRN_TXT "all tests passing\n" RST_COL); \
        } \
    } while (0)

#define RUN_TEST(name) \
    do { \
        test_status = TEST_STATUS_SUCCESS; \
        name(); \
        if (test_status == TEST_STATUS_FAILURE) { \
            printf(RED_TXT "X" RST_COL); \
        } else { \
            printf(GRN_TXT "." RST_COL); \
        } \
    } while (0)

#endif
