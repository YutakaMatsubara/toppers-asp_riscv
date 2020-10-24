/*
 *  TOPPERS Software
 *      Toyohashi Open Platform for Embedded Real-Time Systems
 * 
 *  Copyright (C) 2008-2014 by Embedded and Real-Time Systems Laboratory
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
 *  $Id: test_mutex7.c 2606 2014-01-11 14:15:55Z ertl-hiro $
 */

/* 
 *		�ߥ塼�ƥå����Υƥ���(7)
 *
 * �ڥƥ��Ȥ���Ū��
 *
 *  ͥ���پ�¥ߥ塼�ƥå������Ф��ơ��������ζ�����λ���Υߥ塼�ƥå�
 *  ����Ϣ�ν���������Ū�˥ƥ��Ȥ��롥
 *
 * �ڥƥ��ȹ��ܡ�
 *
 *	(A) �������ζ�����λ����ter_tsk��
 *		(A-1) ��å����Ƥ����ߥ塼�ƥå�����1�ġˤ���å��������뤳�ȡ�
 *		(A-2) ��å����Ƥ����ߥ塼�ƥå�����1�ġˤ���å�������졤���
 *			  �����ԤäƤ�����������������å�����ͥ���٤��Ѳ�������
 *			  ���������뤳�ȡ�
 *		(A-3) (A-2)�η�̡��������ǥ����ѥå��������뤳�ȡ�
 *		(A-4) ��å����Ƥ����ߥ塼�ƥå�����ʣ���ˤ����٤ƥ�å������
 *			  ��뤳�ȡ�
 *		(A-5) ��å����Ƥ����ߥ塼�ƥå�����ʣ���ˤ���å�������졤���
 *			  �����ԤäƤ�����������ʣ���ˤ�������å�����ͥ���٤���
 *			  �������Ԥ��������뤳�ȡ����λ��ˡ���ǥߥ塼�ƥå�����
 *			  ��å���������������˥�å����Ƥ����ߥ塼�ƥå������Ԥ�
 *			  �Ƥ����������ˤ�������ͥ���̤��⤯�ʤ뤳�ȡ�
 *		(A-6) (A-5)�η�̡��������ǥ����ѥå��������뤳�ȡ�
 *
 * �ڥƥ��ȹ��ܤμ¸���ˡ��
 *
 *	(A-1)
 *		��ͥ���٥�������TASK2�ˤ˥ߥ塼�ƥå�����MTX1�ˤ��å���������
 *		�Υ�������TASK1�ˤ���TASK2��ter_tsk����ȡ���å����������뤳
 *		�Ȥ��ǧ���롥
 *	(A-2)
 *		��ͥ���٥�������TASK2�ˤ���ͥ���پ�¥ߥ塼�ƥå�����MTX1�ˤ���
 *		���������̤���ͥ���٥�������TASK3�ˤ�MTX1���Ԥ��������֤ǡ���ͥ
 *		���٥�������TASK1�ˤ���TASK2��ter_tsk����ȡ�TASK3����ͥ���٤�
 *		�ʤä��Ԥ��������뤳�Ȥ��ǧ���롥
 *	(A-3)
 *		��ͥ���٥�������TASK2�ˤ���ͥ���پ�¥ߥ塼�ƥå�����MTX1�ˤ���
 *		���������̤���ͥ���٥�������TASK3�ˤ�MTX1���Ԥ��������֤ǡ��̤�
 *		��ͥ���٥�������TASK1�ˤ���TASK2��ter_tsk����ȡ�TASK3����ͥ��
 *		�٤ˤʤä��Ԥ�������졤TASK3���ڤ괹��뤳�Ȥ��ǧ���롥
 *	(A-4)
 *		��ͥ���٥�������TASK2�ˤ˥ߥ塼�ƥå�����2�ġ�MTX1��MTX2�˥��
 *		���������̤Υ�������TASK1�ˤ���TASK2��ter_tsk����ȡ�ξ���Υ��
 *		�����������뤳�Ȥ��ǧ���롥
 *	(A-5)
 *		��ͥ���٥�������TASK2�ˤ˹�ͥ���پ�¥ߥ塼�ƥå���2�ġ�MTX1��
 *		MTX2�ˤ򤳤ν�ǥ�å��������̤���ͥ���٥�����2�ġ�TASK3��
 *		TASK4�ˤˤ��줾��Υ�å����Ԥ��������֤ǡ���ͥ���٥�����
 *		��TASK1�ˤ���TASK2��ter_tsk����ȡ�TASK3��TASK4����ͥ���٤ˤʤ�
 *		���Ԥ��������뤳�Ȥ��ǧ���롥�ޤ�����˥�å����Ƥ����ߥ塼
 *		�ƥå�����MTX1�ˤ��ԤäƤ�����������TASK3�ˤ���TASK4����ͥ��
 *		��̤��⤯�ʤ뤳�Ȥ��ǧ���롥
 *	(A-6)
 *		��ͥ���٥�������TASK2�ˤ˹�ͥ���پ�¥ߥ塼�ƥå���2�ġ�MTX1��
 *		MTX2�ˤ򤳤ν�ǥ�å��������̤���ͥ���٥�����2�ġ�TASK3��
 *		TASK4�ˤˤ��줾��Υ�å����Ԥ��������֤ǡ��̤���ͥ���٥�����
 *		��TASK1�ˤ���TASK2 ��ter_tsk����ȡ�TASK3��TASK4����ͥ���٤ˤʤ�
 *		���Ԥ�������졤TASK3���ڤ괹��뤳�Ȥ��ǧ���롥
 *
 * �ڻ��ѥ꥽������
 *
 *	TASK1: ��ͥ���٥��������ᥤ�󥿥������ǽ餫�鵯ư
 *	TASK2: ��ͥ���٥�����
 *	TASK3: ��ͥ���٥�����
 *	TASK4: ��ͥ���٥�����
 *	MTX1: �ߥ塼�ƥå�����TA_CEILING°������¤���ͥ���١�
 *	MTX2: �ߥ塼�ƥå�����TA_CEILING°������¤���ͥ���١�
 *
 * �ڥƥ��ȥ������󥹡�
 *
 *	== TASK1��ͥ���١����==
 *		call(set_bit_func(bit_mutex))
 *	1:	act_tsk(TASK2)
 *	2:	slp_tsk()
 *	//		�㡧TASK2
 *	== TASK2-1��ͥ���١����==
 *	3:	loc_mtx(MTX1)
 *	//		�桧TASK2��MTX1��TASK2
 *	4:	wup_tsk(TASK1)
 *	//		�⡧TASK1���桧TASK2��MTX1��TASK2
 *	== TASK1��³����==
 *	5:	ter_tsk(TASK2)			... (A-1)
 *	//		�⡧TASK1
 *	6:	ref_mtx(MTX1, &rmtx)
 *		assert(rmtx.htskid == TSK_NONE)
 *		assert(rmtx.wtskid == TSK_NONE)
 *
 *	7:	act_tsk(TASK2)
 *		act_tsk(TASK3)
 *	8:	slp_tsk()
 *	//		�㡧TASK2��TASK3
 *	== TASK2-2��ͥ���١����==
 *	9:	loc_mtx(MTX1)
 *	//		�桧TASK2���㡧TASK3��MTX1��TASK2
 *	10:	tslp_tsk(10) -> E_TMOUT
 *	//		�㡧TASK3��MTX1��TASK2
 *	== TASK3-1��ͥ���١����==
 *	11:	loc_mtx(MTX1)
 *	//		MTX1��TASK2��TASK3
 *	//		�����ॢ���ȸ�
 *	//		�桧TASK2��MTX1��TASK2��TASK3
 *	== TASK2-2��³����==
 *	12:	wup_tsk(TASK1)
 *	//		�⡧TASK1���桧TASK2��MTX1��TASK2��TASK3
 *	== TASK1��³����==
 *	13:	ter_tsk(TASK2)			... (A-2)
 *	//		�⡧TASK1���桧TASK3��MTX1��TASK3
 *	14:	ref_mtx(MTX1, &rmtx)
 *		assert(rmtx.htskid == TASK3)
 *		assert(rmtx.wtskid == TSK_NONE)
 *		get_pri(TASK3, &tskpri)
 *		assert(tskpri == MID_PRIORITY)
 *	15:	ter_tsk(TASK3)
 *	//		�⡧TASK1
 *
 *	16:	act_tsk(TASK2)
 *		act_tsk(TASK3)
 *	17:	chg_pri(TSK_SELF, LOW_PRIORITY)
 *	//		�㡧TASK2��TASK3��TASK1
 *	== TASK2-3��ͥ���١����==
 *	18:	loc_mtx(MTX1)
 *	//		�桧TASK2���㡧TASK3��TASK1��MTX1��TASK2
 *	19:	slp_tsk()
 *	//		�㡧TASK3��TASK1��MTX1��TASK2
 *	== TASK3-2��ͥ���١����==
 *	20:	loc_mtx(MTX1)
 *	//		�㡧TASK1��MTX1��TASK2��TASK3
 *	== TASK1��³����==
 *	21:	ter_tsk(TASK2)			... (A-3)
 *	//		�桧TASK3���㡧TASK1��MTX1��TASK3
 *	== TASK3-2��³����==
 *	22:	ref_mtx(MTX1, &rmtx)
 *		assert(rmtx.htskid == TASK3)
 *		assert(rmtx.wtskid == TSK_NONE)
 *		get_pri(TASK3, &tskpri)
 *		assert(tskpri == MID_PRIORITY)
 *	23:	ext_tsk() -> noreturn
 *	//		�㡧TASK1
 *	== TASK1��³����==
 *	24:	chg_pri(TSK_SELF, HIGH_PRIORITY)
 *	//		�⡧TASK1
 *
 *	25:	act_tsk(TASK2)
 *	26:	slp_tsk()
 *	//		�㡧TASK2
 *	== TASK2-4��ͥ���١����==
 *	27:	loc_mtx(MTX1)
 *		loc_mtx(MTX2)
 *	//		�桧TASK2��MTX1��TASK2��MTX2��TASK2
 *	28:	wup_tsk(TASK1)
 *	//		�⡧TASK1���桧TASK2��MTX1��TASK2��MTX2��TASK2
 *	== TASK1��³����==
 *	29:	ter_tsk(TASK2)			... (A-4)
 *	//		�⡧TASK1
 *	30:	ref_mtx(MTX1, &rmtx)
 *		assert(rmtx.htskid == TSK_NONE)
 *		assert(rmtx.wtskid == TSK_NONE)
 *		ref_mtx(MTX2, &rmtx)
 *		assert(rmtx.htskid == TSK_NONE)
 *		assert(rmtx.wtskid == TSK_NONE)
 *
 *	31:	act_tsk(TASK2)
 *		act_tsk(TASK3)
 *		act_tsk(TASK4)
 *	32:	slp_tsk()
 *	//		�㡧TASK2��TASK3��TASK4
 *	== TASK2-5��ͥ���١����==
 *	33:	loc_mtx(MTX1)
 *		loc_mtx(MTX2)
 *	//		�桧TASK2���㡧TASK3��TASK4��MTX1��TASK2��MTX2��TASK2
 *	34:	tslp_tsk(10) -> E_TMOUT
 *	//		�㡧TASK3��TASK4��MTX1��TASK2��MTX2��TASK2
 *	== TASK3-3��ͥ���١����==
 *	35:	loc_mtx(MTX1)
 *	//		�㡧TASK4��MTX1��TASK2��TASK3��MTX2��TASK2
 *	== TASK4-1��ͥ���١����==
 *	36:	loc_mtx(MTX2)
 *	//		MTX1��TASK2��TASK3��MTX2��TASK2��TASK4
 *	//		�����ॢ���ȸ�
 *	//		�桧TASK2��MTX1��TASK2��TASK3��MTX2��TASK2��TASK4
 *	== TASK2-5��³����==
 *	37:	wup_tsk(TASK1)
 *	//		�⡧TASK1���桧TASK2��MTX1��TASK2��TASK3��MTX2��TASK2��TASK4
 *	== TASK1��³����==
 *	38:	ter_tsk(TASK2)			... (A-5)
 *	//		�⡧TASK1���桧TASK4��TASK3��MTX1��TASK3��MTX2��TASK4
 *	39:	ref_mtx(MTX1, &rmtx)
 *		assert(rmtx.htskid == TASK3)
 *		assert(rmtx.wtskid == TSK_NONE)
 *		ref_mtx(MTX2, &rmtx)
 *		assert(rmtx.htskid == TASK4)
 *		assert(rmtx.wtskid == TSK_NONE)
 *		get_pri(TASK3, &tskpri)
 *		assert(tskpri == MID_PRIORITY)
 *		get_pri(TASK4, &tskpri)
 *		assert(tskpri == MID_PRIORITY)
 *	40:	chg_pri(TSK_SELF, LOW_PRIORITY)
 *	//		�桧TASK4��TASK3���㡧TASK1��MTX1��TASK3��MTX2��TASK4
 *	== TASK4-1��³����==
 *	41:	ext_tsk() -> noreturn
 *	//		�桧TASK3���㡧TASK1��MTX1��TASK3
 *	== TASK3-3��³����==
 *	42:	ext_tsk() -> noreturn
 *	//		�㡧TASK1
 *	== TASK1��³����==
 *	43:	act_tsk(TASK2)
 *		act_tsk(TASK3)
 *		act_tsk(TASK4)
 *	//		�㡧TASK1��TASK2��TASK3��TASK4
 *	44:	chg_pri(TSK_SELF, LOW_PRIORITY)
 *	//		�㡧TASK2��TASK3��TASK4��TASK1
 *	== TASK2-6��ͥ���١����==
 *	45:	loc_mtx(MTX1)
 *		loc_mtx(MTX2)
 *	//		�桧TASK2���㡧TASK3��TASK4��TASK1��MTX1��TASK2��MTX2��TASK2
 *	46:	slp_tsk()
 *	//		�㡧TASK3��TASK4��TASK1��MTX1��TASK2��MTX2��TASK2
 *	== TASK3-4��ͥ���١����==
 *	47:	loc_mtx(MTX1)
 *	//		�㡧TASK4��TASK1��MTX1��TASK2��TASK3��MTX2��TASK2
 *	== TASK4-2��ͥ���١����==
 *	48:	loc_mtx(MTX2)
 *	//		�㡧TASK1��MTX1��TASK2��TASK3��MTX2��TASK2��TASK4
 *	== TASK1��³����==
 *	49:	ter_tsk(TASK2)			... (A-6)
 *	//		�桧TASK4��TASK3���㡧TASK1��MTX1��TASK3��MTX2��TASK4
 *	== TASK4-2��³����==
 *	50:	ref_mtx(MTX1, &rmtx)
 *		assert(rmtx.htskid == TASK3)
 *		assert(rmtx.wtskid == TSK_NONE)
 *		ref_mtx(MTX2, &rmtx)
 *		assert(rmtx.htskid == TASK4)
 *		assert(rmtx.wtskid == TSK_NONE)
 *		get_pri(TASK3, &tskpri)
 *		assert(tskpri == MID_PRIORITY)
 *		get_pri(TASK4, &tskpri)
 *		assert(tskpri == MID_PRIORITY)
 *	51:	ext_tsk() -> noreturn
 *	//		�桧TASK3���㡧TASK1��MTX1��TASK3
 *	== TASK3-4��³����==
 *	52:	ext_tsk() -> noreturn
 *	//		�㡧TASK1
 *	== TASK1��³����==
 *	53:	END
 */

