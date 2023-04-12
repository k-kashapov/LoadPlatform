#include "screen.h"

// OLED Init commands
#define OLED_SETCONTRAST                    0x81
#define OLED_DISPLAYALLON_RESUME            0xA4
#define OLED_DISPLAYALLON                   0xA5
#define OLED_NORMALDISPLAY                  0xA6
#define OLED_INVERTDISPLAY                  0xA7
#define OLED_DISPLAYOFF                     0xAE
#define OLED_DISPLAYON                      0xAF
#define OLED_SETDISPLAYOFFSET               0xD3
#define OLED_SETCOMPINS                     0xDA
#define OLED_SETVCOMDETECT                  0xDB
#define OLED_SETDISPLAYCLOCKDIV             0xD5
#define OLED_SETPRECHARGE                   0xD9
#define OLED_SETMULTIPLEX                   0xA8
#define OLED_SETLOWCOLUMN                   0x00
#define OLED_SETHIGHCOLUMN                  0x10
#define OLED_SETSTARTLINE                   0x40
#define OLED_MEMORYMODE                     0x20
#define OLED_COMSCANINC                     0xC0
#define OLED_COMSCANDEC                     0xC8
#define OLED_SEGREMAP                       0xA0
#define OLED_CHARGEPUMP                     0x8D

void oled_init(void) {
    // To initialize OLED, we need to send 25 OLED commands
    // We will store these commands in an array
    // We then write them to the SPI one by one

    static const char oled_initcmds[25] = {
        OLED_DISPLAYOFF,
        OLED_SETDISPLAYCLOCKDIV,
        0x80,
        OLED_SETMULTIPLEX,
        0x3F, // 128x64
        OLED_SETDISPLAYOFFSET,
        0x00,
        OLED_SETSTARTLINE | 0x00,
        OLED_CHARGEPUMP,
        0x14,
        OLED_MEMORYMODE,
        0x00,
        OLED_SEGREMAP | 0x01,
        OLED_COMSCANDEC,
        OLED_SETCOMPINS,
        0x12, // 128x64
        OLED_SETCONTRAST,
        0xCF,
        OLED_SETPRECHARGE,
        0xF1,
        OLED_SETVCOMDETECT,
        0x40,
        OLED_DISPLAYALLON_RESUME,
        OLED_NORMALDISPLAY,
        0xAF
    };

    for (unsigned i = 0; i < sizeof(oled_initcmds); i++) {
        SPI_send_byte(oled_initcmds[i]);
        wfi();
    }
}

void scrn_init(void) {
    // We are going to send a command
    SCRN_MODE_SET(MODE_CMD);

    // Will use LED_GREEN as RES pin. It must be High at the start of operation
    BIT_SET(*GPIOC_ODR, RES_PIN);
    wfi();

    // Turn off for a while to reset the screen
    BIT_CLR(*GPIOC_ODR, RES_PIN);
    for (int i = 0; i < 400; i++) {
        wfi();
    }

    // Turn on the power
    BIT_SET(*GPIOC_ODR, RES_PIN);
    for (int i = 0; i < 400; i++) {
        wfi();
    }

    // Turn on the screen
    // int res;
    // do {
    //     res = SPI_send_byte(CMD_TURN_ON);
    // } while (res < 0);

    oled_init();

    // Switch to data transfer mode
    SCRN_MODE_SET(MODE_DATA);
}
