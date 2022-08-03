#include "mpshellport.h"
#include "usart.h"

static mp_shell_ctl_t mp_shell_ctl;
#define MP_SHELL_CTL ((mp_shell_ctl_t *)(&mp_shell_ctl))

int mp_shell_getchar(void) 
{
    uint8_t chr;
    k_err_t err;

    /*===========================================*/
    // FIXME: There must be a better implementation
    extern uint8_t shell_data;
    HAL_UART_Receive_IT(&huart2, &shell_data, 1);
    /*===========================================*/

    if (tos_sem_pend(&MP_SHELL_CTL->shell_rx_sem, TOS_TIME_FOREVER) != K_ERR_NONE) {
        return -1;
    }

    err = tos_chr_fifo_pop(&MP_SHELL_CTL->shell_rx_fifo, &chr);

    return err == K_ERR_NONE ? chr : -1;
}

void mp_shell_putsn(const char *str, size_t len)
{
    tos_hal_uart_write(&MP_SHELL_CTL->shell_uart, (const uint8_t *)str, len, 0xFFFF);
}

int mp_shell_init(int buf_size, hal_uart_port_t uart_port) 
{    
    void *buffer = K_NULL;
    
    memset(MP_SHELL_CTL, 0, sizeof(mp_shell_ctl_t));

    tos_hal_uart_init(&MP_SHELL_CTL->shell_uart, uart_port);

    buffer = tos_mmheap_alloc(buf_size);
    if (!buffer) {
        return -1;
    }

    MP_SHELL_CTL->shell_rx_fifo_buffer = (uint8_t *)buffer;
    tos_chr_fifo_create(&MP_SHELL_CTL->shell_rx_fifo, buffer, buf_size);

    if (tos_sem_create(&MP_SHELL_CTL->shell_rx_sem, (k_sem_cnt_t)0u) != K_ERR_NONE) {
        goto errout;
    }

    return 0;

errout:
    tos_mmheap_free(MP_SHELL_CTL->shell_rx_fifo_buffer);
    MP_SHELL_CTL->shell_rx_fifo_buffer = K_NULL;
    tos_chr_fifo_destroy(&MP_SHELL_CTL->shell_rx_fifo);
    tos_hal_uart_deinit(&MP_SHELL_CTL->shell_uart);

    return -1;
}

void mp_shell_deinit(void)
{
    tos_sem_destroy(&MP_SHELL_CTL->shell_rx_sem);
    
    tos_mmheap_free(MP_SHELL_CTL->shell_rx_fifo_buffer);
    MP_SHELL_CTL->shell_rx_fifo_buffer = K_NULL;
    tos_chr_fifo_destroy(&MP_SHELL_CTL->shell_rx_fifo);

    tos_hal_uart_deinit(&MP_SHELL_CTL->shell_uart);
}

void mp_shell_input_byte(uint8_t data)
{
    if (tos_chr_fifo_push(&MP_SHELL_CTL->shell_rx_fifo, data) == K_ERR_NONE) {
        tos_sem_post(&MP_SHELL_CTL->shell_rx_sem);
    }
}
