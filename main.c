#include "general.h"
#include "GPIO.h"
#include "RCC.h"
#include "tick.h"
#include "uart.h"
#include "SPI.h"
#include "screen.h"

#define LED_TICKS 50

// PA pins
#define SCK_PIN  5
#define MISO_PIN 6
#define MOSI_PIN 7

static int LedChange = 0;

void systick_handler(void) {
    static unsigned ticks = 0;
    ticks++;

    if (ticks >= LED_TICKS) {
        LedChange = 1;
        ticks = 0;
    }
}

/* Configures:
 *      - PA5 as SPI1_SCK
 *      - PA7 as SPI1_MOSI
 *      - PC8 as GPIO_OUT
 *      - PC9 as GPIO_OUT
 */
void board_gpio_init(void) {
    BIT_SET(*REG_RCC_AHBENR, IOPCEN);

    GPIO_SET_MODE(*GPIOC_MODER, RES_PIN, GPIO_MODER_OUT);
    BIT_CLR(*GPIOC_TYPER, RES_PIN);

    GPIO_SET_MODE(*GPIOC_MODER, LED_BLUE, GPIO_MODER_OUT);
    BIT_CLR(*GPIOC_TYPER, LED_BLUE);

    GPIO_SET_MODE(*GPIOC_MODER, 4, GPIO_MODER_OUT);
    BIT_CLR(*GPIOC_TYPER, 4);

    BIT_SET(*REG_RCC_AHBENR, IOPAEN);

    // Push-pull
    BIT_CLR(*GPIOA_TYPER, 5);
    BIT_CLR(*GPIOA_TYPER, 7);

    // Set alternate mode
    GPIO_SET_MODE(*GPIOA_MODER, 5, GPIO_MODER_ALT);
    GPIO_SET_MODE(*GPIOA_MODER, 7, GPIO_MODER_ALT);

    // Set AF0 for each pin
    GPIO_SET_AFRL(*GPIOA_AFRL, 5, PA5_SPI1_SCK);
    GPIO_SET_AFRL(*GPIOA_AFRL, 7, PA7_SPI1_MOSI);

    // Set high speed of operation
    GPIO_SET_OSPEEDR(*GPIOA_OSPEEDR, 5, GPIO_SPD_HIG);
    GPIO_SET_OSPEEDR(*GPIOA_OSPEEDR, 7, GPIO_SPD_HIG);
}

int main(void) {
    board_clocking_init(2, 12, AHB_NODIV, APB_DIV_NONE);
    board_gpio_init();
    systick_init(2000U);

    SPI_init(BAUD_DIV32);

    scrn_init();

    uint8_t last_val = 0xFF;

    while(1) {
        SPI_send_byte(last_val--);
        if (LedChange) {
            BIT_INV(*GPIOC_ODR, LED_BLUE);
            LedChange = 0;
        }
    }
}
