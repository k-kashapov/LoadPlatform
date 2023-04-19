#include <stdbool.h>
#include <stdint.h>

#include "common/api.h"

int umain(struct API* api)
{
    __asm__ volatile("nop");
    __asm__ volatile("nop");
    __asm__ volatile("nop");

    unsigned blinkled_ct = 0U;
    bool blue_led_is_on = false;

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

        if ((blinkled_ct % 50000U) == 0U)
        {
            blinkled_ct = 0U;

            if (!blue_led_is_on)
            {
                api->blue_led_on();
                blue_led_is_on = true;
            }
            else 
            {
                api->blue_led_off();
                blue_led_is_on = false;
            }
        }

        blinkled_ct++;
    }

    return 0;
}