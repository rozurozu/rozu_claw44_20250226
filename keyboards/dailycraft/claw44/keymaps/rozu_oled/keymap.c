/*
Copyright 2012 Jun Wako <wakojun@gmail.com>
Copyright 2015 Jack Humbert
This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.
This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.
You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include QMK_KEYBOARD_H
#include <stdio.h>
#include <print.h>
#include "os_detection.h"

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.

enum layer_number {
    _QWERTY = 0,
    _RAISE,
    _LOWER,
    _OMG,
    _GAME1,
    _GAME2,
    _MAC0,
    _MAC1,
    _MAC2,
    _MAC3,
};

#define KC_L_SPC LT(_LOWER, KC_SPC)  // lower
#define KC_R_ENT LT(_RAISE, KC_ENT)  // raise
#define KC_1_ENT LT(_MAC1, KC_ENT)  // raise
#define KC_2_SPC LT(_MAC2, KC_SPC)  // lower
#define KC_G_JA LGUI_T(KC_LNG1)      // cmd or win
#define KC_A_EN ALT_T(KC_LNG2)      // cmd or win
#define KC_A_DEL ALT_T(KC_DEL)       // alt
#define KC_C_JA LCTL_T(KC_LNG1)      // ctrl
#define KC_C_BS LCTL_T(KC_BSPC)      // ctrl
#define KC_ KC_TRNS
#define KC_RST RESET
#define KC_GAME2 LT(_GAME2, KC_DEL)
#define KC_OMG LT(_OMG, KC_0)

// OSの状態を保存する変数
static os_variant_t current_os_variant = OS_UNSURE;

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_QWERTY] = LAYOUT(
  //,--------+--------+---------+--------+---------+--------.   ,--------+---------+--------+---------+--------+--------.
     KC_ESC , KC_Q   , KC_W    , KC_E   , KC_R    , KC_T   ,     KC_Y   , KC_U    , KC_I   , KC_O    , KC_P   , KC_MINS,
  //|--------+--------+---------+--------+---------+--------|   |--------+---------+--------+---------+--------+--------|
     KC_TAB , KC_A   , KC_S    , KC_D   , KC_F    , KC_G   ,     KC_H   , KC_J    , KC_K   , KC_L    , KC_SCLN, KC_QUOT,
  //|--------+--------+---------+--------+---------+--------|   |--------+---------+--------+---------+--------+--------|
     KC_LSFT, KC_Z   , KC_X    , KC_C   , KC_V    , KC_B   ,     KC_N   , KC_M    , KC_COMM, KC_DOT  , KC_SLSH, KC_RSFT,
  //`--------+--------+---------+--------+---------+--------/   \--------+---------+--------+---------+--------+--------'
                       KC_A_DEL, KC_A_EN, KC_L_SPC, KC_C_JA,     KC_C_BS, KC_R_ENT, KC_RGUI, KC_A_DEL
  //                 `----------+--------+---------+--------'   `--------+---------+--------+---------'
  ),

    [_RAISE] = LAYOUT(
  //,--------+--------+--------+--------+--------+--------.   ,--------+--------+--------+--------+--------+--------.
     KC_TRNS, KC_EXLM, KC_DQUO, KC_HASH, KC_DLR , KC_PERC,   KC_AT,LCTL(KC_LEFT),LCTL(KC_UP),LCTL(KC_RIGHT), KC_TILD, KC_BSLS,
  //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------|
     KC_LPRN, KC_LBRC, KC_GRV , KC_AMPR ,KC_QUOT, KC_EQL,     KC_LEFT, KC_DOWN,  KC_UP , KC_RGHT, KC_RBRC , KC_RPRN,
  //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------|
     KC_LSFT, _______, _______, _______, KC_LCBR, KC_LBRC,     KC_MINS, KC_PPLS,  KC_LT,    KC_GT, _______, _______,
  //`--------+--------+--------+--------+--------+--------/   \--------+--------+--------+--------+--------+--------'
                       KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS,     KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
  //                  `--------+--------+--------+--------'   `--------+--------+--------+--------'
  ),

    [_LOWER] = LAYOUT(
  //,--------+--------+--------+--------+--------+--------.   ,--------+--------+--------+--------+--------+--------.
     KC_TRNS,  KC_PAST  , KC_7  , KC_8 ,   KC_9  , KC_PMNS,     KC_TRNS, _______, _______, _______, _______, KC_TRNS,
  //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------|
     KC_TRNS,  KC_PSLS  , KC_4   , KC_5   , KC_6  , KC_PPLS   , KC_PGUP, _______, _______, _______, _______, _______,
  //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------|
      KC_OMG ,  KC_0  ,   KC_1  , KC_2,    KC_3,   KC_BSPC,     KC_PGDN, LGUI(KC_LEFT), _______, LGUI(KC_RIGHT) , KC_SLSH, _______,
  //`--------+--------+--------+--------+--------+--------/   \--------+--------+--------+--------+--------+--------'
                       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,     KC_TRNS, TG(_GAME1), KC_TRNS, KC_TRNS
  //                  `--------+--------+--------+--------'   `--------+--------+--------+--------
  ),

    [_OMG] = LAYOUT(
    //,--------+--------+--------+--------+--------+--------.   ,--------+--------+--------+--------+--------+--------.
        KC_TRNS, KC_TRNS, KC_F7,   KC_F8,   KC_F9,   KC_F12,     KC_PGUP, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
    //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------|
        KC_TRNS, KC_TRNS, KC_F4,   KC_F5,   KC_F6,   KC_F11,     KC_PGDN, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
    //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------|
        KC_TRNS, KC_TRNS, KC_F1,   KC_F2,   KC_F3,   KC_F10,     KC_CAPS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
    //`--------+--------+--------+--------+--------+--------/   \--------+--------+--------+--------+--------+--------'
                         KC_TRNS, KC_TRNS, KC_TRNS , KC_TRNS,     KC_PSCR, KC_TRNS, KC_TRNS, KC_TRNS
    //                  `--------+--------+--------+--------'   `--------+--------+--------+--------'
    ),
    [_GAME1] = LAYOUT(
    //,--------+--------+--------+--------+--------+--------.   ,--------+--------+--------+--------+--------+--------.
        KC_ESC,  KC_P,    KC_Q,    KC_W,    KC_E,    KC_R,       KC_PGUP, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
    //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------|
        KC_TAB, KC_LSFT,   KC_A,    KC_S,    KC_D,    KC_F,     KC_PGDN, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
    //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------|
        KC_CAPS, KC_K,     KC_Z,    KC_X,    KC_C,    KC_V,     KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
    //`--------+--------+--------+--------+--------+--------/   \--------+--------+--------+--------+--------+--------'
                         KC_LCTL, KC_LALT, KC_SPC ,  KC_GAME2,   KC_TRNS, TG(_GAME1), KC_TRNS, KC_TRNS
    //                  `--------+--------+--------+--------'   `--------+--------+--------+--------'
    ),
    [_GAME2] = LAYOUT(
    //,--------+--------+--------+--------+--------+--------.   ,--------+--------+--------+--------+--------+--------.
        KC_DEL,   KC_O,    KC_7,    KC_8,    KC_9,    KC_T,       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
    //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------|
        KC_LALT, KC_I,     KC_4,    KC_5,    KC_6,    KC_B,       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
    //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------|
        KC_CAPS, KC_J,     KC_1,     KC_2,   KC_3,    KC_H,       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
    //`--------+--------+--------+--------+--------+--------/   \--------+--------+--------+--------+--------+--------'
                         KC_LCTL, KC_LALT, KC_SPC , KC_GAME2,     KC_TRNS, TG(_GAME1), KC_TRNS, KC_TRNS
    //                  `--------+--------+--------+--------'   `--------+--------+--------+--------'
    ),
    [_MAC0] = LAYOUT(
  //,--------+--------+---------+--------+---------+--------.   ,--------+---------+--------+---------+--------+--------.
     KC_ESC , KC_Q   , KC_W    , KC_E   , KC_R    , KC_T   ,     KC_Y   , KC_U    , KC_I   , KC_O    , KC_P   , KC_MINS,
  //|--------+--------+---------+--------+---------+--------|   |--------+---------+--------+---------+--------+--------|
     KC_TAB , KC_A   , KC_S    , KC_D   , KC_F    , KC_G   ,     KC_H   , KC_J    , KC_K   , KC_L    , KC_SCLN, KC_QUOT,
  //|--------+--------+---------+--------+---------+--------|   |--------+---------+--------+---------+--------+--------|
     KC_LSFT, KC_Z   , KC_X    , KC_C   , KC_V    , KC_B   ,     KC_N   , KC_M    , KC_COMM, KC_DOT  , KC_SLSH, KC_RSFT,
  //`--------+--------+---------+--------+---------+--------/   \--------+---------+--------+---------+--------+--------'
             KC_LALT, CTL_T(KC_LNG2),KC_2_SPC,LGUI_T(KC_LNG1),   LALT_T(KC_BSPC),KC_1_ENT, KC_LALT, KC_A_DEL
  //                 `----------+--------+---------+--------'   `--------+---------+--------+---------'
  ),

    [_MAC1] = LAYOUT(
  //,--------+--------+--------+--------+--------+--------.   ,--------+--------+--------+--------+--------+--------.
     KC_TRNS, KC_EXLM, KC_DQUO, KC_HASH, KC_DLR , KC_PERC,   KC_AT,LCTL(KC_LEFT),LCTL(KC_UP),LCTL(KC_RIGHT), KC_TILD, KC_BSLS,
  //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------|
     KC_LPRN, KC_LBRC, KC_GRV , KC_AMPR ,KC_QUOT, KC_EQL,     KC_LEFT, KC_DOWN,  KC_UP , KC_RGHT, KC_RBRC , KC_RPRN,
  //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------|
     KC_LSFT, _______, _______, _______, KC_LCBR, KC_LBRC,     KC_MINS, KC_PPLS,  KC_LT,    KC_GT, _______, _______,
  //`--------+--------+--------+--------+--------+--------/   \--------+--------+--------+--------+--------+--------'
                       KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS,     KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
  //                  `--------+--------+--------+--------'   `--------+--------+--------+--------'
  ),

    [_MAC2] = LAYOUT(
  //,--------+--------+--------+--------+--------+--------.   ,--------+--------+--------+--------+--------+--------.
     KC_TRNS,  KC_PAST  , KC_7  , KC_8 ,   KC_9  , KC_PMNS,     KC_TRNS, _______, _______, _______, _______, KC_TRNS,
  //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------|
     KC_TRNS,  KC_PSLS  , KC_4   , KC_5   , KC_6  , KC_PPLS   , KC_PGUP, _______, _______, _______, _______, _______,
  //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------|
      KC_OMG ,  KC_0  ,   KC_1  , KC_2,    KC_3,   KC_BSPC,     KC_PGDN, LGUI(KC_LEFT), _______, LGUI(KC_RIGHT) , KC_SLSH, _______,
  //`--------+--------+--------+--------+--------+--------/   \--------+--------+--------+--------+--------+--------'
                       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,     KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
  //                  `--------+--------+--------+--------'   `--------+--------+--------+--------
  ),

    [_MAC3] = LAYOUT(
    //,--------+--------+--------+--------+--------+--------.   ,--------+--------+--------+--------+--------+--------.
        TG(_MAC0), KC_TRNS, KC_F7,   KC_F8,   KC_F9,   KC_F12,     KC_PGUP, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, TG(_MAC0),
    //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------|
        KC_TRNS, KC_TRNS, KC_F4,   KC_F5,   KC_F6,   KC_F11,     KC_PGDN, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
    //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------|
        KC_TRNS, KC_TRNS, KC_F1,   KC_F2,   KC_F3,   KC_F10,     KC_CAPS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
    //`--------+--------+--------+--------+--------+--------/   \--------+--------+--------+--------+--------+--------'
                         KC_TRNS, KC_TRNS, KC_TRNS , KC_TRNS,     KC_PSCR, KC_TRNS, KC_TRNS, KC_TRNS
    //                  `--------+--------+--------+--------'   `--------+--------+--------+--------'
    ),

};

#ifdef OLED_ENABLE

void render_layer_state(void) {
    switch (get_highest_layer(layer_state)) {
        case _QWERTY:
            oled_write_ln_P(PSTR("Layer: Default"), false);
            break;
        case _RAISE:
            oled_write_ln_P(PSTR("Layer: Raise"), false);
            break;
        case _LOWER:
            oled_write_ln_P(PSTR("Layer: Lower"), false);
            break;
        case _OMG:
            oled_write_ln_P(PSTR("Layer: OMG"), false);
            break;
        case _GAME1:
            oled_write_ln_P(PSTR("Layer: Game1"), false);
            break;
        case _GAME2:
            oled_write_ln_P(PSTR("Layer: Game2"), false);
            break;

        // Mac用レイヤー
        case _MAC0:
            oled_write_ln_P(PSTR("Layer: Mac0"), false);
            break;
        case _MAC1:
            oled_write_ln_P(PSTR("Layer: Mac1"), false);
            break;
        case _MAC2:
            oled_write_ln_P(PSTR("Layer: Mac2"), false);
            break;
        case _MAC3:
            oled_write_ln_P(PSTR("Layer: Mac3"), false);
            break;

        default:
            oled_write_ln_P(PSTR("Layer: Undefined"), false);
    }
}

void render_logo(void) {
    static const char PROGMEM logo[] = {0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8a, 0x8b, 0x8c, 0x8d, 0x8e, 0x8f, 0x90, 0x91, 0x92, 0x93, 0x94, 0xa0, 0xa1, 0xa2, 0xa3, 0xa4, 0xa5, 0xa6, 0xa7, 0xa8, 0xa9, 0xaa, 0xab, 0xac, 0xad, 0xae, 0xaf, 0xb0, 0xb1, 0xb2, 0xb3, 0xb4, 0xc0, 0xc1, 0xc2, 0xc3, 0xc4, 0xc5, 0xc6, 0xc7, 0xc8, 0xc9, 0xca, 0xcb, 0xcc, 0xcd, 0xce, 0xcf, 0xd0, 0xd1, 0xd2, 0xd3, 0xd4, 0};
    oled_write_P(logo, false);

    uprintf("render_logo\n");
}

char keylog_str[24]  = {};
char keylogs_str[21] = {};
int  keylogs_str_idx = 0;

const char code_to_name[60] = {' ', ' ', ' ', ' ', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', 'R', 'E', 'B', 'T', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ';', '\'', ' ', ',', '.', '/', ' ', ' ', ' '};

void set_keylog(uint16_t keycode, keyrecord_t *record) {
    // char name = ' ';
    // if (keycode < 60) {
    //     name = code_to_name[keycode];
    // }

    // // update keylog
    // snprintf(keylog_str, sizeof(keylog_str), "%dx%d, k%2d : %c", record->event.key.row, record->event.key.col, keycode, name);

    // // update keylogs
    // if (keylogs_str_idx == sizeof(keylogs_str) - 1) {
    //     keylogs_str_idx = 0;
    //     for (int i = 0; i < sizeof(keylogs_str) - 1; i++) {
    //         keylogs_str[i] = ' ';
    //     }
    // }

    // keylogs_str[keylogs_str_idx] = name;
    // keylogs_str_idx++;
}

const char *read_keylog(void) { return keylog_str; }
const char *read_keylogs(void) { return keylogs_str; }

bool oled_task_user(void) {
    if (is_keyboard_master()) {
        render_layer_state();
        // oled_write_ln(read_keylog(), false);
        // oled_write_ln(read_keylogs(), false);
    } else {
        render_logo();
    }
    return false;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        set_keylog(keycode, record);
    }
    //デバッグ用
    // current_os_variant = detected_host_os();
    // uprintf("current_layer: %d\n", get_highest_layer(layer_state));
    // uprintf("current_os_variant: %d\n", current_os_variant);
    return true;
}

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    if (!is_keyboard_master()) return OLED_ROTATION_180;
    return rotation;
}

void matrix_init_kb(void) {
    wait_ms(1000);
    // OSの検出を行う
    current_os_variant = detected_host_os();

    // OSに応じてレイヤーを切り替え
    switch (current_os_variant) {
        case 3:
            layer_clear();  // 全レイヤーをクリア
            layer_on(_MAC0);    // Mac用のベースレイヤーを有効化
            break;
        case 2:
            layer_clear();  // 全レイヤーをクリア
            layer_on(_QWERTY);  // Windows用のベースレイヤーを有効化
            break;
        default:
            // デフォルトはQWERTYレイヤー
            layer_clear();
            layer_on(_QWERTY);
            break;
    }
}

#endif
