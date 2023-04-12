#include "screen.h"

#define SCRN_WIDTH     128
#define SCRN_HEIGHT    64
#define SCRN_SIZ_BITS  (SCRN_HEIGHT * SCRN_WIDTH)
#define SCRN_SIZ_BYTES (SCRN_SIZ_BITS >> 3)

// TODO: Organise screen functions
// TODO: Make text printing

// Init sequence is copied from https://github.com/digitallyamar/STM32_SSD1306_OLED_SPI_Baremetal

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

static uint8_t  FrameBuffer[SCRN_SIZ_BYTES] = {0};

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
        0xFF,
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
    for (int i = 0; i < 100; i++) {
        wfi();
    }

    // Turn on the power
    BIT_SET(*GPIOC_ODR, RES_PIN);
    for (int i = 0; i < 100; i++) {
        wfi();
    }

    oled_init();

    // Switch to data transfer mode
    SCRN_MODE_SET(MODE_DATA);
}

// Fills the entire screen with given value
void scrn_clear(uint8_t value) {
    SCRN_MODE_SET(MODE_DATA);
    for (unsigned byte = 0; byte < SCRN_SIZ_BYTES; byte++) {
        SPI_send_byte(value);
        FrameBuffer[byte] = value;
    }
}

void scrn_draw(void) {
    SCRN_MODE_SET(MODE_DATA);
    for (unsigned byte = 0; byte < SCRN_SIZ_BYTES; byte++) {
        SPI_send_byte(FrameBuffer[byte]);
    }
}

int scrn_set_pxiel(unsigned x, unsigned y) {
    if (x >= SCRN_WIDTH || y >= SCRN_HEIGHT) {
        return -SCRN_E_INVAL;
    }

    unsigned idx_byte = x + ((y >> 3) << 7);
    unsigned idx_bit  = y & MASK_LOWER(3);

    FrameBuffer[idx_byte] |= (1 << idx_bit);

    return SCRN_OK;
}

int scrn_clr_pxiel(unsigned x, unsigned y) {
    if (x >= SCRN_WIDTH || y >= SCRN_HEIGHT) {
        return -SCRN_E_INVAL;
    }

    unsigned idx_byte = x + ((y >> 3) << 7);
    unsigned idx_bit  = y & MASK_LOWER(3);

    FrameBuffer[idx_byte] &= ~(1 << idx_bit);

    return SCRN_OK;
}

int scrn_inv_pxiel(unsigned x, unsigned y) {
    if (x >= SCRN_WIDTH || y >= SCRN_HEIGHT) {
        return -SCRN_E_INVAL;
    }

    unsigned idx_byte = x + ((y >> 3) << 7);
    unsigned idx_bit  = y & MASK_LOWER(3);

    FrameBuffer[idx_byte] &= ~(1 << idx_bit);

    return SCRN_OK;
}

#include "ascii.h"
int scrn_print(char ch) {
    (void) ch;

    for (unsigned idx = 0; idx < 8; idx++) {
        SPI_send_byte(ASCII_A[idx]);
    }

    return SCRN_OK;
}