#include <kernel.h>
#include <t_syslog.h>
#include "kernel_cfg.h"
#include "test_lib.h"
#include "test_mutex7.h"

extern ER	bit_mutex(void);

/* DO NOT DELETE THIS LINE -- gentest depends on it. */

void
task1(intptr_t exinf)
{
	ER_UINT	ercd;
	PRI		tskpri;
	T_RMTX	rmtx;

	test_start(__FILE__);

	set_bit_func(bit_mutex);

	check_point(1);
	ercd = act_tsk(TASK2);
	check_ercd(ercd, E_OK);

	check_point(2);
	ercd = slp_tsk();
	check_ercd(ercd, E_OK);

	check_point(5);
	ercd = ter_tsk(TASK2);
	check_ercd(ercd, E_OK);

	check_point(6);
	ercd = ref_mtx(MTX1, &rmtx);
	check_ercd(ercd, E_OK);

	check_assert(rmtx.htskid == TSK_NONE);

	check_assert(rmtx.wtskid == TSK_NONE);

	check_point(7);
	ercd = act_tsk(TASK2);
	check_ercd(ercd, E_OK);

	ercd = act_tsk(TASK3);
	check_ercd(ercd, E_OK);

	check_point(8);
	ercd = slp_tsk();
	check_ercd(ercd, E_OK);

	check_point(13);
	ercd = ter_tsk(TASK2);
	check_ercd(ercd, E_OK);

	check_point(14);
	ercd = ref_mtx(MTX1, &rmtx);
	check_ercd(ercd, E_OK);

	check_assert(rmtx.htskid == TASK3);

	check_assert(rmtx.wtskid == TSK_NONE);

	ercd = get_pri(TASK3, &tskpri);
	check_ercd(ercd, E_OK);

	check_assert(tskpri == MID_PRIORITY);

	check_point(15);
	ercd = ter_tsk(TASK3);
	check_ercd(ercd, E_OK);

	check_point(16);
	ercd = act_tsk(TASK2);
	check_ercd(ercd, E_OK);

	ercd = act_tsk(TASK3);
	check_ercd(ercd, E_OK);

	check_point(17);
	ercd = chg_pri(TSK_SELF, LOW_PRIORITY);
	check_ercd(ercd, E_OK);

	check_point(21);
	ercd = ter_tsk(TASK2);
	check_ercd(ercd, E_OK);

	check_point(24);
	ercd = chg_pri(TSK_SELF, HIGH_PRIORITY);
	check_ercd(ercd, E_OK);

	check_point(25);
	ercd = act_tsk(TASK2);
	check_ercd(ercd, E_OK);

	check_point(26);
	ercd = slp_tsk();
	check_ercd(ercd, E_OK);

	check_point(29);
	ercd = ter_tsk(TASK2);
	check_ercd(ercd, E_OK);

	check_point(30);
	ercd = ref_mtx(MTX1, &rmtx);
	check_ercd(ercd, E_OK);

	check_assert(rmtx.htskid == TSK_NONE);

	check_assert(rmtx.wtskid == TSK_NONE);

	ercd = ref_mtx(MTX2, &rmtx);
	check_ercd(ercd, E_OK);

	check_assert(rmtx.htskid == TSK_NONE);

	check_assert(rmtx.wtskid == TSK_NONE);

	check_point(31);
	ercd = act_tsk(TASK2);
	check_ercd(ercd, E_OK);

	ercd = act_tsk(TASK3);
	check_ercd(ercd, E_OK);

	ercd = act_tsk(TASK4);
	check_ercd(ercd, E_OK);

	check_point(32);
	ercd = slp_tsk();
	check_ercd(ercd, E_OK);

	check_point(38);
	ercd = ter_tsk(TASK2);
	check_ercd(ercd, E_OK);

	check_point(39);
	ercd = ref_mtx(MTX1, &rmtx);
	check_ercd(ercd, E_OK);

	check_assert(rmtx.htskid == TASK3);

	check_assert(rmtx.wtskid == TSK_NONE);

	ercd = ref_mtx(MTX2, &rmtx);
	check_ercd(ercd, E_OK);

	check_assert(rmtx.htskid == TASK4);

	check_assert(rmtx.wtskid == TSK_NONE);

	ercd = get_pri(TASK3, &tskpri);
	check_ercd(ercd, E_OK);

	check_assert(tskpri == MID_PRIORITY);

	ercd = get_pri(TASK4, &tskpri);
	check_ercd(ercd, E_OK);

	check_assert(tskpri == MID_PRIORITY);

	check_point(40);
	ercd = chg_pri(TSK_SELF, LOW_PRIORITY);
	check_ercd(ercd, E_OK);

	check_point(43);
	ercd = act_tsk(TASK2);
	check_ercd(ercd, E_OK);

	ercd = act_tsk(TASK3);
	check_ercd(ercd, E_OK);

	ercd = act_tsk(TASK4);
	check_ercd(ercd, E_OK);

	check_point(44);
	ercd = chg_pri(TSK_SELF, LOW_PRIORITY);
	check_ercd(ercd, E_OK);

	check_point(49);
	ercd = ter_tsk(TASK2);
	check_ercd(ercd, E_OK);

	check_finish(53);
	check_point(0);
}

