#include "general.h"
#include "GPIO.h"
#include "RCC.h"
#include "tick.h"
#include "uart.h"
#include "SPI.h"

#define LED_TICKS 100

static int LedChange = 0;

void systick_handler(void) {
    static unsigned ticks = 0;
    ticks++;

    if (ticks >= LED_TICKS) {
        LedChange = 1;
        ticks = 0;
    }
}

void board_gpio_init(void) {
    BIT_SET(*REG_RCC_AHBENR, IOPAEN);
    BIT_SET(*REG_RCC_AHBENR, IOPCEN);

    GPIO_SET_MODE(*GPIOC_MODER, LED_GREEN, GPIO_MODER_OUT);
    BIT_CLR(*GPIOC_TYPER, LED_GREEN);
}

int main(void) {
    board_clocking_init(2, 12, AHB_NODIV, APB_DIV_NONE);
    board_gpio_init();
    systick_init(1000U);

    SPI_init();
    // BIT_SET(*GPIOC_ODR, LED_GREEN);

    while(1) {
        if (LedChange) {
            BIT_INV(*GPIOC_ODR, LED_GREEN);
            LedChange = 0;
        }
        // __asm__ volatile ("wfi");
    }
}
