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
 *  上記著作権者は，以下の(1)〜(4)の条件を満たす場合に限り，本ソフトウェ
 *  ア（本ソフトウェアを改変したものを含む．以下同じ）を使用・複製・改
 *  変・再配布（以下，利用と呼ぶ）することを無償で許諾する．
 *  (1) 本ソフトウェアをソースコードの形で利用する場合には，上記の著作
 *      権表示，この利用条件および下記の無保証規定が，そのままの形でソー
 *      スコード中に含まれていること．
 *  (2) 本ソフトウェアを，ライブラリ形式など，他のソフトウェア開発に使
 *      用できる形で再配布する場合には，再配布に伴うドキュメント（利用
 *      者マニュアルなど）に，上記の著作権表示，この利用条件および下記
 *      の無保証規定を掲載すること．
 *  (3) 本ソフトウェアを，機器に組み込むなど，他のソフトウェア開発に使
 *      用できない形で再配布する場合には，次のいずれかの条件を満たすこ
 *      と．
 *    (a) 再配布に伴うドキュメント（利用者マニュアルなど）に，上記の著
 *        作権表示，この利用条件および下記の無保証規定を掲載すること．
 *    (b) 再配布の形態を，別に定める方法によって，TOPPERSプロジェクトに
 *        報告すること．
 *  (4) 本ソフトウェアの利用により直接的または間接的に生じるいかなる損
 *      害からも，上記著作権者およびTOPPERSプロジェクトを免責すること．
 *      また，本ソフトウェアのユーザまたはエンドユーザからのいかなる理
 *      由に基づく請求からも，上記著作権者およびTOPPERSプロジェクトを
 *      免責すること．
 * 
 *  本ソフトウェアは，無保証で提供されているものである．上記著作権者お
 *  よびTOPPERSプロジェクトは，本ソフトウェアに関して，特定の使用目的
 *  に対する適合性も含めて，いかなる保証も行わない．また，本ソフトウェ
 *  アの利用により直接的または間接的に生じたいかなる損害に関しても，そ
 *  の責任を負わない．
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
 *  初期化プログラム（HIFIVE1用）
 */

#ifndef TOPPERS_RAM_EXEC
/*
 *  低レベルのターゲット依存の初期化
 *
 *  スタートアップモジュールの中で，メモリの初期化の前に呼び出される．
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

