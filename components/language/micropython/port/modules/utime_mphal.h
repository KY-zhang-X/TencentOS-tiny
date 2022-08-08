#ifndef _UTIME_MPHAL_H_
#define _UTIME_MPHAL_H_

#include "py/obj.h"

MP_DECLARE_CONST_FUN_OBJ_1(mp_utime_sleep_obj);
MP_DECLARE_CONST_FUN_OBJ_1(mp_utime_sleep_ms_obj);
// MP_DECLARE_CONST_FUN_OBJ_1(mp_utime_sleep_us_obj);
MP_DECLARE_CONST_FUN_OBJ_0(mp_utime_ticks_ms_obj);
// MP_DECLARE_CONST_FUN_OBJ_0(mp_utime_ticks_us_obj);
MP_DECLARE_CONST_FUN_OBJ_0(mp_utime_ticks_cpu_obj);
MP_DECLARE_CONST_FUN_OBJ_2(mp_utime_ticks_diff_obj);
MP_DECLARE_CONST_FUN_OBJ_2(mp_utime_ticks_add_obj);
// MP_DECLARE_CONST_FUN_OBJ_0(mp_utime_time_ns_obj);

#endif /* _UTIME_MPHAL_H_ */
