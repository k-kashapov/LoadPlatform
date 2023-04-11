#ifndef BTN_H
#define BTN_H

#include <stdint.h>
#include <stdbool.h>

struct button {
    volatile uint32_t *reg;
             uint32_t bit;
             uint32_t saturation;
             bool state;
};

bool button_is_pressed(struct button *btn);

#endif // BTN_H
