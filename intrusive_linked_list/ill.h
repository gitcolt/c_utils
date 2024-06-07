/*
 * Example usage:
 *
 * typedef struct {
 *      int val;
 *      ILLNode list_node;
 * } Foo;
 *
 * int main() {
 *      Foo foo_a = { .val = 1 };
 *      Foo foo_b = { .val = 2 };
 *      Foo foo_c = { .val = 3 };
 *
 *      ILLNode head = ILL_HEAD_INIT(head);
 *      ill_link_tail(&head, &foo_a.list_node);
 *      ill_link_tail(&head, &foo_b.list_node);
 *      ill_link_tail(&head, &foo_c.list_node);
 *
 *      Foo *curr;
 *      ill_for_each(curr, &head, list_node) {
 *          int val = curr->val;
 *          // ...
 *      }
 * }
 */

#ifndef ILL_H
#define ILL_H

#include <stddef.h>

#define ILL_HEAD_INIT(name) { &(name), &(name) }

#define container_of(ptr, type, member_name) ({ \
        void *member_ptr = (void *)(ptr); \
        ((type *)(member_ptr - offsetof(type, member_name))); })

#define node_container(node_ptr, container_type, node_member_name) \
    container_of(node_ptr, container_type, node_member_name)

#define ill_for_each(container_iter, head, member) \
    for (container_iter = node_container((head)->next, typeof(*container_iter), member); \
            &container_iter->member != (head); \
            container_iter = node_container(container_iter->member.next, \
                                            typeof(*container_iter), member))

#define ill_for_each_node(node_iter, head) \
    for (node_iter = (head)->next; node_iter != (head); node_iter = node_iter->next)

typedef struct ILLNode {
    struct ILLNode *next, *prev;
} ILLNode;

static inline void __ill_node_splice(ILLNode *new_node, ILLNode *prev, ILLNode *next) {
    next->prev = new_node;
    new_node->next = next;
    new_node->prev = prev;
    prev->next = new_node;
}

static inline void ill_add_before_node(ILLNode *node, ILLNode *new_node) {
    ILLNode *prev = node->prev;
    ILLNode *next = node;
    __ill_node_splice(new_node, prev, next);
}

static inline void ill_link_tail(ILLNode *head, ILLNode *new_node) {
    ill_add_before_node(head, new_node);
}

static inline void ill_link_head(ILLNode *head, ILLNode *new_node) {
    __ill_node_splice(new_node, head, head->next);
}

#endif
