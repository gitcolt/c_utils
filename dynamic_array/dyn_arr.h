/*
 * Example usage:
 * 
 * float *arr = ARR(float, 10);
 * ARR_APPEND(arr, 12.34);
 * ARR_APPEND(arr, 56.78);
 * for (int i = 0; i < ARR_LEN(arr); ++i) {
 *      printf("arr[%d]: %.2f\n", i, arr[i]);
 * }
 * arr_free(arr);
 */

#ifndef DYN_ARR_H
#define DYN_ARR_H

#include <stddef.h>

typedef struct {
    size_t len;
    size_t cap;
} ArrHeader;

#define ARR_HEADER(a) ((ArrHeader *)(a) - 1)
#define ARR_LEN(a) (ARR_HEADER(a)->len)
#define ARR_CAPACITY(a) (ARR_HEADER(a)->cap)

void *arr_init(size_t item_size, size_t capacity);

#define ARR(T, initial_capacity) \
    (T *)arr_init(sizeof(T), initial_capacity)

void *arr_ensure_capacity(void *arr, size_t item_count, size_t item_size);

#define ARR_APPEND(arr, v) ( \
    (arr) = arr_ensure_capacity(arr, ARR_LEN(arr) + 1, sizeof(v)), \
    (arr)[ARR_HEADER(arr)->len] = (v), \
    &(arr)[ARR_HEADER(arr)->len++] )

void *arr_clear(void *arr);

void arr_free(void *arr);

#endif
