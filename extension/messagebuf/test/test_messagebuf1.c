/*
 *  TOPPERS Software
 *      Toyohashi Open Platform for Embedded Real-Time Systems
 * 
 *  Copyright (C) 2014 by Embedded and Real-Time Systems Laboratory
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
 *  $Id: test_messagebuf1.c 2593 2014-01-02 06:29:10Z ertl-hiro $
 */

/* 
 *		��å������Хåե��Υƥ���(1)
 *
 * �ڥƥ��Ȥ���Ū��
 *
 *  FIFO���å������Хåե��ˡ���å�������������������ȼ����������
 *  ����̤�ƥ��Ȥ��롥
 *
 * �ڥƥ��ȹ��ܡ�
 *
 *	(A) ��å������Хåե��ؤ�����������snd_mbf��send_message��
 *		(A-1) �����Ԥ����塼����Ƭ�������������ʥ������ڴ����ʤ���
 *		(A-2) �����Ԥ����塼����Ƭ�������������ʥ������ڴ��������
 *		(A-3) ��å������Хåե������ΰ�˳�Ǽ
 *		(A-4) �����Ԥ����塼�˥����������뤿��������Ԥ����֤�
 *		(A-5) ��å������Хåե������ΰ�˶������ʤ�����������Ԥ����֤�
 *	(B) ��å������Хåե�����μ���������rcv_mbf��receive_message��
 *		(B-1) ��å������Хåե������ΰ褫�����
 *		(B-2) (B-1)�������Ԥ���������1�Ĥޤ���ʣ���ˤ��Ԥ�����ʥ�����
 *			  �ڴ����ʤ���
 *		(B-3) (B-1)�������Ԥ���������1�Ĥޤ���ʣ���ˤ��Ԥ�����ʥ�����
 *			  �ڴ��������
 *		(B-4) �����Ԥ����塼����Ƭ�Υ������Υ�å�����������ʥ�������
 *			  �����ʤ���
 *		(B-5) �����Ԥ����塼����Ƭ�Υ������Υ�å�����������ʥ�������
 *			  ���������
 *		(B-6) �����Ԥ����֤�
 *	(C) ��å������Хåե������ΰ�ؤΥ�å������γ�Ǽ��enqueue_message��
 *		(C-1) �������ȥ�å��������Τ��Ϣ���ΰ�˳�Ǽ
 *		(C-2) ���������Ǽ��˴����ΰ����Ƭ�����
 *		(C-3) ��å��������Τγ�Ǽ����Ǵ����ΰ����Ƭ�����
 *		(C-4) ��å��������Τγ�Ǽ��˴����ΰ����Ƭ�����
 *	(D) ��å������Хåե������ΰ褫��Υ�å������μ�Ф���dequeue_message��
 *		(D-1) �������ȥ�å��������Τ��Ϣ���ΰ褫���Ф�
 *		(D-2) ���������Ф���˴����ΰ����Ƭ�����
 *		(D-3) ��å��������Τμ�Ф�����Ǵ����ΰ����Ƭ�����
 *		(D-4) ��å��������Τμ�Ф���˴����ΰ����Ƭ�����
 *
 * �ڻ��ѥ꥽������
 *
 *	TASK1: ��ͥ���٥��������ᥤ�󥿥������ǽ餫�鵯ư
 *	TASK2: ��ͥ���٥�����
 *	TASK3: ��ͥ���٥�����
 *	MBF1: ��å������Хåե���TA_NULL°���������å�������������26�����
 *		  �������Хåե������ΰ�Υ�������26���ºݤˤ�28��
 *
 * �ڥƥ��ȥ������󥹡�
 *
 *	== TASK1��ͥ���١����==
 *		call(set_bit_func(bit_kernel))
 *	1:	act_tsk(TASK2)
 *		act_tsk(TASK3)
 *		ref_mbf(MBF1, &rmbf)
 *		assert(rmbf.stskid == TSK_NONE)
 *		assert(rmbf.rtskid == TSK_NONE)
 *		assert(rmbf.smbfcnt == 0)
 *		snd_mbf(MBF1, string1, 9)		... (A-3)(C-1)�����ѡ�0��15
 *	2:	snd_mbf(MBF1, string2, 5)		... (A-3)(C-4)�����ѡ�0��27
 *	3:	snd_mbf(MBF1, string3, 4)		... (A-5)
 *	== TASK2��ͥ���١����==
 *	4:	ref_mbf(MBF1, &rmbf)
 *		assert(rmbf.stskid == TASK1)
 *		assert(rmbf.rtskid == TSK_NONE)
 *		assert(rmbf.smbfcnt == 2)
 *	5:	snd_mbf(MBF1, string1, 4)		... (A-4)
 *	== TASK3��ͥ���١����==
 *	6:	rcv_mbf(MBF1, buf1) -> 9		... (B-3)(D-1)(C-1)�����ѡ�16��27,0��15
 *	== TASK1��³����==
 *	7:	assert(strncmp(buf1, string1, 9) == 0)
 *		slp_tsk()
 *	== TASK2��³����==
 *	8:	rcv_mbf(MBF1, buf1) -> 5		... (B-1)(D-4)�����ѡ�0��15
 *		assert(strncmp(buf1, string2, 5) == 0)
 *		rcv_mbf(MBF1, buf1) -> 4		... (B-1)(D-1)�����ѡ�8��15
 *		assert(strncmp(buf1, string3, 4) == 0)
 *		rcv_mbf(MBF1, buf1) -> 4		... (B-1)(D-1)�����ѡ��ʤ�
 *		assert(strncmp(buf1, string1, 4) == 0)
 *	9:	rcv_mbf(MBF1, buf1) -> 10		... (B-6)
 *	== TASK3��³����==
 *	10:	ref_mbf(MBF1, &rmbf)
 *		assert(rmbf.stskid == TSK_NONE)
 *		assert(rmbf.rtskid == TASK2)
 *		assert(rmbf.smbfcnt == 0)
 *	11:	snd_mbf(MBF1, string2, 10)		... (A-2)
 *	== TASK2��³����==
 *	12:	assert(strncmp(buf1, string2, 10) == 0)
 *		rcv_mbf(MBF1, buf1) -> 11		... (B-6)
 *	== TASK3��³����==
 *	13:	wup_tsk(TASK1)
 *	== TASK1��³����==
 *	14:	snd_mbf(MBF1, string3, 11)		... (A-1)
 *		assert(strncmp(buf1, string3, 11) == 0)
 *		snd_mbf(MBF1, string1, 16)		... (A-3)(C-3)�����ѡ�16��27,0��7
 *		tslp_tsk(1) -> E_TMOUT
 *	== TASK2��³����==
 *	15:	slp_tsk()
 *	== TASK3��³����==
 *	16:	snd_mbf(MBF1, string2, 12)		... (A-5)
 *	== TASK1��³����==
 *	17:	wup_tsk(TASK2)
 *		tslp_tsk(1) -> E_TMOUT
 *	== TASK2��³����==
 *	18:	snd_mbf(MBF1, string3, 4)		... (A-4)
 *	== TASK1��³����==
 *	19:	rcv_mbf(MBF1, buf1) -> 16		... (B-2)(D-3)(C-1)(C-2)��
 *										... 				���ѡ�8��27,0��3
 *		assert(strncmp(buf1, string1, 16) == 0)
 *		slp_tsk()
 *	== TASK2��³����==
 *	20:	rcv_mbf(MBF1, buf1) -> 12		... (B-1)(D-1)�����ѡ�24��27��0��3
 *		assert(strncmp(buf1, string2, 12) == 0)
 *	21:	snd_mbf(MBF1, string1, 25)		... (A-5)
 *	== TASK3��³����==
 *	22:	rcv_mbf(MBF1, buf1) -> 4		... (B-1)(D-2)�����ѡ��ʤ�
 *		assert(strncmp(buf1, string3, 4) == 0)
 *		rcv_mbf(MBF1, buf1) -> 25		... (B-5)
 *	== TASK2��³����==
 *	23:	assert(strncmp(buf1, string1, 25) == 0)
 *		snd_mbf(MBF1, string2, 26)		... (A-5)
 *	== TASK3��³����==
 *	24:	wup_tsk(TASK1)
 *	== TASK1��³����==
 *	25:	rcv_mbf(MBF1, buf1) -> 26		... (B-4)
 *		assert(strncmp(buf1, string2, 26) == 0)
 *		slp_tsk()
 *	== TASK2��³����==
 *	26:	slp_tsk()
 *	== TASK3��³����==
 *	27:	END
 */

