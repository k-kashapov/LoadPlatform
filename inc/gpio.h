#pragma once 

//---------------------------------------------------------

#include "modregs.h"

//=========================================================

// GPIO ports
#define GPIOA 0x48000000U
#define GPIOB 0x48000400U
#define GPIOC 0x48000800U
#define GPIOD 0x48000C00U
#define GPIOE 0x48001000U
#define GPIOF 0x48001400U

#define GPIO_offs 0x400

//---------------------------------------------------------

#define GPIO_MODER(GPIOx)   (volatile uint32_t*)(uintptr_t)(GPIOx + 0x00) 
#define GPIO_OTYPER(GPIOx)  (volatile uint32_t*)(uintptr_t)(GPIOx + 0x04) 
#define GPIO_OSPEEDR(GPIOx) (volatile uint32_t*)(uintptr_t)(GPIOx + 0x08) 
#define GPIO_PUPDR(GPIOx)   (volatile uint32_t*)(uintptr_t)(GPIOx + 0x0C) 
#define GPIO_IDR(GPIOx)     (volatile uint32_t*)(uintptr_t)(GPIOx + 0x10) 
#define GPIO_ODR(GPIOx)     (volatile uint32_t*)(uintptr_t)(GPIOx + 0x14) 
#define GPIO_BSRR(GPIOx)    (volatile uint32_t*)(uintptr_t)(GPIOx + 0x18) 
#define GPIO_LCKR(GPIOx)    (volatile uint32_t*)(uintptr_t)(GPIOx + 0x1C) 
#define GPIO_AFRL(GPIOx)    (volatile uint32_t*)(uintptr_t)(GPIOx + 0x20) 
#define GPIO_AFRH(GPIOx)    (volatile uint32_t*)(uintptr_t)(GPIOx + 0x24) 
#define GPIO_BRR(GPIOx)     (volatile uint32_t*)(uintptr_t)(GPIOx + 0x28) 

//---------------------------------------------------------

// Modes

#define GPIO_IOMODE_INPUT              0b00
#define GPIO_IOMODE_GEN_PURPOSE_OUTPUT 0b01
#define GPIO_IOMODE_ALT_FUNC           0b10
#define GPIO_IOMODE_ANALOG_MODE        0b11

#define SET_GPIO_IOMODE(GPIOx, PIN, MODE) SUPER_MODIFY_REG(GPIO_MODER(GPIOx), 0b11, MODE, 2 * (PIN))
#define GET_GPIO_IOMODE(GPIOx, PIN) SUPER_CHECK_REG(GPIO_MODER(GPIOx), 0b11, 2 * (PIN))

//---------------------------------------------------------

// Types

#define GPIO_OTYPE_PUSH_PULL  0b0
#define GPIO_OTYPE_OPEN_DRAIN 0b1

#define SET_GPIO_OTYPE(GPIOx, PIN, TYPE) SUPER_MODIFY_REG(GPIO_OTYPER(GPIOx), 0b1, TYPE, PIN)
#define GET_GPIO_OTYPE(GPIOx, PIN) SUPER_CHECK_REG(GPIO_OTYPER(GPIOx), 0b1, PIN)

//---------------------------------------------------------

// ODR

#define GPIO_ODR_WRITE(GPIOx, VALUE) (*(GPIO_ODR(GPIOx)) = VALUE)
#define GPIO_ODR_READ(GPIOx) (*(GPIO_ODR(GPIOx)))

#define GPIO_ODR_SET_PIN(GPIOx, PIN) SET_BIT(GPIO_ODR(GPIOx), PIN)
#define GPIO_ODR_RESET_PIN(GPIOx, PIN) CLEAR_BIT(GPIO_ODR(GPIOx), PIN)
#define GPIO_ODR_GET_PIN(GPIOx, PIN) CHECK_BIT(GPIO_ODR(GPIOx), PIN)

//---------------------------------------------------------

// BSRR/BRR

