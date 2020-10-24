/*
 *  TOPPERS/ASP Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      Advanced Standard Profile Kernel
 * 
 *  Copyright (C) 2000-2003 by Embedded and Real-Time Systems Laboratory
 *                              Toyohashi Univ. of Technology, JAPAN
 *  Copyright (C) 2005-2010 by Embedded and Real-Time Systems Laboratory
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
 *  $Id: prc_support.S 2015 2019-09-25 17:48:49Z roi $
 */

/*
 *		プロセッサ依存モジュール アセンブリ言語部（RISC-V用）
 */

#define	TOPPERS_MACRO_ONLY
#include "encoding.h"
#define UINT_C(val)			(val)		/* uint_t型の定数を作るマクロ */
#define ULONG_C(val)		(val)		/* ulong_t型の定数を作るマクロ */
#define CAST(type, val)		(val)		/* 型キャストを行うマクロ */
#include "kernel_impl.h"
#include "offset.h"

#if defined(__riscv64)
#define LREG                ld
#define SREG                sd
#define LFREG               fld
#define SFREG               fsd
#define REGSIZE             8
#else
#define LREG                lw
#define SREG                sw
#define LFREG               flw
#define SFREG               fsw
#define REGSIZE             4
#endif

#if defined(USE_FPU) && !defined(__riscv_float_abi_soft)
#define SAVEREG1            27
#define SAVEREG2            42
#define SAVEREG3            26
#else
#define SAVEREG1            15
#define SAVEREG2            22
#define SAVEREG3            14
#endif

/*
 *  タスクディスパッチャ
 */
	.text
	.globl dispatch
dispatch:
	/*
	 *  このルーチンは，タスクコンテキスト・CPUロック状態・ディスパッチ
	 *  許可状態・（モデル上の）割込み優先度マスク全解除状態で呼び出さ
	 *  れる．
	 */
	addi sp, sp, -SAVEREG1*REGSIZE	/* レジスタ保存領域を確保 */
	SREG ra, 0*REGSIZE(sp)			/* returnアドレスを保存 */
	SREG gp, 1*REGSIZE(sp)			/* call先セーブのレジスタを保存 */
	SREG tp, 2*REGSIZE(sp)
	SREG s0, 3*REGSIZE(sp)
	SREG s1, 4*REGSIZE(sp)
	SREG s2, 5*REGSIZE(sp)
	SREG s3, 6*REGSIZE(sp)
	SREG s4, 7*REGSIZE(sp)
	SREG s5, 8*REGSIZE(sp)
	SREG s6, 9*REGSIZE(sp)
	SREG s7, 10*REGSIZE(sp)
	SREG s8, 11*REGSIZE(sp)
	SREG s9, 12*REGSIZE(sp)
	SREG s10, 13*REGSIZE(sp)
	SREG s11, 14*REGSIZE(sp)
#if SAVEREG1 == 27
	SFREG fs0, 15*REGSIZE(sp)
	SFREG fs1, 16*REGSIZE(sp)
	SFREG fs2, 17*REGSIZE(sp)
	SFREG fs3, 18*REGSIZE(sp)
	SFREG fs4, 19*REGSIZE(sp)
	SFREG fs5, 20*REGSIZE(sp)
	SFREG fs6, 21*REGSIZE(sp)
	SFREG fs7, 22*REGSIZE(sp)
	SFREG fs8, 23*REGSIZE(sp)
	SFREG fs9, 24*REGSIZE(sp)
	SFREG fs10, 25*REGSIZE(sp)
	SFREG fs11, 26*REGSIZE(sp)
#endif
	la a1, p_runtsk					/* p_runtskをA0に */
	LREG a0, 0(a1)
	SREG sp, TCB_sp(a0)				/* タスクスタックを保存 */
	la a1, dispatch_r
	SREG a1, TCB_pc(a0)				/* 実行再開番地を保存 */
	j dispatcher

	.globl dispatch_r
dispatch_r:
	LREG ra, 0*REGSIZE(sp)			/* returnアドレスを復帰 */
	LREG gp, 1*REGSIZE(sp)			/* call先セーブのレジスタを復帰 */
	LREG tp, 2*REGSIZE(sp)
	LREG s0, 3*REGSIZE(sp)
	LREG s1, 4*REGSIZE(sp)
	LREG s2, 5*REGSIZE(sp)
	LREG s3, 6*REGSIZE(sp)
	LREG s4, 7*REGSIZE(sp)
	LREG s5, 8*REGSIZE(sp)
	LREG s6, 9*REGSIZE(sp)
	LREG s7, 10*REGSIZE(sp)
	LREG s8, 11*REGSIZE(sp)
	LREG s9, 12*REGSIZE(sp)
	LREG s10, 13*REGSIZE(sp)
	LREG s11, 14*REGSIZE(sp)
