#include QMK_KEYBOARD_H
#include <keymap_uk.h>

enum custom_keycodes {
  CL_CPI_INCREASE = SAFE_RANGE,
  CL_CPI_DECREASE,
  CL_CPI_RESET,
  CL_CLEAR_LAYERS,
  IR_SFT,
};

#include "g/keymap_combo.h"

enum custom_layers {
  _ISRT,
  _QWERTY,
  _NUM,
  _NAV,
  _MOUSE,
  _DEBUG,
  _IRONSEAT
};

static const char * const custom_layer_names[] = {
  [_ISRT] = "ISRT",
  [_QWERTY] = "QWERTY",
  [_NUM] = "Num",
  [_NAV] = "Nav",
  [_MOUSE] = "Mouse",
  [_DEBUG] = "Debug",
  [_IRONSEAT] = "Iron Seat",
};

/* enum custom_keycodes { */
/*   CL_CPI_INCREASE = SAFE_RANGE, */
/*   CL_CPI_DECREASE, */
/*   CL_CPI_RESET, */
/*   CL_CLEAR_LAYERS, */
/*   IR_SFT, */
/* }; */

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

/* const uint16_t PROGMEM default_layer_combo[] = {KC_BSPC, KC_ENT, COMBO_END}; */
/* const uint16_t PROGMEM num_layer_combo[] = {LT(_NUM, UK_M), LT(_NUM, UK_F), COMBO_END}; */
/* const uint16_t PROGMEM mouse_layer_combo[] = {LT(_MOUSE, KC_SPC), LT(_MOUSE, KC_TAB), COMBO_END}; */
/* const uint16_t PROGMEM nav_layer_combo[] = {LT(_NAV, UK_L), LT(_NAV, UK_U), COMBO_END}; */
/* const uint16_t PROGMEM caps_word_combo[] = {MT(MOD_LSFT, UK_D), MT(MOD_RSFT, UK_H), COMBO_END}; */
/* const uint16_t PROGMEM num_layer_q_combo[] = {LT(_NUM, UK_R), LT(_NUM, UK_U), COMBO_END}; */
/* const uint16_t PROGMEM nav_layer_q_combo[] = {LT(_NAV, UK_E), LT(_NAV, UK_I), COMBO_END}; */
/* const uint16_t PROGMEM caps_word_q_combo[] = {MT(MOD_LSFT, UK_V), MT(MOD_RSFT, UK_M), COMBO_END}; */

