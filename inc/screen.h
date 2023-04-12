#ifndef SCREEEN_H
#define SCREEEN_H

#include "SPI.h"
#include "GPIO.h"
#include "general.h"

// GPIOC pins
#define DC_PIN  4
#define RES_PIN LED_GREEN

// DC pin values
#define MODE_DATA 1
#define MODE_CMD  0

// Screen cmd to turn it on
#define CMD_TURN_ON 0xAF

#define SCRN_MODE_SET(MODE)             \
    do {                                \
        if(MODE == MODE_CMD) {          \
            BIT_CLR(*GPIOC_ODR, DC_PIN);\
        } else {                        \
            BIT_SET(*GPIOC_ODR, DC_PIN);\
        }                               \
    } while (0)

void scrn_init(void);

#endif // SCREEEN_H