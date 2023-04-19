#include <math.h>
#include "screen.h"

#define MAP_SIZE 8

void game() {
    const uint8_t MAP[8] = {
        0b00000000,
        0b00000000,
        0b00000000,
        0b00010000,
        0b01111100,
        0b00010000,
        0b00000000,
        0b00000000,
    };

    float FOV = 90;
    float FOV_step = FOV / SCRN_WIDTH;
    
    // Current view
    float view_angle = 0;



    while (1) {
        scrn_clear(0);
        sin(2);
    }
}
