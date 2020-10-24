/*
 *  TOPPERS/ASP Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      Advanced Standard Profile Kernel
 * 
 *  Copyright (C) 2008-2011 by Embedded and Real-Time Systems Laboratory
 *              Graduate School of Information Science, Nagoya Univ., JAPAN
 *  Copyright (C) 2015      by 3rd Designing Center
 *              Imageing System Development Division RICOH COMPANY, LTD.
 *  Copyright (C) 2017-2019 by TOPPERS PROJECT Educational Working Group.
 * 
 *  �嵭����Ԥϡ��ʲ���(1)��(4)�ξ������������˸¤ꡤ�ܥ��եȥ���
 *  �����ܥ��եȥ���������Ѥ�����Τ�ޤࡥ�ʲ�Ʊ���ˤ���ѡ�ʣ������
 *  �ѡ������ۡʰʲ������ѤȸƤ֡ˤ��뤳�Ȥ�̵���ǵ������롥
 *  (1) �ܥ��եȥ������򥽡��������ɤη������Ѥ�����ˤϡ��嵭������
 *      ��ɽ�����������Ѿ�浪��Ӳ�����̵�ݾڵ��꤬�����Τޤޤη��ǥ���
 *      ����������˴ޤޤ�Ƥ��뤳�ȡ�
 *  (2) �ܥ��եȥ������򡤥饤�֥������ʤɡ�¾�Υ��եȥ�������ȯ�˻�
 *      �ѤǤ�����Ǻ����ۤ�����ˤϡ������ۤ�ȼ���ɥ�����ȡ�����
 *      �ԥޥ˥奢��ʤɡˤˡ��嵭�����ɽ�����������Ѿ�浪��Ӳ���
 *      ��̵�ݾڵ����Ǻܤ��뤳�ȡ�
 *  (3) �ܥ��եȥ������򡤵�����Ȥ߹���ʤɡ�¾�Υ��եȥ�������ȯ�˻�
 *      �ѤǤ��ʤ����Ǻ����ۤ�����ˤϡ����Τ����줫�ξ�����������
 *      �ȡ�
 *    (a) �����ۤ�ȼ���ɥ�����ȡ����Ѽԥޥ˥奢��ʤɡˤˡ��嵭����
 *        �ɽ�����������Ѿ�浪��Ӳ�����̵�ݾڵ����Ǻܤ��뤳�ȡ�
 *    (b) �����ۤη��֤��̤�������ˡ�ˤ�äơ�TOPPERS�ץ������Ȥ�
 *        ��𤹤뤳�ȡ�
 *  (4) �ܥ��եȥ����������Ѥˤ��ľ��Ū�ޤ��ϴ���Ū�������뤤���ʤ�»
 *      ������⡤�嵭����Ԥ����TOPPERS�ץ������Ȥ����դ��뤳�ȡ�
 *      �ޤ����ܥ��եȥ������Υ桼���ޤ��ϥ���ɥ桼������Τ����ʤ���
 *      ͳ�˴�Ť����ᤫ��⡤�嵭����Ԥ����TOPPERS�ץ������Ȥ�
 *      ���դ��뤳�ȡ�
 * 
 *  �ܥ��եȥ������ϡ�̵�ݾڤ��󶡤���Ƥ����ΤǤ��롥�嵭����Ԥ�
 *  ���TOPPERS�ץ������Ȥϡ��ܥ��եȥ������˴ؤ��ơ�����λ�����Ū
 *  ���Ф���Ŭ������ޤ�ơ������ʤ��ݾڤ�Ԥ�ʤ����ޤ����ܥ��եȥ���
 *  �������Ѥˤ��ľ��Ū�ޤ��ϴ���Ū�������������ʤ�»���˴ؤ��Ƥ⡤��
 *  ����Ǥ�����ʤ���
 * 
 *  @(#) $Id: target_inithook.c 699 2019-09-30 17:44:10Z roi $
 */

