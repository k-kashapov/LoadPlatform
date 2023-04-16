#include <stdint.h>

#include "inc/gpio.h"
#include "api.h"

//=========================================================

#define BLUE_LED_GPIOC_PIN   8U
#define GREEN_LED_GPIOC_PIN  9U

__attribute__ ((section (".api"))) 
struct API API_host = 
{
    .blue_led_on   = blue_led_on,
    .blue_led_off  = blue_led_off,
    .green_led_on  = green_led_on,
    .green_led_off = green_led_off 
};

//=========================================================

void blue_led_on (void)
{
    GPIO_BSRR_SET_PIN(GPIOC, BLUE_LED_GPIOC_PIN);
}

//---------------------------------------------------------

void green_led_on(void)
{
    GPIO_BSRR_SET_PIN(GPIOC, GREEN_LED_GPIOC_PIN);
}

//---------------------------------------------------------

void blue_led_off (void)
{
    GPIO_BRR_RESET_PIN(GPIOC, BLUE_LED_GPIOC_PIN);
}

//---------------------------------------------------------

void green_led_off(void)
{
    GPIO_BRR_RESET_PIN(GPIOC, GREEN_LED_GPIOC_PIN);
}