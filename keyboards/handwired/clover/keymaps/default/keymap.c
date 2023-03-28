#include QMK_KEYBOARD_H

enum custom_layers {
  _ISRT,
  _NUM,
  _NAV,
};

static const char * const custom_layer_names[] = {
	[_ISRT] = "ISRT",
	[_NUM] = "Num",
	[_NAV] = "Nav",
};

#ifdef OLED_ENABLE
static void render_logo(void) {
    return;
    static const char PROGMEM qmk_logo[] = {
        0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8A, 0x8B, 0x8C, 0x8D, 0x8E, 0x8F, 0x90, 0x91, 0x92, 0x93, 0x94,
        0xA0, 0xA1, 0xA2, 0xA3, 0xA4, 0xA5, 0xA6, 0xA7, 0xA8, 0xA9, 0xAA, 0xAB, 0xAC, 0xAD, 0xAE, 0xAF, 0xB0, 0xB1, 0xB2, 0xB3, 0xB4,
        0xC0, 0xC1, 0xC2, 0xC3, 0xC4, 0xC5, 0xC6, 0xC7, 0xC8, 0xC9, 0xCA, 0xCB, 0xCC, 0xCD, 0xCE, 0xCF, 0xD0, 0xD1, 0xD2, 0xD3, 0xD4, 0x00
    };

    oled_write_P(qmk_logo, false);
}

bool oled_task_user(void) {
    if (is_keyboard_master()) {
      // Host Keyboard Layer Status
      oled_write_P(PSTR("Layer: "), false);
      oled_write_P(PSTR(custom_layer_names[get_highest_layer(layer_state)]), false);
      oled_write_P(PSTR("\n"), false);
    } else {
      render_logo();
    }
    
    return false;
}
#endif

void pointing_device_init_user(void) {
  // set_auto_mouse_enable(true);         // always required before the auto mouse feature will work
}

typedef struct {
    uint16_t tap;
    uint16_t hold;
    uint16_t held;
} tap_dance_tap_hold_t;

enum {
  CT_Y,
  CT_C,
    CT_L,
    CT_M,
    CT_K,
    CT_Z,
    CT_F,
    CT_U,
    CT_COMM,
    CT_QUOT,
    CT_I,
    CT_S,
    CT_R,
    CT_T,
    CT_G,
    CT_P,
    CT_N,
    CT_E,
    CT_A,
    CT_O,
    CT_Q,
    CT_V,
    CT_W,
    CT_D,
    CT_J,
    CT_B,
    CT_H,
    CT_SLSH,
    CT_DOT,
    CT_X,
    CT_TAB,
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    tap_dance_action_t *action;

