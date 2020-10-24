/*
 *  TOPPERS/ASP Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      Advanced Standard Profile Kernel
 * 
 *  Copyright (C) 2000-2003 by Embedded and Real-Time Systems Laboratory
 *                              Toyohashi Univ. of Technology, JAPAN
 *  Copyright (C) 2005-2010 by Embedded and Real-Time Systems Laboratory
 *              Graduate School of Information Science, Nagoya Univ., JAPAN
 *  Copyright (C) 2017-2019 by TOPPERS PROJECT Educational Working Group.
 * 
 *  �嵭����Ԥϡ��ʲ���(1)��(4)�ξ������������˸¤ꡤ�ܥ��եȥ���
 *  �����ܥ��եȥ���������Ѥ�����Τ�ޤࡥ�ʲ�Ʊ���ˤ���ѡ�ʣ������
 *  �ѡ������ۡʰʲ������ѤȸƤ֡ˤ��뤳�Ȥ�̵���ǵ������롥
 *  (1) �ܥ��եȥ������򥽡��������ɤη������Ѥ�����ˤϡ��嵭������
 *      ��ɽ�����������Ѿ�浪��Ӳ�����̵�ݾڵ��꤬�����Τޤޤη��ǥ���
 *      ����������˴ޤޤ�Ƥ��뤳�ȡ�
 *  (2) �ܥ��եȥ������򡤥饤�֥������ʤɡ�¾�Υ��եȥ�������ȯ�˻�
 *      �ѤǤ�����Ǻ����ۤ�����ˤϡ������ۤ�ȼ���ɥ�����ȡ�����
 *      �ԥޥ˥奢��ʤɡˤˡ��嵭�����ɽ�����������Ѿ�浪��Ӳ���
 *      ��̵�ݾڵ����Ǻܤ��뤳�ȡ�
 *  (3) �ܥ��եȥ������򡤵�����Ȥ߹���ʤɡ�¾�Υ��եȥ�������ȯ�˻�
 *      �ѤǤ��ʤ����Ǻ����ۤ�����ˤϡ����Τ����줫�ξ�����������
 *      �ȡ�
 *    (a) �����ۤ�ȼ���ɥ�����ȡ����Ѽԥޥ˥奢��ʤɡˤˡ��嵭����
 *        �ɽ�����������Ѿ�浪��Ӳ�����̵�ݾڵ����Ǻܤ��뤳�ȡ�
 *    (b) �����ۤη��֤��̤�������ˡ�ˤ�äơ�TOPPERS�ץ������Ȥ�
 *        ��𤹤뤳�ȡ�
 *  (4) �ܥ��եȥ����������Ѥˤ��ľ��Ū�ޤ��ϴ���Ū�������뤤���ʤ�»
 *      ������⡤�嵭����Ԥ����TOPPERS�ץ������Ȥ����դ��뤳�ȡ�
 *      �ޤ����ܥ��եȥ������Υ桼���ޤ��ϥ���ɥ桼������Τ����ʤ���
 *      ͳ�˴�Ť����ᤫ��⡤�嵭����Ԥ����TOPPERS�ץ������Ȥ�
 *      ���դ��뤳�ȡ�
 * 
 *  �ܥ��եȥ������ϡ�̵�ݾڤ��󶡤���Ƥ����ΤǤ��롥�嵭����Ԥ�
 *  ���TOPPERS�ץ������Ȥϡ��ܥ��եȥ������˴ؤ��ơ�����λ�����Ū
 *  ���Ф���Ŭ������ޤ�ơ������ʤ��ݾڤ�Ԥ�ʤ����ޤ����ܥ��եȥ���
 *  �������Ѥˤ��ľ��Ū�ޤ��ϴ���Ū�������������ʤ�»���˴ؤ��Ƥ⡤��
 *  ����Ǥ�����ʤ���
 * 
 *  $Id: prc_config.h 2013 2019-09-18 21:29:10Z roi $
 */

/*
 *		�ץ��å���¸�⥸�塼���RISC-V�ѡ�
 *
 *  ���Υ��󥯥롼�ɥե�����ϡ�target_config.h�ʤޤ��ϡ��������饤��
 *  �롼�ɤ����ե�����ˤΤߤ��饤�󥯥롼�ɤ���롥¾�Υե����뤫��
 *  ľ�ܥ��󥯥롼�ɤ��ƤϤʤ�ʤ���
 */

#ifndef TOPPERS_PRC_CONFIG_H
#define TOPPERS_PRC_CONFIG_H

