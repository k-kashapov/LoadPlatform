#ifndef GPIO_H
#define GPIO_H

//----------------
// GPIO Registers
//----------------

#define GPIOA_MODER   (volatile uint32_t*)(uintptr_t)0x48000000U // GPIO port mode register
#define GPIOA_TYPER   (volatile uint32_t*)(uintptr_t)0x48000004U // GPIO port output type register
#define GPIOA_PUPDR   (volatile uint32_t*)(uintptr_t)0x4800000CU // GPIO port pull-up/pull-down register
#define GPIOA_IDR     (volatile uint32_t*)(uintptr_t)0x48000010U // GPIO port input  data register
#define GPIOA_ODR     (volatile uint32_t*)(uintptr_t)0x48000014U // GPIO port output data register
#define GPIOA_BSRR    (volatile uint32_t*)(uintptr_t)0x48000018U // GPIO port bit set register
#define GPIOA_BRR     (volatile uint32_t*)(uintptr_t)0x48000028U // GPIO port bit reset register
#define GPIOA_OSPEEDR (volatile uint32_t*)(uintptr_t)0x48000008U // GPIO port output speed register
#define GPIOA_AFRH    (volatile uint32_t*)(uintptr_t)0x48000024U // GPIO alternate function high register

#define GPIOC_PUPDR (volatile uint32_t*)(uintptr_t)0x4800080CU // GPIO port pull-up/pull-down register
#define GPIOC_MODER (volatile uint32_t*)(uintptr_t)0x48000800U // GPIO port mode register
#define GPIOC_TYPER (volatile uint32_t*)(uintptr_t)0x48000804U // GPIO port output type register
#define GPIOC_IDR   (volatile uint32_t*)(uintptr_t)0x48000810U // GPIO port input  data register
#define GPIOC_ODR   (volatile uint32_t*)(uintptr_t)0x48000814U // GPIO port output data register
#define GPIOC_BSRR  (volatile uint32_t*)(uintptr_t)0x48000818U // GPIO port bit set register
#define GPIOC_BRR   (volatile uint32_t*)(uintptr_t)0x48000828U // GPIO port bit reset register

#define GPIO_ATOMIC_SET(port, bit) do *GPIO##port##_BSRR = 1U << (bit); while(0)
#define GPIO_ATOMIC_CLR(port, bit) do *GPIO##port##_BRR  = 1U << (bit); while(0)

#define LED_BLUE  8U
#define LED_GREEN 9U

#define GPIO_MODER_IN   0b00U
#define GPIO_MODER_OUT  0b01U
#define GPIO_MODER_ALT  0b10U
#define GPIO_MODER_ANLG 0b11U

#define GPIO_SET_MODE(REG, PIN, MODE) do (REG) |= (MODE) << (2U * (PIN)); while(0)

#define GPIO_MODER_ALL_OUT 0x15555555U // All 15 pins are GPIO output (0b01)

#define GPIO_TYPER_PUSHPULL 0b0U
#define GPIO_TYPER_OPNDRN   0b1U

#define GPIO_PUPD_NONE 0b00U
#define GPIO_PUPD_UP   0b01U
#define GPIO_PUPD_DOWN 0b10U

#define GPIO_SET_PUPDR(REG, PIN, MODE) do (REG) |= (MODE) << (2U * (PIN)); while(0)

#define GPIO_SET_AFRL(REG, PIN, FUN) do (REG) |= (FUN) << (4U * (PIN)); while(0)
#define GPIO_SET_AFRH(REG, PIN, FUN) do (REG) |= (FUN) << (4U * ((PIN) - 8U)); while(0)

#define PA9_USART_TX  1U
#define PA10_USART_RX 1U

#define GPIO_SET_OSPEEDR(REG, PIN, SPD) do (REG) |= (SPD) << (2U * (PIN)); while(0)

#define GPIO_SPD_LOW 0U
#define GPIO_SPD_MED 1U
#define GPIO_SPD_HIG 3U

void board_gpio_init(void);

#endif // GPIO_H
