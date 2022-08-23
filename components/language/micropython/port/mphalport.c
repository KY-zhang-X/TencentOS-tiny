#include "py/mpconfig.h"
#include "py/mpthread.h"
#include "py/mphal.h"
#include "tos_k.h"
#include "tos_hal.h"
#include "mpshellport.h"

int mp_hal_stdin_rx_chr(void) 
{
    extern int machine_uart_rx_chr(machine_uart_obj_t *self);
    while (1) {
        // int c = mp_shell_getchar();
        int c = -1;
        machine_uart_obj_t *uart = MP_STATE_PORT(stdio_uart);
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
    extern int machine_uart_tx_strn(machine_uart_obj_t *self, const char *str, mp_uint_t len);
    machine_uart_obj_t *uart = MP_STATE_PORT(stdio_uart);
    machine_uart_tx_strn(uart, str, len);
    // mp_shell_putsn(str, len);
}

void mp_hal_delay_ms(mp_uint_t ms)
{
    tos_task_delay(tos_millisec2tick(ms));
}

void mp_hal_delay_us(mp_uint_t us) 
{
    mp_uint_t ms = us / 1000 + ((us % 1000) > 0 ? 1 : 0);
    tos_task_delay(tos_millisec2tick(ms));
}

mp_uint_t mp_hal_ticks_ms(void)
{
    return tos_tick2millisec(tos_systick_get());
}

mp_uint_t mp_hal_ticks_us(void)
{
    return tos_tick2millisec(tos_systick_get()) * 1000;
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
