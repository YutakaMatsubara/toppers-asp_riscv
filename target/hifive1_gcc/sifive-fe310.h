/*
 *  TOPPERS/ASP Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      Advanced Standard Profile Kernel
 * 
 *  Copyright (C) 2000-2003 by Embedded and Real-Time Systems Laboratory
 *                              Toyohashi Univ. of Technology, JAPAN
 *  Copyright (C) 2005-2011 by Embedded and Real-Time Systems Laboratory
 *              Graduate School of Information Science, Nagoya Univ., JAPAN
 *  Copyright (C) 2017-2018 by TOPPERS PROJECT Educational Working Group.
 *
 *  上記著作権者は，以下の (1)〜(4) の条件か，Free Software Foundation 
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
 *    (b) 再配布の形態を，別に定める方法によって，TOPPERSプロジェクトに
 *        報告すること．
 *  (4) 本ソフトウェアの利用により直接的または間接的に生じるいかなる損
 *      害からも，上記著作権者およびTOPPERSプロジェクトを免責すること．
 *
 *  本ソフトウェアは，無保証で提供されているものである．上記著作権者お
 *  よびTOPPERSプロジェクトは，本ソフトウェアに関して，その適用可能性も
 *  含めて，いかなる保証も行わない．また，本ソフトウェアの利用により直
 *  接的または間接的に生じたいかなる損害に関しても，その責任を負わない．
 * 
 *  @(#) $Id: sifive-fe310.h 2246 2019-10-10 20:23:55Z roi $
 */

#ifndef _SIFIVE_FE310_H_
#define _SIFIVE_FE310_H_

#include <sil.h>
#include "encoding.h"

#define TMAX_INTNO          52
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

#define NUM_GPIO            32

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
#define IRQ_VECTOR_WDOGCMP                  1
#define IRQ_VECTOR_RTCCMP                   2
#define IRQ_VECTOR_UART0                    3
#define IRQ_VECTOR_UART1                    4
#define IRQ_VECTOR_SPI0                     5
#define IRQ_VECTOR_SPI1                     6
#define IRQ_VECTOR_SPI2                     7
#define IRQ_VECTOR_GPIO                     8
#define IRQ_VECTOR_PWM0                     40
#define IRQ_VECTOR_PWM1                     44
#define IRQ_VECTOR_PWM2                     48


/*
 *  SIFIVE FE310 G0000 MEMORY MAP
 */
#define MASKROM_MEM_ADDR        0x00001000
#define TRAPVEC_TABLE_CTRL_ADDR 0x00001010
#define OTP_MEM_ADDR            0x00020000
#define CLINT_CTRL_ADDR         0x02000000
#define PLIC_CTRL_ADDR          0x0C000000
#define AON_CTRL_ADDR           0x10000000
#define PRCI_CTRL_ADDR          0x10008000
#define OTP_CTRL_ADDR           0x10010000
#define GPIO_CTRL_ADDR          0x10012000
#define UART0_CTRL_ADDR         0x10013000
#define SPI0_CTRL_ADDR          0x10014000
#define PWM0_CTRL_ADDR          0x10015000
#define UART1_CTRL_ADDR         0x10023000
#define SPI1_CTRL_ADDR          0x10024000
#define PWM1_CTRL_ADDR          0x10025000
#define SPI2_CTRL_ADDR          0x10034000
#define PWM2_CTRL_ADDR          0x10035000
#define SPI0_MEM_ADDR           0x20000000
#define MEM_CTRL_ADDR           0x80000000

/*
 *  AON-WATCH DOG
 */
#define TADR_AON_BASE       (AON_CTRL_ADDR)
#define TOFF_AON_WDOGCFG    0x0000
  #define AON_WDOGCFG_SCALE       0x0000000F
  #define AON_WDOGCFG_RSTEN       0x00000100
  #define AON_WDOGCFG_ZEROCMP     0x00000200
  #define AON_WDOGCFG_ENALWAYS    0x00001000
  #define AON_WDOGCFG_ENCOREAWAKE 0x00002000
  #define AON_WDOGCFG_CMPIP       0x10000000
#define TOFF_AON_WDOGCOUNT  0x0008
#define TOFF_AON_WDOGS      0x0010
#define TOFF_AON_WDOGFEED   0x0018
  #define AON_WDOGFEED_VALUE      0x0D09F00D
