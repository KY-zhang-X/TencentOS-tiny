
#include "py/mpconfig.h"
#include "py/mpthread.h"
#include "tos_k.h"

#if MICROPY_PY_THREAD

// this structure form a linked list, one node per active thread
typedef struct _mp_thread_t {
    k_task_t *id;
    int ready;
    void *arg;
    void *stack;
    size_t stack_len;
    struct _mp_thread_t *next;
} mp_thread_t;

// the mutex controls access to the linked list
STATIC mp_thread_mutex_t thread_mutex;
STATIC mp_thread_t thread_entry0;
STATIC mp_thread_t *thread = NULL;

void mp_thread_init(void *stack, uint32_t stack_len)
{
    mp_thread_mutex_init(&thread_mutex);
    mp_thread_set_state(&mp_state_ctx.thread);

    // create first entry in linked list of all threads
    thread = &thread_entry0;
    thread->id = tos_task_curr_task_get();
    thread->ready = 1;
    thread->arg = NULL;
    thread->stack = stack;
    thread->stack_len = stack_len;
    thread->next = NULL;
}

void mp_thread_gc_others(void)
{
    mp_thread_mutex_lock(&thread_mutex, 1);
    for (mp_thread_t *th = thread; th != NULL; th = th->next) {
        gc_collect_root((void **)&th, 1);
        gc_collect_root(&th->arg, 1);
        gc_collect_root(&th->stack, 1);
        if (th->id != tos_task_curr_task_get() && th->ready) {
            gc_collect_root(th->stack, th->stack_len);
        }
    }
    mp_thread_mutex_unlock(&thread_mutex);
}

void mp_thread_deinit(void)
{
    for (;;) {
        k_task_t *id = NULL;
        mp_thread_mutex_lock(&thread_mutex, 1);
        for (mp_thread_t *th = thread; th != NULL; th = th->next) {
            if (th->id != tos_task_curr_task_get()) {
                id = th->id;
                break;
            }
        }
        mp_thread_mutex_unlock(&thread_mutex);
        if (id == NULL) {
            break;
        } else {
            tos_task_destroy(id);
        }
    }
}

void mp_thread_set_state(mp_state_thread_t *state)
{
    // TODO task local storage
}

mp_state_thread_t *mp_thread_get_state(void)
{
    // TODO task local storage
}


void mp_thread_create(void *(*entry)(void *), void *arg, size_t *stack_size)
{
    // TODO
}
void mp_thread_start(void)
{
    mp_thread_mutex_lock(&thread_mutex, 1);
    for (mp_thread_t *th = thread; th != NULL; th = th->next) {
        if (th->id == tos_task_curr_task_get()) {
            th->ready = 1;
            break;
        }
    }
    mp_thread_mutex_unlock(&thread_mutex);
}
void mp_thread_finish(void)
{
    mp_thread_mutex_lock(&thread_mutex, 1);
    for (mp_thread_t *th = thread; th != NULL; th = th->next) {
        if (th->id == tos_task_curr_task_get()) {
            th->ready = 0;
            break;
        }
    }
    mp_thread_mutex_unlock(&thread_mutex);
}


void mp_thread_mutex_init(mp_thread_mutex_t *mutex)
{
    // TODO
}

int mp_thread_mutex_lock(mp_thread_mutex_t *mutex, int wait)
{
    return K_ERR_NONE == tos_mutex_pend_timed(mutex->mutex, wait ? TOS_TIME_FOREVER : TOS_TIME_NOWAIT);
}

void mp_thread_mutex_unlock(mp_thread_mutex_t *mutex) 
{
    tos_mutex_post(mutex->mutex);
}

#endif /* MICROPY_PY_THREAD */
