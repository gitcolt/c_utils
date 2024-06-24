/*
 * Example usage:
 *
 * typedef struct { int x; int y; } Point;
 * 
 * int main() {
 *     Q *q = q_init();
 *     Point a = { .x = 111, .y = 222 };
 *     Point b = { .x = 333, .y = 444 };
 *     q_enqueue(q, &a);
 *     q_enqueue(q, &b);
 * 
 *     while (!q_empty(q)) {
 *         Point *point = q_dequeue(q);
 *         printf("(%d, %d)\n", point->x, point->y);
 *     }
 *     q_destroy(q);
 * }
 */

#ifndef Q_H
#define Q_H

#include <stdint.h>
#include <stddef.h>

typedef struct QNode {
    void *val;
    struct QNode *next;
} QNode;

typedef struct {
    QNode *head;
    QNode *tail;
} Q;

Q *q_create();
void q_enqueue(Q *q, void *val);
void *q_dequeue(Q *q);
void *q_peek(Q *q);
void *q_peek_tail(Q *q);
void q_destroy(Q *q);
#define q_empty(q_ptr) !(q_ptr)->head

#endif