/* Copyright 2018 Canaan Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <string.h>
#include "kendryte-k210.h"
#include "target_syssvc.h"

/*
 *  SIL�ؿ��Υޥ������
 */
#define sil_orw_mem(a, b)		sil_wrw_mem((a), sil_rew_mem(a) | (b))
#define sil_andw_mem(a, b)		sil_wrw_mem((a), sil_rew_mem(a) & ~(b))
#define sil_modw_mem(a, b, c)	sil_wrw_mem((a), (sil_rew_mem(a) & (~b)) | (c))

/*
 *  PLL���
 */
#define SYSCTL_PLL0             0
#define SYSCTL_PLL1             1
#define SYSCTL_PLL2             2

/*
 *  ������ץ�����K210�ѡ�
 */
#define FPIOA_TIE_EN            0x01000000
#define FPIOA_TIE_VAL           0x02000000


static const uint32_t function_config[FUNC_MAX] = {
	(0x00900000+FUNC_JTAG_TCLK),
	(0x00900000+FUNC_JTAG_TDI),
	(0x00900000+FUNC_JTAG_TMS),
	(0x00001f00+FUNC_JTAG_TDO),
	(0x00b03f00+FUNC_SPI0_D0),
	(0x00b03f00+FUNC_SPI0_D1),
	(0x00b03f00+FUNC_SPI0_D2),
	(0x00b03f00+FUNC_SPI0_D3),
	(0x00b03f00+FUNC_SPI0_D4),
	(0x00b03f00+FUNC_SPI0_D5),
	(0x00b03f00+FUNC_SPI0_D6),
	(0x00b03f00+FUNC_SPI0_D7),
	(0x00001f00+FUNC_SPI0_SS0),
	(0x00001f00+FUNC_SPI0_SS1),
	(0x00001f00+FUNC_SPI0_SS2),
	(0x00001f00+FUNC_SPI0_SS3),
	(0x03900000+FUNC_SPI0_ARB),
	(0x00001f00+FUNC_SPI0_SCLK),
	(0x00900000+FUNC_UARTHS_RX),
	(0x00001f00+FUNC_UARTHS_TX),
	(0x00900000+FUNC_RESV6),
	(0x00900000+FUNC_RESV7),
	(0x00001f00+FUNC_CLK_SPI1),
	(0x00001f00+FUNC_CLK_I2C1),
	(0x00901f00+FUNC_GPIOHS0),
	(0x00901f00+FUNC_GPIOHS1),
	(0x00901f00+FUNC_GPIOHS2),
	(0x00901f00+FUNC_GPIOHS3),
	(0x00901f00+FUNC_GPIOHS4),
	(0x00901f00+FUNC_GPIOHS5),
	(0x00901f00+FUNC_GPIOHS6),
	(0x00901f00+FUNC_GPIOHS7),

	(0x00901f00+FUNC_GPIOHS8),
	(0x00901f00+FUNC_GPIOHS9),
	(0x00901f00+FUNC_GPIOHS10),
	(0x00901f00+FUNC_GPIOHS11),
	(0x00901f00+FUNC_GPIOHS12),
	(0x00901f00+FUNC_GPIOHS13),
	(0x00901f00+FUNC_GPIOHS14),
	(0x00901f00+FUNC_GPIOHS15),
	(0x00901f00+FUNC_GPIOHS16),
	(0x00901f00+FUNC_GPIOHS17),
	(0x00901f00+FUNC_GPIOHS18),
	(0x00901f00+FUNC_GPIOHS19),
	(0x00901f00+FUNC_GPIOHS20),
	(0x00901f00+FUNC_GPIOHS21),
	(0x00901f00+FUNC_GPIOHS22),
	(0x00901f00+FUNC_GPIOHS23),
	(0x00901f00+FUNC_GPIOHS24),
	(0x00901f00+FUNC_GPIOHS25),
	(0x00901f00+FUNC_GPIOHS26),
	(0x00901f00+FUNC_GPIOHS27),
	(0x00901f00+FUNC_GPIOHS28),
	(0x00901f00+FUNC_GPIOHS29),
	(0x00901f00+FUNC_GPIOHS30),
	(0x00901f00+FUNC_GPIOHS31),
	(0x00901f00+FUNC_GPIO0),
	(0x00901f00+FUNC_GPIO1),
	(0x00901f00+FUNC_GPIO2),
	(0x00901f00+FUNC_GPIO3),
	(0x00901f00+FUNC_GPIO4),
	(0x00901f00+FUNC_GPIO5),
	(0x00901f00+FUNC_GPIO6),
	(0x00901f00+FUNC_GPIO7),

	(0x00900000+FUNC_UART1_RX),
	(0x00001f00+FUNC_UART1_TX),
	(0x00900000+FUNC_UART2_RX),
	(0x00001f00+FUNC_UART2_TX),
	(0x00900000+FUNC_UART3_RX),
	(0x00001f00+FUNC_UART3_TX),
	(0x00b03f00+FUNC_SPI1_D0),
	(0x00b03f00+FUNC_SPI1_D1),
	(0x00b03f00+FUNC_SPI1_D2),
	(0x00b03f00+FUNC_SPI1_D3),
	(0x00b03f00+FUNC_SPI1_D4),
	(0x00b03f00+FUNC_SPI1_D5),
	(0x00b03f00+FUNC_SPI1_D6),
	(0x00b03f00+FUNC_SPI1_D7),
	(0x00001f00+FUNC_SPI1_SS0),
	(0x00001f00+FUNC_SPI1_SS1),
	(0x00001f00+FUNC_SPI1_SS2),
	(0x00001f00+FUNC_SPI1_SS3),
	(0x03900000+FUNC_SPI1_ARB),
	(0x00001f00+FUNC_SPI1_SCLK),
	(0x00b03f00+FUNC_SPI_SLAVE_D0),
	(0x00900000+FUNC_SPI_SLAVE_SS),
	(0x00900000+FUNC_SPI_SLAVE_SCLK),
	(0x00001f00+FUNC_I2S0_MCLK),
	(0x00001f00+FUNC_I2S0_SCLK),
	(0x00001f00+FUNC_I2S0_WS),
	(0x00900000+FUNC_I2S0_IN_D0),
	(0x00900000+FUNC_I2S0_IN_D1),
	(0x00900000+FUNC_I2S0_IN_D2),
	(0x00900000+FUNC_I2S0_IN_D3),
	(0x00001f00+FUNC_I2S0_OUT_D0),
	(0x00001f00+FUNC_I2S0_OUT_D1),

	(0x00001f00+FUNC_I2S0_OUT_D2),
	(0x00001f00+FUNC_I2S0_OUT_D3),
	(0x00001f00+FUNC_I2S1_MCLK),
	(0x00001f00+FUNC_I2S1_SCLK),
	(0x00001f00+FUNC_I2S1_WS),
	(0x00900000+FUNC_I2S1_IN_D0),
	(0x00900000+FUNC_I2S1_IN_D1),
	(0x00900000+FUNC_I2S1_IN_D2),
	(0x00900000+FUNC_I2S1_IN_D3),
	(0x00001f00+FUNC_I2S1_OUT_D0),
	(0x00001f00+FUNC_I2S1_OUT_D1),
	(0x00001f00+FUNC_I2S1_OUT_D2),
	(0x00001f00+FUNC_I2S1_OUT_D3),
	(0x00001f00+FUNC_I2S2_MCLK),
	(0x00001f00+FUNC_I2S2_SCLK),
	(0x00001f00+FUNC_I2S2_WS),
	(0x00900000+FUNC_I2S2_IN_D0),
	(0x00900000+FUNC_I2S2_IN_D1),
	(0x00900000+FUNC_I2S2_IN_D2),
	(0x00900000+FUNC_I2S2_IN_D3),
	(0x00001f00+FUNC_I2S2_OUT_D0),
	(0x00001f00+FUNC_I2S2_OUT_D1),
	(0x00001f00+FUNC_I2S2_OUT_D2),
	(0x00001f00+FUNC_I2S2_OUT_D3),
	(0x00000000+FUNC_RESV0),
	(0x00000000+FUNC_RESV1),
	(0x00000000+FUNC_RESV2),
	(0x00000000+FUNC_RESV3),
	(0x00000000+FUNC_RESV4),
	(0x00000000+FUNC_RESV5),
	(0x00991000+FUNC_I2C0_SCLK),
	(0x00991000+FUNC_I2C0_SDA),

	(0x00991000+FUNC_I2C1_SCLK),
	(0x00991000+FUNC_I2C1_SDA),
	(0x00991000+FUNC_I2C2_SCLK),
	(0x00991000+FUNC_I2C2_SDA),
	(0x00001f00+FUNC_CMOS_XCLK),
	(0x00001f00+FUNC_CMOS_RST),
	(0x00001f00+FUNC_CMOS_PWDN),
	(0x00900000+FUNC_CMOS_VSYNC),
	(0x00900000+FUNC_CMOS_HREF),
	(0x00900000+FUNC_CMOS_PCLK),
	(0x00900000+FUNC_CMOS_D0),
	(0x00900000+FUNC_CMOS_D1),
	(0x00900000+FUNC_CMOS_D2),
	(0x00900000+FUNC_CMOS_D3),
	(0x00900000+FUNC_CMOS_D4),
	(0x00900000+FUNC_CMOS_D5),
	(0x00900000+FUNC_CMOS_D6),
	(0x00900000+FUNC_CMOS_D7),
	(0x00993000+FUNC_SCCB_SCLK),
	(0x00993000+FUNC_SCCB_SDA),
	(0x00900000+FUNC_UART1_CTS),
	(0x00900000+FUNC_UART1_DSR),
	(0x00900000+FUNC_UART1_DCD),
	(0x00900000+FUNC_UART1_RI),
	(0x00900000+FUNC_UART1_SIR_IN),
	(0x00001f00+FUNC_UART1_DTR),
	(0x00001f00+FUNC_UART1_RTS),
	(0x00001f00+FUNC_UART1_OUT2),
	(0x00001f00+FUNC_UART1_OUT1),
	(0x00001f00+FUNC_UART1_SIR_OUT),
	(0x00001f00+FUNC_UART1_BAUD),
	(0x00001f00+FUNC_UART1_RE),

	(0x00001f00+FUNC_UART1_DE),
	(0x00001f00+FUNC_UART1_RS485_EN),
	(0x00900000+FUNC_UART2_CTS),
	(0x00900000+FUNC_UART2_DSR),
	(0x00900000+FUNC_UART2_DCD),
	(0x00900000+FUNC_UART2_RI),
	(0x00900000+FUNC_UART2_SIR_IN),
	(0x00001f00+FUNC_UART2_DTR),
	(0x00001f00+FUNC_UART2_RTS),
	(0x00001f00+FUNC_UART2_OUT2),
	(0x00001f00+FUNC_UART2_OUT1),
	(0x00001f00+FUNC_UART2_SIR_OUT),
	(0x00001f00+FUNC_UART2_BAUD),
	(0x00001f00+FUNC_UART2_RE),
	(0x00001f00+FUNC_UART2_DE),
	(0x00001f00+FUNC_UART2_RS485_EN),
	(0x00900000+FUNC_UART3_CTS),
	(0x00900000+FUNC_UART3_DSR),
	(0x00900000+FUNC_UART3_DCD),
	(0x00900000+FUNC_UART3_RI),
	(0x00900000+FUNC_UART3_SIR_IN),
	(0x00001f00+FUNC_UART3_DTR),
	(0x00001f00+FUNC_UART3_RTS),
	(0x00001f00+FUNC_UART3_OUT2),
	(0x00001f00+FUNC_UART3_OUT1),
	(0x00001f00+FUNC_UART3_SIR_OUT),
	(0x00001f00+FUNC_UART3_BAUD),
	(0x00001f00+FUNC_UART3_RE),
	(0x00001f00+FUNC_UART3_DE),
	(0x00001f00+FUNC_UART3_RS485_EN),
	(0x00001f00+FUNC_TIMER0_TOGGLE1),
	(0x00001f00+FUNC_TIMER0_TOGGLE2),

	(0x00001f00+FUNC_TIMER0_TOGGLE3),
	(0x00001f00+FUNC_TIMER0_TOGGLE4),
	(0x00001f00+FUNC_TIMER1_TOGGLE1),
	(0x00001f00+FUNC_TIMER1_TOGGLE2),
	(0x00001f00+FUNC_TIMER1_TOGGLE3),
	(0x00001f00+FUNC_TIMER1_TOGGLE4),
	(0x00001f00+FUNC_TIMER2_TOGGLE1),
	(0x00001f00+FUNC_TIMER2_TOGGLE2),
	(0x00001f00+FUNC_TIMER2_TOGGLE3),
	(0x00001f00+FUNC_TIMER2_TOGGLE4),
	(0x00001f00+FUNC_CLK_SPI2),
	(0x00001f00+FUNC_CLK_I2C2),
	(0x00001f00+FUNC_INTERNAL0),
	(0x00001f00+FUNC_INTERNAL1),
	(0x00001f00+FUNC_INTERNAL2),
	(0x00001f00+FUNC_INTERNAL3),
	(0x00001f00+FUNC_INTERNAL4),
	(0x00001f00+FUNC_INTERNAL5),
	(0x00001f00+FUNC_INTERNAL6),
	(0x00001f00+FUNC_INTERNAL7),
	(0x00001f00+FUNC_INTERNAL8),
	(0x00900000+FUNC_INTERNAL9),
	(0x00900000+FUNC_INTERNAL10),
	(0x00900000+FUNC_INTERNAL11),
	(0x00900000+FUNC_INTERNAL12),
	(0x00910000+FUNC_INTERNAL13),
	(0x00991f00+FUNC_INTERNAL14),
	(0x00900000+FUNC_INTERNAL15),
	(0x00900000+FUNC_INTERNAL16),
	(0x00900000+FUNC_INTERNAL17),
	(0x00000000+FUNC_CONSTANT),
	(0x00900000+FUNC_INTERNAL18),

	(0x00001f00+FUNC_DEBUG0),
	(0x00001f00+FUNC_DEBUG1),
	(0x00001f00+FUNC_DEBUG2),
	(0x00001f00+FUNC_DEBUG3),
	(0x00001f00+FUNC_DEBUG4),
	(0x00001f00+FUNC_DEBUG5),
	(0x00001f00+FUNC_DEBUG6),
	(0x00001f00+FUNC_DEBUG7),
	(0x00001f00+FUNC_DEBUG8),
	(0x00001f00+FUNC_DEBUG9),
	(0x00001f00+FUNC_DEBUG10),
	(0x00001f00+FUNC_DEBUG11),
	(0x00001f00+FUNC_DEBUG12),
	(0x00001f00+FUNC_DEBUG13),
	(0x00001f00+FUNC_DEBUG14),
	(0x00001f00+FUNC_DEBUG15),
	(0x00001f00+FUNC_DEBUG16),
	(0x00001f00+FUNC_DEBUG17),
	(0x00001f00+FUNC_DEBUG18),
	(0x00001f00+FUNC_DEBUG19),
	(0x00001f00+FUNC_DEBUG20),
	(0x00001f00+FUNC_DEBUG21),
	(0x00001f00+FUNC_DEBUG22),
	(0x00001f00+FUNC_DEBUG23),
	(0x00001f00+FUNC_DEBUG24),
	(0x00001f00+FUNC_DEBUG25),
	(0x00001f00+FUNC_DEBUG26),
	(0x00001f00+FUNC_DEBUG27),
	(0x00001f00+FUNC_DEBUG28),
	(0x00001f00+FUNC_DEBUG29),
	(0x00001f00+FUNC_DEBUG30),
	(0x00001f00+FUNC_DEBUG31),
};

