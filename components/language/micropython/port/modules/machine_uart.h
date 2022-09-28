#ifndef _MACHINE_UART_H_
#define _MACHINE_UART_H_

#include "py/obj.h"

#ifndef MP_GEN_HDR
#include "tos_k.h"
#include "tos_hal.h"
#include "tos_at.h"
#endif

extern const mp_obj_type_t machine_uart_type;

typedef struct _machine_uart_obj_t machine_uart_obj_t;

/* board */
void mp_hal_uart_rx_start(uint32_t uart_id);
void mp_hal_uart_irq_handler(uint32_t uart_id);

/* repl */
int machine_uart_rx_chr(machine_uart_obj_t *self);
int machine_uart_tx_strn(machine_uart_obj_t *self, const char *str, mp_uint_t len);
void machine_uart_rx_start(machine_uart_obj_t *self);
void machine_uart_attach_to_repl(machine_uart_obj_t *self, uint8_t attached);

/* esp8266 */
void machine_uart_set_at_agent(machine_uart_obj_t *self, at_agent_t *at_agent);
hal_uart_port_t machine_uart_get_port(machine_uart_obj_t *self);

#endif /* _MACHINE_UART_H_ */