/* const uint16_t PROGMEM iron_b[] = {KC_R, KC_N, COMBO_END}; */
/* const uint16_t PROGMEM iron_c[] = {KC_S, KC_R, COMBO_END}; */
/* const uint16_t PROGMEM iron_d[] = {KC_E, KC_A, COMBO_END}; */
/* const uint16_t PROGMEM iron_f[] = {KC_S, KC_T, COMBO_END}; */
/* const uint16_t PROGMEM iron_g[] = {KC_N, KC_A, COMBO_END}; */
/* const uint16_t PROGMEM iron_h[] = {KC_R, KC_T, COMBO_END}; */
/* const uint16_t PROGMEM iron_j[] = {KC_R, KC_A, COMBO_END}; */
/* const uint16_t PROGMEM iron_k[] = {KC_S, KC_N, COMBO_END}; */
/* const uint16_t PROGMEM iron_l[] = {KC_N, KC_E, COMBO_END}; */
/* const uint16_t PROGMEM iron_m[] = {KC_R, KC_E, COMBO_END}; */
/* const uint16_t PROGMEM iron_p[] = {KC_I, KC_T, COMBO_END}; */
/* const uint16_t PROGMEM iron_q[] = {KC_I, KC_O, COMBO_END}; */
/* const uint16_t PROGMEM iron_u[] = {KC_T, KC_N, COMBO_END}; */
/* const uint16_t PROGMEM iron_v[] = {KC_T, KC_A, COMBO_END}; */
/* const uint16_t PROGMEM iron_w[] = {KC_T, KC_E, COMBO_END}; */
/* const uint16_t PROGMEM iron_x[] = {KC_S, KC_A, COMBO_END}; */
/* const uint16_t PROGMEM iron_y[] = {KC_N, KC_O, COMBO_END}; */
/* const uint16_t PROGMEM iron_z[] = {KC_S, KC_E, COMBO_END}; */
/* const uint16_t PROGMEM iron_A[] = {IR_SFT, KC_A, COMBO_END}; */
/* const uint16_t PROGMEM iron_B[] = {IR_SFT, KC_R, KC_N, COMBO_END}; */
/* const uint16_t PROGMEM iron_C[] = {IR_SFT, KC_S, KC_R, COMBO_END}; */
/* const uint16_t PROGMEM iron_D[] = {IR_SFT, KC_E, KC_A, COMBO_END}; */
/* const uint16_t PROGMEM iron_E[] = {IR_SFT, KC_E, COMBO_END}; */
/* const uint16_t PROGMEM iron_F[] = {IR_SFT, KC_S, KC_T, COMBO_END}; */
/* const uint16_t PROGMEM iron_G[] = {IR_SFT, KC_N, KC_A, COMBO_END}; */
/* const uint16_t PROGMEM iron_H[] = {IR_SFT, KC_R, KC_T, COMBO_END}; */
/* const uint16_t PROGMEM iron_I[] = {IR_SFT, KC_I, COMBO_END}; */
/* const uint16_t PROGMEM iron_J[] = {IR_SFT, KC_R, KC_A, COMBO_END}; */
/* const uint16_t PROGMEM iron_K[] = {IR_SFT, KC_S, KC_N, COMBO_END}; */
/* const uint16_t PROGMEM iron_L[] = {IR_SFT, KC_N, KC_E, COMBO_END}; */
/* const uint16_t PROGMEM iron_M[] = {IR_SFT,  KC_R, KC_E, COMBO_END}; */
/* const uint16_t PROGMEM iron_N[] = {IR_SFT, KC_N, COMBO_END}; */
/* const uint16_t PROGMEM iron_O[] = {IR_SFT, KC_O, COMBO_END}; */
/* const uint16_t PROGMEM iron_P[] = {IR_SFT, KC_I, KC_T, COMBO_END}; */
/* const uint16_t PROGMEM iron_R[] = {IR_SFT, KC_R, COMBO_END}; */
/* const uint16_t PROGMEM iron_Q[] = {IR_SFT, KC_I, KC_O, COMBO_END}; */
/* const uint16_t PROGMEM iron_S[] = {IR_SFT, KC_S, COMBO_END}; */
/* const uint16_t PROGMEM iron_T[] = {IR_SFT, KC_T, COMBO_END}; */
/* const uint16_t PROGMEM iron_U[] = {IR_SFT, KC_T, KC_N, COMBO_END}; */
/* const uint16_t PROGMEM iron_V[] = {IR_SFT, KC_T, KC_A, COMBO_END}; */
/* const uint16_t PROGMEM iron_W[] = {IR_SFT, KC_T, KC_E, COMBO_END}; */
/* const uint16_t PROGMEM iron_X[] = {IR_SFT, KC_S, KC_A, COMBO_END}; */
/* const uint16_t PROGMEM iron_Y[] = {IR_SFT, KC_N, KC_O, COMBO_END}; */
/* const uint16_t PROGMEM iron_Z[] = {IR_SFT, KC_S, KC_E, COMBO_END}; */
/* const uint16_t PROGMEM iron_ctl[] = {KC_I, KC_S, KC_R, COMBO_END}; */
/* const uint16_t PROGMEM iron_alt[] = {KC_E, KC_A, KC_O, COMBO_END}; */
/* const uint16_t PROGMEM iron_com[] = {KC_T, KC_O, COMBO_END}; */
/* const uint16_t PROGMEM iron_dot[] = {KC_I, KC_N, COMBO_END}; */
/* const uint16_t PROGMEM iron_ent[] = {KC_S, KC_R, KC_T, COMBO_END}; */
/* const uint16_t PROGMEM iron_bkspc[] = {KC_N, KC_E, KC_A, COMBO_END}; */

