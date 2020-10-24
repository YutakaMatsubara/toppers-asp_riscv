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
 *    (b) �����ۤη��֤��̤�������ˡ�ˤ�äơ�TOPPERS�ץ��������Ȥ�
 *        ��𤹤뤳�ȡ�
 *  (4) �ܥ��եȥ����������Ѥˤ��ľ��Ū�ޤ��ϴ���Ū�������뤤���ʤ�»
 *      ������⡤�嵭����Ԥ����TOPPERS�ץ��������Ȥ����դ��뤳�ȡ�
 *      �ޤ����ܥ��եȥ������Υ桼���ޤ��ϥ���ɥ桼������Τ����ʤ���
 *      ͳ�˴�Ť����ᤫ��⡤�嵭����Ԥ����TOPPERS�ץ��������Ȥ�
 *      ���դ��뤳�ȡ�
 * 
 *  �ܥ��եȥ������ϡ�̵�ݾڤ��󶡤���Ƥ����ΤǤ��롥�嵭����Ԥ�
 *  ���TOPPERS�ץ��������Ȥϡ��ܥ��եȥ������˴ؤ��ơ�����λ�����Ū
 *  ���Ф���Ŭ������ޤ�ơ������ʤ��ݾڤ�Ԥ�ʤ����ޤ����ܥ��եȥ���
 *  �������Ѥˤ��ľ��Ū�ޤ��ϴ���Ū�������������ʤ�»���˴ؤ��Ƥ⡤��
 *  ����Ǥ�����ʤ���
 * 
 *  $Id: prc_support.S 2015 2019-09-25 17:48:49Z roi $
 */

/*
 *		�ץ����å���¸�⥸�塼�� ������֥��������RISC-V�ѡ�
 */

#define	TOPPERS_MACRO_ONLY
#include "encoding.h"
#define UINT_C(val)			(val)		/* uint_t�����������ޥ��� */
#define ULONG_C(val)		(val)		/* ulong_t�����������ޥ��� */
#define CAST(type, val)		(val)		/* �����㥹�Ȥ�Ԥ��ޥ��� */
#include "kernel_impl.h"
#include "offset.h"

#if defined(__riscv64)
#define LREG                ld
#define SREG                sd
#define LFREG               fld
#define SFREG               fsd
#define REGSIZE             8
#else
#define LREG                lw
#define SREG                sw
#define LFREG               flw
#define SFREG               fsw
#define REGSIZE             4
#endif

#if defined(USE_FPU) && !defined(__riscv_float_abi_soft)
#define SAVEREG1            27
#define SAVEREG2            42
#define SAVEREG3            26
#else
#define SAVEREG1            15
#define SAVEREG2            22
#define SAVEREG3            14
#endif

/*
 *  �������ǥ����ѥå���
 */
	.text
	.globl dispatch
dispatch:
	/*
	 *  ���Υ롼����ϡ�����������ƥ����ȡ�CPU���å����֡��ǥ����ѥå�
	 *  ���ľ��֡��ʥ�ǥ��Ρ˳����ͥ���٥ޥ�����������֤ǸƤӽФ�
	 *  ��롥
	 */
	addi sp, sp, -SAVEREG1*REGSIZE	/* �쥸������¸�ΰ����� */
	SREG ra, 0*REGSIZE(sp)			/* return���ɥ쥹����¸ */
	SREG gp, 1*REGSIZE(sp)			/* call�襻���֤Υ쥸��������¸ */
	SREG tp, 2*REGSIZE(sp)
	SREG s0, 3*REGSIZE(sp)
	SREG s1, 4*REGSIZE(sp)
	SREG s2, 5*REGSIZE(sp)
	SREG s3, 6*REGSIZE(sp)
	SREG s4, 7*REGSIZE(sp)
	SREG s5, 8*REGSIZE(sp)
	SREG s6, 9*REGSIZE(sp)
	SREG s7, 10*REGSIZE(sp)
	SREG s8, 11*REGSIZE(sp)
	SREG s9, 12*REGSIZE(sp)
	SREG s10, 13*REGSIZE(sp)
	SREG s11, 14*REGSIZE(sp)
#if SAVEREG1 == 27
	SFREG fs0, 15*REGSIZE(sp)
	SFREG fs1, 16*REGSIZE(sp)
	SFREG fs2, 17*REGSIZE(sp)
	SFREG fs3, 18*REGSIZE(sp)
	SFREG fs4, 19*REGSIZE(sp)
	SFREG fs5, 20*REGSIZE(sp)
	SFREG fs6, 21*REGSIZE(sp)
	SFREG fs7, 22*REGSIZE(sp)
	SFREG fs8, 23*REGSIZE(sp)
	SFREG fs9, 24*REGSIZE(sp)
	SFREG fs10, 25*REGSIZE(sp)
	SFREG fs11, 26*REGSIZE(sp)
