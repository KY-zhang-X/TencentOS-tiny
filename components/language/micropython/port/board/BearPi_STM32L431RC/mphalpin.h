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
} machine_pin_obj_t;

#define mp_hal_pin_obj_t const machine_pin_obj_t *

#endif /* _MPHALPIN_H_ */
