#ifndef LIST_HEAD_H
#define LIST_HEAD_H

#include <stddef.h>

typedef struct ListHead {
    struct ListHead *next, *prev;
} ListHead;

#define LIST_HEAD_INIT(name) { &(name), &(name) }

static inline void INIT_LIST_HEAD(ListHead *list) {
    list->next = list;
    list->prev = list;
}

#define LIST_HEAD(name) \
    ListHead name = LIST_HEAD_INIT(name)

static void _list_add(ListHead *lh_new,
                ListHead *lh_prev,
                ListHead *lh_next) {
    lh_next->prev = lh_new;
    lh_new->next = lh_next;
    lh_new->prev = lh_prev;
    lh_prev->next = lh_new;
}

// Insert *AFTER* specified head
static inline void list_add(ListHead *lh_new, ListHead *lh_head) {
    _list_add(lh_new, lh_head, lh_head->next);
}

// Insert *BEFORE* specified head
static inline void list_add_tail(ListHead *lh_new, ListHead *lh_head) {
    _list_add(lh_new, lh_head->prev, lh_head);
}

#define list_for_each(pos, head) \
    for (pos = (head)->next; pos != (head); pos = pos->next)

#define list_entry(ptr, type, member) ({ \
        const typeof( ((type *)0)->member ) *__mptr = (ptr); \
        (type *)( (char *)__mptr - offsetof(type, member) ); })

#define list_for_each_entry(pos, head, member) \
    for (pos = list_entry((head)->next, typeof(*pos), member); \
            &pos->member != (head); \
            pos = list_entry(pos->member.next, typeof(*pos), member))

#endif
