/*
 *  TOPPERS/ASP Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      Advanced Standard Profile Kernel
 * 
 *  Copyright (C) 2000-2003 by Embedded and Real-Time Systems Laboratory
 *                              Toyohashi Univ. of Technology, JAPAN
 *  Copyright (C) 2005-2011 by Embedded and Real-Time Systems Laboratory
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
 *  @(#) $Id: target_config.c 2246 2019-09-22 21:21:20Z roi $
 */

/*
 *		ターゲット依存モジュール（HIFIVE1用）
 */

#include "kernel_impl.h"
#include <sil.h>

#include "target_syssvc.h"
#include "target_serial.h"

#define sil_orw_mem(a, b)		sil_wrw_mem((a), sil_rew_mem(a) | (b))
#define sil_andw_mem(a, b)		sil_wrw_mem((a), sil_rew_mem(a) & ~(b))

#define NUM_INT_LEVEL_TABLE ((TMAX_INTNO+31)/32)
#define mtime_low_value()   sil_rew_mem((uint32_t *)(TADR_CLIC_BASE+TOFF_CLINT_MTIME))

uint32_t		SystemFrequency;


static unsigned long __attribute__((noinline)) measure_cpu_freq(uint32_t n)
{
	unsigned long start_mtime, delta_mtime;
	unsigned long start_mcycle, delta_mcycle;
	unsigned long tmp = mtime_low_value();

	do{
		start_mtime = mtime_low_value();
	}while(start_mtime == tmp);

	start_mcycle = read_csr(mcycle);
	do{
		delta_mtime = mtime_low_value() - start_mtime;
	}while(delta_mtime < n);

	delta_mcycle = read_csr(mcycle) - start_mcycle;

	return (delta_mcycle / delta_mtime) * TIMER_FREQ
	     + ((delta_mcycle % delta_mtime) * TIMER_FREQ) / delta_mtime;
}

/*
 *  MACHINE割込みから割込みハンドラを呼び出す
 */
static void
machine_interrupt(unsigned long mcause, void *p_excinf)
{
	unsigned long hart_id = read_csr(mhartid);
	uint32_t int_num = sil_rew_mem((uint32_t *)(TADR_PLIC_BASE+TOFF_PLIC_CLAIM+(hart_id * NUM_PLIC_THRESHOLD)));
	uint8_t  threshold = (uint8_t)current_ithreshold();
	void (*volatile handler)(void);
	uint8_t  priority;

	if(int_num < TMAX_INTNO){
		if((handler = (void (*volatile)(void))vector_table[int_num]) != NULL){
			priority = current_ipriority(int_num);
			set_ithreshold((uint32_t)priority);
//			set_csr(mie, kernel_mie);
			sil_wrw_mem((uint32_t *)(TADR_PLIC_BASE+TOFF_PLIC_CLAIM+(hart_id * NUM_PLIC_THRESHOLD)), int_num);
			handler();
			clear_csr(mie, KERNEL_MIE);
			set_ithreshold((uint32_t)threshold);
		}
	}
	else{
		syslog(LOG_EMERG, "Illegal global interrupt NO = %d", int_num);
		sil_wrw_mem((uint32_t *)(TADR_PLIC_BASE+TOFF_PLIC_CLAIM+(hart_id * NUM_PLIC_THRESHOLD)), int_num);
	}
}

/*
 *  ターゲット依存の初期化
 */
