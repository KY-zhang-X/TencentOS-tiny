
#include "py/mpconfig.h"
#include "py/mphal.h"
#include "py/obj.h"
#include "py/runtime.h"
#include "py/stream.h"
#if !(MP_GEN_HDR)
#include "tos_k.h"
#include "tos_hal_uart.h"
#endif

int machine_uart_rx_chr(machine_uart_obj_t *self) {
    k_err_t err;
    uint8_t chr;

    if (!self->init)
        return -1;
    
    machine_uart_rx_start(self);

    if (tos_chr_fifo_is_empty(&self->rx_fifo)) {
        if (tos_sem_pend(&self->rx_sem, self->timeout) != K_ERR_NONE) {
            return -1;
        }
    }
    err = tos_chr_fifo_pop(&self->rx_fifo, &chr);

    return err == K_ERR_NONE ? chr : -1;
}

int machine_uart_tx_strn(machine_uart_obj_t *self, const char *str, mp_uint_t len) {
    if (K_ERR_NONE != tos_hal_uart_write(&self->uart, (const uint8_t *)str, len, 0xFFFF)) {
        return -1;
    }
    return 0;
}

extern machine_uart_obj_t *machine_uart_find(mp_obj_t user_obj);
extern void machine_uart_rx_start(machine_uart_obj_t *self);

STATIC void machine_uart_print(const mp_print_t *print, mp_obj_t self_in, mp_print_kind_t kind) {
    machine_uart_obj_t *self = MP_OBJ_TO_PTR(self_in);
    if (self->init) {
        mp_printf(print, "UART(%u, rxbuf=%u, timeout=%u, timeout_char=%u)", self->port, self->rx_fifo_buf_len, self->timeout, self->timeout_char);
    } else {
        mp_printf(print, "UART(%u)", self->port);
    }
}

STATIC mp_obj_t machine_uart_init_helper(machine_uart_obj_t *self, size_t n_args, const mp_obj_t *pos_args, mp_map_t *kw_args);

mp_obj_t machine_uart_make_new(const mp_obj_type_t *type, size_t n_args, size_t n_kw, const mp_obj_t *args) {
    // check arguments
    mp_arg_check_num(n_args, n_kw, 1, MP_OBJ_FUN_ARGS_MAX, true);

    machine_uart_obj_t *uart = machine_uart_find(args[0]);
    if (uart == NULL) {
        mp_raise_msg(&mp_type_ValueError, MP_ERROR_TEXT("invalid uart"));
    }

    mp_map_t kw_args;
    mp_map_init_fixed_table(&kw_args, n_kw, args + n_args);
    machine_uart_init_helper(uart, n_args - 1, args + 1, &kw_args);

    return MP_OBJ_FROM_PTR(uart);
}

