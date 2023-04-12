#include <stdlib.h>
#include <stdbool.h>

//---------------------------------------------------------

#include "inc/uart.h"
#include "inc/gpio.h"
#include "inc/rcc.h"
#include "inc/nvic.h"
#include "inc/dma.h"
#include "uart.h"

//=========================================================

// #define UART_USE_IRQ

//=========================================================

static const uint32_t UARTx[8] = { USART1, USART2, USART3, USART4,
                                        USART5, USART6, USART7, USART8 };

static const uint8_t UARTx_irq_no[8] = { 27U, 28U, 29U, 29U,
                                         29U, 29U, 29U, 29U };

//---------------------------------------------------------

static void uart_gpio_setup(struct Uart* uart, const struct Uart_conf* uart_conf);
static void uart_usart_setup(struct Uart* uart, const struct Uart_conf* uart_conf);

static void uart_handler(unsigned uartno);

//---------------------------------------------------------

#define DMA_CH2_3_IRQ 10U

static bool Trns_complete = true;
static bool Recv_complete = true;

//=========================================================

int uart_setup(struct Uart* uart, const struct Uart_conf* uart_conf)
{
    if (uart == NULL)
        return UART_INV_PTR;

    if (uart_conf == NULL)
        return UART_INV_ARG;

    if (uart_conf->uartno != 1U && uart_conf->uartno != 2U)
        return UART_NO_SUPPORT;

    uart->uartno = uart_conf->uartno;

    uart->irq_no = UARTx_irq_no[uart_conf->uartno - 1];
    uart->UARTx = UARTx[uart_conf->uartno - 1];

    uart->tx = uart_conf->tx;
    uart->rx = uart_conf->rx;

    uart->recv_enabled = false;
    uart->trns_enabled = false;

    uart_gpio_setup(uart, uart_conf);
    uart_usart_setup(uart, uart_conf);

#ifdef UART_USE_IRQ
    NVIC_ENABLE_IRQ(uart->irq_no);
#endif 

    NVIC_ENABLE_IRQ(DMA_CH2_3_IRQ);
    SET_BIT(REG_RCC_AHBENR, REG_RCC_AHBENR_DMAEN);

    return 0;
}

//---------------------------------------------------------

static void uart_gpio_setup(struct Uart* uart, const struct Uart_conf* uart_conf)
{
    uint8_t bit_tx = REG_RCC_AHBENR_IOPAEN + (uart->tx.port - GPIOA) / GPIO_offs;
    uint8_t bit_rx = REG_RCC_AHBENR_IOPAEN + (uart->rx.port - GPIOA) / GPIO_offs;

    SET_BIT(REG_RCC_AHBENR, bit_tx);
    SET_BIT(REG_RCC_AHBENR, bit_rx);

    SET_GPIO_AF(uart->tx.port, uart->tx.pin, uart_conf->af_tx);
    SET_GPIO_AF(uart->rx.port, uart->rx.pin, uart_conf->af_rx);

    SET_GPIO_OSPEED(uart->tx.port, uart->tx.pin, GPIO_OSPEED_HIGH);
    SET_GPIO_OSPEED(uart->rx.port, uart->rx.pin, GPIO_OSPEED_HIGH);

    SET_GPIO_IOMODE(uart->tx.port, uart->tx.pin, GPIO_IOMODE_ALT_FUNC);
    SET_GPIO_IOMODE(uart->rx.port, uart->rx.pin, GPIO_IOMODE_ALT_FUNC);

    return;
}

//---------------------------------------------------------

static void uart_usart_setup(struct Uart* uart, const struct Uart_conf* uart_conf)
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

    CLEAR_BIT(USART_CR2(uart->UARTx), USART_CR2_MSBFIRST); // Endianness: LSB first
    SET_USART_CR2_STOP(uart->UARTx, USART_CR2_STOP_2);     // Number of stop bits: 2 stop bit

    SET_USART_BRR(uart->UARTx, (uart_conf->frequency) / (uart_conf->baudrate));

    SET_BIT(USART_CR1(uart->UARTx), USART_CR1_UE);
}

//---------------------------------------------------------

int uart_transmit_enable(struct Uart* uart)
{
    if (uart == NULL)
        return UART_INV_PTR;

    if (uart->trns_enabled == true)
        return 0;

#ifdef UART_USE_IRQ
    SET_BIT(USART_CR1(uart->UARTx), USART_CR1_TXEIE);
    SET_BIT(USART_CR1(uart->UARTx), USART_CR1_TCIE);
#endif 

    uart->trns_enabled = true;
    return 0;
}

//---------------------------------------------------------