void
target_initialize(void)
{
	extern void	hardware_init_hook(void);
	void (*volatile fp)(void) = hardware_init_hook;
	unsigned long hart_id = read_csr(mhartid);
	uint32_t i, off, len;

	/*
	 *  hardware_init_hookへのポインタを，一旦volatile指定のあるfpに代
	 *  入してから使うのは，0との比較が最適化で削除されないようにするた
	 *  めである．
	 */
	if (fp != 0) {
		(*fp)();
	}

	/*
	 *  CPUクロック測定
	 */
	measure_cpu_freq(1);
	SystemFrequency = measure_cpu_freq(10);

	/*
	 *  プロセッサ依存の初期化
	 */
	prc_initialize();

	/*
	 *  バナー出力用のシリアル初期化
	 */
	target_uart_init(SIO_PORTID);

	/*
	 *  割込み関連の初期化
	 *
	 *  割込みレベルテーブルをHIに設定する．
	 *  PLICに対して割込み禁止、レベルを0、スレシュホールドを0に設定する．
	 */
	off = TOFF_PLIC_ENABLE + (hart_id * NUM_PLIC_ENABLE);
	len = (TMAX_INTNO + 8) / 8;
	for(i = 0 ; i < len ; i += 4){
		sil_wrw_mem((uint32_t *)(TADR_PLIC_BASE + off + i), 0);
	}

	/*
	 *  割込み優先度を0に設定
	 */
	len = (TMAX_INTNO + 1) * sizeof(uint32_t);
	for(i = 0 ; i < len ; i++){
		sil_wrb_mem((uint8_t *)(TADR_PLIC_BASE+TOFF_PLIC_PRIORITY+i), 0);
	}

	/*
	 *  割込みスレシュホールドを0に設定
	 */
//	off = (TOFF_PLIC_THRESHOLD + (hart_id * NUM_PLIC_THRESHOLD));
//	sil_wrw_mem((uint32_t *)(TADR_PLIC_BASE+off), 0);

	/*
	 *  GPIO割込みマスク
	 */
	sil_wrw_mem((uint32_t *)(TADR_GPIO_BASE+TOFF_GPIO_RISE_IE), 0);
	sil_wrw_mem((uint32_t *)(TADR_GPIO_BASE+TOFF_GPIO_FALL_IE), 0);
	sil_wrw_mem((uint32_t *)(TADR_GPIO_BASE+TOFF_GPIO_HIGH_IE), 0);
	sil_wrw_mem((uint32_t *)(TADR_GPIO_BASE+TOFF_GPIO_LOW_IE), 0);

	/*
	 *  MACHINE割込み設定
	 */
	x_machine_inh(IRQ_MACHINE_EXTERNAL, (FP)machine_interrupt);
}

/*
 *  ターゲット依存の終了処理
 */
void
target_exit(void)
{
	unsigned long hart_id = read_csr(mhartid);
	uint32_t i, off, len;

	/*
	 *  プロセッサ依存の終了処理
	 */
	prc_terminate();

	/*
	 *  すべての割込みをマスクする．
	 */
	off = TOFF_PLIC_ENABLE + (hart_id * NUM_PLIC_ENABLE);
	len = (TMAX_INTNO + 8) / 8;
	for(i = 0 ; i < len ; i += 4){
		sil_wrw_mem((uint32_t *)(TADR_PLIC_BASE + off + i), 0);
	}

	/*
	 *  開発環境依存の終了処理
	 */
	while(1);
}

/*
 *  イレギュラーなPDIC割込み処理
 */
void
default_plic_handler(void)
{
	syslog(LOG_EMERG, "\nUnregistered plic Interrupt occurs.");

	target_exit();
}

/*
 *  システムログの低レベル出力のための文字出力
 */
void
target_fput_log(char c)
{
	if (c == '\n') {
		sio_pol_snd_chr('\r', SIO_PORTID);
	}
	sio_pol_snd_chr(c, SIO_PORTID);
}

/*
 *  割込み要求ラインの属性の設定
 *
 *  ASPカーネルでの利用を想定して，パラメータエラーはアサーションでチェッ
 *  クしている．cfg_intサービスコールを設ける場合には，エラーを返すよう
 *  にすべきであろう．
 */
void
x_config_int(INTNO intno, ATR intatr, PRI intpri)
{
	uint32_t	priority;

	assert(VALID_INTNO_CFGINT(intno));
	assert(TIRQ_NMI <= intpri && intpri <= TIRQ_LEVEL1);
	priority = intpri - TIRQ_NMI;

	/*
	 *  割込みのマスク
	 *
	 *  割込みを受け付けたまま，レベルトリガ／エッジトリガの設定や，割
	 *  込み優先度の設定を行うのは危険なため，割込み属性にかかわらず，
	 *  一旦マスクする．
	 */
	(void) x_disable_int(intno);

	/*
	 *  割込み優先度の設定
	 */
	set_ipriority(intno, priority);

	/*
	 *  割込みのマスク解除（必要な場合）
 	 */
	if ((intatr & TA_ENAINT) != 0U) {
		(void) x_enable_int(intno);
	}
}
