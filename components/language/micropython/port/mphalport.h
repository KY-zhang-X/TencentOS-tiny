
#define mp_hal_stdio_poll(poll_flags) (0) // NOT IMPLEMENT
static inline void mp_hal_set_interrupt_char(char c) {}

#include "mphalboard.h"
#include "py/obj.h"

#ifndef MP_HAL_IS_PIN_MODE
#define MP_HAL_IS_PIN_MODE(MODE) (((MODE) == MP_HAL_PIN_MODE_INPUT) || \
    ((MODE) == MP_HAL_PIN_MODE_OUTPUT) || \
    ((MODE) == MP_HAL_PIN_MODE_OPEN_DRAIN) || \
    ((MODE) == MP_HAL_PIN_MODE_ALT) || \
    ((MODE) == MP_HAL_PIN_MODE_ALT_OPEN_DRAIN) || \
    ((MODE) == MP_HAL_PIN_MODE_ANALOG))
#endif

#ifndef MP_HAL_IS_PIN_PULL
#define MP_HAL_IS_PIN_PULL(PULL) (((PULL) == MP_HAL_PIN_PULL_NONE) || \
    ((PULL) == MP_HAL_PIN_PULL_UP) || \
    ((PULL) == MP_HAL_PIN_PULL_DOWN))
#endif

#define mp_hal_pin_obj_t const machine_pin_obj_t *
int mp_hal_pin_read(mp_hal_pin_obj_t pin);
void mp_hal_pin_write(mp_hal_pin_obj_t pin, int v);
void mp_hal_pin_config(mp_hal_pin_obj_t pin, uint32_t mode, uint32_t pull, uint32_t alt);
void mp_hal_gpio_clock_enable(mp_hal_pin_obj_t pin);
void mp_hal_extint_register_pin(mp_hal_pin_obj_t pin, uint32_t mode, mp_obj_t callback_obj);
mp_hal_pin_obj_t mp_hal_pin_find(mp_obj_t name);
void mp_hal_pin_print(const mp_print_t *print, mp_hal_pin_obj_t pin);

#define mp_hal_pin_high(pin)    mp_hal_pin_write(pin, 1)
#define mp_hal_pin_low(pin)     mp_hal_pin_write(pin, 0)