#if SAVEREG1 == 27
	LFREG fs0, 15*REGSIZE(sp)
	LFREG fs1, 16*REGSIZE(sp)
	LFREG fs2, 17*REGSIZE(sp)
	LFREG fs3, 18*REGSIZE(sp)
	LFREG fs4, 19*REGSIZE(sp)
	LFREG fs5, 20*REGSIZE(sp)
	LFREG fs6, 21*REGSIZE(sp)
	LFREG fs7, 22*REGSIZE(sp)
	LFREG fs8, 23*REGSIZE(sp)
	LFREG fs9, 24*REGSIZE(sp)
	LFREG fs10, 25*REGSIZE(sp)
	LFREG fs11, 26*REGSIZE(sp)
#endif
	addi sp, sp, SAVEREG1*REGSIZE	/* レジスタ保存領域を解放 */
	li a2, TCB_enatex_bit			/* enatexがfalseならリターン */
	lbu a1, TCB_enatex(a0)
	sra a1, a1, a2
	andi a1, a1, 1
	beqz a1, dispatch_r_1
	LREG a1, TCB_texptn(a0)			/* texptnが0ならリターン */
	beqz a1, dispatch_r_1
	la a2, ipmflg					/* ipmflgがtrueであれば            */
	lw a1, 0(a2)
	bnez a1, call_texrtn			/* タスク例外処理ルーチンの呼出し */
dispatch_r_1:
	ret

/*
 *  ディスパッチャの動作開始（prc_support.S）
 */
	.globl start_dispatch
start_dispatch:
	/*
	 *  このルーチンは，カーネル起動時に，すべての割込みを禁止した状態
	 * （割込みロック状態と同等）で呼び出される．また，割込みモード（非
	 *  タスクコンテキストと同等）で呼び出されることを想定している．
	 *
	 *  prc_initializeで，lock_flagをtrueに，mieはinit_mieに
	 *  カーネル管理外の割込みを許可済みで，CPUロック状態・（モデル上の）
	 *  割込み優先度マスク全解除状態になっている．
	 *  (カーネル管理外の割込みを許可しておかないとmtipがうまく起動しない)
	 *  また，initialize_taskでdisdspをfalseに初期化しているため，ディ
	 *  スパッチ許可状態になっている．
	 */
	la a0, _kernel_istk				/* STACKをカーネルISTKに */
	LREG sp, 0(a0)
	la a0, _kernel_istksz
	LREG a1, 0(a0)
	add sp, sp, a1
	j dispatcher_0

/*
 *  現在のコンテキストを捨ててディスパッチ
 */
	.globl exit_and_dispatch
exit_and_dispatch:
	/* ディスパッチャ本体（dispatcher）へ */

/*
 *  ディスパッチャ本体
 */
dispatcher:
	/*
	 *  このルーチンは，タスクコンテキスト・CPUロック状態・ディスパッチ
	 *  許可状態・（モデル上の）割込み優先度マスク全解除状態で呼び出さ
	 *  れる．
	 *
	 *  すなわち，マスタモード・lock_flagがtrue・disdspがfalse・dspflg
	 *  がtrue・saved_iipmがIIPM_ENAALLとなっている．実行再開番地へもこ
	 *  の状態のまま分岐する．
	 */
#ifdef LOG_DSP_ENTER
	la a2, p_runtsk					/* p_runtskをパラメータに */
	LREG a0, 0(a2)
	jal log_dsp_enter
#endif /* LOG_DSP_ENTER */
dispatcher_0:
	la a1, p_schedtsk				/* p_schedtskをp_runtskに */
	LREG a0, 0(a1)
	la a2, p_runtsk
	SREG a0, 0(a2)
	beqz a0, dispatcher_1			/* p_runtskがNULLならdispatcher_1へ */
	LREG sp, TCB_sp(a0)				/* タスクスタックを復帰 */
