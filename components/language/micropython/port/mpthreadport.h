#ifndef _MPTHREADPORT_H_
#define _MPTHREADPORT_H_

#if !defined(MP_GEN_HDR)
#include "tos_k.h"
#else
struct k_mutex_st;
typedef struct k_mutex_st k_mutex_t;
#endif

typedef struct _mp_thread_mutex_t {
    k_mutex_t *mutex;
} mp_thread_mutex_t;
// typedef k_mutex_t *mp_thread_mutex_t;

void mp_thread_init(void *stack, uint32_t stack_len);
void mp_thread_gc_others(void);
void mp_thread_deinit(void);

#endif /* _MPTHREAD_PORT_H_ */
