#pragma once
#include "quantum.h"

// effect duration in milliseconds
#define BLINKING_EFFECT_DURATION 1500

// the higher this is, the slower the blinking will be -- must be a positive integer smaller than 16
#define BLINKING_EFFECT_DELAY 8

extern uint16_t blinking_effect_started_time;
extern uint8_t blinking_effect_color_r, blinking_effect_color_g, blinking_effect_color_b;

void start_blinking_effect(uint8_t red, uint8_t green, uint8_t blue);

// should only be called from rgb_matrix_indicators_user or rgb_matrix_indicators_advanced_user if blinking_effect_started_time > 0
void render_blinking_effect(void);
