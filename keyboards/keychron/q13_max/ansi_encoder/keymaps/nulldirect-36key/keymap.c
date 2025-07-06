#include QMK_KEYBOARD_H
#include "keychron_common.h"
#include "config.h"
enum layers {
    BASE = 0,
    SYMBOL = 1,
    EXTRA = 2
};
// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [BASE] = LAYOUT_ansi_107(
        KC_MUTE,      KC_ESC,   KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,     KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,   KC_F12,  KC_DEL,              KC_F13,  KC_F14,  KC_F15,  KC_F16,
        KC_F17,       KC_GRV,   KC_1,     KC_2,     KC_3,     KC_4,     KC_5,      KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_MINS,  KC_EQL,   KC_NO,              KC_NUM,  KC_PSLS, KC_PAST, KC_PMNS,
        KC_F18,       KC_TAB,   KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,      KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_LBRC,  KC_RBRC,  KC_BSLS,            KC_P7,   KC_P8,   KC_P9,   KC_PPLS,
        KC_F19,       LCTL_T(KC_ESC),     KC_A,     KC_S,     KC_D,     KC_F,     KC_G,      KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,  KC_QUOT,  KC_ENT,             KC_P4,   KC_P5,   KC_P6,
        KC_F20,       KC_LSFT,            KC_Z,     KC_X,     KC_C,     KC_V,      KC_B,     KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,  MO(SYMBOL),KC_RSFT,  KC_UP,    KC_P1,   KC_P2,   KC_P3,   KC_PENT,
        KC_F21,       KC_LCTL,  KC_LGUI,           KC_LCTL, KC_BSPC,    KC_SPC,           KC_ENT,             KC_LSFT,           KC_LALT,            KC_LEFT,  KC_DOWN,  KC_RGHT, KC_P0,   KC_PDOT        ),
    [SYMBOL] = LAYOUT_ansi_107(
        _______,    _______,  _______,  _______,  _______,  _______,  _______,   _______,  _______,  _______,  _______,  _______,  _______,   _______,  _______,            _______, _______, _______, _______,
        _______,    _______,  _______,  _______,  _______,  _______,  _______,   _______,  _______,  _______,  _______,  _______,  _______,   _______,  _______,            _______, _______, _______, _______,
        _______,    _______,  _______,  KC_BSLS,  KC_1   ,  KC_2   ,  KC_3   ,   KC_MINS,  KC_EQL ,  _______,  KC_UP  ,  _______,  _______,   _______,  _______,            _______, _______, _______, _______,
        _______,    _______,  _______,  _______,  KC_4   ,  KC_5   ,  KC_6   ,   KC_LBRC,  KC_RBRC,  KC_LEFT,  KC_DOWN,  KC_RIGHT,  _______,             _______,            _______, _______, _______,
        _______,    _______,            _______,  KC_7   ,  KC_8   ,  KC_9   ,   KC_QUOT,  _______,  KC_SLSH,  MO(EXTRA),_______,  _______,  _______,   _______,  _______,  _______,  _______, _______, _______,
        _______,    _______,  _______,            _______,  _______,  _______,             _______,            _______,            _______,             _______,  _______,  _______, _______, _______        ),
    [EXTRA] = LAYOUT_ansi_107(
        EE_CLR,     QK_BOOT,  _______,  _______,  _______,  _______,  _______,   _______,  _______,  _______,  _______,  _______,  _______,   _______,  _______,            _______, _______, _______, _______,
        _______,    _______,  BT_HST1,  BT_HST2,  BT_HST3,  P2P4G,    _______,   _______,  _______,  _______,  _______,  _______,  _______,   _______,  _______,            _______, _______, _______, _______,
        _______,    _______,  _______,  _______,  _______,  _______,  _______,   _______,  _______,  _______,  _______,  _______,  _______,   _______,  _______,            _______, _______, _______, _______,
        _______,    _______,  _______,  _______,  _______,  _______,  _______,   _______,  _______,  _______,  _______,  _______,  _______,             _______,            _______, _______, _______,
        _______,    _______,            _______,  _______,  _______,  _______,   BAT_LVL,  _______,  NK_TOGG,  _______,  _______,  _______,   _______,  _______,  _______,  _______, _______, _______, _______,
        _______,    _______,  _______,            _______,  _______,  _______,             _______,            _______,            _______,             _______,  _______,  _______, _______, _______        ),
};

#if defined(ENCODER_MAP_ENABLE)

const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][2] = {
    [BASE] = {ENCODER_CCW_CW(KC_VOLD, KC_VOLU)},
    [EXTRA] = {ENCODER_CCW_CW(RGB_VAD, RGB_VAI)}
};
#endif // ENCODER_MAP_ENABLE
bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
	if (get_highest_layer(layer_state) > 0) {
		uint8_t layer = get_highest_layer(layer_state);
		for (uint8_t row = 0; row < MATRIX_ROWS; ++row) {
		    for (uint8_t col = 0; col < MATRIX_COLS; ++col) {
			uint8_t index = g_led_config.matrix_co[row][col];

			if (index >= led_min && index < led_max && index != NO_LED &&
			keymap_key_to_keycode(layer, (keypos_t){col,row}) > KC_TRNS) {
			    rgb_matrix_set_color(index, RGB_RED);
			}
		    }
		}
	}
	return false;
}
