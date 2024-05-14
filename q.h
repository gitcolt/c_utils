/*
 * Example usage:
 *
 * #define Q_IMPL
 * #include "q.h"
 * 
 * typedef struct { int x; int y; } Foo;
 * 
 * int main() {
 *     Q q;
 *     q_init(&q, Foo *);
 *     Foo a = { .x = 111, .y = 222 };
 *     Foo b = { .x = 333, .y = 444 };
 *     q_enqueue(&q, &a);
 *     q_enqueue(&q, &b);
 * 
 *     while (!q_empty(&q)) {
 *         Foo *foo = q_dequeue(&q);
 *         printf("foo->x: %d\n", foo->x);
 *     }
 * }
 */

#include <stdint.h>
#include <stddef.h>

typedef struct QNode {
    uint8_t *val;
    struct QNode *next;
} QNode;

typedef struct {
    QNode *head;
    QNode *tail;
    size_t data_type_size;
} Q;

#define q_init(q_ptr, type) \
    do { \
        (q_ptr)->head = NULL; \
        (q_ptr)->tail = NULL; \
        (q_ptr)->data_type_size = sizeof(type); \
    } while (0)

void q_enqueue(Q *q, void *val);

void *q_dequeue(Q *q);

#define q_empty(q_ptr) !(q_ptr)->head

#ifdef Q_IMPL

#include <malloc.h>
#include <memory.h>

void q_enqueue(Q *q, void *val) {
    QNode *new_node = malloc(sizeof(*new_node));
    new_node->val = malloc(q->data_type_size);
    memcpy(new_node->val, val, q->data_type_size);
    new_node->next = NULL;

    if (!q->head) {
        q->head = new_node;
        q->tail = q->head;
        return;
    }
    q->tail->next = new_node;
    q->tail = q->tail->next;
}

void *q_dequeue(Q *q) {
    if (!q->head)
        return NULL;

    QNode *tmp = q->head;
    uint8_t *res = tmp->val;
    q->head = q->head->next;
    free(tmp);
    if (!q->head)
        q->tail = NULL;
    return res;
}

#endif // end implementation
