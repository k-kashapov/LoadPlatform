#pragma once 

//---------------------------------------------------------

#include "modregs.h"

//=========================================================

// RESET AND CLOCK CONTROL
#define REG_RCC 0x40021000U

#define REG_RCC_CR       (volatile uint32_t*)(uintptr_t)(REG_RCC + 0x00) // Clock Control Register
#define REG_RCC_CFGR     (volatile uint32_t*)(uintptr_t)(REG_RCC + 0x04) // Clock configuration register
#define REG_RCC_CIR      (volatile uint32_t*)(uintptr_t)(REG_RCC + 0x08) // Clock interrupt register
#define REG_RCC_APB2RSTR (volatile uint32_t*)(uintptr_t)(REG_RCC + 0x0C) // APB peripheral reset register 2
#define REG_RCC_APB1RSTR (volatile uint32_t*)(uintptr_t)(REG_RCC + 0x10) // APB peripheral reset register 1
#define REG_RCC_AHBENR   (volatile uint32_t*)(uintptr_t)(REG_RCC + 0x14) // AHB1 Peripheral Clock Enable Register
#define REG_RCC_APB2ENR  (volatile uint32_t*)(uintptr_t)(REG_RCC + 0x18) // APB peripheral clock enable register 2
#define REG_RCC_APB1ENR  (volatile uint32_t*)(uintptr_t)(REG_RCC + 0x1C) // APB peripheral clock enable register 1
#define REG_RCC_BDCR     (volatile uint32_t*)(uintptr_t)(REG_RCC + 0x20) // RTC domain control register
#define REG_RCC_CSR      (volatile uint32_t*)(uintptr_t)(REG_RCC + 0x24) // Control/status register
#define REG_RCC_AHBRSTR  (volatile uint32_t*)(uintptr_t)(REG_RCC + 0x28) // AHB peripheral reset register
#define REG_RCC_CFGR2    (volatile uint32_t*)(uintptr_t)(REG_RCC + 0x2C) // Clock configuration register 2
#define REG_RCC_CFGR3    (volatile uint32_t*)(uintptr_t)(REG_RCC + 0x30) // Clock configuration register 3
#define REG_RCC_CR2      (volatile uint32_t*)(uintptr_t)(REG_RCC + 0x34) // Clock Control Register 2

//---------------------------------------------------------

// CR

#define REG_RCC_CR_HSION  0  // HSI clock enable
#define REG_RCC_CR_HSIRDY 1  // HSI clock ready flag
// Bit 2 reserved
#define REG_RCC_CR_HSEON  16 // HSE clock enable
#define REG_RCC_CR_HSERDY 17 // HSE clock ready flag
#define REG_RCC_CR_HSEBYP 18 // HSE crystal oscillator bypass
#define REG_RCC_CR_CSSON  19 // Clock security system enable
// Bits 23:20 reserved
#define REG_RCC_CR_PLLON  24 // PLL enable
#define REG_RCC_CR_PLLRDY 25 // PLL clock ready flag

#define REG_RCC_CR_HSICAL 8  // HSI clock calibration
#define GET_REG_RCC_CR_HSICAL() SUPER_CHECK_REG(REG_RCC_CR, 0xFF, REG_RCC_CR_HSICAL)

#define REG_RCC_CR_HSITRIM 3 // HSI clock trimming
#define GET_REG_RCC_CR_HSITRIM() SUPER_CHECK_REG(REG_RCC_CR, 0b11111, REG_RCC_CR_HSITRIM)
#define SET_REG_RCC_CR_HSITRIM(value) SUPER_MODIFY_REG(REG_RCC_CR, 0b11111, value, REG_RCC_CR_HSITRIM)

//---------------------------------------------------------

// AHBENR

#define REG_RCC_AHBENR_TSCEN   24 // Touch sensing controller clock enable
// Bit 23 reserved
#define REG_RCC_AHBENR_IOPFEN  22 // I/O port F clock enable
#define REG_RCC_AHBENR_IOPEEN  21 // I/O port E clock enable
#define REG_RCC_AHBENR_IOPDEN  20 // I/O port D clock enable
#define REG_RCC_AHBENR_IOPCEN  19 // I/O port C clock enable
#define REG_RCC_AHBENR_IOPBEN  18 // I/O port B clock enable
#define REG_RCC_AHBENR_IOPAEN  17 // I/O port A clock enable
// Bits 16:7 reserved
#define REG_RCC_AHBENR_CRCEN   6  // CRC clock enable
#define REG_RCC_AHBENR_FLITFEN 4  // FLITF clock enable
#define REG_RCC_AHBENR_SRAMEN  2  // SRAM interface clock enable
// Bit 3 reserved
#define REG_RCC_AHBENR_DMA2EN  1  // DMA2 clock enable
#define REG_RCC_AHBENR_DMAEN   0  // DMA clock enable

//---------------------------------------------------------

// CFGR2

// Bits 31:4 reserved
#define REG_RCC_CFGR2_PREDIV 0 // PREDIV division factor     