#define TOFF_AON_WDOGKEY    0x001C
  #define AON_WDOGKEY_VALUE       0x0051F15E
#define TOFF_AON_WDOGCMP    0x0020

/*
 *  AON-RTC
 */
#define TOFF_AON_RTCCFG     0x0040
  #define AON_RTCCFG_SCALE        0x0000000F
  #define AON_RTCCFG_ENALWAYS     0x00001000
  #define AON_RTCCFG_CMPIP        0x10000000
#define TOFF_AON_RTCLO      0x0048
#define TOFF_AON_RTCHI      0x004C
#define TOFF_AON_RTCS       0x0050
#define TOFF_AON_RTCCMP     0x0060

/*
 *  AON-CLOCK
 */
#define TOFF_AON_LFROSC     0x0070
  #define LFROSC_OSC_EN           0x40000000
  #define LFROSC_OSC_RDY          0x80000000

/*
 *  AON-BACKUP
 */
#define TOFF_AON_BACKUP0    0x0080
#define TOFF_AON_BACKUP1    0x0084
#define TOFF_AON_BACKUP2    0x0088
#define TOFF_AON_BACKUP3    0x008C
#define TOFF_AON_BACKUP4    0x0090
#define TOFF_AON_BACKUP5    0x0094
#define TOFF_AON_BACKUP6    0x0098
#define TOFF_AON_BACKUP7    0x009C
#define TOFF_AON_BACKUP8    0x00A0
#define TOFF_AON_BACKUP9    0x00A4
#define TOFF_AON_BACKUP10   0x00A8
#define TOFF_AON_BACKUP11   0x00AC
#define TOFF_AON_BACKUP12   0x00B0
#define TOFF_AON_BACKUP13   0x00B4
#define TOFF_AON_BACKUP14   0x00B8
#define TOFF_AON_BACKUP15   0x00BC

/*
 *  AON-PMU
 */
#define TOFF_AON_PMUWAKEUPI0 0x0100
#define TOFF_AON_PMUWAKEUPI1 0x0104
#define TOFF_AON_PMUWAKEUPI2 0x0108
#define TOFF_AON_PMUWAKEUPI3 0x010C
#define TOFF_AON_PMUWAKEUPI4 0x0110
#define TOFF_AON_PMUWAKEUPI5 0x0114
#define TOFF_AON_PMUWAKEUPI6 0x0118
#define TOFF_AON_PMUWAKEUPI7 0x011C
#define TOFF_AON_PMUSLEEPI0 0x0120
#define TOFF_AON_PMUSLEEPI1 0x0124
#define TOFF_AON_PMUSLEEPI2 0x0128
#define TOFF_AON_PMUSLEEPI3 0x012C
#define TOFF_AON_PMUSLEEPI4 0x0130
#define TOFF_AON_PMUSLEEPI5 0x0134
#define TOFF_AON_PMUSLEEPI6 0x0138
#define TOFF_AON_PMUSLEEPI7 0x013C
#define TOFF_AON_PMUIE      0x0140
#define TOFF_AON_PMUCAUSE   0x0144
  #define AON_PMUCAUSE_WAKEUPCAUSE 0x00000003
  #define AON_WAKEUPCAUSE_RESET   0x00000000
  #define AON_WAKEUPCAUSE_RTC     0x00000001
  #define AON_WAKEUPCAUSE_DWAKEUP 0x00000002
  #define AON_WAKEUPCAUSE_AWAKEUP 0x00000003
  #define AON_PMUCAUSE_RESETCAUSE 0x00000300
  #define AON_RESETCAUSE_POWERON  0x00000000
  #define AON_RESETCAUSE_EXTERNAL 0x00000100
  #define AON_RESETCAUSE_WATCHDOG 0x00000200
#define TOFF_AON_PMUSLEEP   0x0148
#define TOFF_AON_PMUKEY     0x014C

#define RTC_FREQ            32768
#define TIMER_FREQ          (RTC_FREQ)

/*
 *  CLINT
 */
#define TADR_CLIC_BASE      (CLINT_CTRL_ADDR)
#define TOFF_CLINT_MSIP     0x0000
#define CLINT_MSIP_size     0x4
#define TOFF_CLINT_MTIMECMP 0x4000
#define CLINT_MTIMECMP_size 0x8
#define TOFF_CLINT_MTIME    0xBFF8
#define CLINT_MTIME_size    0x8


