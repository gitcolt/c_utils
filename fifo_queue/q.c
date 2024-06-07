#include "q.h"

#include <malloc.h>
#include <memory.h>

void q_init(Q *q) {
    q->head = NULL;
    q->tail = NULL;
}

void q_enqueue(Q *q, void *val) {
    QNode *new_node = malloc(sizeof(*new_node));
    new_node->val = malloc(sizeof(void *));
    memcpy(&new_node->val, &val, sizeof(void *));
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
    void *res = tmp->val;
    q->head = q->head->next;
    free(tmp);
    if (!q->head)
        q->tail = NULL;
    return res;
}