#endif
	la a1, p_runtsk					/* p_runtsk��A0�� */
	LREG a0, 0(a1)
	SREG sp, TCB_sp(a0)				/* �����������å�����¸ */
	la a1, dispatch_r
	SREG a1, TCB_pc(a0)				/* �¹ԺƳ����Ϥ���¸ */
	j dispatcher

	.globl dispatch_r
dispatch_r:
	LREG ra, 0*REGSIZE(sp)			/* return���ɥ쥹������ */
	LREG gp, 1*REGSIZE(sp)			/* call�襻���֤Υ쥸���������� */
	LREG tp, 2*REGSIZE(sp)
	LREG s0, 3*REGSIZE(sp)
	LREG s1, 4*REGSIZE(sp)
	LREG s2, 5*REGSIZE(sp)
	LREG s3, 6*REGSIZE(sp)
	LREG s4, 7*REGSIZE(sp)
	LREG s5, 8*REGSIZE(sp)
	LREG s6, 9*REGSIZE(sp)
	LREG s7, 10*REGSIZE(sp)
	LREG s8, 11*REGSIZE(sp)
	LREG s9, 12*REGSIZE(sp)
	LREG s10, 13*REGSIZE(sp)
	LREG s11, 14*REGSIZE(sp)
#if SAVEREG1 == 27
	LFREG fs0, 15*REGSIZE(sp)
	LFREG fs1, 16*REGSIZE(sp)
	LFREG fs2, 17*REGSIZE(sp)
	LFREG fs3, 18*REGSIZE(sp)
	LFREG fs4, 19*REGSIZE(sp)
	LFREG fs5, 20*REGSIZE(sp)
	LFREG fs6, 21*REGSIZE(sp)
	LFREG fs7, 22*REGSIZE(sp)
	LFREG fs8, 23*REGSIZE(sp)
	LFREG fs9, 24*REGSIZE(sp)
	LFREG fs10, 25*REGSIZE(sp)
	LFREG fs11, 26*REGSIZE(sp)
#endif
	addi sp, sp, SAVEREG1*REGSIZE	/* �쥸������¸�ΰ����� */
	li a2, TCB_enatex_bit			/* enatex��false�ʤ�꥿���� */
	lbu a1, TCB_enatex(a0)
	sra a1, a1, a2
	andi a1, a1, 1
	beqz a1, dispatch_r_1
	LREG a1, TCB_texptn(a0)			/* texptn��0�ʤ�꥿���� */
	beqz a1, dispatch_r_1
	la a2, ipmflg					/* ipmflg��true�Ǥ����            */
	lw a1, 0(a2)
	bnez a1, call_texrtn			/* �������㳰�����롼����θƽФ� */
dispatch_r_1:
	ret

/*
 *  �ǥ����ѥå����ư��ϡ�prc_support.S��
 */
	.globl start_dispatch
start_dispatch:
	/*
	 *  ���Υ롼����ϡ������ͥ뵯ư���ˡ����٤Ƥγ���ߤ�ػߤ�������
	 * �ʳ���ߥ��å����֤�Ʊ���ˤǸƤӽФ���롥�ޤ�������ߥ⡼�ɡ���
	 *  ����������ƥ����Ȥ�Ʊ���ˤǸƤӽФ���뤳�Ȥ����ꤷ�Ƥ��롥
	 *
	 *  prc_initialize�ǡ�lock_flag��true�ˡ�mie��init_mie��
	 *  �����ͥ�������γ���ߤ���ĺѤߤǡ�CPU���å����֡��ʥ�ǥ��Ρ�
	 *  �����ͥ���٥ޥ�����������֤ˤʤäƤ��롥
	 *  (�����ͥ�������γ���ߤ���Ĥ��Ƥ����ʤ���mtip�����ޤ���ư���ʤ�)
	 *  �ޤ���initialize_task��disdsp��false�˽�������Ƥ��뤿�ᡤ�ǥ�
	 *  ���ѥå����ľ��֤ˤʤäƤ��롥
	 */
	la a0, _kernel_istk				/* STACK�򥫡��ͥ�ISTK�� */
	LREG sp, 0(a0)
	la a0, _kernel_istksz
	LREG a1, 0(a0)
	add sp, sp, a1
	j dispatcher_0

/*
 *  ���ߤΥ���ƥ����Ȥ�ΤƤƥǥ����ѥå�
 */
	.globl exit_and_dispatch
exit_and_dispatch:
	/* �ǥ����ѥå������Ρ�dispatcher�ˤ� */

/*
 *  �ǥ����ѥå�������
 */