/*
 *  PLIC
 */
#define TADR_PLIC_BASE      (PLIC_CTRL_ADDR)
#define TOFF_PLIC_PRIORITY  0x00000000
#define TOFF_PLIC_PENDING   0x00001000
#define TOFF_PLIC_ENABLE    0x00002000
#define NUM_PLIC_ENABLE     128
#define TOFF_PLIC_THRESHOLD 0x00200000
#define NUM_PLIC_THRESHOLD  4096
#define TOFF_PLIC_CLAIM     0x00200004


/*
 *  GPIO
 */
#define TADR_GPIO_BASE      (GPIO_CTRL_ADDR)
#define TOFF_GPIO_INPUT_VAL   0x0000
#define TOFF_GPIO_INPUT_EN    0x0004
#define TOFF_GPIO_OUTPUT_EN   0x0008
#define TOFF_GPIO_OUTPUT_VAL  0x000C
#define TOFF_GPIO_PULLUP_EN   0x0010
#define TOFF_GPIO_DRIVE       0x0014
#define TOFF_GPIO_RISE_IE     0x0018
#define TOFF_GPIO_RISE_IP     0x001C
#define TOFF_GPIO_FALL_IE     0x0020
#define TOFF_GPIO_FALL_IP     0x0024
#define TOFF_GPIO_HIGH_IE     0x0028
#define TOFF_GPIO_HIGH_IP     0x002C
#define TOFF_GPIO_LOW_IE      0x0030
#define TOFF_GPIO_LOW_IP      0x0034
#define TOFF_GPIO_IOF_EN      0x0038
  #define IOF_SPI1_SS0        0x00000004
  #define IOF_SPI1_MOSI       0x00000008
  #define IOF_SPI1_MISO       0x00000010
  #define IOF_SPI1_SCK        0x00000020
  #define IOF_SPI1_DQ2        0x00000040
  #define IOF_SPI1_DQ3        0x00000080
  #define IOF_SPI1_SS1        0x00000100
  #define IOF_SPI1_SS2        0x00000200
  #define IOF_SPI1_SS3        0x00000400
  #define IOF_SPI1_DQ0        0x00000008
  #define IOF_SPI1_DQ1        0x00000010
  #define IOF0_SPI1_MASK      (IOF_SPI1_SS0 | IOF_SPI1_MOSI | IOF_SPI1_MISO | IOF_SPI1_SCK | \
                               IOF_SPI1_DQ2 | IOF_SPI1_DQ3  | IOF_SPI1_SS1  | IOF_SPI1_SS2 | IOF_SPI1_SS3)

  #define IOF_UART0_RX        0x00010000
  #define IOF_UART0_TX        0x00020000
  #define IOF0_UART0_MASK     (IOF_UART0_RX | IOF_UART0_TX)
  #define IOF_UART1_RX        0x01000000
  #define IOF_UART1_TX        0x02000000
  #define IOF0_UART1_MASK     (IOF_UART1_RX | IOF_UART1_TX)
  #define IOF_SPI2_SS0        0x04000000
  #define IOF_SPI2_MOSI       0x08000000
  #define IOF_SPI2_MISO       0x10000000
  #define IOF_SPI2_SCK        0x20000000
  #define IOF_SPI2_DQ0        0x08000000
  #define IOF_SPI2_DQ1        0x10000000
  #define IOF_SPI2_DQ2        0x40000000
  #define IOF_SPI2_DQ3        0x80000000
  #define IOF0_SPI2_MASK      (IOF_SPI2_SS0 | IOF_SPI2_MOSI | IOF_SPI2_MISO | IOF_SPI2_SCK | IOF_SPI2_DQ2 | IOF_SPI2_DQ3)
#define TOFF_GPIO_IOF_SEL     0x003C
#define TOFF_GPIO_OUTPUT_XOR  0x0040

/*
 *  IOF1 masks
 */
#define IOF1_PWM0_MASK        0x0000000F
#define IOF1_PWM1_MASK        0x00780000
#define IOF1_PWM2_MASK        0x00003C00


/*
 *  OPT
 */
