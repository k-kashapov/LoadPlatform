#include <stdint.h>
#include "btn.h"
#include "general.h"

#define MAX_SATURATION 24U
#if (MAX_SATURATION * 2 > UINT32_MAX)
    #error MAX_SATURATION is too big
#endif

bool button_is_pressed(struct button *btn) {
    volatile bool active = BIT_READ(*btn->reg, btn->bit);

    if (active) {
        if (btn->saturation < MAX_SATURATION - 1) {
            btn->saturation += 1;
        }

        if (btn->saturation > MAX_SATURATION * 2 / 3) {
            btn->state = 1;
        }
    } else {
        if (btn->saturation > 1) {
            btn->saturation -= 1;
        }

        if (btn->saturation < MAX_SATURATION / 3) {
            btn->state = 0;
        }
    }

    return btn->state;
}

#undef BTN_SATURATION
