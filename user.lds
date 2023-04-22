ENTRY(__reset_handler);

RAM_VADDR  = 0x20000500;
RAM_PADDR  = 0x20000500;
RAM_SIZE   = 0x00001700;

MEMORY
{
    RAM (rwx) : ORIGIN = RAM_VADDR, LENGTH = RAM_SIZE
}

SECTIONS
{
    . = 0x0;

    .text :
    {
        *(.text)
        *(.rodata)
        
    } > RAM AT >RAM

    .data :
    {
        *(.data)
        *(.bss)

    } >RAM AT >RAM

    /DISCARD/ :
    {
        *(.ARM.attributes)
        *(.comment)
        *(.symtab)
    }
}
