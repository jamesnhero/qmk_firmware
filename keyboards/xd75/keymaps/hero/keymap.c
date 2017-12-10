/* Copyright 2017 James Hero
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
#include "xd75.h"
#include "rgblight.h"

// Layer shorthand
#define _QW 0
#define _FN 1
#define _NP 2

// Increase readabilitydsa
#define _______ KC_TRNS
#define XXXXXXX KC_NO
#define KC_RST RESET

bool capslk_status = false;

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* QWERTY
 * .--------------------------------------------------------------------------------------------------------------------------------------.
 * | ESC    | 1      | 2      | 3      | 4      | 5      | `      | -      | =      | 6      | 7      | 8      | 9      | 0      | BACKSP |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+-----------------|
 * | TAB    | Q      | W      | E      | R      | T      | [      | ]      | \      | Y      | U      | I      | O      | P      | DEL    |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+-----------------+--------|
 * | CAP LK | A      | S      | D      | F      | G      | HOME   | INS    | PG UP  | H      | J      | K      | L      | ;      | '      |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------------------------+--------|
 * | LSHIFT | Z      | X      | C      | V      | B      | END    | UP     | PG DN  | N      | M      | ,      | .      | /      | ENTER  |
 * |--------+--------+--------+--------+--------+-----------------+--------+--------+--------+--------+-----------------+--------+--------|
 * | FN     | LCTRL  | LALT   | SUPER  | SPACE  | SPACE  | LEFT   | DOWN   | RIGHT  | SPACE  | SPACE  | MENU   | SUPER  | RALT   | RCTRL  |
 * '--------------------------------------------------------------------------------------------------------------------------------------'
 */

 [_QW] = { /* QWERTY */
  { KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_GRV,  KC_MINS, KC_EQL,  KC_6,    KC_7,   KC_8,    KC_9,    KC_0,    KC_BSPC },
  { KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_LBRC, KC_RBRC, KC_BSLS, KC_Y,    KC_U,   KC_I,    KC_O,    KC_P,    KC_DEL  },
  { KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_HOME, KC_INS,  KC_PGUP, KC_H,    KC_J,   KC_K,    KC_L,    KC_SCLN, KC_QUOT },
  { KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_END,  KC_UP,   KC_PGDN, KC_N,    KC_M,   KC_COMM, KC_DOT,  KC_SLSH, KC_ENT  },
  { MO(_NP), KC_LCTL, KC_LALT, KC_LGUI, KC_SPC,  KC_SPC,  KC_LEFT, KC_DOWN, KC_RGHT, KC_SPC,  KC_SPC, KC_MENU, KC_RGUI, KC_LALT, MO(_FN) },
 },

/* FUNCTION
 * .--------------------------------------------------------------------------------------------------------------------------------------.
 * |        | F1     | F2     | F3     | F4     | F5     | mute   |vol down| vol up | F6     | F7     | F8     | F9     | F10    |        |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * |        | F11    | F12    |        |        |        |        |        |        |        |        |        |        |        |        |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * | XXXXXX |        |        |        |        |        |        |        |        |        |        |        |        |        |        |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * |        |        |        |        |        |        |        |        |        |        |        |        |        |        |        |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * |        |        |        |        |        |        |        |        |        |        |        |        |        |        |        |
 * '--------------------------------------------------------------------------------------------------------------------------------------'
 */

 [_FN] = { /* FUNCTION */
  { _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_MUTE, KC_VOLD, KC_VOLU, KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  _______ },
  { _______, KC_F11,  KC_F12,  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______ },
  { XXXXXXX, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______ },
  { _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______ },
  { _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______ },
 },

 /* NUM PAD
 * .--------------------------------------------------------------------------------------------------------------------------------------.
 * | RESET  |        |        |        |        |        |        |        |        |        |        | NUM    | /      | *      | -      |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * |        |        |        |        |        |        |        |        |        |        |        | 7      | 8      | 9      | +      |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * | XXXXXX |        |        |        |        |        |        |        |        |        |        | 4      | 5      | 6      | +      |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * |        |        |        |        |        |        |        |        |        |        |        | 1      | 2      | 3      | ENTER  |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * |        |        |        |        |        |        |        |        |        |        |        | 0      | 0      | .      | ENTER  |
 * '--------------------------------------------------------------------------------------------------------------------------------------'
 */

 [_NP] = { /* NUM PAD */
  { KC_RST,  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_NLCK, KC_PSLS, KC_PAST, KC_PMNS },
  { _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_P7,   KC_P8,   KC_P9,   KC_PPLS },
  { XXXXXXX, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_P4,   KC_P5,   KC_P6,   KC_PPLS },
  { _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_P1,   KC_P2,   KC_P3,   KC_PENT },
  { _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_P0,   KC_P0,   KC_PDOT, KC_PENT },
 }
};

void setcaps_light(void){
    if (capslk_status == false) {
        rgblight_disable();
    }
    else {
        rgblight_enable();
        rgblight_setrgb(141, 182, 0);
    }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch(keycode) {
        case KC_CAPS:
            if (record->event.pressed) {
                capslk_status = !capslk_status;
                setcaps_light();
            }
            return true; break; /* return true so that CAPS_KEY is processed */

        case MO(_FN):
            /* same as num pad */
        case MO(_NP):
            if (record->event.pressed) {
                rgblight_disable();
            }
            else {
                setcaps_light();
            }
            return true; break;
    }
    return true;
};

void matrix_init_user(void){
  /* start with LEDs switched off */
  rgblight_enable();
  rgblight_disable();
};
