/*
 *  TOPPERS Software
 *      Toyohashi Open Platform for Embedded Real-Time Systems
 * 
 *  Copyright (C) 2008-2013 by Embedded and Real-Time Systems Laboratory
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
 *  $Id: test_sem2.c 2534 2013-10-13 12:27:37Z ertl-hiro $
 */

/* 
 *		���ޥե���ǽ�Υƥ���(2)
 *
 * �ڥƥ��Ȥ���Ū��
 *
 *  isig_sem��sig_sem�Ȥΰ㤤���濴�˥ƥ��Ȥ��롥
 *  pol_sem��twai_sem��wai_sem�Ȥΰ㤤���濴�˥ƥ��Ȥ��롥
 *
 * �ڥƥ��ȹ��ܡ�
 *
 *	(A) isig_sem����Ū���顼�Υƥ���
 *		(A-1) ����������ƥ����Ȥ���θƽФ�
 *		(A-2) CPU��å����֤���θƽФ�
 *	(B) isig_sem�ˤ�ꥻ�ޥե��Ԥ����֤Υ��������Ԥ���������
 *		(B-1) �����ɥ���֤��顤�Ԥ�������줿���������ڤ괹���
 *		(B-2) �¹Ծ��֤Υ��������顤�Ԥ�������줿���������ڤ괹���
 *		(B-3) �ǥ����ѥå���α���֤ǡ��ڤ괹���ʤ�
 *		(B-4) �Ԥ�������줿�������������Ԥ����֤ǡ��ڤ괹���ʤ�
 *		(B-5) �Ԥ�������줿��������ͥ���٤��㤯���ڤ괹���ʤ�
 *	(C) pol_sem����Ū���顼�Υƥ���
 *		(C-1) �󥿥�������ƥ����Ȥ���θƽФ�
 *		(C-2) CPU��å����֤���θƽФ�
 *		(C-3) �ǥ����ѥå��ػ߾��֤���θƽФ���E_CTX���顼�ˤʤ�ʤ���
 *		(C-4) �����ͥ���٥ޥ���������Ǥʤ����֤���θƽФ���E_CTX���顼
 *		      �ˤʤ�ʤ���
 *	(D) pol_sem�ǥݡ���󥰼��Ԥ���
 *	(E) twai_sem����Ū���顼�Υƥ���
 *		(E-1) �󥿥�������ƥ����Ȥ���θƽФ�
 *		(E-2) CPU��å����֤���θƽФ�
 *		(E-3) �ǥ����ѥå��ػ߾��֤���θƽФ�
 *		(E-4) �����ͥ���٥ޥ���������Ǥʤ����֤���θƽФ�
 *		(E-5) tmout������
 *	(F) twai_sem��tmout=TMO_POL�λ��˥ݡ���󥰼��Ԥ���
 *	(G) twai_sem��tmout=TMO_FEVR�λ��˥��ޥե��Ԥ����֤ˤʤ�
 *	(H) twai_sem��tmout�˥����ॢ���Ȥ����ꤷ�����ˡ������ॢ�����դ���
 *		���ޥե��Ԥ����֤ˤʤ�
 *
 * �ڻ��ѥ꥽������
 *
 *	TASK1: ��ͥ���٥�������TA_ACT°��
 *	TASK2: ��ͥ���٥�����
 *	TASK3: ��ͥ���٥�����
 *	TASK4: ��ͥ���٥�����
 *	TASK5: ��ͥ���٥�����
 *	ALM1:  ���顼��ϥ�ɥ�
 *  SEM1:  TA_NULL°��������񸻿�1������񸻿�1
 *
 * �ڥƥ��ȥ������󥹡�
 *
 *	== TASK1��ͥ���١����==
 *  1:	isig_sem(SEM1) -> E_CTX				... (A-1)
 *	2:	loc_cpu()
 *		pol_sem(SEM1) -> E_CTX				... (C-2)
 *		twai_sem(SEM1, TMO_POL) -> E_CTX	... (E-2)
 *		unl_cpu()
 *	3:	dis_dsp()
 *		pol_sem(SEM1)						... (C-3)
 *		twai_sem(SEM1, TMO_POL) -> E_CTX	... (E-3)
 *		ena_dsp()
 *	4:	chg_ipm(TMAX_INTPRI)
 *		pol_sem(SEM1) -> E_TMOUT			... (C-4)(D)
 *		twai_sem(SEM1, TMO_POL) -> E_CTX	... (E-4)
 *		chg_ipm(TIPM_ENAALL)
 *	5:	twai_sem(SEM1, -2) -> E_PAR			... (E-5)
 *		twai_sem(SEM1, TMO_POL) -> E_TMOUT	... (F)
 *	6:	sta_alm(ALM1, 10)
 *	7:	twai_sem(SEM1, TMO_FEVR)			... (G)
 *	== ALM1-1 ==
 *	8:	pol_sem(SEM1) -> E_CTX				... (C-1)
 *		twai_sem(SEM1, TMO_POL) -> E_CTX	... (E-1)
 *	9:	iloc_cpu()
 *		isig_sem(SEM1) -> E_CTX				... (A-2)
 *		iunl_cpu()
 *	10:	isig_sem(SEM1)						... (B-1)
 *		RETURN
 *	== TASK1��³����==
 *	11:	act_tsk(TASK3)
 *	12:	wai_sem(SEM1)
 *	== TASK3��ͥ���١����==
 *	13:	sta_alm(ALM1, 10)
 *		call(wait_var())
 *	== ALM1-2 ==
 *	14:	isig_sem(SEM1)						... (B-2)
 *		call(signal_var())
 *		RETURN
 *	== TASK1��³����==
 *	15:	wai_sem(SEM1)
 *	== TASK3��³����==
 *	16:	sta_alm(ALM1, 10)
 *		dis_dsp()
 *		call(wait_var())
 *	== ALM1-3 ==
 *	17:	isig_sem(SEM1)						... (B-3)
 *		call(signal_var())
 *		RETURN
 *	== TASK3��³����==
 *	18:	ena_dsp()
 *	== TASK1��³����==
 *	19:	wai_sem(SEM1)
 *	== TASK3��³����==
 *	20:	sta_alm(ALM1, 10)
 *		sus_tsk(TASK1)
 *		call(wait_var())
 *	== ALM1-4 ==
 *	21:	isig_sem(SEM1)						... (B-4)
 *		call(signal_var())
 *		RETURN
 *	== TASK3��³����==
 *	22:	rsm_tsk(TASK1)
 *	== TASK1��³����==
 *	23:	act_tsk(TASK2)
 *	== TASK2��ͥ���١����==
 *	24:	tslp_tsk(10) -> E_TMOUT
 *	== TASK1��³����==
 *	25:	wai_sem(SEM1)
 *	== TASK3��³����==
 *	26:	ext_tsk() -> noreturn
 *	== TASK2��³����==
 *	27:	sta_alm(ALM1, 10)
 *		call(wait_var())
 *	== ALM1-5 ==
 *	28:	isig_sem(SEM1)						... (B-5)
 *		call(signal_var())
 *		RETURN
 *	== TASK2��³����==
 *	29:	ext_tsk() -> noreturn
 *	== TASK1��³����==
 *	30:	sta_alm(ALM1, 10)
 *	31:	twai_sem(SEM1, 100) -> E_RLWAI
 *	== ALM1-6 ==
 *	32:	irel_wai(TASK1)
 *		RETURN
 *	== TASK1��³����==
 *	33:	sta_alm(ALM1, 100)
 *	34:	twai_sem(SEM1, 10) -> E_TMOUT		... (H)
 *	35:	stp_alm(ALM1)
 *	36:	END
 */

