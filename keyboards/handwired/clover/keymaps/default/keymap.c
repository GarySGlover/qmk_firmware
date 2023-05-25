#include QMK_KEYBOARD_H
#include <keymap_uk.h>
#include "features/repeat_key.h"

enum custom_keycodes {
  CL_CPI_INCREASE = SAFE_RANGE,
  CL_CPI_DECREASE,
  CL_CPI_RESET,
  CL_CLEAR_LAYERS,
  REPEAT,
};

enum custom_layers {
  _ISRT,
  _ISRT_PLAIN,
  _QWERTY,
  _NUM,
  _NAV,
  _MOUSE,
  _DEBUG,
};

#include "g/keymap_combo.h"

static const char * const custom_layer_names[] = {
  [_ISRT] = "ISRT",
  [_QWERTY] = "QWERTY",
  [_NUM] = "Num",
  [_NAV] = "Nav",
  [_MOUSE] = "Mouse",
  [_DEBUG] = "Debug"
};

#ifdef OLED_ENABLE
static void render_logo(void) {
  static const char PROGMEM qmk_logo[] = {
    0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8A, 0x8B, 0x8C, 0x8D, 0x8E, 0x8F, 0x90, 0x91, 0x92, 0x93, 0x94,
    0xA0, 0xA1, 0xA2, 0xA3, 0xA4, 0xA5, 0xA6, 0xA7, 0xA8, 0xA9, 0xAA, 0xAB, 0xAC, 0xAD, 0xAE, 0xAF, 0xB0, 0xB1, 0xB2, 0xB3, 0xB4,
    0xC0, 0xC1, 0xC2, 0xC3, 0xC4, 0xC5, 0xC6, 0xC7, 0xC8, 0xC9, 0xCA, 0xCB, 0xCC, 0xCD, 0xCE, 0xCF, 0xD0, 0xD1, 0xD2, 0xD3, 0xD4, 0x00
  };

  oled_write_P(qmk_logo, false);
}

