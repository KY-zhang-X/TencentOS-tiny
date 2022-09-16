#include "py/mpconfig.h"
#include "py/mphal.h"
#include "py/runtime.h"

#include "modmachine.h"
#include "mphaluart.h"

#if !(MP_GEN_HDR)
#include "tos_k.h"
#if MICROPY_PY_NETWORK
#include "tos_at.h"
#endif
#endif

/************************** UART *******************************/

#define UART_NUM 4

#define UART(u_port) \
    machine_uart_obj_t machine_uart_##u_port##_obj = { \
        {&machine_uart_type}, \
        .port = HAL_UART_PORT_##u_port, \
        .rx_fifo_buf = NULL, \
        .at_agent = NULL, \
        .init = 0, \
    }

UART(0); UART(1); UART(2); UART(3);

static machine_uart_obj_t *machine_uart_obj_all[UART_NUM] = {
    &machine_uart_0_obj,
    &machine_uart_1_obj,
    &machine_uart_2_obj,
    &machine_uart_3_obj,
};

machine_uart_obj_t *machine_uart_find(mp_obj_t user_obj) {
    machine_uart_obj_t *uart = NULL;
    if (mp_obj_is_int(user_obj)) {
        mp_uint_t uart_id = mp_obj_get_int(user_obj);
        if (uart_id < UART_NUM)
            uart = machine_uart_obj_all[uart_id];
    }
    return uart;
}

void machine_uart_rx_start(machine_uart_obj_t *self) {
    if (self->rx_fifo_buf || self->at_agent) {
        HAL_UART_Receive_IT((UART_HandleTypeDef*)self->uart.private_uart, &self->rx_char_buf, 1);
    }
}

static void uart_irq_handler(uint32_t uart_id) {
    machine_uart_obj_t *self = machine_uart_obj_all[uart_id];
    if (self == NULL || !self->init) {
        return;
    }
    
    machine_uart_rx_start(self);

    #if MICROPY_PY_NETWORK
    // if UART is used as at agent
    if (self->at_agent) {
        tos_at_uart_input_byte(self->at_agent, self->rx_char_buf);
        return;
    }
    #endif

    if (self->rx_fifo_buf) {
        tos_chr_fifo_push(&self->rx_fifo, self->rx_char_buf);
        tos_sem_post(&self->rx_sem);
    }
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
    if (huart->Instance == LPUART1) {
        uart_irq_handler(0);
    } else if (huart->Instance == USART1) {
        uart_irq_handler(1); 
    } else if (huart->Instance == USART2) {
        uart_irq_handler(2);
    } else if (huart->Instance == USART3) {
        uart_irq_handler(3);
    }
}

void mp_hal_uart_rx_start(uint32_t uart_id) {
    machine_uart_obj_t *self = machine_uart_obj_all[uart_id];
    if (self == NULL || !self->init) {
        return;
    }
    machine_uart_rx_start(self);
}
