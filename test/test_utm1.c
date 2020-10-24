/*
 *  TOPPERS Software
 *      Toyohashi Open Platform for Embedded Real-Time Systems
 * 
 *  Copyright (C) 2000-2003 by Embedded and Real-Time Systems Laboratory
 *                              Toyohashi Univ. of Technology, JAPAN
 *  Copyright (C) 2007-2010 by Embedded and Real-Time Systems Laboratory
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
 *  $Id: test_utm1.c 2305 2012-01-29 11:51:08Z ertl-hiro $
 */

/*
 *		get_utm�˴ؤ���ƥ���(1)
 *
 * �ڥƥ��Ȥ���Ū��
 *
 *  ��ǽɾ���ѥ����ƥ���郎�չԤ��뤳�Ȥ��ʤ����Ȥ�ƥ��Ȥ��롥
 *
 * �ڥƥ��Ȥ����ơ�
 *
 *  �ᥤ�󥿥����Ǥϡ���ǽɾ���ѥ����ƥ����򷫤��֤������������郎��
 *  �����ʤ�ʤ���������å����롥������¹Ԥ��ơ������ϥ�ɥ��1�ߥ���
 *  �����Ǽ¹Ԥ���������Ǥ���ǽɾ���ѥ����ƥ�����������ơ����郎��
 *  �����ʤ�ʤ���������å����롥
 *
 *  �ʤ�����ǽɾ���ѥ����ƥ���郎�����ͤ�Ķ����0���������Ϲ�θ���Ƥ�
 *  �ʤ���
 */

#include <kernel.h>
#include <test_lib.h>
#include <t_syslog.h>
#include "kernel_cfg.h"
#include "test_utm1.h"

#define	NO_LOOP		ULONG_C(100000)

SYSUTM	recent_sysutm;
char	*recent_sysutm_pos;
uint_t	cyclic_count;

void
cyclic_handler(intptr_t exinf)
{
	SYSUTM		sysutm, prev_sysutm;
	char		*prev_sysutm_pos;

	iloc_cpu();
	get_utm(&sysutm);
	prev_sysutm = recent_sysutm;
	prev_sysutm_pos = recent_sysutm_pos;
	recent_sysutm = sysutm;
	recent_sysutm_pos = "CYC";
	iunl_cpu();

	if (prev_sysutm > sysutm) {
		syslog(LOG_NOTICE,
				"system performance time goes back: %ld(%s) %ld(CYC)",
				((long_t) prev_sysutm), prev_sysutm_pos, ((ulong_t) sysutm));
	}
	cyclic_count += 1;
}

void
main_task(intptr_t exinf)
{
	SYSUTM		sysutm, prev_sysutm;
	char		*prev_sysutm_pos;
	ulong_t		i;

	cyclic_count = 0U;
	get_utm(&recent_sysutm);
	syslog(LOG_NOTICE, "system performance time test starts.");

	for (i = 0; i < NO_LOOP; i++) {
		loc_cpu();
		get_utm(&sysutm);
		prev_sysutm = recent_sysutm;
		prev_sysutm_pos = recent_sysutm_pos;
		recent_sysutm = sysutm;
		recent_sysutm_pos = "TSK";
		unl_cpu();

		if (prev_sysutm > sysutm) {
			syslog(LOG_NOTICE,
				"system performance time goes back: %ld(%s) %ld(TSK)",
				((long_t) prev_sysutm), prev_sysutm_pos, ((ulong_t) sysutm));
		}
	}

	syslog(LOG_NOTICE, "system performance time test finishes.");
	syslog(LOG_NOTICE, "number of cyclic handler execution: %d", cyclic_count);
	test_finish();
}
