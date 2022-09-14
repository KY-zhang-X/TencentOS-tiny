#ifndef _MPHALBOARD_H_
#define _MPHALBOARD_H_

#if !(MP_GEN_HDR)
#include "main.h"
#include "tos_k.h"
#include "tos_hal_uart.h"
#endif
#include "py/obj.h"
#include "mphalpin.h"
#include "mphaluart.h"
#include "mphalspi.h"

#define IRQ_PRI_SYSTICK         0
#define IRQ_PRI_UART            1
#define IRQ_PRI_SDIO            1
#define IRQ_PRI_DMA             1
#define IRQ_PRI_FLASH           2
#define IRQ_PRI_OTG_FS          2
#define IRQ_PRI_OTG_HS          2
#define IRQ_PRI_TIM5            2
#define IRQ_PRI_CAN             2
#define IRQ_PRI_TIMX            2
#define IRQ_PRI_EXTINT          2
#define IRQ_PRI_PENDSV          3
#define IRQ_PRI_RTC_WKUP        3


#endif /* _MPHALBOARD_H_ */
