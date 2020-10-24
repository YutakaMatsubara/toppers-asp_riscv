/*
 *  TOPPERS Software
 *      Toyohashi Open Platform for Embedded Real-Time Systems
 * 
 *  Copyright (C) 2007-2013 by Embedded and Real-Time Systems Laboratory
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
 *  $Id: test_tex2.c 2596 2014-01-02 12:21:31Z ertl-hiro $
 */

/* 
 *		�������㳰�����˴ؤ���ƥ���(2)
 *
 * �ڥƥ��Ȥ���Ū��
 *
 *  ����ߥϥ�ɥ�ʥ��顼��ϥ�ɥ�ˤ����CPU�㳰�ϥ�ɥ餫�饿������
 *  �������롼�����ư�������������Ū�˥ƥ��Ȥ��롥
 *
 * �ڥƥ��ȹ��ܡ�
 *
 *	(A) iras_tex�Υ��顼����
 *		(A-1) �оݥ��������ٻ߾���
 *		(A-2) �оݥ������Υ������㳰�����롼�����������Ƥ��ʤ�
 *	(B) ����ߥϥ�ɥ餫��ƤФ줿iras_tex���������
 *		(B-1) �оݥ��������¹Ծ��֤Υ��������ĥ������㳰��������
 *		(B-2) �оݥ��������¹Ծ��֤Υ������Ǥʤ�
 *		(B-3) �оݥ��������¹Ծ��֤Υ����������������㳰�����ػ�
 *	(C) CPU�㳰�ϥ�ɥ餫��ƤФ줿iras_tex���������
 *		(C-1) �оݥ��������¹Ծ��֤Υ��������ĥ������㳰��������
 *		(C-2) �оݥ��������¹Ծ��֤Υ������Ǥʤ�
 *		(C-3) �оݥ��������¹Ծ��֤Υ����������������㳰�����ػ�
 *				�� �»ܤ��ʤ��ʥ������å����¸�˼¸��Ǥ��ʤ���
 *	(D) ����ߥϥ�ɥ�νи������ˤ�뵯ư
 *		(D-1) �ǥ����ѥå���Υ��������������㳰���Ĥǥ������㳰������
 *			  �ᤢ��
 *	(E) CPU�㳰�ϥ�ɥ�νи������ˤ�뵯ư
 *		(E-1) �ǥ����ѥå���Υ��������������㳰���Ĥǥ������㳰������
 *			  �ᤢ��
 *	(F) sns_tex�Ǽ¹Ծ��֤Υ��������ʤ�
 *
 * �ڻ��ѥ꥽������
 *
 *	TASK1: �ᥤ��Υ��������¹Ծ��֤Υ��������Ф��ƥ������㳰�������׵᤹
 *		   ���оݥ�����
 *	TASK2: �¹Ծ��֤Ǥʤ����������Ф��ƥ������㳰�������׵᤹���оݥ�����
 *	TASK3: �������㳰�����롼�����������Ƥ��ʤ�������
 *	TASK4: �ٻ߾��֤Υ�����
 *	ALM1:  ���顼��ϥ�ɥ�1
 *	ALM2:  ���顼��ϥ�ɥ�2
 *	ALM3:  ���顼��ϥ�ɥ�3
 *	CPUEXC: CPU�㳰�ϥ�ɥ�
 *
 * �ڥƥ��ȥ������󥹡�
 *
 *	== TASK1��ͥ���١�10��==
 *	1:	state(false, false, TIPM_ENAALL, false, false, true)
 *		ref_tex(TSK_SELF, &rtex)
 *		assert((rtex.texstat & TTEX_DIS) != 0U)
 *		assert(rtex.pndptn == 0U)
 *	2:	sta_alm(ALM1, 1U)
 *		DO(while (!(alm1_flag)))	... ���顼��ϥ�ɥ�1�μ¹Ԥ��Ԥ�
 *	== ALM1 ==
 *	3:	state_i(true, false, false, true, true)
 *		iras_tex(TASK3, 0x0001) -> E_OBJ		... (A-2)
 *		iras_tex(TASK4, 0x0001) -> E_OBJ		... (A-1)
 *		iras_tex(TASK2, 0x0001)					... (B-2)
 *		iras_tex(TASK1, 0x0001)					... (B-3)
 *		DO(alm1_flag = true)
 *		RETURN
 *	== TASK1��³����==
 *	4:	ena_tex()
 *	== TASK1-TEX-1��1���ܡ�==
 *	5:	assert(texptn == 0x0001)
 *		state(false, false, TIPM_ENAALL, false, false, true)
 *	6:	dis_dsp() ... 4�Ĥξ��֤򤽤줾���Ѳ�������
 *		chg_ipm(TMAX_INTPRI)
 *		ena_tex()
 *		loc_cpu()
 *		state(false, true, TMAX_INTPRI, true, true, false)
 *		RETURN
 *	== TASK1��³����==
 *	7:	state(false, false, TIPM_ENAALL, false, false, false)
 *		ref_tex(TSK_SELF, &rtex)
 *		assert((rtex.texstat & TTEX_ENA) != 0U)
 *		assert(rtex.pndptn == 0U)
 *	8:	sta_alm(ALM2, 1U)
 *		DO(while (!(alm2_flag)))
 *	== ALM2 ==
 *	9:	state_i(true, false, false, true, false)
 *		iras_tex(TASK1, 0x0002)					... (B-1)
 *		DO(alm2_flag = true)
 *		RETURN									... (D-1)
 *	== TASK1-TEX-2��2���ܡ�==
 *	10:	assert(texptn == 0x0002)
 *		state(false, false, TIPM_ENAALL, false, false, true)
 *		RETURN
 *	== TASK1��³����==
 *	11:	sus_tsk(TASK2)
 *		sus_tsk(TASK3)
 *	12:	sta_alm(ALM3, 10U)
 *	13:	dly_tsk(50U)
 *	== ALM3 ==
 *	14:	state_i(true, false, false, true, true)	... (F)��sns_tex()��ޤ��
 *		iget_tid(&tskid)
 *		assert(tskid == TSK_NONE)
 *		iras_tex(TASK1, 0x0004)
 *		DO(alm3_flag = true)
 *		RETURN
 *	== TASK1-TEX-3��3���ܡ�==
 *	15:	assert(texptn == 0x0004)
 *		state(false, false, TIPM_ENAALL, false, false, true)
 *		RETURN
 *	== TASK1��³����==
 *	16:	rsm_tsk(TASK2)
 *		rsm_tsk(TASK3)
 *		dis_dsp()
 *	17:	DO(RAISE_CPU_EXCEPTION)
 *	== CPUEXC ==
 *	18:	state_i(true, false, true, true, false)
 *		assert(xsns_xpn(p_excinf) == false)
 *		iras_tex(TASK3, 0x0010) -> E_OBJ		... (A-2)
 *		iras_tex(TASK4, 0x0010) -> E_OBJ		... (A-1)
 *		iras_tex(TASK2, 0x0010)					... (C-2)
 *		iras_tex(TASK1, 0x0010)					... (C-1)
 *		RETURN									... (E-1)
 *	== TASK1-TEX-4��4���ܡ�==
 *	19:	assert(texptn == 0x0010)
 *		state(false, false, TIPM_ENAALL, true, true, true)
 *	20:	ext_tsk()
 *	== TASK2��ͥ���١�10��==
 *	21:	state(false, false, TIPM_ENAALL, false, false, true)
 *	22:	ena_tex()
 *	== TASK2-TEX ==
 *	23:	assert(texptn == 0x0011)
 *		state(false, false, TIPM_ENAALL, false, false, true)
 *		RETURN
 *	== TASK2��³����==
 *	24:	sus_tsk(TASK3)
 *	25:	END
 */

