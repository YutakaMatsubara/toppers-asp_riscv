$ 
$ 		�ѥ�2�Υ������åȰ�¸�ƥ�ץ졼�ȡ�HIFIVE1�ѡ�
$ 

$ 
$  ͭ���ʳ�����ֹ桤����ߥϥ�ɥ��ֹ�
$ 
$INTNO_VALID = RANGE(0, (TMAX_INTNO-1))$
$INHNO_VALID = INTNO_VALID$

$ 
$  ATT_ISR�ǻ��ѤǤ��������ֹ�Ȥ�����б��������ߥϥ�ɥ��ֹ�
$ 
$INTNO_ATTISR_VALID = INTNO_VALID$
$INHNO_ATTISR_VALID = INHNO_VALID$

$ 
$  DEF_INT��DEF_EXC�ǻ��ѤǤ������ߥϥ�ɥ��ֹ桿CPU�㳰�ϥ�ɥ��ֹ�
$ 
$INHNO_DEFINH_VALID = INTNO_VALID$
$EXCNO_DEFEXC_VALID = INHNO_VALID$

$ 
$  CFG_INT�ǻ��ѤǤ��������ֹ�ȳ����ͥ����
$ 
$INTNO_CFGINT_VALID = INTNO_VALID$
$INTPRI_CFGINT_VALID = { -7,-6,...,-1 }$

$ 
$  ɸ��ƥ�ץ졼�ȥե�����Υ��󥯥롼��
$ 
$INCLUDE "kernel/kernel.tf"$

/*$NL$
$SPC$*  Target-dependent Definitions (HIFIVE1)$NL$
$SPC$*/$NL$
$NL$

$ 
$  �٥������ơ��֥�
$ 
$NL$
$cfgint_num = TMAX_INTNO$

const FP _kernel_vector_table[
	$cfgint_num$
] = {$NL$ 

$FOREACH inhno INTNO_VALID$
	$IF LENGTH(INH.INHNO[inhno])$
		$TAB$(FP)(_kernel_
		$INH.INTHDR[inhno]$_
		$INH.INHNO[inhno]$),
	$ELSE$
		$TAB$(FP)(_kernel_default_plic_handler),
	$END$
	$SPC$$FORMAT("/* %d */", +inhno)$$NL$
$END$

$NL$};$NL$
$NL$

$ 
$   CFG_INT�Υ������åȰ�¸�Υ��顼�����å���_kernel_bitpat_cfgint������
$ 
$bitpat_cfgint_num = 0$
$bitpat_cfgint = 0$

const uint32_t	_kernel_bitpat_cfgint[
$IF (TMAX_INTNO & 0x0f) == 0x00 $
	$bitpat_cfgint_num = (TMAX_INTNO >> 5)$
$ELSE$
	$bitpat_cfgint_num = (TMAX_INTNO >> 5) + 1$
$END$
	$bitpat_cfgint_num$
] = {$NL$
$FOREACH num RANGE(0,(bitpat_cfgint_num-1))$
$   //boost �ΥС������ˤ�äƵ�ư���Ѥ�뤿����к�
$   //http://www.toppers.jp/TOPPERS-USERS/201004/msg00034.html
	$bitpat_cfgint = 1-1$
	$FOREACH inhno RANGE(num*32, (num*32)+31)$
		$IF LENGTH(INH.INHNO[inhno])$
			$bitpat_cfgint = bitpat_cfgint | (1 << (inhno & 0x01f))$
		$END$
	$END$
	$TAB$UINT32_C($FORMAT("0x%08x", bitpat_cfgint)$), $NL$
$END$

$NL$};$NL$
$NL$
