#include QMK_KEYBOARD_H
#include <keymap_uk.h>
#include <math.h>
#include "features/repeat_key.h"

enum custom_keycodes {
  CL_CPI_INCREASE = SAFE_RANGE,
  CL_CPI_DECREASE,
  CL_CPI_RESET,
  CL_CLEAR_LAYERS,
  CL_REPEAT,
  CL_MOD_LOCK,
};

enum custom_layers {
  _ISRT,
  _NUM,
  _NAV,
  _MOUSE,
  _SYM,
  _a1,
  _a2,
  _A2,
  _num,
  _fn,
  _sym1,
  _sym2,
  _sys
};

#include "g/keymap_combo.h"

static const char * const custom_layer_names[] = {
  [_ISRT] = "ISRT",
  [_NUM] = "Num",
  [_NAV] = "Nav",
  [_MOUSE] = "Mouse",
  [_SYM] = "Sym",
  [_a1] = "18 a1",
  [_a2] = "18 a2",
  [_A2] = "18 A2",
  [_num] = "18 num",
  [_fn] = "18 fn",
  [_sym1] = "18 sym1",
  [_sym2] = "18 sym2",
  [_sys] = "18 sys"
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

int pointing_speed = 1600;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (!process_repeat_key(keycode, record, CL_REPEAT)) { return false; }
  switch (keycode) {
  case CL_CPI_DECREASE:
    if (record->event.pressed) {
      if (pointing_speed > 800) {
        pointing_speed -= 800;
        pointing_device_set_cpi_on_side(true, pointing_speed);
      }
    }
    return false;
  case CL_CPI_INCREASE:
    if (record->event.pressed) {
      if (pointing_speed < 12800) {
        pointing_speed += 800;
        pointing_device_set_cpi_on_side(true, pointing_speed);
      }
    }
    return false;
  case CL_CPI_RESET:
    if (record->event.pressed) {
      pointing_speed = 1600;
      pointing_device_set_cpi_on_side(true, pointing_speed);
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

void keyboard_post_init_user(void) {
    pointing_device_set_cpi_on_side(true, pointing_speed);
    pointing_device_set_cpi_on_side(false, 1000);
}

report_mouse_t pointing_device_task_combined_user(report_mouse_t left_report, report_mouse_t right_report) {
    right_report.h = right_report.x * 0.2;
    right_report.v = right_report.y * 0.2;
    right_report.x = 0;
    right_report.y = 0;

    float magnitude = sqrtf( left_report.x * left_report.x + left_report.y * left_report.y ) * 0.8;
    //float adjusted_magnitude = powf(magnitude, 1.2f);
    if (left_report.x > 0 ) {
      left_report.x = MAX((int16_t)(left_report.x * magnitude), left_report.x);
    } else {
      left_report.x = MIN((int16_t)(left_report.x * magnitude), left_report.x);
    }

    if (left_report.y > 0) {
      left_report.y = MAX((int16_t)(left_report.y * magnitude), left_report.y);
    } else {
      left_report.y = MIN((int16_t)(left_report.y * magnitude), left_report.y);
    }

    return pointing_device_combine_reports(left_report, right_report);
}

layer_state_t layer_state_set_user(layer_state_t state) {
    switch (get_highest_layer(state)) {
    case _A2:
      set_oneshot_mods(MOD_BIT(KC_LSFT));
        break;
    }
  return state;
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_ISRT] = LAYOUT(
                   UK_Y, UK_C, UK_L, UK_M, UK_K, UK_Z,  UK_F, UK_U, UK_COMM, UK_QUOT,
                   UK_I, UK_S, UK_R, UK_T, UK_G, UK_P, UK_N, UK_E, UK_A, UK_O,
                   UK_Q, UK_V, UK_W, UK_D, UK_J, UK_B, UK_H, UK_SLSH, UK_DOT, UK_X,
                   CL_CPI_DECREASE, CL_CPI_RESET, CL_CPI_INCREASE, KC_VOLD, KC_MUTE, KC_VOLU,
                   CL_REPEAT, KC_SPC, OSM(MOD_LCTL), KC_LGUI, KC_APP, OSM(MOD_LALT), OSM(MOD_LSFT), MO(_MOUSE)
                   ),
  [_NUM] = LAYOUT(
                  XXXXXXX, KC_F9, KC_F8, KC_F9, KC_F10, UK_PLUS, UK_7, UK_8, UK_9, UK_SLSH,
                  XXXXXXX, KC_F6, KC_F5, KC_F4, KC_F11, UK_EQL, UK_4, UK_5, UK_6, UK_0,
                  XXXXXXX, KC_F3, KC_F2, KC_F1, KC_F12, UK_MINS, UK_1, UK_2, UK_3, UK_ASTR,
                  _______, _______, _______, _______, _______, _______,
                  _______, _______, _______, _______, _______, _______, _______, _______
                  ),
  [_SYM] = LAYOUT(
                  UK_GRV, UK_SCLN, UK_LCBR, UK_RCBR, UK_COLN, UK_PLUS, KC_AMPR, XXXXXXX, XXXXXXX, UK_SLSH,
                  UK_TILD, UK_BSLS, UK_LPRN, UK_RPRN, UK_UNDS, UK_EQL, KC_DLR, KC_PERC, KC_CIRC, XXXXXXX,
                  UK_NOT, UK_PIPE, UK_LBRC, UK_RBRC, UK_HASH, UK_MINS, KC_EXLM, UK_DQUO, UK_PND, UK_ASTR,
                  _______, _______, _______, _______, _______, _______,
                  _______, _______, _______, _______, _______, _______, _______, _______
                  ),
  [_NAV] = LAYOUT(
                  KC_NO, KC_NO, KC_UP, KC_HOME, KC_NO, KC_NO, KC_PGUP, KC_NO, KC_NO, KC_NO,
                  KC_NO, KC_LEFT, KC_DOWN, KC_RGHT, KC_TAB, KC_NO, KC_LEFT, KC_UP, KC_DOWN, KC_RGHT,
                  KC_NO, KC_NO, KC_NO, KC_END, _______, _______, KC_PGDN, KC_NO, KC_NO, KC_NO,
                  _______, _______, _______, _______, _______, _______,
                  _______, _______, _______, _______, _______, _______, _______, _______
                  ),
  [_MOUSE] = LAYOUT(
                    KC_NO, KC_NO, KC_WH_U, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
                    KC_NO, KC_WH_L, KC_WH_D, KC_WH_R, KC_NO, KC_BTN5, KC_BTN1, KC_BTN2, KC_BTN3, KC_BTN4,
                    KC_NO,  KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_MS_U, KC_MS_L, KC_MS_R, KC_MS_D,
                    _______, _______, _______, _______, _______, _______,
                    _______, _______, _______, _______, _______, _______, _______, _______
                    ),
  [_a1] = LAYOUT(
                   XXXXXXX, GUI_T(UK_L), ALT_T(UK_L), CTL_T(UK_G), XXXXXXX, XXXXXXX, CTL_T(UK_H), ALT_T(UK_U), GUI_T(UK_O), XXXXXXX,
                   LT(_num, UK_I), LT(_sym2, UK_S), LT(_sym1, UK_R), LT(_sys, UK_T), XXXXXXX, XXXXXXX, LT(_sys, UK_N), LT(_sym1, UK_E), LT(_sym2, UK_A), LT(_fn, UK_C),
                   LT(_num, UK_I), XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, LT(_fn, UK_C),
                   CL_CPI_DECREASE, CL_CPI_RESET, CL_CPI_INCREASE, KC_VOLD, KC_MUTE, KC_VOLU,
                   CL_REPEAT, MEH_T(KC_SPC), XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, OSL(_a2), OSL(_A2)
                   ),
  [_a2] = LAYOUT(
                 XXXXXXX, GUI_T(UK_V), ALT_T(UK_W), CTL_T(UK_M), XXXXXXX, XXXXXXX, CTL_T(UK_F), ALT_T(UK_QUOT), GUI_T(UK_Z), XXXXXXX,
                   UK_Q, UK_J, UK_P, UK_K, XXXXXXX, XXXXXXX, UK_B, UK_DOT, UK_X, UK_Y,
                   LT(_num, UK_Q), XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, UK_Y,
                   _______, _______, _______, _______, _______, _______,
                   _______, OSM(MOD_LSFT),  _______, _______, _______, _______, _______, _______
                 ),
  [_A2] = LAYOUT(
                 XXXXXXX, GUI_T(UK_V), ALT_T(UK_W), CTL_T(UK_M), XXXXXXX, XXXXXXX, CTL_T(UK_F), ALT_T(UK_QUOT), GUI_T(UK_Z), XXXXXXX,
                   UK_Q, UK_J, UK_P, UK_K, XXXXXXX, XXXXXXX, UK_B, UK_DOT, UK_X, UK_Y,
                   LT(_num, UK_Q), XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, UK_Y,
                   _______, _______, _______, _______, _______, _______,
                   _______, OSM(MOD_LSFT),  _______, _______, _______, _______, _______, _______
                   )
};
