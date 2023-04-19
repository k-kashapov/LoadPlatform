#pragma once 

//=========================================================

#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

//=========================================================

struct Button
{
    uint32_t GPIOx;
    uint8_t pin;

    uint32_t saturation;
    bool is_pressed;
};

enum Button_error
{
    BTN_INV_PTR  = -1,
    BTN_INV_GPIO = -2,
    BTN_INV_PIN  = -3
};

//=========================================================

// Setup button on GPIOx:pin
int button_setup(struct Button* button, uint32_t GPIOx, uint8_t pin);

// Read from input and update state of button
int button_update(struct Button* button);

static inline bool button_is_pressed(struct Button* button)
{
    if (button == NULL)
        return BTN_INV_PTR;
    
    return button->is_pressed;
}