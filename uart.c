#include <stdlib.h>
#include <stdbool.h>

//---------------------------------------------------------

#include "inc/uart.h"
#include "inc/gpio.h"
#include "inc/rcc.h"
#include "uart.h"

//=========================================================

static const uint32_t UARTx_addr[8] = { USART1, USART2, USART3, USART4,
                                        USART5, USART6, USART7, USART8 };

//---------------------------------------------------------

static void uart_gpio_setup(struct Uart* uart, uint8_t af_tx, uint8_t af_rx);
static void uart_usart_setup(struct Uart* uart, size_t baudrate, size_t frequency);

//=========================================================

int uart_setup(struct Uart* uart, uint16_t uartno, const struct Port_n_pin* tx, uint8_t af_tx,
                                                   const struct Port_n_pin* rx, uint8_t af_rx,
                                                   size_t baudrate, size_t frequency)
{
    if (uart == NULL)
        return UART_INV_PTR;

    if (tx == NULL || rx == NULL)
        return UART_INV_ARG;

    uart->uartno = uartno;
    uart->UARTx = UARTx_addr[uartno - 1];
    uart->tx = *tx;
    uart->rx = *rx;

    uart_gpio_setup(uart, af_tx, af_rx);
    uart_usart_setup(uart, baudrate, frequency);

    return 0;
}

//---------------------------------------------------------

static void uart_gpio_setup(struct Uart* uart, uint8_t af_tx, uint8_t af_rx)
{
    uint8_t bit_tx = REG_RCC_AHBENR_IOPAEN + (uart->tx.port - GPIOA) / GPIO_offs;
    uint8_t bit_rx = REG_RCC_AHBENR_IOPAEN + (uart->rx.port - GPIOA) / GPIO_offs;

    SET_BIT(REG_RCC_AHBENR, bit_tx);
    SET_BIT(REG_RCC_AHBENR, bit_rx);

    SET_GPIO_AF(uart->tx.port, uart->tx.pin, af_tx);
    SET_GPIO_AF(uart->rx.port, uart->rx.pin, af_rx);

    SET_GPIO_OSPEED(uart->tx.port, uart->tx.pin, GPIO_OSPEED_HIGH);
    SET_GPIO_OSPEED(uart->rx.port, uart->rx.pin, GPIO_OSPEED_HIGH);

    SET_GPIO_IOMODE(uart->tx.port, uart->tx.pin, GPIO_IOMODE_ALT_FUNC);
    SET_GPIO_IOMODE(uart->rx.port, uart->rx.pin, GPIO_IOMODE_ALT_FUNC);

    return;
}

//---------------------------------------------------------

static void uart_usart_setup(struct Uart* uart, size_t baudrate, size_t frequency)
{

    switch (uart->uartno)
    {
        case 1:
        {
            SET_BIT(REG_RCC_APB2ENR, REG_RCC_APB2ENR_USART1EN);
            SET_REG_RCC_CFGR3_USART1SW(REG_RCC_CFGR3_USARTSW_PCLK); 
            break;
        }

        case 2:
        {
            SET_BIT(REG_RCC_APB1ENR, REG_RCC_APB1ENR_USART2EN);
            SET_REG_RCC_CFGR3_USART2SW(REG_RCC_CFGR3_USARTSW_PCLK); 
            break;
        }

        default: break;
    }

    CLEAR_BIT(USART_CR1(uart->UARTx), USART_CR1_M0);    // 1 Start bit, 8 data bits
    CLEAR_BIT(USART_CR1(uart->UARTx), USART_CR1_M1);    
    CLEAR_BIT(USART_CR1(uart->UARTx), USART_CR1_OVER8); // Oversampling by 16
    CLEAR_BIT(USART_CR1(uart->UARTx), USART_CR1_PCE);   // Parity control disabled
    // SET_BIT(USART_CR1(uart->UARTx), USART_CR1_TE);      // Transmitter: enabled

    CLEAR_BIT(USART_CR2(uart->UARTx), USART_CR2_MSBFIRST); // Endianness: LSB first
    SET_USART_CR2_STOP(uart->UARTx, USART_CR2_STOP_2);     // Number of stop bits: 2 stop bit

    SET_USART_BRR(uart->UARTx, (frequency) / (baudrate));

    SET_BIT(USART_CR1(uart->UARTx), USART_CR1_UE);

    // while (CHECK_BIT(USART_ISR(uart->UARTx), USART_ISR_TEACK) == 0U)
    //     continue;
}

