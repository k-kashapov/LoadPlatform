#include <stdbool.h>
#include <stdlib.h>

//---------------------------------------------------------

#include "inc/gpio.h"
#include "inc/rcc.h"
#include "button.h"

//=========================================================

static const uint32_t Saturation_max  = 12U;

static const uint32_t Top_edge = 10U;
static const uint32_t Btm_edge = 2U;

//---------------------------------------------------------

static void button_gpio_setup(struct Button* button);

//=========================================================

int button_setup(struct Button* button, uint32_t GPIOx, uint8_t pin)
{
    if (button == NULL)
        return BTN_INV_PTR;

    if (GPIOx < GPIOA || GPIOx > GPIOF)
        return BTN_INV_GPIO;

    if (pin > 15)
        return BTN_INV_PIN;

    button->is_pressed = false;
    button->saturation = 0U;

    button->GPIOx = GPIOx;
    button->pin = pin;

    button_gpio_setup(button);

    return 0;
}

//---------------------------------------------------------

static void button_gpio_setup(struct Button* button)
{
    uint8_t bit = REG_RCC_AHBENR_IOPAEN + (button->GPIOx - GPIOA) / GPIO_offs;
    SET_BIT(REG_RCC_AHBENR, bit);

    SET_GPIO_IOMODE(button->GPIOx, button->pin, GPIO_IOMODE_INPUT);
    SET_GPIO_PUPD(button->GPIOx, button->pin, GPIO_PUPD_PD);

    return;
}

//---------------------------------------------------------

int button_update(struct Button* button)
{
    if (button == NULL)
        return BTN_INV_PTR;

    bool active = (bool) GPIO_IDR_GET_PIN(button->GPIOx, button->pin);

    if (active == true)
    {
        if (button->saturation < Saturation_max)
            button->saturation += 1;

        if (button->saturation >= Top_edge)
            button->is_pressed = true;
    }
    else 
    {
        if (button->saturation > 0U)
            button->saturation -= 1;

        if (button->saturation <= Btm_edge)
            button->is_pressed = false;
    }

    return 0;
}