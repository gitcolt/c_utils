#include "q.h"

#include <malloc.h>
#include <memory.h>

Q *q_create() {
    Q *q = malloc(sizeof(*q));
    q->head = NULL;
    q->tail = NULL;
    return q;
}

void q_enqueue(Q *q, void *val) {
    QNode *new_node = malloc(sizeof(*new_node));
    new_node->val = val;
    memcpy(&new_node->val, &val, sizeof(void *));
    new_node->next = NULL;

    if (!q->head) {
        q->head = new_node;
        q->tail = q->head;
    } else {
        q->tail->next = new_node;
        q->tail = q->tail->next;
    }
}

void *q_dequeue(Q *q) {
    if (!q->head)
        return NULL;
    QNode *tmp = q->head;
    void *res = tmp->val;
    q->head = q->head->next;
    free(tmp);
    if (!q->head)
        q->tail = NULL;
    return res;
}

void *q_peek(Q *q) {
    if (!q->head)
        return NULL;
    return q->head->val;
}

void *q_peek_tail(Q *q) {
    if (!q->tail)
        return NULL;
    return q->tail->val;
}

void q_destroy(Q *q) {
    QNode *curr = q->head;
    while (curr) {
        QNode *next = curr->next;
        free(curr);
        curr = next;
    }
    free(q);
}