// Available values: 0b0000 - 0b1111
#define SET_REG_RCC_CFGR2_PREDIV(value) SUPER_MODIFY_REG(REG_RCC_CFGR2, 0b1111, (value) - 1, 0)

//---------------------------------------------------------

// RCC_APB1ENR

#define REG_RCC_APB1ENR_TIM2EN   0
#define REG_RCC_APB1ENR_TIM3EN   1
#define REG_RCC_APB1ENR_TIM6EN   4
#define REG_RCC_APB1ENR_TIM7EN   5
#define REG_RCC_APB1ENR_TIM14EN  8
#define REG_RCC_APB1ENR_WWDGEN   11
#define REG_RCC_APB1ENR_SPI2EN   14
#define REG_RCC_APB1ENR_USART2EN 17
#define REG_RCC_APB1ENR_USART3EN 18
#define REG_RCC_APB1ENR_USART4EN 19
#define REG_RCC_APB1ENR_USART5EN 20
#define REG_RCC_APB1ENR_I2C1EN   21
#define REG_RCC_APB1ENR_I2C2EN   22
#define REG_RCC_APB1ENR_USBEN    23
#define REG_RCC_APB1ENR_CANEN    25
#define REG_RCC_APB1ENR_CRSEN    27
#define REG_RCC_APB1ENR_PWREN    28
#define REG_RCC_APB1ENR_DACEN    29
#define REG_RCC_APB1ENR_CECEN    30

//---------------------------------------------------------

// RCC_APB2ENR

#define REG_RCC_APB2ENR_SYSCFGCOMPEN 0
#define REG_RCC_APB2ENR_USART6EN     5
#define REG_RCC_APB2ENR_USART7EN     6
#define REG_RCC_APB2ENR_USART8EN     7
#define REG_RCC_APB2ENR_ADCEN        9
#define REG_RCC_APB2ENR_TIM1EN       11
#define REG_RCC_APB2ENR_SPI1EN       12
#define REG_RCC_APB2ENR_USART1EN     14
#define REG_RCC_APB2ENR_TIM15EN      16
#define REG_RCC_APB2ENR_TIM16EN      17
#define REG_RCC_APB2ENR_TIM17EN      18
#define REG_RCC_APB2ENR_DBGMCUEN     22

//---------------------------------------------------------

// Clock configuration register 3

#define REG_RCC_CFGR3_USARTSW_PCLK   0b00
#define REG_RCC_CFGR3_USARTSW_SYSCLK 0b01
#define REG_RCC_CFGR3_USARTSW_LSE    0b10
#define REG_RCC_CFGR3_USARTSW_HSI    0b11

#define REG_RCC_CFGR3_USART1SW 0

#define SET_REG_RCC_CFGR3_USART1SW(value) SUPER_MODIFY_REG(REG_RCC_CFGR3, 0b11, value, REG_RCC_CFGR3_USART1SW)
#define GET_REG_RCC_CFGR3_USART1SW() SUPER_CHECK_REG(REG_RCC_CFGR3, 0b11, REG_RCC_CFGR3_USART1SW)

#define REG_RCC_CFGR3_I2C1SW 4
#define REG_RCC_CFGR3_CECSW  6
#define REG_RCC_CFGR3_USBSW  7
#define REG_RCC_CFGR3_ADCSW  8

#define REG_RCC_CFGR3_USART2SW 16

#define SET_REG_RCC_CFGR3_USART2SW(value) SUPER_MODIFY_REG(REG_RCC_CFGR3, 0b11, value, REG_RCC_CFGR3_USART2SW)
#define GET_REG_RCC_CFGR3_USART2SW() SUPER_CHECK_REG(REG_RCC_CFGR3, 0b11, REG_RCC_CFGR3_USART2SW)

#define REG_RCC_CFGR3_USART3SW 18

#define SET_REG_RCC_CFGR3_USART3SW(value) SUPER_MODIFY_REG(REG_RCC_CFGR3, 0b11, value, REG_RCC_CFGR3_USART3SW)
#define GET_REG_RCC_CFGR3_USART3SW() SUPER_CHECK_REG(REG_RCC_CFGR3, 0b11, REG_RCC_CFGR3_USART3SW)

//---------------------------------------------------------


// CFGR

// PLL input clock source
#define REG_RCC_CFGR_PLLSRC 15               
#define SET_REG_RCC_CFGR_PLLSRC(value) SUPER_MODIFY_REG(REG_RCC_CFGR, 0b11, value, REG_RCC_CFGR_PLLSRC)
#define GET_REG_RCC_CFGR_PLLSRC() SUPER_CHECK_REG(REG_RCC_CFGR, 0b11, REG_RCC_CFGR_PLLSRC)

#define REG_RCC_CFGR_PLLSRC_HSI_DIV_2    0b00 
#define REG_RCC_CFGR_PLLSRC_HSI_PREDIV   0b01 
#define REG_RCC_CFGR_PLLSRC_HSE_PREDIV   0b10 
#define REG_RCC_CFGR_PLLSRC_HSI48_PREDIV 0b10 

