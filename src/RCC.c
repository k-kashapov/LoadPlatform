#include "RCC.h"
#include "general.h"
#include <stdint.h>

void board_clocking_init(uint16_t prediv, uint16_t pllmul, uint16_t ahb_div, uint16_t apb_div) {
    // (1) Clock HSE and wait for oscillations to setup.
    BIT_SET(*REG_RCC_CR, HSEON);
    while (!(BIT_READ(*REG_RCC_CR, HSERDY)))
        ;

    // (2) Configure PLL:
    // PREDIV output: 8/prediv MHz
    *REG_RCC_CFGR2 |= HSE_PREDIV(prediv);

    // (3) Select PREDIV output as PLL input (4 MHz):
    BIT_SET(*REG_RCC_CFGR, PLLXTPRE);

    // (4) Set PLLMUL to pllmul:
    // SYSCLK frequency = 8 / prediv * pllmul MHz
    FIELD_WRITE(*REG_RCC_CFGR, PLL_MULTIPLIER(pllmul), PLLMUL);

    // (5) Enable PLL:
    BIT_SET(*REG_RCC_CR, PLLON);
    
    while (!(BIT_READ(*REG_RCC_CR, PLLRDY)))
        ;

    // (6) Configure AHB frequency to pllmul / ah_div MHz:
    FIELD_WRITE(*REG_RCC_CFGR, ahb_div, FIELD_AHB_HPRE);

    // (7) Select PLL as SYSCLK source:
    FIELD_WRITE(*REG_RCC_CFGR, SYS_CLK_PLL, 0);

    while (FIELD_READ(*REG_RCC_CFGR, SWS_MASK) != 0x8U)
        ;

    // (8) Set APB frequency to pllmul / apb_div MHz
    FIELD_WRITE(*REG_RCC_CFGR, apb_div, 8U);
}

