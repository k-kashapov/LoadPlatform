#include "screen.h"
#include "inc/arm.h"

#define BIT_SET(REG, BIT)   do (REG) |=  (1U << (BIT)); while(0)
#define BIT_CLR(REG, BIT)   do (REG) &= ~(1U << (BIT)); while(0)
#define BIT_INV(REG, BIT)   do (REG) ^=  (1U << (BIT)); while(0)
#define BIT_READ(REG, BIT)  (REG & (1U << (BIT)))

#define MASK_LOWER(WIDTH) ((1U << (WIDTH)) - 1)

#define FIELD_WRITE(REG, VALUE, SHIFT) ((REG) |= ((VALUE) << (SHIFT)))
#define FIELD_READ(REG, MASK)          ((REG) & (MASK))

#define SCRN_MODE_SET(MODE)                     \
    do {                                        \
        if(MODE == MODE_CMD) {                  \
            BIT_CLR(*GPIO_ODR(GPIOC), DC_PIN);  \
        } else {                                \
            BIT_SET(*GPIO_ODR(GPIOC), DC_PIN);  \
        }                                       \
    } while (0)

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

static uint8_t FrameBuffer[SCRN_SIZ_BYTES] = {0};

static struct ScrSettings {
    unsigned rotated : 1;
} Settings = {0};

static void oled_init() {
    // To initialize OLED, we need to send 25 OLED commands
    // We will store these commands in an array
    // We then write them to the SPI one by one

    const char oled_initcmds[25] = {
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
        Settings.rotated ? OLED_COMSCANINC : OLED_COMSCANDEC,
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
        OLED_DISPLAYON
    };

    for (unsigned i = 0; i < sizeof(oled_initcmds); i++) {
        SPI_send_byte(oled_initcmds[i]);
        wfi();
    }
}

void scrn_init(uint8_t rotated) {
    // We are going to send a command
    SCRN_MODE_SET(MODE_CMD);

    // Will use LED_GREEN as RES pin. It must be High at the start of operation
    BIT_SET(*GPIO_ODR(GPIOC), RES_PIN);
    for (int i = 0; i < 1000; i++);

    // Turn off for a while to reset the screen
    BIT_CLR(*GPIO_ODR(GPIOC), RES_PIN);
    for (int i = 0; i < 100; i++) {
        for (int i = 0; i < 1000; i++);
    }

    // Turn on the power
    BIT_SET(*GPIO_ODR(GPIOC), RES_PIN);
    for (int i = 0; i < 100; i++) {
        for (int i = 0; i < 1000; i++);
    }

    Settings.rotated = !!rotated;

    oled_init();

    // Switch to data transfer mode
    SCRN_MODE_SET(MODE_DATA);
}

// Fills the entire screen with given value
void scrn_clear(uint8_t value) {
    SCRN_MODE_SET(MODE_DATA);
    for (unsigned byte = 0; byte < SCRN_SIZ_BYTES; byte++) {
        // SPI_send_byte(value);
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

int scrn_xline(unsigned x, unsigned y, unsigned len) {
    if (x + len >= SCRN_WIDTH || y >= SCRN_HEIGHT) {
        return -SCRN_E_INVAL;
    }

    unsigned idx_byte = x + ((y >> 3) << 7);
    unsigned idx_bit  = y & MASK_LOWER(3);

    for (unsigned i = 0; i < len; i++) {
        FrameBuffer[idx_byte + i] |= (unsigned char)(1 << idx_bit);
    }

    return SCRN_OK;
}

int scrn_yline(unsigned x, unsigned y, unsigned len) {
    if (x >= SCRN_WIDTH || y + len >= SCRN_HEIGHT) {
        return -SCRN_E_INVAL;
    }

    unsigned idx_byte = x + ((y >> 3) << 7);
    unsigned idx_bit  = y & MASK_LOWER(3);

    FrameBuffer[idx_byte] |= (unsigned char)(MASK_LOWER(len) << idx_bit);
    
    if (len > (8 - idx_bit)) {
        len -= (8 - idx_bit);
        idx_byte += SCRN_WIDTH;

        while (len > 8) {
            FrameBuffer[idx_byte] |= (unsigned char)(MASK_LOWER(8));
            idx_byte += SCRN_WIDTH;
            len -= 8;
        }

        FrameBuffer[idx_byte] |= (unsigned char)(MASK_LOWER(len));
    }
    
    return SCRN_OK;
}

int scrn_box(unsigned x, unsigned y, unsigned x_len, unsigned y_len) {
    if (x + x_len >= SCRN_WIDTH || y + y_len >= SCRN_HEIGHT) {
        return -SCRN_E_INVAL;
    }

    scrn_yline(x, y, y_len);
    scrn_xline(x, y, x_len);

    scrn_yline(x + x_len - 1, y, y_len);
    scrn_xline(x, y + y_len - 1, x_len);

    return SCRN_OK;
}

#include "inc/ascii.h"
int scrn_print(unsigned x, unsigned y, int ch) {
    if (x >= SCRN_WIDTH - 7 || y >= SCRN_HEIGHT - 7) {
        return -SCRN_E_INVAL;
    }

    const uint8_t (*buf)[8] = Settings.rotated ? ASCII_rot : ASCII;

    for (unsigned idx = 0; idx < 8; idx++) {
        FrameBuffer[x++ + ((y >> 3) << 7)] = buf[ch][idx];
    }

    return SCRN_OK;
}

int scrn_puts(unsigned x, unsigned y, char *str, unsigned len) {
    for (unsigned ch = 0; ch < len; ch++) {
        int res = scrn_print(x, y, str[ch]);
        if (res < 0) return res;
        x += 8;
    }

    return SCRN_OK;
}

