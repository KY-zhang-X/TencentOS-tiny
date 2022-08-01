#include "tos_k.h"
#include "mpshellport.h"
#include "mpmain.h"
#include "py/builtin.h"

#define MP_USING_VFS 1
#define MP_USING_QSPI_FLASH 1

#if MP_USING_VFS
#include "tos_vfs.h"
#include "ff.h"
#endif /* MP_USING_VFS */

#if MP_USING_QSPI_FLASH
#include "w25qxx.h"
#endif /* MP_USING_QSPI_FLASH */

#define MP_SHELL_BUF_SIZE   (512)
#define MP_TASK_PRIO        (3)
#define MP_TASK_STACK_SIZE  (4 * 1024)

// MicroPython task stack
__STATIC__ k_stack_t mp_task_stack[MP_TASK_STACK_SIZE];
__STATIC__ k_task_t mp_task;

void mp_entry(void *arg) {

    #if MP_USING_QSPI_FLASH
    w25qxx_init();
    w25qxx_memory_mapped();
    #endif /* MP_USING_QSPI_FLASH */
  
    mp_shell_init(MP_SHELL_BUF_SIZE, HAL_UART_PORT_2);

    #if MP_USING_VFS
    extern vfs_blkdev_ops_t sd_dev;
    extern vfs_fs_ops_t fatfs_ops;

    tos_vfs_block_device_register("/dev/sd", &sd_dev);
    tos_vfs_fs_register("fatfs_sd", &fatfs_ops);

    if (tos_vfs_fs_mount("/dev/sd", "/fs", "fatfs_sd") != 0) {
        printf("mount failed!\n");
    }
    #endif /* MP_USING_VFS */
    
    for (;;) {
        mp_main();
        mp_printf(&mp_plat_print, "exit mp_main()\n");
        tos_task_delay(100);
    }
}

void application_entry(void *arg) {
    tos_task_create(&mp_task, "micropython", mp_entry,
                        K_NULL, MP_TASK_PRIO, mp_task_stack,
                        MP_TASK_STACK_SIZE, 0);
}
