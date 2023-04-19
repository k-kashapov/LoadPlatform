#include <stdint.h>
#include "trigTables.h"
#include "common/api.h"

#define MAP_VALUE(x, y) (MAP[y] & (1 << (7 - x)))
#define PI 3.1415

int sin_aprx(int x) {
    unsigned idx = (unsigned)(x / (2 * PI) * 100) % 100;
    return sineTable[idx];
}

int cos_aprx(int x) {
    unsigned idx = (unsigned)(x / (2 * PI) * 100) % 100;
    return cosTable[idx];
}

int umain(struct API* api) {
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

    const int FOV   = SCRN_WIDTH;
    const int vstep = FOV / SCRN_WIDTH;
    
    const int draw_dist = 5.0;
    const int ray_steps = 20;
    const int step_dist = draw_dist / ray_steps;
    
    // const int plr_spd = 0.1;

    // <----< Player position >----->

    // Current angle between view direction and Ox axis
    int view_angle = 0;
    
    int plr_x = 6;
    int plr_y = 6;

    // <----< Main loop >----->
    while (1) {
        api->scrn_clear(0x00);

        // Ray cast
        for (int x = -SCRN_WIDTH / 2; x < SCRN_WIDTH / 2; x++) {
            int ray_angle = view_angle + vstep * x;
            for (int step = 0; step < ray_steps; step++) {
                unsigned check_x = (unsigned)(plr_x + cos_aprx(ray_angle) * step_dist * step);
                unsigned check_y = (unsigned)(plr_y + sin_aprx(ray_angle) * step_dist * step);

                if (check_x >= 8 || check_y >= 8) break;

                if (MAP_VALUE(check_x, check_y)) {
                    unsigned line_len = (unsigned)((ray_steps - step) * 2);
                    api->scrn_yline(x + SCRN_WIDTH / 2, (SCRN_HEIGHT - line_len) / 2, line_len);
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

        plr_x -= 0.01;
        if (plr_x <= 1) {
            plr_x = 6;
        }

        api->scrn_draw();

        for (int i = 0; i < 250000; i++)
            ;
    }
}
