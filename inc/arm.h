#ifndef ARM_H
#define ARM_H

inline __attribute__ ((always_inline)) void wfi(void) {
    __asm__ volatile ("wfi");
}

#endif // ARM_H
