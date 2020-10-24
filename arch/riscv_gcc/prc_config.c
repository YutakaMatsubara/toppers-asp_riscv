/*
 *  TOPPERS/ASP Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      Advanced Standard Profile Kernel
 * 
 *  Copyright (C) 2000-2003 by Embedded and Real-Time Systems Laboratory
 *                              Toyohashi Univ. of Technology, JAPAN
 *  Copyright (C) 2005-2009 by Embedded and Real-Time Systems Laboratory
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
 *  @(#) $Id: prc_config.c 1430 2019-09-20 18:50:51Z roi $
 */

/*
 *		プロセッサ依存モジュール（RISC-V用）
 */

#include "kernel_impl.h"
#include "check.h"
#include "task.h"

/*
 *  CPUロックフラグ実現のための変数
 */
volatile bool_t			lock_flag;	/* CPUロックフラグの値を保持する変数 */
volatile uint16_t		inest_lvl;	/* 割込みネストを保存する変数 */
volatile unsigned long	kernel_mie;	/* デフォルトのMIE値を保存する変数 */
static unsigned long	saved_trap;	/* MACHINE TRAPデータの保存変数 */

/*
 *  MACHINE割込みハンドラ領域のテーブル
 */
volatile EXCVE m_interrupt_handlers[TMAX_MACHNE_INTNO];


#ifndef OMIT_DEFAULT_INT_HANDLER
/*
 *  未登録の割込みが発生した場合に呼び出される
 */
static void
default_int_handler(unsigned long mcause, void *p_excinf)
{
	unsigned long mstatus = *(((uintptr_t*)p_excinf) + P_EXCINF_OFFSET_MSTATUS);
	uintptr_t     pc      = *(((uintptr_t*)p_excinf) + P_EXCINF_OFFSET_PC);
	unsigned long excno   = mcause & MCAUSE_CAUSE;

	if((long)mcause < 0)
		excno += TMAX_MACHNE_INTNO / 2;
	syslog(LOG_EMERG, "\nUnregistered Interrupt occurs.");
	syslog(LOG_EMERG, "Excno = 0x%02X, PC = 0x%X, mstatus = 0x%X, p_excinf = 0x%X",
		   excno, pc, mstatus, p_excinf);

	target_exit();
}
#endif /* OMIT_DEFAULT_INT_HANDLER */

/*
 *  プロセッサ依存の初期化
 */
void
prc_initialize(void)
{
	extern void	software_init_hook(void);
	void (*volatile fp)(void) = software_init_hook;
	int  i;

	/*
	 *  software_init_hookへのポインタを，一旦volatile指定のあるfpに代
	 *  入してから使うのは，0との比較が最適化で削除されないようにするた
	 *  めである．
	 */
	if (fp != 0) {
		(*fp)();
	}

	/*
	 *  CPUロックフラグ実現のための変数の初期化
	 */
	lock_flag  = true;
	kernel_mie = KERNEL_MIE;
	clear_csr(mie, KERNEL_MIE);
	set_csr(mie, MIP_MSIP);
	inest_lvl  = 0;

	/*
	 *  例外ベクタテーブルの初期化
	 */
#ifndef OMIT_DEFAULT_INT_HANDLER
	for(i = 0 ; i < TMAX_MACHNE_INTNO ; i++){
		m_interrupt_handlers[i].exc_handler = (FP)default_int_handler;
	}
#endif
	saved_trap = read_csr(mtvec);
	write_csr(mtvec, &trap_entry);
	ena_intm();

	/*
	 *  FPU拡張の初期化
	 */
	if(read_csr(misa) & (1 << ('F' - 'A'))){
		set_csr(mstatus, MSTATUS_FS);	/* FPU設定、但し割込みはサポートしない */
		write_csr(fcsr, 0);				/* ラウンディングモード設定 */
	}

	(void)(i);
}

/*
 *  プロセッサ依存の終了処理
 */
void
prc_terminate(void)
{
	extern void	software_term_hook(void);
	void (*volatile fp)(void) = software_term_hook;

	/*
	 *  software_term_hookへのポインタを，一旦volatile指定のあるfpに代
	 *  入してから使うのは，0との比較が最適化で削除されないようにするた
	 *  めである．
	 */
	if (fp != 0) {
		(*fp)();
	}

	write_csr(mtvec, saved_trap);
}

/*
 *  C言語レベル MACHINE割込みハンドラ
 */
uint32_t
handle_trap(unsigned long mcause, void *p_excinf)
{
	uint32_t intno = mcause & MCAUSE_CAUSE;
	void     (*func)(unsigned long, void *);

	if(inest_lvl++ == 0)
		write_csr(mtvec, &trap_nest);
	if((long)mcause < 0)
		intno += TMAX_MACHNE_INTNO / 2;
	if(intno < TMAX_MACHNE_INTNO){
		func = (void(*)(unsigned long, void *))m_interrupt_handlers[intno].exc_handler;
		if(func != NULL)
			func(mcause, p_excinf);
	}
	else{
		syslog_1(LOG_EMERG, "Irrigal machine Exception mcause = %08X", (int)intno);
	}
	if(--inest_lvl == 0)
		write_csr(mtvec, &trap_entry);
	return inest_lvl;
}

/*
 *  CPU例外の発生状況のログ出力
 *
 *  CPU例外ハンドラの中から，CPU例外情報ポインタ（p_excinf）を引数とし
 *  て呼び出すことで，CPU例外の発生状況をシステムログに出力する．
 */
#ifdef SUPPORT_XLOG_SYS

void
xlog_sys(void *p_excinf)
{
	unsigned long *excsp = (unsigned long *) p_excinf;

	syslog_0(LOG_ERROR, "CPU Exception Information:");
	syslog_4(LOG_ERROR, "mstatus = %08x PC = %x mcause = %x STACK = %x",
				*((excsp + P_EXCINF_OFFSET_MSTATUS)), 
				*((excsp + P_EXCINF_OFFSET_PC)),
				*((excsp + P_EXCINF_OFFSET_MCAUSE)),
				((unsigned long)excsp + 19 * 4));
	syslog_1(LOG_ERROR, "p_excinf = %x", (unsigned long)excsp);
}

#endif /* SUPPORT_XLOG_SYS */
