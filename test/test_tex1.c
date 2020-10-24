/*
 *  TOPPERS Software
 *      Toyohashi Open Platform for Embedded Real-Time Systems
 * 
 *  Copyright (C) 2006-2013 by Embedded and Real-Time Systems Laboratory
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
 *  $Id: test_tex1.c 2596 2014-01-02 12:21:31Z ertl-hiro $
 */

/* 
 *		�������㳰�����˴ؤ���ƥ���(1)
 *
 * �ڥƥ��Ȥ���Ū��
 *
 *  ���������饿�����㳰�����롼�����ư�������������Ū�˥ƥ��Ȥ��롥
 *
 * �ڥƥ��ȹ��ܡ�
 *
 *	(A) ras_tex�Υ��顼����
 *		(A-1) �оݥ��������ٻ߾��֡�NGKI1413��
 *		(A-2) �оݥ������Υ������㳰�����롼�����������Ƥ��ʤ���NGKI1414��
 *	(B) dis_tex�Υ��顼����
 *		(B-1) ���������Υ������㳰�����롼�����������Ƥ��ʤ���NGKI1421��
 *	(C) ena_tex�Υ��顼����
 *		(C-1) ���������Υ������㳰�����롼�����������Ƥ��ʤ���NGKI1426��
 *	(D) ref_tex�Υ��顼����
 *		(D-1) �оݥ��������ٻ߾��֡�NGKI1439��
 *		(D-2) �оݥ������Υ������㳰�����롼�����������Ƥ��ʤ���NGKI1440��
 *	(E) ras_tex�����������NGKI1415��
 *		(E-1) �оݥ������������������������㳰�������ġ����ĳ����ͥ��
 *			  �٥ޥ�����������֤ǡ������˼¹Գ���
 *		(E-2) �оݥ����������������Ǥʤ�
 *		(E-3) �оݥ����������������������������㳰�����ػ�
 *		(E-4) �оݥ����������������ǥ������㳰�������Ĥ����������ͥ��
 *			  �٥ޥ�����������Ǥʤ�
 *	(F) ena_tex�����������NGKI1427��
 *		(F-1) �������㳰�����׵᤬���ꡤ���ĳ����ͥ���٥ޥ����������
 *			  �֤ǡ������˼¹Գ���
 *		(F-2) �������㳰�����׵᤬�ʤ�
 *		(F-3) �������㳰�����׵᤬���뤬�������ͥ���٥ޥ������������
 *			  �ʤ�
 *	(G) chg_ipm���������
 *		(G-1) �������㳰�����׵᤬���ꡤ���ĥ������㳰�������Ĥǡ�����
 *			  �˼¹Գ���
 *		(G-2) �������㳰�����׵᤬�ʤ�
 *		(G-3) �������㳰�����׵᤬���뤬���������㳰�����ػ�
 *		(G-4) �������㳰�����׵᤬���뤬�������ͥ���٥ޥ������������
 *			  �ʤ�
 *	(H) �������ǥ����ѥå���ˤ�뵯ư
 *		(H-1) �ǥ����ѥå���Υ��������������㳰���Ĥǥ������㳰������
 *			  �ᤢ��
 *	(I) �������㳰�����롼���󤫤�Υ꥿����ˤ�뵯ư��Ϣ³��ư��
 *	(J) �������㳰�����롼���󤫤�������ˤ���������
 *		(J-1) ����������äƤ����
 *		(J-2) �������㳰�����롼����Ϣ³��ư������
 *	(K) �������㳰�����롼�����¿�ŵ�ư
 *	(L) �������㳰�����롼���󤫤�������Υ������ڴ���
 *
 * �ڻ��ѥ꥽������
 *
 *	TASK1: �ᥤ��Υ������������������Ф��ƥ������㳰�������׵᤹��
 *	TASK2: ¾���������Ф��ƥ������㳰�������׵᤹���оݥ�����
 *	TASK3: �������㳰�����롼�����������Ƥ��ʤ�������
 *	TASK4: �ٻ߾��֤Υ�����
 *
 * �ڥƥ��ȥ������󥹡�
 *
 *	== TASK1��ͥ���١�10��==
 *	1:	state(false, false, TIPM_ENAALL, false, false, true)
 *		ref_tex(TSK_SELF, &rtex)
 *		assert((rtex.texstat & TTEX_DIS) != 0U)
 *		assert(rtex.pndptn == 0U)
 *		ras_tex(TASK3, 0x0001) -> E_OBJ		... (A-2)
 *		ras_tex(TASK4, 0x0001) -> E_OBJ		... (A-1)
 *		ref_tex(TASK3, &rtex) -> E_OBJ		... (D-2)
 *		ref_tex(TASK4, &rtex) -> E_OBJ		... (D-1)
 *	2:	ena_tex()							... (F-2)
 *		state(false, false, TIPM_ENAALL, false, false, false)
 *		ref_tex(TSK_SELF, &rtex)
 *		assert((rtex.texstat & TTEX_ENA) != 0U)
 *		assert(rtex.pndptn == 0U)
 *	3:	ras_tex(TSK_SELF, 0x0001)			... (E-1)
 *	== TASK1-TEX-1��1���ܡ�==
 *	4:	assert(texptn == 0x0001)
 *		state(false, false, TIPM_ENAALL, false, false, true)
 *	5:	dis_dsp() ... 4�Ĥξ��֤򤽤줾���Ѳ�������
 *		chg_ipm(TMAX_INTPRI)
 *		ena_tex()
 *		loc_cpu()
 *		state(false, true, TMAX_INTPRI, true, true, false)
 *		RETURN
 *	== TASK1��³����==
 *	6:	state(false, false, TIPM_ENAALL, false, false, false)	... (J-1)
 *	7:	dis_dsp() ... �ǥ����ѥå��ػߡ��������㳰�����ػ�
 *		dis_tex()
 *		state(false, false, TIPM_ENAALL, true, true, true)
 *	8:	ras_tex(TASK1, 0x0002)				... (E-3)
 *		ref_tex(TSK_SELF, &rtex)
 *		assert((rtex.texstat & TTEX_DIS) != 0)
 *		assert(rtex.pndptn == 0x0002)
 *	9:	ena_tex()							... (F-1)
 *	== TASK1-TEX-2��2���ܡ�==
 *	10:	assert(texptn == 0x0002)
 *		state(false, false, TIPM_ENAALL, true, true, true)
 *	11:	ras_tex(TASK1, 0x0001)				... (E-3)
 *		ras_tex(TASK1, 0x0002)				... (E-3)
 *	12:	ena_dsp() ... 3�Ĥξ��֤򤽤줾���Ѳ�������
 *		chg_ipm(TMAX_INTPRI)
 *		loc_cpu()
 *		state(false, true, TMAX_INTPRI, false, true, true)
 *		RETURN								... (I)
 *	== TASK1-TEX-3��3���ܡ�==
 *	13:	assert(texptn == 0x0003)
 *		state(false, false, TIPM_ENAALL, true, true, true)	... (J-2)
 *	14:	ena_dsp() ... �ǥ����ѥå����ġ��������㳰����
 *		chg_ipm(TMAX_INTPRI)
 *		ena_tex()
 *		state(false, false, TMAX_INTPRI, false, true, false)
 *		chg_ipm(TIPM_ENAALL)				... (G-2)
 *		chg_ipm(TMAX_INTPRI)
 *	15: ras_tex(TSK_SELF, 0x0004)			... (E-4)
 *		chg_ipm(TMAX_INTPRI)				... (G-4)
 *		dis_tex()
 *		chg_ipm(TIPM_ENAALL)				... (G-3)
 *		chg_ipm(TMAX_INTPRI)
 *		ena_tex()							... (F-3)
 *	16:	chg_ipm(TIPM_ENAALL)				... (G-1)(K)
 *	== TASK1-TEX-4��4���ܡ�==
 *	17:	assert(texptn == 0x0004)
 *		state(false, false, TIPM_ENAALL, false, false, true)
 *	18:	dis_dsp() ... 3�Ĥξ��֤򤽤줾���Ѳ�������
 *		chg_ipm(TMAX_INTPRI)
 *		loc_cpu()
 *		state(false, true, TMAX_INTPRI, true, true, true)
 *		RETURN
 *	== TASK1-TEX-3��3����³����==
 *	19:	state(false, false, TIPM_ENAALL, false, false, false)
 *		RETURN
 *	== TASK1��³����==
 *	20:	state(false, false, TIPM_ENAALL, true, true, false)	... (J-1)
 *	21: ena_dsp()
 *		rot_rdq(TPRI_SELF)
 *	== TASK2��ͥ���١�10��	==
 *	22:	state(false, false, TIPM_ENAALL, false, false, true)
 *	23:	ena_tex()
 *		state(false, false, TIPM_ENAALL, false, false, false)
 *		rot_rdq(TPRI_SELF)
 *	== TASK3��ͥ���١�10��	==
 *	24:	state(false, false, TIPM_ENAALL, false, false, true)
 *	25:	ena_tex() -> E_OBJ					... (C-1)
 *		state(false, false, TIPM_ENAALL, false, false, true)
 *	26:	dis_tex() -> E_OBJ					... (B-1)
 *		state(false, false, TIPM_ENAALL, false, false, true)
 *		ext_tsk()
 *	== TASK1��³����==
 *	27: ras_tex(TASK2, 0x0001)				... (E-2)
 *		ref_tex(TASK2, &rtex)
 *	28:	rot_rdq(TPRI_SELF)					... (H-1)
 *	== TASK2-TEX-1��1���ܡ�==
 *	29:	assert(texptn == 0x0001)
 *		state(false, false, TIPM_ENAALL, false, false, true)
 *		RETURN
 *	== TASK2��³����==
 *	30: ras_tex(TSK_SELF, 0x0002)
 *	== TASK2-TEX-2��2���ܡ�==
 *	31:	assert(texptn == 0x0002)
 *		state(false, false, TIPM_ENAALL, false, false, true)
 *	32:	dis_dsp()
 *		rot_rdq(TPRI_SELF)
 *	33:	RETURN
 *	== TASK1��³����==
 *	34:	RETURN
 *	== TASK2��³����==
 *	35:	END
 */