#include <kernel.h>
#include <test_lib.h>
#include <t_syslog.h>
#include "kernel_cfg.h"
#include "test_tex2.h"

volatile bool_t	alm1_flag = false;
volatile bool_t	alm2_flag = false;
volatile bool_t	alm3_flag = false;

/*
 *  task3��task4��tex_task4����������ʤ�
 */

void
task3(intptr_t exinf)
{
	check_point(0);
}

void
task4(intptr_t exinf)
{
	check_point(0);
}

void
tex_task4(TEXPTN texptn, intptr_t exinf)
{
	check_point(0);
}

/* DO NOT DELETE THIS LINE -- gentest depends on it. */

void
alarm1_handler(intptr_t exinf)
{
	ER_UINT	ercd;

	check_point(3);
	check_state_i(true, false, false, true, true);

	ercd = iras_tex(TASK3, 0x0001);
	check_ercd(ercd, E_OBJ);

	ercd = iras_tex(TASK4, 0x0001);
	check_ercd(ercd, E_OBJ);

	ercd = iras_tex(TASK2, 0x0001);
	check_ercd(ercd, E_OK);

	ercd = iras_tex(TASK1, 0x0001);
	check_ercd(ercd, E_OK);

	alm1_flag = true;

	return;

	check_point(0);
}

void
alarm2_handler(intptr_t exinf)
{
	ER_UINT	ercd;

	check_point(9);
	check_state_i(true, false, false, true, false);

	ercd = iras_tex(TASK1, 0x0002);
	check_ercd(ercd, E_OK);

	alm2_flag = true;

	return;

	check_point(0);
}

void
alarm3_handler(intptr_t exinf)
{
	ID		tskid;
	ER_UINT	ercd;

	check_point(14);
	check_state_i(true, false, false, true, true);

	ercd = iget_tid(&tskid);
	check_ercd(ercd, E_OK);

	check_assert(tskid == TSK_NONE);

	ercd = iras_tex(TASK1, 0x0004);
	check_ercd(ercd, E_OK);

	alm3_flag = true;

	return;

	check_point(0);
}

