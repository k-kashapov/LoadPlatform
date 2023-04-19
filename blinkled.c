#include <stdbool.h>
#include <stdint.h>

#include "common/api.h"

int umain(struct API* api)
{
    __asm__ volatile("nop");
    __asm__ volatile("nop");
    __asm__ volatile("nop");

    while (1) 
    {
        for (volatile unsigned iter = 0U; iter < 500000U; iter++);

        api->green_led_on();
        api->blue_led_off();

        for (volatile unsigned iter = 0U; iter < 500000U; iter++);

        api->green_led_off();
        api->blue_led_on();
    }

    return 0;
}