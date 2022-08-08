#include "py/mpconfig.h"
#include "py/mpthread.h"
#include "py/compile.h"
#include "py/gc.h"
#include "py/mperrno.h"
#include "py/stackctrl.h"
#include "py/builtin.h"
#include "shared/runtime/gchelper.h"
#include "shared/runtime/pyexec.h"

#if MICROPY_VFS_TOS
#include "extmod/vfs.h"
#include "vfs_tos.h"
#endif

#include "tos_k.h"

#define MP_HEAP_SIZE        (8 * 1024)

// MicroPython GC heap
__STATIC__ char *heap = K_NULL;
__STATIC__ void *stack_top = K_NULL;

int mp_main(void) 
{
    // Initialise the MicroPython runtime
    // mp_stack_ctrl_init();
    volatile int stack_dummy;
    #if MICROPY_PY_THREAD
    mp_thread_init();
    #endif
    stack_top = (void *)&stack_dummy;
    mp_stack_set_top(stack_top);
    mp_stack_set_limit(tos_task_curr_task_get()->stk_size - MP_THREAD_STACK_LIMIT_MARGIN);

    if (!heap) {
        heap = (char *)tos_mmheap_alloc(MP_HEAP_SIZE);
        if (!heap) {
            return -1;
        }
    }
    gc_init(heap, heap + MP_HEAP_SIZE);
    
    mp_init();
    
    #if MICROPY_VFS_TOS
    {
        mp_obj_t root = mp_obj_new_str("/fs", 3);
        mp_obj_t args[2] = {
            mp_type_vfs_tos.make_new(&mp_type_vfs_tos, 1, 0, &root),
            MP_OBJ_NEW_QSTR(MP_QSTR__slash_),
        };
        mp_vfs_mount(2, args, (mp_map_t *)&mp_const_empty_map);
        MP_STATE_VM(vfs_cur) = MP_STATE_VM(vfs_mount_table);
    }
    #endif

    // Start a normal REPL; will exit when ctrl-D is entered on a blank line.
    for (;;) {
        if (pyexec_mode_kind == PYEXEC_MODE_RAW_REPL) {
            if (pyexec_raw_repl() != 0) {
                break;
            }
        } else {
            if (pyexec_friendly_repl() != 0) {
                break;
            }
        }
    }
    mp_printf(&mp_plat_print, "exit repl\n");

    #if MICROPY_PY_THREAD
    mp_thread_deinit();
    #endif
    
    // Deinitialise the runtime.
    gc_sweep_all();

    mp_deinit();

    return 0;
}

// Handle uncaught exceptions (should never be reached in a correct C implemetation).
void nlr_jump_fail(void *val) {
    mp_obj_print_exception(&mp_plat_print, MP_OBJ_FROM_PTR(val));
    for (;;) {
        tos_task_delay(500);
    }
}

// Do a garbage collection cycle
void gc_collect(void) {
    gc_collect_start();

    uintptr_t stack_base = (uint32_t)tos_task_curr_task_get()->stk_base;
    gc_collect_root((void **)stack_base, ((uintptr_t)MP_STATE_THREAD(stack_top) - (uintptr_t)stack_base) / sizeof(uintptr_t));
    
    // trace root pointers from any threads
    #if MICROPY_PY_THREAD
    mp_thread_gc_others();
    #endif

    gc_collect_end();
}

#if !(MICROPY_VFS)
// There is no filesystem so stating returns noting
mp_import_stat_t mp_import_stat(const char *path) {
    return MP_IMPORT_STAT_NO_EXIST;
}
#endif /* MICROPY_VFS */

#if !(MICROPY_READER_VFS)
mp_lexer_t *mp_lexer_new_from_file(const char *filename) {
    mp_raise_OSError(MP_ENOENT);
}

#if MICROPY_DEBUG_VERBOSE
#include <stdio.h>
#include <stdarg.h>
int DEBUG_printf(const char *format, ...)
{
    static char log_buf[512];
    va_list args;

    /* args point to the first variable parameter */
    va_start(args, format);
    /* must use vprintf to print */
    vsprintf(log_buf, format, args);
    printf("%s", log_buf);
    va_end(args);

    return 0;
}
#endif
