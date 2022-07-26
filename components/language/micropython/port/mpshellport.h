#ifndef _MPSHELLPORT_H_
#define _MPSHELLPORT_H_

#include "tos_k.h"
#include "tos_hal_uart.h"

// FIXME tightly couple with uart
typedef struct _mp_shell_control_st {

    hal_uart_t          shell_uart;

    k_sem_t             shell_rx_sem;
    k_chr_fifo_t        shell_rx_fifo;
    uint8_t            *shell_rx_fifo_buffer;

} mp_shell_ctl_t;

int mp_shell_init(int buf_size, hal_uart_port_t uart_port);
void mp_shell_deinit(void);

int mp_shell_getchar(void);
void mp_shell_putsn(const char *str, size_t len);

void mp_shell_input_byte(uint8_t data);

#endif /* _MPSHELLPORT_H_ */