#ifdef LOG_DSP_LEAVE
	jal log_dsp_leave
	la a2, p_runtsk					/* p_runtskを復帰 */
	LREG a0, 0(a2)
#endif /* LOG_DSP_LEAVE */
	LREG a1, TCB_pc(a0)				/* 実行再開番地へ分岐 */
	jr a1
dispatcher_1:
	/*
	 *  CPUロック状態を解除する準備をする．
	 */
	csrr a5, mie					/* mieをa5に保存 */
	la a3, lock_flag				/* CPUロック解除状態に */
	sw zero, 0(a3)
dispatcher_2:
	/*
	 *  割込みを許可し，割込みモードに切り換えて，割込みを待つ．
	 *
	 *  ここで割込みモードに切り換えるのは，ここで発生する割込み処理に
	 *  どのスタックを使うかという問題の解決と，割込みハンドラ内でのタ
	 *  スクディスパッチの防止という2つの意味がある．
	 *
	 *  プロセッサを割込み待ちに移行させる処理と，割込み許可とは，不可
	 *  分に行なう必要がある（M68040ではstop命令で両方行なうので問題な
	 *  い）．これを不可分に行なわない場合，割込みを許可した直後に割込
	 *  みが入り，その中でタスクが実行可能状態になると，実行すべきタス
	 *  クがあるにもかかわらずプロセッサが割込み待ちになってしまう．
	 *
	 *  割込み待ちの間は，p_runtskをNULL（＝0）に設定しなければならな
	 *  い．このように設定しないと，割込みハンドラからiget_tidを呼び出
	 *  した際の動作が仕様に合致しなくなる．
	 */
	la a1, kernel_mie				/* 割込み待ち */
	LREG a2, 0(a1)
	csrs mie, a2
	wfi
	csrw mie, a5					/* 元の状態に戻す */
	la a2, reqflg					/* reqflgがfalseならdispatcher_2へ */
	lw a1, 0(a2)
	beqz a1, dispatcher_2
	sw zero, 0(a2)					/* reqflgをfalseに */

	/*
	 *  CPUロック状態に戻す．割込み待ちの間に実行した割込みハンドラによ
	 *  り，saved_iipmが書き換えられる可能性があるため，元の値に戻す必
	 *  要がある．dispatcherが実行される時は，saved_iipmがIIPM_ENAALL
	 *  となっているため，ここではsaved_iipmをIIPM_ENAALL（＝0）に戻せ
	 *  ばよい．
	 */
	la a3, lock_flag				/* CPUロック状態に */
	li a1, true
	sw a1, 0(a3)
	j dispatcher_0

/*
 *  カーネルの終了処理の呼出し
 *
 *  RISCVでは，モード切換えによりスタックも切り換わらないため，明示的な
 *  スタック切換えを行う．最初から割込みモードであった場合も，同じ処理
 *  でよい．
 */
	.globl call_exit_kernel
call_exit_kernel:
	la a0, _kernel_istk				/* STACKをカーネルISTKに */
	LREG sp, 0(a0)
	la a0, _kernel_istksz
	LREG a1, 0(a0)
	add sp, sp, a1
	j exit_kernel					/* カーネルの終了処理を呼ぶ */

/*
 *  タスク開始時処理
 */
	.text
	.globl start_r
start_r:
	la a1, lock_flag				/* CPUロック解除状態に */
	sw zero, 0(a1)
	la ra, ext_tsk					/* ext_tskを戻り番地に設定 */
	li a2, KERNEL_MIE
	csrrs a2, mie, a2				/* 割込み許可   */
	LREG a1, TCB_p_tinib(a0)		/* p_runtsk->p_tinibをa1に */
	LREG a0, TINIB_exinf(a1)		/* exinfを引数レジスタa0に  */
	LREG a2, TINIB_task(a1)			/* タスクの起動番地をa2に */
	jr a2


/*
 *  MACHINE割込み出口処理
 *
 *  第一レベルのMACHIE割込みを行う．スタックするレジスタはネスト割込みとほぼ
 *  同じ，ユーザースタック上に，t3-t6までのレジスタはユーザースタックに
 *  保存する．(ネスト割込みではシステムスタックに保存)そのため、
 *  4*RGSIZEバイト分、割込みのためにユーザースタックを消費する．
 *  例外/割込みが発生すると，システムスタック上に以下の情報とスクラッチ
 *  レジスタを保存する．
 *
 *   ------------
 *  | mstatus    |
 *   ------------
 *  | mpc        |
 *   ------------
 *  | mcause     |
 *   ------------
 *  | mip        |
 *   ------------
 *  | sp(x2)     |
 *   ------------
 *  | reserved   |
 *   ------------
 *  | a0(x10)    |
 *   ------------
 *  | a1(x11)    |
 *   ------------
 *  | ra(x1)     |
 *   ------------
 *  | a2(x12)    |
 *   ------------
 */
	.text
	.align 4
	.global trap_entry
