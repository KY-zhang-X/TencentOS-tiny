#ifndef _MPTHREADPORT_H_
#define _MPTHREADPORT_H_

#if !(MP_GEN_HDR)
#include "tos_k.h"
#else
struct k_mutex_st;
typedef struct k_mutex_st k_mutex_t;
#endif

#define MP_THREAD_STACK_LIMIT_MARGIN                    (1024)

// typedef struct _mp_thread_mutex_t {
//     k_mutex_t mutex;
// } mp_thread_mutex_t;
typedef k_mutex_t mp_thread_mutex_t;

void mp_thread_init(void);
void mp_thread_gc_others(void);
void mp_thread_deinit(void);

#endif /* _MPTHREAD_PORT_H_ */
