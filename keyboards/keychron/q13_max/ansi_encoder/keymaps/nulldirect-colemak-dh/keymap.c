/* Copyright 2024 @ Keychron (https://www.keychron.com)
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include QMK_KEYBOARD_H
#include "keychron_common.h"
#include "config.h"
enum layers {
    BASE,
    EXTRA
};
/*enum custom_keycodes {
};*/
// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [BASE] = LAYOUT_ansi_107(
        KC_MUTE,      KC_ESC,   KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,     KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,   KC_F12,  KC_DEL,              KC_F13,  KC_F14,  KC_F15,  KC_F16,
        KC_F17,       KC_GRV,   KC_1,     KC_2,     KC_3,     KC_4,     KC_5,      KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_MINS,  KC_EQL,   KC_NO,            KC_NUM,  KC_PSLS, KC_PAST, KC_PMNS,
        KC_F18,       KC_TAB,   KC_Q,     KC_W,     KC_F,     KC_P,     KC_B,      KC_J,     KC_L,     KC_U,     KC_Y,     KC_SCLN,  KC_LBRC,  KC_RBRC,  KC_BSLS,            KC_P7,   KC_P8,   KC_P9,   KC_PPLS,
        KC_F19,       KC_LCTL,  KC_A,     KC_R,     KC_S,     KC_T,     KC_G,      KC_M,     KC_N,     KC_E,     KC_I,     KC_O,     KC_QUOT,            KC_ENT,             KC_P4,   KC_P5,   KC_P6,
        KC_F20,       KC_LSFT,            KC_X,     KC_C,     KC_D,     KC_V,      KC_Z,     KC_Z,     KC_K,     KC_H,     KC_COMM,  KC_DOT,   KC_SLSH,  KC_RSFT,  KC_UP,    KC_P1,   KC_P2,   KC_P3,   KC_PENT,
        KC_F21,       KC_LCTL,  KC_LGUI,           KC_LALT, KC_SPC,  MO(EXTRA),           KC_BSPC,             KC_RALT,           KC_RCTL,            KC_LEFT,  KC_DOWN,  KC_RGHT, KC_P0,   KC_PDOT        ),
    [EXTRA] = LAYOUT_ansi_107(
        _______,    QK_BOOT,  _______,  _______,  _______,  _______,  _______,   _______,  _______,  _______,  _______,  _______,  _______,   _______,  _______,            _______, _______, _______, _______,
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
// clang-format on
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (!process_record_keychron_common(keycode, record)) {
        return false;
    }
    return true;
}
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
