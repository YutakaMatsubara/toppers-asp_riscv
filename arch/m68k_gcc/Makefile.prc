#
#		Makefile�Υץ��å���¸����M68040�ѡ�
#

#
#  GNU��ȯ�Ķ��Υ������åȥ������ƥ���������
#
GCC_TARGET = m68k-unknown-elf

#
#  �ץ��å���¸���ǥ��쥯�ȥ�̾�����
#
PRCDIR = $(SRCDIR)/arch/$(PRC)_$(TOOL)

#
#  ����ѥ��륪�ץ����
#
COPTS := $(COPTS) -m68020-40 -msoft-float
LDFLAGS := $(LDFLAGS) -msoft-float

#
#  �����ͥ�˴ؤ������
#
KERNEL_DIR := $(KERNEL_DIR) $(PRCDIR)
KERNEL_ASMOBJS := $(KERNEL_ASMOBJS) prc_support.o
KERNEL_COBJS := $(KERNEL_COBJS) prc_config.o

#
#  ����ե�����졼���ط����ѿ������
#
CFG_TABS := $(CFG_TABS) --cfg1-def-table $(PRCDIR)/prc_def.csv

#
#  ���ե��åȥե����������Τ�������
#
OFFSET_TF = $(PRCDIR)/prc_offset.tf
