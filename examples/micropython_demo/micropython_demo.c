#include "tos_k.h"
#include "mpshellport.h"
#include "mpmain.h"
#include "py/builtin.h"

#define MP_SHELL_BUF_SIZE   (512)
#define MP_TASK_PRIO        (3)
#define MP_TASK_STACK_SIZE  (2 * 1024)

// MicroPython task stack
__STATIC__ k_stack_t mp_task_stack[MP_TASK_STACK_SIZE];
__STATIC__ k_task_t mp_task;

void mp_entry(void *arg) {
    mp_shell_init(MP_SHELL_BUF_SIZE, HAL_UART_PORT_2);
    for (;;) {
        mp_main();
        mp_printf(&mp_plat_print, "exit mp_main()\n");
        tos_task_delay(100);
    }
}

void application_entry(void *arg) {
    tos_task_create(&mp_task, "micropython", mp_entry,
                        K_NULL, MP_TASK_PRIO, mp_task_stack,
                        MP_TASK_STACK_SIZE, 0);
}
