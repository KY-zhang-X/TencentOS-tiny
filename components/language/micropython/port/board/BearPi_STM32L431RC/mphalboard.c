
#include "py/mpconfig.h"
#include "py/mphal.h"
#include "py/obj.h"
#include "py/runtime.h"

#include "modmachine.h"

#if !(MP_GEN_HDR)
#include "tos_k.h"
#include "main.h"
#endif

static uint32_t systick_get_us() {
    // get systick value
    uint32_t counter = SysTick->VAL;
    uint32_t load = SysTick->LOAD;

    // convert from decrementing to incrementing
    counter = load - counter;

    return (counter * 1000) / (load + 1);
}

mp_uint_t mp_hal_ticks_us(void) {
    uint32_t ms = tos_tick2millisec(tos_systick_get());
    uint32_t us = systick_get_us();
    return ms * 1000 + us;
}

void mp_hal_delay_us(mp_uint_t usec) {
    mp_uint_t ms = usec / 1000;
    mp_uint_t us = usec % 1000;
    if (ms > 0)
        tos_task_delay(tos_millisec2tick(ms));
    mp_uint_t start = mp_hal_ticks_us();
    while (mp_hal_ticks_us() - start < us) {
    }
}
