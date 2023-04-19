#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include "inc/gpio.h"
#include "inc/rcc.h"
#include "inc/spi.h"
#include "screen.h"

/* Configures:
 *      - PA5 as SPI1_SCK
 *      - PA7 as SPI1_MOSI
 *      - PC7 as GPIO_OUT
 *      - PC6 as GPIO_OUT
 */
static void spi_gpio_init(void) {
    // Enable port A in AHB
    SET_BIT(REG_RCC_AHBENR, REG_RCC_AHBENR_IOPAEN);

    // Push-pull
    CLEAR_BIT(GPIO_OTYPER(GPIOA), SPI1_CLK_PIN);
    CLEAR_BIT(GPIO_OTYPER(GPIOA), SPI1_MOSI_PIN);

    // Set alternate mode
    SET_GPIO_IOMODE(GPIOA, SPI1_CLK_PIN, GPIO_IOMODE_ALT_FUNC);
    SET_GPIO_IOMODE(GPIOA, SPI1_MOSI_PIN, GPIO_IOMODE_ALT_FUNC);

    // Set AF0 for each pin
    SET_GPIO_AF(GPIOA, SPI1_CLK_PIN, 0);
    SET_GPIO_AF(GPIOA, SPI1_MOSI_PIN, 0);

    // Set high speed of operation
    SET_GPIO_OSPEED(GPIOA, SPI1_CLK_PIN, GPIO_OSPEED_HIGH);
    SET_GPIO_OSPEED(GPIOA, SPI1_MOSI_PIN, GPIO_OSPEED_HIGH);

    // Port C config
    SET_BIT(REG_RCC_AHBENR, REG_RCC_AHBENR_IOPCEN);

    SET_GPIO_IOMODE(GPIOC, RES_PIN, GPIO_IOMODE_GEN_PURPOSE_OUTPUT);
    SET_GPIO_IOMODE(GPIOC, DC_PIN,  GPIO_IOMODE_GEN_PURPOSE_OUTPUT);

    SET_GPIO_OTYPE(GPIOC, RES_PIN, GPIO_OTYPE_PUSH_PULL);
    SET_GPIO_OTYPE(GPIOC, DC_PIN,  GPIO_OTYPE_PUSH_PULL);
}

#define BIT_SET(REG, BIT)   do (REG) |=  (1U << (BIT)); while(0)
#define BIT_CLR(REG, BIT)   do (REG) &= ~(1U << (BIT)); while(0)
#define BIT_INV(REG, BIT)   do (REG) ^=  (1U << (BIT)); while(0)
#define BIT_READ(REG, BIT)  (REG & (1U << (BIT)))

#define MASK_LOWER(WIDTH) ((1U << (WIDTH)) - 1)

#define FIELD_WRITE(REG, VALUE, SHIFT) ((REG) |= ((VALUE) << (SHIFT)))
#define FIELD_READ(REG, MASK)          ((REG) & (MASK))

void SPI_init(unsigned divisor) {
    spi_gpio_init();

    SET_BIT(REG_RCC_APB2ENR, REG_RCC_APB2ENR_SPI1EN);

    uint16_t spi_cr1 = 0;
    uint16_t spi_cr2 = 0;

    // Frequency divisor
    FIELD_WRITE(spi_cr1, divisor & 7, SPI_BR);
    
    // Rising edge, no phase
    BIT_CLR(spi_cr1, SPI_CPHA);
    BIT_CLR(spi_cr1, SPI_CPOL);

    BIT_SET(spi_cr1, SPI_BIDIMODE);
    BIT_SET(spi_cr1, SPI_BIDIOE);
    
    BIT_SET(spi_cr1, SPI_SSM);
    BIT_SET(spi_cr1, SPI_SSI);

    // MSB first
    BIT_CLR(spi_cr1, SPI_LSBFIRST);
    // We are master
    BIT_SET(spi_cr1, SPI_MSTR);

    // 8 bit data size
    FIELD_WRITE(spi_cr2, DATA_SIZE_8, SPI_DS);

    *SPI1_CR1 = spi_cr1;
    *SPI1_CR2 = spi_cr2;

    BIT_SET(*SPI1_CR1, SPI_SPE);
}

int SPI_send_byte(uint8_t value) {
    volatile int a = *SPI1_DR;
    (void) a;

    while (BIT_READ(*SPI1_SR, SPI_TXE) == 0)
        ;

    *(uint8_t *)SPI1_DR = value;

    return 0;
}

uint16_t SPI_read(void) {
    while (BIT_READ(*SPI1_SR, SPI_RXNE) == 0)
        ;

    return *(uint8_t *)SPI1_DR;
}