dispatcher:
	/*
	 *  ���Υ롼����ϡ�����������ƥ����ȡ�CPU���å����֡��ǥ����ѥå�
	 *  ���ľ��֡��ʥ�ǥ��Ρ˳����ͥ���٥ޥ�����������֤ǸƤӽФ�
	 *  ��롥
	 *
	 *  ���ʤ�����ޥ����⡼�ɡ�lock_flag��true��disdsp��false��dspflg
	 *  ��true��saved_iipm��IIPM_ENAALL�ȤʤäƤ��롥�¹ԺƳ����Ϥؤ⤳
	 *  �ξ��֤Τޤ�ʬ�����롥
	 */
#ifdef LOG_DSP_ENTER
	la a2, p_runtsk					/* p_runtsk��ѥ�᡼���� */
	LREG a0, 0(a2)
	jal log_dsp_enter
#endif /* LOG_DSP_ENTER */
dispatcher_0:
	la a1, p_schedtsk				/* p_schedtsk��p_runtsk�� */
	LREG a0, 0(a1)
	la a2, p_runtsk
	SREG a0, 0(a2)
	beqz a0, dispatcher_1			/* p_runtsk��NULL�ʤ�dispatcher_1�� */
	LREG sp, TCB_sp(a0)				/* �����������å������� */
#ifdef LOG_DSP_LEAVE
	jal log_dsp_leave
	la a2, p_runtsk					/* p_runtsk������ */
	LREG a0, 0(a2)
#endif /* LOG_DSP_LEAVE */
	LREG a1, TCB_pc(a0)				/* �¹ԺƳ����Ϥ�ʬ�� */
	jr a1
dispatcher_1:
	/*
	 *  CPU���å����֤�����������򤹤롥
	 */
	csrr a5, mie					/* mie��a5����¸ */
	la a3, lock_flag				/* CPU���å�������֤� */
	sw zero, 0(a3)
dispatcher_2:
	/*
	 *  ����ߤ���Ĥ�������ߥ⡼�ɤ��ڤ괹���ơ�����ߤ��Ԥġ�
	 *
	 *  �����ǳ���ߥ⡼�ɤ��ڤ괹����Τϡ�������ȯ���������߽�����
	 *  �ɤΥ����å���Ȥ����Ȥ�������β��ȡ�����ߥϥ�ɥ���ǤΥ�
	 *  �����ǥ����ѥå����ɻߤȤ���2�Ĥΰ�̣�����롥
	 *
	 *  �ץ����å��������Ԥ��˰ܹԤ���������ȡ�����ߵ��ĤȤϡ��Բ�
	 *  ʬ�˹Ԥʤ�ɬ�פ������M68040�Ǥ�stop̿���ξ���Ԥʤ��Τ������
	 *  ���ˡ�������Բ�ʬ�˹Ԥʤ�ʤ���硤����ߤ���Ĥ���ľ��˳��
	 *  �ߤ����ꡤ������ǥ��������¹Բ�ǽ���֤ˤʤ�ȡ��¹Ԥ��٤�����
	 *  ��������ˤ⤫����餺�ץ����å���������Ԥ��ˤʤäƤ��ޤ���
	 *
	 *  ������Ԥ��δ֤ϡ�p_runtsk��NULL�ʡ�0�ˤ����ꤷ�ʤ���Фʤ��
	 *  �������Τ褦�����ꤷ�ʤ��ȡ�����ߥϥ�ɥ餫��iget_tid��Ƥӽ�
	 *  �����ݤ�ư����ͤ˹��פ��ʤ��ʤ롥
	 */
	la a1, kernel_mie				/* ������Ԥ� */
	LREG a2, 0(a1)
	csrs mie, a2
	wfi
	csrw mie, a5					/* ���ξ��֤��᤹ */
	la a2, reqflg					/* reqflg��false�ʤ�dispatcher_2�� */
	lw a1, 0(a2)
	beqz a1, dispatcher_2
	sw zero, 0(a2)					/* reqflg��false�� */

	/*
	 *  CPU���å����֤��᤹��������Ԥ��δ֤˼¹Ԥ�������ߥϥ�ɥ�ˤ�
	 *  �ꡤsaved_iipm���񤭴��������ǽ�������뤿�ᡤ�����ͤ��᤹ɬ
	 *  �פ����롥dispatcher���¹Ԥ������ϡ�saved_iipm��IIPM_ENAALL
	 *  �ȤʤäƤ��뤿�ᡤ�����Ǥ�saved_iipm��IIPM_ENAALL�ʡ�0�ˤ��᤻
	 *  �Ф褤��
	 */
	la a3, lock_flag				/* CPU���å����֤� */
	li a1, true
	sw a1, 0(a3)
	j dispatcher_0

/*
 *  �����ͥ�ν�λ�����θƽФ�
 *
 *  RISCV�Ǥϡ��⡼���ڴ����ˤ�ꥹ���å����ڤ괹���ʤ����ᡤ����Ū��
 *  �����å��ڴ�����Ԥ����ǽ餫�����ߥ⡼�ɤǤ��ä����⡤Ʊ������
 *  �Ǥ褤��
 */
	.globl call_exit_kernel
