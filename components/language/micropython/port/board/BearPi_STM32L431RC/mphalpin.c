#include "py/mpconfig.h"
#include "py/mphal.h"
#include "py/runtime.h"

#include "modmachine.h"
#include "mphalpin.h"

#if !(MP_GEN_HDR)
#include "tos_k.h"
#endif

/********************** GPIO *************************/

#define PIN(p_port, p_pin) \
    const machine_pin_obj_t machine_pin_##p_port##p_pin##_obj = { \
        {&machine_pin_type}, \
        .name = MP_QSTR_##p_port##p_pin, \
        .gpio = GPIO##p_port, \
        .pin_no = p_pin, \
    }

PIN(A, 0);  PIN(A, 1);  PIN(A, 2);  PIN(A, 3); 
PIN(A, 4);  PIN(A, 5);  PIN(A, 6);  PIN(A, 7);
PIN(A, 8);  PIN(A, 9);  PIN(A, 10); PIN(A, 11); 
PIN(A, 12); PIN(A, 13); PIN(A, 14); PIN(A, 15);

PIN(B, 0);  PIN(B, 1);  PIN(B, 2);  PIN(B, 3); 
PIN(B, 4);  PIN(B, 5);  PIN(B, 6);  PIN(B, 7);
PIN(B, 8);  PIN(B, 9);  PIN(B, 10); PIN(B, 11); 
PIN(B, 12); PIN(B, 13); PIN(B, 14); PIN(B, 15);

PIN(C, 0);  PIN(C, 1);  PIN(C, 2);  PIN(C, 3); 
PIN(C, 4);  PIN(C, 5);  PIN(C, 6);  PIN(C, 7);
PIN(C, 8);  PIN(C, 9);  PIN(C, 10); PIN(C, 11); 
PIN(C, 12); PIN(C, 13); PIN(C, 14); PIN(C, 15);

PIN(D, 2);

