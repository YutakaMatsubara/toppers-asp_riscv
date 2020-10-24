/*
 *  TOPPERS Software
 *      Toyohashi Open Platform for Embedded Real-Time Systems
 * 
 *  Copyright (C) 2000-2003 by Embedded and Real-Time Systems Laboratory
 *                              Toyohashi Univ. of Technology, JAPAN
 *  Copyright (C) 2005,2006 by Embedded and Real-Time Systems Laboratory
 *              Graduate School of Information Science, Nagoya Univ., JAPAN
 *  Copyright (C) 2018-2019 by TOPPERS PROJECT Educational Working Group.
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
 *  @(#) $Id: start.S 264 2019-09-21 05:10:21Z roi $
 */

/*
 *  カーネル対応のスタートアップモジュール（RISC-V用）
 */

#define TOPPERS_MACRO_ONLY
#include "encoding.h"

#if defined(__riscv64)
#define LREG                ld
#else
#define LREG                lw
#endif

	.text
	.globl start
start:
	.cfi_startproc
	.cfi_undefined ra
    .option push
    .option norelax
    la gp, __global_pointer$
    .option pop

    csrw mideleg, 0
    csrw medeleg, 0
    csrw mie, 0
    csrw mip, 0
    csrr a0, mhartid
	la a1, _kernel_istksz
    LREG a2, 0(a1)
    sll sp, a2, a0
	la a1, _kernel_istk
	LREG a2, 0(a1)
    add sp, sp, a2
	bnez a0, start_5

	/*
	 *  bssセクションのクリア
	 */
start_1:
	la a0, __bss_start
	la a1, _end
	bgeu a0, a1, start_3
start_2:
	sw zero, (a0)
	addi a0, a0, 4
	bltu a0, a1, start_2

	/*
	 *  dataセクションの初期化（ROM化対応）
	 *
	 *  __idata_startから__idata_endまでを，__data_start以降にコピーす
	 *  る．
	 */
start_3:
	la a0, __idata_start
	la a1, __data_start
	la a2, __idata_end
	bgeu a0, a2, start_5

start_4:
	lw t0, (a0)
	sw t0, (a1)
	addi a0, a0, 4
	addi a1, a1, 4
	bltu a0, a2, start_4

start_5:
#ifndef __riscv_float_abi_soft
	/* Enable FPU */
	li t0, MSTATUS_FS
	csrs mstatus, t0
	csrr t1, mstatus
	and t1, t1, t0
	beqz t1, start_6
	fssr x0

start_6:
#endif

	/*
	 *  カーネルを起動する．
	 */
	j   sta_ker
	.cfi_endproc

