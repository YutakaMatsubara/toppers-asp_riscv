/* This file is generated from prc_rename.def by genrename. */

/* This file is included only when prc_rename.h has been included. */
#ifdef TOPPERS_PRC_RENAME_H
#undef TOPPERS_PRC_RENAME_H

/*
 *  prc_config.c
 */
#undef prc_initialize
#undef prc_terminate
#undef handle_trap
#undef m_interrupt_handlers
#undef lock_flag
#undef inest_lvl
#undef kernel_mie

/*
 *  prc_support.S
 */
#undef dispatch
#undef start_dispatch
#undef exit_and_dispatch
#undef call_exit_kernel
#undef start_r
#undef trap_entry
#undef trap_nest

#ifdef TOPPERS_LABEL_ASM

/*
 *  prc_config.c
 */
#undef _prc_initialize
#undef _prc_terminate
#undef _handle_trap
#undef _m_interrupt_handlers
#undef _lock_flag
#undef _inest_lvl
#undef _kernel_mie

/*
 *  prc_support.S
 */
#undef _dispatch
#undef _start_dispatch
#undef _exit_and_dispatch
#undef _call_exit_kernel
#undef _start_r
#undef _trap_entry
#undef _trap_nest

#endif /* TOPPERS_LABEL_ASM */


#endif /* TOPPERS_PRC_RENAME_H */
