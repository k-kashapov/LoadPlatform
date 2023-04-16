#include <stdbool.h>
#include <stdint.h>

#include "common/api.h"

int umain(struct API* api)
{
    api->blue_led_on();

    static bool green_led_is_off = true;
    static bool blue_led_is_off  = false;

    while (1)
    {
        if (green_led_is_off)
        {
            api->green_led_on();
            green_led_is_off = false;
        }
        else 
        {
            api->green_led_off();
            green_led_is_off = true;
        }

        if (blue_led_is_off)
        {
            api->blue_led_on();
            blue_led_is_off = false;
        }
        else 
        {
            api->blue_led_off();
            blue_led_is_off = true;
        }
    }
}