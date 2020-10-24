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
 *  $Id: test_messagebuf2.c 2593 2014-01-02 06:29:10Z ertl-hiro $
 */

/* 
 *		��å������Хåե��Υƥ���(2)
 *
 * �ڥƥ��Ȥ���Ū��
 *
 *  FIFO���å������Хåե��������Ԥ���������������Ū���Ԥ�������줿
 *  ������̤�ƥ��Ȥ��롥
 *
 * �ڥƥ��ȹ��ܡ�
 *
 *	(A) �����Ԥ���������������λ��ter_tsk��
 *		(A-1) �����Ԥ����������Ԥ�����ʤ�
 *		(A-2) �����Ԥ���������1�Ĥޤ���ʣ���ˤ��Ԥ�����ʥ������ڴ����ʤ���
 *		(A-3) �����Ԥ���������1�Ĥޤ���ʣ���ˤ��Ԥ�����ʥ������ڴ��������
 *	(B) �����Ԥ��������������Ԥ������rel_wai��
 *		(B-1) �����Ԥ����������Ԥ�����ʤ�
 *		(B-2) �����Ԥ���������1�Ĥޤ���ʣ���ˤ��Ԥ�����ʥ������ڴ����ʤ���
 *		(B-3) �����Ԥ���������1�Ĥޤ���ʣ���ˤ��Ԥ�����ʥ������ڴ��������
 *	(C) �����Ԥ��������������Ԥ������irel_wai��
 *		(C-1) �����Ԥ����������Ԥ�����ʤ�
 *		(C-2) �����Ԥ���������1�Ĥޤ���ʣ���ˤ��Ԥ�����ʥ������ڴ����ʤ���
 *		(C-3) �����Ԥ���������1�Ĥޤ���ʣ���ˤ��Ԥ�����ʥ������ڴ��������
 *	(D) �����Ԥ��������������ॢ���Ȥ��Ԥ����
 *		(D-1) �����Ԥ����������Ԥ�����ʤ�
 *		(D-2) �����Ԥ���������1�Ĥޤ���ʣ���ˤ��Ԥ�����ʥ������ڴ����ʤ���
 *		(D-3) �����Ԥ���������1�Ĥޤ���ʣ���ˤ��Ԥ�����ʥ������ڴ��������
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
 *		tslp_tsk(1) -> E_TMOUT
 *	== TASK2-1��ͥ���١����1��� ==
 *	2:	snd_mbf(MBF1, string1, 26)
 *	== TASK3��ͥ���١����==
 *	3:	snd_mbf(MBF1, string2, 26)
 *	== TASK1��³����==
 *	4:	ter_tsk(TASK2)									... (A-1)
 *		tslp_tsk(1) -> E_TMOUT
 *	== TASK1��³����==
 *	5:	rcv_mbf(MBF1, buf1) -> 26
 *		assert(strncmp(buf1, string2, 26) == 0)
 *		act_tsk(TASK2)
 *		tslp_tsk(1) -> E_TMOUT
 *	== TASK2-2��ͥ���١����2��� ==
 *	6:	snd_mbf(MBF1, string1, 26)
 *	== TASK3��³����==
 *	7:	snd_mbf(MBF1, string3, 10)
 *	== TASK1��³����==
 *	8:	ter_tsk(TASK2)									... (A-2)
 *		slp_tsk()
 *	== TASK3��³����==
 *	9:	rcv_mbf(MBF1, buf1) -> 10
 *		assert(strncmp(buf1, string3, 10) == 0)
 *	10:	act_tsk(TASK2)
 *	== TASK2-3��ͥ���١����3��� ==
 *	11:	snd_mbf(MBF1, string1, 26)
 *	== TASK3��³����==
 *	12:	wup_tsk(TASK1)
 *	== TASK1��³����==
 *	13:	snd_mbf(MBF1, string3, 10)
 *	== TASK3��³����==
 *	14:	ter_tsk(TASK2)									... (A-3)
 *	== TASK1��³����==
 *	15:	rcv_mbf(MBF1, buf1) -> 10
 *		assert(strncmp(buf1, string3, 10) == 0)
 *		act_tsk(TASK2)
 *		tslp_tsk(1) -> E_TMOUT
 *	== TASK2-4��ͥ���١����4��� ==
 *	16:	snd_mbf(MBF1, string1, 26) -> E_RLWAI
 *	== TASK3��³����==
 *	17:	snd_mbf(MBF1, string2, 26)
 *	== TASK1��³����==
 *	18:	rel_wai(TASK2)									... (B-1)
 *		tslp_tsk(1) -> E_TMOUT
 *	== TASK2-4��³����==
 *	19:	slp_tsk()
 *	== TASK1��³����==
 *	20:	rcv_mbf(MBF1, buf1) -> 26
 *		assert(strncmp(buf1, string2, 26) == 0)
 *		wup_tsk(TASK2)
 *		tslp_tsk(1) -> E_TMOUT
 *	== TASK2-4��³����==
 *	21:	snd_mbf(MBF1, string1, 26) -> E_RLWAI
 *	== TASK3��³����==
 *	22:	snd_mbf(MBF1, string3, 10)
 *	== TASK1��³����==
 *	23:	rel_wai(TASK2)									... (B-2)
 *		slp_tsk()
 *	== TASK2-4��³����==
 *	24:	slp_tsk()
 *	== TASK3��³����==
 *	25:	rcv_mbf(MBF1, buf1) -> 10
 *		assert(strncmp(buf1, string3, 10) == 0)
 *	26:	wup_tsk(TASK2)
 *	== TASK2-4��³����==
 *	27:	snd_mbf(MBF1, string1, 26) -> E_RLWAI
 *	== TASK3��³����==
 *	28:	wup_tsk(TASK1)
 *	== TASK1��³����==
 *	29:	snd_mbf(MBF1, string3, 10)
 *	== TASK3��³����==
 *	30:	rel_wai(TASK2)									... (B-3)
 *	== TASK1��³����==
 *	31:	rcv_mbf(MBF1, buf1) -> 10
 *		assert(strncmp(buf1, string3, 10) == 0)
 *		tslp_tsk(1) -> E_TMOUT
 *	== TASK2-4��³����==
 *	32:	snd_mbf(MBF1, string1, 26) -> E_RLWAI
 *	== TASK3��³����==
 *	33:	snd_mbf(MBF1, string2, 26)
 *	== TASK1��³����==
 *	34:	sta_alm(ALM1, 1U)
 *		slp_tsk()
 *	== ALM1-1 ==
 *	35:	irel_wai(TASK2)									... (C-1)
 *		iwup_tsk(TASK1)
 *		RETURN
 *	== TASK1��³����==
 *	36:	tslp_tsk(1) -> E_TMOUT
 *	== TASK2-4��³����==
 *	37:	slp_tsk()
 *	== TASK1��³����==
 *	38:	rcv_mbf(MBF1, buf1) -> 26
 *		assert(strncmp(buf1, string2, 26) == 0)
 *		wup_tsk(TASK2)
 *		tslp_tsk(1) -> E_TMOUT
 *	== TASK2-4��³����==
 *	39:	snd_mbf(MBF1, string1, 26) -> E_RLWAI
 *	== TASK3��³����==
 *	40:	snd_mbf(MBF1, string3, 10)
 *	== TASK1��³����==
 *	41:	sta_alm(ALM1, 1U)
 *		slp_tsk()
 *	== ALM1-2 ==
 *	42:	irel_wai(TASK2)									... (C-2)
 *		RETURN
 *	== TASK2-4��³����==
 *	43:	slp_tsk()
 *	== TASK3��³����==
 *	44:	rcv_mbf(MBF1, buf1) -> 10
 *		assert(strncmp(buf1, string3, 10) == 0)
 *	45:	wup_tsk(TASK2)
 *	== TASK2-4��³����==
 *	46:	snd_mbf(MBF1, string1, 26) -> E_RLWAI
 *	== TASK3��³����==
 *	47:	wup_tsk(TASK1)
 *	== TASK1��³����==
 *	48:	snd_mbf(MBF1, string3, 10)
 *	== TASK3��³����==
 *	49:	sta_alm(ALM1, 1U)
 *		slp_tsk()
 *	== ALM1-3 ==
 *	50:	irel_wai(TASK2)									... (C-3)
 *		RETURN
 *	== TASK1��³����==
 *	51:	rcv_mbf(MBF1, buf1) -> 10
 *		assert(strncmp(buf1, string3, 10) == 0)
 *		wup_tsk(TASK3)
 *		slp_tsk()
 *	== TASK2-4��³����==
  *	52:	tsnd_mbf(MBF1, string1, 26, 1) -> E_TMOUT		... (D-1)
 *	== TASK3��³����==
 *	53:	snd_mbf(MBF1, string2, 26)
 *	== TASK2-4��³����==
 *	54:	tslp_tsk(1) -> E_TMOUT
 *	== TASK2-4��³����==
 *	55:	rcv_mbf(MBF1, buf1) -> 26
 *		assert(strncmp(buf1, string2, 26) == 0)
 *	56:	tsnd_mbf(MBF1, string1, 26, 1) -> E_TMOUT		... (D-2)
 *	== TASK3��³����==
 *	57:	snd_mbf(MBF1, string3, 10)
 *	== TASK2-4��³����==
 *	58:	slp_tsk()
 *	== TASK3��³����==
 *	59:	rcv_mbf(MBF1, buf1) -> 10
 *		assert(strncmp(buf1, string3, 10) == 0)
 *	60:	wup_tsk(TASK2)
 *	== TASK2-4��³����==
 *	61:	tsnd_mbf(MBF1, string1, 26, 1) -> E_TMOUT		... (D-3)
 *	== TASK3��³����==
 *	62:	wup_tsk(TASK1)
 *	== TASK1��³����==
 *	63:	snd_mbf(MBF1, string3, 10)
 *	== TASK3��³����==
 *	64:	slp_tsk()
 *	== TASK1��³����==
 *	65:	rcv_mbf(MBF1, buf1) -> 10
 *		assert(strncmp(buf1, string3, 10) == 0)
 *		slp_tsk()
 *	== TASK2-4��³����==
 *	66:	END
 */

