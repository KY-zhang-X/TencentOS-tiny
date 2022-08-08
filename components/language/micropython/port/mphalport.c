#include "py/mpconfig.h"
#include "py/mpthread.h"
#include "tos_k.h"
#include "tos_hal.h"
#include "mpshellport.h"

int mp_hal_stdin_rx_chr(void) 
{
    while (1) {
        int c = mp_shell_getchar();
        if (c != -1) {
            return c;
        }
        MICROPY_EVENT_POLL_HOOK
    }
}

void mp_hal_stdout_tx_strn(const char *str, mp_uint_t len) 
{
    mp_shell_putsn(str, len);
}

mp_uint_t mp_hal_ticks_ms(void)
{
    return tos_tick2millisec(tos_systick_get());
}

void mp_hal_delay_ms(mp_uint_t ms)
{
    tos_task_delay(tos_millisec2tick(ms));
}