#define TADR_OTP_BASE       (OTP_CTRL_ADDR)
#define TOFF_OTP_LOCK       0x0000
#define TOFF_OTP_CK         0x0004
#define TOFF_OTP_OE         0x0008
#define TOFF_OTP_SEL        0x000C
#define TOFF_OTP_WE         0x0010
#define TOFF_OTP_MR         0x0014
#define TOFF_OTP_MRR        0x0018
#define TOFF_OTP_MPP        0x001C
#define TOFF_OTP_VRREN      0x0020
#define TOFF_OTP_VPPEN      0x0024
#define TOFF_OTP_A          0x0028
#define TOFF_OTP_D          0x002C
#define TOFF_OTP_Q          0x0030
#define TOFF_OTP_READ_TIMINGS 0x0034

/*
 *  PRCI
 */
#define TADR_PRCI_BASE      (PRCI_CTRL_ADDR)
#define PRCI_HFROSCCFG      (0x0000)
  #define HFROSCCFG_OSC_DIV   0x0000002F
  #define HFROSCCFG_OSC_TRIM  0x001F0000
  #define HFROSCCFG_OSC_EN    0x40000000
  #define HFROSCCFG_OSC_RDY   0x80000000

#define PRCI_HFXOSCCFG      (0x0004)
#define PRCI_PLLCFG         (0x0008)
  #define PLLCFG_R            0x00000007
  #define PLLCFG_F            0x000003F0
  #define PLLCFG_Q            0x00000C00
  #define PLLCFG_PLL_SEL      0x00010000
  #define PLLCFG_SEL_HFROSC   0x00000000
  #define PLLCFG_SEL_PLL      (PLLCFG_PLL_SEL)
  #define PLLCFG_PLL_REFSEL   0x00020000
  #define PLLCFG_REFSEL_HFROSC  0x00000000
  #define PLLCFG_REFSEL_HFXOSC  (PLLCFG_PLL_REFSEL)
  #define PLLCFG_PLL_BYPASS   0x00040000
  #define PLLCFG_PLL_LOCK     0x80000000
#define PRCI_PLLDIV         (0x000C)
  #define PLL_FINAL_DIV(x)      (((x) & 0x3F) << 0)
  #define PLL_FINAL_DIV_BY_1(x) (((x) & 0x1 ) << 8)
#define PRCI_PROCMONCFG     (0x00F0)
  #define PROCMON_DIV(x)   (((x) & 0x1F) << 0)
  #define PROCMON_TRIM(x)  (((x) & 0x1F) << 8)
  #define PROCMONCFG_EN     0x00010000
  #define PROCMON_SEL(x)   (((x) & 0x3)  << 24)
  #define PROCMONCFG_SEL_HFCLK     (0 << 24)
  #define PROCMONCFG_SEL_HFXOSCIN  (1 << 24)
  #define PROCMONCFG_SEL_PLLOUTDIV (2 << 24)
  #define PROCMONCFG_SEL_PROCMON   (3 << 24)
  #define PROCMONCFG_NT_EN  0x10000000


/*
 *  UART
 */
#define TADR_UART0_BASE     (UART0_CTRL_ADDR)
#define TADR_UART1_BASE     (UART1_CTRL_ADDR)
#define TOFF_UART_TXFIFO    0x0000
  #define UART_TXFIFO_FULL  0x80000000
#define TOFF_UART_RXFIFO    0x0004
  #define UART_RXFIFO_EMPTY 0x80000000
#define TOFF_UART_TXCTRL    0x0008
  #define UART_TXEN         0x00000001
  #define UART_TXCNT        0x00070000
#define TOFF_UART_RXCTRL    0x000C
  #define UART_RXEN         0x00000001
  #define UART_RXCT         0x00070000
#define TOFF_UART_IE        0x0010
#define TOFF_UART_IP        0x0014
  #define UART_IP_TXWM      0x00000001
  #define UART_IP_RXWM      0x00000002
#define TOFF_UART_DIV       0x0018


/*
 *  PWM
 */
