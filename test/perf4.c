/*
 *  TOPPERS Software
 *      Toyohashi Open Platform for Embedded Real-Time Systems
 * 
 *  Copyright (C) 2006-2009 by Embedded and Real-Time Systems Laboratory
 *              Graduate School of Information Science, Nagoya Univ., JAPAN
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
 *  @(#) $Id: perf4.c 2673 2015-02-08 10:08:03Z ertl-hiro $
 */

/*
 *		�����ͥ���ǽɾ���ץ����(4)
 *
 *  act_tsk��iact_tsk�ν������֤ȥ������ڴ������֤��¬���뤿��Υץ�
 *  ��ࡥ�ʲ���3�Ĥλ��֤�¬�ꤹ�롥
 *
 *  (1) �������ڴ����򵯤����ʤ�act_tsk�ν������֡�������������ͥ����
 *      ���㤤���������Ф���act_tsk��ȯ�Ԥ����ٻ߾��֤���¹ԤǤ������
 *      �����ܤ���������λ��֡�
 *
 *  (2) �������ڴ����򵯤���act_tsk�ν������֡�������������ͥ���٤ι�
 *      �����������Ф���act_tsk��ȯ�Ԥ����ٻ߾��֤���¹ԤǤ�����֤���
 *      �ܤ������������ڴ����򵯤����ơ��⤤ͥ���٤Υ������μ¹Ԥ��Ϥ�
 *      ��ޤǤλ��֡�
 *
 *  (3) �������ڴ����򵯤���iact_tsk�ν������֡������ϥ�ɥ餫�顤�¹�
 *      ���֤Υ���������⤤ͥ���٤Υ��������Ф���act_tsk��ȯ�Ԥ�����
 *      �߾��֤���¹ԤǤ�����֤����ܤ��������Ȥ˼����ϥ�ɥ餫��꥿��
 *      �󤷡��������ڴ����򵯤����ơ��⤤ͥ���٤Υ������μ¹Ԥ��Ϥޤ�
 *      �ޤǤλ��֡�
 */

#include <kernel.h>
#include <t_syslog.h>
#include <test_lib.h>
#include <histogram.h>
#include "kernel_cfg.h"
#include "perf4.h"

/*
 *  ��¬����ȼ¹Ի���ʬ�ۤ�Ͽ����������
 */
#define NO_MEASURE	10000U			/* ��¬��� */
#define MAX_TIME	1000U			/* �¹Ի���ʬ�ۤ�Ͽ���������� */

/*
 *  �¹Ի���ʬ�ۤ�Ͽ��������ΰ�
 */
static uint_t	histarea1[MAX_TIME + 1];
static uint_t	histarea2[MAX_TIME + 1];
static uint_t	histarea3[MAX_TIME + 1];

/*
 *  ��¬������1�ʹ�ͥ���١�
 */
void task1(intptr_t exinf)
{
	end_measure(2);
	ext_tsk();
}

/*
 *  ��¬������2�ȥᥤ�󥿥����ζ�ͭ�ѿ�
 */
volatile uint_t		task2_count;

/*
 *  ��¬������2�ʹ�ͥ���١�
 */
void task2(intptr_t exinf)
{
	end_measure(3);
	task2_count++;
	ext_tsk();
}

/*
 *  ��¬������3����ͥ���١�
 */
void task3(intptr_t exinf)
{
	ext_tsk();
}

/*
 *  ��¬������4�ʺ���ͥ���١�
 */
void task4(intptr_t exinf)
{
	while (true) {
		wup_tsk(MAIN_TASK);
	}
}

/*
 *  �����ϥ�ɥ�
 */
void cyclic_handler(intptr_t exinf)
{
	begin_measure(3);
	iact_tsk(TASK2);
}

/*
 *  �ᥤ�󥿥�������ͥ���١�
 */
void main_task(intptr_t exinf)
{
	uint_t	i;

	syslog_0(LOG_NOTICE, "Performance evaluation program (4)");
	init_hist(1, MAX_TIME, histarea1);
	init_hist(2, MAX_TIME, histarea2);
	init_hist(3, MAX_TIME, histarea3);
	syslog_flush();

	/*
	 *  �������ڴ����򵯤����ʤ�act_tsk�ν������֤�¬��
	 */
	for (i = 0; i < NO_MEASURE; i++) {
		begin_measure(1);
		act_tsk(TASK3);
		end_measure(1);
		slp_tsk();
	}

	/*
	 *  �������ڴ����򵯤���act_tsk�ν������֤�¬��
	 */
	for (i = 0; i < NO_MEASURE; i++) {
		begin_measure(2);
		act_tsk(TASK1);
	}

	/*
	 *  �������ڴ����򵯤���iact_tsk�ν������֤�¬���¬������10ʬ��1��
	 */
	task2_count = 0;
	sta_cyc(CYC1);
	while (task2_count < NO_MEASURE / 10) ;
	stp_cyc(CYC1);

	syslog_0(LOG_NOTICE, "Execution times of act_tsk without task switch");
	print_hist(1);
	syslog_0(LOG_NOTICE, "Execution times of act_tsk with task switch");
	print_hist(2);
	syslog_0(LOG_NOTICE, "Execution times of iact_tsk with task switch");
	print_hist(3);
	test_finish();
}
