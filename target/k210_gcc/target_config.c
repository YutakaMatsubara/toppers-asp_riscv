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
 *  @(#) $Id: target_config.c 2246 2019-10-03 17:47:40Z roi $
 */

/*
 *		�������åȰ�¸�⥸�塼���K210�ѡ�
 */

#include "kernel_impl.h"
#include <sil.h>

#include "target_syssvc.h"
#include "target_serial.h"

/*
 *  MACHINE����ߤ������ߥϥ�ɥ��ƤӽФ�
 */
static void
machine_interrupt(unsigned long mcause, void *p_excinf)
{
	uint32_t hart_id = read_csr(mhartid);
	uint32_t int_num = sil_rew_mem((uint32_t *)(TADR_PLIC_BASE+TOFF_PLIC_CLAIM+(hart_id * NUM_PLIC_THRESHOLD)));
	uint8_t  threshold = (uint8_t)current_ithreshold();
	void (*volatile handler)(void);
	uint8_t  priority;

	if(int_num < TMAX_INTNO){
		if((handler = (void (*volatile)(void))vector_table[int_num]) != NULL){
			priority = current_ipriority(int_num);
			set_ithreshold((uint32_t)priority);
			set_csr(mie, kernel_mie);
			sil_wrw_mem((uint32_t *)(TADR_PLIC_BASE+TOFF_PLIC_CLAIM+(hart_id * NUM_PLIC_THRESHOLD)), int_num);
			handler();
			clear_csr(mie, KERNEL_MIE);
			set_ithreshold((uint32_t)threshold);
		}
	}
	else{
		syslog(LOG_EMERG, "Illegal global interrupt NO = %d", int_num);
		sil_wrw_mem((uint32_t *)(TADR_PLIC_BASE+TOFF_PLIC_CLAIM+(hart_id * NUM_PLIC_THRESHOLD)), int_num);
	}
}

/*
 *  �������åȰ�¸�ν����
 */
void
target_initialize(void)
{
	extern void	hardware_init_hook(void);
	void (*volatile fp)(void) = hardware_init_hook;
	unsigned long hart_id = read_csr(mhartid);
	uint32_t i, off, len;

	if(hart_id == 0){
		/*
		 *  hardware_init_hook�ؤΥݥ��󥿤򡤰�övolatile����Τ���fp����
		 *  �����Ƥ���Ȥ��Τϡ�0�Ȥ���Ӥ���Ŭ���Ǻ������ʤ��褦�ˤ��뤿
		 *  ��Ǥ��롥
		 */
		if (fp != 0) {
			(*fp)();
		}

		/*
		 *  �ץ��å���¸�ν����
		 */
		prc_initialize();

		/*
		 *  �Хʡ������ѤΥ��ꥢ������
		 */
		target_uart_init(SIO_PORTID);
	}

	/*
	 *  ����ߴ�Ϣ�ν����
	 *
	 *  ����ߥ�٥�ơ��֥��HI�����ꤹ�롥
	 *  PLIC���Ф��Ƴ���߶ػߡ���٥��0�����쥷��ۡ���ɤ�0�����ꤹ�롥
	 */
	off = TOFF_PLIC_ENABLE + (hart_id * (NUM_PLIC_ENABLE / 8));
	len = (TMAX_INTNO + 8) / 8;
	for(i = 0 ; i < len ; i += 4){
		sil_wrw_mem((uint32_t *)(TADR_PLIC_BASE + off + i), 0);
	}

	/*
	 *  ����ߥ��쥷��ۡ���ɤ�0������
	 */
	off = (TOFF_PLIC_THRESHOLD + (hart_id * NUM_PLIC_THRESHOLD));
	sil_wrw_mem((uint32_t *)(TADR_PLIC_BASE+off), 0);

	if(hart_id == 0){
		/*
		 *  �����ͥ���٤�0������
		 */
		len = (TMAX_INTNO + 1) * sizeof(uint32_t);
		for(i = 0 ; i < len ; i += sizeof(uint32_t)){
			sil_wrw_mem((uint32_t *)(TADR_PLIC_BASE + TOFF_PLIC_PRIORITY + i), 0);
		}
	}
	else{
		for(;;){
			Asm("wfi":::"memory");
		}
	}

	/*
	 *  MACHINE���������
	 */
	x_machine_inh(IRQ_MACHINE_EXTERNAL, (FP)machine_interrupt);
}

/*
 *  �������åȰ�¸�ν�λ����
 */
void
target_exit(void)
{
	unsigned long hart_id = read_csr(mhartid);
	uint32_t i, off, len;

	/*
	 *  �ץ��å���¸�ν�λ����
	 */
	prc_terminate();

	/*
	 *  ���٤Ƥγ���ߤ�ޥ������롥
	 */
	off = TOFF_PLIC_ENABLE + (hart_id * (NUM_PLIC_ENABLE / 8));
	len = (TMAX_INTNO + 8) / 8;
	for(i = 0 ; i < len ; i += 4){
		sil_wrw_mem((uint32_t *)(TADR_PLIC_BASE + off + i), 0);
	}

	/*
	 *  ��ȯ�Ķ���¸�ν�λ����
	 */
	while(1);
}

/*
 *  ���쥮��顼��PDIC����߽���
 */
void
default_plic_handler(void)
{
	syslog(LOG_EMERG, "\nUnregistered plic Interrupt occurs.");

	target_exit();
}

/*
 *  �����ƥ�������٥���ϤΤ����ʸ������
 */
void
target_fput_log(char c)
{
	if (c == '\n') {
		sio_pol_snd_chr('\r', SIO_PORTID);
	}
	sio_pol_snd_chr(c, SIO_PORTID);
}

/*
 *  ������׵�饤���°��������
 *
 *  ASP�����ͥ�Ǥ����Ѥ����ꤷ�ơ��ѥ�᡼�����顼�ϥ����������ǥ�����
 *  �����Ƥ��롥cfg_int�����ӥ���������ߤ�����ˤϡ����顼���֤��褦
 *  �ˤ��٤��Ǥ�����
 */
void
x_config_int(INTNO intno, ATR intatr, PRI intpri)
{
	uint32_t	priority;

	assert(VALID_INTNO_CFGINT(intno));
	assert(TIRQ_NMI <= intpri && intpri <= TIRQ_LEVEL1);
	priority = intpri - TIRQ_NMI;

	/*
	 *  ����ߤΥޥ���
	 *
	 *  ����ߤ�����դ����ޤޡ���٥�ȥꥬ�����å��ȥꥬ������䡤��
	 *  ����ͥ���٤������Ԥ��Τϴ��ʤ��ᡤ�����°���ˤ�����餺��
	 *  ��ö�ޥ������롥
	 */
	(void) x_disable_int(intno);

	/*
	 *  �����ͥ���٤�����
	 */
	set_ipriority(intno, priority);

	/*
	 *  ����ߤΥޥ��������ɬ�פʾ���
 	 */
	if ((intatr & TA_ENAINT) != 0U) {
		(void) x_enable_int(intno);
	}
}

