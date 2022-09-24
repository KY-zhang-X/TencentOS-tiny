#include "tos_k.h"
#include "mpmain.h"
#include "py/builtin.h"

#define MP_TASK_PRIO        (3)
#define MP_TASK_STACK_SIZE  (4 * 1024)

// MicroPython task stack
__STATIC__ k_stack_t mp_task_stack[MP_TASK_STACK_SIZE];
__STATIC__ k_task_t mp_task;

void mp_entry(void *arg) {
    
    for (;;) {
        mp_main();
        tos_task_delay(100);
    }
}

void application_entry(void *arg) {
    tos_task_create(&mp_task, "micropython", mp_entry,
                        K_NULL, MP_TASK_PRIO, mp_task_stack,
                        MP_TASK_STACK_SIZE, 0);
}
