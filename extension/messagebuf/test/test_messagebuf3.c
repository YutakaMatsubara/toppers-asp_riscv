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
 *  $Id: test_messagebuf3.c 2593 2014-01-02 06:29:10Z ertl-hiro $
 */

/* 
 *		��å������Хåե��Υƥ���(3)
 *
 * �ڥƥ��Ȥ���Ū��
 *
 *  ������ͥ���ٽ��å������Хåե��Ρ�FIFO���å������Хåե��Ȱۤ�
 *  �뿶�񤤤�ƥ��Ȥ��롥
 *
 * �ڥƥ��ȹ��ܡ�
 *
 *	(A) �����Ԥ����塼��������ͥ���٤Ǥ��뤳��
 *		(A-1) �夫�����夷����ͥ���٥����������ˤĤʤ���뤳��
 *		(A-2) Ʊ��ͥ���٤Υ�������FIFO��Ǥ��뤳��
 *	(B) �����Ԥ����塼�˥����������뤿��������Ԥ����֤ˤʤ���ΰ㤤
 *		(B-1) �����Ԥ����塼�����ξ��
 *		(B-2) �����Ԥ����塼���㤤ͥ���٤Υ������Τߤ�������
 *		(B-3) �����Ԥ����塼��Ʊ�����⤤ͥ���٤Υ�������������
 *	(C) �����Ԥ����塼����Ƭ��������ͥ���٤򲼤�����Ƭ���������Ѥ����
 *		(C-1) �����Ԥ����������Ԥ�����ʤ�
 *		(C-2) �����Ԥ���������1�Ĥޤ���ʣ���ˤ��Ԥ�����ʥ������ڴ����ʤ���
 *		(C-3) �����Ԥ���������1�Ĥޤ���ʣ���ˤ��Ԥ�����ʥ������ڴ��������
 *	(D) �����Ԥ����塼�����楿������ͥ���٤�夲����Ƭ���������Ѥ����
 *		(D-1) �����Ԥ����������Ԥ�����ʤ�
 *		(D-2) �����Ԥ���������1�Ĥޤ���ʣ���ˤ��Ԥ�����ʥ������ڴ����ʤ���
 *		(D-3) �����Ԥ���������1�Ĥޤ���ʣ���ˤ��Ԥ�����ʥ������ڴ��������
 *
 * �ڻ��ѥ꥽������
 *
 *	TASK1: ��ͥ���٥��������ᥤ�󥿥������ǽ餫�鵯ư
 *	TASK2: ��ͥ���٥�����
 *	TASK3: ��ͥ���٥�����
 *	TASK4: ��ͥ���٥�����
 *	MBF1: ��å������Хåե���TA_TPRI°���������å�������������26�����
 *		  �������Хåե������ΰ�Υ�������26���ºݤˤ�28��
 *
 * �ڥƥ��ȥ������󥹡�
 *
 *	== TASK1��ͥ���١����==
 *		call(set_bit_func(bit_kernel))
 *	1:	act_tsk(TASK2)
 *		act_tsk(TASK4)
 *		slp_tsk()
 *	== TASK2��ͥ���١����==
 *	2:	snd_mbf(MBF1, string1, 26)
 *	== TASK4��ͥ���١����==
 *	3:	wup_tsk(TASK1)
 *	== TASK1��³����==
 *	4:	snd_mbf(MBF1, string2, 25)						... (A-1)
 *	== TASK4��³����==
 *	5:	ref_mbf(MBF1, &rmbf)
 *		assert(rmbf.stskid == TASK1)
 *		assert(rmbf.rtskid == TSK_NONE)
 *		assert(rmbf.smbfcnt == 0)
 *		rcv_mbf(MBF1, buf1) -> 25
 *	== TASK1��³����==
 *	6:	assert(strncmp(buf1, string2, 25) == 0)
 *		act_tsk(TASK3)
 *		slp_tsk()
 *	== TASK3��ͥ���١����==
 *	7:	snd_mbf(MBF1, string2, 26)						... (A-2)
 *	== TASK4��³����==
 *	8:	rcv_mbf(MBF1, buf1) -> 26
 *	== TASK2��³����==
 *	9:	assert(strncmp(buf1, string1, 26) == 0)
 *		rcv_mbf(MBF1, buf1) -> 26
 *		assert(strncmp(buf1, string2, 26) == 0)
 *	10:	snd_mbf(MBF1, string3, 10)						... (B-1)
 *		rcv_mbf(MBF1, buf1) -> 10
 *		assert(strncmp(buf1, string3, 10) == 0)
 *	11:	snd_mbf(MBF1, string1, 26)
 *	== TASK3��³����==
 *	12:	wup_tsk(TASK1)
 *	== TASK1��³����==
 *	13:	snd_mbf(MBF1, string2, 10)						... (B-2)
 *		rcv_mbf(MBF1, buf1) -> 10
 *		assert(strncmp(buf1, string2, 10) == 0)
 *		slp_tsk()
 *	== TASK3��³����==
 *	14:	snd_mbf(MBF1, string3, 10)						... (B-3)
 *	== TASK4��³����==
 *	15:	rcv_mbf(MBF1, buf1) -> 26
 *	== TASK2��³����==
 *	16:	assert(strncmp(buf1, string1, 26) == 0)
 *		rcv_mbf(MBF1, buf1) -> 10
 *		assert(strncmp(buf1, string3, 10) == 0)
 *	17:	snd_mbf(MBF1, string1, 26)
 *	== TASK3��³����==
 *	18:	snd_mbf(MBF1, string2, 26)
 *	== TASK4��³����==
 *	19:	chg_pri(TASK2, LOW_PRIORITY)					... (C-1)
 *		rcv_mbf(MBF1, buf1) -> 26
 *	== TASK3��³����==
 *	20:	assert(strncmp(buf1, string2, 26) == 0)
 *		rcv_mbf(MBF1, buf1) -> 26
 *		assert(strncmp(buf1, string1, 26) == 0)
 *		chg_pri(TASK2, TPRI_INI)						... �����᤹
 *	21:	snd_mbf(MBF1, string1, 26)
 *	== TASK2��³����==
 *	22:	snd_mbf(MBF1, string2, 10)
 *	== TASK4��³����==
 *	23:	wup_tsk(TASK1)
 *	== TASK1��³����==
 *	24:	chg_pri(TASK3, LOW_PRIORITY)					... (C-2)
 *		slp_tsk()
 *	== TASK2��³����==
 *	25:	rcv_mbf(MBF1, buf1) -> 10
 *		assert(strncmp(buf1, string2, 10) == 0)
 *		chg_pri(TASK3, TPRI_INI)						... �����᤹
 *	26:	snd_mbf(MBF1, string3, 10)
 *	== TASK4��³����==
 *	27:	chg_pri(TASK3, LOW_PRIORITY)					... (C-3)
 *	== TASK2��³����==
 *	28:	rcv_mbf(MBF1, buf1) -> 10
 *		assert(strncmp(buf1, string3, 10) == 0)
 *		chg_pri(TASK3, TPRI_INI)						... �����᤹
 *	29:	snd_mbf(MBF1, string1, 26)
 *	== TASK4��³����==
 *	30:	chg_pri(TASK2, HIGH_PRIORITY)					... (D-1)
 *		rcv_mbf(MBF1, buf1) -> 26
 *	== TASK2��³����==
 *	31:	assert(strncmp(buf1, string1, 26) == 0)
 *		chg_pri(TSK_SELF, TPRI_INI)						... �����᤹
 *	32:	snd_mbf(MBF1, string2, 10)
 *	== TASK4��³����==
 *	33:	wup_tsk(TASK1)
 *	== TASK1��³����==
 *	34:	chg_pri(TASK2, HIGH_PRIORITY)					... (D-2)
 *		slp_tsk()
 *	== TASK2��³����==
 *	35:	rcv_mbf(MBF1, buf1) -> 10
 *		assert(strncmp(buf1, string2, 10) == 0)
 *		chg_pri(TSK_SELF, TPRI_INI)						... �����᤹
 *	36:	snd_mbf(MBF1, string3, 10)
 *	== TASK4��³����==
 *	37:	chg_pri(TASK2, HIGH_PRIORITY)					... (D-3)
 *	== TASK2��³����==
 *	38:	rcv_mbf(MBF1, buf1) -> 10
 *		assert(strncmp(buf1, string3, 10) == 0)
 *		rcv_mbf(MBF1, buf1) -> 26
 *		assert(strncmp(buf1, string1, 26) == 0)
 *	39:	END
 */

