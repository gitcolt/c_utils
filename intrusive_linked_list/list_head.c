#include "list_head.h"

static inline void _list_add(ListHead *lh_new,
                ListHead *lh_prev,
                ListHead *lh_next) {
    lh_next->prev = lh_new;
    lh_new->next = lh_next;
    lh_new->prev = lh_prev;
    lh_prev->next = lh_new;
}

void list_add(ListHead *lh_new, ListHead *lh_head) {
    _list_add(lh_new, lh_head, lh_head->next);
}

void list_add_tail(ListHead *lh_new, ListHead *lh_head) {
    _list_add(lh_new, lh_head->prev, lh_head);
}
