#include "py/mpconfig.h"
#include "py/mpthread.h"
#include "py/mphal.h"
#include "tos_k.h"
#include "tos_hal.h"
#include "machine_uart.h"
// #include "mpshellport.h"

int mp_hal_stdin_rx_chr(void) 
{
    while (1) {
        // int c = mp_shell_getchar();
        int c = -1;
        struct _machine_uart_obj_t *uart = MP_STATE_PORT(stdio_uart);
        if (uart != NULL) {
            c = machine_uart_rx_chr(uart);
        }
        if (c != -1) {
            return c;
        }
        MICROPY_EVENT_POLL_HOOK
    }
}

void mp_hal_stdout_tx_strn(const char *str, mp_uint_t len) 
{
    struct _machine_uart_obj_t *uart = MP_STATE_PORT(stdio_uart);
    machine_uart_tx_strn(uart, str, len);
    // mp_shell_putsn(str, len);
}

void mp_hal_delay_ms(mp_uint_t ms)
{
    k_tick_t start_tick = tos_systick_get();
    k_tick_t ticks = tos_millisec2tick(ms);
    while (tos_systick_get() < start_tick + ticks) {
        MICROPY_EVENT_POLL_HOOK
        tos_task_delay(1);
    }
}

mp_uint_t mp_hal_ticks_ms(void)
{
    return tos_tick2millisec(tos_systick_get());
}

mp_uint_t mp_hal_ticks_cpu(void)
{
    return tos_systick_get();
}

uint64_t mp_hal_time_ns(void)
{
    // not support
    return 0;
}
