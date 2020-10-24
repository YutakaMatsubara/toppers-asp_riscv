/*
 *  @(#) $Id: riscv64elf.ld 127 2019-09-17 17:37:39Z roi $
 */

OUTPUT_ARCH(riscv)

PROVIDE(hardware_init_hook = 0);
PROVIDE(software_init_hook = 0);
PROVIDE(software_term_hook = 0);
STARTUP(start.o)

SECTIONS
{
    __stack_size = DEFINED(__stack_size) ? __stack_size : 8K;

    .init :
    {
        KEEP (*(.init))
    }
    .text :
    {
        __text = . ;
        *(.text .stub .text.* .gnu.linkonce.t.*)

    }
    .fini :
    {
        KEEP (*(.fini))
    }
    _etext = . ;
    PROVIDE (etext = .) ;
    .rodata :
    {
        *(.rodata .rodata.* .gnu.linkonce.r.*)
    }
    . = ALIGN(8);
    __idata_start = . ;
    .data :
    {
        __data_start = . ;
        /* Writable data segment (.data segment) */
        *(.data .data.*)
        . = ALIGN(8);
        PROVIDE( __global_pointer$ = ABSOLUTE(.) + 0x800);
    }
    .eh_frame : { KEEP (*(.eh_frame)) }
    .gcc_except_table : { *(.gcc_except_table) }
    .ctors :
    {
        KEEP (*crtbegin.o(.ctors))
        KEEP (*(EXCLUDE_FILE (*crtend.o ) .ctors))
        KEEP (*(SORT(.ctors.*)))
        KEEP (*(.ctors))
    }
    .dtors :
    {
        KEEP (*crtbegin.o(.dtors))
        KEEP (*(EXCLUDE_FILE (*crtend.o ) .dtors))
        KEEP (*(SORT(.dtors.*)))
        KEEP (*(.dtors))
    }
    __idata_end = __idata_start + SIZEOF(.data) ;
    _edata  = . ;
    PROVIDE (edata = .) ;
    . = ALIGN(8) ;
    __bss_start = . ;
    .bss :
    {
        *(.bss)
        *(.sbss)
        *(COMMON)
    }
    _end = . ;
    __bss_end = . ;
    PROVIDE (end = .) ;
    .comment        0 : { *(.comment) }
    .debug          0 : { *(.debug) }
    .line           0 : { *(.line) }
    .debug_srcinfo  0 : { *(.debug_srcinfo) }
    .debug_sfnames  0 : { *(.debug_sfnames) }
    .debug_aranges  0 : { *(.debug_aranges) }
    .debug_pubnames 0 : { *(.debug_pubnames) }
}

