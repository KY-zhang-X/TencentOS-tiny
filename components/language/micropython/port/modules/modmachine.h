#ifndef _MODMACHINE_H_
#define _MODMACHINE_H_

#include "py/obj.h"

extern const mp_obj_type_t machine_pin_type;
extern const mp_obj_type_t machine_uart_type;
extern const mp_obj_type_t machine_timer_type;

void machine_pins_init(void);
void machine_timer_deinit_all(void);

#endif /* _MODMACHINE_H_ */
