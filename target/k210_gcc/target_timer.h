/*
 *  TOPPERS/ASP Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      Advanced Standard Profile Kernel
 * 
 *  Copyright (C) 2000-2003 by Embedded and Real-Time Systems Laboratory
 *                              Toyohashi Univ. of Technology, JAPAN
 *  Copyright (C) 2005-2008 by Embedded and Real-Time Systems Laboratory
 *              Graduate School of Information Science, Nagoya Univ., JAPAN
 *  Copyright (C) 2017-2019 by TOPPERS PROJECT Educational Working Group.
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
 *  @(#) $Id: target_timer.h 889 2019-09-21 05:58:55Z roi $
 */

/*
 *		タイマドライバ（K210用）
 */

#ifndef TOPPERS_TARGET_TIMER_H
#define TOPPERS_TARGET_TIMER_H

/*
 *  ターゲット依存定義
 */
#include "target_syssvc.h"

/*
 *  タイマ割込みハンドラ登録のための定数
 */
#define INTPRI_TIMER	TIRQ_LEVEL4		/* 割込み優先度 */

/*
 *  CLINT周波数定義
 */
#define CLINT_FREQ      (SYS_CLOCK / 50)

/*
 *  プロセッサ依存定義
 */
#include "riscv_gcc/prc_timer.h"

/*
 *  累積値の読み出し
 */
Inline CLOCK
target_current_timer_value(void)
{
	return *((volatile CLOCK *)(TADR_CLIC_BASE+TOFF_CLINT_MTIME));
}

/*
 *  ターゲット値の読み出し
 */
Inline CLOCK
target_get_target_timer_value(void)
{
    uint32_t core_id = read_csr(mhartid);
	return *((volatile CLOCK *)(TADR_CLIC_BASE+TOFF_CLINT_MTIMECMP + core_id * sizeof(CLOCK)));
}

/*
 *  ターゲット値の書き込み
 */
Inline void
target_set_target_timer_value(CLOCK mtimecmp)
{
    uint32_t core_id = read_csr(mhartid);
	*((volatile CLOCK *)(TADR_CLIC_BASE+TOFF_CLINT_MTIMECMP + core_id * sizeof(CLOCK))) = mtimecmp;
}

/*
 *  タイマの現在値の読出し
 */
Inline CLOCK
target_timer_get_current(void)
{
	CLOCK	clk;

	clk = target_current_timer_value() - (target_get_target_timer_value() - TO_CLOCK(TIC_NUME, TIC_DENO));
	return(clk);
}

#define target_timer_probe_int		prc_timer_probe_int

#endif /* TOPPERS_TARGET_TIMER_H */