int uart_receive_enable(struct Uart* uart)
{
    if (uart == NULL)
        return UART_INV_PTR;

    if (uart->recv_enabled == true)
        return 0;

    SET_BIT(USART_CR3(uart->UARTx), USART_CR3_DMAR);

    SET_DMA_CPAR(DMA_CPAR3, (uint32_t) USART_RDR(uart->UARTx)); // Peripheral
    SET_DMA_CCR_PL(DMA_CCR3, DMA_CCR_PL_MED); // Medium priority

    SET_DMA_CCR_MSIZE(DMA_CCR3, DMA_CCR_MSIZE_8);  // Memory size = 8 bits
    SET_DMA_CCR_PSIZE(DMA_CCR3, DMA_CCR_PSIZE_32); // Peripheral size = 32 bits

    SET_BIT(DMA_CCR3, DMA_CCR_MINC);  // Memory increment
    CLEAR_BIT(DMA_CCR3, DMA_CCR_DIR); // Direction - from peripheral to memory

    SET_BIT(USART_CR1(uart->UARTx), USART_CR1_RE);
    while (CHECK_BIT(USART_ISR(uart->UARTx), USART_ISR_REACK) == 0U)
        continue;

#ifdef UART_USE_IRQ
    SET_BIT(USART_CR1(uart->UARTx), USART_CR1_RXNEIE);
    SET_BIT(USART_CR1(uart->UARTx), USART_CR1_IDLEIE);
#endif 

    uart->recv_enabled = true;
    return 0;
}

//---------------------------------------------------------

int uart_transmit_disable(struct Uart* uart)
{
    if (uart == NULL)
        return UART_INV_PTR;

    if (uart->trns_enabled == false)
        return 0;

    CLEAR_BIT(USART_CR3(uart->UARTx), USART_CR3_DMAT);
    CLEAR_BIT(USART_CR1(uart->UARTx), USART_CR1_TE);

    while (CHECK_BIT(USART_ISR(uart->UARTx), USART_ISR_TEACK) == 0U)
        continue;

#ifdef UART_USE_IRQ
    CLEAR_BIT(USART_CR1(uart->UARTx), USART_CR1_TXEIE);
    CLEAR_BIT(USART_CR1(uart->UARTx), USART_CR1_TCIE);
#endif 

    uart->trns_enabled = false;
    return 0;
}

//---------------------------------------------------------

int uart_receive_disable(struct Uart* uart)
{
    if (uart == NULL)
        return UART_INV_PTR;

    if (uart->recv_enabled == false)
        return 0;

    CLEAR_BIT(USART_CR3(uart->UARTx), USART_CR3_DMAR);
    CLEAR_BIT(USART_CR1(uart->UARTx), USART_CR1_RE);

    while (CHECK_BIT(USART_ISR(uart->UARTx), USART_ISR_REACK) == 0U)
        continue;

#ifdef UART_USE_IRQ
    CLEAR_BIT(USART_CR1(uart->UARTx), USART_CR1_RXNEIE);
    CLEAR_BIT(USART_CR1(uart->UARTx), USART_CR1_IDLEIE);
#endif 

    uart->recv_enabled = false;
    return 0;
}

//---------------------------------------------------------

// int uart_trns_byte(struct Uart* uart, uint8_t data, bool wait_tc)
// {
//     if (uart == NULL)
//         return UART_INV_PTR;

//     if (uart->trns_enabled == false)
//         return UART_TRNS_DIS;

//     while (CHECK_BIT(USART_ISR(uart->UARTx), USART_ISR_TXE) == 0U)
//         continue;

//     *USART_TDR(uart->UARTx) = data;

//     if (wait_tc)
//     {
//         while (CHECK_BIT(USART_ISR(uart->UARTx), USART_ISR_TC) == 0U)
//            continue;
//     }

//     return 0;
// }

// //---------------------------------------------------------

// int uart_recv_byte(struct Uart* uart, uint8_t* data, bool wait_rxne)
// {
//     if (uart == NULL)
//         return UART_INV_PTR;

//     if (uart->recv_enabled == false)
//         return UART_RECV_DIS;

//     if (data == NULL)   
//         return UART_INV_ARG;

//     bool rxne = false;

//     if (wait_rxne)
//     {
//         while (CHECK_BIT(USART_ISR(uart->UARTx), USART_ISR_RXNE) == 0U)
//             continue;
    
//         rxne = true;
//     }
//     else 
//     {
//         if (CHECK_BIT(USART_ISR(uart->UARTx), USART_ISR_RXNE) != 0U)
//             rxne = true;
//     }

//     if (rxne == true)
//     {
//         *data = (uint8_t) (*USART_RDR(uart->UARTx));
//         return 0;
//     }

//     return UART_NO_RECV;
// }

// //---------------------------------------------------------

// int uart_recv_string(struct Uart* uart, uint8_t* data)
// {
//     uint8_t value = 0;

//     do
//     {
//         int err = uart_recv_byte(uart, &value, true);
//         if (err < 0) return err;

//         *data = value;
//         data++;

//     } while (value != '\n');

//     return 0;
// }

// //---------------------------------------------------------

// int uart_recv_string_n(struct Uart* uart, uint8_t* data, unsigned n)
// {
//     unsigned ct = 0;

//     while (ct < n)
//     {
//         uint8_t value = 0;
        
//         int err = uart_recv_byte(uart, &value, true);
//         if (err < 0) return err;

//         data[ct] = value;
        
//         if (value == '\r')
//         {
//             data[ct] = '\0';
//             break;
//         }

//         ct++;
//     }

//     return 0;
// }

// //---------------------------------------------------------

