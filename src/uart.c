#include "uart.h"
#include "RCC.h"

void uart_init(size_t baudrate, size_t frequency) {
    // (1) Configure USART1 clocking:
    BIT_SET(*REG_RCC_APB2ENR, USART1EN);
    FIELD_WRITE(*REG_RCC_CFGR3, USART_PCLK, USART1SW);

    // (2) Set USART1 parameters:
    uint32_t reg_usart_cr1 = 0U;
    uint32_t reg_usart_cr2 = 0U;

    // Data length: 8 bits
    USART_SET_WORD_LEN(reg_usart_cr1, USART_WORD_LEN_8BIT);
    
    // Use oversampling by 16
    BIT_CLR(reg_usart_cr1, USART_OVER8);
    
    // Parity control: disabled
    BIT_CLR(reg_usart_cr1, USART_PCE);
    
    // Transmitter: enabled
    BIT_SET(reg_usart_cr1, USART_TE);
    
    // Reciever: enabled
    BIT_SET(reg_usart_cr1, USART_RE);

    // Endianness: LSB first
    BIT_CLR(reg_usart_cr2, USART_MSBFIRST);
    
    // Number of stop bits: 2 stop bit
    USART_SET_STP_BITS(reg_usart_cr2, USART_2_STP_BITS);

    *USART1_CR1 = reg_usart_cr1;
    *USART1_CR2 = reg_usart_cr2;

    // (3) Configure USART baud rate:
    uint32_t usartdiv = (frequency + baudrate / 2) / baudrate;

    *USART1_BRR = usartdiv;

    // (4) Enable UART:
    BIT_SET(*USART1_CR1, USART_UE);

    // (5) Wait for TX to enable:
    while (BIT_READ(*USART1_ISR, USART_ISR_TEACK) == 0U)
        ;
}

void uart_send_byte(char sym) {
    // Wait for TXE:
    while (BIT_READ(*USART1_ISR, USART_ISR_TXE) == 0U)
        ;

    // Put data into DR:
    *USART1_TDR = sym;
}

void print_string(const char *buf) {
    for (size_t i = 0; buf[i] != '\0'; i++) {
        uart_send_byte(buf[i]);
    }
}

int uart_read_byte(void) {
    while (BIT_READ(*USART1_ISR, USART_ISR_RXNE) == 0)
        ;

    return *USART1_RDR;
}
