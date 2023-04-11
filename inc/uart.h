#ifndef UART_H
#define UART_H

#include <stddef.h>
#include "general.h"

//----------------
// UART Registers
//----------------

#define USART1_CR1 (volatile uint32_t*)(uintptr_t)0x40013800U // Control register 1
#define USART1_CR2 (volatile uint32_t*)(uintptr_t)0x40013804U // Control register 2
#define USART1_BRR (volatile uint32_t*)(uintptr_t)0x4001380CU // Baud rate register
#define USART1_ISR (volatile uint32_t*)(uintptr_t)0x4001381CU // Interrupt and status register
#define USART1_RDR (volatile uint32_t*)(uintptr_t)0x40013824U // Recieve data register
#define USART1_TDR (volatile uint32_t*)(uintptr_t)0x40013828U // Transmit data register

// USART_CR1 bitfields
#define USART_UE      0U
#define USART_UESM    1U
#define USART_RE      2U
#define USART_TE      3U
#define USART_IDLEIE  4U
#define USART_RXNEIE  5U
#define USART_TCIE    6U
#define USART_TXEIE   7U
#define USART_PEIE    8U
#define USART_PS      9U
#define USART_PCE    10U
#define USART_WAKE   11U
#define USART_M0     12U
#define USART_MME    13U
#define USART_CMIE   14U
#define USART_OVER8  15U
#define USART_DEDT   16U
#define USART_DEAT   17U
#define USART_RTOIE  18U
#define USART_EOBIE  19U
#define USART_M1     21U

#define USART_SET_WORD_LEN(REG, LEN) (REG) |= (( ((LEN) & 1U) << USART_M0 ) | ( ((LEN) & 2U) << USART_M1 ))

#define USART_WORD_LEN_8BIT 0U
#define USART_WORD_LEN_9BIT 1U
#define USART_WORD_LEN_7BIT 2U

// USART_CR2 bitfields
#define USART_ADDM7     4U
#define USART_LBDL      5U
#define USART_LBDIE     6U
#define USART_LBCL      8U
#define USART_CPHA      9U
#define USART_CPOL     10U
#define USART_CLKEN    11U
#define USART_STOP     12U
#define USART_LINEN    14U
#define USART_SWAP     15U
#define USART_RXINV    16U
#define USART_TXINV    17U
#define USART_DATAINV  18U
#define USART_MSBFIRST 19U
#define USART_ABREN    20U
#define USART_ABRMOD   21U
#define USART_RTOEN    23U
#define USART_ADDL     24U
#define USART_ADDH     28U

#define USART_SET_STP_BITS(REG, BITS) FIELD_WRITE(REG, BITS, USART_STOP);

#define USART_1_STP_BITS   0U
#define USART_0_5_STP_BITS 1U
#define USART_2_STP_BITS   2U
#define USART_1_5_STP_BITS 3U

// USART_ISR bitfields
#define USART_ISR_PE     0U
#define USART_ISR_FE     1U
#define USART_ISR_NF     2U
#define USART_ISR_ORE    3U
#define USART_ISR_IDLE   4U
#define USART_ISR_RXNE   5U
#define USART_ISR_TC     6U
#define USART_ISR_TXE    7U
#define USART_ISR_LBDF   8U
#define USART_ISR_CTSIF  9U
#define USART_ISR_CTS   10U
#define USART_ISR_RTOF  11U
#define USART_ISR_EOBF  12U
#define USART_ISR_ABRE  14U
#define USART_ISR_ABRF  15U
#define USART_ISR_BUSY  16U
#define USART_ISR_CMF   17U
#define USART_ISR_SBKF  18U
#define USART_ISR_RWU   19U
#define USART_ISR_WUF   20U
#define USART_ISR_TEACK 21U
#define USART_ISR_REACK 22U

void uart_init(size_t baudrate, size_t frequency);
void uart_send_byte(char sym);
void print_string(const char *buf);
int uart_read_byte(void);

#endif // UART_H