// int uart_trns_string(struct Uart* uart, const char* string, bool wait_tc)
// {
//     for (size_t iter = 0; string[iter] != '\0'; iter++)
//     {
//         int res = uart_trns_byte(uart, (uint8_t) string[iter], false);
//         if (res < 0) return res;
//     }

//     if (wait_tc)
//     {
//         while (CHECK_BIT(USART_ISR(uart->UARTx), USART_ISR_TC) == 0U)
//            continue;
//     }

//     return 0;
// }

//---------------------------------------------------------

void dma_ch2_3_handler(void)
{
    if (CHECK_BIT(DMA_ISR, DMA_ISR_TCIF2) != 0)
    {
        Trns_complete = true;
    }

    if (CHECK_BIT(DMA_ISR, DMA_ISR_TCIF3) != 0)
    {
        Recv_complete = true;
    }

    // GPIO_BSRR_SET_PIN(GPIOC, 9U);

    NVIC_CLEAR_PEND_IRQ(DMA_CH2_3_IRQ);
}

//---------------------------------------------------------

void uart1_handler(void)
{
    uart_handler(1);
}

//---------------------------------------------------------

void uart2_handler(void)
{
    uart_handler(2);
}

//---------------------------------------------------------

static void uart_handler(unsigned uartno)
{
#ifdef UART_USE_IRQ

    uint32_t uart = UARTx[uartno - 1];

    uint8_t data = 0;

    if (CHECK_BIT(USART_ISR(uart), USART_ISR_RXNE) != 0U)
        data = *USART_RDR(uart);

    if (CHECK_BIT(USART_ISR(uart), USART_ISR_TXE) != 0U)
        *USART_TDR(uart) = 'a';

    if (CHECK_BIT(USART_ISR(uart), USART_ISR_TC) != 0U)
        *USART_ICR(uart) = (1 << USART_ICR_TCCF);

    if (CHECK_BIT(USART_ISR(uart), USART_ISR_IDLE) != 0U)
        *USART_ICR(uart) = (1 << USART_ICR_IDLECF);

    data = data;

    NVIC_CLEAR_PEND_IRQ(UARTx_irq_no[uartno - 1]);

#else 

    (void) uartno;

#endif 
}

//---------------------------------------------------------

int uart_trns_buffer(struct Uart* uart, const void* buffer, size_t size)
{
    if (uart == NULL)
        return UART_INV_PTR;

    if (uart->trns_enabled == false)
        return UART_TRNS_DIS;

    if (Trns_complete != true)
        return UART_TRNS_NOT_COMPL;

    SET_BIT(USART_CR3(uart->UARTx), USART_CR3_DMAT); // use DMA

    SET_DMA_CPAR(DMA_CPAR2, (uint32_t) USART_TDR(uart->UARTx)); // Peripheral
    SET_DMA_CMAR(DMA_CPAR2, (uint32_t) buffer); // memory address
    SET_DMA_CNDTR_NDT(DMA_CNDTR2, size); // byte count

    SET_DMA_CCR_PL(DMA_CCR2, DMA_CCR_PL_MED); // Medium priority

    SET_BIT(DMA_CCR2, DMA_CCR_DIR); // Direction - from memory to peripheral
    SET_BIT(DMA_CCR2, DMA_CCR_MINC);  // Memory increment

    SET_DMA_CCR_MSIZE(DMA_CCR2, DMA_CCR_MSIZE_8);  // Memory size = 8 bits
    SET_DMA_CCR_PSIZE(DMA_CCR2, DMA_CCR_PSIZE_32); // Peripheral size = 32 bits

    SET_BIT(DMA_CCR2, DMA_CCR_TCIE); // Transfer complete interrupt enable

    Trns_complete = false;
    *USART_ICR(uart->UARTx) = (1 << USART_ICR_TCCF);
    SET_BIT(DMA_CCR2, DMA_CCR_EN); // enable channel

    SET_BIT(USART_CR1(uart->UARTx), USART_CR1_TE);
    while (CHECK_BIT(USART_ISR(uart->UARTx), USART_ISR_TEACK) == 0U)
        continue;

    return 0;
}

//---------------------------------------------------------

int uart_recv_buffer(struct Uart* uart, void* buffer, size_t size)
{
    if (uart == NULL)
        return UART_INV_PTR;

    if (uart->recv_enabled == false)
        return UART_TRNS_DIS;

    if (Recv_complete != true)
        return UART_TRNS_NOT_COMPL;

    SET_DMA_CMAR(DMA_CPAR3, (uint32_t) buffer); // memory address
    SET_DMA_CNDTR_NDT(DMA_CNDTR3, size); // byte count

    Recv_complete = false;
    SET_BIT(DMA_CCR3, DMA_CCR_EN); // enable channel

    return 0;
}

bool is_trns_complete(void)
{
    return Trns_complete;
}

//---------------------------------------------------------

bool is_recv_complete(void)
{
    return Recv_complete;
}

//---------------------------------------------------------

void uart_wait_for_tc(struct Uart* uart)
{
    while (CHECK_BIT(USART_ISR(uart->UARTx), USART_ISR_TC) == 0U)
        continue;
}