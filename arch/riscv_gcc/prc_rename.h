/* This file is generated from prc_rename.def by genrename. */

#ifndef TOPPERS_PRC_RENAME_H
#define TOPPERS_PRC_RENAME_H

/*
 *  prc_config.c
 */
#define prc_initialize				_kernel_prc_initialize
#define prc_terminate				_kernel_prc_terminate
#define handle_trap					_kernel_handle_trap
#define m_interrupt_handlers		_kernel_m_interrupt_handlers
#define lock_flag					_kernel_lock_flag
#define inest_lvl					_kernel_inest_lvl

/*
 *  prc_support.S
 */
#define dispatch					_kernel_dispatch
#define start_dispatch				_kernel_start_dispatch
#define exit_and_dispatch			_kernel_exit_and_dispatch
#define call_exit_kernel			_kernel_call_exit_kernel
#define start_r						_kernel_start_r
#define trap_entry					_kernel_trap_entry
#define trap_nest					_kernel_trap_nest

#ifdef TOPPERS_LABEL_ASM

/*
 *  prc_config.c
 */
#define _prc_initialize				__kernel_prc_initialize
#define _prc_terminate				__kernel_prc_terminate
#define _handle_trap				__kernel_handle_trap
#define _m_interrupt_handlers		__kernel_m_interrupt_handlers
#define _lock_flag					__kernel_lock_flag
#define _inest_lvl					__kernel_inest_lvl

/*
 *  prc_support.S
 */
#define _dispatch					__kernel_dispatch
#define _start_dispatch				__kernel_start_dispatch
#define _exit_and_dispatch			__kernel_exit_and_dispatch
#define _call_exit_kernel			__kernel_call_exit_kernel
#define _start_r					__kernel_start_r
#define _trap_entry					__kernel_trap_entry
#define _trap_nest					__kernel_trap_nest

#endif /* TOPPERS_LABEL_ASM */


#endif /* TOPPERS_PRC_RENAME_H */