/* combo_t key_combos[COMBO_COUNT] = { */
/*   COMBO(default_layer_combo, CL_CLEAR_LAYERS), */
/*   COMBO(num_layer_combo, TO(_NUM)), */
/*   COMBO(mouse_layer_combo, TO(_MOUSE)), */
/*   COMBO(nav_layer_combo, TO(_NAV)), */
/*   COMBO(caps_word_combo, QK_CAPS_WORD_TOGGLE), */
/*   COMBO(num_layer_q_combo, TO(_NUM)), */
/*   COMBO(nav_layer_q_combo, TO(_NAV)), */
/*   COMBO(caps_word_q_combo, QK_CAPS_WORD_TOGGLE), */
/*   COMBO(iron_b, KC_B), */
/*   COMBO(iron_c, KC_C), */
/*   COMBO(iron_d, KC_D), */
/*   COMBO(iron_f, KC_F), */
/*   COMBO(iron_g, KC_G), */
/*   COMBO(iron_h, KC_H), */
/*   COMBO(iron_j, KC_J), */
/*   COMBO(iron_k, KC_K), */
/*   COMBO(iron_l, KC_L), */
/*   COMBO(iron_m, KC_M), */
/*   COMBO(iron_p, KC_P), */
/*   COMBO(iron_q, KC_Q), */
/*   COMBO(iron_u, KC_U), */
/*   COMBO(iron_v, KC_V), */
/*   COMBO(iron_w, KC_W), */
/*   COMBO(iron_x, KC_X), */
/*   COMBO(iron_y, KC_Y), */
/*   COMBO(iron_z, KC_Z), */
/*   COMBO(iron_A, LSFT(KC_A)), */
/*   COMBO(iron_B, LSFT(KC_B)), */
/*   COMBO(iron_C, LSFT(KC_C)), */
/*   COMBO(iron_D, LSFT(KC_D)), */
/*   COMBO(iron_E, LSFT(KC_E)), */
/*   COMBO(iron_F, LSFT(KC_F)), */
/*   COMBO(iron_G, LSFT(KC_G)), */
/*   COMBO(iron_H, LSFT(KC_H)), */
/*   COMBO(iron_I, LSFT(KC_I)), */
/*   COMBO(iron_J, LSFT(KC_J)), */
/*   COMBO(iron_K, LSFT(KC_K)), */
/*   COMBO(iron_L, LSFT(KC_L)), */
/*   COMBO(iron_M, LSFT(KC_M)), */
/*   COMBO(iron_N, LSFT(KC_N)), */
/*   COMBO(iron_O, LSFT(KC_O)), */
/*   COMBO(iron_P, LSFT(KC_P)), */
/*   COMBO(iron_Q, LSFT(KC_Q)), */
/*   COMBO(iron_R, LSFT(KC_R)), */
/*   COMBO(iron_S, LSFT(KC_S)), */
/*   COMBO(iron_T, LSFT(KC_T)), */
/*   COMBO(iron_U, LSFT(KC_U)), */
/*   COMBO(iron_V, LSFT(KC_V)), */
/*   COMBO(iron_W, LSFT(KC_W)), */
/*   COMBO(iron_X, LSFT(KC_X)), */
/*   COMBO(iron_Y, LSFT(KC_Y)), */
/*   COMBO(iron_Z, LSFT(KC_Z)), */
/*   COMBO(iron_ctl, OSM(MOD_LCTL)), */
/*   COMBO(iron_alt, OSM(MOD_LALT)), */
/*   COMBO(iron_com, KC_COMM), */
/*   COMBO(iron_dot, KC_DOT), */
/*   COMBO(iron_ent, KC_ENT), */
/*   COMBO(iron_bkspc, KC_BSPC), */
/* }; */

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_ISRT] = LAYOUT(
                   UK_Y, LT(_DEBUG, UK_C), LT(_NAV, UK_L), LT(_NUM, UK_M), UK_K, UK_Z, LT(_NUM, UK_F), LT(_NAV, UK_U), LT(_DEBUG, UK_COMM), UK_QUOT,
                   UK_I, UK_S, UK_R, UK_T, UK_G, UK_P, UK_N, UK_E, UK_A, UK_O,
                   UK_Q, MT(MOD_LALT, UK_V), MT(MOD_LCTL, UK_W), MT(MOD_LSFT, UK_D), MT(MOD_RALT, UK_J), MT(MOD_RALT, UK_B), MT(MOD_RSFT, UK_H), MT(MOD_RCTL, UK_SLSH), MT(MOD_LALT, UK_DOT), UK_X,
                   CL_CPI_DECREASE, CL_CPI_RESET, CL_CPI_INCREASE, KC_NO, KC_NO, KC_NO,
                   KC_BSPC, LT(_MOUSE, KC_SPC), QK_GRAVE_ESCAPE, KC_NO, OSM(MOD_LGUI), OSM(MOD_LSFT), LT(_MOUSE, KC_TAB), KC_ENT
                   ),
  [_QWERTY] = LAYOUT(
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
