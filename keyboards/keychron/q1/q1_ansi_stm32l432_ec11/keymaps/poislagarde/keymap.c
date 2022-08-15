/* Copyright 2021 @ Keychron (https://www.keychron.com)
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include QMK_KEYBOARD_H
// #include "test.h"
#include "layers.h"
#include "blinking_effect.h"
#include "nkro.h"

enum custom_keycodes {
    KC_MISSION_CONTROL = USER00,
    KC_LAUNCHPAD,
    KC_LOPTN,
    KC_ROPTN,
    KC_LCMMD,
    KC_RCMMD,
    KC_TASK_VIEW,
    KC_FILE_EXPLORER,
    KC_ALT_TAB_TOGGLE
};

#define KC_MCTL KC_MISSION_CONTROL
#define KC_LPAD KC_LAUNCHPAD
#define KC_TASK KC_TASK_VIEW
#define KC_FLXP KC_FILE_EXPLORER
#define ATAB_TOG KC_ALT_TAB_TOGGLE

#define LED_LGUI 73
#define LED_TAB 30

bool no_alt_tab = false;

typedef struct PACKED {
    uint8_t len;
    uint8_t keycode[2];
} key_combination_t;

key_combination_t key_comb_list[2] = {
    {2, {KC_LWIN, KC_TAB}},
    {2, {KC_LWIN, KC_E}}
};

static uint8_t mac_keycode[4] = { KC_LOPT, KC_ROPT, KC_LCMD, KC_RCMD };

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [MAC_BASE] = LAYOUT_all(
        KC_ESC,   KC_BRID,  KC_BRIU,  KC_MCTL,  KC_LPAD,  RGB_VAD,  RGB_VAI,  KC_MPRV,  KC_MPLY,  KC_MNXT,  KC_MUTE,  KC_VOLD,    KC_VOLU,  KC_DEL,             KC_VOLD, KC_MUTE, KC_VOLU,
        KC_GRV,   KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_MINS,    KC_EQL,   KC_BSPC,            KC_HOME,
        KC_TAB,   KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,     KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_LBRC,    KC_RBRC,  KC_BSLS,            KC_PGUP,
        KC_CAPS,  KC_A,     KC_S,     KC_D,     KC_F,     KC_G,     KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,  KC_QUOT,              KC_ENT,             KC_PGDN,
        KC_LSFT,            KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,              KC_RSFT,  KC_UP,
        KC_LCTL,  KC_LOPTN, KC_LCMMD,                               KC_SPC,                                 KC_RCMMD, MO(MAC_FN), KC_ROPTN, KC_LEFT,  KC_DOWN,  KC_RGHT),

    [MAC_FN] = LAYOUT_all(
        _______,  KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,     KC_F12,   KC_INS,             RGB_VAD, RGB_TOG, RGB_VAI,
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  RGB_SPD,    RGB_SPI,  _______,            KC_END,
        _______,  _______,  _______,  _______,  NK_TOGG,  _______,  _______,  _______,  _______,  _______,  _______,  RGB_RMOD,   RGB_MOD,  _______,            KC_PSCR,
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  RGB_HUD,  RGB_HUI,              _______,            KC_PAUS,
        _______,            _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  RGB_SAD,  RGB_SAI,              _______,  _______,
        _______,  _______,  _______,                                _______,                                _______,  _______,    _______,  _______,  _______,  _______),

    [WIN_BASE] = LAYOUT_all(
        KC_ESC,   KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,     KC_F12,   KC_DEL,             KC_VOLD, KC_MUTE, KC_VOLU,
        KC_GRV,   KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_MINS,    KC_EQL,   KC_BSPC,            KC_HOME,
        KC_TAB,   KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,     KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_LBRC,    KC_RBRC,  KC_BSLS,            KC_PGUP,
        KC_CAPS,  KC_A,     KC_S,     KC_D,     KC_F,     KC_G,     KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,  KC_QUOT,              KC_ENT,             KC_PGDN,
        KC_LSFT,            KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,              KC_RSFT,  KC_UP,
        KC_LCTL,  KC_LGUI,  KC_LALT,                                KC_SPC,                                 KC_RALT,  MO(WIN_FN), KC_RCTL,  KC_LEFT,  KC_DOWN,  KC_RGHT),

    [WIN_FN] = LAYOUT_all(
        _______,  KC_BRID,  KC_BRIU,  KC_TASK,  KC_FLXP,  RGB_VAD,  RGB_VAI,  KC_MPRV,  KC_MPLY,  KC_MNXT,  KC_MUTE,  KC_VOLD,    KC_VOLU,  KC_INS,             RGB_VAD, RGB_TOG, RGB_VAI,
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  RGB_SPD,    RGB_SPI,  _______,            KC_END,
        ATAB_TOG, _______,  _______,  _______,  NK_TOGG,  _______,  _______,  _______,  _______,  _______,  _______,  RGB_RMOD,   RGB_MOD,  _______,            KC_PSCR,
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  RGB_HUD,  RGB_HUI,              _______,            KC_PAUS,
        _______,            _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  RGB_SAD,  RGB_SAI,              _______,  _______,
        _______,  GUI_TOG,  _______,                                _______,                                _______,  _______,    _______,  _______,  _______,  _______),
};

#if defined(VIA_ENABLE) && defined(ENCODER_ENABLE)

#define ENCODERS 1
static uint8_t  encoder_state[ENCODERS] = {0};
static keypos_t encoder_cw[ENCODERS]    = {{ 8, 5 }};
static keypos_t encoder_ccw[ENCODERS]   = {{ 7, 5 }};

void encoder_action_unregister(void) {
    for (int index = 0; index < ENCODERS; ++index) {
        if (encoder_state[index]) {
            keyevent_t encoder_event = (keyevent_t) {
                .key = encoder_state[index] >> 1 ? encoder_cw[index] : encoder_ccw[index],
                .pressed = false,
                .time = (timer_read() | 1)
            };
            encoder_state[index] = 0;
            action_exec(encoder_event);
        }
    }
}

void encoder_action_register(uint8_t index, bool clockwise) {
    keyevent_t encoder_event = (keyevent_t) {
        .key = clockwise ? encoder_cw[index] : encoder_ccw[index],
        .pressed = true,
        .time = (timer_read() | 1)
    };
    encoder_state[index] = (clockwise ^ 1) | (clockwise << 1);
    action_exec(encoder_event);
}

void matrix_scan_user(void) {
    encoder_action_unregister();
}

bool encoder_update_user(uint8_t index, bool clockwise) {
    encoder_action_register(index, clockwise);
    return false;
};

#endif

bool dip_switch_update_user(uint8_t index, bool active) {
    /* Send default layer state to host */
    // system_switch_state_report(index, active);

    if (index == 0) {
        // reset locked keys when switching between MAC / WIN
        keymap_config.no_gui = false;
        no_alt_tab = false;
    }

    return true;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case KC_MISSION_CONTROL:
            if (record->event.pressed) {
                host_consumer_send(0x29F);
            } else {
                host_consumer_send(0);
            }
            return false;  // Skip all further processing of this key
        case KC_LAUNCHPAD:
            if (record->event.pressed) {
                host_consumer_send(0x2A0);
            } else {
                host_consumer_send(0);
            }
            return false;  // Skip all further processing of this key
        case KC_LOPTN:
        case KC_ROPTN:
        case KC_LCMMD:
        case KC_RCMMD:
            if (record->event.pressed) {
                register_code(mac_keycode[keycode - KC_LOPTN]);
            } else {
                unregister_code(mac_keycode[keycode - KC_LOPTN]);
            }
            return false;  // Skip all further processing of this key
        case KC_TASK:
        case KC_FLXP:
            if (record->event.pressed) {
                for (uint8_t i = 0; i < key_comb_list[keycode - KC_TASK].len; i++) {
                    register_code(key_comb_list[keycode - KC_TASK].keycode[i]);
                }
            } else {
                for (uint8_t i = 0; i < key_comb_list[keycode - KC_TASK].len; i++) {
                    unregister_code(key_comb_list[keycode - KC_TASK].keycode[i]);
                }
            }
            return false;  // Skip all further processing of this key
        case GUI_TOG:
            if (record->event.pressed) {
                keymap_config.no_gui = !keymap_config.no_gui;
            }
            return false;  // Skip all further processing of this key
        case ATAB_TOG:
            if (record->event.pressed) {
                no_alt_tab = !no_alt_tab;
            }
            return false;  // Skip all further processing of this key
        case KC_TAB:
            if (get_mods() & MOD_BIT(KC_LALT)) {
                // suppress key when Alt-Tab is disabled
                return !no_alt_tab;
            }
            return true;
        case RGB_TOG:
            if (record->event.pressed) {
                rgb_matrix_toggle_noeeprom();
            }
            return false;  // Skip all further processing of this key
        case RGB_VAI:
            if (record->event.pressed) {
                if (get_mods() & MOD_MASK_SHIFT) {
                    rgb_matrix_decrease_val_noeeprom();
                } else {
                    rgb_matrix_increase_val_noeeprom();
                }
            }
            return false;  // Skip all further processing of this key
        case RGB_VAD:
            if (record->event.pressed) {
                if (get_mods() & MOD_MASK_SHIFT) {
                    rgb_matrix_increase_val_noeeprom();
                } else {
                    rgb_matrix_decrease_val_noeeprom();
                }
            }
            return false;  // Skip all further processing of this key
        case NK_TOGG:
        case NK_ON:
        case NK_OFF:
            if (record->event.pressed) {
                handle_nkro_keycode(keycode);
            }
            return false; // Skip all further processing of this key
        default:
            return true;   // Process all other keycodes normally
    }
}

void rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    if (blinking_effect_started_time > 0) {
        render_blinking_effect();
    } else {
        // capslock indicator
        if (host_keyboard_led_state().caps_lock) {
            rgb_matrix_set_color(CAPS_LOCK_LED_INDEX, RGB_WHITE);
        }
        // else {
        //     rgb_matrix_set_color(CAPS_LOCK_LED_INDEX, RGB_OFF);
        // }
        
        // turn off GUI key LED when disabled
        if (keymap_config.no_gui) {
            rgb_matrix_set_color(LED_LGUI, RGB_OFF);
        }

        // turn off Tab key LED when Alt-Tab is disabled
        if (no_alt_tab) {
            rgb_matrix_set_color(LED_TAB, RGB_OFF);
        }
    }
}

bool led_update_user (led_t led_state) {
    // disable default caps lock indicator
    return false;
}

void suspend_power_down_user(void) {
    rgb_matrix_set_suspend_state(true);
}

void suspend_wakeup_init_user(void) {
    rgb_matrix_set_suspend_state(false);
}
