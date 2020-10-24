/*
 *  TOPPERS/ASP Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      Advanced Standard Profile Kernel
 * 
 *  Copyright (C) 2008-2011 by Embedded and Real-Time Systems Laboratory
 *              Graduate School of Information Science, Nagoya Univ., JAPAN
 *  Copyright (C) 2015      by 3rd Designing Center
 *              Imageing System Development Division RICOH COMPANY, LTD.
 *  Copyright (C) 2017-2018 by TOPPERS PROJECT Educational Working Group.
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
 *  @(#) $Id: target_inithook.c 699 2018-12-25 21:05:01Z roi $
 */

#include <sil.h>
#include "sifive-fe310.h"

#define sil_orw_mem(a, b)		sil_wrw_mem((a), sil_rew_mem(a) | (b))
#define sil_andw_mem(a, b)		sil_wrw_mem((a), sil_rew_mem(a) & ~(b))

#define DIV		4			/* default DIV value */
#define TRIM    16			/* default TRIM value */
#define F_R     1			/* DIVR to divide-by-2 to get 8MHz frequency (legal values of f_R are 6-12 MHz) */
#define F_F     31			/* DIVF to get 512Mhz frequncy There is an implied multiply-by-2, 16Mhz. So need to write 32-1 */
							/* (legal values of f_F are 384-768 MHz) */
#define F_Q     1			/* DIVQ to divide-by-2 to get 256 MHz frequency (legal values of f_Q are 50-400Mhz) */

/*
 *  ������ץ�����HIFIVE1�ѡ�
 */

#ifndef TOPPERS_RAM_EXEC
/*
 *  ���٥�Υ������åȰ�¸�ν����
 *
 *  �������ȥ��åץ⥸�塼�����ǡ�����ν���������˸ƤӽФ���롥
 */
void hardware_init_hook(void)
{
#ifdef DEFAULT_CLOCK
	/*
	 *  Turn off the LFROSC
	 */
	sil_andw_mem((uint32_t *)(TADR_AON_BASE+TOFF_AON_LFROSC), LFROSC_OSC_EN);

	/*
	 *  Setup the HFROSC using default running value.
	 */
	sil_wrw_mem((uint32_t *)(TADR_PRCI_BASE+PRCI_HFROSCCFG), ((DIV << 0) | (TRIM << 16) | HFROSCCFG_OSC_EN));
	while((sil_rew_mem((uint32_t *)(TADR_PRCI_BASE+PRCI_HFROSCCFG)) & HFROSCCFG_OSC_RDY) == 0);
	sil_andw_mem((uint32_t *)(TADR_PRCI_BASE+PRCI_PLLCFG), PLLCFG_PLL_SEL);

	/* In case we are executing from QSPI,
	 * (which is quite likely) we need to
	 * set the QSPI clock divider appropriately
	 * before boosting the clock frequency. */
	/*
	 *  Div = f_sck/2
	 */
	sil_wrw_mem((uint32_t *)(TADR_SPI0_BASE+TOFF_SPI_SCKDIV), 8);

	/*
	 *  Set our Final output divide to divide-by-1.
	 */
	sil_wrw_mem((uint32_t *)(TADR_PRCI_BASE+PRCI_PLLDIV), (PLL_FINAL_DIV_BY_1(1) | PLL_FINAL_DIV(0)));

	/*
	 *  Setup PLL with 16MHz source clock.
	 */
	sil_wrw_mem((uint32_t *)(TADR_PRCI_BASE+PRCI_PLLCFG), (PLLCFG_PLL_BYPASS | (F_R << 0) | (F_F << 4) | (F_Q << 10)));

	/*
	 *  Not Bypass the PLL
	 */
	sil_andw_mem((uint32_t *)(TADR_PRCI_BASE+PRCI_PLLCFG), PLLCFG_PLL_BYPASS);

	/*
	 *  Wait for PLL Lock 100 us
	 */
	sil_dly_nse(100*1000);

	/*
	 *  Check PLL Lock
	 */
	while((sil_rew_mem((uint32_t *)(TADR_PRCI_BASE+PRCI_PLLCFG)) & PLLCFG_PLL_LOCK) == 0) ;

	/*
	 *  Select PLL clock source
	 */
	sil_orw_mem((uint32_t *)(TADR_PRCI_BASE+PRCI_PLLCFG), PLLCFG_SEL_PLL);
#else
	/*
	 *  Setup the HFROSC using default running value.
	 */
	sil_wrw_mem((uint32_t *)(TADR_PRCI_BASE+PRCI_HFROSCCFG), ((DIV << 0) | (TRIM << 16) | HFROSCCFG_OSC_EN));

	/*
	 *  PLL running original clock(16MHz).
	 */
	sil_wrw_mem((uint32_t *)(TADR_PRCI_BASE+PRCI_PLLCFG), (PLLCFG_PLL_REFSEL | PLLCFG_PLL_BYPASS));
	sil_orw_mem((uint32_t *)(TADR_PRCI_BASE+PRCI_PLLCFG), PLLCFG_SEL_PLL);

	/*
	 * Turn off HFROSC (power save mode)
	 */
	sil_andw_mem((uint32_t *)(TADR_PRCI_BASE+PRCI_HFROSCCFG), HFROSCCFG_OSC_EN);
#endif
}
#endif

