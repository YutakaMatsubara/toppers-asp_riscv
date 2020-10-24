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
 *  $Id: prc_config.h 2013 2019-09-18 21:29:10Z roi $
 */

/*
 *		プロセッサ依存モジュール（RISC-V用）
 *
 *  このインクルードファイルは，target_config.h（または，そこからインク
 *  ルードされるファイル）のみからインクルードされる．他のファイルから
 *  直接インクルードしてはならない．
 */

#ifndef TOPPERS_PRC_CONFIG_H
#define TOPPERS_PRC_CONFIG_H

#ifndef TOPPERS_MACRO_ONLY

/*
 *  プロセッサの特殊命令のインライン関数定義
 */
#include "encoding.h"

/*
 *  MCAUSE REGISTER定義
 */
#define MCAUSE_CAUSE        0x7FFFFFFF

/*
 *  使用するシリアルポートID
 */
#ifndef SIO_PORTID
#define SIO_PORTID		(1)
#endif /* SIO_PORTID */

/*
 *  MACHINEの最大割込み数を定義
 */
#define TMAX_MACHNE_INTNO	32

/*
 *  タスクコンテキストブロックの定義
 */
typedef struct task_context_block {
	void	*sp;		/* スタックポインタ */
	FP		pc;			/* プログラムカウンタ */
} TSKCTXB;

#endif /* TOPPERS_MACRO_ONLY */

/*
 *  割込み優先度マスク操作ライブラリ
 *
 *  RISCV/32では，PLICの割込みスレッシュホールドで割込みレベルを管理する．
 */

/*
 *  割込み優先度マスクの外部表現と内部表現の変換
 */
#define EXT_IPM(iipm)	(-CAST(PRI, (iipm)))		/* 外部表現に変換 */
#define INT_IPM(ipm)	CAST(uint16_t, -(ipm))		/* 内部表現に変換 */

/*
 *  カーネル割込み設定定義
 */
#define KERNEL_MIE		(MIP_MTIP | MIP_MEIP)


#ifndef TOPPERS_MACRO_ONLY

/*
 *  CPUロックフラグ実現のための変数
 *
 *  これらの変数は，CPUロック状態の時のみ書き換えてよいものとする．
 */
extern volatile bool_t			lock_flag;	/* CPUロックフラグの値を保持する変数 */
extern volatile uint16_t		inest_lvl;	/* 割込みネストを保存する変数 */
extern volatile unsigned long	kernel_mie;	/* デフォルトのMIE値を保存する変数 */

/*
 *  TOPPERS標準割込み処理モデルの実現
 *
 *  割込み優先度マスクとしては，mie（MACHINE割込みイネーブルレジスタ）を
 *  用いる．全割込みを禁止する機能として，mstatusのMIEやPLICの割込みスレ
 *  ッドが，カーネル管理外の割込みをサポートするため，これらはCPUロック
 *  のために用いない．
 *  PLICの割込みスレッドでは、MITの割込みロックができないことも、
 *  この選択とした理由である．
 *
 *  CPUロック状態を管理すための変数(lock_flag)を用意する．
 *  システムスタックのネスト管理の変数(inest_lvl)を用意する．
 *  外部割込みの制御はPLICを用いるが、この制御はPRCでは管理せず
 *  ターゲットレベルで管理を行う．
 */

/*
 *  コンテキストの参照
 *
 *  RISCVでは，割込みネストレベルでコンテキストを判定する．
 */
Inline bool_t
sense_context(void)
{
	return inest_lvl != 0;
}

#endif /* TOPPERS_MACRO_ONLY */

/*
 *  例外フレームのオフセット
 */
#define P_EXCINF_OFFSET_MSTATUS     0x00
#define P_EXCINF_OFFSET_PC          0x01
#define P_EXCINF_OFFSET_MCAUSE		0x02
#define P_EXCONF_OFFSET_MIE         0x03
#define P_EXCONF_OFFSET_SP          0x04


#ifndef TOPPERS_MACRO_ONLY

/*
 *  MACHINE割込みの禁止
 *
 *  割込み制御で使用するため作成．
 */
Inline void
dis_intm(void)
{
	clear_csr(mstatus, MSTATUS_MIE);
}

/*
 *  MACHINE割込みの許可
 *
 *  割込み制御で使用するため作成．
 */
Inline void
ena_intm(void)
{
	set_csr(mstatus, MSTATUS_MIE);
}

/*
 *  CPUロック状態への移行
 *
 *  mie（MACHINE割込みイネーブルレジスタ）を，カーネル管理割込み設
 *  定をマスクすることでCPUロック状態を設定する．
 *  また，lock_flagをtrueにする．
 *
 *  この関数は，CPUロック状態（lock_flagがtrueの状態）で呼ばれることは
 *  ないものと想定している．
 */
Inline void
x_lock_cpu(void)
{
	clear_csr(mie, KERNEL_MIE);
	lock_flag = true;
}

#define t_lock_cpu()	x_lock_cpu()
#define i_lock_cpu()	x_lock_cpu()

