/* This file is generated from target_rename.def by genrename. */

#ifndef TOPPERS_TARGET_RENAME_H
#define TOPPERS_TARGET_RENAME_H

/*
 *  kernel_cfg.c
 */
#define vector_table				_kernel_vector_table
#define bitpat_cfgint				_kernel_bitpat_cfgint

/*
 *  target_config.c
 */
#define target_initialize			_kernel_target_initialize
#define target_exit					_kernel_target_exit
#define default_plic_handler		_kernel_default_plic_handler
#define x_config_int				_kernel_x_config_int

/*
 *  trace_config.c
 */
#define log_dsp_enter				_kernel_log_dsp_enter
#define log_dsp_leave				_kernel_log_dsp_leave
#define log_inh_enter				_kernel_log_inh_enter
#define log_inh_leave				_kernel_log_inh_leave
#define log_exc_enter				_kernel_log_exc_enter
#define log_exc_leave				_kernel_log_exc_leave


#ifdef TOPPERS_LABEL_ASM

/*
 *  kernel_cfg.c
 */
#define _vector_table				__kernel_vector_table
#define _bitpat_cfgint				__kernel_bitpat_cfgint

/*
 *  target_config.c
 */
#define _target_initialize			__kernel_target_initialize
#define _target_exit				__kernel_target_exit
#define _default_plic_handler		__kernel_default_plic_handler
#define _x_config_int				__kernel_x_config_int

/*
 *  trace_config.c
 */
#define _log_dsp_enter				__kernel_log_dsp_enter
#define _log_dsp_leave				__kernel_log_dsp_leave
#define _log_inh_enter				__kernel_log_inh_enter
#define _log_inh_leave				__kernel_log_inh_leave
#define _log_exc_enter				__kernel_log_exc_enter
#define _log_exc_leave				__kernel_log_exc_leave


#endif /* TOPPERS_LABEL_ASM */

#include "riscv_gcc/prc_rename.h"

#endif /* TOPPERS_TARGET_RENAME_H */