// PLL multiplication factor
#define REG_RCC_CFGR_PLLMUL 18 
// Values from 16 to 2
#define SET_REG_RCC_CFGR_PLLMUL(value) SUPER_MODIFY_REG(REG_RCC_CFGR, 0b1111, (value) - 2, REG_RCC_CFGR_PLLMUL) 
#define GET_REG_RCC_CFGR_PLLMUL() ((SUPER_CHECK_REG(REG_RCC_CFGR, 0b1111), REG_RCC_CFGR_PLLMUL) + 2)

// HCLK prescaler
#define REG_RCC_CFGR_HPRE 4      
#define GET_REG_RCC_CFGR_HPRE() SUPER_CHECK_REG(REG_RCC_CFGR, 0b1111, REG_RCC_CFGR_HPRE) 

#define SET_REG_RCC_CFGR_HPRE_NOT_DIV() SUPER_MODIFY_REG(REG_RCC_CFGR, 0b1111, 0b0000, REG_RCC_CFGR_HPRE)
#define SET_REG_RCC_CFGR_HPRE_2()       SUPER_MODIFY_REG(REG_RCC_CFGR, 0b1111, 0b1000, REG_RCC_CFGR_HPRE)
#define SET_REG_RCC_CFGR_HPRE_4()       SUPER_MODIFY_REG(REG_RCC_CFGR, 0b1111, 0b1001, REG_RCC_CFGR_HPRE)
#define SET_REG_RCC_CFGR_HPRE_8()       SUPER_MODIFY_REG(REG_RCC_CFGR, 0b1111, 0b1010, REG_RCC_CFGR_HPRE)
#define SET_REG_RCC_CFGR_HPRE_16()      SUPER_MODIFY_REG(REG_RCC_CFGR, 0b1111, 0b1011, REG_RCC_CFGR_HPRE) 
#define SET_REG_RCC_CFGR_HPRE_64()      SUPER_MODIFY_REG(REG_RCC_CFGR, 0b1111, 0b1100, REG_RCC_CFGR_HPRE) 
#define SET_REG_RCC_CFGR_HPRE_128()     SUPER_MODIFY_REG(REG_RCC_CFGR, 0b1111, 0b1101, REG_RCC_CFGR_HPRE)
#define SET_REG_RCC_CFGR_HPRE_256()     SUPER_MODIFY_REG(REG_RCC_CFGR, 0b1111, 0b1110, REG_RCC_CFGR_HPRE)
#define SET_REG_RCC_CFGR_HPRE_512()     SUPER_MODIFY_REG(REG_RCC_CFGR, 0b1111, 0b1111, REG_RCC_CFGR_HPRE)

// System clock switch
#define REG_RCC_CFGR_SW 0       
#define SET_REG_RCC_CFGR_SW(value) SUPER_MODIFY_REG(REG_RCC_CFGR, 0b11, value, REG_RCC_CFGR_SW)
#define GET_REG_RCC_CFGR_SW() SUPER_CHECK_REG(REG_RCC_CFGR, 0b11, REG_RCC_CFGR_SW)

#define REG_RCC_CFGR_SW_HSI   0b00 
#define REG_RCC_CFGR_SW_HSE   0b01 
#define REG_RCC_CFGR_SW_PLL   0b10 
#define REG_RCC_CFGR_SW_HSI48 0b11 

// System clock switch status
#define REG_RCC_CFGR_SWS 2       
#define SET_REG_RCC_CFGR_SWS(value) SUPER_MODIFY_REG(REG_RCC_CFGR, 0b11, value, REG_RCC_CFGR_SWS)
#define GET_REG_RCC_CFGR_SWS() SUPER_CHECK_REG(REG_RCC_CFGR, 0b11, REG_RCC_CFGR_SWS)

#define REG_RCC_CFGR_SWS_HSI   0b00 
#define REG_RCC_CFGR_SWS_HSE   0b01 
#define REG_RCC_CFGR_SWS_PLL   0b10 
#define REG_RCC_CFGR_SWS_HSI48 0b11  

// PCLK prescaler
#define REG_RCC_CFGR_PPRE 8          
#define SET_REG_RCC_CFGR_PPRE(value) SUPER_MODIFY_REG(REG_RCC_CFGR, 0b111, value, REG_RCC_CFGR_PPRE)
#define GET_REG_RCC_CFGR_PPRE() SUPER_CHECK_REG(REG_RCC_CFGR, 0b111, REG_RCC_CFGR_PPRE)

#define REG_RCC_CFGR_PPRE_NOT_DIV 0b000 
#define REG_RCC_CFGR_PPRE_DIV_2   0b100 
#define REG_RCC_CFGR_PPRE_DIV_4   0b101
#define REG_RCC_CFGR_PPRE_DIV_8   0b110
#define REG_RCC_CFGR_PPRE_DIV_16  0b111