#pragma once 

//=========================================================

#include <stdint.h>

//=========================================================

struct Port_n_pin
{
    uint32_t port;
    uint8_t pin;
};

struct Uart
{
    uint16_t uartno;
    uint32_t UARTx;

    struct Port_n_pin tx;
    struct Port_n_pin rx;
};

enum Uart_error
{
    UART_INV_PTR = -1,
    UART_INV_ARG = -2,
    UART_NO_RECV = -3
};

//=========================================================

int uart_setup(struct Uart* uart, uint16_t uartno, const struct Port_n_pin* tx, uint8_t af_tx,
                                                   const struct Port_n_pin* rx, uint8_t af_rx,
                                                   size_t baudrate, size_t frequency);

int uart_transmit_enable(struct Uart* uart);
int uart_receive_enable(struct Uart* uart);

int uart_send_byte(struct Uart* uart, uint8_t data, bool wait_tc);
int uart_send_string(struct Uart* uart, const char* string, bool wat_tc);

int uart_recv_byte(struct Uart* uart, uint8_t* data, bool wait_rxne);
int uart_recv_string(struct Uart* uart, uint8_t* data);
int uart_recv_string_n(struct Uart* uart, uint8_t* data, unsigned n);
