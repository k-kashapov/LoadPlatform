#pragma once 

//=========================================================

#include <stdint.h>

//=========================================================

struct Port_n_pin
{
    uint32_t port;
    uint8_t pin;
};

struct Uart_conf
{
    unsigned uartno;

    struct Port_n_pin tx;
    struct Port_n_pin rx;

    uint8_t af_tx;
    uint8_t af_rx;

    size_t baudrate;
    size_t frequency;
};

struct Uart
{
    uint16_t uartno;
    uint32_t UARTx;
    uint8_t irq_no;

    struct Port_n_pin tx;
    struct Port_n_pin rx;

    bool recv_enabled;
    bool trns_enabled;

    size_t baudrate;
};

enum Uart_error
{
    UART_INV_PTR        = -1,
    UART_INV_ARG        = -2,
    UART_NO_RECV        = -3,
    UART_RECV_DIS       = -4,
    UART_TRNS_DIS       = -5,
    UART_NO_SUPPORT     = -6,
    UART_TRNS_NOT_COMPL = -7,
    UART_RECV_NOT_COMPL = -8,
    UART_RECV_PE        = -9,
    UART_RECV_FE        = -10,
    UART_RECV_ORE       = -11,
    UART_RECV_NF        = -12,
};

//=========================================================

int uart_setup(struct Uart* uart, const struct Uart_conf* uart_conf);

int uart_transmit_enable(struct Uart* uart);
int uart_receive_enable(struct Uart* uart);

int uart_transmit_disable(struct Uart* uart);
int uart_receive_disable(struct Uart* uart);

int uart_trns_byte(struct Uart* uart, uint8_t data, bool wait_tc);
int uart_trns_string(struct Uart* uart, const char* string, bool wait_tc);

int uart_recv_byte(struct Uart* uart, uint8_t* data, bool wait_rxne);
int uart_recv_string(struct Uart* uart, uint8_t* data);
int uart_recv_string_n(struct Uart* uart, uint8_t* data, unsigned n);

int uart_trns_buffer(struct Uart* uart, const void* buffer, size_t size);
int uart_recv_buffer(struct Uart* uart, void* buffer, size_t size);

int is_trns_complete(void);
int is_recv_complete(void);

void uart_wait_for_tc(struct Uart* uart);
