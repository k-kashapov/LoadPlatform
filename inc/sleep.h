#pragma once 

//=========================================================

#include <stdint.h>

//=========================================================

#define CPU_FREQENCY 48000000U // CPU frequency: 48 MHz
#define ONE_MILLISECOND CPU_FREQENCY / 1000U
#define ONE_MICROSECOND ONE_MILLISECOND / 1000U

//=========================================================

static inline void NON_ACCURATE_sleep(unsigned us)
{
    for (uint32_t i = 0; i < us * ONE_MICROSECOND; ++i)
    {
        __asm__ volatile("nop");
    }
}