static const uint8_t pll_table[3][4] = {
	{1, 62,  2, 62},	/* PLL 0 */
	{1, 46,  4, 46},	/* PLL 1 */
	{1, 26, 15, 26},	/* PLL 0 */
};

/*
 *  FPIOA�����
 */
static ER
fpioa_init(void)
{
    int i = 0;
	uint32_t en[FUNC_MAX / 32];
	uint32_t val[FUNC_MAX / 32];

	/* Enable fpioa clock in system controller */
	sil_orw_mem((uint32_t *)(TADR_SYSCTL_BASE+TOFF_SYSCTL_CLK_EN_CENT), SYSCTL_CLK_EN_CENT_APB0_CLK_EN);
	sil_orw_mem((uint32_t *)(TADR_SYSCTL_BASE+TOFF_SYSCTL_CLK_EN_PERI), SYSCTL_CLK_EN_PERI_FPIOA_CLK_EN);

	/* Initialize tie */
	memset(en, 0, FUNC_MAX/8);
	memset(val, 0, FUNC_MAX/8);

	/* Set tie enable and tie value */
	for(i = 0; i < FUNC_MAX; i++){
		if((function_config[i] & FPIOA_TIE_EN) != 0)
			en[i / 32] |= 1 << (i % 32);
		if((function_config[i] & FPIOA_TIE_VAL) != 0)
			val[i / 32] |= 1 << (i % 32);
	}

	/* Atomic write every 32bit register to fpioa function */
	for(i = 0; i < FUNC_MAX / 32; i++){
		/* Set value before enable */
		sil_wrw_mem((uint32_t *)(TADR_FPIOA_BASE+TOFF_FPIOA_TIE_EN+i*4), en[i]);
		sil_wrw_mem((uint32_t *)(TADR_FPIOA_BASE+TOFF_FPIOA_TIE_VAL+i*4), val[i]);
	}
    return E_OK;
}

