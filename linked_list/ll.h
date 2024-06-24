#ifndef LL_H
#define LL_H

#include <stddef.h>
#include <stdbool.h>

typedef struct LLNode {
    void *val;
    struct LLNode *next;
} LLNode;

typedef struct LL {
    struct LLNode *head;
    struct LLNode *tail;
    size_t length;
} LL;

typedef void (*ll_each_func)(void *val);

LL *ll_create();
void ll_destroy(LL *ll);
void ll_append_tail(LL *ll, void *val);
bool ll_insert(LL *ll, LLNode *node_before, void *val);
bool ll_remove(LL *ll, void *val);
void ll_for_each(LL *ll, ll_each_func f);
LLNode *ll_find(LL *ll, void *val);

#endif
