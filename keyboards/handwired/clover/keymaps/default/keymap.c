#include QMK_KEYBOARD_H
#include <keymap_uk.h>

enum custom_layers {
  _ISRT,
  _NUM,
  _NUMOLD,
  _NAV,
  _SYM,
  _MOUSE,
  _DEBUG,
};

static const char * const custom_layer_names[] = {
	[_ISRT] = "ISRT",
	[_NUM] = "Num",
  [_NUMOLD] = "NumOLD", 
	[_NAV] = "Nav",
  [_SYM] = "Sym",
  [_MOUSE] = "Mouse",
  [_DEBUG] = "Debug",
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
    } else {
      render_logo();
    }
    
    return false;
}
#endif

const uint16_t PROGMEM left_reset_combo[] = {KC_WH_U, KC_WH_D, KC_TAB, COMBO_END};
const uint16_t PROGMEM right_reset_combo[] = {KC_MS_BTN1, KC_MS_BTN2, KC_MS_BTN3, COMBO_END};

combo_t key_combos[COMBO_COUNT] = {
    COMBO(left_reset_combo, QK_BOOT),
    COMBO(right_reset_combo, QK_BOOT),
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_ISRT] = LAYOUT(
      UK_Y,            LT(_NAV, UK_C),  UK_L,  LT(_NUM, UK_M),  UK_K, UK_Z,            LT(_NUM, UK_F),  UK_U,  LT(_NAV, UK_COMM), UK_QUOT,
      UK_I,            UK_S,            UK_R,            UK_T,            UK_G,       UK_P,            UK_N,            UK_E,            UK_A,            UK_O, 
      UK_Q,            MT(MOD_LALT, UK_V),  MT(MOD_LCTL, UK_W),  MT(MOD_LSFT, UK_D),  MT(MOD_RALT, UK_J),      MT(MOD_RALT, UK_B),  MT(MOD_RSFT, UK_H),  MT(MOD_RCTL, UK_SLSH), MT(MOD_LALT, UK_DOT),  UK_X, 
      KC_NO,         KC_NO,         KC_NO,      KC_NO,      KC_NO,      KC_NO,
      KC_BSPC,         LT(_MOUSE, KC_SPC), KC_NO,        KC_NO,      OSM(MOD_LGUI),   KC_NO,           LT(_MOUSE, KC_TAB), KC_ENT
                   ),
  [_NUM2] = LAYOUT(
                   MT(MOD_LALT, UK_GRV), MT(MOD_LCTL, UK_SCLN), MT(MOD_LSFT, UK_COLN), UK_LCBR, UK_RCBR,                   UK_PLUS, UK_7, MT(MOD_RSFT, UK_8),  MT(MOD_RCTL, UK_9), MT(MOD_LALT, UK_SLSH),
                   UK_TILD, UK_BSLS, UK_UNDS, UK_LPRN, UK_RPRN,                   UK_EQL, UK_4, UK_5, UK_6, UK_0,                   UK_NOT, UK_PIPE, UK_HASH, UK_LBRC, UK_RBRC,                   UK_MINS, UK_1, UK_2, UK_3, UK_ASTR,
                   KC_TRNS, KC_TRNS, KC_TRNS,                   KC_TRNS, KC_TRNS, KC_TRNS,
                   KC_TRNS,         KC_TRNS,         KC_TRNS,         KC_TRNS,                   KC_TRNS,         KC_TRNS,         KC_TRNS,         KC_TRNS
                   ),
  [_NUM] = LAYOUT(
      KC_NO,           KC_PDOT,         KC_PSLS,         KC_PMNS,         KC_F12,      KC_F12,          KC_PPLS,         KC_PAST,         KC_PEQL,         KC_NO,
            KC_9,            KC_7,            KC_5,            KC_3,            KC_1,      KC_0,            KC_2,            KC_4,            KC_6,            KC_8,
            KC_F9,           MT(MOD_LALT, KC_F7), MT(MOD_LCTL, KC_F5), MT(MOD_LSFT, KC_F3), KC_F1,      KC_F10,          MT(MOD_RSFT, KC_F2), MT(MOD_RCTL, KC_F4), MT(MOD_LALT, KC_F6),  KC_F8,
      KC_TRNS,         KC_TRNS,         KC_TRNS,      KC_TRNS,         KC_TRNS,         KC_TRNS,
      KC_TRNS,         KC_TRNS,         KC_TRNS,         KC_TRNS,      KC_TRNS,         KC_TRNS,         KC_TRNS,         KC_TRNS
                  ),
  [_NAV] = LAYOUT(
      KC_NO,           KC_NO,           KC_UP,           KC_HOME,         KC_NO,      KC_NO,           KC_PGUP,         KC_NO,           KC_NO,           KC_NO,
      KC_NO,           KC_LEFT,         KC_DOWN,         KC_RGHT,         KC_TAB,      KC_NO,           KC_LEFT,         KC_UP,           KC_DOWN,         KC_RGHT,
      KC_NO,           KC_NO,           KC_NO,           KC_END,          KC_TRNS,      KC_TRNS,         KC_PGDN,         KC_NO,           KC_NO,           KC_NO,
      KC_TRNS,         KC_TRNS,         KC_TRNS,      KC_TRNS,         KC_TRNS,         KC_TRNS,
      KC_TRNS,         KC_TRNS,         KC_TRNS,         KC_TRNS,      KC_TRNS,         KC_TRNS,         KC_TRNS,         KC_TRNS
                  ),
  [_SYM] = LAYOUT(
      KC_EXLM,         KC_AT,           KC_HASH,         KC_DLR,          KC_PERC,      KC_CIRC,         KC_AMPR,         KC_ASTR,         KC_UNDS,         KC_PLUS,
      KC_LT,           KC_LBRC,         KC_LCBR,         KC_LPRN,         KC_SCLN,      KC_COLN,         KC_RPRN,         KC_RCBR,         KC_RBRC,         KC_GT,
      KC_NO,           MT(MOD_LALT, KC_NO), MT(MOD_LCTL, KC_PIPE), MT(MOD_LSFT, KC_SLSH), KC_NO,      KC_NO,           MT(MOD_RSFT, KC_NUBS), MT(MOD_RCTL, KC_QUES), MT(MOD_LALT, KC_NO), KC_NO,
      KC_TRNS,         KC_TRNS,         KC_TRNS,      KC_TRNS,         KC_TRNS,         KC_TRNS,
      KC_TRNS,         KC_TRNS,         KC_TRNS,         KC_TRNS,      KC_TRNS,         KC_TRNS,         KC_TRNS,         KC_TRNS
                  ),
  [_MOUSE] = LAYOUT(
      KC_NO,           KC_NO,           KC_WH_U,         KC_NO,           KC_NO,      KC_NO,           KC_NO,           KC_NO,           KC_NO,           KC_NO,
      KC_NO,           KC_WH_L,         KC_WH_D,         KC_WH_R,         KC_NO,      KC_BTN5,         KC_BTN1,         KC_BTN2,         KC_BTN3,         KC_BTN4,
      KC_NO,           KC_NO,           KC_NO,           KC_NO,           KC_NO,      KC_NO,           KC_MS_U,         KC_MS_L,         KC_MS_R,         KC_MS_D,
      KC_TRNS,         KC_TRNS,         KC_TRNS,      KC_TRNS,         KC_TRNS,         KC_TRNS,
      KC_TRNS,         KC_TRNS,         KC_TRNS,         KC_TRNS,      KC_TRNS,         KC_TRNS,         KC_TRNS,         KC_TRNS
                    ),
};
