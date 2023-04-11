#include "tick.h"
#include "general.h"

//-----------------------
// SysTick configuration
//-----------------------

void systick_init(uint32_t period_us) {
    // (0) Read STM32F051 SysTick configuration:
    // Assumptions:
    // - There is a reference clock and it can be chosen as clock source.
    // - The SYST_CALIB SKEW bit is 1.
    uint32_t reload_value = period_us * (CPU_FREQENCY / 1000000U) / 8;

    // (1) Program the reload value:
    *SYSTICK_RVR = reload_value & MASK_LOWER(SYSTICK_VAL_WIDTH);

    // (2) Clear the current value:
    *SYSTICK_CVR = 0U;

    // (3) Program the CSR:
    BIT_SET(*SYSTICK_CSR, SYSTICK_TICKINT);
    BIT_SET(*SYSTICK_CSR, SYSTICK_ENABLE);
}