call_exit_kernel:
	la a0, _kernel_istk				/* STACK�򥫡��ͥ�ISTK�� */
	LREG sp, 0(a0)
	la a0, _kernel_istksz
	LREG a1, 0(a0)
	add sp, sp, a1
	j exit_kernel					/* �����ͥ�ν�λ������Ƥ� */

/*
 *  ���������ϻ�����
 */
	.text
	.globl start_r
start_r:
	la a1, lock_flag				/* CPU���å�������֤� */
	sw zero, 0(a1)
	la ra, ext_tsk					/* ext_tsk��������Ϥ����� */
	li a2, KERNEL_MIE
	csrrs a2, mie, a2				/* ����ߵ���   */
	LREG a1, TCB_p_tinib(a0)		/* p_runtsk->p_tinib��a1�� */
	LREG a0, TINIB_exinf(a1)		/* exinf������쥸����a0��  */
	LREG a2, TINIB_task(a1)			/* �������ε�ư���Ϥ�a2�� */
	jr a2


/*
 *  MACHINE����߽и�����
 *
 *  ����٥��MACHIE����ߤ�Ԥ��������å�����쥸�����ϥͥ��ȳ���ߤȤۤ�
 *  Ʊ�����桼���������å���ˡ�t3-t6�ޤǤΥ쥸�����ϥ桼���������å���
 *  ��¸���롥(�ͥ��ȳ���ߤǤϥ����ƥॹ���å�����¸)���Τ��ᡢ
 *  4*RGSIZE�Х���ʬ������ߤΤ���˥桼���������å�����񤹤롥
 *  �㳰/����ߤ�ȯ������ȡ������ƥॹ���å���˰ʲ��ξ���ȥ�����å�
 *  �쥸��������¸���롥
 *
 *   ------------
 *  | mstatus    |
 *   ------------
 *  | mpc        |
 *   ------------
 *  | mcause     |
 *   ------------
 *  | mip        |
 *   ------------
 *  | sp(x2)     |
 *   ------------
 *  | reserved   |
 *   ------------
 *  | a0(x10)    |
 *   ------------
 *  | a1(x11)    |
 *   ------------
 *  | ra(x1)     |
 *   ------------
 *  | a2(x12)    |
 *   ------------
 */
	.text
	.align 4
	.global trap_entry
trap_entry:
	addi sp, sp, -SAVEREG2*REGSIZE	/* �桼���������å��˥���쥸��������¸�ΰ����� */
	SREG t3, 18*REGSIZE(sp)			/* t3-t6�����쥸�����Ȥ��ƻ��Ѥ��� */
	SREG t4, 19*REGSIZE(sp)
	SREG t5, 20*REGSIZE(sp)
	SREG t6, 21*REGSIZE(sp)
	la t4, _kernel_istk				/* STACK�򥫡��ͥ�ISTK�� */
	LREG t5, 0(t4)
	la t4, _kernel_istksz
	LREG t6, 0(t4)
	mv t4, sp						/* �桼���������å���t4�˥��ԡ� */
	add sp, t5, t6					/* �����ƥॹ���å������� */

	addi sp, sp, -SAVEREG2*REGSIZE	/* �����ƥॹ���å���¸�ΰ����� */
	SREG a0, 6*REGSIZE(sp)			/* ������å��쥸��������¸ */
	SREG a1, 7*REGSIZE(sp)
	SREG a2, 8*REGSIZE(sp)
	SREG ra, 9*REGSIZE(sp)
	SREG a3, 10*REGSIZE(sp)
	SREG a4, 11*REGSIZE(sp)
	SREG a5, 12*REGSIZE(sp)
	SREG a6, 13*REGSIZE(sp)
	SREG a7, 14*REGSIZE(sp)
	SREG t0, 15*REGSIZE(sp)
	SREG t1, 16*REGSIZE(sp)
	SREG t2, 17*REGSIZE(sp)
#if SAVEREG2 == 42
	SFREG ft0, 22*REGSIZE(sp)
	SFREG ft1, 23*REGSIZE(sp)
	SFREG ft2, 24*REGSIZE(sp)
	SFREG ft3, 25*REGSIZE(sp)
	SFREG ft4, 26*REGSIZE(sp)
	SFREG ft5, 27*REGSIZE(sp)
	SFREG ft6, 28*REGSIZE(sp)
	SFREG ft7, 29*REGSIZE(sp)
	SFREG fa0, 30*REGSIZE(sp)
	SFREG fa1, 31*REGSIZE(sp)
	SFREG fa2, 32*REGSIZE(sp)
	SFREG fa3, 33*REGSIZE(sp)
	SFREG fa4, 34*REGSIZE(sp)
	SFREG fa5, 35*REGSIZE(sp)
	SFREG fa6, 36*REGSIZE(sp)
	SFREG fa7, 37*REGSIZE(sp)
	SFREG ft8, 38*REGSIZE(sp)
	SFREG ft9, 39*REGSIZE(sp)
	SFREG ft10, 40*REGSIZE(sp)
	SFREG ft11, 41*REGSIZE(sp)
