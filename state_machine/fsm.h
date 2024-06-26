#ifndef FSM_H
#define FSM_H

#include <stddef.h>

#define MAX_STATES 10
#define MAX_TRANSITIONS_PER_STATE 3

typedef struct {
    int event;
    int target_state_id;
} Transition;

typedef struct {
    int event;
    size_t target_state_idx;
} _Transition;

typedef struct {
    int id;
    Transition transitions[MAX_TRANSITIONS_PER_STATE];
    size_t transitions_sz;
    void (*on_exit)(void *ctx);
    void (*on_entry)(void *ctx);
} State;

typedef struct {
    int id;
    int idx;
    _Transition transitions[MAX_TRANSITIONS_PER_STATE];
    size_t transitions_sz;
    void (*on_exit)(void *ctx);
    void (*on_entry)(void *ctx);
} _State;

typedef struct {
    _State states[MAX_STATES];
    size_t states_sz;
    _State *curr_state;
    void *ctx;
} FSM;

void fsm_init(FSM *fsm, State *states, size_t states_sz, int initial_state_id);
void fsm_event(FSM *fsm, int ev);

#endif