#include <kernel.h>
#include <t_syslog.h>
#include "kernel_cfg.h"
#include "test_lib.h"
#include "test_messagebuf1.h"
#include <string.h>

const char string1[26] = "abcdefghijklmnopqrstuvwxyz";
const char string2[26] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
const char string3[16] = "0123456789abcdef";

char buf1[26];

extern ER	bit_kernel(void);

/* DO NOT DELETE THIS LINE -- gentest depends on it. */

void
task1(intptr_t exinf)
{
	ER_UINT	ercd;
	T_RMBF	rmbf;

	test_start(__FILE__);

	set_bit_func(bit_kernel);

	check_point(1);
	ercd = act_tsk(TASK2);
	check_ercd(ercd, E_OK);

	ercd = act_tsk(TASK3);
	check_ercd(ercd, E_OK);

	ercd = ref_mbf(MBF1, &rmbf);
	check_ercd(ercd, E_OK);

	check_assert(rmbf.stskid == TSK_NONE);

	check_assert(rmbf.rtskid == TSK_NONE);

	check_assert(rmbf.smbfcnt == 0);

	ercd = snd_mbf(MBF1, string1, 9);
	check_ercd(ercd, E_OK);

	check_point(2);
	ercd = snd_mbf(MBF1, string2, 5);
	check_ercd(ercd, E_OK);

	check_point(3);
	ercd = snd_mbf(MBF1, string3, 4);
	check_ercd(ercd, E_OK);

	check_point(7);
	check_assert(strncmp(buf1, string1, 9) == 0);

	ercd = slp_tsk();
	check_ercd(ercd, E_OK);

	check_point(14);
	ercd = snd_mbf(MBF1, string3, 11);
	check_ercd(ercd, E_OK);

	check_assert(strncmp(buf1, string3, 11) == 0);

	ercd = snd_mbf(MBF1, string1, 16);
	check_ercd(ercd, E_OK);

	ercd = tslp_tsk(1);
	check_ercd(ercd, E_TMOUT);

	check_point(17);
	ercd = wup_tsk(TASK2);
	check_ercd(ercd, E_OK);

	ercd = tslp_tsk(1);
	check_ercd(ercd, E_TMOUT);

	check_point(19);
	ercd = rcv_mbf(MBF1, buf1);
	check_ercd(ercd, 16);

	check_assert(strncmp(buf1, string1, 16) == 0);

	ercd = slp_tsk();
	check_ercd(ercd, E_OK);

	check_point(25);
	ercd = rcv_mbf(MBF1, buf1);
	check_ercd(ercd, 26);

	check_assert(strncmp(buf1, string2, 26) == 0);

	ercd = slp_tsk();
	check_ercd(ercd, E_OK);

	check_point(0);
}

