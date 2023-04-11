#include "general.h"
#include "GPIO.h"
#include "RCC.h"
#include "tick.h"
#include "uart.h"
#include "SPI.h"

#define LED_TICKS 500

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
    BIT_SET(*REG_RCC_AHBENR, IOPCEN);

    GPIO_SET_MODE(*GPIOC_MODER, LED_BLUE, GPIO_MODER_OUT);
    BIT_SET(*GPIOC_TYPER, LED_BLUE);
    GPIO_SET_PUPDR(*GPIOC_PUPDR, LED_BLUE, GPIO_PUPD_NONE);
}

int main(void) {
    board_clocking_init(2, 12, AHB_NODIV, APB_DIV_NONE);
    systick_init(1000);

    SPI_init();

    while(1) {
        if (LedChange) {
            BIT_INV(*GPIOC_ODR, LED_BLUE);
            LedChange = 0;
        }
        // __asm__ volatile ("wfi");
    }
}