/*
 *  CPUロック状態の解除
 *
 *  lock_flagをfalseにし，mie（MACHINE割込みイネーブルレジスタ）中の，
 *  イネーブル設定を行う．
 *
 *  この関数は，CPUロック状態（lock_flagがtrueの状態）でのみ呼ばれるも
 *  のと想定している．
 */
Inline void
x_unlock_cpu(void)
{
	lock_flag = false;
	set_csr(mie, kernel_mie);
}

#define t_unlock_cpu()	x_unlock_cpu()
#define i_unlock_cpu()	x_unlock_cpu()

/*
 *  CPUロック状態の参照
 */
Inline bool_t
x_sense_lock(void)
{
	return(lock_flag);
}

#define t_sense_lock()	x_sense_lock()
#define i_sense_lock()	x_sense_lock()

/*
 *  chg_ipmで有効な割込み優先度の範囲の判定
 */
#define VALID_INTPRI_CHGIPM(intpri) \
				(TMIN_INTPRI <= (intpri) && (intpri) <= TMAX_INTPRI)

/*
 * （モデル上の）割込み優先度マスクの設定
 *
 *  CPUロックフラグがクリアされている時は，ハードウェアの割込み優先度マ
 *  スクを設定する．(mitは想定していない)
 */
Inline void
x_set_ipm(PRI intpri)
{
	set_ithreshold(INT_IPM(intpri));
}

#define t_set_ipm(intpri)	x_set_ipm(intpri)
#define i_set_ipm(intpri)	x_set_ipm(intpri)

/*
 * （モデル上の）割込み優先度マスクの参照
 *
 *  CPUロックフラグがクリアされている時はハードウェアの割込み優先度マ
 *  スクを参照する．
 */
Inline PRI
x_get_ipm(void)
{
	return(EXT_IPM(current_ithreshold()));
}

#define t_get_ipm()		x_get_ipm()
#define i_get_ipm()		x_get_ipm()

/*
 *  最高優先順位タスクへのディスパッチ（prc_support.S）
 *
 *  dispatchは，タスクコンテキストから呼び出されたサービスコール処理か
 *  ら呼び出すべきもので，タスクコンテキスト・CPUロック状態・ディスパッ
 *  チ許可状態・（モデル上の）割込み優先度マスク全解除状態で呼び出さな
 *  ければならない．
 */
extern void	dispatch(void);

/*
 *  ディスパッチャの動作開始（prc_support.S）
 *
 *  start_dispatchは，カーネル起動時に呼び出すべきもので，すべての割込
 *  みを禁止した状態（割込みロック状態と同等の状態）で呼び出さなければ
 *  ならない．
 */
extern void	start_dispatch(void) NoReturn;

/*
 *  現在のコンテキストを捨ててディスパッチ（prc_support.S）
 *
 *  exit_and_dispatchは，ext_tskから呼び出すべきもので，タスクコンテキ
 *  スト・CPUロック状態・ディスパッチ許可状態・（モデル上の）割込み優先
 *  度マスク全解除状態で呼び出さなければならない．
 */
extern void	exit_and_dispatch(void) NoReturn;

/*
 *  カーネルの終了処理の呼出し（prc_support.S）
 *
 *  call_exit_kernelは，カーネルの終了時に呼び出すべきもので，非タスク
 *  コンテキストに切り換えて，カーネルの終了処理（exit_kernel）を呼び出
 *  す．
 */
extern void call_exit_kernel(void) NoReturn;

/*
 *  MACHINE割込みトラップ関数 （prc_support.S）
 *
 *  trap_entryは最初のMACHINE割込みを処理する関数．
 */
extern void trap_entry(void);

/*
 *  MACHINE割込みネストトラップ関数 （prc_support.S）
 *
 *  trap_entryはネスト時のMACHINE割込みを処理する関数．
 */
extern void trap_nest(void);


/*
 *  タスクコンテキストの初期化
 *
 *  タスクが休止状態から実行できる状態に移行する時に呼ばれる．この時点
 *  でスタック領域を使ってはならない．
 *
 *  activate_contextを，インライン関数ではなくマクロ定義としているのは，
 *  この時点ではTCBが定義されていないためである．
 */
extern void	start_r(void);

#define activate_context(p_tcb)											\
{																		\
	(p_tcb)->tskctxb.sp = (void *)((char *)((p_tcb)->p_tinib->stk)		\
										+ (p_tcb)->p_tinib->stksz);		\
	(p_tcb)->tskctxb.pc = (void *) start_r;								\
}

/*
 *  calltexは使用しない
 */
#define OMIT_CALLTEX

/*
 *  例外ベクタテーブルの構造の定義
 */
typedef struct exc_vector_entry {
	FP		exc_handler;		/* 例外ハンドラの起動番地 */
} EXCVE;

/*
 *  MACHINE割込みハンドラ領域のテーブル
 */
extern volatile EXCVE m_interrupt_handlers[TMAX_MACHNE_INTNO];

/*
 *  CPU例外ハンドラの設定
 *
 *  ベクトル番号excnoのCPU例外ハンドラの出入口処理の番地をexc_entryに設
 *  定する．
 */