void
task2(intptr_t exinf)
{
	ER_UINT	ercd;
	T_RMBF	rmbf;

	check_point(4);
	ercd = ref_mbf(MBF1, &rmbf);
	check_ercd(ercd, E_OK);

	check_assert(rmbf.stskid == TASK1);

	check_assert(rmbf.rtskid == TSK_NONE);

	check_assert(rmbf.smbfcnt == 2);

	check_point(5);
	ercd = snd_mbf(MBF1, string1, 4);
	check_ercd(ercd, E_OK);

	check_point(8);
	ercd = rcv_mbf(MBF1, buf1);
	check_ercd(ercd, 5);

	check_assert(strncmp(buf1, string2, 5) == 0);

	ercd = rcv_mbf(MBF1, buf1);
	check_ercd(ercd, 4);

	check_assert(strncmp(buf1, string3, 4) == 0);

	ercd = rcv_mbf(MBF1, buf1);
	check_ercd(ercd, 4);

	check_assert(strncmp(buf1, string1, 4) == 0);

	check_point(9);
	ercd = rcv_mbf(MBF1, buf1);
	check_ercd(ercd, 10);

	check_point(12);
	check_assert(strncmp(buf1, string2, 10) == 0);

	ercd = rcv_mbf(MBF1, buf1);
	check_ercd(ercd, 11);

	check_point(15);
	ercd = slp_tsk();
	check_ercd(ercd, E_OK);

	check_point(18);
	ercd = snd_mbf(MBF1, string3, 4);
	check_ercd(ercd, E_OK);

	check_point(20);
	ercd = rcv_mbf(MBF1, buf1);
	check_ercd(ercd, 12);

	check_assert(strncmp(buf1, string2, 12) == 0);

	check_point(21);
	ercd = snd_mbf(MBF1, string1, 25);
	check_ercd(ercd, E_OK);

	check_point(23);
	check_assert(strncmp(buf1, string1, 25) == 0);

	ercd = snd_mbf(MBF1, string2, 26);
	check_ercd(ercd, E_OK);

	check_point(26);
	ercd = slp_tsk();
	check_ercd(ercd, E_OK);

	check_point(0);
}

void
task3(intptr_t exinf)
{
	ER_UINT	ercd;
	T_RMBF	rmbf;

	check_point(6);
	ercd = rcv_mbf(MBF1, buf1);
	check_ercd(ercd, 9);

	check_point(10);
	ercd = ref_mbf(MBF1, &rmbf);
	check_ercd(ercd, E_OK);

	check_assert(rmbf.stskid == TSK_NONE);

	check_assert(rmbf.rtskid == TASK2);

	check_assert(rmbf.smbfcnt == 0);

	check_point(11);
	ercd = snd_mbf(MBF1, string2, 10);
	check_ercd(ercd, E_OK);

	check_point(13);
	ercd = wup_tsk(TASK1);
	check_ercd(ercd, E_OK);

	check_point(16);
	ercd = snd_mbf(MBF1, string2, 12);
	check_ercd(ercd, E_OK);

	check_point(22);
	ercd = rcv_mbf(MBF1, buf1);
	check_ercd(ercd, 4);

	check_assert(strncmp(buf1, string3, 4) == 0);

	ercd = rcv_mbf(MBF1, buf1);
	check_ercd(ercd, 25);

	check_point(24);
	ercd = wup_tsk(TASK1);
	check_ercd(ercd, E_OK);

	check_finish(27);
	check_point(0);
}