#include <kernel.h>
#include <test_lib.h>
#include <t_syslog.h>
#include "kernel_cfg.h"
#include "test_sem2.h"

static volatile bool_t	flagvar;

static void
wait_var(void)
{
	flagvar = false;
	while (!flagvar);
}

static void
signal_var(void)
{
	flagvar = true;
}

/* DO NOT DELETE THIS LINE -- gentest depends on it. */

static uint_t	alarm1_count = 0;

void
alarm1_handler(intptr_t exinf)
{
	ER_UINT	ercd;

	switch (++alarm1_count) {
	case 1:
		check_point(8);
		ercd = pol_sem(SEM1);
		check_ercd(ercd, E_CTX);

		ercd = twai_sem(SEM1, TMO_POL);
		check_ercd(ercd, E_CTX);

		check_point(9);
		ercd = iloc_cpu();
		check_ercd(ercd, E_OK);

		ercd = isig_sem(SEM1);
		check_ercd(ercd, E_CTX);

		ercd = iunl_cpu();
		check_ercd(ercd, E_OK);

		check_point(10);
		ercd = isig_sem(SEM1);
		check_ercd(ercd, E_OK);

		return;

		check_point(0);

	case 2:
		check_point(14);
		ercd = isig_sem(SEM1);
		check_ercd(ercd, E_OK);

		signal_var();

		return;

		check_point(0);

	case 3:
		check_point(17);
		ercd = isig_sem(SEM1);
		check_ercd(ercd, E_OK);

		signal_var();

		return;

		check_point(0);

	case 4:
		check_point(21);
		ercd = isig_sem(SEM1);
		check_ercd(ercd, E_OK);

		signal_var();

		return;

		check_point(0);

	case 5:
		check_point(28);
		ercd = isig_sem(SEM1);
		check_ercd(ercd, E_OK);

		signal_var();

		return;

		check_point(0);

	case 6:
		check_point(32);
		ercd = irel_wai(TASK1);
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

	check_point(1);
	ercd = isig_sem(SEM1);
	check_ercd(ercd, E_CTX);

	check_point(2);
	ercd = loc_cpu();
	check_ercd(ercd, E_OK);

	ercd = pol_sem(SEM1);
	check_ercd(ercd, E_CTX);

	ercd = twai_sem(SEM1, TMO_POL);
	check_ercd(ercd, E_CTX);

	ercd = unl_cpu();
	check_ercd(ercd, E_OK);

	check_point(3);
	ercd = dis_dsp();
	check_ercd(ercd, E_OK);

	ercd = pol_sem(SEM1);
	check_ercd(ercd, E_OK);

	ercd = twai_sem(SEM1, TMO_POL);
	check_ercd(ercd, E_CTX);

	ercd = ena_dsp();
	check_ercd(ercd, E_OK);

	check_point(4);
	ercd = chg_ipm(TMAX_INTPRI);
	check_ercd(ercd, E_OK);

	ercd = pol_sem(SEM1);
	check_ercd(ercd, E_TMOUT);

	ercd = twai_sem(SEM1, TMO_POL);
	check_ercd(ercd, E_CTX);

	ercd = chg_ipm(TIPM_ENAALL);
	check_ercd(ercd, E_OK);

	check_point(5);
	ercd = twai_sem(SEM1, -2);
	check_ercd(ercd, E_PAR);

	ercd = twai_sem(SEM1, TMO_POL);
	check_ercd(ercd, E_TMOUT);

	check_point(6);
	ercd = sta_alm(ALM1, 10);
	check_ercd(ercd, E_OK);

	check_point(7);
	ercd = twai_sem(SEM1, TMO_FEVR);
	check_ercd(ercd, E_OK);

	check_point(11);
	ercd = act_tsk(TASK3);
	check_ercd(ercd, E_OK);

	check_point(12);
	ercd = wai_sem(SEM1);
	check_ercd(ercd, E_OK);

	check_point(15);
	ercd = wai_sem(SEM1);
	check_ercd(ercd, E_OK);

	check_point(19);
	ercd = wai_sem(SEM1);
	check_ercd(ercd, E_OK);

	check_point(23);
	ercd = act_tsk(TASK2);
	check_ercd(ercd, E_OK);

	check_point(25);
	ercd = wai_sem(SEM1);
	check_ercd(ercd, E_OK);

	check_point(30);
	ercd = sta_alm(ALM1, 10);
	check_ercd(ercd, E_OK);

	check_point(31);
	ercd = twai_sem(SEM1, 100);
	check_ercd(ercd, E_RLWAI);

	check_point(33);
	ercd = sta_alm(ALM1, 100);
	check_ercd(ercd, E_OK);

	check_point(34);
	ercd = twai_sem(SEM1, 10);
	check_ercd(ercd, E_TMOUT);

	check_point(35);
	ercd = stp_alm(ALM1);
	check_ercd(ercd, E_OK);

	check_finish(36);
	check_point(0);
}

void
task2(intptr_t exinf)
{
	ER_UINT	ercd;

	check_point(24);
	ercd = tslp_tsk(10);
	check_ercd(ercd, E_TMOUT);

	check_point(27);
	ercd = sta_alm(ALM1, 10);
	check_ercd(ercd, E_OK);

	wait_var();

	check_point(29);
	ercd = ext_tsk();

	check_point(0);
}

void
task3(intptr_t exinf)
{
	ER_UINT	ercd;

	check_point(13);
	ercd = sta_alm(ALM1, 10);
	check_ercd(ercd, E_OK);

	wait_var();

	check_point(16);
	ercd = sta_alm(ALM1, 10);
	check_ercd(ercd, E_OK);

	ercd = dis_dsp();
	check_ercd(ercd, E_OK);

	wait_var();

	check_point(18);
	ercd = ena_dsp();
	check_ercd(ercd, E_OK);

	check_point(20);
	ercd = sta_alm(ALM1, 10);
	check_ercd(ercd, E_OK);

	ercd = sus_tsk(TASK1);
	check_ercd(ercd, E_OK);

	wait_var();

	check_point(22);
	ercd = rsm_tsk(TASK1);
	check_ercd(ercd, E_OK);

	check_point(26);
	ercd = ext_tsk();

	check_point(0);
}