#define TADR_PWM0_BASE      (PWM0_CTRL_ADDR)
#define TADR_PWM1_BASE      (PWM1_CTRL_ADDR)
#define TADR_PWM2_BASE      (PWM2_CTRL_ADDR)
#define TOFF_PWM_CFG        0x0000
  #define PWM_CFG_SCALE       0x0000000F
  #define PWM_CFG_STICKY      0x00000100
  #define PWM_CFG_ZEROCMP     0x00000200
  #define PWM_CFG_DEGLITCH    0x00000400
  #define PWM_CFG_ENALWAYS    0x00001000
  #define PWM_CFG_ONESHOT     0x00002000
  #define PWM_CFG_CMP0CENTER  0x00010000
  #define PWM_CFG_CMP1CENTER  0x00020000
  #define PWM_CFG_CMP2CENTER  0x00040000
  #define PWM_CFG_CMP3CENTER  0x00080000
  #define PWM_CFG_CMP0GANG    0x01000000
  #define PWM_CFG_CMP1GANG    0x02000000
  #define PWM_CFG_CMP2GANG    0x04000000
  #define PWM_CFG_CMP3GANG    0x08000000
  #define PWM_CFG_CMP0IP      0x10000000
  #define PWM_CFG_CMP1IP      0x20000000
  #define PWM_CFG_CMP2IP      0x40000000
  #define PWM_CFG_CMP3IP      0x80000000
#define TOFF_PWM_COUNT      0x0008
#define TOFF_PWM_S          0x0010
#define TOFF_PWM_CMP0       0x0020
#define TOFF_PWM_CMP1       0x0024
#define TOFF_PWM_CMP2       0x0028
#define TOFF_PWM_CMP3       0x002C


/*
 *  SPI
 */
#define TADR_SPI0_BASE      (SPI0_CTRL_ADDR)
#define TADR_SPI1_BASE      (SPI1_CTRL_ADDR)
#define TADR_SPI2_BASE      (SPI2_CTRL_ADDR)
#define TOFF_SPI_SCKDIV     0x0000
#define TOFF_SPI_SCKMODE    0x0004
  #define SPI_SCK_PHA         0x00000001
  #define SPI_SCK_POL         0x00000002
#define TOFF_SPI_CSID       0x0010
#define TOFF_SPI_CSDEF      0x0014
#define TOFF_SPI_CSMODE     0x0018
  #define SPI_CSMODE_AUTO     0
  #define SPI_CSMODE_HOLD     2
  #define SPI_CSMODE_OFF      3
#define TOFF_SPI_DCSSCK     0x0028
#define TOFF_SPI_DSCKCS     0x002A
#define TOFF_SPI_DINTERCS   0x002C
#define TOFF_SPI_DINTERXFR  0x002E

#define TOFF_SPI_FMT        0x0040
  #define SPI_PROTO_S         0
  #define SPI_PROTO_D         1
  #define SPI_PROTO_Q         2
  #define SPI_FMT_PROTO       0x00000003
  #define SPI_FMT_ENDIAN_MSB  0x00000000
  #define SPI_FMT_ENDIAN_LSB  0x00000004
  #define SPI_FMT_DIR_RX      0x00000000
  #define SPI_FMT_DIR_TX      0x00000008
  #define SPI_FMT_LEN         0x000F0000
#define TOFF_SPI_TXFIFO     0x0048
  #define SPI_TXFIFO_FULL     0x80000000
#define TOFF_SPI_RXFIFO     0x004C
  #define SPI_RXFIFO_EMPTY    0x80000000
#define TOFF_SPI_TXCTRL     0x0050
  #define SPI_TXWM(x)         ((x) & 0xffff)
#define TOFF_SPI_RXCTRL     0x0054
  #define SPI_RXWM(x)         ((x) & 0xffff)

#define TOFF_SPI_FCTRL      0x0060
  #define SPI_FCTRL_EN        0x0000001

#define TOFF_SPI_FFMT       0x0064
  #define SPI_INSN_CMD_EN     0x00000001
  #define SPI_INSN_ADDR_LEN(x)    (((x) & 0x7) << 1)
  #define SPI_INSN_PAD_CNT(x)     (((x) & 0xf) << 4)
  #define SPI_INSN_CMD_PROTO(x)   (((x) & 0x3) << 8)
  #define SPI_INSN_ADDR_PROTO(x)  (((x) & 0x3) << 10)
  #define SPI_INSN_DATA_PROTO(x)  (((x) & 0x3) << 12)
  #define SPI_INSN_CMD_CODE(x)    (((x) & 0xff) << 16)
  #define SPI_INSN_PAD_CODE(x)    (((x) & 0xff) << 24)

#define TOFF_SPI_IE         0x0070
#define TOFF_SPI_IP         0x0074
  #define SPI_IP_TXWM         0x00000001
  #define SPI_IP_RXWM         0x00000002

#define SPI1_NUM_SS       (4)
#define SPI2_NUM_SS       (1)

#endif /* _SIFIVE_FE310_H_ */