STATIC const mp_rom_map_elem_t machine_pins_locals_dict_table[] = {
    // { MP_ROM_QSTR(MP_QSTR_A0),  MP_ROM_PTR(&machine_pin_A0_obj) },
    // { MP_ROM_QSTR(MP_QSTR_A1),  MP_ROM_PTR(&machine_pin_A1_obj) },
    // { MP_ROM_QSTR(MP_QSTR_A2),  MP_ROM_PTR(&machine_pin_A2_obj) },
    // { MP_ROM_QSTR(MP_QSTR_A3),  MP_ROM_PTR(&machine_pin_A3_obj) },
    // { MP_ROM_QSTR(MP_QSTR_A4),  MP_ROM_PTR(&machine_pin_A4_obj) },
    // { MP_ROM_QSTR(MP_QSTR_A5),  MP_ROM_PTR(&machine_pin_A5_obj) },
    // { MP_ROM_QSTR(MP_QSTR_A6),  MP_ROM_PTR(&machine_pin_A6_obj) },
    // { MP_ROM_QSTR(MP_QSTR_A7),  MP_ROM_PTR(&machine_pin_A7_obj) },
    // { MP_ROM_QSTR(MP_QSTR_A8),  MP_ROM_PTR(&machine_pin_A8_obj) },
    // { MP_ROM_QSTR(MP_QSTR_A9),  MP_ROM_PTR(&machine_pin_A9_obj) },
    // { MP_ROM_QSTR(MP_QSTR_A10), MP_ROM_PTR(&machine_pin_A10_obj) },
    // { MP_ROM_QSTR(MP_QSTR_A11), MP_ROM_PTR(&machine_pin_A11_obj) },
    // { MP_ROM_QSTR(MP_QSTR_A12), MP_ROM_PTR(&machine_pin_A12_obj) },
    // { MP_ROM_QSTR(MP_QSTR_A13), MP_ROM_PTR(&machine_pin_A13_obj) },
    // { MP_ROM_QSTR(MP_QSTR_A14), MP_ROM_PTR(&machine_pin_A14_obj) },
    // { MP_ROM_QSTR(MP_QSTR_A15), MP_ROM_PTR(&machine_pin_A15_obj) },

    // { MP_ROM_QSTR(MP_QSTR_B0),  MP_ROM_PTR(&machine_pin_B0_obj) },
    // { MP_ROM_QSTR(MP_QSTR_B1),  MP_ROM_PTR(&machine_pin_B1_obj) },
    { MP_ROM_QSTR(MP_QSTR_B2),  MP_ROM_PTR(&machine_pin_B2_obj) },
    { MP_ROM_QSTR(MP_QSTR_B3),  MP_ROM_PTR(&machine_pin_B3_obj) },
    // { MP_ROM_QSTR(MP_QSTR_B4),  MP_ROM_PTR(&machine_pin_B4_obj) },
    // { MP_ROM_QSTR(MP_QSTR_B5),  MP_ROM_PTR(&machine_pin_B5_obj) },
    // { MP_ROM_QSTR(MP_QSTR_B6),  MP_ROM_PTR(&machine_pin_B6_obj) },
    // { MP_ROM_QSTR(MP_QSTR_B7),  MP_ROM_PTR(&machine_pin_B7_obj) },
    // { MP_ROM_QSTR(MP_QSTR_B8),  MP_ROM_PTR(&machine_pin_B8_obj) },
    // { MP_ROM_QSTR(MP_QSTR_B9),  MP_ROM_PTR(&machine_pin_B9_obj) },
    // { MP_ROM_QSTR(MP_QSTR_B10), MP_ROM_PTR(&machine_pin_B10_obj) },
    // { MP_ROM_QSTR(MP_QSTR_B11), MP_ROM_PTR(&machine_pin_B11_obj) },
    // { MP_ROM_QSTR(MP_QSTR_B12), MP_ROM_PTR(&machine_pin_B12_obj) },
    // { MP_ROM_QSTR(MP_QSTR_B13), MP_ROM_PTR(&machine_pin_B13_obj) },
    // { MP_ROM_QSTR(MP_QSTR_B14), MP_ROM_PTR(&machine_pin_B14_obj) },
    // { MP_ROM_QSTR(MP_QSTR_B15), MP_ROM_PTR(&machine_pin_B15_obj) },

    // { MP_ROM_QSTR(MP_QSTR_C0),  MP_ROM_PTR(&machine_pin_C0_obj) },
    // { MP_ROM_QSTR(MP_QSTR_C1),  MP_ROM_PTR(&machine_pin_C1_obj) },
    // { MP_ROM_QSTR(MP_QSTR_C2),  MP_ROM_PTR(&machine_pin_C2_obj) },
    // { MP_ROM_QSTR(MP_QSTR_C3),  MP_ROM_PTR(&machine_pin_C3_obj) },
    // { MP_ROM_QSTR(MP_QSTR_C4),  MP_ROM_PTR(&machine_pin_C4_obj) },
    // { MP_ROM_QSTR(MP_QSTR_C5),  MP_ROM_PTR(&machine_pin_C5_obj) },
    // { MP_ROM_QSTR(MP_QSTR_C6),  MP_ROM_PTR(&machine_pin_C6_obj) },
    // { MP_ROM_QSTR(MP_QSTR_C7),  MP_ROM_PTR(&machine_pin_C7_obj) },
    // { MP_ROM_QSTR(MP_QSTR_C8),  MP_ROM_PTR(&machine_pin_C8_obj) },
    // { MP_ROM_QSTR(MP_QSTR_C9),  MP_ROM_PTR(&machine_pin_C9_obj) },
    // { MP_ROM_QSTR(MP_QSTR_C10), MP_ROM_PTR(&machine_pin_C10_obj) },
    // { MP_ROM_QSTR(MP_QSTR_C11), MP_ROM_PTR(&machine_pin_C11_obj) },
    // { MP_ROM_QSTR(MP_QSTR_C12), MP_ROM_PTR(&machine_pin_C12_obj) },
    { MP_ROM_QSTR(MP_QSTR_C13), MP_ROM_PTR(&machine_pin_C13_obj) },
    // { MP_ROM_QSTR(MP_QSTR_C14), MP_ROM_PTR(&machine_pin_C14_obj) },
    // { MP_ROM_QSTR(MP_QSTR_C15), MP_ROM_PTR(&machine_pin_C15_obj) },

    // { MP_ROM_QSTR(MP_QSTR_D2),  MP_ROM_PTR(&machine_pin_D2_obj) },

    { MP_ROM_QSTR(MP_QSTR_LED), MP_ROM_PTR(&machine_pin_C13_obj) },
    { MP_ROM_QSTR(MP_QSTR_KEY1), MP_ROM_PTR(&machine_pin_B2_obj) },
    { MP_ROM_QSTR(MP_QSTR_KEY2), MP_ROM_PTR(&machine_pin_B3_obj) },

};
STATIC MP_DEFINE_CONST_DICT(machine_pins_locals_dict, machine_pins_locals_dict_table);

STATIC int mask2no(uint32_t mask) {
    for (int i = 0; i < 32; i++) {
        if ((1U << i) == mask) {
            return i;
        }
    }
    return -1;
}

#define no2mask(no) \
    (1UL << (no))

int mp_hal_pin_read(const machine_pin_obj_t *pin) {
    return (GPIO_PIN_SET == HAL_GPIO_ReadPin(pin->gpio, no2mask(pin->pin_no)) ? 1 : 0);
}

void mp_hal_pin_write(const machine_pin_obj_t *pin, int v) {
    HAL_GPIO_WritePin(pin->gpio, no2mask(pin->pin_no), (v == 1) ? GPIO_PIN_SET : GPIO_PIN_RESET);
}

void mp_hal_pin_config(const machine_pin_obj_t *pin, uint32_t mode, uint32_t pull, uint32_t alt) {
    GPIO_InitTypeDef GPIO_InitStruct;
    GPIO_InitStruct.Pin = no2mask(pin->pin_no);
    GPIO_InitStruct.Mode = mode;
    GPIO_InitStruct.Pull = pull;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    GPIO_InitStruct.Alternate = alt;
    HAL_GPIO_Init(pin->gpio, &GPIO_InitStruct);
}

