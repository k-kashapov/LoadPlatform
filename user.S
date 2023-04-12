.syntax unified

.section .text

.global user_start
user_start:

    .word api_ptr

.thumb_func
.global __reset_handler
__reset_handler:

    // Fill .bss section with zeros:
	ldr r1, __bss_start_vma_val
	ldr r2, __bss_end_vma_val

__loop_fill_bss_section:
	cmp r1, r2 
	beq __loop_fill_bss_section_end

	ldr r4, =0
	str r4, [r1, #0]

	adds r1, r1, #4
	b __loop_fill_bss_section
__loop_fill_bss_section_end:

    // Run user code
    blx main

__halt:
	b __halt

.align
__bss_start_vma_val:
.word __bss_start_vma
__bss_end_vma_val:
.word __bss_end_vma