#include <kernel.h>
#include <test_lib.h>
#include <t_syslog.h>
#include "kernel_cfg.h"
#include "test_tex1.h"

/*
 *  task4��tex_task4����������ʤ�
 */

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

	ercd = ras_tex(TASK3, 0x0001);
	check_ercd(ercd, E_OBJ);

	ercd = ras_tex(TASK4, 0x0001);
	check_ercd(ercd, E_OBJ);

	ercd = ref_tex(TASK3, &rtex);
	check_ercd(ercd, E_OBJ);

	ercd = ref_tex(TASK4, &rtex);
	check_ercd(ercd, E_OBJ);

	check_point(2);
	ercd = ena_tex();
	check_ercd(ercd, E_OK);

	check_state(false, false, TIPM_ENAALL, false, false, false);

	ercd = ref_tex(TSK_SELF, &rtex);
	check_ercd(ercd, E_OK);

	check_assert((rtex.texstat & TTEX_ENA) != 0U);

	check_assert(rtex.pndptn == 0U);

	check_point(3);
	ercd = ras_tex(TSK_SELF, 0x0001);
	check_ercd(ercd, E_OK);

	check_point(6);
	check_state(false, false, TIPM_ENAALL, false, false, false);

	check_point(7);
	ercd = dis_dsp();
	check_ercd(ercd, E_OK);

	ercd = dis_tex();
	check_ercd(ercd, E_OK);

	check_state(false, false, TIPM_ENAALL, true, true, true);

	check_point(8);
	ercd = ras_tex(TASK1, 0x0002);
	check_ercd(ercd, E_OK);

	ercd = ref_tex(TSK_SELF, &rtex);
	check_ercd(ercd, E_OK);

	check_assert((rtex.texstat & TTEX_DIS) != 0);

	check_assert(rtex.pndptn == 0x0002);

	check_point(9);
	ercd = ena_tex();
	check_ercd(ercd, E_OK);

	check_point(20);
	check_state(false, false, TIPM_ENAALL, true, true, false);

	check_point(21);
	ercd = ena_dsp();
	check_ercd(ercd, E_OK);

	ercd = rot_rdq(TPRI_SELF);
	check_ercd(ercd, E_OK);

	check_point(27);
	ercd = ras_tex(TASK2, 0x0001);
	check_ercd(ercd, E_OK);

	ercd = ref_tex(TASK2, &rtex);
	check_ercd(ercd, E_OK);

	check_point(28);
	ercd = rot_rdq(TPRI_SELF);
	check_ercd(ercd, E_OK);

	check_point(34);
	return;

	check_point(0);
}

