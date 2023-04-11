#ifndef RCC_H
#define RCC_H

#include <stdint.h>

#define HSEON  16U // HSE ON      (RCC_CR)
#define HSERDY 17U // HSE ready   (RCC_CR)
#define HSEBYP 18U // HSE bypass  (RCC_CR)

#define HSE_PREDIV(DIV) ((DIV - 1) & 0xFU) // HSE clock freq divisor (RCC_CFGR2)

#define PLLON  24U // PLL ON    (RCC_CR)
#define PLLRDY 25U // PLL ready (RCC_CR)

#define PLL_MULTIPLIER(MUL) ((MUL - 2) & 0xFU) // HSE clock freq divisor (RCC_CFGR2)

#define SYS_CLK_HSI   0b00U // (RCC_CFGR)
#define SYS_CLK_HSE   0b01U // (RCC_CFGR)
#define SYS_CLK_PLL   0b10U // (RCC_CFGR)
#define SYS_CLK_HSI48 0b11U // (RCC_CFGR)

#define PLLXTPRE 17U  // HSE divider for PLL input clock (RCC_CFGR)
#define PLLMUL   18U  // PLL freq multplier              (RCC_CFGR)
#define SWS_MASK 0xCU // System clock switch status bits (RCC_CFGR)

#define FIELD_AHB_HPRE  4U      // Prescaler field of AHB clock (RCC_CFGR)
#define AHB_NODIV       0b0000U // (RCC_CFGR)

#define APB_DIV_NONE 0b000U // (RCC_CFGR)
#define APB_DIV_2    0b100U // (RCC_CFGR)
#define APB_DIV_4    0b101U // (RCC_CFGR)
#define APB_DIV_8    0b110U // (RCC_CFGR)
#define APB_DIV_16   0b111U // (RCC_CFGR)

#define IOPAEN 17U // IOPA enable (RCC_AHBENR)
#define IOPBEN 18U // IOPB enable (RCC_AHBENR)
#define IOPCEN 19U // IOPC enable (RCC_AHBENR)
#define IOPDEN 20U // IOPD enable (RCC_AHBENR)
#define IOPEEN 21U // IOPE enable (RCC_AHBENR)
#define IOPFEN 22U // IOPF enable (RCC_AHBENR)

// RCC_APB2ENR
#define SYSCFGCOMPEN  0U
#define USART6EN      5U
#define USART7EN      6U
#define USART8EN      7U
#define ADCEN         9U
#define TIM1EN       11U
#define SPI1EN       12U
#define USART1EN     14U
#define TIM15EN      16U
#define TIM16EN      17U
#define TIM17EN      18U
#define DBGMCUEN     22U

// RCC_CFGR3
#define USART1SW  0U
#define I2C1SW    4U
#define CECSW     6U
#define USBSW     7U
#define ADCSW     8U
#define USART2SW 16U
#define USART3SW 17U

#define USART_PCLK   0b00U
#define USART_SYSCLK 0b01U
#define USART_LSE    0b10U
#define USART_HSI    0b11U

//---------------
// RCC Registers
//---------------

#define REG_RCC_CR      (volatile uint32_t*)(uintptr_t)0x40021000U // Clock Control Register
#define REG_RCC_CFGR    (volatile uint32_t*)(uintptr_t)0x40021004U // PLL Configuration Register
#define REG_RCC_AHBENR  (volatile uint32_t*)(uintptr_t)0x40021014U // AHB1 Peripheral Clock Enable Register
#define REG_RCC_APB2ENR (volatile uint32_t*)(uintptr_t)0x40021018U // APB1 Peripheral Clock Enable Register
#define REG_RCC_CFGR2   (volatile uint32_t*)(uintptr_t)0x4002102CU // Clock configuration register 2
#define REG_RCC_CFGR3   (volatile uint32_t*)(uintptr_t)0x40021030U // Clock configuration register 3

//-------------------
// RCC configuration
//-------------------

#define CPU_FREQENCY    48000000U
#define ONE_MILLISECOND CPU_FREQENCY / 1000U
void board_clocking_init(uint16_t prediv, uint16_t pllmul, uint16_t ahb_div, uint16_t apb_div);

#endif // RCC_H