void
cpuexc_handler(void *p_excinf)
{
	ER_UINT	ercd;

	check_point(18);
	check_state_i(true, false, true, true, false);

	check_assert(xsns_xpn(p_excinf) == false);

	ercd = iras_tex(TASK3, 0x0010);
	check_ercd(ercd, E_OBJ);

	ercd = iras_tex(TASK4, 0x0010);
	check_ercd(ercd, E_OBJ);

	ercd = iras_tex(TASK2, 0x0010);
	check_ercd(ercd, E_OK);

	ercd = iras_tex(TASK1, 0x0010);
	check_ercd(ercd, E_OK);

	return;

	check_point(0);
}

void
task1(intptr_t exinf)
{
	ER_UINT	ercd;
	T_RTEX	rtex;

	test_start(__FILE__);

	check_point(1);
	check_state(false, false, TIPM_ENAALL, false, false, true);

	ercd = ref_tex(TSK_SELF, &rtex);
	check_ercd(ercd, E_OK);

	check_assert((rtex.texstat & TTEX_DIS) != 0U);

	check_assert(rtex.pndptn == 0U);

	check_point(2);
	ercd = sta_alm(ALM1, 1U);
	check_ercd(ercd, E_OK);

	while (!(alm1_flag));

	check_point(4);
	ercd = ena_tex();
	check_ercd(ercd, E_OK);

	check_point(7);
	check_state(false, false, TIPM_ENAALL, false, false, false);

	ercd = ref_tex(TSK_SELF, &rtex);
	check_ercd(ercd, E_OK);

	check_assert((rtex.texstat & TTEX_ENA) != 0U);

	check_assert(rtex.pndptn == 0U);

	check_point(8);
	ercd = sta_alm(ALM2, 1U);
	check_ercd(ercd, E_OK);

	while (!(alm2_flag));

	check_point(11);
	ercd = sus_tsk(TASK2);
	check_ercd(ercd, E_OK);

	ercd = sus_tsk(TASK3);
	check_ercd(ercd, E_OK);

	check_point(12);
	ercd = sta_alm(ALM3, 10U);
	check_ercd(ercd, E_OK);

	check_point(13);
	ercd = dly_tsk(50U);
	check_ercd(ercd, E_OK);

	check_point(16);
	ercd = rsm_tsk(TASK2);
	check_ercd(ercd, E_OK);

	ercd = rsm_tsk(TASK3);
	check_ercd(ercd, E_OK);

	ercd = dis_dsp();
	check_ercd(ercd, E_OK);

	check_point(17);
	RAISE_CPU_EXCEPTION;

	check_point(0);
}

static uint_t	tex_task1_count = 0;

void
tex_task1(TEXPTN texptn, intptr_t exinf)
{
	ER_UINT	ercd;

	switch (++tex_task1_count) {
	case 1:
		check_point(5);
		check_assert(texptn == 0x0001);

		check_state(false, false, TIPM_ENAALL, false, false, true);

		check_point(6);
		ercd = dis_dsp();
		check_ercd(ercd, E_OK);

		ercd = chg_ipm(TMAX_INTPRI);
		check_ercd(ercd, E_OK);

		ercd = ena_tex();
		check_ercd(ercd, E_OK);

		ercd = loc_cpu();
		check_ercd(ercd, E_OK);

		check_state(false, true, TMAX_INTPRI, true, true, false);

		return;

		check_point(0);

	case 2:
		check_point(10);
		check_assert(texptn == 0x0002);

		check_state(false, false, TIPM_ENAALL, false, false, true);

		return;

		check_point(0);

	case 3:
		check_point(15);
		check_assert(texptn == 0x0004);

		check_state(false, false, TIPM_ENAALL, false, false, true);

		return;

		check_point(0);

	case 4:
		check_point(19);
		check_assert(texptn == 0x0010);

		check_state(false, false, TIPM_ENAALL, true, true, true);

		check_point(20);
		ercd = ext_tsk();
		check_ercd(ercd, E_OK);

		check_point(0);

	default:
		check_point(0);
	}
	check_point(0);
}

void
task2(intptr_t exinf)
{
	ER_UINT	ercd;

	check_point(21);
	check_state(false, false, TIPM_ENAALL, false, false, true);

	check_point(22);
	ercd = ena_tex();
	check_ercd(ercd, E_OK);

	check_point(24);
	ercd = sus_tsk(TASK3);
	check_ercd(ercd, E_OK);

	check_finish(25);
	check_point(0);
}

void
tex_task2(TEXPTN texptn, intptr_t exinf)
{

	check_point(23);
	check_assert(texptn == 0x0011);

	check_state(false, false, TIPM_ENAALL, false, false, true);

	return;

	check_point(0);
}
