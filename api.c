#include <stdint.h>

#include "inc/gpio.h"
#include "inc/rcc.h"
#include "api.h"
#include "button.h"
#include "screen.h"

//=========================================================

void blue_led_on(void);
void blue_led_off(void);
void green_led_on(void);
void green_led_off(void);

int is_button_pressed(unsigned num);

//---------------------------------------------------------

#define BLUE_LED_GPIOC_PIN   8U
#define GREEN_LED_GPIOC_PIN  9U

__attribute__ ((section (".api_const"))) 
const struct API API_host = 
{
    .blue_led_on = blue_led_on,
    .blue_led_off = blue_led_off,
    .green_led_on = green_led_on,
    .green_led_off = green_led_off,
    .is_button_pressed = is_button_pressed,
    .scrn_clear = scrn_clear,
    .scrn_draw = scrn_draw,
    .scrn_set_pxl = scrn_set_pxiel,
    .scrn_clr_pxl = scrn_clr_pxiel,
    .scrn_inv_pxl = scrn_inv_pxiel,
    .scrn_xline = scrn_xline,
    .scrn_yline = scrn_yline,
    .scrn_box = scrn_box
};

__attribute__ ((section (".api"))) 
static struct Button buttons[BUTTONS_NUM] = { 0 };

//=========================================================

int api_init(void)
{
    // (1) Enable GPIOC clocking:
    SET_BIT(REG_RCC_AHBENR, REG_RCC_AHBENR_IOPCEN);

    // Configure PC8 & PC9 mode:
    SET_GPIO_IOMODE(GPIOC, BLUE_LED_GPIOC_PIN, GPIO_IOMODE_GEN_PURPOSE_OUTPUT);
    SET_GPIO_IOMODE(GPIOC, GREEN_LED_GPIOC_PIN, GPIO_IOMODE_GEN_PURPOSE_OUTPUT);

    // Configure PC8 & PC9 type:
    SET_GPIO_OTYPE(GPIOC, BLUE_LED_GPIOC_PIN, GPIO_OTYPE_PUSH_PULL);
    SET_GPIO_OTYPE(GPIOC, GREEN_LED_GPIOC_PIN, GPIO_OTYPE_PUSH_PULL);

    for (unsigned iter = 0; iter < BUTTONS_NUM; iter++)
    {
        int err = button_setup(&buttons[iter], GPIOA, iter);
        if (err < 0) return err;
    }

    SPI_init(BAUD_DIV128);
    scrn_init(0);

    return 0;
}

//---------------------------------------------------------

void api_update(unsigned handler_ticks)
{
    (void) handler_ticks;

    for (unsigned iter = 0; iter < BUTTONS_NUM; iter++)
    {
        button_update(&(buttons[iter]));
    }

    // static bool led_is_on = false;

    // if ((handler_ticks % SYSTICK_FREQ) == 0)
    // {
    //     if (led_is_on == false)
    //     {
    //         led_is_on = true;
    //         GPIO_BSRR_SET_PIN(GPIOC, BLUE_LED_GPIOC_PIN);
    //     }
    //     else 
    //     {
    //         led_is_on = false;
    //         GPIO_BRR_RESET_PIN(GPIOC, BLUE_LED_GPIOC_PIN);
    //     }
    // }
}

//---------------------------------------------------------

int is_button_pressed(unsigned num)
{
    if (num >= BUTTONS_NUM)
        return -1;

    return button_is_pressed(&(buttons[num]));
}

//---------------------------------------------------------

void blue_led_on(void)
{
    GPIO_BSRR_SET_PIN(GPIOC, BLUE_LED_GPIOC_PIN);
}

//---------------------------------------------------------

void green_led_on(void)
{
    GPIO_BSRR_SET_PIN(GPIOC, GREEN_LED_GPIOC_PIN);
}

//---------------------------------------------------------

void blue_led_off(void)
{
    GPIO_BRR_RESET_PIN(GPIOC, BLUE_LED_GPIOC_PIN);
}

//---------------------------------------------------------

void green_led_off(void)
{
    GPIO_BRR_RESET_PIN(GPIOC, GREEN_LED_GPIOC_PIN);
}