STATIC mp_obj_t machine_uart_init_helper(machine_uart_obj_t *self, size_t n_args, const mp_obj_t *pos_args, mp_map_t *kw_args) {
    enum { /*ARG_baudrate, ARG_bits, ARG_parity, ARG_stop, ARG_flow, ARG_txbuf, */ARG_rxbuf, ARG_timeout, ARG_timeout_char };
    static const mp_arg_t allowed_args[] = {
        // { MP_QSTR_baudrate, MP_ARG_REQUIRED | MP_ARG_INT, {.u_int = 9600} },
        // { MP_QSTR_bits, MP_ARG_INT, {.u_int = 8} },
        // { MP_QSTR_parity, MP_ARG_OBJ, {.u_rom_obj = MP_ROM_NONE} },
        // { MP_QSTR_stop, MP_ARG_INT, {.u_int = 1} },
        // { MP_QSTR_flow, MP_ARG_KW_ONLY | MP_ARG_INT, {.u_int}}
        // { MP_QSTR_txbuf, MP_ARG_KW_ONLY | MP_ARG_INT, {.u_int = -1} },
        { MP_QSTR_rxbuf, MP_ARG_KW_ONLY | MP_ARG_INT, {.u_int = 64} },
        { MP_QSTR_timeout, MP_ARG_KW_ONLY | MP_ARG_INT, {.u_int = 0} },
        { MP_QSTR_timeout_char, MP_ARG_KW_ONLY | MP_ARG_INT, {.u_int = 0} },
    };
    mp_arg_val_t args[MP_ARRAY_SIZE(allowed_args)];
    mp_arg_parse_all(n_args, pos_args, kw_args, MP_ARRAY_SIZE(allowed_args), allowed_args, args);

    if (self->init) {
        mp_raise_msg_varg(&mp_type_OSError, MP_ERROR_TEXT("UART(%u) has been initialized"), self->port);
    }

    if (0 != tos_hal_uart_init(&self->uart, self->port)) {
        mp_raise_msg_varg(&mp_type_ValueError, MP_ERROR_TEXT("UART(%u) doesn't exist"), self->port);
    }

    if (args[ARG_rxbuf].u_int >= 0) {
        self->rx_fifo_buf_len = args[ARG_rxbuf].u_int;
    }
    self->timeout = args[ARG_timeout].u_int;
    self->timeout_char = args[ARG_timeout_char].u_int;
    // minimal char timeout is 2ms
    if (self->timeout_char < 2) {
        self->timeout_char = 2;
    }

    // reset rx fifo buffer before reallocation
    if (self->rx_fifo_buf) {
        tos_mmheap_free(self->rx_fifo_buf);
        self->rx_fifo_buf = NULL;
    }
    // TODO: reset rx fifo and rx sem?
    // tos_chr_fifo_destroy(&self->rx_fifo);
    // tos_sem_destroy(&self->rx_sem);
    // setup rx fifo
    if (self->rx_fifo_buf_len > 0) {
        self->rx_fifo_buf = tos_mmheap_alloc(self->rx_fifo_buf_len);
        if (!self->rx_fifo_buf) {
            goto err0;
        }
        tos_chr_fifo_create(&self->rx_fifo, self->rx_fifo_buf, self->rx_fifo_buf_len);
        if (K_ERR_NONE != tos_sem_create(&self->rx_sem, 0)) {
            goto err1;
        }
        machine_uart_rx_start(self);
    }

    self->init = 1;

    return mp_const_none;
		
err1:
    tos_mmheap_free(self->rx_fifo_buf);
    self->rx_fifo_buf = NULL;
    tos_chr_fifo_destroy(&self->rx_fifo);
err0:
    tos_hal_uart_deinit(&self->uart);
    mp_raise_msg(&mp_type_OSError, MP_ERROR_TEXT("can't create rxbuf"));

    return mp_const_none;
}

// uart.init()
STATIC mp_obj_t machine_uart_init(size_t n_args, const mp_obj_t *args, mp_map_t *kw_args) {
    return machine_uart_init_helper(MP_OBJ_TO_PTR(args[0]), n_args - 1, args + 1, kw_args);
}
STATIC MP_DEFINE_CONST_FUN_OBJ_KW(machine_uart_init_obj, 1, machine_uart_init);

// uart.deinit()
STATIC mp_obj_t machine_uart_deinit(mp_obj_t self_in) {
    machine_uart_obj_t *self = MP_OBJ_TO_PTR(self_in);
    if (self->init) {
        if (self->rx_fifo_buf) {
            tos_mmheap_free(self->rx_fifo_buf);
            self->rx_fifo_buf = NULL;
        }
        tos_chr_fifo_destroy(&self->rx_fifo);
        tos_sem_destroy(&self->rx_sem);
        tos_hal_uart_deinit(&self->uart);
        self->init = 0;
    }
    return mp_const_none;
}
STATIC MP_DEFINE_CONST_FUN_OBJ_1(machine_uart_deinit_obj, machine_uart_deinit);

// uart.any()
// Return `True` if any characters waiting, else `False`.
STATIC mp_obj_t machine_uart_any(mp_obj_t self_in) {
    machine_uart_obj_t *self = MP_OBJ_TO_PTR(self_in);
    if (self->rx_fifo_buf) {
        return MP_OBJ_NEW_SMALL_INT(!tos_chr_fifo_is_empty(&self->rx_fifo));
    } else {
        return MP_OBJ_NEW_SMALL_INT(0);
    }
}
STATIC MP_DEFINE_CONST_FUN_OBJ_1(machine_uart_any_obj, machine_uart_any);