#ifndef TOPPERS_MACRO_ONLY

/*
 *  �ץ��å����ü�̿��Υ���饤��ؿ����
 */
#include "encoding.h"

/*
 *  MCAUSE REGISTER���
 */
#define MCAUSE_CAUSE        0x7FFFFFFF

/*
 *  ���Ѥ��륷�ꥢ��ݡ���ID
 */
#ifndef SIO_PORTID
#define SIO_PORTID		(1)
#endif /* SIO_PORTID */

/*
 *  MACHINE�κ������߿������
 */
#define TMAX_MACHNE_INTNO	32

/*
 *  ����������ƥ����ȥ֥�å������
 */
typedef struct task_context_block {
	void	*sp;		/* �����å��ݥ��� */
	FP		pc;			/* �ץ���५���� */
} TSKCTXB;

#endif /* TOPPERS_MACRO_ONLY */

/*
 *  �����ͥ���٥ޥ������饤�֥��
 *
 *  RISCV/32�Ǥϡ�PLIC�γ���ߥ���å���ۡ���ɤǳ���ߥ�٥��������롥
 */

/*
 *  �����ͥ���٥ޥ����γ���ɽ��������ɽ�����Ѵ�
 */
#define EXT_IPM(iipm)	(-CAST(PRI, (iipm)))		/* ����ɽ�����Ѵ� */
#define INT_IPM(ipm)	CAST(uint16_t, -(ipm))		/* ����ɽ�����Ѵ� */

/*
 *  �����ͥ������������
 */
#define KERNEL_MIE		(MIP_MTIP | MIP_MEIP)


#ifndef TOPPERS_MACRO_ONLY

/*
 *  CPU��å��ե饰�¸��Τ�����ѿ�
 *
 *  �������ѿ��ϡ�CPU��å����֤λ��Τ߽񤭴����Ƥ褤��ΤȤ��롥
 */
extern volatile bool_t			lock_flag;	/* CPU��å��ե饰���ͤ��ݻ������ѿ� */
extern volatile uint16_t		inest_lvl;	/* ����ߥͥ��Ȥ���¸�����ѿ� */
extern volatile unsigned long	kernel_mie;	/* �ǥե���Ȥ�MIE�ͤ���¸�����ѿ� */

/*
 *  TOPPERSɸ�����߽�����ǥ�μ¸�
 *
 *  �����ͥ���٥ޥ����Ȥ��Ƥϡ�mie��MACHINE����ߥ��͡��֥�쥸�����ˤ�
 *  �Ѥ��롥������ߤ�ػߤ��뵡ǽ�Ȥ��ơ�mstatus��MIE��PLIC�γ���ߥ���
 *  �åɤ��������ͥ�������γ���ߤ򥵥ݡ��Ȥ��뤿�ᡤ������CPU��å�
 *  �Τ�����Ѥ��ʤ���
 *  PLIC�γ���ߥ���åɤǤϡ�MIT�γ���ߥ�å����Ǥ��ʤ����Ȥ⡢
 *  ��������Ȥ�����ͳ�Ǥ��롥
 *
 *  CPU��å����֤������������ѿ�(lock_flag)���Ѱդ��롥
 *  �����ƥॹ���å��Υͥ��ȴ������ѿ�(inest_lvl)���Ѱդ��롥
 *  ��������ߤ������PLIC���Ѥ��뤬�����������PRC�Ǥϴ�������
 *  �������åȥ�٥�Ǵ�����Ԥ���
 */

/*
 *  ����ƥ����Ȥλ���
 *
 *  RISCV�Ǥϡ�����ߥͥ��ȥ�٥�ǥ���ƥ����Ȥ�Ƚ�ꤹ�롥
 */
Inline bool_t
sense_context(void)
{
	return inest_lvl != 0;
}

#endif /* TOPPERS_MACRO_ONLY */

/*
 *  �㳰�ե졼��Υ��ե��å�
 */
#define P_EXCINF_OFFSET_MSTATUS     0x00
#define P_EXCINF_OFFSET_PC          0x01
#define P_EXCINF_OFFSET_MCAUSE		0x02
#define P_EXCONF_OFFSET_MIE         0x03
#define P_EXCONF_OFFSET_SP          0x04


#ifndef TOPPERS_MACRO_ONLY

/*
 *  MACHINE����ߤζػ�
 *
 *  ���������ǻ��Ѥ��뤿�������
 */
Inline void
dis_intm(void)
{
	clear_csr(mstatus, MSTATUS_MIE);
}

