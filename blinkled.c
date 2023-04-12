#include <stdbool.h>
#include <stdint.h>

#include "common/api.h"

struct API api = {};
uint32_t api_ptr = (uint32_t) &api;

int main()
{
    static bool led_is_off = true;

    while (1)
    {
        if (led_is_off)
        {
            api.green_led_on();
            led_is_off = false;
        }
        else 
        {
            api.blue_led_off();
            led_is_off = true;
        }
    }
}