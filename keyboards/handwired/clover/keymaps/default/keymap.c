// Copyright 2020 QMK
// SPDX-License-Identifier: GPL-2.0-or-later
#include QMK_KEYBOARD_H

enum custom_layers {
  _ISRT,
  _NUM,
  _SYM,
  _NAV,
  _EMPTY,
  _DEB
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_ISRT] = LAYOUT(
                   KC_Y, KC_C, KC_L, KC_M, KC_K, KC_Z, KC_F, KC_U, KC_COMMA, KC_QUOTE,
                   LGUI_T(KC_I), LALT_T(KC_S), LCTL_T(KC_R), LSFT_T(KC_T), RGUI_T(KC_G), RGUI_T(KC_P), LSFT_T(KC_N), LCTL_T(KC_E), LALT_T(KC_A), LGUI_T(KC_O),
                   KC_Q, KC_V, KC_W, KC_D, KC_J,         KC_B, KC_H, KC_SLASH, KC_DOT, KC_X,
                   KC_NO, KC_NO, KC_NO,                  KC_NO, KC_NO, KC_NO,
                   KC_NO, LT(_SYM,KC_BSPC), KC_ENT, KC_NO, KC_NO, QK_GESC, LT(_NUM,KC_SPC), KC_NO
                   ),
  [_NUM] = LAYOUT(
                   KC_NO, KC_PDOT, KC_PSLS, KC_PMNS, KC_F12, KC_F12, KC_PPLS, KC_PAST, KC_PEQL, KC_NO,
                   KC_9, KC_7, KC_5, KC_3, KC_1, KC_0, KC_2, KC_4, KC_6, KC_8,
                   KC_F9, KC_F7, KC_F5, KC_F3, KC_F1, KC_F10, KC_F2, KC_F4, KC_F6, KC_F8,
                   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                   KC_TRNS, KC_TRNS, MO(_NAV), KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
                  ),
  [_SYM] = LAYOUT(
                  KC_EXLM, KC_AT, KC_HASH, KC_DLR, KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_UNDS, KC_PLUS,
                  KC_LT, KC_LBRC, KC_LCBR, KC_LPRN, KC_SCLN, KC_COLN, KC_RPRN, KC_RCBR, KC_RBRC, KC_GT,
                  KC_NO, KC_NO, KC_PIPE, KC_SLSH, KC_NO, KC_NO, KC_NUBS, KC_QUES, KC_NO, KC_NO,
                  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, MO(3), KC_TRNS, KC_TRNS
                  ),
  [_NAV] = LAYOUT(
                  KC_NO, KC_NO, KC_UP, KC_HOME, KC_NO, KC_NO, KC_PGUP, KC_NO, KC_NO, KC_NO,
                  KC_NO, KC_LEFT, KC_DOWN, KC_RGHT, KC_NO, KC_NO, KC_LEFT, KC_UP, KC_DOWN, KC_RGHT,
                  KC_NO, KC_NO, KC_NO, KC_END, KC_NO, KC_NO, KC_PGDN, KC_NO, KC_NO, KC_NO,
                  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                  OSL(_DEB), KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
                  ),
  [_DEB] = LAYOUT(
                  KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
                  KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
                  KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
                  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, QK_BOOT,
                  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
                  ),
  [_EMPTY] = LAYOUT(
                  KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
                  KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
                  KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
                  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
                  )
};
