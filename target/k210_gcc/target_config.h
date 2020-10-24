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
 *  @(#) $Id: target_config.h 1952 2019-09-22 20:33:30Z roi $
 */

/*
 *		ターゲット依存モジュール（K210用）
 *
 *  カーネルのターゲット依存部のインクルードファイル．kernel_impl.hの
 *  ターゲット依存部の位置付けとなる．
 */

#ifndef TOPPERS_TARGET_CONFIG_H
#define TOPPERS_TARGET_CONFIG_H

/*
 *  ターゲットシステムのハードウェア資源の定義
 */
#include "kendryte-k210.h"

/*
 *  ターゲット定義のオブジェクト属性
 */
#define TARGET_INHATR	TA_NONKERNEL	/* カーネル管理外の割込み */

/*
 *  エラーチェック方法の指定
 */
#define CHECK_STKSZ_ALIGN	8	/* スタックサイズのアライン単位 */
#define CHECK_FUNC_ALIGN	2	/* 関数のアライン単位 */
#define CHECK_FUNC_NONNULL		/* 関数の非NULLチェック */
#define CHECK_STACK_ALIGN	8	/* スタック領域のアライン単位 */
#define CHECK_STACK_NONNULL		/* スタック領域の非NULLチェック */
#define CHECK_MPF_ALIGN		4	/* 固定長メモリプール領域のアライン単位 */
#define CHECK_MPF_NONNULL		/* 固定長メモリプール領域の非NULLチェック */
#define CHECK_MB_ALIGN		4	/* 管理領域のアライン単位 */

/*
 *  トレースログに関する設定
 */
#ifdef TOPPERS_ENABLE_TRACE
#include "logtrace/trace_config.h"
#endif /* TOPPERS_ENABLE_TRACE */

/*
 *  デフォルトの非タスクコンテキスト用のスタック領域の定義
 */
#define DEFAULT_ISTKSZ		0x4000U
#define DEFAULT_ISTK		(void *)(RAM_BASE_ADDR + RAM_SIZE - DEFAULT_ISTKSZ * 2)


#ifndef TOPPERS_MACRO_ONLY

/*
 *  割込み番号の範囲の判定
 */
#define VALID_INTNO(intno)          ((1 <= (intno)) && ((intno) <= TMAX_INTNO))
#define	VALID_INTNO_CREISR(intno)	VALID_INTNO(intno)
#define VALID_INTNO_DISINT(intno)	VALID_INTNO(intno)
#define VALID_INTNO_CFGINT(intno)	VALID_INTNO(intno)

/*
 *  PLIC THRESHOLD（ハードウェアの割込み優先度マスク，内部表現）の現在値の読出し
 */
Inline uint32_t
current_ithreshold(void)
{
	uint32_t hard_id = read_csr(mhartid);
	uint32_t off = TOFF_PLIC_THRESHOLD + (hard_id * NUM_PLIC_THRESHOLD);
	return sil_rew_mem((uint32_t *)(TADR_PLIC_BASE+off));
}

/*
 *  PLIC THRESHOLD（ハードウェアの割込み優先度マスク，内部表現）の現在値の設定
 */
Inline void
set_ithreshold(uint32_t threshold)
{
	uint32_t hard_id = read_csr(mhartid);
	uint32_t off = TOFF_PLIC_THRESHOLD + (hard_id * NUM_PLIC_THRESHOLD);
	sil_wrw_mem((uint32_t *)(TADR_PLIC_BASE+off), threshold);
}

/*
 *  PLIC 割込み優先度（ハードウェアの割込み優先度マスク，内部表現）の現在値の読出し
 */
Inline uint32_t
current_ipriority(INTNO intno)
{
	uint32_t off = TOFF_PLIC_PRIORITY + (intno * sizeof(uint32_t));
	return sil_rew_mem((uint32_t *)(TADR_PLIC_BASE+off));
}

/*
 *  PLIC 割込み優先度（ハードウェアの割込み優先度マスク，内部表現）の現在値の設定
 */
Inline void
set_ipriority(INTNO intno, uint32_t priority)
{
	uint32_t off = TOFF_PLIC_PRIORITY + (intno * sizeof(uint32_t));
	sil_wrw_mem((uint32_t *)(TADR_PLIC_BASE+off), (uint32_t)priority);
}

/*
 *  PLIC割込みハンドラテーブル
 */
extern const FP vector_table[];

/*
 *  割込み属性が設定されているかを判別するための変数（kernel_cfg.c）
 */
extern const uint32_t	bitpat_cfgint[];

/*
 *  割込み要求禁止フラグのセット
 *
 *  割込み属性が設定されていない割込み要求ラインに対して割込み要求禁止
 *  フラグをセットしようとした場合には，falseを返す．
 */
Inline bool_t
x_disable_int(INTNO intno)
{
	unsigned long hart_id = read_csr(mhartid);
	uint32_t	bitpat = 1 << (intno & 0x1f);
	uint32_t    bitpno = intno >> 5;
	uint32_t	off = TOFF_PLIC_ENABLE + (hart_id * NUM_PLIC_ENABLE) + ((intno / 32) * 4);

	if ((bitpat_cfgint[bitpno] & bitpat) == 0U) {
		return(false);
	}
	sil_wrw_mem((uint32_t *)(TADR_PLIC_BASE+off),
		(sil_rew_mem((uint32_t *)(TADR_PLIC_BASE+off)) & ~(1 << (intno % 32))));
	return(true);
}


#define t_disable_int(intno)	x_disable_int(intno)
#define i_disable_int(intno)	x_disable_int(intno)

/*
 *  割込み要求禁止フラグのクリア
 *
 *  割込み属性が設定されていない割込み要求ラインに対して割込み要求禁止
 *  フラグをクリアしようとした場合には，falseを返す．
 */
Inline bool_t
x_enable_int(INTNO intno)
{
	unsigned long hart_id = read_csr(mhartid);
	uint32_t	bitpat = 1 << (intno & 0x1f);
	uint32_t    bitpno = intno >> 5;
	uint32_t	off = TOFF_PLIC_ENABLE + (hart_id * (NUM_PLIC_ENABLE / 8)) + ((intno / 32) * 4);

	if ((bitpat_cfgint[bitpno] & bitpat) == 0U) {
		return(false);
	}

	sil_wrw_mem((uint32_t *)(TADR_PLIC_BASE+off),
		(sil_rew_mem((uint32_t *)(TADR_PLIC_BASE+off)) | (1 << (intno % 32))));
	return(true);
}

#define t_enable_int(intno)		x_enable_int(intno)
#define i_enable_int(intno)		x_enable_int(intno)

/*
 *  割込み要求のクリア
 */
Inline void
x_clear_int(INTNO intno)
{
}

#define t_clear_int(intno)		x_clear_int(intno)
#define i_clear_int(intno)		x_clear_int(intno)

/*
 *  割込み要求のチェック
 */
Inline bool_t
x_probe_int(INTNO intno)
{
	unsigned long hart_id = read_csr(mhartid);
	uint32_t off = TOFF_PLIC_ENABLE + (hart_id * NUM_PLIC_ENABLE) + (intno >> 3);

	return((sil_reb_mem((uint8_t *)(TADR_PLIC_BASE+off)) & (1 << (intno & 7))) != 0);
}

#define t_probe_int(intno)		x_probe_int(intno)
#define i_probe_int(intno)		x_probe_int(intno)

/*
 *  割込みハンドラの設定
 *
 *  ベクトル番号inhnoの割込みハンドラの出入口処理の番地をint_entryに設
 *  定する．
 */
Inline void
x_define_inh(INHNO inhno, FP int_entry)
{
}


/*
 *  割込み要求ラインの属性の設定
 *
 *  DVE-68K/40のIRCでは，割込み要求ラインの割込み優先度にNMIを指定する
 *  ことができため，-7を与えるとNMIに設定されることとする（ターゲット定
 *  義の拡張）．
 */
extern void	x_config_int(INTNO intno, ATR intatr, PRI intpri);

/*
 *  割込みハンドラの入口で必要なIRC操作
 *
 *  エッジトリガの場合には，割込み要求をクリアする．エッジトリガかレベ
 *  ルトリガかが設定できる場合も，現在の設定値を見ずにクリアしている．
 *  レベルトリガの場合もクリア処理をして差し支えないが，最適化で消える
 *  ことを期待して，クリアしないこととしている．
 */
Inline void
i_begin_int(INTNO intno)
{
}

/*
 *  割込みハンドラの出口で必要なIRC操作
 *
 *  K210では必要なIRC操作はない．
 */
Inline void
i_end_int(INTNO intno)
{
}

/*
 *  割込みハンドラの出入口処理の生成
 */

/*
 *  割込みハンドラの出入口処理のラベルを作るマクロ
 */
#define INT_ENTRY(inhno, inthdr)	_kernel_##inthdr##_##inhno

/*
 *  LOG_INH_ENTERがマクロ定義されている場合に，CALL_LOG_INH_ENTERを，
 *  inhno_numをパラメータとしてlog_inh_enterを呼び出すアセンブリ言語コー
 *  ドにマクロ定義する．
 */
#ifdef LOG_INH_ENTER

#define CALL_LOG_INH_ENTER(inhno_num) \
"	li a0," #inhno_num "			\n"  /* inhno_numをパラメータに */ \
"	jal _kernel_log_inh_enter		\n"  /* log_inh_enterを呼び出す */

#else /* LOG_INH_ENTER */
#define CALL_LOG_INH_ENTER(inhno_num)
#endif /* LOG_INH_ENTER */

#ifdef LOG_INH_LEAVE

/*
 *  CALL_LOG_INH_LEAVEを，inhno_numをパラメータとしてlog_inh_leaveを呼
 *  び出すアセンブリ言語コードにマクロ定義する．
 */
#define CALL_LOG_INH_LEAVE(inhno_num) \
"	li a0," #inhno_num "			\n"  /* inhno_numをパラメータに */ \
"	jal _kernel_log_inh_leave		\n"  /* log_inh_leaveを呼び出す */

/*
 *  LOG_INH_LEAVEがマクロ定義されている場合の割込みハンドラの出入口処理．
 *  割込みハンドラをサブルーチンコールし，戻ってきたら，トレースログの
 *  取得後，呼び出し先に分岐する．
 */
#define INTHDR_ENTRY(inhno, inhno_num, inthdr) \
extern void _kernel_##inthdr##_##inhno(void); \
asm(".text							\n" \
"_kernel_" #inthdr "_" #inhno ":	\n" \
"	addi sp, sp, -32				\n"	 /* 保存領域を確保 */ \
"	sd ra, 24(sp)					\n"	 /* return addressをセーブ */ \
	CALL_LOG_INH_ENTER(inhno_num) \
"	jal " #inthdr "				\n"  /* 割込みハンドラを呼び出す */ \
	CALL_LOG_INH_LEAVE(inhno_num) \
"	ld ra, 24(sp)					\n"	 /* return addressをリストア */ \
"	addi sp, sp, 32					\n"	 /* 保存領域を開放 */ \
"	ret								\n");/* リターン */


#elif defined(LOG_INH_ENTER)

/*
 *  LOG_INH_LEAVEがマクロ定義されていなくてLOG_INH_ENTERが定義されている
 *  場合の割込みハンドラの出入口処理．log_inh_enterを実行後、
 *  ハンドラを呼び出し、呼び出し先に分岐する．
 */
#define INTHDR_ENTRY(inhno, inhno_num, inthdr) \
extern void _kernel_##inthdr##_##inhno(void); \
asm(".text							\n" \
"_kernel_" #inthdr "_" #inhno ":	\n" \
"	addi sp, sp, -32				\n"	 /* 保存領域を確保 */ \
"	sd ra, 24(sp)					\n"	 /* return addressをセーブ */ \
	CALL_LOG_INH_ENTER(inhno_num) \
"	jal " #inthdr "					\n"	 /* 割込みハンドラへ分岐 */ \
"	ld ra, 24(sp)					\n"	 /* return addressをリストア */ \
"	addi sp, sp, 32					\n"	 /* 保存領域を開放 */ \
"	ret								\n");/* リターン */

#else

/*
 *  LOG_INH_ENTER/LOG_INH_LEAVEがマクロ定義されていない場合、raを保持したまま
 *  ハンドラにジャンプする．
 */
#define INTHDR_ENTRY(inhno, inhno_num, inthdr) \
extern void _kernel_##inthdr##_##inhno(void); \
asm(".text							\n" \
"_kernel_" #inthdr "_" #inhno ":	\n" \
"	j " #inthdr "					\n");	 /* 割込みハンドラへ分岐 */ \

#endif /* LOG_INH_LEAVE */

#endif /* TOPPERS_MACRO_ONLY */

#ifndef TOPPERS_MACRO_ONLY

/*
 *  ターゲットシステム依存の初期化
 */
extern void	target_initialize(void);

/*
 *  ターゲットシステムの終了
 *
 *  システムを終了する時に使う．
 */
extern void	target_exit(void) NoReturn;

/*
 *  イレギュラーなPDIC割込み処理
 */
extern void default_plic_handler(void);

#endif /* TOPPERS_MACRO_ONLY */

/*
 *  微少時間待ちのための定義（本来はSILのターゲット依存部）
 */
#define SIL_DLY_TIM1    1
#define SIL_DLY_TIM2    5

/*
 *  プロセッサ依存モジュール（RISC-V用）
 */
#include "riscv_gcc/prc_config.h"

#endif /* TOPPERS_TARGET_CONFIG_H */
