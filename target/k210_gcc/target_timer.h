/*
 *  TOPPERS/ASP Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      Advanced Standard Profile Kernel
 * 
 *  Copyright (C) 2000-2003 by Embedded and Real-Time Systems Laboratory
 *                              Toyohashi Univ. of Technology, JAPAN
 *  Copyright (C) 2005-2008 by Embedded and Real-Time Systems Laboratory
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
 *  @(#) $Id: target_timer.h 889 2019-09-21 05:58:55Z roi $
 */

/*
 *		�����ޥɥ饤�С�K210�ѡ�
 */

#ifndef TOPPERS_TARGET_TIMER_H
#define TOPPERS_TARGET_TIMER_H

/*
 *  �������åȰ�¸���
 */
#include "target_syssvc.h"

/*
 *  �����޳���ߥϥ�ɥ���Ͽ�Τ�������
 */
#define INTPRI_TIMER	TIRQ_LEVEL4		/* �����ͥ���� */

/*
 *  CLINT���ȿ����
 */
#define CLINT_FREQ      (SYS_CLOCK / 50)

/*
 *  �ץ����å���¸���
 */
#include "riscv_gcc/prc_timer.h"

/*
 *  �����ͤ��ɤ߽Ф�
 */
Inline CLOCK
target_current_timer_value(void)
{
	return *((volatile CLOCK *)(TADR_CLIC_BASE+TOFF_CLINT_MTIME));
}

/*
 *  �������å��ͤ��ɤ߽Ф�
 */
Inline CLOCK
target_get_target_timer_value(void)
{
    uint32_t core_id = read_csr(mhartid);
	return *((volatile CLOCK *)(TADR_CLIC_BASE+TOFF_CLINT_MTIMECMP + core_id * sizeof(CLOCK)));
}

/*
 *  �������å��ͤν񤭹���
 */
Inline void
target_set_target_timer_value(CLOCK mtimecmp)
{
    uint32_t core_id = read_csr(mhartid);
	*((volatile CLOCK *)(TADR_CLIC_BASE+TOFF_CLINT_MTIMECMP + core_id * sizeof(CLOCK))) = mtimecmp;
}

/*
 *  �����ޤθ����ͤ��ɽФ�
 */
Inline CLOCK
target_timer_get_current(void)
{
	CLOCK	clk;

	clk = target_current_timer_value() - (target_get_target_timer_value() - TO_CLOCK(TIC_NUME, TIC_DENO));
	return(clk);
}

#define target_timer_probe_int		prc_timer_probe_int

#endif /* TOPPERS_TARGET_TIMER_H */