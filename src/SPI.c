#include "SPI.h"
#include "general.h"
#include "RCC.h"

/* Expects:
 *      - PA5 as SPI1_SCK
 *      - PA7 as SPI1_MOSI
 */
void SPI_init(unsigned divisor) {
    BIT_SET(*REG_RCC_APB2ENR, SPI1EN);

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

    // SS output enable to forbid multimaster mode
    // BIT_SET(spi_cr2, SPI_SSOE);
    // 8 bit FIFO level RXNE
    // BIT_SET(spi_cr2, SPI_FRXTH);

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
