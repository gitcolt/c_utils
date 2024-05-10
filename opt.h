/*
 * Example usage:
 *
 * #include "opt.h"
 * #include <stdlib.h>
 * 
 * typedef struct {
 *     int x;
 *     int y;
 * } Point;
 * OPT_DECL(Point);
 * 
 * OPT_T(Point) get_rand_point() {
 *     int x_val = rand() % 10 - 1;
 *     int y_val = rand() % 10 - 1;
 *     return (OPT_T(Point)){
 *         .present = (x_val >= 0 && y_val >= 0),
 *         .val.x = x_val,
 *         .val.y = y_val,
 *     };
 * }
 * 
 * int main() {
 *     srand(0);
 * 
 *     Point p; 
 *     for (int i = 0; i < 10; ++i) {
 *         if (OPT_GET(get_rand_point(), p))
 *             printf("p: (%d, %d)\n", p.x, p.y);
 *         else
 *             printf("p: Not present\n");
 *     }
 * }
 */

#ifndef OPT_H
#define OPT_H

#include <stdio.h>

#define OPT_T(type) \
    Opt_##type

#define OPT_DECL(type) \
    typedef struct { \
        type val; \
        int present; \
    } OPT_T(type)

#define OPT_SET(instance, v) \
    instance.val = v

#define OPT_GET(instance, out) \
    (instance.present ? ((out = instance.val), 1) : 0)

#endif
