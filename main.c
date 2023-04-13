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

static volatile int LedChange = 0;

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
    board_clocking_init(2, 8, AHB_NODIV, APB_DIV_16);
    board_gpio_init();
    systick_init(8000U);

    SPI_init(BAUD_DIV8);

    scrn_init(1);

    scrn_clear(0x00);

    scrn_set_pxiel(0, 0);
    scrn_set_pxiel(1, 0);
    scrn_set_pxiel(1, 1);
    scrn_set_pxiel(1, 20);
    scrn_set_pxiel(127, 63);

    scrn_set_pxiel(10, 10);
    unsigned len = 64;
    unsigned x   = 10;

    while (len > 0) {
        scrn_yline(x++, 0, len--);
    }

    scrn_xline(  0,  0, 127);
    scrn_xline(  0, 63, 127);
    scrn_yline(  0,  0,  63);
    scrn_yline(127,  0,  63);

    scrn_box(1, 1, 125, 61);

    scrn_draw();

    uint8_t last_ch = 0;

    x = 0;

    while(1) {
        if (LedChange) {
            scrn_print(x, 30, last_ch++);
            x = ((x + 8) % 128);
            scrn_draw();
            BIT_INV(*GPIOC_ODR, LED_BLUE);
            LedChange = 0;
        }
    }
}