#endif

	csrr a0, mcause					/* mcause��2����¸ */
	SREG a0, 2*REGSIZE(sp)
	csrr t5, mepc					/* mpc��1����¸ */
	SREG t5, 1*REGSIZE(sp)
	csrr t6, mstatus				/* mstatus��0����¸ */
	SREG t6, 0*REGSIZE(sp)
	csrr t3, mie					/* mie��3����¸ */
	SREG t3, 3*REGSIZE(sp)
	SREG t4, 4*REGSIZE(sp)			/* �桼���������å���4����¸ */
	li a2, KERNEL_MIE
	csrc mie, a2					/* �����ͥ������߶ػ�   */
	li a3, (MSTATUS_MPP | MSTATUS_MIE)
	csrs mstatus, a3				/* �����ͥ볰����ߵ��� */
	mv a1, sp						/* �����å���a1������ */
	call handle_trap				/* MACHINE�ϥ�ɥ��ƤӽФ� */

	LREG a0, 6*REGSIZE(sp)			/* ������å��쥸���������� */
	LREG a1, 7*REGSIZE(sp)
	LREG a2, 8*REGSIZE(sp)
	LREG ra, 9*REGSIZE(sp)
	LREG a3, 10*REGSIZE(sp)
	LREG a4, 11*REGSIZE(sp)
	LREG a5, 12*REGSIZE(sp)
	LREG a6, 13*REGSIZE(sp)
	LREG a7, 14*REGSIZE(sp)
	LREG t0, 15*REGSIZE(sp)
	LREG t1, 16*REGSIZE(sp)
	LREG t2, 17*REGSIZE(sp)
#if SAVEREG2 == 42
	LFREG ft0, 22*REGSIZE(sp)
	LFREG ft1, 23*REGSIZE(sp)
	LFREG ft2, 24*REGSIZE(sp)
	LFREG ft3, 25*REGSIZE(sp)
	LFREG ft4, 26*REGSIZE(sp)
	LFREG ft5, 27*REGSIZE(sp)
	LFREG ft6, 28*REGSIZE(sp)
	LFREG ft7, 29*REGSIZE(sp)
	LFREG fa0, 30*REGSIZE(sp)
	LFREG fa1, 31*REGSIZE(sp)
	LFREG fa2, 32*REGSIZE(sp)
	LFREG fa3, 33*REGSIZE(sp)
	LFREG fa4, 34*REGSIZE(sp)
	LFREG fa5, 35*REGSIZE(sp)
	LFREG fa6, 36*REGSIZE(sp)
	LFREG fa7, 37*REGSIZE(sp)
	LFREG ft8, 38*REGSIZE(sp)
	LFREG ft9, 39*REGSIZE(sp)
	LFREG ft10, 40*REGSIZE(sp)
	LFREG ft11, 41*REGSIZE(sp)
#endif

	la t5, reqflg					/* reqflg��true�Ǥ����trap_entery_2�� */
	lw t6, 0(t5)
	bnez t6, trap_entry_2
	la t5, lock_flag				/* CPU���å�����ν��� */
	sw zero, 0(t5)
	LREG t5, 1*REGSIZE(sp)			/* mepc�μ��Ф� */
	LREG t6, 0*REGSIZE(sp)			/* mstatus�μ��Ф� */
	LREG t4, 3*REGSIZE(sp)			/* mie�μ��Ф� */
	csrw mepc, t5					/* mepc������ */
	csrw mstatus, t6				/* mstatus������ */
	csrw mie, t4					/* mie������ */
	LREG sp, 4*REGSIZE(sp)			/* �桼���������å������� */

	LREG t3, 18*REGSIZE(sp)			/* ����ѥ�����å��쥸���������� */
	LREG t4, 19*REGSIZE(sp)
	LREG t5, 20*REGSIZE(sp)
	LREG t6, 21*REGSIZE(sp)
	addi sp, sp, SAVEREG2*REGSIZE	/* �����å����� */
	mret