void mp_hal_gpio_clock_enable(const machine_pin_obj_t *pin) {
    #define AHBxENR AHB2ENR
    #define AHBxENR_GPIOAEN_Pos RCC_AHB2ENR_GPIOAEN_Pos

    uint32_t gpio_idx = ((uint32_t)pin->gpio - GPIOA_BASE) / (GPIOB_BASE - GPIOA_BASE);
    RCC->AHBxENR |= 1 << (AHBxENR_GPIOAEN_Pos + gpio_idx);
    volatile uint32_t tmp = RCC->AHBxENR; // Delay after enabling clock
    (void)tmp;
}

const machine_pin_obj_t *mp_hal_get_pin_obj(mp_obj_t name) {
    const mp_map_t *named_map = &machine_pins_locals_dict.map;
    mp_map_elem_t *named_elem = mp_map_lookup((mp_map_t *)named_map, name, MP_MAP_LOOKUP);
    if (named_elem != NULL && named_elem->value != MP_OBJ_NULL) {
        return MP_OBJ_TO_PTR(named_elem->value);
    }
    return NULL;
}

qstr mp_hal_pin_name(const machine_pin_obj_t *pin) {
    return pin->name;
}

void mp_hal_pin_print(const mp_print_t *print, const machine_pin_obj_t *pin) {
    mp_printf(print, "Pin(%q)", pin->name);
}

/********************** External Interrupt *************************/
#define EXTI_NUM_VECTORS        (16)

STATIC const uint8_t nvic_irq_channel[EXTI_NUM_VECTORS] = {
    EXTI0_IRQn,     EXTI1_IRQn,     EXTI2_IRQn,     EXTI3_IRQn,
    EXTI4_IRQn,     EXTI9_5_IRQn,   EXTI9_5_IRQn,   EXTI9_5_IRQn,
    EXTI9_5_IRQn,   EXTI9_5_IRQn,   EXTI15_10_IRQn, EXTI15_10_IRQn,
    EXTI15_10_IRQn, EXTI15_10_IRQn, EXTI15_10_IRQn, EXTI15_10_IRQn,
};

STATIC mp_obj_t machine_pin_irq_handler[EXTI_NUM_VECTORS];
STATIC mp_obj_t machine_pin_irq_handler_arg[EXTI_NUM_VECTORS];

STATIC void extint_enable(int line) {
    TOS_CPU_CPSR_ALLOC();
    if (line >= EXTI_NUM_VECTORS) {
        return;
    }
    TOS_CPU_INT_DISABLE();
    EXTI->IMR1 |= no2mask(line);
    TOS_CPU_INT_ENABLE();
}

STATIC void extint_disable(int line) {
    TOS_CPU_CPSR_ALLOC();
    if (line >= EXTI_NUM_VECTORS) {
        return;
    }
    TOS_CPU_INT_DISABLE();
    EXTI->IMR1 &= ~(no2mask(line));
    TOS_CPU_INT_ENABLE();
}

STATIC void mp_hal_extint_config(const machine_pin_obj_t *pin, uint32_t mode) {
    GPIO_InitTypeDef GPIO_InitStruct;
    GPIO_InitStruct.Pin = no2mask(pin->pin_no);
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    GPIO_InitStruct.Alternate = 0;
    GPIO_InitStruct.Mode = mode;
    GPIO_InitStruct.Pull = (mode == MP_HAL_PIN_IRQ_RISING) ? MP_HAL_PIN_PULL_DOWN : MP_HAL_PIN_PULL_UP;
    HAL_GPIO_Init(pin->gpio, &GPIO_InitStruct);

    HAL_NVIC_SetPriority(nvic_irq_channel[pin->pin_no], IRQ_PRI_EXTINT, 0);
    HAL_NVIC_EnableIRQ(nvic_irq_channel[pin->pin_no]);
}

void mp_hal_extint_register_pin(const machine_pin_obj_t *pin, uint32_t mode, mp_obj_t handler) {
    uint32_t line = pin->pin_no;
    if (machine_pin_irq_handler[line] != mp_const_none && machine_pin_irq_handler_arg[line] != MP_OBJ_FROM_PTR(pin)) {
        mp_raise_msg_varg(&mp_type_OSError, MP_ERROR_TEXT("ExtInt vector %d is already in use"), line);
    }
    extint_disable(line);
    machine_pin_irq_handler[line] = handler;
    machine_pin_irq_handler_arg[line] = MP_OBJ_FROM_PTR(pin);
    extint_enable(line);
    mp_hal_extint_config(pin, mode);
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
    uint32_t line = mask2no(GPIO_Pin);
    mp_obj_t handler = machine_pin_irq_handler[line];
    mp_sched_schedule(handler, machine_pin_irq_handler_arg[line]);
}
