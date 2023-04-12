ENTRY(user_start);

SRAM_VADDR  = 0x20000400;
SRAM_PADDR  = 0x20000400;
SRAM_SIZE   = 0x00002000;

MEMORY
{
    SRAM   (rwx) : ORIGIN =  SRAM_VADDR, LENGTH =  SRAM_SIZE
}

SECTIONS
{
    . = 0x0;

    .text :
    {
        *(.text)
        *(.rodata)
    } > SRAM AT >SRAM

    .data :
    {
        *(.data)
    } >SRAM AT >SRAM

    .bss :
    {
        . = ALIGN(4);
        __bss_start_vma = .;

        *(.bss)

        . = ALIGN(4);
        __bss_end_vma = .;
    } > SRAM AT >SRAM

    /DISCARD/ :
    {
        *(.ARM.attributes)
        *(.comment)
        *(.symtab)
    }
}
