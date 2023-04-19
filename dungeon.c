#include "screen.h"
#include "inc/arm.h"

#define MAP_VALUE(x, y) (MAP[y] & (1 << (7 - x)))
#define PI 3.1415

float sin_aprx(int x) {
    return x - x*x*x / 6;
}

float cos_aprx(int x) {
    return 1 - x * x / 2;
}

void game(void) {
    // <-----< Settings >----->

    const uint8_t MAP[8] = {
        0b00000000,
        0b00000000,
        0b00000000,
        0b00000000,
        0b00010000,
        0b00000000,
        0b00000000,
        0b00000000,
    };

    const float FOV   = PI / 2;
    const float vstep = FOV / SCRN_WIDTH;
    
    const float draw_dist = 5.0;
    const int   ray_steps = 10;
    const float step_dist = draw_dist / ray_steps;
    
    // <----< Player position >----->

    // Current angle between view direction and Ox axis
    float view_angle = 0;
    
    float plr_x = 0;
    float plr_y = 4;

    // <----< Main loop >----->
    while (1) {
        scrn_clear(0x00);

        // Ray cast
        for (int x = -SCRN_WIDTH / 2; x < SCRN_WIDTH / 2; x++) {
            float ray_angle = view_angle + vstep * x;
            for (int step = 1; step < ray_steps; step++) {
                unsigned check_x = (unsigned)(plr_x + cos_aprx(ray_angle) * step_dist * step);
                unsigned check_y = (unsigned)(plr_y + sin_aprx(ray_angle) * step_dist * step);

                if (check_x >= 8 || check_y >= 8 ||
                    check_x  < 0 || check_y < 0) break;

                if (MAP_VALUE(check_x, check_y)) {
                    unsigned line_len = (ray_steps - step) * 4;
                    scrn_yline(x + SCRN_WIDTH / 2, (SCRN_HEIGHT - line_len) / 2, line_len);
                    break;
                }
            }

            view_angle += 0.002;
            if      (view_angle >=  2 * PI)   view_angle -= 2 * PI;
            else if (view_angle <= -2 * PI) view_angle += 2 * PI;
        }

        scrn_draw();

        for (int i = 0; i < 5000; i++)
            wfi();
    }
}