trap_entry:
	addi sp, sp, -SAVEREG2*REGSIZE	/* ユーザースタックにワークレジスタの保存領域を作成 */
	SREG t3, 18*REGSIZE(sp)			/* t3-t6をワークレジスタとして使用する */
	SREG t4, 19*REGSIZE(sp)
	SREG t5, 20*REGSIZE(sp)
	SREG t6, 21*REGSIZE(sp)
	la t4, _kernel_istk				/* STACKをカーネルISTKに */
	LREG t5, 0(t4)
	la t4, _kernel_istksz
	LREG t6, 0(t4)
	mv t4, sp						/* ユーザースタックをt4にコピー */
	add sp, t5, t6					/* システムスタックを設定 */

	addi sp, sp, -SAVEREG2*REGSIZE	/* システムスタック保存領域を作成 */
	SREG a0, 6*REGSIZE(sp)			/* スクラッチレジスタを保存 */
	SREG a1, 7*REGSIZE(sp)
	SREG a2, 8*REGSIZE(sp)
	SREG ra, 9*REGSIZE(sp)
	SREG a3, 10*REGSIZE(sp)
	SREG a4, 11*REGSIZE(sp)
	SREG a5, 12*REGSIZE(sp)
	SREG a6, 13*REGSIZE(sp)
	SREG a7, 14*REGSIZE(sp)
	SREG t0, 15*REGSIZE(sp)
	SREG t1, 16*REGSIZE(sp)
	SREG t2, 17*REGSIZE(sp)
#if SAVEREG2 == 42
	SFREG ft0, 22*REGSIZE(sp)
	SFREG ft1, 23*REGSIZE(sp)
	SFREG ft2, 24*REGSIZE(sp)
	SFREG ft3, 25*REGSIZE(sp)
	SFREG ft4, 26*REGSIZE(sp)
	SFREG ft5, 27*REGSIZE(sp)
	SFREG ft6, 28*REGSIZE(sp)
	SFREG ft7, 29*REGSIZE(sp)
	SFREG fa0, 30*REGSIZE(sp)
	SFREG fa1, 31*REGSIZE(sp)
	SFREG fa2, 32*REGSIZE(sp)
	SFREG fa3, 33*REGSIZE(sp)
	SFREG fa4, 34*REGSIZE(sp)
	SFREG fa5, 35*REGSIZE(sp)
	SFREG fa6, 36*REGSIZE(sp)
	SFREG fa7, 37*REGSIZE(sp)
	SFREG ft8, 38*REGSIZE(sp)
	SFREG ft9, 39*REGSIZE(sp)
	SFREG ft10, 40*REGSIZE(sp)
	SFREG ft11, 41*REGSIZE(sp)
#endif

	csrr a0, mcause					/* mcauseを2に保存 */
	SREG a0, 2*REGSIZE(sp)
	csrr t5, mepc					/* mpcを1に保存 */
	SREG t5, 1*REGSIZE(sp)
	csrr t6, mstatus				/* mstatusを0に保存 */
	SREG t6, 0*REGSIZE(sp)
	csrr t3, mie					/* mieを3に保存 */
	SREG t3, 3*REGSIZE(sp)
	SREG t4, 4*REGSIZE(sp)			/* ユーザースタックを4に保存 */
	li a2, KERNEL_MIE
	csrc mie, a2					/* カーネル内割込み禁止   */
	li a3, (MSTATUS_MPP | MSTATUS_MIE)
	csrs mstatus, a3				/* カーネル外割込み許可 */
	mv a1, sp						/* スタックをa1に設定 */
	call handle_trap				/* MACHINEハンドラを呼び出す */

	LREG a0, 6*REGSIZE(sp)			/* スクラッチレジスタを復帰 */
	LREG a1, 7*REGSIZE(sp)
	LREG a2, 8*REGSIZE(sp)
	LREG ra, 9*REGSIZE(sp)
	LREG a3, 10*REGSIZE(sp)
	LREG a4, 11*REGSIZE(sp)
	LREG a5, 12*REGSIZE(sp)
	LREG a6, 13*REGSIZE(sp)
	LREG a7, 14*REGSIZE(sp)
	LREG t0, 15*REGSIZE(sp)
	LREG t1, 16*REGSIZE(sp)
	LREG t2, 17*REGSIZE(sp)