Inline void
x_define_exc(EXCNO excno, FP exc_entry)
{
	m_interrupt_handlers[excno].exc_handler = exc_entry;
}

/*
 *  MACHINE割込みハンドラの設定
 */
Inline void
x_machine_inh(INHNO inhno, FP int_entry)
{
	m_interrupt_handlers[inhno+16].exc_handler = int_entry;
}

/*
 *  CPU例外ハンドラの出入口処理の生成
 *
 *  CPU例外ハンドラの番地をA1に，CPU例外ハンドラ番号をD1に入れて，
 *  exchdr_entryに分岐する．割込みハンドラの出入口処理と同様に，CPU例外
 *  ハンドラ毎にCPU例外ハンドラを呼び出す処理を展開する方法もあるが，展
 *  開する処理内容が複雑であるため，採用していない．
 */

/*
 *  CPU例外ハンドラの出入口処理のラベルを作るマクロ
 */
#define EXC_ENTRY(excno, exchdr)	_kernel_##exchdr##_##excno

/*
 *  CPU例外ハンドラの出入口処理
 */
#if defined(__riscv64)
#define EXCHDR_ENTRY(excno, excno_num, exchdr) \
extern void _kernel_##exchdr##_##excno(void *sp); \
asm(".text							\n" \
"_kernel_" #exchdr "_" #excno ":	\n" \
"	addi sp, sp, -32				\n"	 /* 保存領域を確保 */ \
"	sd ra, 24(sp)					\n"	 /* return addressをセーブ */ \
"	csrsi mstatus, 8				\n"	 /* 割込みを許可(MSTATUS_MIE) */ \
"	mv a0, a1						\n"  /* stack pointerをa0に */ \
"	jal " #exchdr "					\n"	 /* exchdrに分岐 */ \
"	ld ra, 24(sp)					\n"	 /* return addressをリストア */ \
"	csrci mstatus, 8				\n"	 /* 割込みを禁止(MSTATUS_MIE) */ \
"	addi sp, sp, 32					\n"	 /* 保存領域を開放 */ \
"	ret								\n");/* リターン */
#else
#define EXCHDR_ENTRY(excno, excno_num, exchdr) \
extern void _kernel_##exchdr##_##excno(void *sp); \
asm(".text							\n" \
"_kernel_" #exchdr "_" #excno ":	\n" \
"	addi sp, sp, -16				\n"	 /* 保存領域を確保 */ \
"	sw ra, 12(sp)					\n"	 /* return addressをセーブ */ \
"	csrsi mstatus, 8				\n"	 /* 割込みを許可(MSTATUS_MIE) */ \
"	mv a0, a1						\n"  /* stack pointerをa0に */ \
"	jal " #exchdr "					\n"	 /* exchdrに分岐 */ \
"	lw ra, 12(sp)					\n"	 /* return addressをリストア */ \
"	csrci mstatus, 8				\n"	 /* 割込みを禁止(MSTATUS_MIE) */ \
"	addi sp, sp, 16					\n"	 /* 保存領域を開放 */ \
"	ret								\n");/* リターン */
#endif

/*
 *  CPU例外の発生した時のコンテキストの参照
 *
 *  CPU例外の発生した時のコンテキストが，タスクコンテキストの時にfalse，
 *  そうでない時にtrueを返す．
 */
Inline bool_t
exc_sense_context(void *p_excinf)
{
	return inest_lvl > 1;
}

/*
 *  CPU例外の発生した時のコンテキストと割込みのマスク状態の参照
 *
 *  CPU例外の発生した時のシステム状態が，カーネル実行中でなく，タスクコ
 *  ンテキストであり，全割込みロック状態でなく，CPUロック状態でなく，割
 *  込み優先度マスク全解除状態である時にtrue，そうでない時にfalseを返す
 *  （CPU例外がカーネル管理外の割込み処理中で発生した場合にもfalseを返
 *  す）．
 *
 *  CPU例外の発生した時のmie（MACHINE割込みイネーブルレジスタ）が初期設
 *  定でないで，カーネル実行中でないこと，全割込みロック状態でないこと
 *  ，CPUロック状態でないこと，割込み優先度マスク全解除状態であることの
 *  4つの条件をチェックすることができる（CPU例外が発生した時のlock_flag
 *  を参照する必要はない）．
 */
Inline bool_t
exc_sense_intmask(void *p_excinf)
{
	return(!exc_sense_context(p_excinf)
					&& ((read_csr(mie) & KERNEL_MIE) != 0));
}


/*
 *  プロセッサ依存の初期化
 */
extern void	prc_initialize(void);

/*
 *  プロセッサ依存の終了時処理
 */
extern void	prc_terminate(void);

/*
 *  C言語レベル MACHINE割込みハンドラ
 */
extern uint32_t handle_trap(unsigned long mcause, void *p_excinf);

#endif /* TOPPERS_MACRO_ONLY */
#endif /* TOPPERS_PRC_CONFIG_H */