trap_entry_2:
	LREG t5, 1*REGSIZE(sp)			/* mepc�μ��Ф� */
	LREG t4, 2*REGSIZE(sp)			/* mcause�μ��Ф� */
	LREG t3, 3*REGSIZE(sp)			/* mie�μ��Ф� */
	LREG t6, 0*REGSIZE(sp)			/* mstatus�μ��Ф� */
	LREG sp, 4*REGSIZE(sp)			/* �桼���������å������� */

	SREG t6, 0*REGSIZE(sp)			/* mstatus����¸ */
	SREG t3, 3*REGSIZE(sp)			/* mie����¸ */
	SREG t4, 2*REGSIZE(sp)			/* mcause����¸ */
	SREG t5, 1*REGSIZE(sp)			/* mepc����¸ */
	SREG a0, 6*REGSIZE(sp)			/* ������å��쥸��������¸ */
	SREG a1, 7*REGSIZE(sp)
	SREG a2, 8*REGSIZE(sp)
	SREG ra, 9*REGSIZE(sp)
	SREG a3, 10*REGSIZE(sp)
	SREG a4, 11*REGSIZE(sp)
	SREG a5, 12*REGSIZE(sp)
	SREG a6, 13*REGSIZE(sp)
	SREG a7, 14*REGSIZE(sp)
	SREG t0, 15*REGSIZE(sp)
	SREG t1, 16*REGSIZE(sp)
	SREG t2, 17*REGSIZE(sp)
#if SAVEREG2 == 42
	SFREG ft0, 22*REGSIZE(sp)
	SFREG ft1, 23*REGSIZE(sp)
	SFREG ft2, 24*REGSIZE(sp)
	SFREG ft3, 25*REGSIZE(sp)
	SFREG ft4, 26*REGSIZE(sp)
	SFREG ft5, 27*REGSIZE(sp)
	SFREG ft6, 28*REGSIZE(sp)
	SFREG ft7, 29*REGSIZE(sp)
	SFREG fa0, 30*REGSIZE(sp)
	SFREG fa1, 31*REGSIZE(sp)
	SFREG fa2, 32*REGSIZE(sp)
	SFREG fa3, 33*REGSIZE(sp)
	SFREG fa4, 34*REGSIZE(sp)
	SFREG fa5, 35*REGSIZE(sp)
	SFREG fa6, 36*REGSIZE(sp)
	SFREG fa7, 37*REGSIZE(sp)
	SFREG ft8, 38*REGSIZE(sp)
	SFREG ft9, 39*REGSIZE(sp)
	SFREG ft10, 40*REGSIZE(sp)
	SFREG ft11, 41*REGSIZE(sp)
#endif

	la a0, reqflg					/* reqflg��false�� */
	sw zero, 0(a0)
	la a1, lock_flag				/* loc_flag��true�� */
	li a2, true
	sw a2, 0(a1)

	la a1, p_runtsk					/* p_runtsk��a0�� */
	LREG a0, 0(a1)
	la a2, dspflg					/* dspflg��false�ʤ�ret_int_1�� */
	lw a3, 0(a2)
	beqz a3, ret_int_1
	la a2, p_schedtsk				/* p_runtsk��p_schedtsk��Ʊ���ʤ� */
	LREG a3, 0(a2)
	beq a0, a3, ret_int_1			/* ret_int_1�� */

	addi sp, sp, -SAVEREG3*REGSIZE	/* call�襻���֤Υ쥸��������¸ */
	SREG gp, 0*REGSIZE(sp)
	SREG tp, 1*REGSIZE(sp)
	SREG s0, 2*REGSIZE(sp)
	SREG s1, 3*REGSIZE(sp)
	SREG s2, 4*REGSIZE(sp)
	SREG s3, 5*REGSIZE(sp)
	SREG s4, 6*REGSIZE(sp)
	SREG s5, 7*REGSIZE(sp)
	SREG s6, 8*REGSIZE(sp)
	SREG s7, 9*REGSIZE(sp)
	SREG s8, 10*REGSIZE(sp)
	SREG s9, 11*REGSIZE(sp)
	SREG s10, 12*REGSIZE(sp)
	SREG s11, 13*REGSIZE(sp)
#if SAVEREG3 == 26
	SFREG fs0, 14*REGSIZE(sp)
	SFREG fs1, 15*REGSIZE(sp)
	SFREG fs2, 16*REGSIZE(sp)
	SFREG fs3, 17*REGSIZE(sp)
	SFREG fs4, 18*REGSIZE(sp)
	SFREG fs5, 19*REGSIZE(sp)
	SFREG fs6, 20*REGSIZE(sp)
	SFREG fs7, 21*REGSIZE(sp)
	SFREG fs8, 22*REGSIZE(sp)
	SFREG fs9, 23*REGSIZE(sp)
	SFREG fs10, 24*REGSIZE(sp)
	SFREG fs11, 25*REGSIZE(sp)
#endif
	SREG sp, TCB_sp(a0)				/* �����������å�����¸ */
	la a1, ret_int_r				/* �¹ԺƳ����Ϥ���¸ */
	SREG a1, TCB_pc(a0)
	j dispatcher

