#include QMK_KEYBOARD_H
#include <keymap_uk.h>
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
  _ISRT_PLAIN,
  _NUM,
  _NAV,
  _MOUSE,
  _DEBUG,
};

#include "g/keymap_combo.h"

typedef struct {
    uint16_t tap;
    uint16_t hold;
    uint16_t held;
} tap_dance_tap_hold_t;

enum {
    TD_SPACE_MODLOCK,
    TD_SHIFT_MOUSE,
};

static const char * const custom_layer_names[] = {
  [_ISRT] = "ISRT",
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
  if (!process_repeat_key(keycode, record, CL_REPEAT)) { return false; }
  tap_dance_action_t *action;

  switch (keycode) {
  case TD(TD_SPACE_MODLOCK):
    action = &tap_dance_actions[TD_INDEX(keycode)];
    if (!record->event.pressed && action->state.count && !action->state.finished) {
      tap_dance_tap_hold_t *tap_hold = (tap_dance_tap_hold_t *)action->user_data;
      tap_code16(tap_hold->tap);
    }
    break;
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

void tap_dance_tap_hold_finished(tap_dance_state_t *state, void *user_data) {
    tap_dance_tap_hold_t *tap_hold = (tap_dance_tap_hold_t *)user_data;

    if (state->pressed) {
        if (state->count == 1
#ifndef PERMISSIVE_HOLD
            && !state->interrupted
#endif
        ) {
            register_code16(tap_hold->hold);
            tap_hold->held = tap_hold->hold;
        } else {
            register_code16(tap_hold->tap);
            tap_hold->held = tap_hold->tap;
        }
    }
}

void tap_dance_tap_hold_reset(tap_dance_state_t *state, void *user_data) {
    tap_dance_tap_hold_t *tap_hold = (tap_dance_tap_hold_t *)user_data;

    if (tap_hold->held) {
        unregister_code16(tap_hold->held);
        tap_hold->held = 0;
    }
}

#define ACTION_TAP_DANCE_TAP_HOLD(tap, hold) \
    { .fn = {NULL, tap_dance_tap_hold_finished, tap_dance_tap_hold_reset}, .user_data = (void *)&((tap_dance_tap_hold_t){tap, hold, 0}), }


// Define a type containing as many tapdance states as you need
typedef enum {
    TD_NONE,
    TD_UNKNOWN,
    TD_SINGLE_TAP,
    TD_SINGLE_HOLD,
    TD_DOUBLE_TAP,
    TD_DOUBLE_HOLD,
} td_state_t;

static td_state_t td_state;

// Determine the tapdance state to return
td_state_t cur_dance(tap_dance_state_t *state) {
    if (state->count == 1) {
        if (state->interrupted || !state->pressed) return TD_SINGLE_TAP;
        else return TD_SINGLE_HOLD;
    } else if (state->count == 2) {
        if (state->interrupted || !state->pressed) return TD_DOUBLE_TAP;
        else return TD_DOUBLE_HOLD;
    }
    else return TD_UNKNOWN; // Any number higher than the maximum state value you return above
}

// Handle the possible states for each tapdance keycode you define:
void shiftmouse_finished(tap_dance_state_t *state, void *user_data) {
    td_state = cur_dance(state);
    switch (td_state) {
    case TD_SINGLE_TAP:
      if(get_oneshot_mods() && MOD_BIT(KC_LSFT)) {
        clear_oneshot_mods();
      } else {
        set_oneshot_mods(MOD_BIT(KC_LSFT));
      }
      break;
    case TD_SINGLE_HOLD:
      layer_on(_MOUSE);
      break;
    case TD_DOUBLE_TAP:
      caps_word_toggle();
      break;
    case TD_DOUBLE_HOLD:
      register_mods(MOD_BIT(KC_LSFT));
      break;
    default:
      break;
    }
}

void shiftmouse_reset(tap_dance_state_t *state, void *user_data) {
    switch (td_state) {
    case TD_SINGLE_HOLD:
      layer_off(_MOUSE);
      break;
    case TD_DOUBLE_HOLD:
      unregister_mods(MOD_BIT(KC_LSFT));
    default:
      break;
    }
}

tap_dance_action_t tap_dance_actions[] = {
  [TD_SPACE_MODLOCK] = ACTION_TAP_DANCE_TAP_HOLD(KC_SPC, CL_MOD_LOCK),
  [TD_SHIFT_MOUSE] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, shiftmouse_finished, shiftmouse_reset),
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_ISRT] = LAYOUT(
                   UK_Y, LT(_DEBUG, UK_C), LT(_NAV, UK_L), LT(_NUM, UK_M), UK_K, UK_Z,  LT(_NUM, UK_F), LT(_NAV, UK_U), LT(_DEBUG, UK_COMM), UK_QUOT,
                   UK_I, UK_S, UK_R, UK_T, UK_G, UK_P, UK_N, UK_E, UK_A, UK_O,
                   UK_Q, UK_V, UK_W, UK_D, UK_J, UK_B, UK_H, UK_SLSH, UK_DOT, UK_X,
                   CL_CPI_DECREASE, CL_CPI_RESET, CL_CPI_INCREASE, KC_VOLD, KC_MUTE, KC_VOLU,
                   // KC_NO, KC_SPC, CL_MOD_LOCK, TD(TD_SPACE_MODLOCK), KC_NO, KC_NO, TD(TD_SHIFT_MOUSE), CL_REPEAT
                   CL_REPEAT, KC_SPC, OSM(MOD_LCTL), XXXXXXX, XXXXXXX, OSM(MOD_LALT), OSM(MOD_LSFT), MO(_MOUSE)
                   ),
  [_ISRT_PLAIN] = LAYOUT(
                   UK_Y, UK_C, UK_L, UK_M, UK_K, UK_Z, UK_F, UK_U, UK_COMM, UK_QUOT,
                   UK_I, UK_S, UK_R, UK_T, UK_G, UK_P, UK_N, UK_E, UK_A, UK_O,
                   UK_Q, UK_V, UK_W, UK_D, UK_J,  UK_B, UK_H, UK_SLSH, UK_DOT, UK_X,
                   CL_CPI_DECREASE, CL_CPI_RESET, CL_CPI_INCREASE, KC_VOLD, KC_MUTE, KC_VOLU,
                   KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8
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
                    KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
                    KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
                    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
                    )
};
