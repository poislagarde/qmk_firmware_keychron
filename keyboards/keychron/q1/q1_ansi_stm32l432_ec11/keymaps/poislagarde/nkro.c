#include "nkro.h"
#include "blinking_effect.h"

void set_nkro_helper(bool nkro) {
    keymap_config.nkro = nkro;
    clear_keyboard();  // clear to prevent stuck keys
}

void eeconfig_update_nkro(void) {
    // avoid persisting win lock state
    bool no_gui = keymap_config.no_gui;
    keymap_config.no_gui = false;

    eeconfig_update_keymap(keymap_config.raw);

    // restore win lock state
    keymap_config.no_gui = no_gui;

}

void set_nkro(bool enable) {
    if (keymap_config.nkro != enable) {
        set_nkro_helper(enable);
        eeconfig_update_nkro();
    }

    if (enable) {
        start_blinking_effect(RGB_GREEN);
    } else {
        start_blinking_effect(RGB_RED);
    }
}

void handle_nkro_keycode(uint16_t keycode) {
  switch (keycode) {
    case NK_TOGG:
        if (keymap_config.nkro) {
            // turn NKRO OFF
            set_nkro(false);
        } else {
            // turn NKRO ON
            set_nkro(true);
        }
        break;
    case NK_ON:
        // turn NKRO ON
        set_nkro(true);
        break;
    case NK_OFF:
        // turn NKRO OFF
        set_nkro(false);
        break;
  }
}