#if SAVEREG2 == 42
	LFREG ft0, 22*REGSIZE(sp)
	LFREG ft1, 23*REGSIZE(sp)
	LFREG ft2, 24*REGSIZE(sp)
	LFREG ft3, 25*REGSIZE(sp)
	LFREG ft4, 26*REGSIZE(sp)
	LFREG ft5, 27*REGSIZE(sp)
	LFREG ft6, 28*REGSIZE(sp)
	LFREG ft7, 29*REGSIZE(sp)
	LFREG fa0, 30*REGSIZE(sp)
	LFREG fa1, 31*REGSIZE(sp)
	LFREG fa2, 32*REGSIZE(sp)
	LFREG fa3, 33*REGSIZE(sp)
	LFREG fa4, 34*REGSIZE(sp)
	LFREG fa5, 35*REGSIZE(sp)
	LFREG fa6, 36*REGSIZE(sp)
	LFREG fa7, 37*REGSIZE(sp)
	LFREG ft8, 38*REGSIZE(sp)
	LFREG ft9, 39*REGSIZE(sp)
	LFREG ft10, 40*REGSIZE(sp)
	LFREG ft11, 41*REGSIZE(sp)
#endif

	la t5, reqflg					/* reqflgがtrueであればtrap_entery_2へ */
	lw t6, 0(t5)
	bnez t6, trap_entry_2
	la t5, lock_flag				/* CPUロック解除の準備 */
	sw zero, 0(t5)
	LREG t5, 1*REGSIZE(sp)			/* mepcの取り出し */
	LREG t6, 0*REGSIZE(sp)			/* mstatusの取り出し */
	LREG t4, 3*REGSIZE(sp)			/* mieの取り出し */
	csrw mepc, t5					/* mepcを復帰 */
	csrw mstatus, t6				/* mstatusを復帰 */
	csrw mie, t4					/* mieを復帰 */
	LREG sp, 4*REGSIZE(sp)			/* ユーザースタックを復帰 */

	LREG t3, 18*REGSIZE(sp)			/* ワーク用スクラッチレジスタを復帰 */
	LREG t4, 19*REGSIZE(sp)
	LREG t5, 20*REGSIZE(sp)
	LREG t6, 21*REGSIZE(sp)
	addi sp, sp, SAVEREG2*REGSIZE	/* スタックを開放 */
	mret

trap_entry_2:
	LREG t5, 1*REGSIZE(sp)			/* mepcの取り出し */
	LREG t4, 2*REGSIZE(sp)			/* mcauseの取り出し */
	LREG t3, 3*REGSIZE(sp)			/* mieの取り出し */
	LREG t6, 0*REGSIZE(sp)			/* mstatusの取り出し */
	LREG sp, 4*REGSIZE(sp)			/* ユーザースタックを復帰 */

	SREG t6, 0*REGSIZE(sp)			/* mstatusの保存 */
	SREG t3, 3*REGSIZE(sp)			/* mieの保存 */
	SREG t4, 2*REGSIZE(sp)			/* mcauseの保存 */
	SREG t5, 1*REGSIZE(sp)			/* mepcの保存 */
	SREG a0, 6*REGSIZE(sp)			/* スクラッチレジスタを保存 */
	SREG a1, 7*REGSIZE(sp)
	SREG a2, 8*REGSIZE(sp)
	SREG ra, 9*REGSIZE(sp)
	SREG a3, 10*REGSIZE(sp)
	SREG a4, 11*REGSIZE(sp)
	SREG a5, 12*REGSIZE(sp)
	SREG a6, 13*REGSIZE(sp)
	SREG a7, 14*REGSIZE(sp)
	SREG t0, 15*REGSIZE(sp)
	SREG t1, 16*REGSIZE(sp)
	SREG t2, 17*REGSIZE(sp)