/*
 *  MACHINE����ߤε���
 *
 *  ���������ǻ��Ѥ��뤿�������
 */
Inline void
ena_intm(void)
{
	set_csr(mstatus, MSTATUS_MIE);
}

/*
 *  CPU��å����֤ؤΰܹ�
 *
 *  mie��MACHINE����ߥ��͡��֥�쥸�����ˤ򡤥����ͥ�����������
 *  ���ޥ������뤳�Ȥ�CPU��å����֤����ꤹ�롥
 *  �ޤ���lock_flag��true�ˤ��롥
 *
 *  ���δؿ��ϡ�CPU��å����֡�lock_flag��true�ξ��֡ˤǸƤФ�뤳�Ȥ�
 *  �ʤ���Τ����ꤷ�Ƥ��롥
 */
Inline void
x_lock_cpu(void)
{
	clear_csr(mie, KERNEL_MIE);
	lock_flag = true;
}

#define t_lock_cpu()	x_lock_cpu()
#define i_lock_cpu()	x_lock_cpu()

/*
 *  CPU��å����֤β��
 *
 *  lock_flag��false�ˤ���mie��MACHINE����ߥ��͡��֥�쥸��������Ρ�
 *  ���͡��֥������Ԥ���
 *
 *  ���δؿ��ϡ�CPU��å����֡�lock_flag��true�ξ��֡ˤǤΤ߸ƤФ���
 *  �Τ����ꤷ�Ƥ��롥
 */
Inline void
x_unlock_cpu(void)
{
	lock_flag = false;
	set_csr(mie, kernel_mie);
}

#define t_unlock_cpu()	x_unlock_cpu()
#define i_unlock_cpu()	x_unlock_cpu()

/*
 *  CPU��å����֤λ���
 */
Inline bool_t
x_sense_lock(void)
{
	return(lock_flag);
}

#define t_sense_lock()	x_sense_lock()
#define i_sense_lock()	x_sense_lock()

/*
 *  chg_ipm��ͭ���ʳ����ͥ���٤��ϰϤ�Ƚ��
 */
#define VALID_INTPRI_CHGIPM(intpri) \
				(TMIN_INTPRI <= (intpri) && (intpri) <= TMAX_INTPRI)

/*
 * �ʥ�ǥ��Ρ˳����ͥ���٥ޥ���������
 *
 *  CPU��å��ե饰�����ꥢ����Ƥ�����ϡ��ϡ��ɥ������γ����ͥ���٥�
 *  ���������ꤹ�롥(mit�����ꤷ�Ƥ��ʤ�)
 */
Inline void
x_set_ipm(PRI intpri)
{
	set_ithreshold(INT_IPM(intpri));
}

#define t_set_ipm(intpri)	x_set_ipm(intpri)
#define i_set_ipm(intpri)	x_set_ipm(intpri)

/*
 * �ʥ�ǥ��Ρ˳����ͥ���٥ޥ����λ���
 *
 *  CPU��å��ե饰�����ꥢ����Ƥ�����ϥϡ��ɥ������γ����ͥ���٥�
 *  �����򻲾Ȥ��롥
 */
Inline PRI
x_get_ipm(void)
{
	return(EXT_IPM(current_ithreshold()));
}

#define t_get_ipm()		x_get_ipm()
#define i_get_ipm()		x_get_ipm()

/*
 *  �ǹ�ͥ���̥������ؤΥǥ����ѥå���prc_support.S��
 *
 *  dispatch�ϡ�����������ƥ����Ȥ���ƤӽФ��줿�����ӥ������������
 *  ��ƤӽФ��٤���Τǡ�����������ƥ����ȡ�CPU��å����֡��ǥ����ѥ�
 *  �����ľ��֡��ʥ�ǥ��Ρ˳����ͥ���٥ޥ�����������֤ǸƤӽФ���
 *  ����Фʤ�ʤ���
 */
extern void	dispatch(void);

/*
 *  �ǥ����ѥå����ư��ϡ�prc_support.S��
 *
 *  start_dispatch�ϡ������ͥ뵯ư���˸ƤӽФ��٤���Τǡ����٤Ƥγ��
 *  �ߤ�ػߤ������֡ʳ���ߥ�å����֤�Ʊ���ξ��֡ˤǸƤӽФ��ʤ����
 *  �ʤ�ʤ���
 */
extern void	start_dispatch(void) NoReturn;

