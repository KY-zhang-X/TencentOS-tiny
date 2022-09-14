#ifndef _MPHALSPI_H_
#define _MPHALSPI_H_

#include "py/obj.h"

#if !(MP_GEN_HDR)
#include "tos_k.h"
#include "mp_tos_hal_spi.h"
#endif

typedef struct _machine_hard_spi_obj_t {
    mp_obj_base_t base;
    hal_spi_port_t port;
    hal_spi_t spi;
    uint16_t timeout;
    uint16_t timeout_char;
    uint8_t init : 1;
} machine_hard_spi_obj_t;

machine_hard_spi_obj_t *machine_hard_spi_find(mp_obj_t user_obj);

#endif /* _MPHALSPI_H_ */
