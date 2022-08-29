#include "py/mpconfig.h"

#if MICROPY_PY_MACHINE

#include "py/runtime.h"
#include "shared/runtime/pyexec.h"
#include "extmod/machine_mem.h"
#include "extmod/machine_signal.h"
#include "extmod/machine_spi.h"
#include "extmod/machine_i2c.h"
#include "modmachine.h"

STATIC mp_obj_t machine_soft_reset(void) {
    pyexec_system_exit = PYEXEC_FORCED_EXIT;
    mp_raise_type(&mp_type_SystemExit);
}
MP_DEFINE_CONST_FUN_OBJ_0(machine_soft_reset_obj, machine_soft_reset);

STATIC const mp_rom_map_elem_t machine_module_globals_table[] = {
    { MP_ROM_QSTR(MP_QSTR___name__), MP_ROM_QSTR(MP_QSTR_umachine) },

    { MP_ROM_QSTR(MP_QSTR_soft_reset), MP_ROM_PTR(&machine_soft_reset_obj) },

    { MP_ROM_QSTR(MP_QSTR_mem8), MP_ROM_PTR(&machine_mem8_obj) },
    { MP_ROM_QSTR(MP_QSTR_mem16), MP_ROM_PTR(&machine_mem16_obj) },
    { MP_ROM_QSTR(MP_QSTR_mem32), MP_ROM_PTR(&machine_mem32_obj) },

    { MP_ROM_QSTR(MP_QSTR_Pin), MP_ROM_PTR(&machine_pin_type) },
    { MP_ROM_QSTR(MP_QSTR_Signal), MP_ROM_PTR(&machine_signal_type) },

    #if MICROPY_PY_MACHINE_I2C
    #if MICROPY_PY_MACHINE_SOFTI2C
    { MP_ROM_QSTR(MP_QSTR_SoftI2C), MP_ROM_PTR(&mp_machine_soft_i2c_type) },
    #endif
    #endif
    #if MICROPY_PY_MACHINE_SPI
    #if MICROPY_PY_MACHINE_SOFTSPI
    { MP_ROM_QSTR(MP_QSTR_SoftSPI), MP_ROM_PTR(&mp_machine_soft_spi_type) },
    #endif
    #endif

    { MP_ROM_QSTR(MP_QSTR_UART), MP_ROM_PTR(&machine_uart_type) },
    { MP_ROM_QSTR(MP_QSTR_Timer), MP_ROM_PTR(&machine_timer_type) },
};
STATIC MP_DEFINE_CONST_DICT(machine_module_globals, machine_module_globals_table);

const mp_obj_module_t mp_module_machine = {
    .base = { &mp_type_module },
    .globals = (mp_obj_dict_t *)&machine_module_globals,
};
MP_REGISTER_MODULE(MP_QSTR_umachine, mp_module_machine);

#endif /* MICROPY_PY_MACHINE */