/*
 *  FPIOA�ϡ��ɥ���������
 */
static ER
fpioa_set_function_raw(int number, uint8_t function)
{
	uint32_t *p  = (uint32_t *)&function_config[function];
	uint32_t off = TOFF_FPIOA_IO + number * sizeof(uint32_t);

	/* Check parameters */
	if(number < 0 || number >= FPIOA_NUM_IO || function >= FUNC_MAX)
		return E_PAR;
	sil_modw_mem((uint32_t *)(TADR_FPIOA_BASE+off), 0x00FFFFFF, (*p & 0x00FFFFFF));
    return E_OK;
}

/*
 *  FPIOA�˥ե��󥯥��������ꤹ��
 *  param1  number      The IO number
 *  param2  function    The function enum number
 *  return  0-OK
 */
ER
fpioa_set_function(int number, uint8_t function)
{
	uint8_t i = 0;
	/* Check parameters */
	if(number < 0 || number >= FPIOA_NUM_IO || function >= FUNC_MAX)
		return E_PAR;
	if(function == FUNC_RESV0){
		return fpioa_set_function_raw(number, FUNC_RESV0);
	}
	/* Compare all IO */
	for(i = 0 ; i < FPIOA_NUM_IO ; i++){
		if(((sil_rew_mem((uint32_t *)(TADR_FPIOA_BASE+TOFF_FPIOA_IO+i*4)) & FPIOA_CH_SEL) == function) && (i != number))
			fpioa_set_function_raw(i, FUNC_RESV0);
	}
	return fpioa_set_function_raw(number, function);
}