static uint_t	task2_count = 0;

void
task2(intptr_t exinf)
{
	ER_UINT	ercd;

	switch (++task2_count) {
	case 1:
		check_point(3);
		ercd = loc_mtx(MTX1);
		check_ercd(ercd, E_OK);

		check_point(4);
		ercd = wup_tsk(TASK1);
		check_ercd(ercd, E_OK);

		check_point(0);

	case 2:
		check_point(9);
		ercd = loc_mtx(MTX1);
		check_ercd(ercd, E_OK);

		check_point(10);
		ercd = tslp_tsk(10);
		check_ercd(ercd, E_TMOUT);

		check_point(12);
		ercd = wup_tsk(TASK1);
		check_ercd(ercd, E_OK);

		check_point(0);

	case 3:
		check_point(18);
		ercd = loc_mtx(MTX1);
		check_ercd(ercd, E_OK);

		check_point(19);
		ercd = slp_tsk();
		check_ercd(ercd, E_OK);

		check_point(0);

	case 4:
		check_point(27);
		ercd = loc_mtx(MTX1);
		check_ercd(ercd, E_OK);

		ercd = loc_mtx(MTX2);
		check_ercd(ercd, E_OK);

		check_point(28);
		ercd = wup_tsk(TASK1);
		check_ercd(ercd, E_OK);

		check_point(0);

	case 5:
		check_point(33);
		ercd = loc_mtx(MTX1);
		check_ercd(ercd, E_OK);

		ercd = loc_mtx(MTX2);
		check_ercd(ercd, E_OK);

		check_point(34);
		ercd = tslp_tsk(10);
		check_ercd(ercd, E_TMOUT);

		check_point(37);
		ercd = wup_tsk(TASK1);
		check_ercd(ercd, E_OK);

		check_point(0);

	case 6:
		check_point(45);
		ercd = loc_mtx(MTX1);
		check_ercd(ercd, E_OK);

		ercd = loc_mtx(MTX2);
		check_ercd(ercd, E_OK);

		check_point(46);
		ercd = slp_tsk();
		check_ercd(ercd, E_OK);

		check_point(0);

	default:
		check_point(0);
	}
	check_point(0);
}