#if SAVEREG2 == 42
	SFREG ft0, 22*REGSIZE(sp)
	SFREG ft1, 23*REGSIZE(sp)
	SFREG ft2, 24*REGSIZE(sp)
	SFREG ft3, 25*REGSIZE(sp)
	SFREG ft4, 26*REGSIZE(sp)
	SFREG ft5, 27*REGSIZE(sp)
	SFREG ft6, 28*REGSIZE(sp)
	SFREG ft7, 29*REGSIZE(sp)
	SFREG fa0, 30*REGSIZE(sp)
	SFREG fa1, 31*REGSIZE(sp)
	SFREG fa2, 32*REGSIZE(sp)
	SFREG fa3, 33*REGSIZE(sp)
	SFREG fa4, 34*REGSIZE(sp)
	SFREG fa5, 35*REGSIZE(sp)
	SFREG fa6, 36*REGSIZE(sp)
	SFREG fa7, 37*REGSIZE(sp)
	SFREG ft8, 38*REGSIZE(sp)
	SFREG ft9, 39*REGSIZE(sp)
	SFREG ft10, 40*REGSIZE(sp)
	SFREG ft11, 41*REGSIZE(sp)
#endif

	la a0, reqflg					/* reqflgをfalseに */
	sw zero, 0(a0)
	la a1, lock_flag				/* loc_flagをtrueに */
	li a2, true
	sw a2, 0(a1)

	la a1, p_runtsk					/* p_runtskをa0に */
	LREG a0, 0(a1)
	la a2, dspflg					/* dspflgがfalseならret_int_1へ */
	lw a3, 0(a2)
	beqz a3, ret_int_1
	la a2, p_schedtsk				/* p_runtskとp_schedtskが同じなら */
	LREG a3, 0(a2)
	beq a0, a3, ret_int_1			/* ret_int_1へ */

	addi sp, sp, -SAVEREG3*REGSIZE	/* call先セーブのレジスタを保存 */
	SREG gp, 0*REGSIZE(sp)
	SREG tp, 1*REGSIZE(sp)
	SREG s0, 2*REGSIZE(sp)
	SREG s1, 3*REGSIZE(sp)
	SREG s2, 4*REGSIZE(sp)
	SREG s3, 5*REGSIZE(sp)
	SREG s4, 6*REGSIZE(sp)
	SREG s5, 7*REGSIZE(sp)
	SREG s6, 8*REGSIZE(sp)
	SREG s7, 9*REGSIZE(sp)
	SREG s8, 10*REGSIZE(sp)
	SREG s9, 11*REGSIZE(sp)
	SREG s10, 12*REGSIZE(sp)
	SREG s11, 13*REGSIZE(sp)
#if SAVEREG3 == 26
	SFREG fs0, 14*REGSIZE(sp)
	SFREG fs1, 15*REGSIZE(sp)
	SFREG fs2, 16*REGSIZE(sp)
	SFREG fs3, 17*REGSIZE(sp)
	SFREG fs4, 18*REGSIZE(sp)
	SFREG fs5, 19*REGSIZE(sp)
	SFREG fs6, 20*REGSIZE(sp)
	SFREG fs7, 21*REGSIZE(sp)
	SFREG fs8, 22*REGSIZE(sp)
	SFREG fs9, 23*REGSIZE(sp)
	SFREG fs10, 24*REGSIZE(sp)
	SFREG fs11, 25*REGSIZE(sp)
#endif
	SREG sp, TCB_sp(a0)				/* タスクスタックを保存 */
	la a1, ret_int_r				/* 実行再開番地を保存 */
	SREG a1, TCB_pc(a0)
	j dispatcher

ret_int_r:
	LREG gp, 0*REGSIZE(sp)			/* call先セーブのレジスタを復帰 */
	LREG tp, 1*REGSIZE(sp)
	LREG s0, 2*REGSIZE(sp)
	LREG s1, 3*REGSIZE(sp)
	LREG s2, 4*REGSIZE(sp)
	LREG s3, 5*REGSIZE(sp)
	LREG s4, 6*REGSIZE(sp)
	LREG s5, 7*REGSIZE(sp)
	LREG s6, 8*REGSIZE(sp)
	LREG s7, 9*REGSIZE(sp)
	LREG s8, 10*REGSIZE(sp)
	LREG s9, 11*REGSIZE(sp)
	LREG s10, 12*REGSIZE(sp)
	LREG s11, 13*REGSIZE(sp)
