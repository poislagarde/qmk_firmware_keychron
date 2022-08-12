#include "blinking_effect.h"

uint16_t blinking_effect_started_time = 0;
uint8_t blinking_effect_color_r = 0x0, blinking_effect_color_g = 0x0, blinking_effect_color_b = 0x0;

void start_blinking_effect(uint8_t red, uint8_t green, uint8_t blue) {
    blinking_effect_color_r = red;
    blinking_effect_color_g = green;
    blinking_effect_color_b = blue;

    blinking_effect_started_time = sync_timer_read();
}

void render_blinking_effect(void) {
    // render blinking effect
    uint16_t deltaTime = sync_timer_elapsed(blinking_effect_started_time);
    if (deltaTime <= BLINKING_EFFECT_DURATION) {
        uint8_t led_state = ((~deltaTime) >> BLINKING_EFFECT_DELAY) & 0x01;
        uint8_t val_r = led_state * blinking_effect_color_r;
        uint8_t val_g = led_state * blinking_effect_color_g;
        uint8_t val_b = led_state * blinking_effect_color_b;
        rgb_matrix_set_color_all(val_r, val_g, val_b);
    } else {
        // effect finished
        blinking_effect_started_time = 0;
    }
}