#include <kernel.h>
#include <t_syslog.h>
#include "kernel_cfg.h"
#include "test_lib.h"
#include "test_messagebuf3.h"
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

	test_start(__FILE__);

	set_bit_func(bit_kernel);

	check_point(1);
	ercd = act_tsk(TASK2);
	check_ercd(ercd, E_OK);

	ercd = act_tsk(TASK4);
	check_ercd(ercd, E_OK);

	ercd = slp_tsk();
	check_ercd(ercd, E_OK);

	check_point(4);
	ercd = snd_mbf(MBF1, string2, 25);
	check_ercd(ercd, E_OK);

	check_point(6);
	check_assert(strncmp(buf1, string2, 25) == 0);

	ercd = act_tsk(TASK3);
	check_ercd(ercd, E_OK);

	ercd = slp_tsk();
	check_ercd(ercd, E_OK);

	check_point(13);
	ercd = snd_mbf(MBF1, string2, 10);
	check_ercd(ercd, E_OK);

	ercd = rcv_mbf(MBF1, buf1);
	check_ercd(ercd, 10);

	check_assert(strncmp(buf1, string2, 10) == 0);

	ercd = slp_tsk();
	check_ercd(ercd, E_OK);

	check_point(24);
	ercd = chg_pri(TASK3, LOW_PRIORITY);
	check_ercd(ercd, E_OK);

	ercd = slp_tsk();
	check_ercd(ercd, E_OK);

	check_point(34);
	ercd = chg_pri(TASK2, HIGH_PRIORITY);
	check_ercd(ercd, E_OK);

	ercd = slp_tsk();
	check_ercd(ercd, E_OK);

	check_point(0);
}

