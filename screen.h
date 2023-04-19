#ifndef SCREEEN_H
#define SCREEEN_H

#include "inc/spi.h"
#include "inc/gpio.h"

// GPIOC pins
#define DC_PIN  6
#define RES_PIN 7

// DC pin values
#define MODE_DATA 1
#define MODE_CMD  0

// Screen cmd to turn it on
#define CMD_TURN_ON 0xAF

enum SCRN_ERR {
    SCRN_OK = 0,
    SCRN_E_INVAL = 3
};

#define SCRN_WIDTH  128
#define SCRN_HEIGHT 64

void scrn_init(uint8_t rotated);
void scrn_clear(uint8_t value);
void scrn_draw(void);

int scrn_set_pxiel(unsigned x, unsigned y);
int scrn_clr_pxiel(unsigned x, unsigned y);
int scrn_inv_pxiel(unsigned x, unsigned y);
int scrn_print    (unsigned x, unsigned y, int ch);

int scrn_xline(unsigned x, unsigned y, unsigned len);
int scrn_yline(unsigned x, unsigned y, unsigned len);

int scrn_box(unsigned x, unsigned y, unsigned x_len, unsigned y_len);

#endif // SCREEEN_H