/*
 *  ���ߤΥ���ƥ����Ȥ�ΤƤƥǥ����ѥå���prc_support.S��
 *
 *  exit_and_dispatch�ϡ�ext_tsk����ƤӽФ��٤���Τǡ�����������ƥ�
 *  ���ȡ�CPU��å����֡��ǥ����ѥå����ľ��֡��ʥ�ǥ��Ρ˳����ͥ��
 *  �٥ޥ�����������֤ǸƤӽФ��ʤ���Фʤ�ʤ���
 */
extern void	exit_and_dispatch(void) NoReturn;

/*
 *  �����ͥ�ν�λ�����θƽФ���prc_support.S��
 *
 *  call_exit_kernel�ϡ������ͥ�ν�λ���˸ƤӽФ��٤���Τǡ��󥿥���
 *  ����ƥ����Ȥ��ڤ괹���ơ������ͥ�ν�λ������exit_kernel�ˤ�Ƥӽ�
 *  ����
 */
extern void call_exit_kernel(void) NoReturn;

/*
 *  MACHINE����ߥȥ�å״ؿ� ��prc_support.S��
 *
 *  trap_entry�Ϻǽ��MACHINE����ߤ��������ؿ���
 */
extern void trap_entry(void);

/*
 *  MACHINE����ߥͥ��ȥȥ�å״ؿ� ��prc_support.S��
 *
 *  trap_entry�ϥͥ��Ȼ���MACHINE����ߤ��������ؿ���
 */
extern void trap_nest(void);


/*
 *  ����������ƥ����Ȥν����
 *
 *  ���������ٻ߾��֤���¹ԤǤ�����֤˰ܹԤ�����˸ƤФ�롥���λ���
 *  �ǥ����å��ΰ��ȤäƤϤʤ�ʤ���
 *
 *  activate_context�򡤥���饤��ؿ��ǤϤʤ��ޥ�������Ȥ��Ƥ���Τϡ�
 *  ���λ����Ǥ�TCB���������Ƥ��ʤ�����Ǥ��롥
 */
extern void	start_r(void);

#define activate_context(p_tcb)											\
{																		\
	(p_tcb)->tskctxb.sp = (void *)((char *)((p_tcb)->p_tinib->stk)		\
										+ (p_tcb)->p_tinib->stksz);		\
	(p_tcb)->tskctxb.pc = (void *) start_r;								\
}

/*
 *  calltex�ϻ��Ѥ��ʤ�
 */
#define OMIT_CALLTEX

/*
 *  �㳰�٥����ơ��֥�ι�¤�����
 */
typedef struct exc_vector_entry {
	FP		exc_handler;		/* �㳰�ϥ�ɥ�ε�ư���� */
} EXCVE;

/*
 *  MACHINE����ߥϥ�ɥ��ΰ�Υơ��֥�
 */
extern volatile EXCVE m_interrupt_handlers[TMAX_MACHNE_INTNO];

/*
 *  CPU�㳰�ϥ�ɥ������
 *
 *  �٥��ȥ��ֹ�excno��CPU�㳰�ϥ�ɥ�ν��������������Ϥ�exc_entry����
 *  �ꤹ�롥
 */
Inline void
x_define_exc(EXCNO excno, FP exc_entry)
{
	m_interrupt_handlers[excno].exc_handler = exc_entry;
}

/*
 *  MACHINE����ߥϥ�ɥ������
 */
Inline void
x_machine_inh(INHNO inhno, FP int_entry)
{
	m_interrupt_handlers[inhno+16].exc_handler = int_entry;
}

/*
 *  CPU�㳰�ϥ�ɥ�ν���������������
 *
 *  CPU�㳰�ϥ�ɥ�����Ϥ�A1�ˡ�CPU�㳰�ϥ�ɥ��ֹ��D1������ơ�
 *  exchdr_entry��ʬ�����롥����ߥϥ�ɥ�ν�����������Ʊ�ͤˡ�CPU�㳰
 *  �ϥ�ɥ����CPU�㳰�ϥ�ɥ��ƤӽФ�������Ÿ��������ˡ�⤢�뤬��Ÿ
 *  ������������Ƥ�ʣ���Ǥ��뤿�ᡤ���Ѥ��Ƥ��ʤ���
 */

/*
 *  CPU�㳰�ϥ�ɥ�ν����������Υ�٥����ޥ���
 */
#define EXC_ENTRY(excno, exchdr)	_kernel_##exchdr##_##excno

/*
 *  CPU�㳰�ϥ�ɥ�ν���������
 */
