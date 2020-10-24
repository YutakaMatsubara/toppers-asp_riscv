/*
 *  TOPPERS/ASP Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      Advanced Standard Profile Kernel
 * 
 *  Copyright (C) 2005,2006 by Embedded and Real-Time Systems Laboratory
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
 *  @(#) $Id: prc_timer.c 264 2019-09-20 18:51:36Z roi $
 */

/*
 *		タイマドライバ（RISC-V用）
 */

#include "kernel_impl.h"
#include "time_event.h"
#include <sil.h>
#include "target_timer.h"


static int32_t  molecule;

/*
 *  最初の割込みのタイマー値は不定のため
 *  割込み発生時のタイマー値をベースにマッチ時間を設定する．
 */
static void
pre_timer_handler(void)
{
	CLOCK mtimecmp = target_current_timer_value() + TO_CLOCK(TIC_NUME, TIC_DENO);

	target_set_target_timer_value(mtimecmp);
	x_machine_inh(IRQ_M_TIMER, (FP)prc_timer_handler);
}

/*
 *  タイマの起動処理
 */
void
prc_timer_initialize(intptr_t exinf)
{
	CLOCK	mtimecmp;

	/*
	 *  タイマ周期を設定し，タイマの動作を開始する．
	 */
	mtimecmp = target_current_timer_value() + TO_CLOCK(TIC_NUME, TIC_DENO);
	target_set_target_timer_value(mtimecmp);
	molecule = REMAINDER(TIC_NUME, TIC_DENO);

	/*
	 *  タイマ割込み要求をクリアする．
	 */
	x_machine_inh(IRQ_M_TIMER, (FP)pre_timer_handler);
}

/*
 *  タイマの停止処理
 */
void
prc_timer_terminate(intptr_t exinf)
{
	/*
	 *  タイマの動作を停止する．
	 */
	clear_csr(mie, MIP_MTIP);
}

/*
 *  タイマ割込みハンドラ
 */
void
prc_timer_handler(void)
{
	uint8_t  threshold = (uint8_t)current_ithreshold();
	CLOCK	mtimecmp;
	int32_t	difference;

	kernel_mie &= ~MIP_MTIP;
	mtimecmp = target_get_target_timer_value();
	do{
		mtimecmp += TO_CLOCK(TIC_NUME, TIC_DENO);
		if(molecule >= DENOMINATOR(TIC_NUME, TIC_DENO)){
			mtimecmp++;
			molecule -= DENOMINATOR(TIC_NUME, TIC_DENO);
		}
		molecule += REMAINDER(TIC_NUME, TIC_DENO);
		difference = mtimecmp - target_current_timer_value();
	}while(difference <= 0);
	target_set_target_timer_value(mtimecmp);
	set_ithreshold((uint32_t)INT_IPM(INTPRI_TIMER));
	set_csr(mie, kernel_mie);
	signal_time();					/* タイムティックの供給 */
	clear_csr(mie, KERNEL_MIE);
	set_ithreshold((uint32_t)threshold);
	kernel_mie |= MIP_MTIP;
}