/*
 *  PLL����å�����
 */
uint32_t
get_pll_clock(uint8_t no)
{
	uint32_t pll, freq_in = 0, freq_out = 0;
	uint32_t nr = 0, nf = 0, od = 0;
	uint32_t select = 0;

	switch(no){
	case 0:		/* PLL0 */
		pll     = sil_rew_mem((uint32_t *)(TADR_SYSCTL_BASE+TOFF_SYSCTL_PLL0));
		freq_in = SYSCTRL_CLOCK_FREQ_IN0;
		nr      = (pll & SYSCTL_PLL_CLKR0) + 1;
		nf      = ((pll & SYSCTL_PLL_CLKF0) >> 4) + 1;
		od      = ((pll & SYSCTL_PLL_CLKOD0) >> 10) + 1;
		break;
	case 1:		/* PLL1 */
		pll     = sil_rew_mem((uint32_t *)(TADR_SYSCTL_BASE+TOFF_SYSCTL_PLL1));
		freq_in = SYSCTRL_CLOCK_FREQ_IN0;
		nr      = (pll & SYSCTL_PLL_CLKR1) + 1;
		nf      = ((pll & SYSCTL_PLL_CLKF1) >> 4) + 1;
		od      = ((pll & SYSCTL_PLL_CLKOD1) >> 10) + 1;
		break;
	case 2:		/* PLL2 */
		pll     = sil_rew_mem((uint32_t *)(TADR_SYSCTL_BASE+TOFF_SYSCTL_PLL2));
		select  = (pll & SYSCTL_PLL_CKIN_SEL2) >> 26;
		if(select == 0)
			freq_in = SYSCTRL_CLOCK_FREQ_IN0;
		else if(select == 1)
			freq_in = get_pll_clock(0);
		else if(select == 2)
			freq_in = get_pll_clock(1);
		nr      = (pll & SYSCTL_PLL_CLKR2) + 1;
		nf      = ((pll & SYSCTL_PLL_CLKF2) >> 4) + 1;
		od      = ((pll & SYSCTL_PLL_CLKOD2) >> 10) + 1;
		break;
	default:
		break;
	}
	freq_out = (uint64_t)freq_in * nf / nr / od;
	return freq_out;
}

