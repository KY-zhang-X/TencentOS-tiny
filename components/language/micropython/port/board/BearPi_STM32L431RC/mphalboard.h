#ifndef _MPHALBOARD_H_
#define _MPHALBOARD_H_

#if !(MP_GEN_HDR)
#include "main.h"
#include "tos_k.h"
#include "tos_hal_uart.h"
#endif
#include "py/obj.h"

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

#define IRQ_PRI_SYSTICK         0
#define IRQ_PRI_UART            1
#define IRQ_PRI_SDIO            1
#define IRQ_PRI_DMA             1
#define IRQ_PRI_FLASH           2
#define IRQ_PRI_OTG_FS          2
#define IRQ_PRI_OTG_HS          2
#define IRQ_PRI_TIM5            2
#define IRQ_PRI_CAN             2
#define IRQ_PRI_TIMX            2
#define IRQ_PRI_EXTINT          2
#define IRQ_PRI_PENDSV          3
#define IRQ_PRI_RTC_WKUP        3

typedef struct _machine_uart_obj_t {
    mp_obj_base_t base;
    hal_uart_port_t port;
    hal_uart_t uart;
    uint8_t rx_char_buf;
    k_sem_t rx_sem;
    k_chr_fifo_t rx_fifo;
    uint8_t *rx_fifo_buf;
    uint16_t rx_fifo_buf_len;
    uint16_t timeout;           // timeout waiting for first char
    uint16_t timeout_char;      // timeout waiting between chars
    uint8_t init : 1;
} machine_uart_obj_t;

#endif /* _MPHALBOARD_H_ */
