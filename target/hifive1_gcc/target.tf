$ 
$ 		パス2のターゲット依存テンプレート（HIFIVE1用）
$ 

$ 
$  有効な割込み番号，割込みハンドラ番号
$ 
$INTNO_VALID = RANGE(0, (TMAX_INTNO-1))$
$INHNO_VALID = INTNO_VALID$

$ 
$  ATT_ISRで使用できる割込み番号とそれに対応する割込みハンドラ番号
$ 
$INTNO_ATTISR_VALID = INTNO_VALID$
$INHNO_ATTISR_VALID = INHNO_VALID$

$ 
$  DEF_INT／DEF_EXCで使用できる割込みハンドラ番号／CPU例外ハンドラ番号
$ 
$INHNO_DEFINH_VALID = INTNO_VALID$
$EXCNO_DEFEXC_VALID = INHNO_VALID$

$ 
$  CFG_INTで使用できる割込み番号と割込み優先度
$ 
$INTNO_CFGINT_VALID = INTNO_VALID$
$INTPRI_CFGINT_VALID = { -7,-6,...,-1 }$

$ 
$  標準テンプレートファイルのインクルード
$ 
$INCLUDE "kernel/kernel.tf"$

/*$NL$
$SPC$*  Target-dependent Definitions (HIFIVE1)$NL$
$SPC$*/$NL$
$NL$

$ 
$  ベクターテーブル
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
$   CFG_INTのターゲット依存のエラーチェックと_kernel_bitpat_cfgintの生成
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
$   //boost のバージョンによって挙動が変わるための対策
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
