
#include "py/mpconfig.h"
#if MICROPY_PY_MACHINE_SPI

#include "py/mphal.h"
#include "py/obj.h"
#include "py/runtime.h"
#include "extmod/machine_spi.h"

#if !(MP_GEN_HDR)
#include "tos_k.h"
#include "mp_tos_hal_spi.h"
#endif

extern machine_hard_spi_obj_t *machine_spi_find(mp_obj_t user_obj);

STATIC void machine_hard_spi_print(const mp_print_t *print, mp_obj_t self_in, mp_print_kind_t kind) {
    machine_hard_spi_obj_t *self = MP_OBJ_TO_PTR(self_in);
    mp_printf(print, "SPI(%u)", self->port);
}

STATIC mp_obj_t machine_hard_spi_init_helper(machine_hard_spi_obj_t *self, size_t n_args, const mp_obj_t *pos_args, mp_map_t *kw_args);

mp_obj_t machine_hard_spi_make_new(const mp_obj_type_t *type, size_t n_args, size_t n_kw, const mp_obj_t *args) {
    // check arguments
    mp_arg_check_num(n_args, n_kw, 1, MP_OBJ_FUN_ARGS_MAX, true);

    machine_hard_spi_obj_t *spi = machine_hard_spi_find(args[0]);
    if (spi == NULL) {
        mp_raise_msg(&mp_type_ValueError, MP_ERROR_TEXT("invalid spi"));
    }

    mp_map_t kw_args;
    mp_map_init_fixed_table(&kw_args, n_kw, args + n_args);
    machine_hard_spi_init_helper(spi, n_args - 1, args + 1, &kw_args);

    return MP_OBJ_FROM_PTR(spi);
}

STATIC mp_obj_t machine_hard_spi_init_helper(machine_hard_spi_obj_t *self, size_t n_args, const mp_obj_t *pos_args, mp_map_t *kw_args) {
    /*
    enum { ARG_baudrate, ARG_polarity, ARG_phase, ARG_bits, ARG_firstbit };
    static const mp_arg_t allowed_args[] = {
        { MP_QSTR_baudrate, MP_ARG_INT, {.u_int = 500000} },
        { MP_QSTR_polarity, MP_ARG_KW_ONLY | MP_ARG_INT, {.u_int = 0} },
        { MP_QSTR_phase,    MP_ARG_KW_ONLY | MP_ARG_INT, {.u_int = 0} },
        { MP_QSTR_bits,     MP_ARG_KW_ONLY | MP_ARG_INT, {.u_int = 8} },
        { MP_QSTR_firstbit, MP_ARG_KW_ONLY | MP_ARG_INT, {.u_int = SPI_FIRSTBIT_MSB} },
    };
    mp_arg_val_t args[MP_ARRAY_SIZE(allowed_args)];
    mp_arg_parse_all(n_args, pos_args, kw_args, MP_ARRAY_SIZE(allowed_args), allowed_args, args);
    */

    if (self->init) {
        mp_raise_msg_varg(&mp_type_OSError, MP_ERROR_TEXT("SPI(%u) has been initialized"), self->port);
    }

    if (0 != tos_hal_spi_init(&self->spi, self->port)) {
        mp_raise_msg_varg(&mp_type_ValueError, MP_ERROR_TEXT("SPI(%u) doesn't exist"), self->port);
    }

    // FIXME: should not be fixed
    self->timeout = 100;
    self->timeout_char = 1;

    self->init = 1;
    
    return mp_const_none;
}

STATIC void machine_hard_spi_init(mp_obj_base_t *self_in, size_t n_args, const mp_obj_t *pos_args, mp_map_t *kw_args) {
    machine_hard_spi_obj_t *self = (machine_hard_spi_obj_t *)self_in;
    machine_hard_spi_init_helper(self, n_args, pos_args, kw_args);
}

STATIC void machine_hard_spi_deinit(mp_obj_base_t *self_in) {
    machine_hard_spi_obj_t *self = (machine_hard_spi_obj_t *)self_in;
    if (self->init) {
        tos_hal_spi_deinit(&self->spi);
        self->init = 0;
    }
}

STATIC void machine_hard_spi_transfer(mp_obj_base_t *self_in, size_t len, const uint8_t *src, uint8_t *dest) {
    machine_hard_spi_obj_t *self = (machine_hard_spi_obj_t *)self_in;
    tos_hal_spi_transfer(&self->spi, src, dest, len, self->timeout + len * self->timeout_char);
}

STATIC const mp_machine_spi_p_t machine_hard_spi_p = {
    .init = machine_hard_spi_init,
    .deinit = machine_hard_spi_deinit,
    .transfer = machine_hard_spi_transfer,
};

const mp_obj_type_t machine_hard_spi_type = {
    { &mp_type_type },
    .name = MP_QSTR_SPI,
    .print = machine_hard_spi_print,
    .make_new = machine_hard_spi_make_new,
    .protocol = &machine_hard_spi_p,
    .locals_dict = (mp_obj_dict_t *)&mp_machine_spi_locals_dict,
};
#endif /* MICROPY_PY_MACHINE_SPI */