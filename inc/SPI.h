#ifndef SPI_H
#define SPI_H

#include <stddef.h>

#define SPI1_CR_BASE ((uint16_t*)0x40013000) // SPI 1 Control    registers base
#define SPI1_CR1     ((uint16_t*)0x40013000) // SPI 1 Control    register 1
#define SPI1_CR2     ((uint16_t*)0x40013004) // SPI 1 Control    register 2
#define SPI1_SR      ((uint16_t*)0x40013008) // SPI 1 Status     register
#define SPI1_DR      ((uint16_t*)0x4001300C) // SPI 1 Data       register
#define SPI1_CRCPR   ((uint16_t*)0x40013010) // SPI 1 Polynomial register
#define SPI1_RXCRCR  ((uint16_t*)0x40013014) // SPI 1 Rx CRC     register
#define SPI1_TXCRCR  ((uint16_t*)0x40013018) // SPI 1 Tx CRC     register

// SPIx_CR1 bitfields
#define SPI_BIDIMODE 15U // Bidirectional data mode enable
#define SPI_BIDIOE   14U // Output enabled in BIDI mode
#define SPI_CRCEN    13U // Hardware CRC calculation enable
#define SPI_CRCNEXT  12U // Next transmit value is from [0:Tx buffer | 1:Tx CRC register]
#define SPI_CRCL     11U // CRCL
#define SPI_RXONLY   10U // Recieve only mode
#define SPI_SSM       9U // Software slave management
#define SPI_SSI       8U // Internal slave select
#define SPI_LSBFIRST  7U // MSB/LSB frame format
#define SPI_SPE       6U // SPI enable
#define SPI_BR        3U // Baud rate control: Rate = f_PCLK / (2^(BR + 1))
#define SPI_MSTR      2U // Master config
#define SPI_CPOL      1U // Clock polarity
#define SPI_CPHA      0U // Clock phase

// SPIx_CR2 bitfields
// Bit 15 reserved
#define SPI_LDMA_TX 14U // Last DMA transfer for transmission
#define SPI_LDMA_RX 13U // Last DMA transfer for reception
#define SPI_FRXTH   12U // FIFO reception threshold. Generate RXNE event on [0: 1/2 of FIFO | 1: 1/4 of FIFO]
#define SPI_DS       8U // Data size: Size = DS + 1. Cannot be lower than 0b0011 = 4 bit
#define SPI_TXEIE    7U // Tx buffer empty interrupt enable
#define SPI_RXNEIE   6U // RX buffer not empty interrupt enable
#define SPI_ERRIE    5U // Error interrupt enable
#define SPI_FRF      4U // Frame format [0: Motorola | 1: TI] mode
#define SPI_NSSP     3U // NSS pulse manager. Master mode only.
#define SPI_SSOE     2U // SS output enable
#define SPI_TXDMAEN  1U // Tx buffer DMA enable
#define SPI_RXDMAEN  0U // Rx buffer DMA enable

// SPIx_SR bitfields
// Bits [15; 13] are reserved
#define SPI_FTLVL  11U // FIFO Transmission Level. These bits are set and cleared by hardware.
#define SPI_FRLVL   9U // FIFO reception level. These bits are set and cleared by hardware.
#define SPI_FRE     8U // Frame format error
#define SPI_BSY     7U // Busy flag
#define SPI_OVR     6U // Overrun flag
#define SPI_MODF    5U // Mode fault
#define SPI_CRCERR  4U // CRC error flag
#define SPI_UDR     3U // Underrun flag
#define SPI_CHSIDE  2U // Channel side. Not used in SPI mode
#define SPI_TXE     1U // Transmit buffer empty
#define SPI_RXNE    0U // Receive buffer not empty



#endif // SPI_H
