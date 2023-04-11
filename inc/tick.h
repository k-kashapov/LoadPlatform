#ifndef TICK_H
#define TICK_H

//-------------------
// SysTick registers
//-------------------

#include "general.h"
#include "RCC.h"

#define SYSTICK_CSR   (volatile uint32_t*)(uintptr_t)0xE000E010U // SysTick Control and Status Register
#define SYSTICK_RVR   (volatile uint32_t*)(uintptr_t)0xE000E014U // SysTick Reload Value Register
#define SYSTICK_CVR   (volatile uint32_t*)(uintptr_t)0xE000E018U // SysTick Current Value Register
#define SYSTICK_CALIB (volatile uint32_t*)(uintptr_t)0xE000E01CU // SysTick Calibration Value Register

#define SYSTICK_ENABLE    0U // (SYSTICK_CSR)
#define SYSTICK_TICKINT   1U // (SYSTICK_CSR)
#define SYSTICK_CLKSOURCE 2U // (SYSTICK_CSR)

#define SYSTICK_VAL_WIDTH 24U

void systick_init(uint32_t period_ms);

#endif // TICK_H