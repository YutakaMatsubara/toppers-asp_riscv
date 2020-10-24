/*
 *  TOPPERS/ASP Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      Advanced Standard Profile Kernel
 * 
 *  Copyright (C) 2000-2003 by Embedded and Real-Time Systems Laboratory
 *                              Toyohashi Univ. of Technology, JAPAN
 *  Copyright (C) 2005-2014 by Embedded and Real-Time Systems Laboratory
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
 *  $Id: messagebuf.h 2589 2014-01-02 05:10:53Z ertl-hiro $
 */

/*
 *		��å������Хåե���ǽ
 */

#ifndef TOPPERS_MESSAGEBUF_H
#define TOPPERS_MESSAGEBUF_H

#include "wait.h"

/*
 *  ��å������Хåե�������֥�å�
 *
 *  ���ι�¤�Τϡ�Ʊ�����̿����֥������Ȥν�����֥�å��ζ�����ʬ
 *  ��WOBJINIB�ˤ��ĥ�ʥ��֥������Ȼظ�����ηѾ��������ˤ�����Τǡ�
 *  �ǽ�Υե�����ɤ����̤ˤʤäƤ��롥
 */
typedef struct messagebuf_initialization_block {
	ATR			mbfatr;			/* ��å������Хåե�°�� */
	uint_t		maxmsz;			/* ��å������κ���Ĺ */
	SIZE		mbfsz;			/* ��å������Хåե������ΰ�Υ����� */
	void		*mbfmb;			/* ��å������Хåե������ΰ����Ƭ���� */
} MBFINIB;

/*
 *  ��å������Хåե������֥�å�
 *
 *  ���ι�¤�Τϡ�Ʊ�����̿����֥������Ȥδ����֥�å��ζ�����ʬ��WOBJCB��
 *  ���ĥ�ʥ��֥������Ȼظ�����ηѾ��������ˤ�����Τǡ��ǽ��2�Ĥ�
 *  �ե�����ɤ����̤ˤʤäƤ��롥
 */
typedef struct messagebuf_control_block {
	QUEUE		swait_queue;	/* ��å������Хåե������Ԥ����塼 */
	const MBFINIB *p_mbfinib;	/* ������֥�å��ؤΥݥ��� */
	QUEUE		rwait_queue;	/* ��å������Хåե������Ԥ����塼 */
	SIZE		fmbfsz;			/* �����ΰ�Υ����� */
	SIZE		head;			/* �ǽ�Υ�å������γ�Ǽ��� */
	SIZE		tail;			/* �Ǹ�Υ�å������γ�Ǽ���μ� */
	uint_t		smbfcnt;		/* �����ΰ�˳�Ǽ����Ƥ����å������ο� */
} MBFCB;

/*
 *  ��å������Хåե��Ԥ�����֥�å������
 *
 *  ���ι�¤�Τϡ�Ʊ�����̿����֥������Ȥ��Ԥ�����֥�å��ζ�����ʬ
 *  ��WINFO_WOBJ�ˤ��ĥ�ʥ��֥������Ȼظ�����ηѾ��������ˤ�����Τǡ�
 *  �ǽ��2�ĤΥե�����ɤ����̤ˤʤäƤ��롥
 *  ��å������Хåե��ؤ������Ԥ��ȥ�å������Хåե�����μ����Ԥ��ǡ�
 *  Ʊ���Ԥ�����֥�å���Ȥ���
 */
typedef struct messagebuf_waiting_information {
	WINFO		winfo;			/* ɸ����Ԥ�����֥�å� */
	MBFCB		*p_mbfcb;		/* �ԤäƤ����å������Хåե��δ����֥�å� */
	void		*msg;			/* ��������å����� */
	uint_t		msgsz;			/* ��������å����������� */
} WINFO_MBF;

/*
 *  ��å������Хåե�ID�κ����͡�kernel_cfg.c��
 */
extern const ID	tmax_mbfid;

/*
 *  ��å������Хåե�������֥�å��Υ��ꥢ��kernel_cfg.c��
 */
extern const MBFINIB	mbfinib_table[];

/*
 *  ��å������Хåե������֥�å��Υ��ꥢ��kernel_cfg.c��
 */
extern MBFCB	mbfcb_table[];

/*
 *  ��å������Хåե������֥�å������å������Хåե�ID����Ф���
 *  ��Υޥ���
 */
#define	MBFID(p_mbfcb)	((ID)(((p_mbfcb) - mbfcb_table) + TMIN_MBFID))

/*
 *  ��å������Хåե���ǽ�ν����
 */
extern void	initialize_messagebuf(void);

/*
 *  ��å������Хåե������ΰ�ؤΥ�å������γ�Ǽ
 */
extern bool_t	enqueue_message(MBFCB *p_mbfcb, const void *msg, uint_t msgsz);

/*
 *  ��å������Хåե������ΰ褫��Υ�å������μ�Ф�
 */
extern uint_t	dequeue_message(MBFCB *p_mbfcb, void *msg);

/*
 *  ��å������Хåե��ؤΥ�å���������
 */
extern bool_t	send_message(MBFCB *p_mbfcb, const void *msg,
											uint_t msgsz, bool_t *p_dspreq);

/*
 *  ��å������Хåե������Ԥ��������Υ����å�
 */
extern bool_t	messagebuf_signal(MBFCB *p_mbfcb);

/*
 *  ��å������Хåե�����Υ�å���������
 */
extern uint_t	receive_message(MBFCB *p_mbfcb, void *msg, bool_t *p_dspreq);

/*
 *  ��å������Хåե������Ԥ����������Ԥ����������
 */
extern bool_t	(*mbfhook_dequeue_wobj)(TCB *p_tcb);
extern bool_t	messagebuf_dequeue_wobj(TCB *p_tcb);

/*
 *  ��å������Хåե������Ԥ���������ͥ�����ѹ�������
 */
extern bool_t	(*mbfhook_change_priority)(WOBJCB *p_wobjcb);
extern bool_t	messagebuf_change_priority(WOBJCB *p_wobjcb);

#endif /* TOPPERS_MESSAGEBUF_H */
