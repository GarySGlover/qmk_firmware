// Copyright 2020 QMK
// SPDX-License-Identifier: GPL-2.0-or-later
#include QMK_KEYBOARD_H

enum custom_layers {
  _ISRT,
  _NUM,
  _SYM,
  _NAV,
  _MOUSE
};

#ifdef OLED_ENABLE
bool oled_task_user(void) {
    // Host Keyboard Layer Status
    oled_write_P(PSTR("Layer: "), false);
    oled_write_P(PSTR(get_highest_layer(layer_state)), false);
    oled_write_P(PSTR("\n"));
    
    return false;
}
#endif

static void render_logo(void) {
    static const char PROGMEM qmk_logo[] = {
        0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8A, 0x8B, 0x8C, 0x8D, 0x8E, 0x8F, 0x90, 0x91, 0x92, 0x93, 0x94,
        0xA0, 0xA1, 0xA2, 0xA3, 0xA4, 0xA5, 0xA6, 0xA7, 0xA8, 0xA9, 0xAA, 0xAB, 0xAC, 0xAD, 0xAE, 0xAF, 0xB0, 0xB1, 0xB2, 0xB3, 0xB4,
        0xC0, 0xC1, 0xC2, 0xC3, 0xC4, 0xC5, 0xC6, 0xC7, 0xC8, 0xC9, 0xCA, 0xCB, 0xCC, 0xCD, 0xCE, 0xCF, 0xD0, 0xD1, 0xD2, 0xD3, 0xD4, 0x00
    };

    oled_write_P(qmk_logo, false);
}

bool oled_task_user(void) {
    render_logo();
    return false;
}

void pointing_device_init_user(void) {
    set_auto_mouse_enable(true);         // always required before the auto mouse feature will work
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_ISRT] = LAYOUT(
      KC_Y,
      KC_C,
      KC_L,
      KC_M,
      KC_K,
      KC_Z,
      KC_F,
      KC_U,
      KC_COMM,
      KC_QUOT,
      KC_I,
      KC_S,
      KC_R,
      KC_T,
      KC_G,
      KC_P,
      KC_N,
      KC_E,
      KC_A,
      KC_O,
      KC_Q,
      KC_V,
      KC_W,
      KC_D,
      KC_J,
      KC_B,
      KC_H,
      KC_SLSH,
      KC_DOT,
      KC_X,
      KC_BSPC,
      KC_SPC,
      OSM(MOD_LSFT),
      OSM(MOD_LALT),
      OSM(MOD_LGUI),
      OSM(MOD_LCTL),
      TO(1),
      KC_ENT
                   ),
  [_NUM] = LAYOUT(
      TO(3),
      KC_PDOT,
      KC_PSLS,
      KC_PMNS,
      KC_F12,
      KC_F12,
      KC_PPLS,
      KC_PAST,
      KC_PEQL,
      TO(4),
      KC_9,
      KC_7,
      KC_5,
      KC_3,
      KC_1,
      KC_0,
      KC_2,
      KC_4,
      KC_6,
      KC_8,
      KC_F9,
      KC_F7,
      KC_F5,
      KC_F3,
      KC_F1,
      KC_F10,
      KC_F2,
      KC_F4,
      KC_F6,
      KC_F8,
      KC_TAB,
      TO(0),
      KC_TRNS,
      KC_TRNS,
      KC_TRNS,
      KC_TRNS,
      TO(2),
      KC_TRNS
                  ),
  [_SYM] = LAYOUT(
      KC_EXLM,
      KC_AT,
      KC_HASH,
      KC_DLR,
      KC_PERC,
      KC_CIRC,
      KC_AMPR,
      KC_ASTR,
      KC_UNDS,
      KC_PLUS,
      KC_LT,
      KC_LBRC,
      KC_LCBR,
      KC_LPRN,
      KC_SCLN,
      KC_COLN,
      KC_RPRN,
      KC_RCBR,
      KC_RBRC,
      KC_GT,
      KC_NO,
      KC_NO,
      KC_PIPE,
      KC_NUHS,
      KC_NO,
      KC_NO,
      KC_NUBS,
      KC_QUES,
      KC_NO,
      KC_NO,
      KC_BSPC,
      TO(0),
      KC_TRNS,
      KC_TRNS,
      KC_TRNS,
      KC_TRNS,
      TO(2),
      KC_TRNS
                  ),
  [_NAV] = LAYOUT(
      KC_NO,
      KC_NO,
      KC_UP,
      KC_HOME,
      KC_SCLN,
      KC_ASTR,
      KC_PGUP,
      KC_NO,
      KC_NO,
      KC_NO,
      KC_NO,
      KC_LEFT,
      KC_DOWN,
      KC_RGHT,
      KC_SLSH,
      KC_NUHS,
      KC_LEFT,
      KC_UP,
      KC_DOWN,
      KC_RGHT,
      KC_NO,
      KC_NO,
      KC_NO,
      KC_END,
      KC_NO,
      KC_NO,
      KC_PGDN,
      KC_NO,
      KC_NO,
      KC_NO,
      KC_BSPC,
      TO(0),
      KC_TRNS,
      KC_TRNS,
      KC_TRNS,
      KC_TRNS,
      KC_TRNS,
      KC_TRNS
                  ),
  [_MOUSE] = LAYOUT(
      KC_NO,
      KC_NO,
      KC_WH_U,
      KC_NO,
      KC_NO,
      KC_NO,
      KC_NO,
      KC_NO,
      KC_NO,
      KC_NO,
      KC_NO,
      KC_WH_L,
      KC_WH_D,
      KC_WH_R,
      KC_NO,
      KC_BTN5,
      KC_BTN1,
      KC_BTN2,
      KC_BTN3,
      KC_BTN4,
      KC_NO,
      KC_NO,
      KC_NO,
      KC_NO,
      KC_NO,
      KC_NO,
      KC_MS_U,
      KC_MS_L,
      KC_MS_R,
      KC_MS_D,
      KC_BSPC,
      TO(0),
      KC_TRNS,
      KC_TRNS,
      KC_TRNS,
      KC_TRNS,
      KC_TRNS,
      KC_TRNS
                  )
};
