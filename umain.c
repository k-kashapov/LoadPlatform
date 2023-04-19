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
        if (api->is_button_pressed(0) || api->is_button_pressed(1) 
         || api->is_button_pressed(2) || api->is_button_pressed(3))
        {
            api->green_led_on();
        }
        else
        {
            api->green_led_off();
        }
    }

    return 0;
}