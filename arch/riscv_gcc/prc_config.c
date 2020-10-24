/*
 *  TOPPERS/ASP Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      Advanced Standard Profile Kernel
 * 
 *  Copyright (C) 2000-2003 by Embedded and Real-Time Systems Laboratory
 *                              Toyohashi Univ. of Technology, JAPAN
 *  Copyright (C) 2005-2009 by Embedded and Real-Time Systems Laboratory
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
 *  @(#) $Id: prc_config.c 1430 2019-09-20 18:50:51Z roi $
 */

/*
 *		�ץ��å���¸�⥸�塼���RISC-V�ѡ�
 */

#include "kernel_impl.h"
#include "check.h"
#include "task.h"

/*
 *  CPU��å��ե饰�¸��Τ�����ѿ�
 */
volatile bool_t			lock_flag;	/* CPU��å��ե饰���ͤ��ݻ������ѿ� */
volatile uint16_t		inest_lvl;	/* ����ߥͥ��Ȥ���¸�����ѿ� */
volatile unsigned long	kernel_mie;	/* �ǥե���Ȥ�MIE�ͤ���¸�����ѿ� */
static unsigned long	saved_trap;	/* MACHINE TRAP�ǡ�������¸�ѿ� */

/*
 *  MACHINE����ߥϥ�ɥ��ΰ�Υơ��֥�
 */
volatile EXCVE m_interrupt_handlers[TMAX_MACHNE_INTNO];


#ifndef OMIT_DEFAULT_INT_HANDLER
/*
 *  ̤��Ͽ�γ���ߤ�ȯ���������˸ƤӽФ����
 */
static void
default_int_handler(unsigned long mcause, void *p_excinf)
{
	unsigned long mstatus = *(((uintptr_t*)p_excinf) + P_EXCINF_OFFSET_MSTATUS);
	uintptr_t     pc      = *(((uintptr_t*)p_excinf) + P_EXCINF_OFFSET_PC);
	unsigned long excno   = mcause & MCAUSE_CAUSE;

	if((long)mcause < 0)
		excno += TMAX_MACHNE_INTNO / 2;
	syslog(LOG_EMERG, "\nUnregistered Interrupt occurs.");
	syslog(LOG_EMERG, "Excno = 0x%02X, PC = 0x%X, mstatus = 0x%X, p_excinf = 0x%X",
		   excno, pc, mstatus, p_excinf);

	target_exit();
}
#endif /* OMIT_DEFAULT_INT_HANDLER */

/*
 *  �ץ��å���¸�ν����
 */
void
prc_initialize(void)
{
	extern void	software_init_hook(void);
	void (*volatile fp)(void) = software_init_hook;
	int  i;

	/*
	 *  software_init_hook�ؤΥݥ��󥿤򡤰�övolatile����Τ���fp����
	 *  �����Ƥ���Ȥ��Τϡ�0�Ȥ���Ӥ���Ŭ���Ǻ������ʤ��褦�ˤ��뤿
	 *  ��Ǥ��롥
	 */
	if (fp != 0) {
		(*fp)();
	}

	/*
	 *  CPU��å��ե饰�¸��Τ�����ѿ��ν����
	 */
	lock_flag  = true;
	kernel_mie = KERNEL_MIE;
	clear_csr(mie, KERNEL_MIE);
	set_csr(mie, MIP_MSIP);
	inest_lvl  = 0;

	/*
	 *  �㳰�٥����ơ��֥�ν����
	 */
#ifndef OMIT_DEFAULT_INT_HANDLER
	for(i = 0 ; i < TMAX_MACHNE_INTNO ; i++){
		m_interrupt_handlers[i].exc_handler = (FP)default_int_handler;
	}
#endif
	saved_trap = read_csr(mtvec);
	write_csr(mtvec, &trap_entry);
	ena_intm();

	/*
	 *  FPU��ĥ�ν����
	 */
	if(read_csr(misa) & (1 << ('F' - 'A'))){
		set_csr(mstatus, MSTATUS_FS);	/* FPU���ꡢâ������ߤϥ��ݡ��Ȥ��ʤ� */
		write_csr(fcsr, 0);				/* �饦��ǥ��󥰥⡼������ */
	}

	(void)(i);
}

/*
 *  �ץ��å���¸�ν�λ����
 */
void
prc_terminate(void)
{
	extern void	software_term_hook(void);
	void (*volatile fp)(void) = software_term_hook;

	/*
	 *  software_term_hook�ؤΥݥ��󥿤򡤰�övolatile����Τ���fp����
	 *  �����Ƥ���Ȥ��Τϡ�0�Ȥ���Ӥ���Ŭ���Ǻ������ʤ��褦�ˤ��뤿
	 *  ��Ǥ��롥
	 */
	if (fp != 0) {
		(*fp)();
	}

	write_csr(mtvec, saved_trap);
}

/*
 *  C�����٥� MACHINE����ߥϥ�ɥ�
 */
uint32_t
handle_trap(unsigned long mcause, void *p_excinf)
{
	uint32_t intno = mcause & MCAUSE_CAUSE;
	void     (*func)(unsigned long, void *);

	if(inest_lvl++ == 0)
		write_csr(mtvec, &trap_nest);
	if((long)mcause < 0)
		intno += TMAX_MACHNE_INTNO / 2;
	if(intno < TMAX_MACHNE_INTNO){
		func = (void(*)(unsigned long, void *))m_interrupt_handlers[intno].exc_handler;
		if(func != NULL)
			func(mcause, p_excinf);
	}
	else{
		syslog_1(LOG_EMERG, "Irrigal machine Exception mcause = %08X", (int)intno);
	}
	if(--inest_lvl == 0)
		write_csr(mtvec, &trap_entry);
	return inest_lvl;
}

/*
 *  CPU�㳰��ȯ�������Υ�����
 *
 *  CPU�㳰�ϥ�ɥ���椫�顤CPU�㳰����ݥ��󥿡�p_excinf�ˤ�����Ȥ�
 *  �ƸƤӽФ����Ȥǡ�CPU�㳰��ȯ�������򥷥��ƥ���˽��Ϥ��롥
 */
#ifdef SUPPORT_XLOG_SYS

void
xlog_sys(void *p_excinf)
{
	unsigned long *excsp = (unsigned long *) p_excinf;

	syslog_0(LOG_ERROR, "CPU Exception Information:");
	syslog_4(LOG_ERROR, "mstatus = %08x PC = %x mcause = %x STACK = %x",
				*((excsp + P_EXCINF_OFFSET_MSTATUS)), 
				*((excsp + P_EXCINF_OFFSET_PC)),
				*((excsp + P_EXCINF_OFFSET_MCAUSE)),
				((unsigned long)excsp + 19 * 4));
	syslog_1(LOG_ERROR, "p_excinf = %x", (unsigned long)excsp);
}

#endif /* SUPPORT_XLOG_SYS */
