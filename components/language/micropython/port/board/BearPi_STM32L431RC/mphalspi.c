#include "modmachine.h"
#include "mphalspi.h"

#if !(MP_GEN_HDR)
#include "tos_k.h"
#include "mp_tos_hal_spi.h"
#endif

#define SPI_NUM 4

#define SPI(u_port) \
    machine_hard_spi_obj_t machine_hard_spi_##u_port##_obj = { \
        {&machine_hard_spi_type}, \
        .port = HAL_SPI_PORT_##u_port, \
        .init = 0, \
    }

SPI(1); SPI(2); SPI(3);

static machine_hard_spi_obj_t *machine_hard_spi_obj_all[SPI_NUM] = {
    NULL,
    &machine_hard_spi_1_obj,
    &machine_hard_spi_2_obj,
    &machine_hard_spi_3_obj,
};

machine_hard_spi_obj_t *machine_hard_spi_find(mp_obj_t user_obj) {
    machine_hard_spi_obj_t *spi = NULL;
    if (mp_obj_is_int(user_obj)) {
        mp_uint_t spi_id = mp_obj_get_int(user_obj);
        if (spi_id < SPI_NUM)
            spi = machine_hard_spi_obj_all[spi_id];
    }
    return spi;
}