static uint_t	task3_count = 0;

void
task3(intptr_t exinf)
{
	ER_UINT	ercd;
	PRI		tskpri;
	T_RMTX	rmtx;

	switch (++task3_count) {
	case 1:
		check_point(11);
		ercd = loc_mtx(MTX1);
		check_ercd(ercd, E_OK);

		check_point(0);

	case 2:
		check_point(20);
		ercd = loc_mtx(MTX1);
		check_ercd(ercd, E_OK);

		check_point(22);
		ercd = ref_mtx(MTX1, &rmtx);
		check_ercd(ercd, E_OK);

		check_assert(rmtx.htskid == TASK3);

		check_assert(rmtx.wtskid == TSK_NONE);

		ercd = get_pri(TASK3, &tskpri);
		check_ercd(ercd, E_OK);

		check_assert(tskpri == MID_PRIORITY);

		check_point(23);
		ercd = ext_tsk();

		check_point(0);

	case 3:
		check_point(35);
		ercd = loc_mtx(MTX1);
		check_ercd(ercd, E_OK);

		check_point(42);
		ercd = ext_tsk();

		check_point(0);

	case 4:
		check_point(47);
		ercd = loc_mtx(MTX1);
		check_ercd(ercd, E_OK);

		check_point(52);
		ercd = ext_tsk();

		check_point(0);

	default:
		check_point(0);
	}
	check_point(0);
}