void
task2(intptr_t exinf)
{
	ER_UINT	ercd;

	check_point(2);
	ercd = snd_mbf(MBF1, string1, 26);
	check_ercd(ercd, E_OK);

	check_point(9);
	check_assert(strncmp(buf1, string1, 26) == 0);

	ercd = rcv_mbf(MBF1, buf1);
	check_ercd(ercd, 26);

	check_assert(strncmp(buf1, string2, 26) == 0);

	check_point(10);
	ercd = snd_mbf(MBF1, string3, 10);
	check_ercd(ercd, E_OK);

	ercd = rcv_mbf(MBF1, buf1);
	check_ercd(ercd, 10);

	check_assert(strncmp(buf1, string3, 10) == 0);

	check_point(11);
	ercd = snd_mbf(MBF1, string1, 26);
	check_ercd(ercd, E_OK);

	check_point(16);
	check_assert(strncmp(buf1, string1, 26) == 0);

	ercd = rcv_mbf(MBF1, buf1);
	check_ercd(ercd, 10);

	check_assert(strncmp(buf1, string3, 10) == 0);

	check_point(17);
	ercd = snd_mbf(MBF1, string1, 26);
	check_ercd(ercd, E_OK);

	check_point(22);
	ercd = snd_mbf(MBF1, string2, 10);
	check_ercd(ercd, E_OK);

	check_point(25);
	ercd = rcv_mbf(MBF1, buf1);
	check_ercd(ercd, 10);

	check_assert(strncmp(buf1, string2, 10) == 0);

	ercd = chg_pri(TASK3, TPRI_INI);
	check_ercd(ercd, E_OK);

	check_point(26);
	ercd = snd_mbf(MBF1, string3, 10);
	check_ercd(ercd, E_OK);

	check_point(28);
	ercd = rcv_mbf(MBF1, buf1);
	check_ercd(ercd, 10);

	check_assert(strncmp(buf1, string3, 10) == 0);

	ercd = chg_pri(TASK3, TPRI_INI);
	check_ercd(ercd, E_OK);

	check_point(29);
	ercd = snd_mbf(MBF1, string1, 26);
	check_ercd(ercd, E_OK);

	check_point(31);
	check_assert(strncmp(buf1, string1, 26) == 0);

	ercd = chg_pri(TSK_SELF, TPRI_INI);
	check_ercd(ercd, E_OK);

	check_point(32);
	ercd = snd_mbf(MBF1, string2, 10);
	check_ercd(ercd, E_OK);

	check_point(35);
	ercd = rcv_mbf(MBF1, buf1);
	check_ercd(ercd, 10);

	check_assert(strncmp(buf1, string2, 10) == 0);

	ercd = chg_pri(TSK_SELF, TPRI_INI);
	check_ercd(ercd, E_OK);

	check_point(36);
	ercd = snd_mbf(MBF1, string3, 10);
	check_ercd(ercd, E_OK);

	check_point(38);
	ercd = rcv_mbf(MBF1, buf1);
	check_ercd(ercd, 10);

	check_assert(strncmp(buf1, string3, 10) == 0);

	ercd = rcv_mbf(MBF1, buf1);
	check_ercd(ercd, 26);

	check_assert(strncmp(buf1, string1, 26) == 0);

	check_finish(39);
	check_point(0);
}

