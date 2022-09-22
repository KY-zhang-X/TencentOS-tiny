#ifndef _MACHINE_TIMER_H_
#define _MACHINE_TIMER_H_

#include "py/obj.h"

extern const mp_obj_type_t machine_timer_type;

void machine_timer_deinit_all(void);

#endif /* _MACHINE_TIMER_H_ */