#include <kernel.h>
#include <t_syslog.h>
#include "kernel_cfg.h"
#include "test_lib.h"
#include "test_messagebuf2.h"
#include <string.h>

const char string1[26] = "abcdefghijklmnopqrstuvwxyz";
const char string2[26] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
const char string3[16] = "0123456789abcdef";

char buf1[26];

extern ER	bit_kernel(void);

/* DO NOT DELETE THIS LINE -- gentest depends on it. */

static uint_t	alarm1_count = 0;

void
alarm1_handler(intptr_t exinf)
{
	ER_UINT	ercd;

	switch (++alarm1_count) {
	case 1:
		check_point(35);
		ercd = irel_wai(TASK2);
		check_ercd(ercd, E_OK);

		ercd = iwup_tsk(TASK1);
		check_ercd(ercd, E_OK);

		return;

		check_point(0);

	case 2:
		check_point(42);
		ercd = irel_wai(TASK2);
		check_ercd(ercd, E_OK);

		return;

		check_point(0);

	case 3:
		check_point(50);
		ercd = irel_wai(TASK2);
		check_ercd(ercd, E_OK);

		return;

		check_point(0);

	default:
		check_point(0);
	}
	check_point(0);
}

void
task1(intptr_t exinf)
{
	ER_UINT	ercd;

	test_start(__FILE__);

	set_bit_func(bit_kernel);

	check_point(1);
	ercd = act_tsk(TASK2);
	check_ercd(ercd, E_OK);

	ercd = act_tsk(TASK3);
	check_ercd(ercd, E_OK);

	ercd = tslp_tsk(1);
	check_ercd(ercd, E_TMOUT);

	check_point(4);
	ercd = ter_tsk(TASK2);
	check_ercd(ercd, E_OK);

	ercd = tslp_tsk(1);
	check_ercd(ercd, E_TMOUT);

	check_point(5);
	ercd = rcv_mbf(MBF1, buf1);
	check_ercd(ercd, 26);

	check_assert(strncmp(buf1, string2, 26) == 0);

	ercd = act_tsk(TASK2);
	check_ercd(ercd, E_OK);

	ercd = tslp_tsk(1);
	check_ercd(ercd, E_TMOUT);

	check_point(8);
	ercd = ter_tsk(TASK2);
	check_ercd(ercd, E_OK);

	ercd = slp_tsk();
	check_ercd(ercd, E_OK);

	check_point(13);
	ercd = snd_mbf(MBF1, string3, 10);
	check_ercd(ercd, E_OK);

	check_point(15);
	ercd = rcv_mbf(MBF1, buf1);
	check_ercd(ercd, 10);

	check_assert(strncmp(buf1, string3, 10) == 0);

	ercd = act_tsk(TASK2);
	check_ercd(ercd, E_OK);

	ercd = tslp_tsk(1);
	check_ercd(ercd, E_TMOUT);

	check_point(18);
	ercd = rel_wai(TASK2);
	check_ercd(ercd, E_OK);

	ercd = tslp_tsk(1);
	check_ercd(ercd, E_TMOUT);

	check_point(20);
	ercd = rcv_mbf(MBF1, buf1);
	check_ercd(ercd, 26);

	check_assert(strncmp(buf1, string2, 26) == 0);

	ercd = wup_tsk(TASK2);
	check_ercd(ercd, E_OK);

	ercd = tslp_tsk(1);
	check_ercd(ercd, E_TMOUT);

	check_point(23);
	ercd = rel_wai(TASK2);
	check_ercd(ercd, E_OK);

	ercd = slp_tsk();
	check_ercd(ercd, E_OK);

	check_point(29);
	ercd = snd_mbf(MBF1, string3, 10);
	check_ercd(ercd, E_OK);

	check_point(31);
	ercd = rcv_mbf(MBF1, buf1);
	check_ercd(ercd, 10);

	check_assert(strncmp(buf1, string3, 10) == 0);

	ercd = tslp_tsk(1);
	check_ercd(ercd, E_TMOUT);

	check_point(34);
	ercd = sta_alm(ALM1, 1U);
	check_ercd(ercd, E_OK);

	ercd = slp_tsk();
	check_ercd(ercd, E_OK);

	check_point(36);
	ercd = tslp_tsk(1);
	check_ercd(ercd, E_TMOUT);

	check_point(38);
	ercd = rcv_mbf(MBF1, buf1);
	check_ercd(ercd, 26);

	check_assert(strncmp(buf1, string2, 26) == 0);

	ercd = wup_tsk(TASK2);
	check_ercd(ercd, E_OK);

	ercd = tslp_tsk(1);
	check_ercd(ercd, E_TMOUT);

	check_point(41);
	ercd = sta_alm(ALM1, 1U);
	check_ercd(ercd, E_OK);

	ercd = slp_tsk();
	check_ercd(ercd, E_OK);

	check_point(48);
	ercd = snd_mbf(MBF1, string3, 10);
	check_ercd(ercd, E_OK);

	check_point(51);
	ercd = rcv_mbf(MBF1, buf1);
	check_ercd(ercd, 10);

	check_assert(strncmp(buf1, string3, 10) == 0);

	ercd = wup_tsk(TASK3);
	check_ercd(ercd, E_OK);

	ercd = slp_tsk();
	check_ercd(ercd, E_OK);

	check_point(63);
	ercd = snd_mbf(MBF1, string3, 10);
	check_ercd(ercd, E_OK);

	check_point(65);
	ercd = rcv_mbf(MBF1, buf1);
	check_ercd(ercd, 10);

	check_assert(strncmp(buf1, string3, 10) == 0);

	ercd = slp_tsk();
	check_ercd(ercd, E_OK);

	check_point(0);
}

