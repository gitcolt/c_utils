#include "ll.h"

#include <malloc.h>

LLNode *ll_node_create(void *val) {
    LLNode *node = malloc(sizeof(*node));
    node->val = val;
    node->next = NULL;
    return node;
}

void ll_node_destroy(LLNode *node) {
    free(node);
}

LL *ll_create() {
    return calloc(1, sizeof(LL));
}

void ll_destroy(LL *ll) {
    LLNode *curr = ll->head;
    while (curr) {
        LLNode *next = curr->next;
        free(curr);
        curr = next;
    }
    free(ll);
}

void ll_append_tail(LL *ll, void *val) {
    if (!ll->head) {
        ll->head = ll_node_create(val);
        ll->tail = ll->head;
        ++ll->length;
        return;
    }

    ll->tail->next = ll_node_create(val);
    ll->tail->next->val = val;
    ll->tail = ll->tail->next;

    ++ll->length;
}

bool ll_insert(LL *ll, LLNode *node_before, void *val) {
    if (!node_before)
        return false;

    LLNode *next = node_before->next;
    LLNode *new_node = ll_node_create(val);
    node_before->next = new_node;
    new_node->next = next;

    ++ll->length;
    return true;
}

bool ll_remove(LL *ll, void *val) {
    LLNode *node_to_remove = ll_find(ll, val);
    if (!node_to_remove)
        return false;
    LLNode *node_after = node_to_remove->next;

    if (node_to_remove == ll->head) {
        ll->head = node_to_remove->next;
        ll_node_destroy(node_to_remove);
        --ll->length;
        return true;
    }

    LLNode *curr = ll->head;

    while (curr) {
        if (curr->next == node_to_remove) {
            curr->next = node_after;
            ll_node_destroy(node_to_remove);
            --ll->length;
            return true;
        }
        curr = curr->next;
    }
    return false;
}

void ll_for_each(LL *ll, ll_each_func f) {
    LLNode *curr = ll->head;
    while (curr) {
        f(curr->val);
        curr = curr->next;
    }
}

LLNode *ll_find(LL *ll, void *val) {
    LLNode *curr = ll->head;
    while (curr) {
        if (curr->val == val)
            return curr;
        curr = curr->next;
    }
    return NULL;
}
