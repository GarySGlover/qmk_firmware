// Copyright 2020 QMK
// SPDX-License-Identifier: GPL-2.0-or-later
#include QMK_KEYBOARD_H

enum custom_layers {
  _ISRT,
  _NUMPAD
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_ISRT] = LAYOUT_c_tractyl(
                   KC_Y, KC_C, KC_L, KC_M, KC_K,         KC_Z, KC_F, KC_U, KC_COMMA, KC_QUOTE,
                   KC_I, KC_S, KC_R, KC_T, KC_G,         KC_P, KC_N, KC_E, KC_A, KC_O,
                   KC_Q, KC_V, KC_W, KC_D, KC_J,         KC_B, KC_H, KC_SLASH, KC_DOT,
                   KC_NO, KC_NO, KC_NO, KC_NO,           KC_NO, KC_NO, KC_NO, KC_NO,
                   KC_NO, MO(_NUMPAD), KC_NO, KC_NO,     KC_NO, KC_NO, KC_NO, KC_NO
                   ),
  [_NUMBERS] = LAYOUT_c_tractyl(
                   KC_TRNS, KC_F1, KC_F2, KC_F3, KC_F4,    KC_1, KC_2, KC_3, KC_TRNS, KC_TRNS,
                   KC_TRNS, KC_F5, KC_F6, KC_F7, KC_F8,    KC_4, KC_5, KC_6, KC_0, KC_TRNS,
                   KC_TRNS, KC_F9, KC_F10, KC_F11, KC_F12, KC_7, KC_8, KC_9, KC_DOT, KC_TRNS,
                   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,     KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,     KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
                   
  )
};