ret_int_r:
	LREG gp, 0*REGSIZE(sp)			/* call�襻���֤Υ쥸���������� */
	LREG tp, 1*REGSIZE(sp)
	LREG s0, 2*REGSIZE(sp)
	LREG s1, 3*REGSIZE(sp)
	LREG s2, 4*REGSIZE(sp)
	LREG s3, 5*REGSIZE(sp)
	LREG s4, 6*REGSIZE(sp)
	LREG s5, 7*REGSIZE(sp)
	LREG s6, 8*REGSIZE(sp)
	LREG s7, 9*REGSIZE(sp)
	LREG s8, 10*REGSIZE(sp)
	LREG s9, 11*REGSIZE(sp)
	LREG s10, 12*REGSIZE(sp)
	LREG s11, 13*REGSIZE(sp)
#if SAVEREG3 == 26
	LFREG fs0, 14*REGSIZE(sp)
	LFREG fs1, 15*REGSIZE(sp)
	LFREG fs2, 16*REGSIZE(sp)
	LFREG fs3, 17*REGSIZE(sp)
	LFREG fs4, 18*REGSIZE(sp)
	LFREG fs5, 19*REGSIZE(sp)
	LFREG fs6, 20*REGSIZE(sp)
	LFREG fs7, 21*REGSIZE(sp)
	LFREG fs8, 22*REGSIZE(sp)
	LFREG fs9, 23*REGSIZE(sp)
	LFREG fs10, 24*REGSIZE(sp)
	LFREG fs11, 25*REGSIZE(sp)
#endif
	addi sp, sp, SAVEREG3*REGSIZE
ret_int_1:
	/*
	 *  enatex��true�ǡ�texptn��0�Ǥʤ���ipmflg��true�Ǥ���С�������
	 *  �㳰�����롼�����ƤӽФ���
	 */
	li a2, TCB_enatex_bit			/* enatex��false�ʤ�ret_int_2�� */
	lbu a1, TCB_enatex(a0)
	sra a1, a1, a2
	andi a1, a1, 1
	beqz a1, ret_int_2
	lw a1, TCB_texptn(a0)			/* texptn��0�ʤ��ret_int_2�� */
	beqz a1, ret_int_2
	la a2, ipmflg					/* ipmflg��false�ʤ�ret_int_2�� */
	lw a1, 0(a2)
	beqz a1, ret_int_2
	jal call_texrtn
ret_int_2:
	/*
	 *  ����߽�������Υ꥿����ˤ�ꡤCPU���å�������֤˰ܹԤ����
	 *  ���������롥�����ͥ���٥ޥ����ϡ�MRET̿��ˤ�긵���ͤ���뤿
	 *  �ᡤlock_flag��false�ˤ��Ƥ����Ф褤��
	 */
	la a0, lock_flag				/* CPU���å�����ν��� */
	sw zero, 0(a0)

ret_int_3:
	LREG a1, 3*REGSIZE(sp)			/* mie�μ��Ф� */
	LREG a2, 1*REGSIZE(sp)			/* mpc�μ��Ф� */
	LREG a3, 0*REGSIZE(sp)			/* mstatus�μ��Ф� */
	csrw mepc, a2					/* mpc������ */
	csrw mstatus, a3				/* mstatus������ */
	csrw mie, a1					/* mie������ */

	LREG a0, 6*REGSIZE(sp)			/* ������å��쥸���������� */
	LREG a1, 7*REGSIZE(sp)
	LREG a2, 8*REGSIZE(sp)
	LREG ra, 9*REGSIZE(sp)
	LREG a3, 10*REGSIZE(sp)
	LREG a4, 11*REGSIZE(sp)
	LREG a5, 12*REGSIZE(sp)
	LREG a6, 13*REGSIZE(sp)
	LREG a7, 14*REGSIZE(sp)
	LREG t0, 15*REGSIZE(sp)
	LREG t1, 16*REGSIZE(sp)
	LREG t2, 17*REGSIZE(sp)
	LREG t3, 18*REGSIZE(sp)
	LREG t4, 19*REGSIZE(sp)
	LREG t5, 20*REGSIZE(sp)
	LREG t6, 21*REGSIZE(sp)
#if SAVEREG2 == 42
	LFREG ft0, 22*REGSIZE(sp)
	LFREG ft1, 23*REGSIZE(sp)
	LFREG ft2, 24*REGSIZE(sp)
	LFREG ft3, 25*REGSIZE(sp)
	LFREG ft4, 26*REGSIZE(sp)
	LFREG ft5, 27*REGSIZE(sp)
	LFREG ft6, 28*REGSIZE(sp)
	LFREG ft7, 29*REGSIZE(sp)
	LFREG fa0, 30*REGSIZE(sp)
	LFREG fa1, 31*REGSIZE(sp)
	LFREG fa2, 32*REGSIZE(sp)
	LFREG fa3, 33*REGSIZE(sp)
	LFREG fa4, 34*REGSIZE(sp)
	LFREG fa5, 35*REGSIZE(sp)
	LFREG fa6, 36*REGSIZE(sp)
	LFREG fa7, 37*REGSIZE(sp)
	LFREG ft8, 38*REGSIZE(sp)
	LFREG ft9, 39*REGSIZE(sp)
	LFREG ft10, 40*REGSIZE(sp)
	LFREG ft11, 41*REGSIZE(sp)
