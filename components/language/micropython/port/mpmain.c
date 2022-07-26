#include "py/compile.h"
#include "py/gc.h"
#include "py/mperrno.h"
#include "py/stackctrl.h"
#include "py/builtin.h"
#include "shared/runtime/gchelper.h"
#include "shared/runtime/pyexec.h"
#include "tos_k.h"

#define MP_HEAP_SIZE        (4 * 1024)

// MicroPython GC heap
__STATIC__ char *heap;

int mp_main(void) 
{
    // Initialise the MicroPython runtime
    mp_stack_ctrl_init();

    // mp_shell_init(MP_SHELL_BUF_SIZE, HAL_UART_PORT_2);

    if (!heap) {
        heap = (char *)tos_mmheap_alloc(MP_HEAP_SIZE);
        if (!heap) {
            return -1;
        }
    }
    gc_init(heap, heap + MP_HEAP_SIZE);
    
    mp_init();
    
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
    // Deinitialise the runtime.
    gc_sweep_all();
    // tos_mmheap_free(heap);

    mp_deinit();

    // mp_shell_deinit();

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
		uintptr_t sp = (uint32_t)tos_task_curr_task_get()->sp;
    gc_collect_root((void **)sp, ((uintptr_t)MP_STATE_THREAD(stack_top) - (uintptr_t)sp) / sizeof(uintptr_t));
    gc_collect_end();
}

// There is no filesystem so stating returns noting
mp_import_stat_t mp_import_stat(const char *path) {
    return MP_IMPORT_STAT_NO_EXIST;
}

mp_lexer_t *mp_lexer_new_from_file(const char *filename) {
    mp_raise_OSError(MP_ENOENT);
}