#if SAVEREG3 == 26
	LFREG fs0, 14*REGSIZE(sp)
	LFREG fs1, 15*REGSIZE(sp)
	LFREG fs2, 16*REGSIZE(sp)
	LFREG fs3, 17*REGSIZE(sp)
	LFREG fs4, 18*REGSIZE(sp)
	LFREG fs5, 19*REGSIZE(sp)
	LFREG fs6, 20*REGSIZE(sp)
	LFREG fs7, 21*REGSIZE(sp)
	LFREG fs8, 22*REGSIZE(sp)
	LFREG fs9, 23*REGSIZE(sp)
	LFREG fs10, 24*REGSIZE(sp)
	LFREG fs11, 25*REGSIZE(sp)
#endif
	addi sp, sp, SAVEREG3*REGSIZE
ret_int_1:
	/*
	 *  enatexがtrueで，texptnが0でなく，ipmflgがtrueであれば，タスク
	 *  例外処理ルーチンを呼び出す．
	 */
	li a2, TCB_enatex_bit			/* enatexがfalseならret_int_2へ */
	lbu a1, TCB_enatex(a0)
	sra a1, a1, a2
	andi a1, a1, 1
	beqz a1, ret_int_2
	lw a1, TCB_texptn(a0)			/* texptnが0ならばret_int_2へ */
	beqz a1, ret_int_2
	la a2, ipmflg					/* ipmflgがfalseならret_int_2へ */
	lw a1, 0(a2)
	beqz a1, ret_int_2
	jal call_texrtn
ret_int_2:
	/*
	 *  割込み処理からのリターンにより，CPUロック解除状態に移行するよ
	 *  う準備する．割込み優先度マスクは，MRET命令により元の値に戻るた
	 *  め，lock_flagをfalseにしておけばよい．
	 */
	la a0, lock_flag				/* CPUロック解除の準備 */
	sw zero, 0(a0)

ret_int_3:
	LREG a1, 3*REGSIZE(sp)			/* mieの取り出し */
	LREG a2, 1*REGSIZE(sp)			/* mpcの取り出し */
	LREG a3, 0*REGSIZE(sp)			/* mstatusの取り出し */
	csrw mepc, a2					/* mpcの復帰 */
	csrw mstatus, a3				/* mstatusの復帰 */
	csrw mie, a1					/* mieの復帰 */

	LREG a0, 6*REGSIZE(sp)			/* スクラッチレジスタの復帰 */
	LREG a1, 7*REGSIZE(sp)
	LREG a2, 8*REGSIZE(sp)
	LREG ra, 9*REGSIZE(sp)
	LREG a3, 10*REGSIZE(sp)
	LREG a4, 11*REGSIZE(sp)
	LREG a5, 12*REGSIZE(sp)
	LREG a6, 13*REGSIZE(sp)
	LREG a7, 14*REGSIZE(sp)
	LREG t0, 15*REGSIZE(sp)
	LREG t1, 16*REGSIZE(sp)
	LREG t2, 17*REGSIZE(sp)
	LREG t3, 18*REGSIZE(sp)
	LREG t4, 19*REGSIZE(sp)
	LREG t5, 20*REGSIZE(sp)
	LREG t6, 21*REGSIZE(sp)
#if SAVEREG2 == 42
	LFREG ft0, 22*REGSIZE(sp)
	LFREG ft1, 23*REGSIZE(sp)
	LFREG ft2, 24*REGSIZE(sp)
	LFREG ft3, 25*REGSIZE(sp)
	LFREG ft4, 26*REGSIZE(sp)
	LFREG ft5, 27*REGSIZE(sp)
	LFREG ft6, 28*REGSIZE(sp)
	LFREG ft7, 29*REGSIZE(sp)
	LFREG fa0, 30*REGSIZE(sp)
	LFREG fa1, 31*REGSIZE(sp)
	LFREG fa2, 32*REGSIZE(sp)
	LFREG fa3, 33*REGSIZE(sp)
	LFREG fa4, 34*REGSIZE(sp)
	LFREG fa5, 35*REGSIZE(sp)
	LFREG fa6, 36*REGSIZE(sp)
	LFREG fa7, 37*REGSIZE(sp)
	LFREG ft8, 38*REGSIZE(sp)
	LFREG ft9, 39*REGSIZE(sp)
	LFREG ft10, 40*REGSIZE(sp)
	LFREG ft11, 41*REGSIZE(sp)