    switch (keycode) {
    case TD(CT_Y):  // list all tap dance keycodes with tap-hold configurations
    case TD(CT_C):
    case TD(CT_L):
    case TD(CT_M):
    case TD(CT_K):
    case TD(CT_Z):
    case TD(CT_F):
    case TD(CT_U):
    case TD(CT_COMM):
    case TD(CT_QUOT):
    case TD(CT_I):
    case TD(CT_S):
    case TD(CT_R):
    case TD(CT_T):
    case TD(CT_G):
    case TD(CT_P):
    case TD(CT_N):
    case TD(CT_E):
    case TD(CT_A):
    case TD(CT_O):
    case TD(CT_Q):
    case TD(CT_V):
    case TD(CT_W):
    case TD(CT_D):
    case TD(CT_J):
    case TD(CT_B):
    case TD(CT_H):
    case TD(CT_SLSH):
    case TD(CT_DOT):
    case TD(CT_X):
    case TD(CT_TAB):
            action = &tap_dance_actions[TD_INDEX(keycode)];
            if (!record->event.pressed && action->state.count && !action->state.finished) {
                tap_dance_tap_hold_t *tap_hold = (tap_dance_tap_hold_t *)action->user_data;
                tap_code16(tap_hold->tap);
            }
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

tap_dance_action_t tap_dance_actions[] = {
    [CT_Y] = ACTION_TAP_DANCE_TAP_HOLD(KC_Y, KC_EXLM),
    [CT_C] = ACTION_TAP_DANCE_TAP_HOLD(KC_C, KC_AT),
    [CT_L] = ACTION_TAP_DANCE_TAP_HOLD(KC_L, KC_HASH),
    [CT_M] = ACTION_TAP_DANCE_TAP_HOLD(KC_M, KC_DLR),
    [CT_K] = ACTION_TAP_DANCE_TAP_HOLD(KC_K, KC_PERC),
    
    [CT_Z] = ACTION_TAP_DANCE_TAP_HOLD(KC_Z, KC_CIRC),
    [CT_F] = ACTION_TAP_DANCE_TAP_HOLD(KC_F, KC_AMPR),
    [CT_U] = ACTION_TAP_DANCE_TAP_HOLD(KC_U, KC_ASTR),
    [CT_COMM] = ACTION_TAP_DANCE_TAP_HOLD(KC_COMM, KC_UNDS),
    [CT_QUOT] = ACTION_TAP_DANCE_TAP_HOLD(KC_QUOT, KC_PLUS),

    [CT_I] = ACTION_TAP_DANCE_TAP_HOLD(KC_I, KC_LT),
    [CT_S] = ACTION_TAP_DANCE_TAP_HOLD(KC_S, KC_LBRC),
    [CT_R] = ACTION_TAP_DANCE_TAP_HOLD(KC_R, KC_LCBR),
    [CT_T] = ACTION_TAP_DANCE_TAP_HOLD(KC_T, KC_LPRN),
    [CT_G] = ACTION_TAP_DANCE_TAP_HOLD(KC_G, KC_SCLN),

    [CT_P] = ACTION_TAP_DANCE_TAP_HOLD(KC_P, KC_COLN),
    [CT_N] = ACTION_TAP_DANCE_TAP_HOLD(KC_N, KC_RPRN),
    [CT_E] = ACTION_TAP_DANCE_TAP_HOLD(KC_E, KC_RCBR),
    [CT_A] = ACTION_TAP_DANCE_TAP_HOLD(KC_A, KC_RBRC),
    [CT_O] = ACTION_TAP_DANCE_TAP_HOLD(KC_O, KC_GT),

    [CT_Q] = ACTION_TAP_DANCE_TAP_HOLD(KC_Q, KC_X),
    [CT_V] = ACTION_TAP_DANCE_TAP_HOLD(KC_V, KC_X),
    [CT_W] = ACTION_TAP_DANCE_TAP_HOLD(KC_W, KC_PIPE),
    [CT_D] = ACTION_TAP_DANCE_TAP_HOLD(KC_D, KC_NUHS),
    [CT_J] = ACTION_TAP_DANCE_TAP_HOLD(KC_J, KC_X),

    [CT_B] = ACTION_TAP_DANCE_TAP_HOLD(KC_B, KC_X),
    [CT_H] = ACTION_TAP_DANCE_TAP_HOLD(KC_H, KC_NUBS),
    [CT_SLSH] = ACTION_TAP_DANCE_TAP_HOLD(KC_SLSH, KC_QUES),
    [CT_DOT] = ACTION_TAP_DANCE_TAP_HOLD(KC_DOT, KC_X),
    [CT_X] = ACTION_TAP_DANCE_TAP_HOLD(KC_X, KC_X),

    [CT_TAB] = ACTION_TAP_DANCE_TAP_HOLD(KC_X, QK_CAPS_WORD_TOGGLE),
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_ISRT] = LAYOUT(
      TD(CT_Y),        TD(CT_C),        TD(CT_L),        TD(CT_M),        TD(CT_K),
      TD(CT_Z),        TD(CT_F),        TD(CT_U),        TD(CT_COMM),     TD(CT_QUOT),
      
      TD(CT_I),        TD(CT_S),        TD(CT_R),        TD(CT_T),        TD(CT_G),
      TD(CT_P),        TD(CT_N),        TD(CT_E),        TD(CT_A),        TD(CT_O),
      
      TD(CT_Q),        TD(CT_V),        TD(CT_W),        TD(CT_D),        TD(CT_J),
      TD(CT_B),        TD(CT_H),        TD(CT_SLSH),     TD(CT_DOT),      TD(CT_X),

      KC_WH_U,         KC_WH_D,         TD(CT_TAB),
      KC_MS_BTN1,      KC_MS_BTN2,      KC_MS_BTN3,
      
      KC_BSPC,         KC_SPC,          OSM(MOD_LSFT),   OSM(MOD_LALT),
      OSM(MOD_LGUI),   OSM(MOD_LCTL),   OSL(1),          KC_ENT
                   ),
  [_NUM] = LAYOUT(
      KC_NO,           KC_PDOT,         KC_PSLS,         KC_PMNS,         KC_F12,
      KC_F12,          KC_PPLS,         KC_PAST,         KC_PEQL,         KC_NO,
      
      KC_9,            KC_7,            KC_5,            KC_3,            KC_1,
      KC_0,            KC_2,            KC_4,            KC_6,            KC_8,
      
      KC_F9,           KC_F7,           KC_F5,           KC_F3,           KC_F1,
      KC_F10,          KC_F2,           KC_F4,           KC_F6,           KC_F8,

      KC_TRNS,         KC_TRNS,         KC_TRNS,
      KC_TRNS,         KC_TRNS,         KC_TRNS,
      
      KC_TRNS,         KC_TRNS,         KC_TRNS,         KC_TRNS,
      KC_TRNS,         KC_TRNS,         OSL(2),          KC_TRNS
                  ),
  [_NAV] = LAYOUT(
      KC_NO,           KC_NO,           KC_UP,           KC_HOME,         KC_NO,
      KC_NO,           KC_PGUP,         KC_NO,           KC_NO,           KC_NO,
      
      KC_NO,           KC_LEFT,         KC_DOWN,         KC_RGHT,         KC_TAB,
      KC_NO,           KC_LEFT,         KC_UP,           KC_DOWN,         KC_RGHT,
      
      KC_NO,           KC_NO,           KC_NO,           KC_END,          KC_TRNS,
      KC_TRNS,         KC_PGDN,         KC_NO,           KC_NO,           KC_NO,
      
      KC_TRNS,         KC_TRNS,         KC_TRNS,
      KC_TRNS,         KC_TRNS,         KC_TRNS,

      KC_TRNS,         KC_TRNS,         KC_TRNS,         KC_TRNS,
      KC_TRNS,         KC_TRNS,         KC_TRNS,         KC_TRNS
                  ),
};
