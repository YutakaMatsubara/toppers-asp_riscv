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
 *  @(#) $Id: target_config.h 1952 2019-09-20 19:58:45Z roi $
 */

/*
 *		�������åȰ�¸�⥸�塼���HIFIVE1�ѡ�
 *
 *  �����ͥ�Υ������åȰ�¸���Υ��󥯥롼�ɥե����롥kernel_impl.h�Υ���
 *  ���åȰ�¸���ΰ����դ��Ȥʤ롥
 */

#ifndef TOPPERS_TARGET_CONFIG_H
#define TOPPERS_TARGET_CONFIG_H

/*
 *  �������åȥ����ƥ�Υϡ��ɥ������񸻤����
 */
#include "sifive-fe310.h"

/*
 *  �������å�����Υ��֥�������°��
 */
#define TARGET_INHATR	TA_NONKERNEL	/* �����ͥ�������γ���� */

/*
 *  ���顼�����å���ˡ�λ���
 */
#define CHECK_STKSZ_ALIGN	4	/* �����å��������Υ��饤��ñ�� */
#define CHECK_FUNC_ALIGN	2	/* �ؿ��Υ��饤��ñ�� */
#define CHECK_FUNC_NONNULL		/* �ؿ�����NULL�����å� */
#define CHECK_STACK_ALIGN	4	/* �����å��ΰ�Υ��饤��ñ�� */
#define CHECK_STACK_NONNULL		/* �����å��ΰ����NULL�����å� */
#define CHECK_MPF_ALIGN		4	/* ����Ĺ����ס����ΰ�Υ��饤��ñ�� */
#define CHECK_MPF_NONNULL		/* ����Ĺ����ס����ΰ����NULL�����å� */
#define CHECK_MB_ALIGN		4	/* �����ΰ�Υ��饤��ñ�� */

/*
 *  �ȥ졼�����˴ؤ�������
 */
#ifdef TOPPERS_ENABLE_TRACE
#include "logtrace/trace_config.h"
#endif /* TOPPERS_ENABLE_TRACE */

/*
 *  �ǥե���Ȥ��󥿥�������ƥ������ѤΥ����å��ΰ�����
 */
#define DEFAULT_ISTKSZ		0x1000U
#define DEFAULT_ISTK		(void *)(0x80004000U - DEFAULT_ISTKSZ)


#ifndef TOPPERS_MACRO_ONLY

/*
 *  ������ֹ���ϰϤ�Ƚ��
 */
#define VALID_INTNO(intno)          ((1 <= (intno)) && ((intno) <= TMAX_INTNO))
#define	VALID_INTNO_CREISR(intno)	VALID_INTNO(intno)
#define VALID_INTNO_DISINT(intno)	VALID_INTNO(intno)
#define VALID_INTNO_CFGINT(intno)	VALID_INTNO(intno)

/*
 *  PLIC THRESHOLD�ʥϡ��ɥ������γ����ͥ���٥ޥ���������ɽ���ˤθ����ͤ��ɽФ�
 */
Inline uint32_t
current_ithreshold(void)
{
	unsigned long hard_id = read_csr(mhartid);
	uint32_t off = TOFF_PLIC_THRESHOLD + (hard_id * NUM_PLIC_THRESHOLD);
	return sil_rew_mem((uint32_t *)(TADR_PLIC_BASE+off));
}

/*
 *  PLIC THRESHOLD�ʥϡ��ɥ������γ����ͥ���٥ޥ���������ɽ���ˤθ����ͤ�����
 */
Inline void
set_ithreshold(uint32_t threshold)
{
	unsigned long hard_id = read_csr(mhartid);
	uint32_t off = TOFF_PLIC_THRESHOLD + (hard_id * NUM_PLIC_THRESHOLD);
	sil_wrw_mem((uint32_t *)(TADR_PLIC_BASE+off), threshold);
}

/*
 *  PLIC �����ͥ���١ʥϡ��ɥ������γ����ͥ���٥ޥ���������ɽ���ˤθ����ͤ��ɽФ�
 */
Inline uint32_t
current_ipriority(INTNO intno)
{
	uint32_t off = TOFF_PLIC_PRIORITY + (intno * sizeof(uint32_t));
	return (uint32_t)sil_reb_mem((uint8_t *)(TADR_PLIC_BASE+off));
}

/*
 *  PLIC �����ͥ���١ʥϡ��ɥ������γ����ͥ���٥ޥ���������ɽ���ˤθ����ͤ�����
 */
Inline void
set_ipriority(INTNO intno, uint32_t priority)
{
	uint32_t off = TOFF_PLIC_PRIORITY + (intno * sizeof(uint32_t));
	sil_wrb_mem((uint8_t *)(TADR_PLIC_BASE+off), (uint8_t)priority);
}

/*
 *  PLIC����ߥϥ�ɥ�ơ��֥�
 */
extern const FP vector_table[];

/*
 *  �����°�������ꤵ��Ƥ��뤫��Ƚ�̤��뤿����ѿ���kernel_cfg.c��
 */
extern const uint32_t	bitpat_cfgint[];

/*
 *  ������׵�ػߥե饰�Υ��å�
 *
 *  �����°�������ꤵ��Ƥ��ʤ�������׵�饤����Ф��Ƴ�����׵�ػ�
 *  �ե饰�򥻥åȤ��褦�Ȥ������ˤϡ�false���֤���
 */
Inline bool_t
x_disable_int(INTNO intno)
{
	unsigned long hart_id = read_csr(mhartid);
	uint32_t	bitpat = 1 << (intno & 0x1f);
	uint32_t    bitpno = intno >> 5;
	uint32_t	off = TOFF_PLIC_ENABLE + (hart_id * NUM_PLIC_ENABLE) + (intno >> 3);

	if ((bitpat_cfgint[bitpno] & bitpat) == 0U) {
		return(false);
	}
	sil_wrb_mem((uint8_t *)(TADR_PLIC_BASE+off), (sil_reb_mem((uint8_t *)(TADR_PLIC_BASE+off)) & ~(1 << (intno & 7))));
	return(true);
}


#define t_disable_int(intno)	x_disable_int(intno)
#define i_disable_int(intno)	x_disable_int(intno)

/*
 *  ������׵�ػߥե饰�Υ��ꥢ
 *
 *  �����°�������ꤵ��Ƥ��ʤ�������׵�饤����Ф��Ƴ�����׵�ػ�
 *  �ե饰�򥯥ꥢ���褦�Ȥ������ˤϡ�false���֤���
 */
Inline bool_t
x_enable_int(INTNO intno)
{
	unsigned long hart_id = read_csr(mhartid);
	uint32_t	bitpat = 1 << (intno & 0x1f);
	uint32_t    bitpno = intno >> 5;
	uint32_t	off = TOFF_PLIC_ENABLE + (hart_id * NUM_PLIC_ENABLE) + (intno >> 3);

	if ((bitpat_cfgint[bitpno] & bitpat) == 0U) {
		return(false);
	}

	sil_wrb_mem((uint8_t *)(TADR_PLIC_BASE+off),
			(sil_reb_mem((uint8_t *)(TADR_PLIC_BASE+off)) | (1 << (intno & 7))));
	return(true);
}

#define t_enable_int(intno)		x_enable_int(intno)
#define i_enable_int(intno)		x_enable_int(intno)

/*
 *  ������׵�Υ��ꥢ
 */
Inline void
x_clear_int(INTNO intno)
{
}

#define t_clear_int(intno)		x_clear_int(intno)
#define i_clear_int(intno)		x_clear_int(intno)

/*
 *  ������׵�Υ����å�
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
 *  ����ߥϥ�ɥ������
 *
 *  �٥��ȥ��ֹ�inhno�γ���ߥϥ�ɥ�ν��������������Ϥ�int_entry����
 *  �ꤹ�롥
 */
Inline void
x_define_inh(INHNO inhno, FP int_entry)
{
}


/*
 *  ������׵�饤���°��������
 *
 *  DVE-68K/40��IRC�Ǥϡ�������׵�饤��γ����ͥ���٤�NMI����ꤹ��
 *  ���Ȥ��Ǥ����ᡤ-7��Ϳ�����NMI�����ꤵ��뤳�ȤȤ���ʥ������å���
 *  ���γ�ĥ�ˡ�
 */
extern void	x_config_int(INTNO intno, ATR intatr, PRI intpri);

/*
 *  ����ߥϥ�ɥ��������ɬ�פ�IRC���
 *
 *  ���å��ȥꥬ�ξ��ˤϡ�������׵�򥯥ꥢ���롥���å��ȥꥬ�����
 *  ��ȥꥬ��������Ǥ�����⡤���ߤ������ͤ򸫤��˥��ꥢ���Ƥ��롥
 *  ��٥�ȥꥬ�ξ��⥯�ꥢ�����򤷤ƺ����٤��ʤ�������Ŭ���Ǿä���
 *  ���Ȥ���Ԥ��ơ����ꥢ���ʤ����ȤȤ��Ƥ��롥
 */
Inline void
i_begin_int(INTNO intno)
{
}

/*
 *  ����ߥϥ�ɥ�νи���ɬ�פ�IRC���
 *
 *  DVE-68K/40�Ǥ�ɬ�פ�IRC���Ϥʤ���
 */
Inline void
i_end_int(INTNO intno)
{
}

/*
 *  ����ߥϥ�ɥ�ν���������������
 */

/*
 *  ����ߥϥ�ɥ�ν����������Υ�٥����ޥ���
 */
#define INT_ENTRY(inhno, inthdr)	_kernel_##inthdr##_##inhno

/*
 *  LOG_INH_ENTER���ޥ����������Ƥ�����ˡ�CALL_LOG_INH_ENTER��
 *  inhno_num��ѥ�᡼���Ȥ���log_inh_enter��ƤӽФ�������֥���쥳��
 *  �ɤ˥ޥ���������롥
 */
#ifdef LOG_INH_ENTER

#define CALL_LOG_INH_ENTER(inhno_num) \
"	li a0," #inhno_num "			\n"  /* inhno_num��ѥ�᡼���� */ \
"	jal _kernel_log_inh_enter		\n"  /* log_inh_enter��ƤӽФ� */

#else /* LOG_INH_ENTER */
#define CALL_LOG_INH_ENTER(inhno_num)
#endif /* LOG_INH_ENTER */

#ifdef LOG_INH_LEAVE

/*
 *  CALL_LOG_INH_LEAVE��inhno_num��ѥ�᡼���Ȥ���log_inh_leave���
 *  �ӽФ�������֥���쥳���ɤ˥ޥ���������롥
 */
#define CALL_LOG_INH_LEAVE(inhno_num) \
"	li a0," #inhno_num "			\n"  /* inhno_num��ѥ�᡼���� */ \
"	jal _kernel_log_inh_leave		\n"  /* log_inh_leave��ƤӽФ� */

/*
 *  LOG_INH_LEAVE���ޥ����������Ƥ�����γ���ߥϥ�ɥ�ν�����������
 *  ����ߥϥ�ɥ�򥵥֥롼���󥳡��뤷����äƤ����顤�ȥ졼������
 *  �����塤�ƤӽФ����ʬ�����롥
 */
#define INTHDR_ENTRY(inhno, inhno_num, inthdr) \
extern void _kernel_##inthdr##_##inhno(void); \
asm(".text							\n" \
"_kernel_" #inthdr "_" #inhno ":	\n" \
"	addi sp, sp, -16				\n"	 /* ��¸�ΰ����� */ \
"	sw ra, 12(sp)					\n"	 /* return address�򥻡��� */ \
	CALL_LOG_INH_ENTER(inhno_num) \
"	jal " #inthdr "				\n"  /* ����ߥϥ�ɥ��ƤӽФ� */ \
	CALL_LOG_INH_LEAVE(inhno_num) \
"	lw ra, 12(sp)					\n"	 /* return address��ꥹ�ȥ� */ \
"	addi sp, sp, 16					\n"	 /* ��¸�ΰ���� */ \
"	ret								\n");/* �꥿���� */


#elif defined(LOG_INH_ENTER)

/*
 *  LOG_INH_LEAVE���ޥ����������Ƥ��ʤ���LOG_INH_ENTER���������Ƥ���
 *  ���γ���ߥϥ�ɥ�ν�����������log_inh_enter��¹Ը塢
 *  �ϥ�ɥ��ƤӽФ����ƤӽФ����ʬ�����롥
 */
#define INTHDR_ENTRY(inhno, inhno_num, inthdr) \
extern void _kernel_##inthdr##_##inhno(void); \
asm(".text							\n" \
"_kernel_" #inthdr "_" #inhno ":	\n" \
"	addi sp, sp, -16				\n"	 /* ��¸�ΰ����� */ \
"	sw ra, 12(sp)					\n"	 /* return address�򥻡��� */ \
	CALL_LOG_INH_ENTER(inhno_num) \
"	jal " #inthdr "					\n"	 /* ����ߥϥ�ɥ��ʬ�� */ \
"	lw ra, 12(sp)					\n"	 /* return address��ꥹ�ȥ� */ \
"	addi sp, sp, 16					\n"	 /* ��¸�ΰ���� */ \
"	ret								\n");/* �꥿���� */

#else

/*
 *  LOG_INH_ENTER/LOG_INH_LEAVE���ޥ����������Ƥ��ʤ���硢ra���ݻ������ޤ�
 *  �ϥ�ɥ�˥����פ��롥
 */
#define INTHDR_ENTRY(inhno, inhno_num, inthdr) \
extern void _kernel_##inthdr##_##inhno(void); \
asm(".text							\n" \
"_kernel_" #inthdr "_" #inhno ":	\n" \
"	j " #inthdr "					\n");	 /* ����ߥϥ�ɥ��ʬ�� */ \

#endif /* LOG_INH_LEAVE */

#endif /* TOPPERS_MACRO_ONLY */

#ifndef TOPPERS_MACRO_ONLY

/*
 *  �������åȥ����ƥ��¸�ν����
 */
extern void	target_initialize(void);

/*
 *  �������åȥ����ƥ�ν�λ
 *
 *  �����ƥ��λ������˻Ȥ���
 */
extern void	target_exit(void) NoReturn;

/*
 *  ���쥮��顼��PDIC����߽���
 */
extern void default_plic_handler(void);

#endif /* TOPPERS_MACRO_ONLY */

/*
 *  ���������Ԥ��Τ��������������SIL�Υ������åȰ�¸����
 */
#define SIL_DLY_TIM1    1
#ifdef DEFAULT_CLOCK
#define SIL_DLY_TIM2    7
#else
#define SIL_DLY_TIM2    110
#endif

/*
 *  �ץ��å���¸�⥸�塼���RISCV�ѡ�
 */
#include "riscv_gcc/prc_config.h"

#endif /* TOPPERS_TARGET_CONFIG_H */