#endif
	addi sp, sp, SAVEREG2*REGSIZE
	mret

/*
 *  MACHINEネスト割込み出入口処理
 *
 *  trap_nestは，ネストしたMACHINE割込みの出入口処理を行う．
 *  mtvecの設定は呼び出したhandle_trapで行う．
 *  handle_trapからのリターンはネスト状態に限定されるため
 *  この出入り口では、スタックの変更も行わない．
 */
	.text
	.align 4
	.global trap_nest
trap_nest:
	addi sp, sp, -SAVEREG2*REGSIZE	/* システムスタック保存領域を作成 */
	SREG a0, 6*REGSIZE(sp)			/* スクラッチレジスタを保存 */
	SREG a1, 7*REGSIZE(sp)
	SREG a2, 8*REGSIZE(sp)
	SREG ra, 9*REGSIZE(sp)
	SREG a3, 10*REGSIZE(sp)
	SREG a4, 11*REGSIZE(sp)
	SREG a5, 12*REGSIZE(sp)
	SREG a6, 13*REGSIZE(sp)
	SREG a7, 14*REGSIZE(sp)
	SREG t0, 15*REGSIZE(sp)
	SREG t1, 16*REGSIZE(sp)
	SREG t2, 17*REGSIZE(sp)
	SREG t3, 18*REGSIZE(sp)
	SREG t4, 19*REGSIZE(sp)
	SREG t5, 20*REGSIZE(sp)
	SREG t6, 21*REGSIZE(sp)
#if SAVEREG2 == 42
	SFREG ft0, 22*REGSIZE(sp)
	SFREG ft1, 23*REGSIZE(sp)
	SFREG ft2, 24*REGSIZE(sp)
	SFREG ft3, 25*REGSIZE(sp)
	SFREG ft4, 26*REGSIZE(sp)
	SFREG ft5, 27*REGSIZE(sp)
	SFREG ft6, 28*REGSIZE(sp)
	SFREG ft7, 29*REGSIZE(sp)
	SFREG fa0, 30*REGSIZE(sp)
	SFREG fa1, 31*REGSIZE(sp)
	SFREG fa2, 32*REGSIZE(sp)
	SFREG fa3, 33*REGSIZE(sp)
	SFREG fa4, 34*REGSIZE(sp)
	SFREG fa5, 35*REGSIZE(sp)
	SFREG fa6, 36*REGSIZE(sp)
	SFREG fa7, 37*REGSIZE(sp)
	SFREG ft8, 38*REGSIZE(sp)
	SFREG ft9, 39*REGSIZE(sp)
	SFREG ft10, 40*REGSIZE(sp)
	SFREG ft11, 41*REGSIZE(sp)
#endif

	csrr a3, mstatus			    /* mstatusを0に保存 */
	SREG a3, 0*REGSIZE(sp)
	csrr a1, mie					/* mieを3に保存 */
	SREG a1, 3*REGSIZE(sp)
	addi a2, sp, 22*REGSIZE			/* システムスタックを4に保存 */
	SREG a2, 4*REGSIZE(sp)
	csrr a0, mcause					/* mcauseをa0に取り出し */
	SREG a0, 2*REGSIZE(sp)			/* mcauseを2に保存 */
	csrr a3, mepc					/* mpcを1に保存 */
	SREG a3, 1*REGSIZE(sp)
	li a2, KERNEL_MIE
	csrc mie, a2					/* カーネル内割込み禁止   */
	li a3, (MSTATUS_MPP | MSTATUS_MIE)
	csrs mstatus, a3				/* カーネル外割込み許可 */
	mv a1, sp						/* スタックをa1に設定 */
	la ra, ret_int_3				/* リターンアドレスをセット */
	j handle_trap					/* MACHINEハンドラを呼び出す */

/*
 *  微少時間待ち（本来はSILのターゲット依存部）
 */
	.globl sil_dly_nse
	.align 4
sil_dly_nse:
	addi  a0, a0, (-SIL_DLY_TIM1)	/* a0からSIL_DLY_TIM1を引く */
	blez  a0, _sil_dly_nse_2		/* 結果が0以下ならリターン */
_sil_dly_nse_1:
	addi  a0, a0, (-SIL_DLY_TIM2)	/* a0からSIL_DLY_TIM2を引く */
	bgtz  a0, _sil_dly_nse_1		/* 結果が0より大きければループ */
_sil_dly_nse_2:
	ret