void
task3(intptr_t exinf)
{
	ER_UINT	ercd;

	check_point(7);
	ercd = snd_mbf(MBF1, string2, 26);
	check_ercd(ercd, E_OK);

	check_point(12);
	ercd = wup_tsk(TASK1);
	check_ercd(ercd, E_OK);

	check_point(14);
	ercd = snd_mbf(MBF1, string3, 10);
	check_ercd(ercd, E_OK);

	check_point(18);
	ercd = snd_mbf(MBF1, string2, 26);
	check_ercd(ercd, E_OK);

	check_point(20);
	check_assert(strncmp(buf1, string2, 26) == 0);

	ercd = rcv_mbf(MBF1, buf1);
	check_ercd(ercd, 26);

	check_assert(strncmp(buf1, string1, 26) == 0);

	ercd = chg_pri(TASK2, TPRI_INI);
	check_ercd(ercd, E_OK);

	check_point(21);
	ercd = snd_mbf(MBF1, string1, 26);
	check_ercd(ercd, E_OK);

	check_point(0);
}

void
task4(intptr_t exinf)
{
	ER_UINT	ercd;
	T_RMBF	rmbf;

	check_point(3);
	ercd = wup_tsk(TASK1);
	check_ercd(ercd, E_OK);

	check_point(5);
	ercd = ref_mbf(MBF1, &rmbf);
	check_ercd(ercd, E_OK);

	check_assert(rmbf.stskid == TASK1);

	check_assert(rmbf.rtskid == TSK_NONE);

	check_assert(rmbf.smbfcnt == 0);

	ercd = rcv_mbf(MBF1, buf1);
	check_ercd(ercd, 25);

	check_point(8);
	ercd = rcv_mbf(MBF1, buf1);
	check_ercd(ercd, 26);

	check_point(15);
	ercd = rcv_mbf(MBF1, buf1);
	check_ercd(ercd, 26);

	check_point(19);
	ercd = chg_pri(TASK2, LOW_PRIORITY);
	check_ercd(ercd, E_OK);

	ercd = rcv_mbf(MBF1, buf1);
	check_ercd(ercd, 26);

	check_point(23);
	ercd = wup_tsk(TASK1);
	check_ercd(ercd, E_OK);

	check_point(27);
	ercd = chg_pri(TASK3, LOW_PRIORITY);
	check_ercd(ercd, E_OK);

	check_point(30);
	ercd = chg_pri(TASK2, HIGH_PRIORITY);
	check_ercd(ercd, E_OK);

	ercd = rcv_mbf(MBF1, buf1);
	check_ercd(ercd, 26);

	check_point(33);
	ercd = wup_tsk(TASK1);
	check_ercd(ercd, E_OK);

	check_point(37);
	ercd = chg_pri(TASK2, HIGH_PRIORITY);
	check_ercd(ercd, E_OK);

	check_point(0);
}