static uint_t	tex_task1_count = 0;

void
tex_task1(TEXPTN texptn, intptr_t exinf)
{
	ER_UINT	ercd;

	switch (++tex_task1_count) {
	case 1:
		check_point(4);
		check_assert(texptn == 0x0001);

		check_state(false, false, TIPM_ENAALL, false, false, true);

		check_point(5);
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

		check_state(false, false, TIPM_ENAALL, true, true, true);

		check_point(11);
		ercd = ras_tex(TASK1, 0x0001);
		check_ercd(ercd, E_OK);

		ercd = ras_tex(TASK1, 0x0002);
		check_ercd(ercd, E_OK);

		check_point(12);
		ercd = ena_dsp();
		check_ercd(ercd, E_OK);

		ercd = chg_ipm(TMAX_INTPRI);
		check_ercd(ercd, E_OK);

		ercd = loc_cpu();
		check_ercd(ercd, E_OK);

		check_state(false, true, TMAX_INTPRI, false, true, true);

		return;

		check_point(0);

	case 3:
		check_point(13);
		check_assert(texptn == 0x0003);

		check_state(false, false, TIPM_ENAALL, true, true, true);

		check_point(14);
		ercd = ena_dsp();
		check_ercd(ercd, E_OK);

		ercd = chg_ipm(TMAX_INTPRI);
		check_ercd(ercd, E_OK);

		ercd = ena_tex();
		check_ercd(ercd, E_OK);

		check_state(false, false, TMAX_INTPRI, false, true, false);

		ercd = chg_ipm(TIPM_ENAALL);
		check_ercd(ercd, E_OK);

		ercd = chg_ipm(TMAX_INTPRI);
		check_ercd(ercd, E_OK);

		check_point(15);
		ercd = ras_tex(TSK_SELF, 0x0004);
		check_ercd(ercd, E_OK);

		ercd = chg_ipm(TMAX_INTPRI);
		check_ercd(ercd, E_OK);

		ercd = dis_tex();
		check_ercd(ercd, E_OK);

		ercd = chg_ipm(TIPM_ENAALL);
		check_ercd(ercd, E_OK);

		ercd = chg_ipm(TMAX_INTPRI);
		check_ercd(ercd, E_OK);

		ercd = ena_tex();
		check_ercd(ercd, E_OK);

		check_point(16);
		ercd = chg_ipm(TIPM_ENAALL);
		check_ercd(ercd, E_OK);

		check_point(19);
		check_state(false, false, TIPM_ENAALL, false, false, false);

		return;

		check_point(0);

	case 4:
		check_point(17);
		check_assert(texptn == 0x0004);

		check_state(false, false, TIPM_ENAALL, false, false, true);

		check_point(18);
		ercd = dis_dsp();
		check_ercd(ercd, E_OK);

		ercd = chg_ipm(TMAX_INTPRI);
		check_ercd(ercd, E_OK);

		ercd = loc_cpu();
		check_ercd(ercd, E_OK);

		check_state(false, true, TMAX_INTPRI, true, true, true);

		return;

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

	check_point(22);
	check_state(false, false, TIPM_ENAALL, false, false, true);

	check_point(23);
	ercd = ena_tex();
	check_ercd(ercd, E_OK);

	check_state(false, false, TIPM_ENAALL, false, false, false);

	ercd = rot_rdq(TPRI_SELF);
	check_ercd(ercd, E_OK);

	check_point(30);
	ercd = ras_tex(TSK_SELF, 0x0002);
	check_ercd(ercd, E_OK);

	check_finish(35);
	check_point(0);
}

static uint_t	tex_task2_count = 0;

void
tex_task2(TEXPTN texptn, intptr_t exinf)
{
	ER_UINT	ercd;

	switch (++tex_task2_count) {
	case 1:
		check_point(29);
		check_assert(texptn == 0x0001);

		check_state(false, false, TIPM_ENAALL, false, false, true);

		return;

		check_point(0);

	case 2:
		check_point(31);
		check_assert(texptn == 0x0002);

		check_state(false, false, TIPM_ENAALL, false, false, true);

		check_point(32);
		ercd = dis_dsp();
		check_ercd(ercd, E_OK);

		ercd = rot_rdq(TPRI_SELF);
		check_ercd(ercd, E_OK);

		check_point(33);
		return;

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

	check_point(24);
	check_state(false, false, TIPM_ENAALL, false, false, true);

	check_point(25);
	ercd = ena_tex();
	check_ercd(ercd, E_OBJ);

	check_state(false, false, TIPM_ENAALL, false, false, true);

	check_point(26);
	ercd = dis_tex();
	check_ercd(ercd, E_OBJ);

	check_state(false, false, TIPM_ENAALL, false, false, true);

	ercd = ext_tsk();
	check_ercd(ercd, E_OK);

	check_point(0);
}