static uint_t	task2_count = 0;

void
task2(intptr_t exinf)
{
	ER_UINT	ercd;

	switch (++task2_count) {
	case 1:
		check_point(2);
		ercd = snd_mbf(MBF1, string1, 26);
		check_ercd(ercd, E_OK);

		check_point(0);

	case 2:
		check_point(6);
		ercd = snd_mbf(MBF1, string1, 26);
		check_ercd(ercd, E_OK);

		check_point(0);

	case 3:
		check_point(11);
		ercd = snd_mbf(MBF1, string1, 26);
		check_ercd(ercd, E_OK);

		check_point(0);

	case 4:
		check_point(16);
		ercd = snd_mbf(MBF1, string1, 26);
		check_ercd(ercd, E_RLWAI);

		check_point(19);
		ercd = slp_tsk();
		check_ercd(ercd, E_OK);

		check_point(21);
		ercd = snd_mbf(MBF1, string1, 26);
		check_ercd(ercd, E_RLWAI);

		check_point(24);
		ercd = slp_tsk();
		check_ercd(ercd, E_OK);

		check_point(27);
		ercd = snd_mbf(MBF1, string1, 26);
		check_ercd(ercd, E_RLWAI);

		check_point(32);
		ercd = snd_mbf(MBF1, string1, 26);
		check_ercd(ercd, E_RLWAI);

		check_point(37);
		ercd = slp_tsk();
		check_ercd(ercd, E_OK);

		check_point(39);
		ercd = snd_mbf(MBF1, string1, 26);
		check_ercd(ercd, E_RLWAI);

		check_point(43);
		ercd = slp_tsk();
		check_ercd(ercd, E_OK);

		check_point(46);
		ercd = snd_mbf(MBF1, string1, 26);
		check_ercd(ercd, E_RLWAI);

		check_point(52);
		ercd = tsnd_mbf(MBF1, string1, 26, 1);
		check_ercd(ercd, E_TMOUT);

		check_point(54);
		ercd = tslp_tsk(1);
		check_ercd(ercd, E_TMOUT);

		check_point(55);
		ercd = rcv_mbf(MBF1, buf1);
		check_ercd(ercd, 26);

		check_assert(strncmp(buf1, string2, 26) == 0);

		check_point(56);
		ercd = tsnd_mbf(MBF1, string1, 26, 1);
		check_ercd(ercd, E_TMOUT);

		check_point(58);
		ercd = slp_tsk();
		check_ercd(ercd, E_OK);

		check_point(61);
		ercd = tsnd_mbf(MBF1, string1, 26, 1);
		check_ercd(ercd, E_TMOUT);

		check_finish(66);
		check_point(0);

	default:
		check_point(0);
	}
	check_point(0);
}

