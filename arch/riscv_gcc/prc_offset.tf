$ 
$ 		���ե��åȥե����������ѥƥ�ץ졼�ȥե������RISC-V�ѡ�
$ 

$ 
$  ɸ��ƥ�ץ졼�ȥե�����Υ��󥯥롼��
$ 
$INCLUDE "kernel/genoffset.tf"$

$ 
$  ���ե��å��ͤΥޥ������������
$ 
$DEFINE("TCB_p_tinib", offsetof_TCB_p_tinib)$
$DEFINE("TCB_texptn", offsetof_TCB_texptn)$
$DEFINE("TCB_sp", offsetof_TCB_sp)$
$DEFINE("TCB_pc", offsetof_TCB_pc)$

$DEFINE("TINIB_exinf", offsetof_TINIB_exinf)$
$DEFINE("TINIB_task", offsetof_TINIB_task)$

$ 
$  �ӥåȥ��ե��å������Υޥ������������
$ 
$DEFINE_BIT("TCB_enatex", sizeof_TCB, "B")$
