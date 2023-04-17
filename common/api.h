#pragma once 

struct API
{
    void (*blue_led_on )(void);
    void (*green_led_on)(void);

    void (*blue_led_off )(void);
    void (*green_led_off)(void);
};

typedef int (*umain_t) (struct API* api);
int umain(struct API* api);