//---------------------------------------------------------

int uart_transmit_enable(struct Uart* uart)
{
    if (uart == NULL)
        return UART_INV_PTR;

    SET_BIT(USART_CR1(uart->UARTx), USART_CR1_TE);

    while (CHECK_BIT(USART_ISR(uart->UARTx), USART_ISR_TEACK) == 0U)
        continue;

    return 0;
}

//---------------------------------------------------------

int uart_receive_enable(struct Uart* uart)
{
    if (uart == NULL)
        return UART_INV_PTR;

    SET_BIT(USART_CR1(uart->UARTx), USART_CR1_RE);

    while (CHECK_BIT(USART_ISR(uart->UARTx), USART_ISR_REACK) == 0U)
        continue;

    return 0;
}

//---------------------------------------------------------

int uart_send_byte(struct Uart* uart, uint8_t data, bool wait_tc)
{
    if (uart == NULL)
        return UART_INV_PTR;

    while (CHECK_BIT(USART_ISR(uart->UARTx), USART_ISR_TXE) == 0U)
        continue;

    *USART_TDR(uart->UARTx) = data;

    if (wait_tc)
    {
        while (CHECK_BIT(USART_ISR(uart->UARTx), USART_ISR_TC) == 0U)
           continue;
    }

    return 0;
}

//---------------------------------------------------------

int uart_recv_byte(struct Uart* uart, uint8_t* data, bool wait_rxne)
{
    if (uart == NULL)
        return UART_INV_PTR;

    if (data == NULL)   
        return UART_INV_ARG;

    bool rxne = false;

    if (wait_rxne)
    {
        while (CHECK_BIT(USART_ISR(uart->UARTx), USART_ISR_RXNE) == 0U)
            continue;
    
        rxne = true;
    }
    else 
    {
        if (CHECK_BIT(USART_ISR(uart->UARTx), USART_ISR_RXNE) != 0U)
            rxne = true;
    }

    if (rxne == true)
    {
        *data = (uint8_t) (*USART_RDR(uart->UARTx));
        return 0;
    }

    return UART_NO_RECV;
}

//---------------------------------------------------------

int uart_recv_string(struct Uart* uart, uint8_t* data)
{
    uint8_t value = 0;

    do
    {
        int err = uart_recv_byte(uart, &value, true);
        if (err < 0) return err;

        *data = value;
        data++;

    } while (value != '\n');

    return 0;
}

//---------------------------------------------------------

int uart_recv_string_n(struct Uart* uart, uint8_t* data, unsigned n)
{
    unsigned ct = 0;

    while (ct < n)
    {
        uint8_t value = 0;
        
        int err = uart_recv_byte(uart, &value, true);
        if (err < 0) return err;

        // uart_send_byte(uart, value, false);

        data[ct] = value;
        
        if (value == '\r')
        {
            data[ct] = '\0';
            break;
        }

        ct++;
    }

    return 0;
}

//---------------------------------------------------------

int uart_send_string(struct Uart* uart, const char* string, bool wait_tc)
{
    for (size_t iter = 0; string[iter] != '\0'; iter++)
    {
        int res = uart_send_byte(uart, (uint8_t) string[iter], false);
        if (res < 0) return res;
    }

    if (wait_tc)
    {
        while (CHECK_BIT(USART_ISR(uart->UARTx), USART_ISR_TC) == 0U)
           continue;
    }

    return 0;
}
