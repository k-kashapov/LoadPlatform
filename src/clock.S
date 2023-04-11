.syntax unified
.section .text

# Waits for a given time in milliseconds.
# Expects: r0 - time
# Return:  none
.global timing_imperfect_delay

.thumb_func
timing_imperfect_delay:

push {r7, lr}

big_loop:
    # 1 cycle
    cmp r0, #0

    # 1 cycle if not taken
    ble end
    
    # 2 cycles
    ldr r1, =9600
    
    # Entire loop lasts 5 cycles
    loop:
        subs r1, #1
        cmp  r1, #0
        bhi loop

    # We do 9600 loops = 48000 cycles = 1 ms

    # 1 cycle
    subs r0, #1

    # 3 cycles
    b big_loop

end:
    pop {r7, pc}
