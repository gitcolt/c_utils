#include "dyn_arr.h"

#include <malloc.h>

void *arr_init(size_t item_size, size_t capacity) {
    void *ptr = NULL;
    size_t size = item_size * capacity + sizeof(ArrHeader);
    ArrHeader *h = malloc(size);
    if (h) {
        h->cap = capacity;
        h->len = 0;
        ptr = h + 1;
    }
    return ptr;
}

void *arr_ensure_capacity(void *a, size_t item_count, size_t item_size) {
    ArrHeader *h = ARR_HEADER(a);
    if (h->cap < item_count) {
        h = realloc(h, sizeof(ArrHeader) + item_size * item_count);
        h->cap = item_count;
    }
    if (h)
        ++h;
    return h;
}

void *arr_clear(void *arr) {
    ArrHeader *h = ARR_HEADER(arr);
    h = realloc(h, sizeof(ArrHeader));
    h->len = 0;
    h->cap = 0;

    return h + 1;
}

void arr_free(void *arr) {
    free(ARR_HEADER(arr));
}
