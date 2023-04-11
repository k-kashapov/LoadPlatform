#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

#include "inc/modregs.h"
#include "inc/gpio.h"
#include "inc/rcc.h"
#include "inc/uart.h"
#include "uart.h"

//=========================================================

#define CPU_FREQENCY 48000000U // CPU frequency: 48 MHz
#define BLUE_LED_GPIOC_PIN  8U

//=========================================================

static void board_clocking_init(void);
static void board_gpio_init(void);

//=========================================================

void board_clocking_init()
{
    // (1) Clock HSE and wait for oscillations to setup.
    SET_BIT(REG_RCC_CR, REG_RCC_CR_HSEON);
    while (CHECK_BIT(REG_RCC_CR, REG_RCC_CR_HSERDY))
        continue;

    // (2) Configure PLL:
    // PREDIV output: HSE/2 = 4 MHz
    SET_REG_RCC_CFGR2_PREDIV(2);

    // (3) Select PREDIV output as PLL input (4 MHz):
    SET_REG_RCC_CFGR_PLLSRC(REG_RCC_CFGR_PLLSRC_HSE_PREDIV);

    // (4) Set PLLMUL to 12:
    // SYSCLK frequency = 48 MHz
    SET_REG_RCC_CFGR_PLLMUL(12);

    // (5) Enable PLL:
    SET_BIT(REG_RCC_CR, REG_RCC_CR_PLLON);
    while(CHECK_BIT(REG_RCC_CR, REG_RCC_CR_PLLRDY))
        continue;

    // (6) Configure AHB frequency to 48 MHz:
    SET_REG_RCC_CFGR_HPRE_NOT_DIV();

    // (7) Select PLL as SYSCLK source:
    SET_REG_RCC_CFGR_SW(REG_RCC_CFGR_SW_PLL);

    while(GET_REG_RCC_CFGR_SWS() != REG_RCC_CFGR_SWS_PLL)
        continue;

    // (8) Set APB frequency to 24 MHz
    SET_REG_RCC_CFGR_PPRE(REG_RCC_CFGR_PPRE_NOT_DIV);
}

//--------------------
// GPIO configuration
//--------------------

void board_gpio_init()
{
    // (1) Enable GPIOC clocking:
    SET_BIT(REG_RCC_AHBENR, REG_RCC_AHBENR_IOPCEN);

    // Configure PC8 mode:
    SET_GPIO_IOMODE(GPIOC, BLUE_LED_GPIOC_PIN, GPIO_IOMODE_GEN_PURPOSE_OUTPUT);

    // Configure PC8 type:
    SET_GPIO_OTYPE(GPIOC, BLUE_LED_GPIOC_PIN, GPIO_OTYPE_PUSH_PULL);
}

//------
// Main
//------

#define UART_BAUDRATE 9600U
#define BUFFER_SIZE 128U

int main()
{
    board_clocking_init();
    board_gpio_init();

    struct Uart uart = {};
    struct Port_n_pin tx = {.port = GPIOA, .pin = 9U};
    struct Port_n_pin rx = {.port = GPIOA, .pin = 10U};

    uint8_t tx_af = GPIO_AF1; 
    uint8_t rx_af = GPIO_AF1;

    int err = uart_setup(&uart, 1, &tx, tx_af,
                                   &rx, rx_af, UART_BAUDRATE, CPU_FREQENCY);
    if (err < 0) return err;
 
    err = uart_transmit_enable(&uart);
    if (err < 0) return err;
    
    err = uart_receive_enable(&uart);
    if (err < 0) return err;

    err = uart_send_string(&uart, "Hello, world!\r", true);
    if (err < 0) return err;

    while (1)
    {
        char buffer[BUFFER_SIZE] = { 0 };
            
        int err = uart_recv_string_n(&uart, (uint8_t*) buffer, BUFFER_SIZE);
        if (err < 0) return err;

        err = uart_send_string(&uart, "no you ", false);
        if (err < 0) return err;

        err = uart_send_string(&uart, buffer, false);
        if (err < 0) return err;

        err = uart_send_string(&uart, "\r", false);
        if (err < 0) return err;
    }

    // char string[] = "\rECHO: \n\r";
    // uint8_t data = 0;

    // while (1)
    // {
    //     err = uart_recv_byte(&uart, &data, false);
    //     if (err < 0 && err != UART_NO_RECV) return err;

    //     if (err == UART_NO_RECV)
    //         continue;

    //     string[7] = (char) data;

    //     err = uart_send_string(&uart, string, true);
    //     if (err < 0) return err;
    // }

    // bool led_is_on = false;
    // while (1)
    // {
    //     if (led_is_on == false)
    //     {
    //         led_is_on = true;
    //         GPIO_BSRR_SET_PIN(GPIOC, BLUE_LED_GPIOC_PIN);
    //     }
    //     else 
    //     {
    //         led_is_on = false;
    //         GPIO_BRR_RESET_PIN(GPIOC, BLUE_LED_GPIOC_PIN);
    //     }

    //     for (unsigned iter = 0; iter < 1000000; iter++);
    // }
}
