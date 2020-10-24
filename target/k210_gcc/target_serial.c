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
 *  @(#) $Id: target_serial.c 2246 2019-09-24 21:24:50Z roi $
 */

/*
 *		シリアルI/Oデバイス（SIO）ドライバ（K210用）
 */

#include <kernel.h>
#include <t_syslog.h>
#include "target_stddef.h"
#include "target_serial.h"
#include "target_syssvc.h"

/*
 *  SIL関数のマクロ定義
 */
#define sil_orw_mem(a, b)		sil_wrw_mem((a), sil_rew_mem(a) | (b))
#define sil_andw_mem(a, b)		sil_wrw_mem((a), sil_rew_mem(a) & ~(b))

/*
 * レジスタ設定値
 */
#define INDEX_PORT(x)	((x) - 1)
#define GET_SIOPCB(x)	(&siopcb_table[INDEX_PORT(x)])

#define __UART_BRATE_CONST  16

#ifndef COM0
#define COM0                0
#endif

/*
 *  ビット長パラメータ
 */
#define UART_WordLength_5B  0x00000000
#define UART_WordLength_6B  0x00000001
#define UART_WordLength_7B  0x00000002
#define UART_WordLength_8b  0x00000003

/*
 *  ストップビットパラメータ
 */ 
#define UART_StopBits_1     0x00000000
#define UART_StopBits_1_5   UART_LCR_STB

/*
 *  パリティパラメータ
 */
#define UART_Parity_No      0x00000000
#define UART_Parity_Odd     UART_LCR_PARITY
#define UART_Parity_Even    (UART_LCR_PARITY | UART_LCR_PEVEN)

/*
 *  送信FIFO
 */
#define UART_SEND_FIFO0     0
#define UART_SEND_FIFO2     1
#define UART_SEND_FIFO4     2
#define UART_SEND_FIFO8     3

/*
 *  受信FIFO
 */
#define UART_RECEIVE_FIFO1  0
#define UART_RECEIVE_FIFO4  1
#define UART_RECEIVE_FIFO8  2
#define UART_RECEIVE_FIFO14 3

/*
 *  シリアルI/Oポート初期化ブロックの定義
 */
typedef struct sio_port_initialization_block {
	uint64_t base;
	INTNO    intno_usart;
	uint32_t clk;
	uint8_t  txfunc;
	uint8_t  rxfunc;
	uint8_t  com;
} SIOPINIB;

/*
 *  シリアルI/Oポート管理ブロックの定義
 */
struct sio_port_control_block {
	const SIOPINIB  *p_siopinib;  /* シリアルI/Oポート初期化ブロック */
	intptr_t        exinf;        /* 拡張情報 */
	bool_t          opnflg;       /* オープン済みフラグ */
};

/*
 * シリアルI/Oポート初期化ブロック
 */
const SIOPINIB siopinib_table[TNUM_SIOP] = {
	{(uint32_t)TADR_UART1_BASE, (INTNO)IRQ_VECTOR_UART1, SYSCTL_CLK_EN_PERI_UART1_CLK_EN, FUNC_UART1_TX, FUNC_UART1_RX, COM0},
#if TNUM_SIOP >= 2
	{(uint32_t)TADR_UART3_BASE, (INTNO)IRQ_VECTOR_UART3, SYSCTL_CLK_EN_PERI_UART3_CLK_EN, FUNC_UART3_TX, FUNC_UART3_RX, COM0^1}
#endif
};

/*
 *  FPIOA番号テーブル
 */
static uint8_t uartpin[2][2] = {
	{5, 4},		/* com0 tx, rx */
	{6, 7},		/* com1 tx, rx */
};

/*
 *  シリアルI/Oポート管理ブロックのエリア
 */
SIOPCB	siopcb_table[TNUM_SIOP];

/*
 *  シリアルI/OポートIDから管理ブロックを取り出すためのマクロ
 */
#define INDEX_SIOP(siopid)	((uint_t)((siopid) - 1))
#define get_siopcb(siopid)	(&(siopcb_table[INDEX_SIOP(siopid)]))

extern uint32_t get_pll_clock(uint8_t no);
extern ER fpioa_set_function(int number, uint8_t function);

/*
 *  PLL0クロックを取得
 */
static uint32_t
get_clock_aclk(void)
{
	uint32_t clk_sel0 = sil_rew_mem((uint32_t *)(TADR_SYSCTL_BASE+TOFF_CLK_SEL0));
	uint32_t select = clk_sel0 & SYSCTL_CLK_SEL0_ACLK_SEL;
	uint32_t source = 0;

	if(select == 0)
		source = SYSCTRL_CLOCK_FREQ_IN0;
	else if(select == 1)
		source = get_pll_clock(0) / (2UL << ((clk_sel0 & SYSCTL_CLK_SEL0_ACLK_SDIVISER)>>1));
	return source;
}


void put_hex(char a, int val)
{
	int i, j;
	target_fput_log(a);
	target_fput_log(' ');
	for(i = 28 ; i >= 0 ; i-= 4){
		j = (val >> i) & 0xf;;
		if(j > 9)
			j += ('A'-10);
		else
			j += '0';
		target_fput_log(j);
	}
	target_fput_log('\n');
}

/*
 *  SIOドライバの初期化
 */
void
sio_initialize(intptr_t exinf)
{
	SIOPCB	*p_siopcb;
	uint_t	i;

	/*
	 *  シリアルI/Oポート管理ブロックの初期化
	 */
	for (p_siopcb = siopcb_table, i = 0; i < TNUM_SIOP; p_siopcb++, i++) {
		p_siopcb->p_siopinib = &(siopinib_table[i]);
		p_siopcb->opnflg = false;
	}
}


/*
 *  シリアルI/Oポートのオープン
 */
SIOPCB *
sio_opn_por(ID siopid, intptr_t exinf)
{
	SIOPCB          *p_siopcb;
	const SIOPINIB  *p_siopinib;
	bool_t   opnflg;
	ER       ercd;
	unsigned long base;
	uint32_t divisor, threshold, tmp;
	uint8_t  dlh, dll, dlf;

	p_siopcb = get_siopcb(siopid);
	p_siopinib = p_siopcb->p_siopinib;

	/*
	 *  オープンしたポートがあるかをopnflgに読んでおく．
	 */
	opnflg = p_siopcb->opnflg;

	p_siopcb->exinf = exinf;
	base = p_siopinib->base;
	if(base == 0)				/* no uart port */
		goto sio_opn_exit;

	/*
	 *  ハードウェアの初期化
	 */
	sil_orw_mem((uint32_t *)(TADR_SYSCTL_BASE+TOFF_SYSCTL_CLK_EN_PERI), p_siopinib->clk);

	sil_wrw_mem((uint32_t *)(base+TOFF_UART_IER), 0x00000000);
	sil_dly_nse(10000);

	threshold = (sil_rew_mem((uint32_t *)(TADR_SYSCTL_BASE+TOFF_CLK_SEL0)) & SYSCTL_CLK_SEL0_APB0_CLK_SEL) >> 3;
    divisor = (get_clock_aclk() / (threshold+1)) / BPS_SETTING;
    dlh = divisor >> 12;
    dll = (divisor - (dlh << 12)) / __UART_BRATE_CONST;
    dlf = divisor - (dlh << 12) - dll * __UART_BRATE_CONST;

    /* Set UART registers */
	sil_orw_mem((uint32_t *)(base+TOFF_UART_LCR), UART_LCR_DMD);
	sil_wrw_mem((uint32_t *)(base+TOFF_UART_DLH), dlh);
	sil_wrw_mem((uint32_t *)(base+TOFF_UART_DLL), dll);
	sil_wrw_mem((uint32_t *)(base+TOFF_UART_DLF), dlf);
	sil_wrw_mem((uint32_t *)(base+TOFF_UART_LCR), 0x00);
	sil_wrw_mem((uint32_t *)(base+TOFF_UART_LCR), (UART_WordLength_8b | UART_StopBits_1 | UART_Parity_No));
	sil_andw_mem((uint32_t *)(base+TOFF_UART_LCR), UART_LCR_DMD);
	sil_orw_mem((uint32_t *)(base+TOFF_UART_IER), UART_IER_THRE);
	sil_wrw_mem((uint32_t *)(base+TOFF_UART_FCR),
			(UART_RECEIVE_FIFO1 << 6 | UART_SEND_FIFO8 << 4 | 0x1 << 3 | 0x1));

	fpioa_set_function(uartpin[p_siopinib->com][1], p_siopinib->rxfunc);
	fpioa_set_function(uartpin[p_siopinib->com][0], p_siopinib->txfunc);
	sil_orw_mem((uint32_t *)(base+TOFF_UART_IER), UART_IER_RIE);
	tmp = sil_rew_mem((uint32_t *)(p_siopcb->p_siopinib->base+TOFF_UART_RBR));
	p_siopcb->opnflg = true;
	(void)(tmp);

	/*
	 *  シリアルI/O割込みのマスクを解除する．
	 */
	if (!opnflg) {
		ercd = ena_int(p_siopinib->intno_usart);
		assert(ercd == E_OK);
	}
	sil_dly_nse(20000);

sio_opn_exit:;
	return(p_siopcb);
}

/*
 *  シリアルI/Oポートのクローズ
 */
void
sio_cls_por(SIOPCB *p_siopcb)
{
	const SIOPINIB  *p_siopinib;

	p_siopinib = p_siopcb->p_siopinib;
	/*
	 *  シリアルI/O割込みをマスクする．
	 */
	if ((p_siopcb->opnflg)) {
		dis_int(p_siopinib->intno_usart);
	}

	/*
	 *  シリアル停止
	 */
	sil_wrw_mem((uint32_t *)(p_siopinib->base+TOFF_UART_IER), 0x00000000);
	sil_andw_mem((uint32_t *)(TADR_SYSCTL_BASE+TOFF_SYSCTL_CLK_EN_PERI), p_siopinib->clk);
	p_siopcb->opnflg = false;
}

/*
 *  SIOの割込みサービスルーチン
 */
void
sio_isr(intptr_t exinf)
{
	SIOPCB *p_siopcb = get_siopcb(exinf);
	unsigned long base = p_siopcb->p_siopinib->base;
	uint32_t ip = sil_rew_mem((uint32_t *)(base+TOFF_UART_IIR)) & 0x0F;
	uint32_t tmp;

	if(ip == UART_IIR_RECEIVE || ip == UART_IIR_CTIMEOUT){
		sio_irdy_rcv(p_siopcb->exinf);
	}
	else if(ip == UART_IIR_SEND){
		sio_irdy_snd(p_siopcb->exinf);
	}
	else{
		tmp = sil_rew_mem((uint32_t *)(base+TOFF_UART_LSR));
		tmp = sil_rew_mem((uint32_t *)(base+TOFF_UART_USR));
		tmp = sil_rew_mem((uint32_t *)(base+TOFF_UART_MSR));
	}
	(void)(tmp);
}

/*
 *  シリアルI/Oポートへの文字送信
 */
Inline bool_t
sio_putready(SIOPCB* p_siopcb)
{
	uint32_t lsr = sil_rew_mem((uint32_t *)(p_siopcb->p_siopinib->base+TOFF_UART_LSR));

	if((lsr & UART_LSR_TFL) == 0){
		return 1;
	}
	return 0;
}

bool_t
sio_snd_chr(SIOPCB *p_siopcb, char c)
{
	if(sio_putready(p_siopcb)){
		sil_wrw_mem((uint32_t *)(p_siopcb->p_siopinib->base+TOFF_UART_THR), (uint32_t)c);
		return true;
	}
	return false;
}

/*
 *  シリアルI/Oポートからの文字受信
 */
int_t
sio_rcv_chr(SIOPCB *p_siopcb)
{
	int_t c = -1;

	if((sil_rew_mem((uint32_t *)(p_siopcb->p_siopinib->base+TOFF_UART_LSR)) & UART_LSR_RFL) != 0){
		c = sil_rew_mem((uint32_t *)(p_siopcb->p_siopinib->base+TOFF_UART_RBR)) & 0xFF;
	}
	return c;
}

/*
 *  シリアルI/Oポートからのコールバックの許可
 */
void
sio_ena_cbr(SIOPCB *p_siopcb, uint_t cbrtn)
{
	switch (cbrtn) {
	case SIO_RDY_SND:
		sil_orw_mem((uint32_t *)(p_siopcb->p_siopinib->base+TOFF_UART_IER), UART_IER_TIE);
		break;
	case SIO_RDY_RCV:
		sil_orw_mem((uint32_t *)(p_siopcb->p_siopinib->base+TOFF_UART_IER), UART_IER_RIE);
		break;
	}
}

/*
 *  シリアルI/Oポートからのコールバックの禁止
 */
void
sio_dis_cbr(SIOPCB *p_siopcb, uint_t cbrtn)
{
	switch (cbrtn) {
	case SIO_RDY_SND:
		sil_andw_mem((uint32_t *)(p_siopcb->p_siopinib->base+TOFF_UART_IER), UART_IER_TIE);
		break;
	case SIO_RDY_RCV:
		sil_andw_mem((uint32_t *)(p_siopcb->p_siopinib->base+TOFF_UART_IER), UART_IER_RIE);
		break;
	}
}

/*
 *  1文字出力（ポーリングでの出力）
 */
void sio_pol_snd_chr(int8_t c, ID siopid)
{
	unsigned long base = siopinib_table[INDEX_PORT(siopid)].base;

	sil_wrw_mem((uint32_t *)(base+TOFF_UART_THR), (uint32_t)c);
	while(0 != (sil_rew_mem((uint32_t *)(base+TOFF_UART_LSR)) & UART_LSR_TFL));

	/*
	 *  出力が完全に終わるまで待つ
	 */
	volatile int n = SYS_CLOCK/BPS_SETTING;
	while(n--);
}

/*
 *  ターゲットのシリアル初期化
 */
void target_uart_init(ID siopid)
{
	const SIOPINIB  *p_siopinib;
	unsigned long base;
	uint32_t divisor, threshold;
	uint8_t  dlh, dll, dlf;

	p_siopinib = &siopinib_table[INDEX_PORT(siopid)];
	base = p_siopinib->base;

	/*
	 *  ハードウェアの初期化
	 */
	sil_orw_mem((uint32_t *)(TADR_SYSCTL_BASE+TOFF_SYSCTL_CLK_EN_PERI), p_siopinib->clk);

	threshold = (sil_rew_mem((uint32_t *)(TADR_SYSCTL_BASE+TOFF_CLK_SEL0)) & SYSCTL_CLK_SEL0_APB0_CLK_SEL) >> 3;
    divisor = (get_clock_aclk() / (threshold+1)) / BPS_SETTING;
    dlh = divisor >> 12;
    dll = (divisor - (dlh << 12)) / __UART_BRATE_CONST;
    dlf = divisor - (dlh << 12) - dll * __UART_BRATE_CONST;

    /* Set UART registers */
	sil_orw_mem((uint32_t *)(base+TOFF_UART_LCR), UART_LCR_DMD);
	sil_wrw_mem((uint32_t *)(base+TOFF_UART_DLH), dlh);
	sil_wrw_mem((uint32_t *)(base+TOFF_UART_DLL), dll);
	sil_wrw_mem((uint32_t *)(base+TOFF_UART_DLF), dlf);
	sil_wrw_mem((uint32_t *)(base+TOFF_UART_LCR), 0x00);
	sil_wrw_mem((uint32_t *)(base+TOFF_UART_LCR), (UART_WordLength_8b | UART_StopBits_1 | UART_Parity_No));
	sil_andw_mem((uint32_t *)(base+TOFF_UART_LCR), UART_LCR_DMD);
	sil_orw_mem((uint32_t *)(base+TOFF_UART_IER), UART_IER_THRE);
	sil_wrw_mem((uint32_t *)(base+TOFF_UART_FCR),
			(UART_RECEIVE_FIFO1 << 6 | UART_SEND_FIFO8 << 4 | 0x1 << 3 | 0x1));

	fpioa_set_function(uartpin[p_siopinib->com][1], p_siopinib->rxfunc);
	fpioa_set_function(uartpin[p_siopinib->com][0], p_siopinib->txfunc);
	sil_dly_nse(10000);
}
