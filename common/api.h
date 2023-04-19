#pragma once 

#define BUTTONS_NUM 4

struct API
{
    void (*blue_led_on )(void);
    void (*green_led_on)(void);

    void (*blue_led_off )(void);
    void (*green_led_off)(void);

    int (*is_button_pressed)(unsigned num);

    void (*scrn_clear)(uint8_t value);
    int (*scrn_draw)(void);

    int (*scrn_set_pxl)(unsigned x, unsigned y);
    int (*scrn_clr_pxl)(unsigned x, unsigned y);
    int (*scrn_inv_pxl)(unsigned x, unsigned y);
    int (*scrn_putchar)(unsigned x, unsigned y, int ch);

    int (*scrn_xline)(unsigned x, unsigned y, unsigned len);
    int (*scrn_yline)(unsigned x, unsigned y, unsigned len);

    int (*scrn_box)(unsigned x, unsigned y, unsigned x_len, unsigned y_len);
};

typedef int (*umain_t) (struct API* api);
int umain(struct API* api);