// #define GPIO_BSRR_SET_PIN(GPIOx, PIN) SET_BIT(GPIO_BSRR(GPIOx), PIN)
// #define GPIO_BRR_RESET_PIN(GPIOx, PIN) SET_BIT(GPIO_BRR(GPIOx), PIN)

#define GPIO_BSRR_SET_PIN(GPIOx, PIN) (*GPIO_BSRR(GPIOx) = 1 << PIN)
#define GPIO_BRR_RESET_PIN(GPIOx, PIN) (*GPIO_BRR(GPIOx) = 1 << PIN)

//---------------------------------------------------------

// OSPEEDR

#define GPIO_OSPEED_LOW    0b00
#define GPIO_OSPEED_MEDIUM 0b01
#define GPIO_OSPEED_HIGH   0b11

#define SET_GPIO_OSPEED(GPIOx, PIN, OSPEED) SUPER_MODIFY_REG(GPIO_OSPEEDR(GPIOx), 0b11, OSPEED, 2 * (PIN))
#define GET_GPIO_OSPEED(GPIOx, PIN) SUPER_CHECK_REG(GPIO_OSPEEDR(GPIOx), 0b11, 2 * (PIN))

//---------------------------------------------------------

// PUPDR

#define GPIO_PUPD_NONE 0b00
#define GPIO_PUPD_PU   0b01
#define GPIO_PUPD_PD   0b10

#define SET_GPIO_PUPD(GPIOx, PIN, PUPD) SUPER_MODIFY_REG(GPIO_PUPDR(GPIOx), 0b11, PUPD, 2 * (PIN))
#define GET_GPIO_PUPD(GPIOx, PIN) SUPER_CHECK_REG(GPIO_PUPDR(GPIOx), 0b11, 2 * (PIN))

//---------------------------------------------------------

// IDR

#define GPIO_IDR_READ(GPIOx) (*(GPIO_IDR(GPIOx)))
#define GPIO_IDR_GET_PIN(GPIOx, PIN) (CHECK_BIT(GPIO_IDR(GPIOx), PIN))

//---------------------------------------------------------

// Alternate function low & high registers

#define GPIO_AF0 0b000
#define GPIO_AF1 0b001
#define GPIO_AF2 0b010
#define GPIO_AF3 0b011
#define GPIO_AF4 0b100
#define GPIO_AF5 0b101
#define GPIO_AF6 0b110
#define GPIO_AF7 0b111

#define SET_GPIO_AF_LOW(GPIOx, PIN, AFSEL) SUPER_MODIFY_REG(GPIO_AFRL(GPIOx), 0b1111, AFSEL, 4 * (PIN))
#define SET_GPIO_AF_HIGH(GPIOx, PIN, AFSEL) SUPER_MODIFY_REG(GPIO_AFRH(GPIOx), 0b1111, AFSEL, 4 * (PIN))

#define GET_GPIO_AF_LOW(GPIOx, PIN) SUPER_CHECK_REG(GPIO_AFRL(GPIOx), 0b1111, 4 * (PIN))
#define GET_GPIO_AF_HIGH(GPIOx, PIN) SUPER_CHECK_REG(GPIO_AFRH(GPIOx), 0b1111, 4 * (PIN))

#define SET_GPIO_AF(GPIOx, PIN, AFSEL)                  \
    do                                                  \
    {                                                   \
        if ((PIN) >= 8)                                 \
        {                                               \
            SET_GPIO_AF_HIGH(GPIOx, (PIN) - 8, AFSEL);  \
        }                                               \
        else                                            \
        {                                               \
            SET_GPIO_AF_LOW(GPIOx, PIN, AFSEL);         \
        }                                               \
                                                        \
    } while(0);

#define GET_GPIO_AF(GPIOx, PIN)                         \
    do                                                  \
    {                                                   \
        if ((PIN) >= 8)                                 \
        {                                               \
            GET_GPIO_AF_HIGH(GPIOx, (PIN) - 8);         \
        }                                               \
        else                                            \
        {                                               \
            GET_GPIO_AF_LOW(GPIOx, PIN);                \
        }                                               \
                                                        \
    } while(0);


