
#include <stdint.h>
#include <stdbool.h>

#include "mpconfigboard.h"

#ifndef MICROPY_CONFIG_ROM_LEVEL
// #define MICROPY_CONFIG_ROM_LEVEL (MICROPY_CONFIG_ROM_LEVEL_MINIMUM)
// #define MICROPY_CONFIG_ROM_LEVEL (MICROPY_CONFIG_ROM_LEVEL_CORE_FEATURES)
// #define MICROPY_CONFIG_ROM_LEVEL (MICROPY_CONFIG_ROM_LEVEL_BASIC_FEATURES)
#define MICROPY_CONFIG_ROM_LEVEL (MICROPY_CONFIG_ROM_LEVEL_EXTRA_FEATURES)

#endif

// Object representation
#define MICROPY_OBJ_REPR (MICROPY_OBJ_REPR_A)

// Optimisations
#define MICROPY_OPT_COMPUTED_GOTO       (1)

// Compiler configuration
#define MICROPY_ENABLE_COMPILER         (1)
#define MICROPY_COMP_MODULE_CONST       (0)
#define MICROPY_DEBUG_VERBOSE           (0)

// Python internal features
#define MICROPY_READER_POSIX            (0)
#define MICROPY_READER_VFS              (1)
#define MICROPY_ENABLE_GC               (1)
#define MICROPY_HELPER_REPL             (1)
// #define MICROPY_TRACKED_ALLOC           (MICROPY_SSL_MBEDTLS)
// #define MICROPY_ENABLE_PYSTACK          (0)
#define MICROPY_ENABLE_EMERGENCY_EXCEPTION_BUF (1)
#define MICROPY_REPL_INFO               (0)
#define MICROPY_LONGINT_IMPL            (MICROPY_LONGINT_IMPL_MPZ)
#define MICROPY_WARNINGS                (1)
#define MICROPY_FLOAT_IMPL              (MICROPY_FLOAT_IMPL_FLOAT)
// #define MICROPY_STREAMS_POSIX_API       (1)
#define MICROPY_MODULE_FROZEN_STR       (0)
#define MICROPY_MODULE_FROZEN_MPY       (0)
#define MICROPY_USE_INTERNAL_ERRNO      (1)
#define MICROPY_USE_INTERNAL_PRINTF     (0)
#define MICROPY_SCHEDULER_DEPTH         (4)
#define MICROPY_PY_SYS_STDIO_BUFFER     (1)
#define MICROPY_VFS                     (1)
#define MICROPY_VFS_TOS                 (1)
#define MICROPY_VFS_POSIX               (0)
#define MICROPY_VFS_FAT                 (0)


// Control over Python builtins
#define MICROPY_PY_STR_BYTES_CMP_WARN   (1)
#define MICROPY_PY_BUILTINS_RANGE_BINOP (0)
#define MICROPY_PY_BUILTINS_NEXT2       (0)
#define MICROPY_PY_ALL_INPLACE_SPECIAL_METHODS (1)
#define MICROPY_PY_BUILTINS_HELP_TEXT   tencentos_tiny_help_text
#define MICROPY_PY_GC_COLLECT_RETVAL    (0)
// #define MICROPY_PY_IO                   (0)
// #define MICROPY_PY_IO_BUFFEREDWRITER    (0)
// #define MICROPY_PY_SYS_MODULES          (1)
// TODO: lgammaf() is not supported
#define MICROPY_PY_MATH_SPECIAL_FUNCTIONS (0)
#define MICROPY_PY_UTIME                (1)
#define MICROPY_PY_UTIME_MP_HAL         (1)
#define MICROPY_PY_THREAD               (1)

// Extended modules
// #define MICROPY_PY_UTIMEQ               (0)
// #define MICROPY_PY_UHASHLIB_MD5         (0)
// #define MICROPY_PY_UHASHLIB_SHA1        (0)
// #define MICROPY_PY_UHASHLIB_SHA256      (1)
// #define MICROPY_PY_UCRYPTOLIB           (0)
// #define MICROPY_PY_UJSON                (0)
#define MICROPY_PY_OS_DUPTERM           (0)
#define MICROPY_PY_UOS_DUPTERM_NOTIFY   (0)
#define MICROPY_PY_UOS_UNAME            (1)
#define MICROPY_PY_MACHINE              (1)
#define MICROPY_PY_MACHINE_PIN_MAKE_NEW mp_pin_make_new
#define MICROPY_PY_MACHINE_SPI          (1)
#define MICROPY_PY_MACHINE_SOFTSPI      (1)


#if MICROPY_VFS_TOS
#define mp_type_fileio mp_type_vfs_tos_fileio
#define mp_type_textio mp_type_vfs_tos_textio
#elif MICROPY_VFS_FAT
#define mp_type_fileio mp_type_vfs_fat_fileio
#define mp_type_textio mp_type_vfs_fat_textio
#elif MICROPY_VFS_POSIX
#define mp_type_fileio mp_type_vfs_posix_fileio
#define mp_type_textio mp_type_vfs_posix_textio
#endif



#define __BYTE_ORDER__  __ORDER_LITTLE_ENDIAN__

#define MP_SSIZE_MAX (0x7fffffff)
// Type definitions for the specific machine.
typedef int mp_int_t; // must be pointer size
typedef unsigned int mp_uint_t; // must be pointer size
typedef long mp_off_t;
#define UINT_FMT "%u"
#define INT_FMT "%d"

#define MICROPY_BEGIN_ATOMIC_SECTION()      tos_cpu_cpsr_save()
#define MICROPY_END_ATOMIC_SECTION(state)   tos_cpu_cpsr_restore(state)

#if MICROPY_PY_THREAD
#define MICROPY_EVENT_POLL_HOOK \
    do { \
        extern void mp_handle_pending(bool); \
        mp_handle_pending(true); \
        MP_THREAD_GIL_EXIT(); \
        /* tos_task_delay(1); */ \
        MP_THREAD_GIL_ENTER(); \
    } while (0);
#else
#define MICROPY_EVENT_POLL_HOOK \
    do { \
        extern void mp_handle_pending(bool); \
        mp_handle_pending(true); \
        /* tos_task_delay(1); */ \
    } while (0);
#endif

#if defined(__CC_ARM)
// #define MICROPY_GCREGS_SETJMP (1)
#undef __GNUC__
#undef __arm__
#undef __thumb__
#undef __thumb2__
#endif

#include <alloca.h>

#define MICROPY_PY_SYS_PLATFORM                     "TencentOS-tiny"

#define MP_STATE_PORT MP_STATE_VM

#define MICROPY_PORT_ROOT_POINTERS \
    const char *readline_hist[8]; \
    struct _machine_uart_obj_t *stdio_uart; \
    struct _machine_timer_obj_t *machine_timer_obj_head; \