/*
 *  PLL��å�Ƚ��
 */
static int
pll_is_lock(uint8_t pll)
{
	uint32_t pll_lock = sil_rew_mem((uint32_t *)(TADR_SYSCTL_BASE+TOFF_SYSCTL_PLL_LOCK));
	if(pll == SYSCTL_PLL0)
		return (pll_lock & SYSCTL_PLL_LOCK_LOCK0) == 3;
	else if(pll == SYSCTL_PLL1)
		return (pll_lock >> 8) & 1;
	else if(pll == SYSCTL_PLL2)
		return (pll_lock >> 16) & 1;
	else
	    return 0;
}

/*
 *  PLL����
 */
static uint32_t
pll_set_freq(uint8_t pll, const uint8_t *conf)
{
	unsigned long base = TADR_SYSCTL_BASE;
	uint32_t voff = TOFF_SYSCTL_PLL0;
	uint32_t pll_value;

	switch(pll){
	case SYSCTL_PLL0:
		voff = TOFF_SYSCTL_PLL0;
		break;
	case SYSCTL_PLL1:
		voff = TOFF_SYSCTL_PLL1;
		break;
	case SYSCTL_PLL2:
		voff = TOFF_SYSCTL_PLL2;
		break;
	default:
		return 0;
		break;
    }

    /*
	 *  PLL0����ʤ�С�ACLK��INO���ѹ�
	 */
    if(pll == SYSCTL_PLL0)
		sil_modw_mem((uint32_t *)(base+TOFF_CLK_SEL0), SYSCTL_CLK_SEL0_ACLK_SEL, SYSCTL_CLK_SEL0_SOURCE_IN0);

    /*
	 *  PLL�������
	 */
	sil_andw_mem((uint32_t *)(base+voff), SYSCTL_PLL_OUT_EN0);

    /*
	 *  PLL�ѥ����
	 */
	sil_andw_mem((uint32_t *)(base+voff), SYSCTL_PLL_PWRD0);

    /*
	 *  PLL�����ѹ�
	 */
	pll_value = sil_rew_mem((uint32_t *)(base+TOFF_SYSCTL_PLL0+pll*4));
	if(pll == SYSCTL_PLL2){
		pll_value &= SYSCTL_PLL_CKIN_SEL2;
		pll_value |= SYSCTL_CLK_SEL0_SOURCE_IN0 << 22;
	}
	pll_value &= ~(SYSCTL_PLL_CLKR0 | SYSCTL_PLL_CLKF0 | SYSCTL_PLL_CLKOD0 | SYSCTL_PLL_BWADJ0);
	pll_value |= conf[0] - 1;
	pll_value |= (conf[1] - 1) << 4;
	pll_value |= (conf[2] - 1) << 10;
	pll_value |= (conf[3] - 1) << 14;
	sil_wrw_mem((uint32_t *)(base+TOFF_SYSCTL_PLL0+pll*4), pll_value);

    /*
	 *  PLL�ѥ����
	 */
	sil_orw_mem((uint32_t *)(base+voff), SYSCTL_PLL_PWRD0);
	sil_dly_nse(1000);

    /*
	 *  PLL�ꥻ�å�
	 */
	sil_andw_mem((uint32_t *)(base+voff), SYSCTL_PLL_RESET0);
	sil_orw_mem((uint32_t *)(base+voff), SYSCTL_PLL_RESET0);
	sil_dly_nse(1000);
	sil_andw_mem((uint32_t *)(base+voff), SYSCTL_PLL_RESET0);

    /*
	 *  PLL��å����
	 */
    while (pll_is_lock(pll) == 0){
		sil_orw_mem((uint32_t *)(base+TOFF_SYSCTL_PLL_LOCK), (SYSCTL_PLL_LOCK_SLIP_CLEAR0 << (pll*8)));
	}

    /*
	 *  PLL���ϳ���
	 */
	sil_orw_mem((uint32_t *)(base+voff), SYSCTL_PLL_OUT_EN0);

    /*
	 *  PLL0����ʤ�С�ACLK��PLL0���ѹ�
	 */
    if(pll == SYSCTL_PLL0)
		sil_modw_mem((uint32_t *)(base+TOFF_CLK_SEL0), SYSCTL_CLK_SEL0_ACLK_SEL, SYSCTL_CLK_SEL0_SOURCE_PLL0);

    return get_pll_clock(pll);
}