bool oled_task_user(void) {
  if (is_keyboard_master()) {
    oled_write_P(PSTR("Layer: "), false);
    oled_write_P(PSTR(custom_layer_names[get_highest_layer(layer_state)]), false);
    oled_write_P(PSTR("\n"), false);

    char master_cpi[5];
    utoa(pointing_device_get_cpi(), master_cpi, 10);
    oled_write_P(PSTR("LM: "), false);
    oled_write_P(PSTR(master_cpi), false);
    oled_write_P(PSTR(" RM: "), false);

    oled_write_P(PSTR("\n"), false);
  } else {
    render_logo();
  }

  return false;
}
#endif

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (!process_repeat_key(keycode, record, REPEAT)) { return false; }

  switch (keycode) {
  case CL_CPI_DECREASE:
    if (record->event.pressed) {
      if (pointing_device_get_cpi() > 800) {
        pointing_device_set_cpi(pointing_device_get_cpi() - 800);
        pointing_device_set_cpi_on_side(true, pointing_device_get_cpi());
        pointing_device_set_cpi_on_side(false, pointing_device_get_cpi());
      }
    }
    return false;
  case CL_CPI_INCREASE:
    if (record->event.pressed) {
      if (pointing_device_get_cpi() < 12800) {
        pointing_device_set_cpi(pointing_device_get_cpi() + 800);
        pointing_device_set_cpi_on_side(true, pointing_device_get_cpi());
        pointing_device_set_cpi_on_side(false, pointing_device_get_cpi());
      }
    }
    return false;
  case CL_CPI_RESET:
    if (record->event.pressed) {
      pointing_device_set_cpi(1600);
      pointing_device_set_cpi_on_side(true, 1600);
      pointing_device_set_cpi_on_side(false, 1600);
    }
    return false;
  case CL_CLEAR_LAYERS:
    if (record->event.pressed) {
      layer_clear();
    }
    return false;
  }

  return true;
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_ISRT] = LAYOUT(
                   UK_Y, LT(_DEBUG, UK_C), LT(_NAV, UK_L), LT(_NUM, UK_M), UK_K, UK_Z,  LT(_NUM, UK_F), LT(_NAV, UK_U), LT(_DEBUG, UK_COMM), UK_QUOT,
                   UK_I, UK_S, UK_R, UK_T, UK_G, UK_P, UK_N, UK_E, UK_A, UK_O,
                   UK_Q, MT(MOD_LALT, UK_V), MT(MOD_LCTL, UK_W), MT(MOD_LSFT, UK_D), MT(MOD_RALT, UK_J), MT(MOD_RALT, UK_B), MT(MOD_RSFT, UK_H), MT(MOD_RCTL, UK_SLSH), MT(MOD_LALT, UK_DOT), UK_X,
                   CL_CPI_DECREASE, CL_CPI_RESET, CL_CPI_INCREASE, KC_NO, KC_NO, KC_NO,
                   KC_BSPC, LT(_MOUSE, KC_SPC), QK_GRAVE_ESCAPE, REPEAT, OSM(MOD_LGUI), OSM(MOD_LSFT), LT(_MOUSE, KC_TAB), KC_ENT
                   ),
  [_ISRT_PLAIN] = LAYOUT(
                   UK_Y, UK_C, UK_L, UK_M, UK_K, UK_Z, UK_F, UK_U, UK_COMM, UK_QUOT,
                   UK_I, UK_S, UK_R, UK_T, UK_G, UK_P, UK_N, UK_E, UK_A, UK_O,
                   UK_Q, UK_V, UK_W, UK_D, UK_J,  UK_B, UK_H, UK_SLSH, UK_DOT, UK_X,
                   CL_CPI_DECREASE, CL_CPI_RESET, CL_CPI_INCREASE, KC_NO, KC_NO, KC_NO,
                   KC_BSPC, LT(_MOUSE, KC_SPC), QK_GRAVE_ESCAPE, KC_NO, OSM(MOD_LGUI), OSM(MOD_LSFT), LT(_MOUSE, KC_TAB), KC_ENT
                   ),  [_QWERTY] = LAYOUT(
                   UK_Q, LT(_DEBUG, UK_W), LT(_NAV, UK_E), LT(_NUM, UK_R), UK_T, UK_Y, LT(_NUM, UK_U), LT(_NAV, UK_I), LT(_DEBUG, UK_O), UK_P,
                   UK_A, UK_S, UK_D, UK_F, UK_G, UK_H, UK_J, UK_K, UK_L, UK_QUOT,
                   UK_Z, MT(MOD_LALT, UK_X), MT(MOD_LCTL, UK_C), MT(MOD_LSFT, UK_V), MT(MOD_RALT, UK_B), MT(MOD_RALT, UK_N), MT(MOD_RSFT, UK_M), MT(MOD_RCTL, UK_COMM), MT(MOD_LALT, UK_DOT), UK_SLSH,
                   CL_CPI_DECREASE, CL_CPI_RESET, CL_CPI_INCREASE, KC_NO, KC_NO, KC_NO,
                   KC_BSPC, LT(_MOUSE, KC_SPC), QK_GRAVE_ESCAPE, KC_NO, OSM(MOD_LGUI), KC_NO, LT(_MOUSE, KC_TAB), KC_ENT
                   ),
  [_NUM] = LAYOUT(
                  MT(MOD_LALT, UK_GRV), MT(MOD_LCTL, UK_SCLN), MT(MOD_LSFT, UK_COLN), UK_LCBR, UK_RCBR, UK_PLUS, UK_7, MT(MOD_RSFT, UK_8), MT(MOD_RCTL, UK_9), MT(MOD_LALT, UK_SLSH),
                  UK_TILD, UK_BSLS, UK_UNDS, UK_LPRN, UK_RPRN, UK_EQL, UK_4, UK_5, UK_6, UK_0,
                  UK_NOT, MT(MOD_LALT, UK_PIPE), MT(MOD_LCTL, UK_HASH), MT(MOD_LSFT, UK_LBRC), MT(MOD_RALT, UK_RBRC), MT(MOD_RALT, UK_MINS), MT(MOD_RSFT, UK_1), MT(MOD_RCTL, UK_2), MT(MOD_LALT, UK_3), UK_ASTR,
                  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
                  ),
  [_NAV] = LAYOUT(
                  KC_NO, KC_NO, KC_UP, KC_HOME, KC_NO, KC_NO, KC_PGUP, KC_NO, KC_NO, KC_NO,
                  KC_NO, KC_LEFT, KC_DOWN, KC_RGHT, KC_TAB, KC_NO, KC_LEFT, KC_UP, KC_DOWN, KC_RGHT,
                  KC_NO, KC_NO, KC_NO, KC_END, KC_TRNS, KC_TRNS, KC_PGDN, KC_NO, KC_NO, KC_NO,
                  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
                  ),
  [_MOUSE] = LAYOUT(
                    KC_NO, KC_NO, KC_WH_U, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
                    KC_NO, KC_WH_L, KC_WH_D, KC_WH_R, KC_NO, KC_BTN5, KC_BTN1, KC_BTN2, KC_BTN3, KC_BTN4,
                    KC_NO,  KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_MS_U, KC_MS_L, KC_MS_R, KC_MS_D,
                    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
                    ),
  [_DEBUG] = LAYOUT(
                    QK_BOOT, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, QK_BOOT,
                    DF(_ISRT), DF(_QWERTY), KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
                    KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
                    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
                    )
};
