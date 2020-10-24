/*
 *  TOPPERS/ASP Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      Advanced Standard Profile Kernel
 * 
 *  Copyright (C) 2005,2006 by Embedded and Real-Time Systems Laboratory
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
 *  @(#) $Id: prc_timer.c 264 2019-09-20 18:51:36Z roi $
 */

/*
 *		�����ޥɥ饤�С�RISC-V�ѡ�
 */

#include "kernel_impl.h"
#include "time_event.h"
#include <sil.h>
#include "target_timer.h"


static int32_t  molecule;

/*
 *  �ǽ�γ���ߤΥ����ޡ��ͤ�����Τ���
 *  �����ȯ�����Υ����ޡ��ͤ�١����˥ޥå����֤����ꤹ�롥
 */
static void
pre_timer_handler(void)
{
	CLOCK mtimecmp = target_current_timer_value() + TO_CLOCK(TIC_NUME, TIC_DENO);

	target_set_target_timer_value(mtimecmp);
	x_machine_inh(IRQ_M_TIMER, (FP)prc_timer_handler);
}

/*
 *  �����ޤε�ư����
 */
void
prc_timer_initialize(intptr_t exinf)
{
	CLOCK	mtimecmp;

	/*
	 *  �����޼��������ꤷ�������ޤ�ư��򳫻Ϥ��롥
	 */
	mtimecmp = target_current_timer_value() + TO_CLOCK(TIC_NUME, TIC_DENO);
	target_set_target_timer_value(mtimecmp);
	molecule = REMAINDER(TIC_NUME, TIC_DENO);

	/*
	 *  �����޳�����׵�򥯥ꥢ���롥
	 */
	x_machine_inh(IRQ_M_TIMER, (FP)pre_timer_handler);
}

/*
 *  �����ޤ���߽���
 */
void
prc_timer_terminate(intptr_t exinf)
{
	/*
	 *  �����ޤ�ư�����ߤ��롥
	 */
	clear_csr(mie, MIP_MTIP);
}

/*
 *  �����޳���ߥϥ�ɥ�
 */
void
prc_timer_handler(void)
{
	uint8_t  threshold = (uint8_t)current_ithreshold();
	CLOCK	mtimecmp;
	int32_t	difference;

	kernel_mie &= ~MIP_MTIP;
	mtimecmp = target_get_target_timer_value();
	do{
		mtimecmp += TO_CLOCK(TIC_NUME, TIC_DENO);
		if(molecule >= DENOMINATOR(TIC_NUME, TIC_DENO)){
			mtimecmp++;
			molecule -= DENOMINATOR(TIC_NUME, TIC_DENO);
		}
		molecule += REMAINDER(TIC_NUME, TIC_DENO);
		difference = mtimecmp - target_current_timer_value();
	}while(difference <= 0);
	target_set_target_timer_value(mtimecmp);
	set_ithreshold((uint32_t)INT_IPM(INTPRI_TIMER));
	set_csr(mie, kernel_mie);
	signal_time();					/* ������ƥ��å��ζ��� */
	clear_csr(mie, KERNEL_MIE);
	set_ithreshold((uint32_t)threshold);
	kernel_mie |= MIP_MTIP;
}
