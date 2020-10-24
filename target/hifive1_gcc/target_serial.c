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
 *  @(#) $Id: target_serial.c 2246 2019-01-12 00:16:51Z roi $
 */

/*
 *		シリアルI/Oデバイス（SIO）ドライバ（HIFIVE1用）
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

/*
 *  シリアルI/Oポート初期化ブロックの定義
 */
typedef struct sio_port_initialization_block {
	uint32_t base;
	INTNO    intno_usart;
	uint32_t iof;
} SIOPINIB;

/*
 *  シリアルI/Oポート管理ブロックの定義
 */
struct sio_port_control_block {
	const SIOPINIB  *p_siopinib;  /* シリアルI/Oポート初期化ブロック */
	intptr_t        exinf;        /* 拡張情報 */
	bool_t          opnflg;       /* オープン済みフラグ */
	int32_t         rxdata;       /* 受信FIFOデータ保存領域 */
};

/*
 * シリアルI/Oポート初期化ブロック
 */
const SIOPINIB siopinib_table[TNUM_SIOP] = {
	{(uint32_t)TADR_UART0_BASE, (INTNO)IRQ_VECTOR_UART0, IOF0_UART0_MASK},
#if TNUM_SIOP >= 2
	{(uint32_t)TADR_UART1_BASE, (INTNO)IRQ_VECTOR_UART1, IOF0_UART1_MASK}
#endif
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
	uint32_t base;

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
	sil_orw_mem((uint32_t *)(TADR_GPIO_BASE+TOFF_GPIO_OUTPUT_VAL), p_siopinib->iof);
	sil_orw_mem((uint32_t *)(TADR_GPIO_BASE+TOFF_GPIO_OUTPUT_EN), p_siopinib->iof);
	sil_andw_mem((uint32_t *)(TADR_GPIO_BASE+TOFF_GPIO_IOF_SEL), p_siopinib->iof);
	sil_orw_mem((uint32_t *)(TADR_GPIO_BASE+TOFF_GPIO_IOF_EN), p_siopinib->iof);

	sil_wrw_mem((uint32_t *)(base+TOFF_UART_DIV), SYS_CLOCK / BPS_SETTING - 1);
	sil_wrw_mem((uint32_t *)(base+TOFF_UART_TXCTRL), UART_TXEN + 0x10000);
	sil_wrw_mem((uint32_t *)(base+TOFF_UART_RXCTRL), UART_RXEN);
	p_siopcb->opnflg = true;

	/*
	 *  シリアルI/O割込みのマスクを解除する．
	 */
	if (!opnflg) {
		ercd = ena_int(p_siopinib->intno_usart);
		assert(ercd == E_OK);
	}
	sil_dly_nse(10000);

sio_opn_exit:;
	return(p_siopcb);
}

/*
 *  シリアルI/Oポートのクローズ
 */
void
sio_cls_por(SIOPCB *p_siopcb)
{
	/*
	 *  シリアルI/O割込みをマスクする．
	 */
	if ((p_siopcb->opnflg)) {
		dis_int(p_siopcb->p_siopinib->intno_usart);
	}
	p_siopcb->opnflg = false;
}

/*
 *  SIOの割込みサービスルーチン
 */

Inline bool_t
sio_putintready(SIOPCB* p_siopcb)
{
	uint32_t ip = sil_rew_mem((uint32_t *)(p_siopcb->p_siopinib->base+TOFF_UART_IP));
	uint32_t ie = sil_rew_mem((uint32_t *)(p_siopcb->p_siopinib->base+TOFF_UART_IE));

	if((ip & UART_IP_TXWM) != 0 && (ie & UART_IP_TXWM) != 0){
		return 1;
	}
	return 0;
}

Inline bool_t
sio_getintready(SIOPCB* p_siopcb)
{
	uint32_t ip = sil_rew_mem((uint32_t *)(p_siopcb->p_siopinib->base+TOFF_UART_IP));

	if((ip & UART_IP_RXWM) != 0){
		p_siopcb->rxdata = sil_rew_mem((uint32_t *)(p_siopcb->p_siopinib->base+TOFF_UART_RXFIFO));
		if(p_siopcb->rxdata < 0)
			return 0;
		else
			return 1;
	}
	else
		return 0;
}

Inline bool_t
sio_putready(SIOPCB* p_siopcb)
{
	uint32_t txfifo = sil_rew_mem((uint32_t *)(p_siopcb->p_siopinib->base+TOFF_UART_TXFIFO));

	if((txfifo & UART_TXFIFO_FULL) == 0){
		return 1;
	}
	return 0;
}

void
sio_isr(intptr_t exinf)
{
	SIOPCB          *p_siopcb;

	p_siopcb = get_siopcb(exinf);

	if (sio_getintready(p_siopcb)) {
		sio_irdy_rcv(p_siopcb->exinf);
	}
	if (sio_putintready(p_siopcb)) {
		sio_irdy_snd(p_siopcb->exinf);
	}
}

/*
 *  シリアルI/Oポートへの文字送信
 */
bool_t
sio_snd_chr(SIOPCB *p_siopcb, char c)
{
#ifndef DEFAULT_CLOCK
	if(sio_putready(p_siopcb)){
		sil_wrw_mem((uint32_t *)(p_siopcb->p_siopinib->base+TOFF_UART_TXFIFO), (uint32_t)c);
		return true;
	}
	return false;
#else
	while(sio_putready(p_siopcb) == 0);
	sil_wrw_mem((uint32_t *)(p_siopcb->p_siopinib->base+TOFF_UART_TXFIFO), (uint32_t)c);
	return true;
#endif
}

/*
 *  シリアルI/Oポートからの文字受信
 */
int_t
sio_rcv_chr(SIOPCB *p_siopcb)
{
	int_t c = -1;

	if(p_siopcb->rxdata >= 0){
		c = p_siopcb->rxdata & 0xFF;
		p_siopcb->rxdata = -1;
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
		sil_orw_mem((uint32_t *)(p_siopcb->p_siopinib->base+TOFF_UART_IE), UART_IP_TXWM);
		break;
	case SIO_RDY_RCV:
		sil_orw_mem((uint32_t *)(p_siopcb->p_siopinib->base+TOFF_UART_IE), UART_IP_RXWM);
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
		sil_andw_mem((uint32_t *)(p_siopcb->p_siopinib->base+TOFF_UART_IE), UART_IP_TXWM);
		break;
	case SIO_RDY_RCV:
		sil_andw_mem((uint32_t *)(p_siopcb->p_siopinib->base+TOFF_UART_IE), UART_IP_RXWM);
		break;
	}
}

/*
 *  1文字出力（ポーリングでの出力）
 */
void sio_pol_snd_chr(int8_t c, ID siopid)
{
	uint32_t base = siopinib_table[INDEX_PORT(siopid)].base;

	sil_wrw_mem((uint32_t *)(base+TOFF_UART_TXFIFO), (uint32_t)c);
	while(0 != (sil_rew_mem((uint32_t *)(base+TOFF_UART_TXFIFO)) & UART_TXFIFO_FULL));

	/*
	 *  出力が完全に終わるまで待つ
	 */
	volatile int n = SystemFrequency/BPS_SETTING;
	while(n--);
}

/*
 *  ターゲットのシリアル初期化
 */
void target_uart_init(ID siopid)
{
	const SIOPINIB  *p_siopinib;
	uint32_t base;

	p_siopinib = &siopinib_table[INDEX_PORT(siopid)];
	base = p_siopinib->base;

	/*
	 *  ハードウェアの初期化
	 */
	sil_orw_mem((uint32_t *)(TADR_GPIO_BASE+TOFF_GPIO_OUTPUT_VAL), p_siopinib->iof);
	sil_orw_mem((uint32_t *)(TADR_GPIO_BASE+TOFF_GPIO_OUTPUT_EN), p_siopinib->iof);
	sil_andw_mem((uint32_t *)(TADR_GPIO_BASE+TOFF_GPIO_IOF_SEL), p_siopinib->iof);
	sil_orw_mem((uint32_t *)(TADR_GPIO_BASE+TOFF_GPIO_IOF_EN), p_siopinib->iof);

	sil_wrw_mem((uint32_t *)(base+TOFF_UART_DIV), SYS_CLOCK / BPS_SETTING - 1);
	sil_wrw_mem((uint32_t *)(base+TOFF_UART_TXCTRL), UART_TXEN);
	sil_wrw_mem((uint32_t *)(base+TOFF_UART_RXCTRL), UART_RXEN);
	sil_dly_nse(10000);
}