STATIC const mp_rom_map_elem_t machine_uart_locals_dict_table[] = {
    // instance methods
    { MP_ROM_QSTR(MP_QSTR_init), MP_ROM_PTR(&machine_uart_init_obj) },
    { MP_ROM_QSTR(MP_QSTR_deinit), MP_ROM_PTR(&machine_uart_deinit_obj) },
    { MP_ROM_QSTR(MP_QSTR_any), MP_ROM_PTR(&machine_uart_any_obj) },
    { MP_ROM_QSTR(MP_QSTR_read), MP_ROM_PTR(&mp_stream_read_obj) },
    { MP_ROM_QSTR(MP_QSTR_readline), MP_ROM_PTR(&mp_stream_unbuffered_readline_obj) },
    { MP_ROM_QSTR(MP_QSTR_readinto), MP_ROM_PTR(&mp_stream_readinto_obj) },
    { MP_ROM_QSTR(MP_QSTR_write), MP_ROM_PTR(&mp_stream_write_obj) },
};
STATIC MP_DEFINE_CONST_DICT(machine_uart_locals_dict, machine_uart_locals_dict_table);

mp_uint_t machine_uart_read(mp_obj_t self_in, void *buf_in, mp_uint_t size, int *errcode) {
    machine_uart_obj_t *self = MP_OBJ_TO_PTR(self_in);
    uint8_t *buf = buf_in;

    if (size == 0) {
        return 0;
    }

    if (!self->rx_fifo_buf) {
        // no buffering
        if (0 != tos_hal_uart_read(&self->uart, (const uint8_t *)buf, size, self->timeout + self->timeout_char * size)) {
            return MP_STREAM_ERROR;
        }
        return size;
    } else {
        uint8_t *orig_buf = buf;
        if (tos_chr_fifo_is_empty(&self->rx_fifo)) {
            if (K_ERR_NONE != tos_sem_pend(&self->rx_sem, self->timeout)) {
                *errcode = MP_EAGAIN;
                return MP_STREAM_ERROR;
            }
        }
        for (;;) {
            int read_size = tos_chr_fifo_pop_stream(&self->rx_fifo, buf, size);
            size -= read_size; buf += read_size;
            if (size <= 0) {
                return buf - orig_buf;
            }
            if (tos_chr_fifo_is_empty(&self->rx_fifo)) {
                if (K_ERR_NONE != tos_sem_pend(&self->rx_sem, self->timeout_char)) {
                    return buf - orig_buf;
                }
            }
        }
    }
}

mp_uint_t machine_uart_write(mp_obj_t self_in, const void *buf, mp_uint_t size, int *errcode) {
    machine_uart_obj_t *self = MP_OBJ_TO_PTR(self_in);
    if (0 != tos_hal_uart_write(&self->uart, (uint8_t *)buf, size, 0xFFFF)) {   // timeout_char ?
        return MP_STREAM_ERROR;
    }
    return size;
}

mp_uint_t machine_uart_ioctl(mp_obj_t self_in, mp_uint_t request, uintptr_t arg, int *errcode) {
    machine_uart_obj_t *self = MP_OBJ_TO_PTR(self_in);
    mp_uint_t ret;
    if (request == MP_STREAM_POLL) {
        uintptr_t flags = arg;
        ret = 0;
        if ((flags & MP_STREAM_POLL_RD) && !tos_chr_fifo_is_empty(&self->rx_fifo)) {
            ret |= MP_STREAM_POLL_RD;
        }
        if ((flags & MP_STREAM_POLL_WR) && 1) {
            ret |= MP_STREAM_POLL_WR;
        }
    } else {
        *errcode = MP_EINVAL;
        ret = MP_STREAM_ERROR;
    }
    return ret;
}

STATIC const mp_stream_p_t uart_stream_p = {
    .read = machine_uart_read,
    .write = machine_uart_write,
    .ioctl = machine_uart_ioctl,
    .is_text = false,
};

const mp_obj_type_t machine_uart_type = {
    { &mp_type_type },
    .name = MP_QSTR_UART,
    .print = machine_uart_print,
    .make_new = machine_uart_make_new,
    .getiter = mp_identity_getiter,
    .iternext = mp_stream_unbuffered_iter,
    .protocol = &uart_stream_p,
    .locals_dict = (mp_obj_dict_t *)&machine_uart_locals_dict,
};