#endif
	addi sp, sp, SAVEREG2*REGSIZE
	mret

/*
 *  MACHINE�ͥ��ȳ���߽���������
 *
 *  trap_nest�ϡ��ͥ��Ȥ���MACHINE����ߤν�����������Ԥ���
 *  mtvec������ϸƤӽФ���handle_trap�ǹԤ���
 *  handle_trap����Υ꥿����ϥͥ��Ⱦ��֤˸��ꤵ��뤿��
 *  ���ν�������Ǥϡ������å����ѹ���Ԥ�ʤ���
 */
	.text
	.align 4
	.global trap_nest
trap_nest:
	addi sp, sp, -SAVEREG2*REGSIZE	/* �����ƥॹ���å���¸�ΰ����� */
	SREG a0, 6*REGSIZE(sp)			/* ������å��쥸��������¸ */
	SREG a1, 7*REGSIZE(sp)
	SREG a2, 8*REGSIZE(sp)
	SREG ra, 9*REGSIZE(sp)
	SREG a3, 10*REGSIZE(sp)
	SREG a4, 11*REGSIZE(sp)
	SREG a5, 12*REGSIZE(sp)
	SREG a6, 13*REGSIZE(sp)
	SREG a7, 14*REGSIZE(sp)
	SREG t0, 15*REGSIZE(sp)
	SREG t1, 16*REGSIZE(sp)
	SREG t2, 17*REGSIZE(sp)
	SREG t3, 18*REGSIZE(sp)
	SREG t4, 19*REGSIZE(sp)
	SREG t5, 20*REGSIZE(sp)
	SREG t6, 21*REGSIZE(sp)
#if SAVEREG2 == 42
	SFREG ft0, 22*REGSIZE(sp)
	SFREG ft1, 23*REGSIZE(sp)
	SFREG ft2, 24*REGSIZE(sp)
	SFREG ft3, 25*REGSIZE(sp)
	SFREG ft4, 26*REGSIZE(sp)
	SFREG ft5, 27*REGSIZE(sp)
	SFREG ft6, 28*REGSIZE(sp)
	SFREG ft7, 29*REGSIZE(sp)
	SFREG fa0, 30*REGSIZE(sp)
	SFREG fa1, 31*REGSIZE(sp)
	SFREG fa2, 32*REGSIZE(sp)
	SFREG fa3, 33*REGSIZE(sp)
	SFREG fa4, 34*REGSIZE(sp)
	SFREG fa5, 35*REGSIZE(sp)
	SFREG fa6, 36*REGSIZE(sp)
	SFREG fa7, 37*REGSIZE(sp)
	SFREG ft8, 38*REGSIZE(sp)
	SFREG ft9, 39*REGSIZE(sp)
	SFREG ft10, 40*REGSIZE(sp)
	SFREG ft11, 41*REGSIZE(sp)
#endif

	csrr a3, mstatus			    /* mstatus��0����¸ */
	SREG a3, 0*REGSIZE(sp)
	csrr a1, mie					/* mie��3����¸ */
	SREG a1, 3*REGSIZE(sp)
	addi a2, sp, 22*REGSIZE			/* �����ƥॹ���å���4����¸ */
	SREG a2, 4*REGSIZE(sp)
	csrr a0, mcause					/* mcause��a0�˼��Ф� */
	SREG a0, 2*REGSIZE(sp)			/* mcause��2����¸ */
	csrr a3, mepc					/* mpc��1����¸ */
	SREG a3, 1*REGSIZE(sp)
	li a2, KERNEL_MIE
	csrc mie, a2					/* �����ͥ������߶ػ�   */
	li a3, (MSTATUS_MPP | MSTATUS_MIE)
	csrs mstatus, a3				/* �����ͥ볰����ߵ��� */
	mv a1, sp						/* �����å���a1������ */
	la ra, ret_int_3				/* �꥿���󥢥ɥ쥹�򥻥å� */
	j handle_trap					/* MACHINE�ϥ�ɥ��ƤӽФ� */

/*
 *  ���������Ԥ��������SIL�Υ������åȰ�¸����
 */
	.globl sil_dly_nse
	.align 4
sil_dly_nse:
	addi  a0, a0, (-SIL_DLY_TIM1)	/* a0����SIL_DLY_TIM1����� */
	blez  a0, _sil_dly_nse_2		/* ��̤�0�ʲ��ʤ�꥿���� */
_sil_dly_nse_1:
	addi  a0, a0, (-SIL_DLY_TIM2)	/* a0����SIL_DLY_TIM2����� */
	bgtz  a0, _sil_dly_nse_1		/* ��̤�0����礭����Х롼�� */
_sil_dly_nse_2:
	ret
