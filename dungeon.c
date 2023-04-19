#include <stdint.h>
#include "trigTables.h"
#include "screen.h"
// #include "common/api.h"

// <====< WARNING >====>
// All floating point values are replaced with
// integer counterparts * 1000 to save space.

#define MAP_VALUE(x, y) (MAP[y / 1000] & (1 << (7 - (x / 1000) )))
#define PI 3141

// TODO: tables are symmetrical so they can be optimized further
int sin_aprx(int x_deg) {
    unsigned idx = (unsigned)(x_deg * 100 / 180) % 100;
    return sineTable[idx];
}

int cos_aprx(int x_deg) {
    unsigned idx = (unsigned)(x_deg * 100 / 180) % 100;
    return cosTable[idx];
}

void game(void) {

// int umain(struct API* api) {
    // <-----< Settings >----->

    const uint8_t MAP[8] = {
        0b11111111,
        0b10000001,
        0b10000001,
        0b10000001,
        0b10001001,
        0b10010001,
        0b10000001,
        0b11111111,
    };
    
    const int draw_dist = 5000;
    const int ray_steps = 20;
    const int step_dist = draw_dist / ray_steps;
    
    // const int plr_spd = 0.1;

    // <----< Player position >----->

    // Current angle between view direction and Ox axis
    int view_angle = 0; // Degrees
    
    int plr_x = 6000;
    int plr_y = 6000;

    // <----< Main loop >----->
    while (1) {
        scrn_clear(0xFF);

        // Ray cast
        for (int x = -SCRN_WIDTH / 2; x < SCRN_WIDTH / 2; x++) {
            int ray_angle = view_angle + x;

            for (int step = 0; step < ray_steps; step++) {
                unsigned check_x = (unsigned)(plr_x + cos_aprx(ray_angle) * step_dist * step / 1000);
                unsigned check_y = (unsigned)(plr_y + sin_aprx(ray_angle) * step_dist * step / 1000);

                if (check_x >= 8000 || check_y >= 8000) break;

                scrn_yline(x + SCRN_WIDTH / 2, (SCRN_HEIGHT - 20) / 2, 20);

                if (MAP_VALUE(check_x, check_y)) {
                    unsigned line_len = (unsigned)((ray_steps - step) * 2);
                    scrn_yline(x + SCRN_WIDTH / 2, (SCRN_HEIGHT - line_len) / 2, line_len);
                    break;
                }
            }

            // view_angle += 0.002;
            // if      (view_angle >=  2 * PI) view_angle -= 2 * PI;
            // else if (view_angle <= -2 * PI) view_angle += 2 * PI;
        }

        // if (button_left) {
        //     plr_x += sin_aprx(view_angle) * plr_spd;
        //     plr_y += cos_aprx(view_angle) * plr_spd;
        // }
        // if (button_right) {
            
        // }

        scrn_draw();

        for (int i = 0; i < 250000; i++)
            ;
    }
}
