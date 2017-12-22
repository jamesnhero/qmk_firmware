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
#define _DV 0
#define _QW 1
#define _FN 2
#define _NP 3

// Increase readabilitydsa
#define _______ KC_TRNS
#define XXXXXXX KC_NO
#define KC_RST RESET

bool capslk_status = false;
bool numlk_status = false;

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* DVORAK
 * .--------------------------------------------------------------------------------------------------------------------------------------.
 * | ESC    | 1      | 2      | 3      | 4      | 5      | [      | -      | ]      | 6      | 7      | 8      | 9      | 0      | BACKSP |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+-----------------|
 * | TAB    | '      | ,      | .      | P      | Y      | /      | +      | \      | F      | G      | C      | R      | L      | DEL    |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+-----------------+--------|
 * | CAP LK | A      | O      | E      | U      | I      | HOME   | INS    | PG UP  | D      | H      | T      | N      | A      | ENTER  |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------------------------+--------|
 * | LSHIFT | ;      | Q      | J      | K      | X      | END    | UP     | PG DN  | B      | M      | W      | V      | Z      | `      |
 * |--------+--------+--------+--------+--------+-----------------+--------+--------+--------+--------+-----------------+--------+--------|
 * | NUMPAD | LCTRL  | LALT   | SUPER  | SPACE  | SPACE  | LEFT   | DOWN   | RIGHT  | SPACE  | SPACE  | MENU   | SUPER  | RALT   | FN     |
 * '--------------------------------------------------------------------------------------------------------------------------------------'
 */

 [_DV] = { /* DVORAK */
  { KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_LBRC, KC_MINS, KC_RBRC, KC_6,    KC_7,   KC_8,    KC_9,    KC_0,    KC_BSPC },
  { KC_TAB,  KC_QUOT, KC_COMM, KC_DOT,  KC_P,    KC_Y,    KC_SLSH, KC_EQL,  KC_BSLS, KC_F,    KC_G,   KC_C,    KC_R,    KC_L,    KC_DEL  },
  { KC_CAPS, KC_A,    KC_O,    KC_E,    KC_U,    KC_I,    KC_HOME, KC_INS,  KC_PGUP, KC_D,    KC_H,   KC_T,    KC_N,    KC_S,    KC_ENT },
  { KC_LSFT, KC_SCLN, KC_Q,    KC_J,    KC_K,    KC_X,    KC_END,  KC_UP,   KC_PGDN, KC_B,    KC_M,   KC_W,    KC_V,    KC_Z,    KC_GRV  },
  { MO(_NP), KC_LCTL, KC_LALT, KC_LGUI, KC_SPC,  KC_SPC,  KC_LEFT, KC_DOWN, KC_RGHT, KC_SPC,  KC_SPC, KC_MENU, KC_RGUI, KC_LALT, MO(_FN) },
 },

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
 * | NUMPAD | LCTRL  | LALT   | SUPER  | SPACE  | SPACE  | LEFT   | DOWN   | RIGHT  | SPACE  | SPACE  | MENU   | SUPER  | RALT   | FN     |
 * '--------------------------------------------------------------------------------------------------------------------------------------'
 */

 [_QW] = { /* QWERTY */
  { KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_QUOT, KC_MINS, KC_EQL,  KC_6,    KC_7,   KC_8,    KC_9,    KC_0,    KC_BSPC },
  { KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_LBRC, KC_RBRC, KC_BSLS, KC_Y,    KC_U,   KC_I,    KC_O,    KC_P,    KC_DEL  },
  { KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_HOME, KC_INS,  KC_PGUP, KC_H,    KC_J,   KC_K,    KC_L,    KC_SCLN, KC_ENT  },
  { KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_END,  KC_UP,   KC_PGDN, KC_N,    KC_M,   KC_COMM, KC_DOT,  KC_SLSH, KC_GRV  },
  { MO(_NP), KC_LCTL, KC_LALT, KC_LGUI, KC_SPC,  KC_SPC,  KC_LEFT, KC_DOWN, KC_RGHT, KC_SPC,  KC_SPC, KC_MENU, KC_RGUI, KC_LALT, MO(_FN) },
 },

/* FUNCTION
 * .--------------------------------------------------------------------------------------------------------------------------------------.
 * | XXXXXX | F1     | F2     | F3     | F4     | F5     | mute   |vol down| vol up | F6     | F7     | F8     | F9     | F10    | XXXXXX |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * | XXXXXX | F11    | F12    | XXXXXX | XXXXXX | XXXXXX | XXXXXX | XXXXXX | XXXXXX | XXXXXX | XXXXXX | XXXXXX | XXXXXX | XXXXXX | XXXXXX |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * | XXXXXX | XXXXXX | XXXXXX | XXXXXX | XXXXXX | XXXXXX | XXXXXX | XXXXXX | XXXXXX | DVORAK | XXXXXX | XXXXXX | XXXXXX | XXXXXX | XXXXXX |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * | XXXXXX | XXXXXX | QUERTY | XXXXXX | XXXXXX | XXXXXX | XXXXXX | XXXXXX | XXXXXX | XXXXXX | XXXXXX | XXXXXX | XXXXXX | XXXXXX | XXXXXX |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * | XXXXXX | XXXXXX | XXXXXX | XXXXXX | XXXXXX | XXXXXX | XXXXXX | XXXXXX | XXXXXX | XXXXXX | XXXXXX | XXXXXX | XXXXXX | XXXXXX |        |
 * '--------------------------------------------------------------------------------------------------------------------------------------'
 */

 [_FN] = { /* FUNCTION */
  { XXXXXXX, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_MUTE, KC_VOLD, KC_VOLU, KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  XXXXXXX },
  { XXXXXXX, KC_F11,  KC_F12,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX },
  { XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, DF(_DV), XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX },
  { XXXXXXX, XXXXXXX, DF(_QW), XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX },
  { XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______ },
 },

 /* NUM PAD
 * .--------------------------------------------------------------------------------------------------------------------------------------.
 * | RESET  | XXXXXX | XXXXXX | XXXXXX | XXXXXX | XXXXXX | XXXXXX | XXXXXX | XXXXXX | XXXXXX | XXXXXX | NUM    | /      | *      | -      |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * | XXXXXX | XXXXXX | XXXXXX | XXXXXX | XXXXXX | XXXXXX | XXXXXX | XXXXXX | XXXXXX | XXXXXX | XXXXXX | 7      | 8      | 9      | +      |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * | XXXXXX | XXXXXX | XXXXXX | XXXXXX | XXXXXX | XXXXXX | XXXXXX | XXXXXX | XXXXXX | XXXXXX | XXXXXX | 4      | 5      | 6      | +      |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * | XXXXXX | XXXXXX | XXXXXX | XXXXXX | XXXXXX | XXXXXX | XXXXXX | XXXXXX | XXXXXX | XXXXXX | XXXXXX | 1      | 2      | 3      | ENTER  |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * |        | XXXXXX | XXXXXX | XXXXXX | XXXXXX | XXXXXX | XXXXXX | XXXXXX | XXXXXX | XXXXXX | XXXXXX | 0      | 0      | .      | ENTER  |
 * '--------------------------------------------------------------------------------------------------------------------------------------'
 */

 [_NP] = { /* NUM PAD */
  { KC_RST,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_NLCK, KC_PSLS, KC_PAST, KC_PMNS },
  { XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_P7,   KC_P8,   KC_P9,   KC_PPLS },
  { XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_P4,   KC_P5,   KC_P6,   KC_PPLS },
  { XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_P1,   KC_P2,   KC_P3,   KC_PENT },
  { _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_P0,   KC_P0,   KC_PDOT, KC_PENT },
 }
};

void setlight_green(void){
    rgblight_enable();
    rgblight_setrgb(141, 182, 0);
};

void setlight_blue(void){
    rgblight_enable();
    rgblight_setrgb(49, 140, 231);
};

void setlight_off(void){
    rgblight_disable();
};

void setlight_caps(void){
    if (capslk_status == true){
        setlight_green();
    }
    else {
        setlight_off();
    }
};

void setlight_num(void){
    if (numlk_status == true){
        setlight_blue();
    }
    else{
        setlight_off();
    }
};

void led_set_user(uint8_t usb_led) {

    if (usb_led & (1<<USB_LED_CAPS_LOCK)) {
        capslk_status = true;
    } else {
        capslk_status = false;
    }

    if (usb_led & (1<<USB_LED_NUM_LOCK)) {
        numlk_status = true;
    } else {
        numlk_status = false;
    }

    switch (layer_state){
        /* if on numpad layer, show status of numlock */
        case (1<<_NP):
            setlight_num();
            break;
        /* if on function layer, switch off lights */
        case (1<<_FN):
            setlight_off();
            break;
        /* otherwise show status of capslock */
        default:
            setlight_caps();
    }
}
