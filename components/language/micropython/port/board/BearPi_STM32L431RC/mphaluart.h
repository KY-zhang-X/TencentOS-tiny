#ifndef _MPHALUART_H_
#define _MPHALUART_H_

#include "py/obj.h"

#if !(MP_GEN_HDR)
#include "tos_k.h"
#include "tos_hal_uart.h"
#include "tos_at.h"
#endif

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
    at_agent_t *at_agent;
    uint8_t init : 1;
} machine_uart_obj_t;

machine_uart_obj_t *machine_uart_find(mp_obj_t user_obj);
void machine_uart_rx_start(machine_uart_obj_t *self);

#endif /* _MPHALUART_H_ */

