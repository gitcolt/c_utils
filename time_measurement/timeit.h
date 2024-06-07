#ifndef TIMEIT_H
#define TIMEIT_H

#include <time.h>

#define TIMEIT_BEGIN \
    clock_t timeit_start = clock();

#define TIMEIT_END \
    clock_t timeit_end = clock(); \
    double TIMEIT_ELAPSED_MS = \
        ((double)(timeit_end - timeit_start) * 1000) / CLOCKS_PER_SEC; \

#endif
