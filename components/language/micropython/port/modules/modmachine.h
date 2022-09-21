#ifndef _MODMACHINE_H_
#define _MODMACHINE_H_

#include "py/obj.h"

#include "machine_pin.h"
#include "machine_uart.h"

extern const mp_obj_type_t machine_timer_type;
extern const mp_obj_type_t machine_hard_spi_type;

void machine_timer_deinit_all(void);

#endif /* _MODMACHINE_H_ */
