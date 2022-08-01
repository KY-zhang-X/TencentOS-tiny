#ifndef _VFS_TOS_H_
#define _VFS_TOS_H_

#include "py/obj.h"

extern const byte vfs_err_to_errno_table[22];
extern const mp_obj_type_t mp_type_vfs_tos;
extern const mp_obj_type_t mp_type_vfs_tos_fileio;
extern const mp_obj_type_t mp_type_vfs_tos_textio;

mp_obj_t mp_vfs_tos_file_open(const mp_obj_type_t *type, mp_obj_t file_in, mp_obj_t mode_in);

#endif /* _VFS_TOS_H_ */
