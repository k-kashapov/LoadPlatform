.syntax unified

.section .text

.thumb_func
.global __reset_handler
__reset_handler:

    // Run user code
    blx umain

__halt:
	b __halt