void
task3(intptr_t exinf)
{
	ER_UINT	ercd;

	check_point(3);
	ercd = snd_mbf(MBF1, string2, 26);
	check_ercd(ercd, E_OK);

	check_point(7);
	ercd = snd_mbf(MBF1, string3, 10);
	check_ercd(ercd, E_OK);

	check_point(9);
	ercd = rcv_mbf(MBF1, buf1);
	check_ercd(ercd, 10);

	check_assert(strncmp(buf1, string3, 10) == 0);

	check_point(10);
	ercd = act_tsk(TASK2);
	check_ercd(ercd, E_OK);

	check_point(12);
	ercd = wup_tsk(TASK1);
	check_ercd(ercd, E_OK);

	check_point(14);
	ercd = ter_tsk(TASK2);
	check_ercd(ercd, E_OK);

	check_point(17);
	ercd = snd_mbf(MBF1, string2, 26);
	check_ercd(ercd, E_OK);

	check_point(22);
	ercd = snd_mbf(MBF1, string3, 10);
	check_ercd(ercd, E_OK);

	check_point(25);
	ercd = rcv_mbf(MBF1, buf1);
	check_ercd(ercd, 10);

	check_assert(strncmp(buf1, string3, 10) == 0);

	check_point(26);
	ercd = wup_tsk(TASK2);
	check_ercd(ercd, E_OK);

	check_point(28);
	ercd = wup_tsk(TASK1);
	check_ercd(ercd, E_OK);

	check_point(30);
	ercd = rel_wai(TASK2);
	check_ercd(ercd, E_OK);

	check_point(33);
	ercd = snd_mbf(MBF1, string2, 26);
	check_ercd(ercd, E_OK);

	check_point(40);
	ercd = snd_mbf(MBF1, string3, 10);
	check_ercd(ercd, E_OK);

	check_point(44);
	ercd = rcv_mbf(MBF1, buf1);
	check_ercd(ercd, 10);

	check_assert(strncmp(buf1, string3, 10) == 0);

	check_point(45);
	ercd = wup_tsk(TASK2);
	check_ercd(ercd, E_OK);

	check_point(47);
	ercd = wup_tsk(TASK1);
	check_ercd(ercd, E_OK);

	check_point(49);
	ercd = sta_alm(ALM1, 1U);
	check_ercd(ercd, E_OK);

	ercd = slp_tsk();
	check_ercd(ercd, E_OK);

	check_point(53);
	ercd = snd_mbf(MBF1, string2, 26);
	check_ercd(ercd, E_OK);

	check_point(57);
	ercd = snd_mbf(MBF1, string3, 10);
	check_ercd(ercd, E_OK);

	check_point(59);
	ercd = rcv_mbf(MBF1, buf1);
	check_ercd(ercd, 10);

	check_assert(strncmp(buf1, string3, 10) == 0);

	check_point(60);
	ercd = wup_tsk(TASK2);
	check_ercd(ercd, E_OK);

	check_point(62);
	ercd = wup_tsk(TASK1);
	check_ercd(ercd, E_OK);

	check_point(64);
	ercd = slp_tsk();
	check_ercd(ercd, E_OK);

	check_point(0);
}
