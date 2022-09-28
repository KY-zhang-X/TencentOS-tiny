
#define mp_hal_stdio_poll(poll_flags) (0) // NOT IMPLEMENT

#include "mphalboard.h"
#include "py/obj.h"
#include "shared/runtime/interrupt_char.h"

#if !(MP_GEN_HDR)
#include "tos_k.h"
#include "mp_tos_hal_pin.h"
#endif

#define MP_HAL_IS_PIN_MODE(mode) \
   (((mode) == HAL_PIN_MODE_OUTPUT) || \
    ((mode) == HAL_PIN_MODE_OUTPUT_OD) || \
    ((mode) == HAL_PIN_MODE_INPUT) || \
    ((mode) == HAL_PIN_MODE_INPUT_PULLUP) || \
    ((mode) == HAL_PIN_MODE_INPUT_PULLDOWN))

struct _machine_pin_obj_t;
#define MP_HAL_PIN_FMT "%q"
#define mp_hal_pin_obj_t struct _machine_pin_obj_t *
void mp_hal_pin_write(mp_hal_pin_obj_t pin, int v);
int mp_hal_pin_read(mp_hal_pin_obj_t pin);
void mp_hal_pin_config(mp_hal_pin_obj_t pin, uint32_t mode);

#define mp_hal_pin_high(pin)        mp_hal_pin_write((pin), 1)
#define mp_hal_pin_low(pin)         mp_hal_pin_write((pin), 0)
#define mp_hal_pin_od_high(pin)     mp_hal_pin_high(pin)
#define mp_hal_pin_od_low(pin)      mp_hal_pin_low(pin)
#define mp_hal_pin_input(pin)       mp_hal_pin_config((pin), HAL_PIN_MODE_INPUT)
#define mp_hal_pin_output(pin)      mp_hal_pin_config((pin), HAL_PIN_MODE_OUTPUT)
#define mp_hal_pin_open_drain(pin)  mp_hal_pin_config((pin), HAL_PIN_MODE_OUTPUT_OD)

#define mp_hal_delay_us_fast(us)    mp_hal_delay_us(us)