/*
 *  ���٥�Υ������åȰ�¸�ν����
 *
 *  �������ȥ��åץ⥸�塼�����ǡ�����ν���������˸ƤӽФ���롥
 */
void hardware_init_hook(void)
{
	/*
	 *  PLL����
	 */
	pll_set_freq(SYSCTL_PLL0, &pll_table[SYSCTL_PLL0][0]);	/* 800000000 */
	pll_set_freq(SYSCTL_PLL1, &pll_table[SYSCTL_PLL1][0]);	/* 300000000 */
	pll_set_freq(SYSCTL_PLL2, &pll_table[SYSCTL_PLL2][0]);	/* 45158400 */

	/*
	 *  BANK6,7��1.8V������
	 */
	sil_orw_mem((uint32_t *)(TADR_SYSCTL_BASE+TOFF_SYSCTL_POWER_SEL),
		SYSCTL_POWER_SEL_POWER_MODE_6);
	sil_orw_mem((uint32_t *)(TADR_SYSCTL_BASE+TOFF_SYSCTL_POWER_SEL),
		SYSCTL_POWER_SEL_POWER_MODE_7);
	/* Init FPIOA */
	fpioa_init();
	/*
	 *  SYSCTL���ơ�������ꥻ�å�
	 */
	sil_orw_mem((uint32_t *)(TADR_SYSCTL_BASE+TOFF_SYSCTL_RST_STATUS),
		 SYSCTL_RST_STATUS_RESET_STS_CLR);
}