static uint_t	task4_count = 0;

void
task4(intptr_t exinf)
{
	ER_UINT	ercd;
	PRI		tskpri;
	T_RMTX	rmtx;

	switch (++task4_count) {
	case 1:
		check_point(36);
		ercd = loc_mtx(MTX2);
		check_ercd(ercd, E_OK);

		check_point(41);
		ercd = ext_tsk();

		check_point(0);

	case 2:
		check_point(48);
		ercd = loc_mtx(MTX2);
		check_ercd(ercd, E_OK);

		check_point(50);
		ercd = ref_mtx(MTX1, &rmtx);
		check_ercd(ercd, E_OK);

		check_assert(rmtx.htskid == TASK3);

		check_assert(rmtx.wtskid == TSK_NONE);

		ercd = ref_mtx(MTX2, &rmtx);
		check_ercd(ercd, E_OK);

		check_assert(rmtx.htskid == TASK4);

		check_assert(rmtx.wtskid == TSK_NONE);

		ercd = get_pri(TASK3, &tskpri);
		check_ercd(ercd, E_OK);

		check_assert(tskpri == MID_PRIORITY);

		ercd = get_pri(TASK4, &tskpri);
		check_ercd(ercd, E_OK);

		check_assert(tskpri == MID_PRIORITY);

		check_point(51);
		ercd = ext_tsk();

		check_point(0);

	default:
		check_point(0);
	}
	check_point(0);
}
