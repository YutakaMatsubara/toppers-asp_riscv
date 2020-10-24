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
 *  上記著作権者は，以下の (1)～(4) の条件か，Free Software Foundation 
 *  によって公表されている GNU General Public License の Version 2 に記
 *  述されている条件を満たす場合に限り，本ソフトウェア（本ソフトウェア
 *  を改変したものを含む．以下同じ）を使用・複製・改変・再配布（以下，
 *  利用と呼ぶ）することを無償で許諾する．
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
 *    (3) 再配布の形態を，別に定める方法によって，TOPPERSプロジェクトに
 *        報告すること．
 *  (4) 本ソフトウェアの利用により直接的または間接的に生じるいかなる損
 *      害からも，上記著作権者およびTOPPERSプロジェクトを免責すること．
 *
 *  本ソフトウェアは，無保証で提供されているものである．上記著作権者お
 *  よびTOPPERSプロジェクトは，本ソフトウェアに関して，その適用可能性も
 *  含めて，いかなる保証も行わない．また，本ソフトウェアの利用により直
 *  接的または間接的に生じたいかなる損害に関しても，その責任を負わない．
 * 
 *  @(#) $Id: kendryte-k210.h 2246 2019-10-10 20:23:15Z roi $
 */

#ifndef _KENDRYTE_K210_H_
#define _KENDRYTE_K210_H_

#include <sil.h>
#include "encoding.h"

#define TMAX_INTNO          66
#define TMAX_PRIORITY       8

/*
 *  割込み優先度設定のための定義
 */
#define TIRQ_NMI           (-8)		/* ノンマスカブル割込み */
#define TIRQ_LEVEL7        (-7)		/* 割込みレベル7 */
#define TIRQ_LEVEL6        (-6)		/* 割込みレベル6 */
#define TIRQ_LEVEL5        (-5)		/* 割込みレベル5 */
#define TIRQ_LEVEL4        (-4)		/* 割込みレベル4 */
#define TIRQ_LEVEL3        (-3)		/* 割込みレベル3 */
#define TIRQ_LEVEL2        (-2)		/* 割込みレベル2 */
#define TIRQ_LEVEL1        (-1)		/* 割込みレベル1 */

/*
 *  MACHINE EXCEPTION NUMBER
 */
#define EXC_INSTRUCTION_ADDRESS_MISALIGNED  0
#define EXC_INSTRUCTION_ADDRESS_FAULT       1
#define EXC_ILLEGAL_INSTRUCTION             2
#define EXC_BREAKPOINT                      3
#define EXC_LOAD_ADDRESS_MISALIGNED         4
#define EXC_LOAD_ADDRESS_FAULT              5
#define EXC_STORE_AMO_ADDRESS_MISALIGNED    6
#define EXC_STORE_AMO_ACCESS_FAUT           7
#define EXC_ENVIRONMENT_CALL_FROM_MMODE     11

/*
 *  MACHINE INTERRUPT NUMBER
 */
#define IRQ_MACHINE_SOFTWARE                3
#define IRQ_MACHIE_TIMER                    7
#define IRQ_MACHINE_EXTERNAL                11

/*
 *  GLOBAL INTERRUPT NUMBER
 */
#define IRQ_VECTOR_RESERVED                 0
#define IRQ_VECTOR_SPI0                     1	/* SPI0 interrupt */
#define IRQ_VECTOR_SPI1                     2	/* SPI1 interrupt */
#define IRQ_VECTOR_SPI_SLAVE                3	/* SPI_SLAVE interrupt */
#define IRQ_VECTOR_SPI3                     4	/* SPI3 interrupt */
#define IRQ_VECTOR_I2S0                     5	/* I2S0 interrupt */
#define IRQ_VECTOR_I2S1                     6	/* I2S1 interrupt */
#define IRQ_VECTOR_I2S2                     7	/* I2S2 interrupt */
#define IRQ_VECTOR_I2C0                     8	/* I2C0 interrupt */
#define IRQ_VECTOR_I2C1                     9	/* I2C1 interrupt */
#define IRQ_VECTOR_I2C2                     10	/* I2C2 interrupt */
#define IRQ_VECTOR_UART1                    11	/* UART1 interrupt */
#define IRQ_VECTOR_UART2                    12	/* UART2 interrupt */
#define IRQ_VECTOR_UART3                    13	/* UART3 interrupt */
#define IRQ_VECTOR_TIMER0A                  14	/* TIMER0 channel 0 or 1 interrupt */
#define IRQ_VECTOR_TIMER0B                  15	/* TIMER0 channel 2 or 3 interrupt */
#define IRQ_VECTOR_TIMER1A                  16	/* TIMER1 channel 0 or 1 interrupt */
#define IRQ_VECTOR_TIMER1B                  17	/* TIMER1 channel 2 or 3 interrupt */
#define IRQ_VECTOR_TIMER2A                  18	/* TIMER2 channel 0 or 1 interrupt */
#define IRQ_VECTOR_TIMER2B                  19	/* TIMER2 channel 2 or 3 interrupt */
#define IRQ_VECTOR_RTC                      20	/* RTC tick and alarm interrupt */
#define IRQ_VECTOR_WDT0                     21	/* Watching dog timer0 interrupt */
#define IRQ_VECTOR_WDT1                     22	/* Watching dog timer1 interrupt */
#define IRQ_VECTOR_APB_GPIO                 23	/* APB GPIO interrupt */
#define IRQ_VECTOR_DVP                      24	/* Digital video port interrupt */
#define IRQ_VECTOR_AI                       25	/* AI accelerator interrupt */
#define IRQ_VECTOR_FFT                      26	/* FFT accelerator interrupt */
#define IRQ_VECTOR_DMA0                     27	/* DMA channel0 interrupt */
#define IRQ_VECTOR_DMA1                     28	/* DMA channel1 interrupt */
#define IRQ_VECTOR_DMA2                     29	/* DMA channel2 interrupt */
#define IRQ_VECTOR_DMA3                     30	/* DMA channel3 interrupt */
#define IRQ_VECTOR_DMA4                     31	/* DMA channel4 interrupt */
#define IRQ_VECTOR_DMA5                     32	/* DMA channel5 interrupt */
#define IRQ_VECTOR_UARTHS                   33	/* Hi-speed UART0 interrupt */
#define IRQ_VECTOR_GPIOHS0                  34	/* Hi-speed GPIO0 interrupt */
#define IRQ_VECTOR_GPIOHS1                  35	/* Hi-speed GPIO1 interrupt */
#define IRQ_VECTOR_GPIOHS2                  36	/* Hi-speed GPIO2 interrupt */
#define IRQ_VECTOR_GPIOHS3                  37	/* Hi-speed GPIO3 interrupt */
#define IRQ_VECTOR_GPIOHS4                  38	/* Hi-speed GPIO4 interrupt */
#define IRQ_VECTOR_GPIOHS5                  39	/* Hi-speed GPIO5 interrupt */
#define IRQ_VECTOR_GPIOHS6                  40	/* Hi-speed GPIO6 interrupt */
#define IRQ_VECTOR_GPIOHS7                  41	/* Hi-speed GPIO7 interrupt */
#define IRQ_VECTOR_GPIOHS8                  42	/* Hi-speed GPIO8 interrupt */
#define IRQ_VECTOR_GPIOHS9                  43	/* Hi-speed GPIO9 interrupt */
#define IRQ_VECTOR_GPIOHS10                 44	/* Hi-speed GPIO10 interrupt */
#define IRQ_VECTOR_GPIOHS11                 45	/* Hi-speed GPIO11 interrupt */
#define IRQ_VECTOR_GPIOHS12                 46	/* Hi-speed GPIO12 interrupt */
#define IRQ_VECTOR_GPIOHS13                 47	/* Hi-speed GPIO13 interrupt */
#define IRQ_VECTOR_GPIOHS14                 48	/* Hi-speed GPIO14 interrupt */
#define IRQ_VECTOR_GPIOHS15                 49	/* Hi-speed GPIO15 interrupt */
#define IRQ_VECTOR_GPIOHS16                 50	/* Hi-speed GPIO16 interrupt */
#define IRQ_VECTOR_GPIOHS17                 51	/* Hi-speed GPIO17 interrupt */
#define IRQ_VECTOR_GPIOHS18                 52	/* Hi-speed GPIO18 interrupt */
#define IRQ_VECTOR_GPIOHS19                 53	/* Hi-speed GPIO19 interrupt */
#define IRQ_VECTOR_GPIOHS20                 54	/* Hi-speed GPIO20 interrupt */
#define IRQ_VECTOR_GPIOHS21                 55	/* Hi-speed GPIO21 interrupt */
#define IRQ_VECTOR_GPIOHS22                 56	/* Hi-speed GPIO22 interrupt */
#define IRQ_VECTOR_GPIOHS23                 57	/* Hi-speed GPIO23 interrupt */
#define IRQ_VECTOR_GPIOHS24                 58	/* Hi-speed GPIO24 interrupt */
#define IRQ_VECTOR_GPIOHS25                 59	/* Hi-speed GPIO25 interrupt */
#define IRQ_VECTOR_GPIOHS26                 60	/* Hi-speed GPIO26 interrupt */
#define IRQ_VECTOR_GPIOHS27                 61	/* Hi-speed GPIO27 interrupt */
#define IRQ_VECTOR_GPIOHS28                 62	/* Hi-speed GPIO28 interrupt */
#define IRQ_VECTOR_GPIOHS29                 63	/* Hi-speed GPIO29 interrupt */
#define IRQ_VECTOR_GPIOHS30                 64	/* Hi-speed GPIO30 interrupt */
#define IRQ_VECTOR_GPIOHS31                 65	/* Hi-speed GPIO31 interrupt */


/*
 *  FPIOAファンクション定義
 */
#define FUNC_JTAG_TCLK                      0	/* JTAG Test Clock */
#define FUNC_JTAG_TDI                       1	/* JTAG Test Data In */
#define FUNC_JTAG_TMS                       2	/* JTAG Test Mode Select */
#define FUNC_JTAG_TDO                       3	/* JTAG Test Data Out */
#define FUNC_SPI0_D0                        4	/* SPI0 Data 0 */
#define FUNC_SPI0_D1                        5	/* SPI0 Data 1 */
#define FUNC_SPI0_D2                        6	/* SPI0 Data 2 */
#define FUNC_SPI0_D3                        7	/* SPI0 Data 3 */
#define FUNC_SPI0_D4                        8	/* SPI0 Data 4 */
#define FUNC_SPI0_D5                        9	/* SPI0 Data 5 */
#define FUNC_SPI0_D6                        10	/* SPI0 Data 6 */
#define FUNC_SPI0_D7                        11	/* SPI0 Data 7 */
#define FUNC_SPI0_SS0                       12	/* SPI0 Chip Select 0 */
#define FUNC_SPI0_SS1                       13	/* SPI0 Chip Select 1 */
#define FUNC_SPI0_SS2                       14	/* SPI0 Chip Select 2 */
#define FUNC_SPI0_SS3                       15	/* SPI0 Chip Select 3 */
#define FUNC_SPI0_ARB                       16	/* SPI0 Arbitration */
#define FUNC_SPI0_SCLK                      17	/* SPI0 Serial Clock */
#define FUNC_UARTHS_RX                      18	/* UART High speed Receiver */
#define FUNC_UARTHS_TX                      19	/* UART High speed Transmitter */
#define FUNC_RESV6                          20	/* Reserved function */
#define FUNC_RESV7                          21	/* Reserved function */
#define FUNC_CLK_SPI1                       22	/* Clock SPI1 */
#define FUNC_CLK_I2C1                       23	/* Clock I2C1 */
#define FUNC_GPIOHS0                        24	/* GPIO High speed 0 */
#define FUNC_GPIOHS1                        25	/* GPIO High speed 1 */
#define FUNC_GPIOHS2                        26	/* GPIO High speed 2 */
#define FUNC_GPIOHS3                        27	/* GPIO High speed 3 */
#define FUNC_GPIOHS4                        28	/* GPIO High speed 4 */
#define FUNC_GPIOHS5                        29	/* GPIO High speed 5 */
#define FUNC_GPIOHS6                        30	/* GPIO High speed 6 */
#define FUNC_GPIOHS7                        31	/* GPIO High speed 7 */
#define FUNC_GPIOHS8                        32	/* GPIO High speed 8 */
#define FUNC_GPIOHS9                        33	/* GPIO High speed 9 */
#define FUNC_GPIOHS10                       34	/* GPIO High speed 10 */
#define FUNC_GPIOHS11                       35	/* GPIO High speed 11 */
#define FUNC_GPIOHS12                       36	/* GPIO High speed 12 */
#define FUNC_GPIOHS13                       37	/* GPIO High speed 13 */
#define FUNC_GPIOHS14                       38	/* GPIO High speed 14 */
#define FUNC_GPIOHS15                       39	/* GPIO High speed 15 */
#define FUNC_GPIOHS16                       40	/* GPIO High speed 16 */
#define FUNC_GPIOHS17                       41	/* GPIO High speed 17 */
#define FUNC_GPIOHS18                       42	/* GPIO High speed 18 */
#define FUNC_GPIOHS19                       43	/* GPIO High speed 19 */
#define FUNC_GPIOHS20                       44	/* GPIO High speed 20 */
#define FUNC_GPIOHS21                       45	/* GPIO High speed 21 */
#define FUNC_GPIOHS22                       46	/* GPIO High speed 22 */
#define FUNC_GPIOHS23                       47	/* GPIO High speed 23 */
#define FUNC_GPIOHS24                       48	/* GPIO High speed 24 */
#define FUNC_GPIOHS25                       49	/* GPIO High speed 25 */
#define FUNC_GPIOHS26                       50	/* GPIO High speed 26 */
#define FUNC_GPIOHS27                       51	/* GPIO High speed 27 */
#define FUNC_GPIOHS28                       52	/* GPIO High speed 28 */
#define FUNC_GPIOHS29                       53	/* GPIO High speed 29 */
#define FUNC_GPIOHS30                       54	/* GPIO High speed 30 */
#define FUNC_GPIOHS31                       55	/* GPIO High speed 31 */
#define FUNC_GPIO0                          56	/* GPIO pin 0 */
#define FUNC_GPIO1                          57	/* GPIO pin 1 */
#define FUNC_GPIO2                          58	/* GPIO pin 2 */
#define FUNC_GPIO3                          59	/* GPIO pin 3 */
#define FUNC_GPIO4                          60	/* GPIO pin 4 */
#define FUNC_GPIO5                          61	/* GPIO pin 5 */
#define FUNC_GPIO6                          62	/* GPIO pin 6 */
#define FUNC_GPIO7                          63	/* GPIO pin 7 */
#define FUNC_UART1_RX                       64	/* UART1 Receiver */
#define FUNC_UART1_TX                       65	/* UART1 Transmitter */
#define FUNC_UART2_RX                       66	/* UART2 Receiver */
#define FUNC_UART2_TX                       67	/* UART2 Transmitter */
#define FUNC_UART3_RX                       68	/* UART3 Receiver */
#define FUNC_UART3_TX                       69	/* UART3 Transmitter */
#define FUNC_SPI1_D0                        70	/* SPI1 Data 0 */
#define FUNC_SPI1_D1                        71	/* SPI1 Data 1 */
#define FUNC_SPI1_D2                        72	/* SPI1 Data 2 */
#define FUNC_SPI1_D3                        73	/* SPI1 Data 3 */
#define FUNC_SPI1_D4                        74	/* SPI1 Data 4 */
#define FUNC_SPI1_D5                        75	/* SPI1 Data 5 */
#define FUNC_SPI1_D6                        76	/* SPI1 Data 6 */
#define FUNC_SPI1_D7                        77	/* SPI1 Data 7 */
#define FUNC_SPI1_SS0                       78	/* SPI1 Chip Select 0 */
#define FUNC_SPI1_SS1                       79	/* SPI1 Chip Select 1 */
#define FUNC_SPI1_SS2                       80	/* SPI1 Chip Select 2 */
#define FUNC_SPI1_SS3                       81	/* SPI1 Chip Select 3 */
#define FUNC_SPI1_ARB                       82	/* SPI1 Arbitration */
#define FUNC_SPI1_SCLK                      83	/* SPI1 Serial Clock */
#define FUNC_SPI_SLAVE_D0                   84	/* SPI Slave Data 0 */
#define FUNC_SPI_SLAVE_SS                   85	/* SPI Slave Select */
#define FUNC_SPI_SLAVE_SCLK                 86	/* SPI Slave Serial Clock */
#define FUNC_I2S0_MCLK                      87	/* I2S0 Master Clock */
#define FUNC_I2S0_SCLK                      88	/* I2S0 Serial Clock(BCLK) */
#define FUNC_I2S0_WS                        89	/* I2S0 Word Select(LRCLK) */
#define FUNC_I2S0_IN_D0                     90	/* I2S0 Serial Data Input 0 */
#define FUNC_I2S0_IN_D1                     91	/* I2S0 Serial Data Input 1 */
#define FUNC_I2S0_IN_D2                     92	/* I2S0 Serial Data Input 2 */
#define FUNC_I2S0_IN_D3                     93	/* I2S0 Serial Data Input 3 */
#define FUNC_I2S0_OUT_D0                    94	/* I2S0 Serial Data Output 0 */
#define FUNC_I2S0_OUT_D1                    95	/* I2S0 Serial Data Output 1 */
#define FUNC_I2S0_OUT_D2                    96	/* I2S0 Serial Data Output 2 */
#define FUNC_I2S0_OUT_D3                    97	/* I2S0 Serial Data Output 3 */
#define FUNC_I2S1_MCLK                      98	/* I2S1 Master Clock */
#define FUNC_I2S1_SCLK                      99	/* I2S1 Serial Clock(BCLK) */
#define FUNC_I2S1_WS                        100	/* I2S1 Word Select(LRCLK) */
#define FUNC_I2S1_IN_D0                     101	/* I2S1 Serial Data Input 0 */
#define FUNC_I2S1_IN_D1                     102	/* I2S1 Serial Data Input 1 */
#define FUNC_I2S1_IN_D2                     103	/* I2S1 Serial Data Input 2 */
#define FUNC_I2S1_IN_D3                     104	/* I2S1 Serial Data Input 3 */
#define FUNC_I2S1_OUT_D0                    105	/* I2S1 Serial Data Output 0 */
#define FUNC_I2S1_OUT_D1                    106	/* I2S1 Serial Data Output 1 */
#define FUNC_I2S1_OUT_D2                    107	/* I2S1 Serial Data Output 2 */
#define FUNC_I2S1_OUT_D3                    108	/* I2S1 Serial Data Output 3 */
#define FUNC_I2S2_MCLK                      109	/* I2S2 Master Clock */
#define FUNC_I2S2_SCLK                      110	/* I2S2 Serial Clock(BCLK) */
#define FUNC_I2S2_WS                        111	/* I2S2 Word Select(LRCLK) */
#define FUNC_I2S2_IN_D0                     112	/* I2S2 Serial Data Input 0 */
#define FUNC_I2S2_IN_D1                     113	/* I2S2 Serial Data Input 1 */
#define FUNC_I2S2_IN_D2                     114	/* I2S2 Serial Data Input 2 */
#define FUNC_I2S2_IN_D3                     115	/* I2S2 Serial Data Input 3 */
#define FUNC_I2S2_OUT_D0                    116	/* I2S2 Serial Data Output 0 */
#define FUNC_I2S2_OUT_D1                    117	/* I2S2 Serial Data Output 1 */
#define FUNC_I2S2_OUT_D2                    118	/* I2S2 Serial Data Output 2 */
#define FUNC_I2S2_OUT_D3                    119	/* I2S2 Serial Data Output 3 */
#define FUNC_RESV0                          120	/* Reserved function */
#define FUNC_RESV1                          121	/* Reserved function */
#define FUNC_RESV2                          122	/* Reserved function */
#define FUNC_RESV3                          123	/* Reserved function */
#define FUNC_RESV4                          124	/* Reserved function */
#define FUNC_RESV5                          125	/* Reserved function */
#define FUNC_I2C0_SCLK                      126	/* I2C0 Serial Clock */
#define FUNC_I2C0_SDA                       127	/* I2C0 Serial Data */
#define FUNC_I2C1_SCLK                      128	/* I2C1 Serial Clock */
#define FUNC_I2C1_SDA                       129	/* I2C1 Serial Data */
#define FUNC_I2C2_SCLK                      130	/* I2C2 Serial Clock */
#define FUNC_I2C2_SDA                       131	/* I2C2 Serial Data */
#define FUNC_CMOS_XCLK                      132	/* DVP System Clock */
#define FUNC_CMOS_RST                       133	/* DVP System Reset */
#define FUNC_CMOS_PWDN                      134	/* DVP Power Down Mode */
#define FUNC_CMOS_VSYNC                     135	/* DVP Vertical Sync */
#define FUNC_CMOS_HREF                      136	/* DVP Horizontal Reference output */
#define FUNC_CMOS_PCLK                      137	/* Pixel Clock */
#define FUNC_CMOS_D0                        138	/* Data Bit 0 */
#define FUNC_CMOS_D1                        139	/* Data Bit 1 */
#define FUNC_CMOS_D2                        140	/* Data Bit 2 */
#define FUNC_CMOS_D3                        141	/* Data Bit 3 */
#define FUNC_CMOS_D4                        142	/* Data Bit 4 */
#define FUNC_CMOS_D5                        143	/* Data Bit 5 */
#define FUNC_CMOS_D6                        144	/* Data Bit 6 */
#define FUNC_CMOS_D7                        145	/* Data Bit 7 */
#define FUNC_SCCB_SCLK                      146	/* SCCB Serial Clock */
#define FUNC_SCCB_SDA                       147	/* SCCB Serial Data */
#define FUNC_UART1_CTS                      148	/* UART1 Clear To Send */
#define FUNC_UART1_DSR                      149	/* UART1 Data Set Ready */
#define FUNC_UART1_DCD                      150	/* UART1 Data Carrier Detect */
#define FUNC_UART1_RI                       151	/* UART1 Ring Indicator */
#define FUNC_UART1_SIR_IN                   152	/* UART1 Serial Infrared Input */
#define FUNC_UART1_DTR                      153	/* UART1 Data Terminal Ready */
#define FUNC_UART1_RTS                      154	/* UART1 Request To Send */
#define FUNC_UART1_OUT2                     155	/* UART1 User-designated Output 2 */
#define FUNC_UART1_OUT1                     156	/* UART1 User-designated Output 1 */
#define FUNC_UART1_SIR_OUT                  157	/* UART1 Serial Infrared Output */
#define FUNC_UART1_BAUD                     158	/* UART1 Transmit Clock Output */
#define FUNC_UART1_RE                       159	/* UART1 Receiver Output Enable */
#define FUNC_UART1_DE                       160	/* UART1 Driver Output Enable */
#define FUNC_UART1_RS485_EN                 161	/* UART1 RS485 Enable */
#define FUNC_UART2_CTS                      162	/* UART2 Clear To Send */
#define FUNC_UART2_DSR                      163	/* UART2 Data Set Ready */
#define FUNC_UART2_DCD                      164	/* UART2 Data Carrier Detect */
#define FUNC_UART2_RI                       165	/* UART2 Ring Indicator */
#define FUNC_UART2_SIR_IN                   166	/* UART2 Serial Infrared Input */
#define FUNC_UART2_DTR                      167	/* UART2 Data Terminal Ready */
#define FUNC_UART2_RTS                      168	/* UART2 Request To Send */
#define FUNC_UART2_OUT2                     169	/* UART2 User-designated Output 2 */
#define FUNC_UART2_OUT1                     170	/* UART2 User-designated Output 1 */
#define FUNC_UART2_SIR_OUT                  171	/* UART2 Serial Infrared Output */
#define FUNC_UART2_BAUD                     172	/* UART2 Transmit Clock Output */
#define FUNC_UART2_RE                       173	/* UART2 Receiver Output Enable */
#define FUNC_UART2_DE                       174	/* UART2 Driver Output Enable */
#define FUNC_UART2_RS485_EN                 175	/* UART2 RS485 Enable */
#define FUNC_UART3_CTS                      176	/* UART3 Clear To Send */
#define FUNC_UART3_DSR                      177	/* UART3 Data Set Ready */
#define FUNC_UART3_DCD                      178	/* UART3 Data Carrier Detect */
#define FUNC_UART3_RI                       179	/* UART3 Ring Indicator */
#define FUNC_UART3_SIR_IN                   180	/* UART3 Serial Infrared Input */
#define FUNC_UART3_DTR                      181	/* UART3 Data Terminal Ready */
#define FUNC_UART3_RTS                      182	/* UART3 Request To Send */
#define FUNC_UART3_OUT2                     183	/* UART3 User-designated Output 2 */
#define FUNC_UART3_OUT1                     184	/* UART3 User-designated Output 1 */
#define FUNC_UART3_SIR_OUT                  185	/* UART3 Serial Infrared Output */
#define FUNC_UART3_BAUD                     186	/* UART3 Transmit Clock Output */
#define FUNC_UART3_RE                       187	/* UART3 Receiver Output Enable */
#define FUNC_UART3_DE                       188	/* UART3 Driver Output Enable */
#define FUNC_UART3_RS485_EN                 189	/* UART3 RS485 Enable */
#define FUNC_TIMER0_TOGGLE1                 190	/* TIMER0 Toggle Output 1 */
#define FUNC_TIMER0_TOGGLE2                 191	/* TIMER0 Toggle Output 2 */
#define FUNC_TIMER0_TOGGLE3                 192	/* TIMER0 Toggle Output 3 */
#define FUNC_TIMER0_TOGGLE4                 193	/* TIMER0 Toggle Output 4 */
#define FUNC_TIMER1_TOGGLE1                 194	/* TIMER1 Toggle Output 1 */
#define FUNC_TIMER1_TOGGLE2                 195	/* TIMER1 Toggle Output 2 */
#define FUNC_TIMER1_TOGGLE3                 196	/* TIMER1 Toggle Output 3 */
#define FUNC_TIMER1_TOGGLE4                 197	/* TIMER1 Toggle Output 4 */
#define FUNC_TIMER2_TOGGLE1                 198	/* TIMER2 Toggle Output 1 */
#define FUNC_TIMER2_TOGGLE2                 199	/* TIMER2 Toggle Output 2 */
#define FUNC_TIMER2_TOGGLE3                 200	/* TIMER2 Toggle Output 3 */
#define FUNC_TIMER2_TOGGLE4                 201	/* TIMER2 Toggle Output 4 */
#define FUNC_CLK_SPI2                       202	/* Clock SPI2 */
#define FUNC_CLK_I2C2                       203	/* Clock I2C2 */
#define FUNC_INTERNAL0                      204	/* Internal function signal 0 */
#define FUNC_INTERNAL1                      205	/* Internal function signal 1 */
#define FUNC_INTERNAL2                      206	/* Internal function signal 2 */
#define FUNC_INTERNAL3                      207	/* Internal function signal 3 */
#define FUNC_INTERNAL4                      208	/* Internal function signal 4 */
#define FUNC_INTERNAL5                      209	/* Internal function signal 5 */
#define FUNC_INTERNAL6                      210	/* Internal function signal 6 */
#define FUNC_INTERNAL7                      211	/* Internal function signal 7 */
#define FUNC_INTERNAL8                      212	/* Internal function signal 8 */
#define FUNC_INTERNAL9                      213	/* Internal function signal 9 */
#define FUNC_INTERNAL10                     214	/* Internal function signal 10 */
#define FUNC_INTERNAL11                     215	/* Internal function signal 11 */
#define FUNC_INTERNAL12                     216	/* Internal function signal 12 */
#define FUNC_INTERNAL13                     217	/* Internal function signal 13 */
#define FUNC_INTERNAL14                     218	/* Internal function signal 14 */
#define FUNC_INTERNAL15                     219	/* Internal function signal 15 */
#define FUNC_INTERNAL16                     220	/* Internal function signal 16 */
#define FUNC_INTERNAL17                     221	/* Internal function signal 17 */
#define FUNC_CONSTANT                       222	/* Constant function */
#define FUNC_INTERNAL18                     223	/* Internal function signal 18 */
#define FUNC_DEBUG0                         224	/* Debug function 0 */
#define FUNC_DEBUG1                         225	/* Debug function 1 */
#define FUNC_DEBUG2                         226	/* Debug function 2 */
#define FUNC_DEBUG3                         227	/* Debug function 3 */
#define FUNC_DEBUG4                         228	/* Debug function 4 */
#define FUNC_DEBUG5                         229	/* Debug function 5 */
#define FUNC_DEBUG6                         230	/* Debug function 6 */
#define FUNC_DEBUG7                         231	/* Debug function 7 */
#define FUNC_DEBUG8                         232	/* Debug function 8 */
#define FUNC_DEBUG9                         233	/* Debug function 9 */
#define FUNC_DEBUG10                        234	/* Debug function 10 */
#define FUNC_DEBUG11                        235	/* Debug function 11 */
#define FUNC_DEBUG12                        236	/* Debug function 12 */
#define FUNC_DEBUG13                        237	/* Debug function 13 */
#define FUNC_DEBUG14                        238	/* Debug function 14 */
#define FUNC_DEBUG15                        239	/* Debug function 15 */
#define FUNC_DEBUG16                        240	/* Debug function 16 */
#define FUNC_DEBUG17                        241	/* Debug function 17 */
#define FUNC_DEBUG18                        242	/* Debug function 18 */
#define FUNC_DEBUG19                        243	/* Debug function 19 */
#define FUNC_DEBUG20                        244	/* Debug function 20 */
#define FUNC_DEBUG21                        245	/* Debug function 21 */
#define FUNC_DEBUG22                        246	/* Debug function 22 */
#define FUNC_DEBUG23                        247	/* Debug function 23 */
#define FUNC_DEBUG24                        248	/* Debug function 24 */
#define FUNC_DEBUG25                        249	/* Debug function 25 */
#define FUNC_DEBUG26                        250	/* Debug function 26 */
#define FUNC_DEBUG27                        251	/* Debug function 27 */
#define FUNC_DEBUG28                        252	/* Debug function 28 */
#define FUNC_DEBUG29                        253	/* Debug function 29 */
#define FUNC_DEBUG30                        254	/* Debug function 30 */
#define FUNC_DEBUG31                        255	/* Debug function 31 */
#define FUNC_MAX                            256	/* Function numbers */


#define CLINT_BASE_ADDR         0x02000000UL
#define PLIC_BASE_ADDR          0x0C000000UL

/* Under TileLink */
#define UARTHS_BASE_ADDR        0x38000000UL
#define GPIOHS_BASE_ADDR        0x38001000UL

/* Under AXI 64 bit */
#define RAM_BASE_ADDR           0x80000000UL
#define RAM_SIZE                (6 * 1024 * 1024U)
#define AI_RAM_BASE_ADDR        (RAM_BASE_ADDR + RAM_SIZE)
#define AI_RAM_SIZE             (2 * 1024 * 1024U)

#define IO_BASE_ADDR            0x40000000UL
#define IO_SIZE                 (6 * 1024 * 1024U)
#define AI_IO_BASE_ADDR         (IO_BASE_ADDR + IO_SIZE)
#define AI_IO_SIZE              (2 * 1024 * 1024U)
#define AI_BASE_ADDR            (AI_IO_BASE_ADDR + AI_IO_SIZE)
#define AI_SIZE                 (12 * 1024 * 1024U)

#define FFT_BASE_ADDR           0x42000000UL
#define FFT_SIZE                (4 * 1024 * 1024U)

#define ROM_BASE_ADDR           0x88000000UL
#define ROM_SIZE                (128 * 1024U)

/* Under AHB 32 bit */
#define DMAC_BASE_ADDR          0x50000000UL

/* Under APB1 32 bit */
#define GPIO_BASE_ADDR          0x50200000UL
#define UART1_BASE_ADDR         0x50210000UL
#define SPI_SLAVE_BASE_ADDR     0x50240000UL
#define I2S0_BASE_ADDR          0x50250000UL
#define I2S1_BASE_ADDR          0x50260000UL
#define I2S2_BASE_ADDR          0x50270000UL
#define I2C0_BASE_ADDR          0x50280000UL
#define I2C1_BASE_ADDR          0x50290000UL
#define I2C2_BASE_ADDR          0x502A0000UL
#define FPIOA_BASE_ADDR         0x502B0000UL
#define SHA256_BASE_ADDR        0x502C0000UL
#define TIMER0_BASE_ADDR        0x502D0000UL
#define TIMER1_BASE_ADDR        0x502E0000UL
#define TIMER2_BASE_ADDR        0x502F0000UL

/* Under APB2 32 bit */
#define WDT0_BASE_ADDR          0x50400000UL
#define WDT1_BASE_ADDR          0x50410000UL
#define OTP_BASE_ADDR           0x50420000UL
#define DVP_BASE_ADDR           0x50430000UL
#define SYSCTL_BASE_ADDR        0x50440000UL
#define AES_BASE_ADDR           0x50450000UL
#define RTC_BASE_ADDR           0x50460000UL


/* Under APB3 32 bit */
#define SPI0_BASE_ADDR          0x52000000UL
#define SPI1_BASE_ADDR          0x53000000UL
#define SPI3_BASE_ADDR          0x54000000UL


/*
 *  CLINT (64bits registers)
 */
#define TADR_CLIC_BASE      (CLINT_BASE_ADDR)
#define TOFF_CLINT_MSIP     0x0000			/* (RW) MSIP Registers 4bytes */
  #define CLINT_MSOFTIP       0x000000001	/* Machine-mode software interrupt */
#define TOFF_CLINT_MTIMECMP 0x4000			/* (RW) Timer compare Registers Machine-mode timer interrupts 8bytes */
#define TOFF_CLINT_MTIME    0xBFF8			/* (R)  Timer Registers 8bytes */

#define CLINT_MAX_CORES     (4095)


/*
 *  PLIC
 */
#define TADR_PLIC_BASE      (PLIC_BASE_ADDR)
#define TOFF_PLIC_PRIORITY  0x00000000
#define TOFF_PLIC_PENDING   0x00001000
#define TOFF_PLIC_ENABLE    0x00002000
#define NUM_PLIC_ENABLE     1024
#define TOFF_PLIC_THRESHOLD 0x00200000
#define NUM_PLIC_THRESHOLD  4096
#define TOFF_PLIC_CLAIM     0x00200004


/*
 *  DMAC (64bits registers)
 */
#define TADR_DMAC_BASE      (DMAC_BASE_ADDR)
#define TOFF_DMAC_ID                0x0000	/* (R)  DMAC ID Rgister */
#define TOFF_DMAC_COMPVER           0x0008	/* (R)  DMAC COMPVER Register */
#define TOFF_DMAC_CFG               0x0010	/* (RW) DMAC Configure Register */
  #define DMAC_CFG_DMAC_EN              0x00000001L	/* enable dmac(dmac_en) */
  #define DMAC_CFG_INT_EN               0x00000002L	/* glabally enable interrupt generation(int_en) */
#define TOFF_DMAC_CHEN              0x0018	/* (RW) Channel Enable Register */
  #define DMAC_CHEN_CH1_EN              0x0000000000000001	 /* enable channel 1(ch1_en) */
  #define DMAC_CHEN_CH2_EN              0x0000000000000002	 /* enable channel 2(ch2_en) */
  #define DMAC_CHEN_CH3_EN              0x0000000000000004	 /* enable channel 3(ch3_en) */
  #define DMAC_CHEN_CH4_EN              0x0000000000000008	 /* enable channel 4(ch4_en) */
  #define DMAC_CHEN_CH5_EN              0x0000000000000010	 /* enable channel 5(ch5_en) */
  #define DMAC_CHEN_CH6_EN              0x0000000000000020	 /* enable channel 6(ch6_en) */
  #define DMAC_CHEN_CH1_EN_WE           0x0000000000000100	 /* write enable bit channel 1(ch1_en_we) */
  #define DMAC_CHEN_CH2_EN_WE           0x0000000000000200	 /* write enable bit channel 2(ch2_en_we) */
  #define DMAC_CHEN_CH3_EN_WE           0x0000000000000400	 /* write enable bit channel 3(ch3_en_we) */
  #define DMAC_CHEN_CH4_EN_WE           0x0000000000000800	 /* write enable bit channel 4(ch4_en_we) */
  #define DMAC_CHEN_CH5_EN_WE           0x0000000000001000	 /* write enable bit channel 5(ch5_en_we) */
  #define DMAC_CHEN_CH6_EN_WE           0x0000000000002000	 /* write enable bit channel 6(ch6_en_we) */
  #define DMAC_CHEN_CH1_SUSP            0x0000000000010000	 /* susped reuest channel 1(ch1_susp) */
  #define DMAC_CHEN_CH2_SUSP            0x0000000000020000	 /* susped reuest channel 2(ch2_susp) */
  #define DMAC_CHEN_CH3_SUSP            0x0000000000040000	 /* susped reuest channel 3(ch3_susp) */
  #define DMAC_CHEN_CH4_SUSP            0x0000000000080000	 /* susped reuest channel 4(ch4_susp) */
  #define DMAC_CHEN_CH5_SUSP            0x0000000000100000	 /* susped reuest channel 5(ch5_susp) */
  #define DMAC_CHEN_CH6_SUSP            0x0000000000200000	 /* susped reuest channel 6(ch6_susp) */
  #define DMAC_CHEN_CH1_SUSP_WE         0x0000000001000000	 /* swrite enable to the channel 1 suspend(ch1_susp_we) */
  #define DMAC_CHEN_CH2_SUSP_WE         0x0000000002000000	 /* swrite enable to the channel 2 suspend(ch2_susp_we) */
  #define DMAC_CHEN_CH3_SUSP_WE         0x0000000004000000	 /* swrite enable to the channel 3 suspend(ch3_susp_we) */
  #define DMAC_CHEN_CH4_SUSP_WE         0x0000000008000000	 /* swrite enable to the channel 4 suspend(ch4_susp_we) */
  #define DMAC_CHEN_CH5_SUSP_WE         0x0000000010000000	 /* swrite enable to the channel 5 suspend(ch5_susp_we) */
  #define DMAC_CHEN_CH6_SUSP_WE         0x0000000020000000	 /* swrite enable to the channel 6 suspend(ch6_susp_we) */
  #define DMAC_CHEN_CH1_ABOUT           0x0000000100000000	 /* channel-1 abort requst bit(ch1_abort) */
  #define DMAC_CHEN_CH2_ABOUT           0x0000000200000000	 /* channel-2 abort requst bit(ch2_abort) */
  #define DMAC_CHEN_CH3_ABOUT           0x0000000400000000	 /* channel-3 abort requst bit(ch3_abort) */
  #define DMAC_CHEN_CH4_ABOUT           0x0000000800000000	 /* channel-4 abort requst bit(ch4_abort) */
  #define DMAC_CHEN_CH5_ABOUT           0x0000001000000000	 /* channel-5 abort requst bit(ch5_abort) */
  #define DMAC_CHEN_CH6_ABOUT           0x0000002000000000	 /* channel-6 abort requst bit(ch6_abort) */
  #define DMAC_CHEN_CH1_ABOUT_WE        0x0000010000000000	 /* write enable  channel-1 abort bit(ch1_abort_we) */
  #define DMAC_CHEN_CH2_ABOUT_WE        0x0000020000000000	 /* write enable  channel-2 abort bit(ch2_abort_we) */
  #define DMAC_CHEN_CH3_ABOUT_WE        0x0000040000000000	 /* write enable  channel-3 abort bit(ch3_abort_we) */
  #define DMAC_CHEN_CH4_ABOUT_WE        0x0000080000000000	 /* write enable  channel-4 abort bit(ch4_abort_we) */
  #define DMAC_CHEN_CH5_ABOUT_WE        0x0000100000000000	 /* write enable  channel-5 abort bit(ch5_abort_we) */
  #define DMAC_CHEN_CH6_ABOUT_WE        0x0000200000000000	 /* write enable  channel-6 abort bit(ch6_abort_we) */
#define TOFF_DMAC_INTSTATUS         0x0030	/* (RW) DMAC Interrupt Status Register */
  #define DMAC_INTSTATUS_CH1            0x00000001L	 /* channel 1 interrupt bit(ch1_intstat) */
  #define DMAC_INTSTATUS_CH2            0x00000002L	 /* channel 2 interrupt bit(ch2_intstat) */
  #define DMAC_INTSTATUS_CH3            0x00000004L	 /* channel 3 interrupt bit(ch3_intstat) */
  #define DMAC_INTSTATUS_CH4            0x00000008L	 /* channel 4 interrupt bit(ch4_intstat) */
  #define DMAC_INTSTATUS_CH5            0x00000010L	 /* channel 5 interrupt bit(ch5_intstat) */
  #define DMAC_INTSTATUS_CH6            0x00000020L	 /* channel 6 interrupt bit(ch6_intstat) */
#define TOFF_DMAC_COM_INTCLEAR      0x0038	/* (RW) DMAC Common register Interrupt Status Register */
  #define DMAC_COM_INTCLEAR_SLVIF_DEC_ERR           0x00000001L	/* Slave Interface Common Register Decode Error Interrupt Status clear(clear_slvif_dec_err_intstat) */
  #define DMAC_COM_INTCLEAR_SLVIF_WR2RO_ERR         0x00000002L	/* Slave Interface Common Register Write to Read only Error Interrupt Status clear(clear_slvif_wr2ro_err_intstat) */
  #define DMAC_COM_INTCLEAR_SLVIF_RD2WO_ERR         0x00000004L	/* Slave Interface Common Register Read to Write only Error Interrupt Status clear(clear_slvif_rd2wo_err_intstat) */
  #define DMAC_COM_INTCLEAR_SLVIF_WRONHOLD_ERR      0x00000008L	/* Slave Interface Common Register Write On Hold Error Interrupt Status clear(clear_slvif_wronhold_err_intstat) */
  #define DMAC_COM_INTCLEAR_SLVIF_UNDEFREG_ERR      0x00000100L	/* Slave Interface Undefined register Decode Error Interrupt Status clear(clear_slvif_undefinedreg_dec_err_intstat) */
#define TOFF_DMAC_COM_INTSTATUS_EN  0x0040	/* (RW) DMAC Common Interrupt Enable Register */
  #define DMAC_COM_INTSTATUS_EN_SLVIF_DEC_ERR       0x00000001L	/* Slave Interface Common Register Decode Error Interrupt Status Enable(enable_slvif_dec_err_intstat) */
  #define DMAC_COM_INTSTATUS_EN_SLVIF_WR2RO_ERR     0x00000002L	/* Slave Interface Common Register Write to Read only Error Interrupt Status Enable(enable_slvif_wr2ro_err_intstat) */
  #define DMAC_COM_INTSTATUS_EN_SLVIF_RD2WO_ERR     0x00000004L	/* Slave Interface Common Register Read to Write only Error Interrupt Status Enable(enable_slvif_rd2wo_err_intstat) */
  #define DMAC_COM_INTSTATUS_EN_SLVIF_WRONHOLD_ERR  0x00000008L	/* Slave Interface Common Register Write On Hold Error Interrupt Status Enable(enable_slvif_wronhold_err_intstat) */
  #define DMAC_COM_INTSTATUS_EN_SLVIF_UNDEFREG_ERR  0x00000100L	/* Slave Interface Undefined register Decode Error Interrupt Status Enable(enable_slvif_undefinedreg_dec_err_intstat) */
#define TOFF_DMAC_COM_INTSIGNAL_EN  0x0048	/* (RW) DMAC Common Interrupt Signal Enable Register */
  #define DMAC_COM_INTSIGNAL_EN_SLVIF_DEC_ERR       0x00000001L	/* Slave Interface Common Register Decode Error Interrupt Signal Enable(enable_slvif_dec_err_intsignal) */
  #define DMAC_COM_INTSIGNAL_EN_SLVIF_WR2RO_ERR     0x00000002L	/* Slave Interface Common Register Write to Read only Error Interrupt Signal Enable(enable_slvif_wr2ro_err_intsignal) */
  #define DMAC_COM_INTSIGNAL_EN_SLVIF_RD2WO_ERR     0x00000004L	/* Slave Interface Common Register Read to Write only Error Interrupt Signal Enable(enable_slvif_rd2wo_err_intsignal) */
  #define DMAC_COM_INTSIGNAL_EN_SLVIF_WRONHOLD_ERR  0x00000008L	/* Slave Interface Common Register Write On Hold Error Interrupt Signal Enable(enable_slvif_wronhold_err_intsignal) */
  #define DMAC_COM_INTSIGNAL_EN_SLVIF_UNDEFREG_ERR  0x00000100L	/* Slave Interface Undefined register Decode Error Interrupt Signal Enable(enable_slvif_undefinedreg_dec_err_intsignal) */
#define TOFF_DMAC_COM_INTSTATUS     0x0050	/* (RW) DMAC Common Interrupt Status */
  #define DMAC_COM_INTSTATUS_SLVIF_DEC_ERR          0x00000001L	/* Slave Interface Common Register Decode(slvif_dec_err_intstat) */
  #define DMAC_COM_INTSTATUS_SLVIF_WR2RO_ERR        0x00000002L	/* Slave Interface Common Register Write to Read Only(slvif_wr2ro_err_intstat */
  #define DMAC_COM_INTSTATUS_SLVIF_RD2WO_ERR        0x00000004L	/* Slave Interface Common Register Read to Write(slvif_rd2wo_err_intstat) */
  #define DMAC_COM_INTSTATUS_SLVIF_WRONHOLD_ERR     0x00000008L	/*Slave Interface Common Register Write On(slvif_wronhold_err_intstat) */
  #define DMAC_COM_INTSTATUS_SLVIF_UNDEFREG_ERR     0x00000100L	/*Slave Interface Undefined register Decode Error(slvif_undefinedreg_dec_err_intstat) */
#define TOFF_DMAC_RESET             0x0058	/* (RW) DMAC Reset register */
  #define DMAC_RESET_RST                0x00000001L	/* DMAC reset request bit */
#define TOFF_DMAC_CHANNEL           0x0100	/* (RW) DMAC channel registers */

/*
 *  DMAC CHANNEL WINDOW
 */
#define TOFF_DMAC_CH_SAR            0x0000	/* (RW) SAR Address Register */
#define TOFF_DMAC_CH_DAR            0x0008	/* (RW) DAR Address Register */
#define TOFF_DMAC_CH_BLOCK_TS       0x0010	/* (RW) Block Transfer Size Register */
  #define DMACCH_BLOCK_TS               0x03FFFFFFL	/* block transfer size(block_ts) */
#define TOFF_DMAC_CH_CTL            0x0018	/* (RW) Control Register */
  #define DMACCH_CTL_SMS                0x0000000000000001	/* source master select(sms) */
  #define DMACCH_CTL_DMS                0x0000000000000004	/* destination master select(dms) */
  #define DMACCH_CTL_SINC               0x0000000000000010	/* source address increment(sinc) */
  #define DMACCH_CTL_DINC               0x0000000000000040	/* destination address incremnet(dinc) */
  #define DMACCH_CTL_SRC_TR_WIDTH       0x0000000000000700	/* source transfer width(src_tr_width) */
  /* * 0x0 for source transfer width is 8 bits
     * 0x1 for source transfer width is 16 bits
     * 0x2 for source transfer width is 32 bits
     * 0x3 for source transfer width is 64 bits
     * 0x4 for source transfer width is 128 bits
     * 0x5  for source transfer width is 256 bits
     * 0x6 for source transfer width is 512 bits
     */
  #define DMACCH_CTL_DST_TR_WIDTH       0x0000000000003800	/* detination transfer width(dst_tr_width) */
  /* * 0x0 for detination transfer width is 8 bits
     * 0x1 for detination transfer width is 16 bits
     * 0x2 for detination transfer width is 32 bits
     * 0x3 for detination transfer width is 64 bits
     * 0x4 for detination transfer width is 128 bits
     * 0x5  for detination transfer width is 256 bits
     * 0x6 for detination transfer width is 512 bits
     */
  #define DMACCH_CTL_SRC_MSIZE          0x000000000003C000	/* source burst transaction length(src_msize) */
  /* * 0x0 for 1 data item read from rource in the burst transaction
     * 0x1 for 4 data item read from rource in the burst transaction
     * 0x2 for 8 data item read from rource in the burst transaction
     * 0x3 for 16 data item read from rource in the burst transaction
     * 0x4 for 32 data item read from rource in the burst transaction
     * 0x5 for 64 data item read from rource in the burst transaction
     * 0x6 for 128 data item read from rource in the burst transaction
     * 0x7 for 256 data item read from rource in the burst transaction
     * 0x8 for 512 data item read from rource in the burst transaction
     * 0x9 for 1024 data item read from rource in the burst transaction
     */
  #define DMACCH_CTL_DST_MSIZE          0x00000000003C0000	/* destination burst transaction length(dst_msize) */
  /* * 0x0 for 1 data item read from rource in the burst transaction
     * 0x1 for 4 data item read from rource in the burst transaction
     * 0x2 for 8 data item read from rource in the burst transaction
     * 0x3 for 16 data item read from rource in the burst transaction
     * 0x4 for 32 data item read from rource in the burst transaction
     * 0x5 for 64 data item read from rource in the burst transaction
     * 0x6 for 128 data item read from rource in the burst transaction
     * 0x7 for 256 data item read from rource in the burst transaction
     * 0x8 for 512 data item read from rource in the burst transaction
     * 0x9 for 1024 data item read from rource in the burst transaction
     */
  #define DMACCH_CTL_NONP_LASTWRITE_EN  0x0000000040000000	/* Non Posted Last Write Enable(nonposted_lastwrite_en) */
  #define DMACCH_CTL_ARLEN_EN           0x0000004000000000	/* source burst length enable(arlen_en) */
  #define DMACCH_CTL_ARLEN              0x00007F1000000000	/* source burst length(arlen) */
  #define DMACCH_CTL_AWLEN_EN           0x0000800000000000	/* destination burst length enable(awlen_en) */
  #define DMACCH_CTL_AWLEN              0x00FF000000000000	/* destination burst length(awlen) */
  #define DMACCH_CTL_SRC_STAT_EN        0x0100000000000000	/* source status enable(src_stat_en) */
  #define DMACCH_CTL_DST_STAT_EN        0x0200000000000000	/* destination status enable(dst_stat_en) */
  #define DMACCH_CTL_IOC_BLKTFR         0x0400000000000000	/* interrupt completion of block transfer(ioc_blktfr) */
  #define DMACCH_CTL_SHREG_OR_LLI_LAST  0x4000000000000000	/* last shadow linked list item(shadowreg_or_lli_last) */
  #define DMACCH_CTL_SHREG_OR_LLI_VALID 0x8000000000000000	/* last shadow linked list item valid(shadowreg_or_lli_valid) */
#define TOFF_DMAC_CH_CFG            0x0020	/* (RW) Configure Register */
  #define DMACCH_CFG_SRC_MULTBLKTYPE    0x0000000000000003	/* source multi block transfer type(src_multblk_type) */
  /* * 0x0 for continuous multiblock type
     * 0x1 for reload multiblock type
     * 0x2 for shadow register based multiblock type
     * 0x3 for linked lisr bases multiblock type
     */
  #define DMACCH_CFG_DST_MULTBLKTYPE    0x000000000000000C	/* destination multi block transfer type(dst_multblk_type) */
  /* * 0x0 for continuous multiblock type
     * 0x1 for reload multiblock type
     * 0x2 for shadow register based multiblock type
     * 0x3 for linked lisr bases multiblock type
     */
  #define DMACCH_CFG_TT_FC              0x0000000700000000	/* transfer type and flow control(tt_fc) */
  /* * 0x0  transfer memory to memory and flow controler is dmac
     * 0x1  transfer memory to peripheral and flow controler is dmac
     * 0x2  transfer peripheral to memory and flow controler is dmac
     * 0x3  transfer peripheral to peripheral and flow controler is dmac
     * 0x4  transfer peripheral to memory and flow controler is
     * source peripheral
     * 0x5  transfer peripheral to peripheral and flow controler
     * is source peripheral
     * 0x6  transfer memory to peripheral and flow controler is
     * destination peripheral
     * 0x7  transfer peripheral to peripheral and flow controler
     * is destination peripheral
     */
  #define DMACCH_CFG_HS_SEL_SRC         0x0000000800000000	/* source software or hardware handshaking select(hs_sel_src) */
  #define DMACCH_CFG_HS_SEL_DST         0x0000001000000000	/* destination software or hardware handshaking select(hs_sel_dst) */
  #define DMACCH_CFG_SRC_HWHS_POL       0x0000002000000000	/* sorce hardware handshaking interface polarity(src_hwhs_pol) */
  #define DMACCH_CFG_DST_HWHS_POL       0x0000004000000000	/* destination hardware handshaking interface polarity(dst_hwhs_pol) */
  #define DMACCH_CFG_SRC_PER            0x0000078000000000	/* assign a hardware handshaking interfaceto source of channel x(src_per) */
  #define DMACCH_CFG_DST_PER            0x0000F00000000000	/* assign a hardware handshaking interfaceto destination of channel x(dst_per) */
  #define DMACCH_CFG_CH_PRIOR           0x000E000000000000	/* channel priority,7 is highest, 0 is lowest(ch_prior) */
  #define DMACCH_CFG_LOCK_CH            0x0010000000000000	/* channel lock bit(lock_ch) */
  #define DMACCH_CFG_LOCK_CH_L          0x0060000000000000	/* channel lock level(lock_ch_l) */
  #define DMACCH_CFG_SRC_OSR_LMT        0x0780000000000000	/* source outstanding request limit(src_osr_lmt) */
  #define DMACCH_CFG_DST_OSR_LMT        0x7800000000000000	/* destination outstanding request limit(dst_osr_lmt) */
#define TOFF_DMAC_CH_LLP            0x0028	/* (RW) Linked List Pointer register */
  #define DMACCH_LLP_LMS                0x0000000000000001	/* LLI master select(lms) */
  #define DMACCH_LLP_LOC                0xFFFFFFFFFFFFFFC0	/* starting address memeory of LLI block(loc) */
#define TOFF_DMAC_CH_STATUS         0x0030	/* (RW) Channelx Status Register */
  #define DMACCH_CMPLTD_BLK_SIZE        0x03FFFFFFL	/* completed block transfer size(cmpltd_blk_size) */
#define TOFF_DMAC_CH_SWHSSRC        0x0038	/* (RW) Channelx Software handshake Source Register */
  #define DMACCH_SWHS_REQ_SRC           0x00000001L	/* software handshake request for channel source(swhs_req_src) */
  #define DMACCH_SWHS_REQ_SRC_WE        0x00000002L	/* write enable bit for software handshake request(swhs_req_src_we) */
  #define DMACCH_SWHS_SGLREQ_SRC        0x00000004L	/* software handshake single request for channel source(swhs_sglreq_src) */
  #define DMACCH_SWHS_SGLREQ_SRC_WE     0x00000008L	/* write enable bit for software handshake single request for channle source(swhs_sglreq_src_we) */
  #define DMACCH_SWHS_LST_SRC           0x00000010L	/* software handshake last request for channel source(swhs_lst_src) */
  #define DMACCH_SWHS_LST_SRC_WE        0x00000020L	/* write enable bit for software handshake last request(swhs_lst_src_we) */
#define TOFF_DMAC_CH_SWHSDST        0x0040	/* (RW) Channelx Software handshake Destination Register */
  #define DMACCH_SWHS_REQ_DST           0x00000001L	/* software handshake request for channel destination(swhs_req_dst) */
  #define DMACCH_SWHS_REQ_DST_WE        0x00000002L	/* write enable bit for software handshake request(swhs_req_dst_we) */
  #define DMACCH_SWHS_SGLREQ_DST        0x00000004L	/* software handshake single request for channel destination(swhs_sglreq_dst) */
  #define DMACCH_SWHS_SGLREQ_DST_WE     0x00000008L	/* write enable bit for software handshake single request for channle destination(swhs_sglreq_dst_we) */
  #define DMACCH_SWHS_LST_DST           0x00000010L	/* software handshake last request for channel destination(swhs_lst_dst) */
  #define DMACCH_SWHS_LST_DST_WE        0x00000020L	/* write enable bit for software handshake last request(swhs_lst_dst_we) */
#define TOFF_DMAC_CH_BLK_TFR        0x0048	/* (RW) Channelx Block Transfer Resume Request Register */
  #define DMACCH_BLK_TFR_RESUMEREQ      0x00000001L	/* block transfer resume request bit */
#define TOFF_DMAC_CH_AXI_ID         0x0050	/* (R)  Channelx AXI ID Register */
#define TOFF_DMAC_CH_AXI_QOS        0x0058	/* (RW) Channelx AXI QOS Register */
#define TOFF_DMAC_CH_INTSTATUS_EN   0x0080	/* (RW) Interrupt Status Enable Register */
  #define DMACCH_ENABLE_BLOCK_TFR_DONE_INTSTAT 0x00000001L	/* block transfer done interrupt status enable(enable_block_tfr_done_intstatus) */
  #define DMACCH_ENABLE_DMA_TFR_DONE_INTSTAT   0x00000002L	/* DMA transfer done interrupt status enable(enable_dma_tfr_done_intstat) */
  #define DMACCH_ENABLE_SRC_TRANSCOMP_INTSTAT  0x00000008L	/* source transaction complete status enable(enable_src_transcomp_intstat) */
  #define DMACCH_ENABLE_DST_TRANSCOMP_INSTAT   0x00000010L	/* destination transaction complete(enable_dst_transcomp_intstat) */
  #define DMACCH_ENABLE_SRC_DEC_ERR_INSTAT     0x00000020L	/* Source Decode Error Status Enable(enable_src_dec_err_intstat) */
  #define DMACCH_ENABLE_DST_DEC_ERR_INSTAT     0x00000040L	/* Destination Decode Error Status Enable(enable_dst_dec_err_intstat) */
  #define DMACCH_ENABLE_SRC_SLV_ERR_INSTAT     0x00000080L	/* Source Slave Error Status Enable(enable_src_slv_err_intstat) */
  #define DMACCH_ENABLE_DST_SLV_ERR_INSTAT     0x00000100L	/* Destination Slave Error Status Enable(enable_dst_slv_err_intstat) */
  #define DMACCH_ENABLE_LLI_RD_DEC_ERR_INSTAT  0x00000200L	/* LLI Read Decode Error Status Enable(enable_lli_rd_dec_err_intstat) */
  #define DMACCH_ENABLE_LLI_WR_DEC_ERR_INSTAT  0x00000400L	/* LLI WRITE Decode Error Status Enable(enable_lli_wr_dec_err_intstat) */
  #define DMACCH_ENABLE_LLI_RD_SLV_ERR_INSTAT  0x00000800L	/* LLI Read Slave Error Status Enable(enable_lli_rd_slv_err_intstat) */
  #define DMACCH_ENABLE_LLI_WR_SLV_ERR_INSTAT  0x00001000L	/* LLI WRITE Slave Error Status Enable(enable_lli_wr_slv_err_intstat) */
#define TOFF_DMAC_CH_INTSTATUS      0x0088	/* (RW) Channelx Interrupt Status Register */
#define TOFF_DMAC_CH_INTSIGNAL_EN   0x0090	/* (RW) Interrupt  Siganl Enable Register */
#define TOFF_DMAC_CH_INTCLEAR       0x0098	/* (W)  Interrupt Clear Register */
  #define DMACCH_BLK_TFR_DONE_INSTAT    0x00000001L	/* block transfer done interrupt clear bit(blk_tfr_done_intstat) */
  #define DMACCH_DMA_TFR_DONE_INSTAT    0x00000002L	/* DMA transfer done interrupt clear bit(dma_tfr_done_intstat) */

#define DMAC_CHANNEL_WINDOW_SIZE    0x0100
#define NUM_DMAC_CHANNEL            6

/*
 *  GPIOHS
 */
#define TADR_GPIOHS_BASE    (GPIOHS_BASE_ADDR)
#define TOFF_GPIOHS_INPUT_VAL   0x0000	/* (RW) Input Values */
#define TOFF_GPIOHS_INPUT_EN    0x0004	/* (RW) Input enable */
#define TOFF_GPIOHS_OUTPUT_EN   0x0008	/* (RW) Output enable */
#define TOFF_GPIOHS_OUTPUT_VAL  0x000C	/* (RW) Onput Values */
#define TOFF_GPIOHS_PULLUP_EN   0x0010	/* (RW) Internal Pull-Ups enable */
#define TOFF_GPIOHS_DRIVE       0x0014	/* (RW) Drive Strength */
#define TOFF_GPIOHS_RISE_IE     0x0018	/* (RW) Rise interrupt enable */
#define TOFF_GPIOHS_RISE_IP     0x001C	/* (RW) Rise interrupt pending */
#define TOFF_GPIOHS_FALL_IE     0x0020	/* (RW) Fall interrupt enable */
#define TOFF_GPIOHS_FALL_IP     0x0024	/* (RW) Fall interrupt pending */
#define TOFF_GPIOHS_HIGH_IE     0x0028	/* (RW) High interrupt enable */
#define TOFF_GPIOHS_HIGH_IP     0x002C	/* (RW) High interrupt pending */
#define TOFF_GPIOHS_LOW_IE      0x0030	/* (RW) Low interrupt enable */
#define TOFF_GPIOHS_LOW_IP      0x0034	/* (RW) Low interrupt pending */
#define TOFF_GPIOHS_IOF_EN      0x0038	/* (RW) HW I/O Function enable */
#define TOFF_GPIOHS_IOF_SEL     0x003C	/* (RW) HW I/O Function select */
#define TOFF_GPIOHS_OUTPOT_XOR  0x0040	/* (RW) Output XOR (invert) */

#define GPIOHS_MAX_PINNO        32


/*
 *  GPIO
 */
#define TADR_GPIO_BASE      (GPIO_BASE_ADDR)
#define TOFF_GPIO_DATA_OUTOUT     0x0000	/* (RW) Data (output) registers */
#define TOFF_GPIO_DIRECTION       0x0004	/* (RW) Data direction registers */
#define TOFF_GPIO_SOURCE          0x0008	/* (RW) Data source registers */
#define TOFF_GPIO_INT_ENABLE      0x0030	/* (RW) Interrupt enable/disable registers */
#define TOFF_GPIO_INT_MASK        0x0034	/* (RW) Interrupt mask registers */
#define TOFF_GPIO_INT_LEVEL       0x0038	/* (RW) Interrupt level registers */
#define TOFF_GPIO_INT_POLARITY    0x003C	/* (RW) Interrupt polarity registers */
#define TOFF_GPIO_INT_STATUS      0x0040	/* (RW) Interrupt status registers */
#define TOFF_GPIO_INT_STATUS_RAW  0x0044	/* (RW) Raw interrupt status registers */
#define TOFF_GPIO_INT_DEBOUNCE    0x0048	/* (RW) Interrupt debounce registers */
#define TOFF_GPIO_INT_CLEAR       0x004C	/* (RW) Registers for clearing interrupts */
#define TOFF_GPIO_DATA_INPUT      0x0050	/* (RW) External port (data input) registers */
#define TOFF_GPIO_SYNC_LEVEL      0x0060	/* (RW) Sync level registers */
#define TOFF_GPIO_ID_CODE         0x0064	/* (R)  ID code */
#define TOFF_GPIO_INT_BOTHEDGE    0x0068	/* (RW) Interrupt both edge type */

#define GPIO_MAX_PINNO            8


/*
 *  UART
 */
#define TADR_UART1_BASE     (UART1_BASE_ADDR)
#define TADR_UART2_BASE     (UART1_BASE_ADDR + 0x10000)
#define TADR_UART3_BASE     (UART1_BASE_ADDR + 0x20000)
#define TOFF_UART_RBR       0x0000
#define TOFF_UART_DLL       0x0000
#define TOFF_UART_THR       0x0000
#define TOFF_UART_DLH       0x0004
#define TOFF_UART_IER       0x0004
  #define UART_IER_RIE        0x000000001
  #define UART_IER_TIE        0x000000002
  #define UART_IER_THRE       0x000000080
#define TOFF_UART_FCR       0x0008
#define TOFF_UART_IIR       0x0008
  #define UART_IIR_SEND       0x000000002
  #define UART_IIR_RECEIVE    0x000000004
  #define UART_IIR_CTIMEOUT   0x00000000C
#define TOFF_UART_LCR       0x000C
  #define UART_LCR_DLN        0x000000003
  #define UART_LCR_STB        0x000000004
  #define UART_LCR_PARITY     0x000000008
  #define UART_LCR_PEVEN      0x000000010
  #define UART_LCR_DMD        0x000000080
#define TOFF_UART_MCR       0x0010
#define TOFF_UART_LSR       0x0014
  #define UART_LSR_RFL        0x000000001
  #define UART_LSR_TFL        0x000000020
#define TOFF_UART_MSR       0x0018
#define TOFF_UART_SCR       0x001C
#define TOFF_UART_LPDLL     0x0020
#define TOFF_UART_LPDLH     0x0024

#define TOFF_UART_SRBR      0x0030
#define TOFF_UART_STHR      0x0030

#define TOFF_UART_FAR       0x0070
#define TOFF_UART_TFR       0x0074
#define TOFF_UART_RFW       0x0078
#define TOFF_UART_USR       0x007C
#define TOFF_UART_TFL       0x0080
#define TOFF_UART_RFL       0x0084
#define TOFF_UART_SRR       0x0088
#define TOFF_UART_SRTS      0x008C
#define TOFF_UART_SBCR      0x0090
#define TOFF_UART_SDMAM     0x0094
#define TOFF_UART_SFE       0x0098
#define TOFF_UART_SRT       0x009C
#define TOFF_UART_STET      0x00A0
#define TOFF_UART_HTX       0x00A4
#define TOFF_UART_DMASA     0x00A8
#define TOFF_UART_TCR       0x00AC
#define TOFF_UART_DE_EN     0x00B0
#define TOFF_UART_RE_EN     0x00B4
#define TOFF_UART_DET       0x00B8
#define TOFF_UART_TAT       0x00BC
#define TOFF_UART_DLF       0x00C0
#define TOFF_UART_RAR       0x00C4
#define TOFF_UART_TAR       0x00C8
#define TOFF_UART_LCR_EXT   0x00CC
#define TOFF_UART_CPR       0x00F4
#define TOFF_UART_UCV       0x00F8
#define TOFF_UART_CTR       0x00FC


/*
 *  I2S
 */
#define TADR_I2S0_BASE      (I2S0_BASE_ADDR)
#define TADR_I2S1_BASE      (I2S0_BASE_ADDR+0x10000)
#define TADR_I2S2_BASE      (I2S0_BASE_ADDR+0x20000)
#define TOFF_I2S_IER            0x0000		/* (RW) I2S Enable Register */
#define TOFF_I2S_IRER           0x0004		/* (RW) I2S Receiver Block Enable Register */
#define TOFF_I2S_ITER           0x0008		/* (RW) I2S Transmitter Block Enable Register */
#define TOFF_I2S_CER            0x000C		/* (RW) Clock Enable Register */
  #define I2S_CER_CLKEN             0x00000001	/* clock generation enable/disable */
#define TOFF_I2S_CCR            0x0010		/* (RW) Clock Configuration Register */
  #define I2S_CCR_CLK_GATE          0x00000007	/* program  the gating of sclk */
  /* * 0x0 for clock gating is diable,
     * 0x1 for gating after 12 sclk cycles
     * 0x2 for gating after 16 sclk cycles
     * 0x3 for gating after 20 sclk cycles
     * 0x4 for gating after 24 sclk cycles
     */
  #define I2S_CCR_CLK_WORD_SIZE     0x00000018	/* the number of sclk cycles for which the word select line stayd in the left aligned or right aligned mode. */
  #define I2S_CCR_ALIGN_MODE        0x000000E0	/* alignment mode setting. */
  /* * 0x1 for standard i2s format
     * 0x2 for right aligned format
     * 0x4 for left aligned format
     */
  #define I2S_CCR_DMA_TX_EN         0x00000100	/* DMA transmit enable control */
  #define I2S_CCR_DMA_RX_EN         0x00000200	/* DMA receive enable control */
  #define I2S_CCR_DMA_DIVIED_16     0x00000400	/* split 32bit data to two 16 bit data and filled in left and right channel. Used with dma_tx_en or dma_rx_en */
  #define I2S_CCR_SIGN_EXPAND_EN    0x00000800
#define TOFF_I2S_RXFFR          0x0014		/* (RW) Receiver Block FIFO Reset Register */
#define TOFF_I2S_TXFFR          0x0018		/* (RW) Transmitter Block FIFO Reset Register */
#define TOFF_I2S_CHANNEL        0x0020		/* (RW) channel 0x40 * 4 */
#define TOFF_I2S_RXDMA          0x01C0		/* (RW) Receiver Block DMA Register */
#define TOFF_I2S_RRXDMA         0x01C4		/* (RW) Reset Receiver Block DMA Register */
#define TOFF_I2S_TXDMA          0x01C8		/* (RW) Transmitter Block DMA Register */
#define TOFF_I2S_RTXDMA         0x01CC		/* (RW) Reset Transmitter Block DMA Register */
#define TOFF_I2S_COMP_PARAM_2   0x01F0		/* (RW) Component Parameter Register 2 */
#define TOFF_I2S_COMP_PARAM_1   0x01F4		/* (RW) Component Parameter Register 1 */
#define TOFF_I2S_COMP_VERSION   0x01F8		/* (RW) I2S Component Version Register */
#define TOFF_I2S_COMP_TYPE      0x01FC		/* (RW) I2S Component Type Register */

/*
 *  I2S CHANNEL WINDOW
 */
#define TOFF_I2SC_LEFT_RXTX     0x0000		/* (RW) Left  Receive or Left Transmit Register */
#define TOFF_I2SC_RIGHT_RXTX    0x0004		/* (RW) Right Receive or Right Transmit Register */
#define TOFF_I2SC_RER           0x0008		/* (RW) Receive Enable Register */
  #define I2SC_RER_RXCHENX          0x00000001	/* receive channel enable/disable */
#define TOFF_I2SC_TER           0x000C		/* (RW) Transmit Enable Register */
  #define I2SC_TER_TXCHENX          0x00000001	/* transmit channel enable/disable */
#define TOFF_I2SC_RCR           0x0010		/* (RW) Receive Configuration Register */
  #define I2SC_RCR_WLEN             0x00000007	/* program desired data resolution of receiver */
#define TOFF_I2SC_TCR           0x0014		/* (RW) Transmit Configuration Register */
  #define I2SC_TCR_WLEN             0x00000007	/* program desired data resolution of transmitter */
  /* * 0x0 for ignore the word length
     * 0x1 for 12-bit data resolution of the receiver/transmitter,
     * 0x2 for 16-bit data resolution of the receiver/transmitter,
     * 0x3 for 20-bit data resolution of the receiver/transmitter,
     * 0x4 for 24-bit data resolution of the receiver/transmitter,
     * 0x5 for 32-bit data resolution of the receiver/transmitter
     */
#define TOFF_I2SC_ISR           0x0018		/* (RW) Interrupt Status Register */
  #define I2SC_ISR_RXDA             0x00000001	/* status of receiver data avaliable interrupt */
  #define I2SC_ISR_RXFO             0x00000002	/* status of data overrun interrupt for rx channel */
  #define I2SC_ISR_TXFE             0x00000010	/* status of transmit empty triger interrupt */
  #define I2SC_ISR_TXFO             0x00000020	/* status of data overrun interrupt for the TX channel */
#define TOFF_I2SC_IMR           0x001C		/* (RW) Interrupt Mask Register */
  #define I2SC_IMR_RXDAM            0x00000001	/* mask RX FIFO data available interrupt */
  #define I2SC_IMR_RXFOM            0x00000002	/* mask RX FIFO overrun interrupt */
  #define I2SC_IMR_TXFEM            0x00000010	/* mask TX FIFO empty interrupt */
  #define I2SC_IMR_TXFOM            0x00000020	/* mask TX FIFO overrun interrupt */
#define TOFF_I2SC_ROR           0x0020		/* (RW) Receive Overrun Register */
  #define I2CS_ROR_RXCHO            0x00000001	/* read this bit to clear RX FIFO data overrun interrupt */
#define TOFF_I2SC_TOR           0x0024		/* (RW) Transmit Overrun Register */
  #define I2CS_TOR_TXCHO            0x00000001	/* read this bit to clear TX FIFO data overrun interrupt */
#define TOFF_I2SC_RFCR          0x0028		/* (RW) Receive FIFO Configuration Register */
  #define I2SC_RFCR_RXCHDT          0x0000000F	/* program the trigger level in the RX FIFO at which the receiver data available interrupt generate */
  /* * 0x0 for interrupt trigger when FIFO level is 1,
     * 0x2 for interrupt trigger when FIFO level is 2,
     * 0x3 for interrupt trigger when FIFO level is 4,
     * 0x4 for interrupt trigger when FIFO level is 5,
     * 0x5 for interrupt trigger when FIFO level is 6,
     * 0x6 for interrupt trigger when FIFO level is 7,
     * 0x7 for interrupt trigger when FIFO level is 8,
     * 0x8 for interrupt trigger when FIFO level is 9,
     * 0x9 for interrupt trigger when FIFO level is 10,
     * 0xa for interrupt trigger when FIFO level is 11,
     * 0xb for interrupt trigger when FIFO level is 12,
     * 0xc for interrupt trigger when FIFO level is 13,
     * 0xd for interrupt trigger when FIFO level is 14,
     * 0xe for interrupt trigger when FIFO level is 15,
     * 0xf for interrupt trigger when FIFO level is 16
     */
#define TOFF_I2SC_TFCR          0x002C		/* (RW) Transmit FIFO Configuration Register */
  #define I2CS_TFCR_TXCHET          0x0000000F	/* program the trigger level in the TX FIFO at which the receiver data available interrupt generate */
  /* * 0x0 for interrupt trigger when FIFO level is 1,
     * 0x2 for interrupt trigger when FIFO level is 2,
     * 0x3 for interrupt trigger when FIFO level is 4,
     * 0x4 for interrupt trigger when FIFO level is 5,
     * 0x5 for interrupt trigger when FIFO level is 6,
     * 0x6 for interrupt trigger when FIFO level is 7,
     * 0x7 for interrupt trigger when FIFO level is 8,
     * 0x8 for interrupt trigger when FIFO level is 9,
     * 0x9 for interrupt trigger when FIFO level is 10,
     * 0xa for interrupt trigger when FIFO level is 11,
     * 0xb for interrupt trigger when FIFO level is 12,
     * 0xc for interrupt trigger when FIFO level is 13,
     * 0xd for interrupt trigger when FIFO level is 14,
     * 0xe for interrupt trigger when FIFO level is 15,
     * 0xf for interrupt trigger when FIFO level is 16
     */
#define TOFF_I2SC_RFF           0x0030		/* (RW) Receive FIFO Flush Register */
  #define I2SC_RFF_RXCHFR           0x00000001	/* receiver channel FIFO reset */
#define TOFF_I2SC_TFF           0x0034		/* (RW) Transmit FIFO Flush Register */
  #define I2SC_TFF_RTXCHFR          0x00000001	/* transmit channel FIFO reset */

#define I2S_CHANNEL_WINDOW_SIZE 0x0040
#define NUM_I2S_CHANNEL         4


/*
 *  I2C
 */
#define TADR_I2C0_BASE      (I2C0_BASE_ADDR)
#define TADR_I2C1_BASE      (I2C0_BASE_ADDR+0x10000)
#define TADR_I2C2_BASE      (I2C0_BASE_ADDR+0x20000)
#define TOFF_I2C_CON            0x0000		/* (RW) I2C Control Register */
  #define I2C_CON_MASTER_MODE           0x00000001
  #define I2C_CON_SPEED_MASK            0x00000006
  #define I2C_CON_10BITADDR_SLAVE       0x00000008
  #define I2C_CON_RESTART_EN            0x00000020
  #define I2C_CON_SLAVE_DISABLE         0x00000040
  #define I2C_CON_STOP_DET_IFADDRESSED  0x00000080
  #define I2C_CON_TX_EMPTY_CTRL         0x00000100
#define TOFF_I2C_TAR            0x0004		/* (RW) I2C Target Address Register */
  #define I2C_TAR_ADDRESS_MASK          0x000003FF
  #define I2C_TAR_GC_OR_START           0x00000400
  #define I2C_TAR_SPECIAL               0x00000800
  #define I2C_TAR_10BITADDR_MASTER      0x00001000
#define TOFF_I2C_SAR            0x0008		/* (RW) I2C Slave Address Register */
  #define I2C_SAR_ADDRESS_MASK          0x000003FF
#define TOFF_I2C_DATA_CMD       0x0010		/* (RW) I2C Data Buffer and Command Register */
  #define I2C_DATA_CMD_CMD              0x00000100
  #define I2C_DATA_CMD_DATA_MASK        0x000000FF
#define TOFF_I2C_SS_SCL_HCNT    0x0014		/* (RW) I2C Standard Speed Clock SCL High Count Register */
#define TOFF_I2C_SS_SCL_LCNT    0x0018		/* (RW) I2C Standard Speed Clock SCL Low Count Register */
#define TOFF_I2C_INTR_STAT      0x002C		/* (RW) I2C Interrupt Status Register */
  #define I2C_INTR_STAT_RX_UNDER        0x00000001
  #define I2C_INTR_STAT_RX_OVER         0x00000002
  #define I2C_INTR_STAT_RX_FULL         0x00000004
  #define I2C_INTR_STAT_TX_OVER         0x00000008
  #define I2C_INTR_STAT_TX_EMPTY        0x00000010
  #define I2C_INTR_STAT_RD_REQ          0x00000020
  #define I2C_INTR_STAT_TX_ABRT         0x00000040
  #define I2C_INTR_STAT_RX_DONE         0x00000080
  #define I2C_INTR_STAT_ACTIVITY        0x00000100
  #define I2C_INTR_STAT_STOP_DET        0x00000200
  #define I2C_INTR_STAT_START_DET       0x00000400
  #define I2C_INTR_STAT_GEN_CALL        0x00000800
#define TOFF_I2C_INTR_MASK      0x0030		/* (RW) I2C Interrupt Mask Register */
  #define I2C_INTR_MASK_RX_UNDER        0x00000001
  #define I2C_INTR_MASK_RX_OVER         0x00000002
  #define I2C_INTR_MASK_RX_FULL         0x00000004
  #define I2C_INTR_MASK_TX_OVER         0x00000008
  #define I2C_INTR_MASK_TX_EMPTY        0x00000010
  #define I2C_INTR_MASK_RD_REQ          0x00000020
  #define I2C_INTR_MASK_TX_ABRT         0x00000040
  #define I2C_INTR_MASK_RX_DONE         0x00000080
  #define I2C_INTR_MASK_ACTIVITY        0x00000100
  #define I2C_INTR_MASK_STOP_DET        0x00000200
  #define I2C_INTR_MASK_START_DET       0x00000400
  #define I2C_INTR_MASK_GEN_CALL        0x00000800
#define TOFF_I2C_RAW_INTR_STAT  0x0034		/* (RW) I2C Raw Interrupt Status Register */
  #define I2C_RAW_INTR_MASK_RX_UNDER    0x00000001
  #define I2C_RAW_INTR_MASK_RX_OVER     0x00000002
  #define I2C_RAW_INTR_MASK_RX_FULL     0x00000004
  #define I2C_RAW_INTR_MASK_TX_OVER     0x00000008
  #define I2C_RAW_INTR_MASK_TX_EMPTY    0x00000010
  #define I2C_RAW_INTR_MASK_RD_REQ      0x00000020
  #define I2C_RAW_INTR_MASK_TX_ABRT     0x00000040
  #define I2C_RAW_INTR_MASK_RX_DONE     0x00000080
  #define I2C_RAW_INTR_MASK_ACTIVITY    0x00000100
  #define I2C_RAW_INTR_MASK_STOP_DET    0x00000200
  #define I2C_RAW_INTR_MASK_START_DET   0x00000400
  #define I2C_RAW_INTR_MASK_GEN_CALL    0x00000800
#define TOFF_I2C_RX_TL          0x0038		/* (RW) I2C Receive FIFO Threshold Register */
  #define I2C_RX_TL_VALUE_MASK          0x00000007
#define TOFF_I2C_TX_TL          0x003C		/* (RW) I2C Transmit FIFO Threshold Register */
  #define I2C_TX_TL_VALUE_MASK          0x00000007
#define TOFF_I2C_CLR_INTR       0x0040		/* (RW) I2C Clear Combined and Individual Interrupt Register */
  #define I2C_CLR_INTR_CLR              0x00000001
#define TOFF_I2C_CLR_RX_UNDER   0x0044		/* (RW) I2C Clear RX_UNDER Interrupt Register */
  #define I2C_CLR_RX_UNDER_CLR          0x00000001
#define TOFF_I2C_CLR_RX_OVER    0x0048		/* (RW) I2C Clear RX_OVER Interrupt Register */
  #define I2C_CLR_RX_OVER_CLR           0x00000001
#define TOFF_I2C_CLR_TX_OVER    0x004C		/* (RW) I2C Clear TX_OVER Interrupt Register */
  #define I2C_CLR_TX_OVER_CLR           0x00000001
#define TOFF_I2C_CLR_RD_REQ     0x0050		/* (RW) I2C Clear RD_REQ Interrupt Register */
  #define I2C_CLR_RD_REQ_CLR            0x00000001
#define TOFF_I2C_CLR_TX_ABRT    0x0054		/* (RW) I2C Clear TX_ABRT Interrupt Register */
  #define I2C_CLR_TX_ABRT_CLR           0x00000001
#define TOFF_I2C_CLR_RX_DONE    0x0058		/* (RW) I2C Clear RX_DONE Interrupt Register */
  #define I2C_CLR_RX_DONE_CLR           0x00000001
#define TOFF_I2C_CLR_ACTIVITY   0x005C		/* (RW) I2C Clear ACTIVITY Interrupt Register */
  #define I2C_CLR_ACTIVITY_CLR          0x00000001
#define TOFF_I2C_CLR_STOP_DET   0x0060		/* (RW) I2C Clear STOP_DET Interrupt Register */
  #define I2C_CLR_STOP_DET_CLR          0x00000001
#define TOFF_I2C_CLR_START_DET  0x0064		/* (RW) I2C Clear START_DET Interrupt Register */
  #define I2C_CLR_START_DET_CLR         0x00000001
#define TOFF_I2C_CLR_GEN_CALL   0x0068		/* (RW) I2C Clear GEN_CALL Interrupt Register */
  #define I2C_CLR_GEN_CALL_CLR          0x00000001
#define TOFF_I2C_ENABLE         0x006C		/* (RW) I2C Enable Register */
  #define I2C_ENABLE_ENABLE             0x00000001
  #define I2C_ENABLE_ABORT              0x00000002
  #define I2C_ENABLE_TX_CMD_BLOCK       0x00000004
#define TOFF_I2C_STATUS         0x0070		/* (RW) I2C Status Register */
  #define I2C_STATUS_ACTIVITY           0x00000001
  #define I2C_STATUS_TFNF               0x00000002
  #define I2C_STATUS_TFE                0x00000004
  #define I2C_STATUS_RFNE               0x00000008
  #define I2C_STATUS_RFF                0x00000010
  #define I2C_STATUS_MST_ACTIVITY       0x00000020
  #define I2C_STATUS_SLV_ACTIVITY       0x00000040
#define TOFF_I2C_TXFLR          0x0074		/* (RW) I2C Transmit FIFO Level Register */
  #define I2C_TXFLR_VALUE_MASK          0x00000007
#define TOFF_I2C_RXFLR          0x0078		/* (RW) I2C Receive FIFO Level Register */
  #define I2C_RXFLR_VALUE_MASK          0x00000007
#define TOFF_I2C_SDA_HOLD       0x007C		/* (RW) I2C SDA Hold Time Length Register */
  #define I2C_SDA_HOLD_TX_MASK          0x0000FFFF
  #define I2C_SDA_HOLD_RX_MASK          0x00FF0000
#define TOFF_I2C_TX_ABRT_SOURCE 0x0080		/* (RW) I2C Transmit Abort Source Register */
  #define I2C_TX_ABRT_SOURCE_7B_ADDR_NOACK   0x00000001
  #define I2C_TX_ABRT_SOURCE_10B_ADDR1_NOACK 0x00000002
  #define I2C_TX_ABRT_SOURCE_10B_ADDR2_NOACK 0x00000004
  #define I2C_TX_ABRT_SOURCE_TXDATA_NOACK    0x00000008
  #define I2C_TX_ABRT_SOURCE_GCALL_NOACK     0x00000010
  #define I2C_TX_ABRT_SOURCE_GCALL_READ      0x00000020
  #define I2C_TX_ABRT_SOURCE_HS_ACKDET       0x00000040
  #define I2C_TX_ABRT_SOURCE_SBYTE_ACKDET    0x00000080
  #define I2C_TX_ABRT_SOURCE_HS_NORSTRT      0x00000100
  #define I2C_TX_ABRT_SOURCE_SBYTE_NORSTRT   0x00000200
  #define I2C_TX_ABRT_SOURCE_10B_RD_NORSTRT  0x00000400
  #define I2C_TX_ABRT_SOURCE_MASTER_DIS      0x00000800
  #define I2C_TX_ABRT_SOURCE_MST_ARBLOST     0x00001000
  #define I2C_TX_ABRT_SOURCE_SLVFLUSH_TXFIFO 0x00002000
  #define I2C_TX_ABRT_SOURCE_SLV_ARBLOST     0x00004000
  #define I2C_TX_ABRT_SOURCE_SLVRD_INTX      0x00008000
  #define I2C_TX_ABRT_SOURCE_USER_ABRT       0x00010000
#define TOFF_I2C_DMA_CR         0x0088		/* (RW) I2C DMA Control Register */
  #define I2C_DMA_CR_RDMAE              0x00000001
  #define I2C_DMA_CR_TDMAE              0x00000002
#define TOFF_I2C_DMA_TDLR       0x008C		/* (RW) I2C DMA Transmit Data Level Register */
  #define I2C_DMA_TDLR_VALUE_MASK       0x00000007
#define TOFF_I2C_DMA_RDLR       0x0090		/* (RW) I2C DMA Receive Data Level Register */
  #define I2C_DMA_RDLR_VALUE_MASK       0x00000007
#define TOFF_I2C_SDA_SETUP      0x0094		/* (RW) I2C SDA Setup Register */
  #define I2C_SDA_SETUP_VALUE_MASK      0x000000FF
#define TOFF_I2C_GENERAL_CALL   0x0098		/* (RW) I2C ACK General Call Register */
  #define I2C_ACK_GENERAL_CALL_ENABLE   0x00000001
#define TOFF_I2C_ENABLE_STATUS  0x009C		/* (RW) I2C Enable Status Register */
  #define I2C_ENABLE_STATUS_IC_ENABLE        0x00000001
  #define I2C_ENABLE_STATUS_SLV_DIS_BUSY     0x00000002
  #define I2C_ENABLE_STATUS_SLV_RX_DATA_LOST 0x00000004
#define TOFF_I2C_FS_SPKLEN      0x00A0		/* (RW) I2C SS, FS or FM+ spike suppression limit */
  #define I2C_FS_SPKLEN_VALUE_MASK      0x000000FF
#define TOFF_I2C_COMP_PARAM_1   0x00F4		/* (RW) I2C Component Parameter Register 1 */
  #define I2C_COMP_PARAM1_APB_DATA_WIDTH     0x00000003
  #define I2C_COMP_PARAM1_MAX_SPEED_MODE     0x0000000C
  #define I2C_COMP_PARAM1_HC_COUNT_VALUES    0x00000010
  #define I2C_COMP_PARAM1_INTR_IO            0x00000020
  #define I2C_COMP_PARAM1_HAS_DMA            0x00000040
  #define I2C_COMP_PARAM1_ENCODED_PARAMS     0x00000080
  #define I2C_COMP_PARAM1_RX_BUFFER_DEPTH    0x0000FF00
  #define I2C_COMP_PARAM1_TX_BUFFER_DEPTH    0x00FF0000
#define TOFF_I2C_COMP_VERSION   0x00F8		/* (RW) I2C Component Version Register */
#define TOFF_I2C_COMP_TYPE      0x00FC		/* (RW) I2C Component Type Register */


/*
 *  FPIOA
 */
#define TADR_FPIOA_BASE     (FPIOA_BASE_ADDR)
#define FPIOA_NUM_IO        (48)
#define TOFF_FPIOA_IO       0x0000
  #define FPIOA_CH_SEL        0x000000FF	/* Channel select from 256 input. */
  #define FPIOA_DS            0x00000F00	/* Driving selector. */
  #define FPIOA_OE_EN         0x00001000	/* Static output enable, will AND with OE_INV. */
  #define FPIOA_OE_INV        0x00002000	/* Invert output enable. */
  #define FPIOA_DO_SEL        0x00004000	/* Data output select: 0 for DO, 1 for OE. */
  #define FPIOA_DO_INV        0x00008000	/* Invert the result of data output select (DO_SEL). */
  #define FPIOA_PU            0x00010000	/* Pull up enable. 0 for nothing, 1 for pull up. */
  #define FPIOA_PD            0x00020000	/* Pull down enable. 0 for nothing, 1 for pull down. */
  #define FPIOA_SL            0x00080000	/* Slew rate control enable. */
  #define FPIOA_IE_EN         0x00100000	/* Static input enable, will AND with IE_INV. */
  #define FPIOA_IE_INV        0x00200000	/* Invert input enable. */
  #define FPIOA_DI_INV        0x00400000	/* Invert Data input. */
  #define FPIOA_ST            0x00800000	/* Schmitt trigger. */
  #define FPIOA_PAD_DI        0x80000000	/* Read current IO's data input. */
#define TOFF_FPIOA_TIE_EN   (FPIOA_NUM_IO*4)
#define TOFF_FPIOA_TIE_VAL  (TOFF_FPIOA_TIE_EN+(FUNC_MAX/8))


/*
 *  TIMER
 */
#define TADR_TIMER0_BASE    (TIMER0_BASE_ADDR)
#define TADR_TIMER1_BASE    (TIMER0_BASE_ADDR+0x10000)
#define TADR_TIMER2_BASE    (TIMER0_BASE_ADDR+0x20000)
#define TOFF_TIMER_CHANNEL        0x0000	/* (RW) TIMER_N Register 20bytes * 4 */
#define TOFF_TIMER_INT_STATR      0x00A0	/* (RW) TIMER Interrupt Status Register */
#define TOFF_TIMER_EOI            0x00A4	/* (RW) TIMER Interrupt Clear Register */
#define TOFF_TIMER_RAW_INTR_STAT  0x00A8	/* (RW) TIMER Raw Interrupt Status Register */
#define TOFF_TIMER_COMP_VERSION   0x00AC	/* (RW) TIMER Component Version Register */
#define TOFF_TIMER_LOAD_COUNT2    0x00B0	/* (RW) TIMER_N Load Count2 Register 4 *4 */

/*
 *  TIMER CHANNEL WINDOW
 */
#define TOFF_TIMERC_LOAD_COUNT    0x0000	/* (RW) TIMER_N Load Count Register */
#define TOFF_TIMERC_CURRENT_VALUE 0x0004	/* (RW) TIMER_N Current Value Register */
#define TOFF_TIMERC_CONTROL       0x0008	/* (RW) TIMER_N Control Register */
  #define TIMERC_CR_ENABLE          0x00000001
  #define TIMERC_CR_MODE_MASK       0x00000002
  #define TIMERC_CR_FREE_MODE       0x00000000
  #define TIMERC_CR_USER_MODE       0x00000002
  #define TIMERC_CR_INTERRUPT_MASK  0x00000004
  #define TIMERC_CR_PWM_ENABLE      0x00000008
#define TOFF_TIMERC_EOI           0x000C	/* (RW) TIMER_N Interrupt Clear Register */
#define TOFF_TIMERC_INTR_STAT     0x0010	/* (RW) TIMER_N Interrupt Status Register */

#define TIMER_CHANNEL_WINDOW_SIZE 0x0014
#define NUM_TIMER_CHANNEL         4


/*
 *  WDT
 */
#define TADR_WDT0_BASE      (WDT0_BASE_ADDR)
#define TADR_WDT1_BASE      (WDT0_BASE_ADDR+0x10000)
#define TOFF_WDT_CR         0x0000		/* (RW) WDT Control Register */
  #define WDT_CR_ENABLE         0x00000001
  #define WDT_CR_RMOD_MASK      0x00000002
  #define WDT_CR_RMOD_RESET     0x00000000
  #define WDT_CR_RMOD_INTERRUPT 0x00000002
  #define WDT_CR_RPL_MASK       0x0000001C
#define TOFF_WDT_TORR       0x0004		/* (RW) WDT Timeout Range Register */
  #define WDT_TORR_TOP_MASK     0x000000FF
#define TOFF_WDT_CCVR       0x0008		/* (RW) WDT Current Counter Value Register */
#define TOFF_WDT_CRR        0x000C		/* (RW) WDT Counter Restart Register */
  #define WDT_CRR_MASK          0x00000076
#define TOFF_WDT_STAT       0x0010		/* (RW) WDT Interrupt Status Register */
#define TOFF_WDT_EOI        0x0014		/* (RW) WDT Interrupt Clear Register */
#define TOFF_WDT_PROT_LEVEL 0x001C		/* (RW) WDT Protection level Register */
  #define WDT_PROT_LEVEL_MASK   0x00000007
#define TOFF_WDT_CMP_PARAM5 0x00E4		/* (RW) WDT Component Parameters Register 5 */
#define TOFF_WDT_CMP_PARAM4 0x00E8		/* (RW) WDT Component Parameters Register 4 */
#define TOFF_WDT_CMP_PARAM3 0x00EC		/* (RW) WDT Component Parameters Register 3 */
#define TOFF_WDT_CMP_PARAM2 0x00F0		/* (RW) WDT Component Parameters Register 2 */
#define TOFF_WDT_CMP_PARAM1 0x00F4		/* (RW) WDT Component Parameters Register 1 */
  #define WDT_COMP_PARAM_1_WDT_ALWAYS_EN_MASK      0x00000001
  #define WDT_COMP_PARAM_1_WDT_DFLT_RMOD_MASK      0x00000002
  #define WDT_COMP_PARAM_1_WDT_DUAL_TOP_MASK       0x00000004
  #define WDT_COMP_PARAM_1_WDT_HC_RMOD_MASK        0x00000008
  #define WDT_COMP_PARAM_1_WDT_HC_RPL_MASK         0x00000010
  #define WDT_COMP_PARAM_1_WDT_HC_TOP_MASK         0x00000020
  #define WDT_COMP_PARAM_1_WDT_USE_FIX_TOP_MASK    0x00000040
  #define WDT_COMP_PARAM_1_WDT_PAUSE_MASK          0x00000080
  #define WDT_COMP_PARAM_1_APB_DATA_WIDTH_MASK     0x00000300
  #define WDT_COMP_PARAM_1_WDT_DFLT_RPL_MASK       0x00001C00
  #define WDT_COMP_PARAM_1_WDT_DFLT_TOP_MASK       0x000F0000
  #define WDT_COMP_PARAM_1_WDT_DFLT_TOP_INIT_MASK  0x00F00000
  #define WDT_COMP_PARAM_1_WDT_CNT_WIDTH_MASK      0x1F000000
#define TOFF_WDT_CMP_VER    0x00F8		/* (RW) WDT Component Version Register */
#define TOFF_WDT_CMP_TYPE   0x00FC		/* (RW) WDT Component Type Register */


/*
 *  SYSCTL
 */
#define TADR_SYSCTL_BASE    (SYSCTL_BASE_ADDR)
#define TOFF_SYSCTL_GIT_ID      0x0000			/* (RW) No. 0: Git short commit id */
#define TOFF_SYSCTL_CLK_FREQ    0x0004			/* (RW) No. 1: System clock base frequency */
#define TOFF_SYSCTL_PLL0        0x0008			/* (RW) No. 2: PLL0 controller */
  #define SYSCTL_PLL_CLKR0              0x0000000F	/* clkr0 : 4 */
  #define SYSCTL_PLL_CLKF0              0x000003F0	/* clkf0 : 6 */
  #define SYSCTL_PLL_CLKOD0             0x00003C00	/* clkod0 : 4 */
  #define SYSCTL_PLL_BWADJ0             0x000FC000	/* bwadj0 : 6 */
  #define SYSCTL_PLL_RESET0             0x00100000	/* pll_reset0 : 1 */
  #define SYSCTL_PLL_PWRD0              0x00200000	/* pll_pwrd0 : 1 */
  #define SYSCTL_PLL_INTFB0             0x00400000	/* pll_intfb0 : 1 */
  #define SYSCTL_PLL_BYPASS0            0x00800000	/* pll_bypass0 : 1 */
  #define SYSCTL_PLL_TEST0              0x01000000	/* pll_test0 : 1 */
  #define SYSCTL_PLL_OUT_EN0            0x02000000	/* pll_out_en0 : 1 */
  #define SYSCTL_PLL_TEST_EN            0x04000000	/* pll_test_en : 1 */
#define TOFF_SYSCTL_PLL1        0x000C			/* (RW) No. 3: PLL1 controller */
  #define SYSCTL_PLL_CLKR1              0x0000000F	/* clkr1 : 4 */
  #define SYSCTL_PLL_CLKF1              0x000003F0	/* clkf1 : 6 */
  #define SYSCTL_PLL_CLKOD1             0x00003C00	/* clkod1 : 4 */
  #define SYSCTL_PLL_BWADJ1             0x000FC000	/* bwadj1 : 6 */
  #define SYSCTL_PLL_RESET1             0x00100000	/* pll_reset1 : 1 */
  #define SYSCTL_PLL_PWRD1              0x00200000	/* pll_pwrd1 : 1 */
  #define SYSCTL_PLL_INTFB1             0x00400000	/* pll_intfb1 : 1 */
  #define SYSCTL_PLL_BYPASS1            0x00800000	/* pll_bypass1 : 1 */
  #define SYSCTL_PLL_TEST1              0x01000000	/* pll_test1 : 1 */
  #define SYSCTL_PLL_OUT_EN1            0x02000000	/* pll_out_en1 : 1 */
#define TOFF_SYSCTL_PLL2        0x0010			/* (RW) No. 4: PLL2 controller */
  #define SYSCTL_PLL_CLKR2              0x0000000F	/* clkr2 : 4 */
  #define SYSCTL_PLL_CLKF2              0x000003F0	/* clkf2 : 6 */
  #define SYSCTL_PLL_CLKOD2             0x00003C00	/* clkod2 : 4 */
  #define SYSCTL_PLL_BWADJ2             0x000FC000	/* bwadj2 : 6 */
  #define SYSCTL_PLL_RESET2             0x00100000	/* pll_reset2 : 1 */
  #define SYSCTL_PLL_PWRD2              0x00200000	/* pll_pwrd2 : 1 */
  #define SYSCTL_PLL_INTFB2             0x00400000	/* pll_intfb2 : 1 */
  #define SYSCTL_PLL_BYPASS2            0x00800000	/* pll_bypass2 : 1 */
  #define SYSCTL_PLL_TEST2              0x01000000	/* pll_test2 : 1 */
  #define SYSCTL_PLL_OUT_EN2            0x02000000	/* pll_out_en2 : 1 */
  #define SYSCTL_PLL_CKIN_SEL2          0x0C000000	/* pll_ckin_sel2 : 2 */
#define TOFF_SYSCTL_PLL_LOCK    0x0018			/* (RW) No. 6: PLL lock tester */
  #define SYSCTL_PLL_LOCK_LOCK0         0x00000003	/* pll_lock0 : 2 */
  #define SYSCTL_PLL_LOCK_SLIP_CLEAR0   0x00000004	/* pll_slip_clear0 : 1 */
  #define SYSCTL_PLL_LOCK_TEST_CLK_OUT0 0x00000008	/* test_clk_out0 : 1 */
  #define SYSCTL_PLL_LOCK_LOCK1         0x00000300	/* pll_lock1 : 2 */
  #define SYSCTL_PLL_LOCK_SLIP_CLEAR1   0x00000400	/* pll_slip_clear1 : 1 */
  #define SYSCTL_PLL_LOCK_TEST_CLK_OUT1 0x00000800	/* test_clk_out1 : 1 */
  #define SYSCTL_PLL_LOCK_LOCK2         0x00030000  /* pll_lock2 : 2 */
  #define SYSCTL_PLL_LOCK_SLIP_CLEAR2   0x00040000	/* pll_slip_clear2 : 1 */
  #define SYSCTL_PLL_LOCK_TEST_CLK_OUT2 0x00080000	/* test_clk_out2 : 1 */
#define TOFF_SYSCTL_ROM_ERROR   0x001C			/* (RW) No. 7: AXI ROM detector */
  #define SYSCTL_ROM_ERROR_NUL_ERROR    0x00000001	/* rom_mul_error : 1 */
  #define SYSCTL_ROM_ERROR_ONE_ERROR    0x00000002	/* rom_one_error : 1 */
#define TOFF_CLK_SEL0           0x0020			/* (RW) No. 8: Clock select controller0 */
  #define SYSCTL_CLK_SEL0_ACLK_SEL      0x00000001	/* aclk_sel : 1 */
  #define SYSCTL_CLK_SEL0_SOURCE_IN0    0x00000000
  #define SYSCTL_CLK_SEL0_SOURCE_PLL0   0x00000001
  #define SYSCTL_CLK_SEL0_ACLK_SDIVISER 0x00000006	/* aclk_divider_sel : 2 */
  #define SYSCTL_CLK_SEL0_APB0_CLK_SEL  0x00000038	/* apb0_clk_sel : 3 */
  #define SYSCTL_CLK_SEL0_APB1_CLK_SEL  0x000001C0	/* apb1_clk_sel : 3 */
  #define SYSCTL_CLK_SEL0_APB2_CLK_SEL  0x00000E00	/* apb2_clk_sel : 3 */
  #define SYSCTL_CLK_SEL0_SPI3_CLK_SEL  0x00001000	/* spi3_clk_sel : 1 */
  #define SYSCTL_CLK_SEL0_TIM0_CLK_SEL  0x00002000	/* timer0_clk_sel : 1 */
  #define SYSCTL_CLK_SEL0_TIM1_CLK_SEL  0x00004000	/* timer1_clk_sel : 1 */
  #define SYSCTL_CLK_SEL0_TIM2_CLK_SEL  0x00008000	/* timer2_clk_sel : 1 */
#define TOFF_CLK_SEL1           0x0024			/* (RW) No. 9: Clock select controller1 */
  #define SYSCTL_CLK_SEL1_SPI3S_CLK_SEL 0x00000001	/* spi3_sample_clk_sel : 1 */
#define TOFF_SYSCTL_CLK_EN_CENT 0x0028			/* (RW) No. 10: Central clock enable */
  #define SYSCTL_CLK_EN_CENT_CPU_CLK_EN   0x00000001	/* cpu_clk_en : 1 */
  #define SYSCTL_CLK_EN_CENT_SRAM0_CLK_EN 0x00000002	/* sram0_clk_en : 1 */
  #define SYSCTL_CLK_EN_CENT_SRAM1_CLK_EN 0x00000004	/* sram1_clk_en : 1 */
  #define SYSCTL_CLK_EN_CENT_APB0_CLK_EN  0x00000008	/* apb0_clk_en : 1 */
  #define SYSCTL_CLK_EN_CENT_APB1_CLK_EN  0x00000010	/* apb1_clk_en : 1 */
  #define SYSCTL_CLK_EN_CENT_APB2_CLK_EN  0x00000020	/* apb2_clk_en : 1 */
#define TOFF_SYSCTL_CLK_EN_PERI 0x002C			/* (RW) No. 11: Peripheral clock enable */
  #define SYSCTL_CLK_EN_PERI_ROM_CLK_EN   0x00000001	/* rom_clk_en : 1 */
  #define SYSCTL_CLK_EN_PERI_DMA_CLK_EN   0x00000002	/* dma_clk_en : 1 */
  #define SYSCTL_CLK_EN_PERI_AI_CLK_EN    0x00000004	/* ai_clk_en : 1 */
  #define SYSCTL_CLK_EN_PERI_DVP_CLK_EN   0x00000008	/* dvp_clk_en : 1 */
  #define SYSCTL_CLK_EN_PERI_FFT_CLK_EN   0x00000010	/* fft_clk_en : 1 */
  #define SYSCTL_CLK_EN_PERI_GPIO_CLK_EN  0x00000020	/* gpio_clk_en : 1 */
  #define SYSCTL_CLK_EN_PERI_SPI0_CLK_EN  0x00000040	/* spi0_clk_en : 1 */
  #define SYSCTL_CLK_EN_PERI_SPI1_CLK_EN  0x00000080	/* spi1_clk_en : 1 */
  #define SYSCTL_CLK_EN_PERI_SPI2_CLK_EN  0x00000100	/* spi2_clk_en : 1 */
  #define SYSCTL_CLK_EN_PERI_SPI3_CLK_EN  0x00000200	/* spi3_clk_en : 1 */
  #define SYSCTL_CLK_EN_PERI_I2S0_CLK_EN  0x00000400	/* i2s0_clk_en : 1 */
  #define SYSCTL_CLK_EN_PERI_I2S1_CLK_EN  0x00000800	/* i2s1_clk_en : 1 */
  #define SYSCTL_CLK_EN_PERI_I2S2_CLK_EN  0x00001000	/* i2s2_clk_en : 1 */
  #define SYSCTL_CLK_EN_PERI_I2C0_CLK_EN  0x00002000	/* i2c0_clk_en : 1 */
  #define SYSCTL_CLK_EN_PERI_I2C1_CLK_EN  0x00004000	/* i2c1_clk_en : 1 */
  #define SYSCTL_CLK_EN_PERI_I2C2_CLK_EN  0x00008000	/* i2c2_clk_en : 1 */
  #define SYSCTL_CLK_EN_PERI_UART1_CLK_EN 0x00010000	/* uart1_clk_en : 1 */
  #define SYSCTL_CLK_EN_PERI_UART2_CLK_EN 0x00020000	/* uart2_clk_en : 1 */
  #define SYSCTL_CLK_EN_PERI_UART3_CLK_EN 0x00040000	/* uart3_clk_en : 1 */
  #define SYSCTL_CLK_EN_PERI_AES_CLK_EN   0x00080000	/* aes_clk_en : 1 */
  #define SYSCTL_CLK_EN_PERI_FPIOA_CLK_EN 0x00100000	/* fpioa_clk_en : 1 */
  #define SYSCTL_CLK_EN_PERI_TIM0_CLK_EN  0x00200000	/* timer0_clk_en : 1 */
  #define SYSCTL_CLK_EN_PERI_TIM1_CLK_EN  0x00400000	/* timer1_clk_en : 1 */
  #define SYSCTL_CLK_EN_PERI_TIM2_CLK_EN  0x00800000	/* timer2_clk_en : 1 */
  #define SYSCTL_CLK_EN_PERI_WDT0_CLK_EN  0x01000000	/* wdt0_clk_en : 1 */
  #define SYSCTL_CLK_EN_PERI_WDT1_CLK_EN  0x02000000	/* wdt1_clk_en : 1 */
  #define SYSCTL_CLK_EN_PERI_SHA_CLK_EN   0x04000000	/* sha_clk_en : 1 */
  #define SYSCTL_CLK_EN_PERI_OTP_CLK_EN   0x08000000	/* otp_clk_en : 1 */
  #define SYSCTL_CLK_EN_PERI_RTC_CLK_EN   0x20000000	/* rtc_clk_en : 1 */
#define TOFF_SYSCTL_SOFT_RESET  0x0030			/* (RW) No. 12: Soft reset ctrl */
  #define SYSCTL_SOFT_RESET_RESET         0x00000001	/* soft_reset : 1 */
#define TOFF_SYSCTL_PERI_RESET  0x0034			/* (RW) No. 13: Peripheral reset controller */
  #define SYSCTL_PERI_RESET_ROM_RESET     0x00000001	/* rom_reset : 1 */
  #define SYSCTL_PERI_RESET_DMA_RESET     0x00000002	/* dma_reset : 1 */
  #define SYSCTL_PERI_RESET_AI_RESET      0x00000004	/* ai_reset : 1 */
  #define SYSCTL_PERI_RESET_DVP_RESET     0x00000008	/* dvp_reset : 1 */
  #define SYSCTL_PERI_RESET_FFT_RESET     0x00000010	/* fft_reset : 1 */
  #define SYSCTL_PERI_RESET_GPIO_RESET    0x00000020	/* gpio_reset : 1 */
  #define SYSCTL_PERI_RESET_SPI0_RESET    0x00000040	/* spi0_reset : 1 */
  #define SYSCTL_PERI_RESET_SPI1_RESET    0x00000080	/* spi1_reset : 1 */
  #define SYSCTL_PERI_RESET_SPI2_RESET    0x00000100	/* spi2_reset : 1 */
  #define SYSCTL_PERI_RESET_SPI3_RESET    0x00000200	/* spi3_reset : 1 */
  #define SYSCTL_PERI_RESET_I2S0_RESET    0x00000400	/* i2s0_reset : 1 */
  #define SYSCTL_PERI_RESET_I2S1_RESET    0x00000800	/* i2s1_reset : 1 */
  #define SYSCTL_PERI_RESET_I2S2_RESET    0x00001000	/* i2s2_reset : 1 */
  #define SYSCTL_PERI_RESET_I2C0_RESET    0x00002000	/* i2c0_reset : 1 */
  #define SYSCTL_PERI_RESET_I2C1_RESET    0x00004000	/* i2c1_reset : 1 */
  #define SYSCTL_PERI_RESET_I2C2_RESET    0x00008000	/* i2c2_reset : 1 */
  #define SYSCTL_PERI_RESET_UART1_RESET   0x00010000	/* uart1_reset : 1 */
  #define SYSCTL_PERI_RESET_UART2_RESET   0x00020000	/* uart2_reset : 1 */
  #define SYSCTL_PERI_RESET_UART3_RESET   0x00040000	/* uart3_reset : 1 */
  #define SYSCTL_PERI_RESET_AES_RESET     0x00080000	/* aes_reset : 1 */
  #define SYSCTL_PERI_RESET_FPIOA_RESET   0x00100000	/* fpioa_reset : 1 */
  #define SYSCTL_PERI_RESET_TIM0_RESET    0x00200000	/* timer0_reset : 1 */
  #define SYSCTL_PERI_RESET_TIM1_RESET    0x00400000	/* timer1_reset : 1 */
  #define SYSCTL_PERI_RESET_TIM2_RESET    0x00800000	/* timer2_reset : 1 */
  #define SYSCTL_PERI_RESET_WDT0_RESET    0x01000000	/* wdt0_reset : 1 */
  #define SYSCTL_PERI_RESET_WDT1_RESET    0x02000000	/* wdt1_reset : 1 */
  #define SYSCTL_PERI_RESET_SHA_RESET     0x04000000	/* sha_reset : 1 */
  #define SYSCTL_PERI_RESET_RTC_RESET     0x20000000	/* rtc_reset : 1 */
#define TOFF_SYSCTL_CLK_TH0     0x0038			/* (RW) No. 14: Clock threshold controller 0 */
  #define SYSCTL_CLK_TH0_SRAM0_GCLK_THHD  0x0000000F	/* sram0_gclk_threshold : 4 */
  #define SYSCTL_CLK_TH0_SRAM1_GCLK_THHD  0x000000F0	/* sram1_gclk_threshold : 4 */
  #define SYSCTL_CLK_TH0_AI_GCLK_THHD     0x00000F00	/* ai_gclk_threshold : 4 */
  #define SYSCTL_CLK_TH0_DVP_GCLK_THHD    0x0000F000	/* dvp_gclk_threshold : 4 */
  #define SYSCTL_CLK_TH0_ROM_GCLK_THHD    0x000F0000	/* rom_gclk_threshold : 4 */
#define TOFF_SYSCTL_CLK_TH1     0x003C			/* (RW) No. 15: Clock threshold controller 1 */
  #define SYSCTL_CLK_TH1_SPI0_CLK_THHD    0x000000FF	/* spi0_clk_threshold : 8 */
  #define SYSCTL_CLK_TH1_SPI1_CLK_THHD    0x0000FF00	/* spi1_clk_threshold : 8 */
  #define SYSCTL_CLK_TH1_SPI2_CLK_THHD    0x00FF0000	/* spi2_clk_threshold : 8 */
  #define SYSCTL_CLK_TH1_SPI3_CLK_THHD    0xFF000000	/* spi3_clk_threshold : 8 */
#define TOFF_SYSCTL_CLK_TH2     0x0040			/* (RW) No. 16: Clock threshold controller 2 */
  #define SYSCTL_CLK_TH2_TM0_CLK_THHD     0x000000FF	/* timer0_clk_threshold : 8 */
  #define SYSCTL_CLK_TH2_TM1_CLK_THHD     0x0000FF00	/* timer1_clk_threshold : 8 */
  #define SYSCTL_CLK_TH2_TM2_CLK_THHD     0x00FF0000	/* timer2_clk_threshold : 8 */
#define TOFF_SYSCTL_CLK_TH3     0x0044			/* (RW) No. 17: Clock threshold controller 3 */
  #define SYSCTL_CLK_TH3_I2S0_CLK_THHD    0x0000FFFF	/* i2s0_clk_threshold : 16 */
  #define SYSCTL_CLK_TH3_I2S1_CLK_THHD    0xFFFF0000	/* i2s1_clk_threshold : 16 */
#define TOFF_SYSCTL_CLK_TH4     0x0048			/* (RW) No. 18: Clock threshold controller 4 */
  #define SYSCTL_CLK_TH4_I2S2_CLK_THHD    0x0000FFFF	/* i2s2_clk_threshold : 16 */
  #define SYSCTL_CLK_TH4_I2S0_MCLK_THHD   0x00FF0000	/* i2s0_mclk_threshold : 8 */
  #define SYSCTL_CLK_TH4_I2S1_MCLK_THHD   0xFF000000	/* i2s1_mclk_threshold : 8 */
#define TOFF_SYSCTL_CLK_TH5     0x004C			/* (RW) No. 19: Clock threshold controller 5 */
  #define SYSCTL_CLK_TH5_I2S2_MCLK_THHD   0x000000FF	/* i2s2_mclk_threshold : 8 */
  #define SYSCTL_CLK_TH5_I2C0_CLK_THHD    0x0000FF00	/* i2c0_clk_threshold : 8 */
  #define SYSCTL_CLK_TH5_I2C1_CLK_THHD    0x00FF0000	/* i2c1_clk_threshold : 8 */
  #define SYSCTL_CLK_TH5_I2C2_CLK_THHD    0xFF000000	/* i2c2_clk_threshold : 8 */
#define TOFF_SYSCTL_CLK_TH6     0x0050			/* (RW) No. 20: Clock threshold controller 6 */
  #define SYSCTL_CLK_TH6_WD0_CLK_THHD     0x000000FF	/* wdt0_clk_threshold : 8 */
  #define SYSCTL_CLK_TH6_WD1_CLK_THHD     0x0000FF00	/* wdt1_clk_threshold : 8 */
#define TOFF_SYSCTL_MISC        0x0054			/* (RW) No. 21: Miscellaneous controller */
  #define SYSCTL_MISC_DEBUG_SEL           0x0000003F	/* debug_sel : 6 */
  #define SYSCTL_MISC_SPI_DVP_DATA_ENABLE 0x00000400	/* spi_dvp_data_enable: 1 */
#define TOFF_SYSCTL_PERI        0x0058			/* (RW) No. 22: Peripheral controller */
  #define SYSCTL_PERI_TIMER0_PAUSE        0x00000001	/* timer0_pause : 1 */
  #define SYSCTL_PERI_TIMER1_PAUSE        0x00000002	/* timer1_pause : 1 */
  #define SYSCTL_PERI_TIMER2_PAUSE        0x00000004	/* timer2_pause : 1 */
  #define SYSCTL_PERI_TIMER3_PAUSE        0x00000008	/* timer3_pause : 1 */
  #define SYSCTL_PERI_TIMER4_PAUSE        0x00000010	/* timer4_pause : 1 */
  #define SYSCTL_PERI_TIMER5_PAUSE        0x00000020	/* timer5_pause : 1 */
  #define SYSCTL_PERI_TIMER6_PAUSE        0x00000040	/* timer6_pause : 1 */
  #define SYSCTL_PERI_TIMER7_PAUSE        0x00000080	/* timer7_pause : 1 */
  #define SYSCTL_PERI_TIMER8_PAUSE        0x00000100	/* timer8_pause : 1 */
  #define SYSCTL_PERI_TIMER9_PAUSE        0x00000200	/* timer9_pause : 1 */
  #define SYSCTL_PERI_TIMER10_PAUSE       0x00000400	/* timer10_pause : 1 */
  #define SYSCTL_PERI_TIMER11_PAUSE       0x00000800	/* timer11_pause : 1 */
  #define SYSCTL_PERI_SPI0_XIP_EN         0x00001000	/* spi0_xip_en : 1 */
  #define SYSCTL_PERI_SPI1_XIP_EN         0x00002000	/* spi1_xip_en : 1 */
  #define SYSCTL_PERI_SPI2_XIP_EN         0x00004000	/* spi2_xip_en : 1 */
  #define SYSCTL_PERI_SPI3_XIP_EN         0x00008000	/* spi3_xip_en : 1 */
  #define SYSCTL_PERI_SPI0_CLK_BYPASS     0x00010000	/* spi0_clk_bypass : 1 */
  #define SYSCTL_PERI_SPI1_CLK_BYPASS     0x00020000	/* spi1_clk_bypass : 1 */
  #define SYSCTL_PERI_SPI2_CLK_BYPASS     0x00040000	/* spi2_clk_bypass : 1 */
  #define SYSCTL_PERI_I2S0_CLK_BYPASS     0x00080000	/* i2s0_clk_bypass : 1 */
  #define SYSCTL_PERI_I2S1_CLK_BYPASS     0x00100000	/* i2s1_clk_bypass : 1 */
  #define SYSCTL_PERI_I2S2_CLK_BYPASS     0x00200000	/* i2s2_clk_bypass : 1 */
  #define SYSCTL_PERI_JTAG_CLK_BYPASS     0x00400000	/* jtag_clk_bypass : 1 */
  #define SYSCTL_PERI_DVP_CLK_BYPASS      0x00800000	/* dvp_clk_bypass : 1 */
  #define SYSCTL_PERI_DEBUG_CLK_BYPASS    0x01000000	/* debug_clk_bypass : 1 */
#define TOFF_SYSCTL_SPI_SLEEP   0x005C			/* (RW) No. 23: SPI sleep controller */
  #define SYSCTL_SPI_SLEEP_SSI0_SLEEP     0x00000001	/* ssi0_sleep : 1 */
  #define SYSCTL_SPI_SLEEP_SSI1_SLEEP     0x00000002	/* ssi1_sleep : 1 */
  #define SYSCTL_SPI_SLEEP_SSI2_SLEEP     0x00000004	/* ssi2_sleep : 1 */
  #define SYSCTL_SPI_SLEEP_SSI3_SLEEP     0x00000008	/* ssi3_sleep : 1 */
#define TOFF_SYSCTL_RST_STATUS  0x0060			/* (RW) No. 24: Reset source status */
  #define SYSCTL_RST_STATUS_RESET_STS_CLR 0x00000001	/* reset_sts_clr : 1 */
  #define SYSCTL_RST_STATUS_PIN_RESET_STS 0x00000002	/* pin_reset_sts : 1 */
  #define SYSCTL_RST_STATUS_WDT0_RESET_STS 0x00000004	/* wdt0_reset_sts : 1 */
  #define SYSCTL_RST_STATUS_WDT1_RESET_STS 0x00000008	/* wdt1_reset_sts : 1 */
  #define SYSCTL_RST_STATUS_SOFT_RESET_STS 0x00000010	/* soft_reset_sts : 1 */
#define TOFF_SYSCTL_DMA_SEL0    0x0064			/* (RW) No. 25: DMA handshake selector */
  #define SYSCTL_DMA_SEL0_DMA_SEL0        0x0000003F	/* dma_sel0 : 6 */
  #define SYSCTL_DMA_SEL0_DMA_SEL1        0x00000FC0	/* dma_sel1 : 6 */
  #define SYSCTL_DMA_SEL0_DMA_SEL2        0x0003F000	/* dma_sel2 : 6 */
  #define SYSCTL_DMA_SEL0_DMA_SEL3        0x00FC0000	/* dma_sel3 : 6 */
  #define SYSCTL_DMA_SEL0_DMA_SEL4        0x3F000000	/* dma_sel4 : 6 */
#define TOFF_SYSCTL_DMA_SEL1    0x0068			/* (RW) No. 26: DMA handshake selector */
  #define SYSCTL_DMA_SEL0_DMA_SEL5        0x0000003F	/* dma_sel5 : 6 */
#define TOFF_SYSCTL_POWER_SEL   0x006C			/* (RW) No. 27: IO Power Mode Select controller */
  #define SYSCTL_POWER_SEL_POWER_MODE_0   0x00000001	/* power_mode_sel0 : 1 */
  #define SYSCTL_POWER_SEL_POWER_MODE_1   0x00000002	/* power_mode_sel1 : 1 */
  #define SYSCTL_POWER_SEL_POWER_MODE_2   0x00000004	/* power_mode_sel2 : 1 */
  #define SYSCTL_POWER_SEL_POWER_MODE_3   0x00000008	/* power_mode_sel3 : 1 */
  #define SYSCTL_POWER_SEL_POWER_MODE_4   0x00000010	/* power_mode_sel4 : 1 */
  #define SYSCTL_POWER_SEL_POWER_MODE_5   0x00000020	/* power_mode_sel5 : 1 */
  #define SYSCTL_POWER_SEL_POWER_MODE_6   0x00000040	/* power_mode_sel6 : 1 */
  #define SYSCTL_POWER_SEL_POWER_MODE_7   0x00000080	/* power_mode_sel7 : 1 */

/*
 *  RTC
 */
#define TADR_RTC_BASE       (RTC_BASE_ADDR)
#define TOFF_RTC_DATE       0x0000		/* (RW) Timer date information */
  #define RTC_DATE_WEEK         0x00000007	/* Week. Range [0,6]. 0 is Sunday. */
  #define RTC_DATE_DAY          0x00001F00	/* Day. Range [1,31] or [1,30] or [1,29] or [1,28] */
  #define RTC_DATE_MONTH        0x000F0000	/* Month. Range [1,12] */
  #define RTC_DATE_YEAR         0x3FF00000	/* Year. Range [0,99] */
#define TOFF_RTC_TIME       0x0004		/* (RW) Timer time information */
  #define RTC_TIME_SECOND       0x0000FC00	/* Second. Range [0,59] */
  #define RTC_TIME_MINUTE       0x003F0000	/* Minute. Range [0,59] */
  #define RTC_TIME_HOUR         0x1F000000	/* Hour. Range [0,23] */
#define TOFF_ALARM_DATE     0x0008		/* (RW) Alarm date information */
  #define RTC_ALARM_DATE_WEEK   0x00000003	/* Alarm Week. Range [0,6]. 0 is Sunday. */
  #define RTC_ALARM_DATE_DAY    0x00001F00	/* Alarm Day. Range [1,31] or [1,30] or [1,29] or [1,28] */
  #define RTC_ALARM_DATE_MONTH  0x000F0000	/* Alarm Month. Range [1,12] */
  #define RTC_ALARM_DATE_YEAR   0x3FF00000	/* Alarm Year. Range [0,99] */
#define TOFF_ALARM_TIME     0x000C		/* (RW) Alarm time information */
  #define RTC_ALARM_TIME_SECOND 0x0000FC00	/* Alarm Second. Range [0,59] */
  #define RTC_ALARM_TIME_MINUTE 0x003F0000	/* Alarm Minute. Range [0,59] */
  #define RTC_ALARM_TIME_HOUR   0x1F000000	/* Alarm Hour. Range [0,23] */
#define TOFF_INITIAL_COUNT  0x0010		/* (RW) Timer counter initial value */
#define TOFF_COURRNT_COUNT  0x0014		/* (RW) Timer counter current value */
#define TOFF_INTERRUPT_CTRL 0x0018		/* (RW) RTC interrupt settings */
  #define RTC_INT_TICK_ENABLE   0x00000001	/* Reserved */
  #define RTC_INT_ALARM_ENABLE  0x00000002	/* Alarm interrupt enable */
  #define RTC_INT_TICK_INT_MODE 0x0000000C	/* Tick interrupt enable */
  #define RTC_INT_ARARM_C_MASK  0xFF000000	/* Alarm compare mask for interrupt */
#define TOFF_REGISTER_CTRL  0x001C		/* (RW) RTC register settings */
  #define RTC_RCTL_READ_ENABLE  0x00000001	/* RTC timer read enable */
  #define RTC_RCTL_WRITE_ENABLE 0x00000002	/* RTC timer write enable */
  #define RTC_RCTL_TIMER_MASK   0x001FE000	/* RTC timer mask */
  #define RTC_RCTL_ALARAM_MASK  0x1FE00000	/* RTC alarm mask */
  #define RTC_RCTL_INT_CNT_MASK 0x20000000	/* RTC counter initial count value mask */
  #define RTC_RCTL_INT_REG_MASK 0x40000000	/* RTC interrupt register mask */
#define TOFF_RTC_EXTENDED   0x0028			/* (RW) Timer extended information */
  #define RTC_EXTENDED_CENTURY  0x0000001F	/* Century. Range [0,31] */
  #define RTC_EXTENDED_YEAR     0x00000020	/* Is leap year. 1 is leap year, 0 is not leap year */


/*
 *  SPI
 */
#define TADR_SPI0_BASE      (SPI0_BASE_ADDR)
#define TADR_SPI1_BASE      (SPI1_BASE_ADDR)
#define TADR_SPIS_BASE      (SPI_SLAVE_BASE_ADDR)
#define TADR_SPI2_BASE      (SPI3_BASE_ADDR)
#define TOFF_SPI_CTRLR0         0x0000		/* (RW) SPI Control Register 0 */
#define TOFF_SPI_CTRLR1         0x0004		/* (RW) SPI Control Register 1 */
#define TOFF_SPI_SSIENR         0x0008		/* (RW) SPI Enable Register */
#define TOFF_SPI_MWCR           0x000C		/* (RW) SPI Microwire Control Register */
#define TOFF_SPI_SER            0x0010		/* (RW) SPI Slave Enable Register */
#define TOFF_SPI_BAUDR          0x0014		/* (RW) SPI Baud Rate Select */
#define TOFF_SPI_TXFTLR         0x0018		/* (RW) SPI Transmit FIFO Threshold Level */
#define TOFF_SPI_RXFTLR         0x001C		/* (RW) SPI Receive FIFO Threshold Level */
#define TOFF_SPI_TXFLR          0x0020		/* (RW) SPI Transmit FIFO Level Register */
#define TOFF_SPI_RXFLR          0x0024		/* (RW) SPI Receive FIFO Level Register */
#define TOFF_SPI_SR             0x0028		/* (RW) SPI Status Register */
#define TOFF_SPI_IMR            0x002C		/* (RW) SPI Interrupt Mask Register */
#define TOFF_SPI_ISR            0x0030		/* (RW) SPI Interrupt Status Register */
#define TOFF_SPI_RISR           0x0034		/* (RW) SPI Raw Interrupt Status Register */
#define TOFF_SPI_TXOICR         0x0038		/* (RW) SPI Transmit FIFO Overflow Interrupt Clear Register */
#define TOFF_SPI_RXOICR         0x003C		/* (RW) SPI Receive FIFO Overflow Interrupt Clear Register */
#define TOFF_SPI_RXUICR         0x0040		/* (RW) SPI Receive FIFO Underflow Interrupt Clear Register */
#define TOFF_SPI_MSTICR         0x0044		/* (RW) SPI Multi-Master Interrupt Clear Register */
#define TOFF_SPI_ICR            0x0048		/* (RW) SPI Interrupt Clear Register */
#define TOFF_SPI_DMACR          0x004C		/* (RW) SPI DMA Control Register */
#define TOFF_SPI_DMATDLR        0x0050		/* (RW) SPI DMA Transmit Data Level */
#define TOFF_SPI_DMARDLR        0x0054		/* (RW) SPI DMA Receive Data Level */
#define TOFF_SPI_IDR            0x0058		/* (RW) SPI Identification Register */
#define TOFF_SPI_SSIC_VER_ID    0x005C		/* (RW) SPI DWC_ssi component version */
#define TOFF_SPI_DR             0x0060		/* (RW) SPI Data Register 0-35 */
#define TOFF_SPI_RX_SAMPL_DELAY 0x00F0		/* (RW) SPI RX Sample Delay Register */
#define TOFF_SPI_SPI_CTRLR0     0x00F4		/* (RW) SPI SPI Control Register */
#define TOFF_SPI_XIP_MODE_BITS  0x00FC		/* (RW) SPI XIP Mode bits */
#define TOFF_SPI_XIP_INCR_INST  0x0100		/* (RW) SPI XIP INCR transfer opcode */
#define TOFF_SPI_XIP_WRAP_INST  0x0104		/* (RW) SPI XIP WRAP transfer opcode */
#define TOFF_SPI_XIP_CTRL       0x0108		/* (RW) SPI XIP Control Register */
#define TOFF_SPI_XIP_SER        0x010C		/* (RW) SPI XIP Slave Enable Register */
#define TOFF_SPI_XRXOICR        0x0110		/* (RW) SPI XIP Receive FIFO Overflow Interrupt Clear Register */
#define TOFF_SPI_XIP_CNT_TIMOUT 0x0114		/* (RW) SPI XIP time out register for continuous transfers */
#define TOFF_SPI_ENDIAN         0x0118

#endif /* _KENDRYTE_K210_H_ */
