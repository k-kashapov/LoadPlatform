#pragma once 

struct API // TODO pass as argument, bss -> data, divide section mb, lds
{
    void (*blue_led_on )(void);
    void (*green_led_on)(void);

    void (*blue_led_off )(void);
    void (*green_led_off)(void);
};