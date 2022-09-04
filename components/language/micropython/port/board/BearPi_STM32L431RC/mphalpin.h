#ifndef _MPHALPIN_H_
#define _MPHALPIN_H_

#include "py/obj.h"
#if !(MP_GEN_HDR)
#include "gpio.h"
#endif

#define MP_HAL_PIN_FMT      "%q"
#define MP_HAL_PIN_MODE_INPUT           (GPIO_MODE_INPUT)
#define MP_HAL_PIN_MODE_OUTPUT          (GPIO_MODE_OUTPUT_PP)
#define MP_HAL_PIN_MODE_ALT             (GPIO_MODE_AF_PP)
#define MP_HAL_PIN_MODE_ANALOG          (GPIO_MODE_ANALOG)
// #if defined(GPIO_ASCR_ASC0)
// #define MP_HAL_PIN_MODE_ADC             (11)
// #else
// #define MP_HAL_PIN_MODE_ADC             (3)
// #endif
#define MP_HAL_PIN_MODE_OPEN_DRAIN      (GPIO_MODE_OUTPUT_PP)
#define MP_HAL_PIN_MODE_ALT_OPEN_DRAIN  (GPIO_MODE_AF_OD)

#define MP_HAL_PIN_PULL_NONE            (GPIO_NOPULL)
#define MP_HAL_PIN_PULL_UP              (GPIO_PULLUP)
#define MP_HAL_PIN_PULL_DOWN            (GPIO_PULLDOWN)

#define MP_HAL_PIN_IRQ_RISING           (GPIO_MODE_IT_RISING)
#define MP_HAL_PIN_IRQ_FALLING          (GPIO_MODE_IT_FALLING)

typedef struct  _machine_pin_obj_t {
    mp_obj_base_t base;
    qstr name;
    GPIO_TypeDef *gpio;
    uint32_t pin_no;
    uint32_t pull;
} machine_pin_obj_t;

#define mp_hal_pin_obj_t machine_pin_obj_t *

int mp_hal_pin_read(mp_hal_pin_obj_t pin);
void mp_hal_pin_write(mp_hal_pin_obj_t pin, int v);
void mp_hal_pin_config(mp_hal_pin_obj_t pin, uint32_t mode, uint32_t pull, uint32_t alt);
void mp_hal_gpio_clock_enable(mp_hal_pin_obj_t pin);
mp_hal_pin_obj_t mp_hal_get_pin_obj(mp_obj_t name);
qstr mp_hal_pin_name(mp_hal_pin_obj_t pin);
void mp_hal_pin_print(const mp_print_t *print, mp_hal_pin_obj_t pin);

void mp_hal_extint_config(mp_hal_pin_obj_t pin, uint32_t mode);
void mp_hal_extint_enable(int line);
void mp_hal_extint_disable(int line);


#endif /* _MPHALPIN_H_ */
