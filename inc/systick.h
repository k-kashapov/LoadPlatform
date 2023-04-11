#pragma once 

//---------------------------------------------------------

#include "modregs.h"

//=========================================================

#define STM_SYSTICK_TENMS_REF_FREQ 6000000U

// SysTick

#define SYSTICK_CSR   (volatile uint32_t*)(uintptr_t)0xE000E010U // RW - SysTick Control and Status Register
#define SYSTICK_RVR   (volatile uint32_t*)(uintptr_t)0xE000E014U // RW - SysTick Reload Value Register
#define SYSTICK_CVR   (volatile uint32_t*)(uintptr_t)0xE000E018U // RW - SysTick Current Value Register
#define SYSTICK_CALIB (volatile uint32_t*)(uintptr_t)0xE000E01CU // RO - SysTick Calibration Value Register

//---------------------------------------------------------

// SysTick Control and Status Register

#define SYSTICK_CSR_ENABLE 0 // Enables the counter
                             // 0 = counter disabled
                             // 1 = counter enabled

#define SYSTICK_ENABLE() SET_BIT(SYSTICK_CSR, SYSTICK_CSR_ENABLE)
#define SYSTICK_DISABLE() CLEAR_BIT(SYSTICK_CSR, SYSTICK_CSR_ENABLE)
#define SYSTICK_IS_ENABLE() CHECK_BIT(SYSTICK_CSR, SYSTICK_CSR_ENABLE)

#define SYSTICK_CSR_TICKINT 1 // Enables SysTick exception request 
                              // 0 = = counting down to zero does not assert the SysTick exception request
                              // 1 = counting down to zero to asserts the SysTick exception request

#define SYSTICK_EXC_ENABLE() SET_BIT(SYSTICK_CSR, SYSTICK_CSR_TICKINT)
#define SYSTICK_EXC_DISABLE() CLEAR_BIT(SYSTICK_CSR, SYSTICK_CSR_TICKINT)
#define SYSTICK_EXC_IS_ENABLE() CHECK_BIT(SYSTICK_CSR, SYSTICK_CSR_TICKINT)

#define SYSTICK_CSR_CLKSOURCE 2 // Selects the SysTick timer clock source
                                // 0 = reference 
                                // 1 = processor

#define SYSTICK_SET_SRC_REF() CLEAR_BIT(SYSTICK_CSR, SYSTICK_CSR_CLKSOURCE)
#define SYSTICK_SET_SRC_CPU() SET_BIT(SYSTICK_CSR, SYSTICK_CSR_CLKSOURCE)

#define SYSTICK_CSR_COUNTFLAG 16 // Returns 1 if timer counted to 0 since the last read of this register

#define SYSTICK_GET_COUNTFLAG() CHECK_BIT(SYSTICK_CSR, SYSTICK_CSR_COUNTFLAG)

//---------------------------------------------------------

// SysTick Reload Value Register

#define SYSTICK_SET_RELOAD(reload_val) MODIFY_REG(SYSTICK_RVR, 0xFFFFFFU, reload_val)
#define SYSTICK_GET_RELOAD() CHECK_REG(SYSTICK_RVR, 0xFFFFFFU)

//---------------------------------------------------------

// SysTick Current Value Register

#define SYSTICK_SET_CURRENT(current_val) MODIFY_REG(SYSTICK_CVR, 0xFFFFFF, current_val)
#define SYSTICK_GET_CURRENT() CHECK_REG(SYSTICK_CVR, 0xFFFFFF)

//---------------------------------------------------------

// SysTick Calibration Value Register

#define SYSTICK_CALIB_NOREF 31 // Indicates whether the device provides a reference clock to the processor
                               // 0 = reference clock provided
                               // 1 = reference clock is not provided

#define SYSTICK_CALIB_SKEW  30 // Indicates whether the TENMS value is exact
                               // 0 = TENMS value is exact
                               // 1 = TENMS value is inexact, or not given

#define SYSTICK_GET_NOREF() CHECK_BIT(SYSTICK_CALIB, SYSTICK_CALIB_NOREF)
#define SYSTICK_GET_SKEW() CHECK_BIT(SYSTICK_CALIB, SYSTICK_CALIB_SKEW)

#define SYSTICK_GET_TENMS() SUPER_CHECK_REG(SYSTICK_CALIB, 0xFFFFFF, 0)