#if defined(__riscv64)
#define EXCHDR_ENTRY(excno, excno_num, exchdr) \
extern void _kernel_##exchdr##_##excno(void *sp); \
asm(".text							\n" \
"_kernel_" #exchdr "_" #excno ":	\n" \
"	addi sp, sp, -32				\n"	 /* ��¸�ΰ����� */ \
"	sd ra, 24(sp)					\n"	 /* return address�򥻡��� */ \
"	csrsi mstatus, 8				\n"	 /* ����ߤ����(MSTATUS_MIE) */ \
"	mv a0, a1						\n"  /* stack pointer��a0�� */ \
"	jal " #exchdr "					\n"	 /* exchdr��ʬ�� */ \
"	ld ra, 24(sp)					\n"	 /* return address��ꥹ�ȥ� */ \
"	csrci mstatus, 8				\n"	 /* ����ߤ�ػ�(MSTATUS_MIE) */ \
"	addi sp, sp, 32					\n"	 /* ��¸�ΰ���� */ \
"	ret								\n");/* �꥿���� */
#else
#define EXCHDR_ENTRY(excno, excno_num, exchdr) \
extern void _kernel_##exchdr##_##excno(void *sp); \
asm(".text							\n" \
"_kernel_" #exchdr "_" #excno ":	\n" \
"	addi sp, sp, -16				\n"	 /* ��¸�ΰ����� */ \
"	sw ra, 12(sp)					\n"	 /* return address�򥻡��� */ \
"	csrsi mstatus, 8				\n"	 /* ����ߤ����(MSTATUS_MIE) */ \
"	mv a0, a1						\n"  /* stack pointer��a0�� */ \
"	jal " #exchdr "					\n"	 /* exchdr��ʬ�� */ \
"	lw ra, 12(sp)					\n"	 /* return address��ꥹ�ȥ� */ \
"	csrci mstatus, 8				\n"	 /* ����ߤ�ػ�(MSTATUS_MIE) */ \
"	addi sp, sp, 16					\n"	 /* ��¸�ΰ���� */ \
"	ret								\n");/* �꥿���� */
#endif

/*
 *  CPU�㳰��ȯ���������Υ���ƥ����Ȥλ���
 *
 *  CPU�㳰��ȯ���������Υ���ƥ����Ȥ�������������ƥ����Ȥλ���false��
 *  �����Ǥʤ�����true���֤���
 */
Inline bool_t
exc_sense_context(void *p_excinf)
{
	return inest_lvl > 1;
}

/*
 *  CPU�㳰��ȯ���������Υ���ƥ����Ȥȳ���ߤΥޥ������֤λ���
 *
 *  CPU�㳰��ȯ���������Υ����ƥ���֤��������ͥ�¹���Ǥʤ�����������
 *  ��ƥ����ȤǤ��ꡤ������ߥ�å����֤Ǥʤ���CPU��å����֤Ǥʤ�����
 *  ����ͥ���٥ޥ�����������֤Ǥ������true�������Ǥʤ�����false���֤�
 *  ��CPU�㳰�������ͥ�������γ���߽������ȯ���������ˤ�false����
 *  ���ˡ�
 *
 *  CPU�㳰��ȯ����������mie��MACHINE����ߥ��͡��֥�쥸�����ˤ������
 *  ��Ǥʤ��ǡ������ͥ�¹���Ǥʤ����ȡ�������ߥ�å����֤Ǥʤ�����
 *  ��CPU��å����֤Ǥʤ����ȡ������ͥ���٥ޥ�����������֤Ǥ��뤳�Ȥ�
 *  4�Ĥξ�������å����뤳�Ȥ��Ǥ����CPU�㳰��ȯ����������lock_flag
 *  �򻲾Ȥ���ɬ�פϤʤ��ˡ�
 */
Inline bool_t
exc_sense_intmask(void *p_excinf)
{
	return(!exc_sense_context(p_excinf)
					&& ((read_csr(mie) & KERNEL_MIE) != 0));
}


/*
 *  �ץ��å���¸�ν����
 */
extern void	prc_initialize(void);

/*
 *  �ץ��å���¸�ν�λ������
 */
extern void	prc_terminate(void);

/*
 *  C�����٥� MACHINE����ߥϥ�ɥ�
 */
extern uint32_t handle_trap(unsigned long mcause, void *p_excinf);

#endif /* TOPPERS_MACRO_ONLY */
#endif /* TOPPERS_PRC_CONFIG_H */
