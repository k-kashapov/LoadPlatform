#include <stdbool.h>
#include <stdint.h>

#include "common/api.h"

int umain(struct API* api)
{
    __asm__ volatile("nop"::);
    __asm__ volatile("nop"::);
    __asm__ volatile("nop"::);

    // api->blue_led_on();
    // static bool blue_led_is_off  = false;

    // bool green_led_is_off = true;

    while (1) {
        // if (green_led_is_off)
        // {
        //     api->green_led_on();
        //     green_led_is_off = false;
        // }
        // else if (!green_led_is_off)
        // {
        //     api->green_led_off();
        //     green_led_is_off = true;
        // }

        // if (blue_led_is_off)
        // {
        //     api->blue_led_on();
        //     blue_led_is_off = false;
        // }
        // else if (!blue_led_is_off)
        // {
        //     api->blue_led_off();
        //     blue_led_is_off = true;
        // }

        for (volatile unsigned iter = 0; iter < 100000; iter++);

        api->green_led_on();

        for (volatile unsigned iter = 0; iter < 100000; iter++);

        api->green_led_off();
    }

    return 0;
}