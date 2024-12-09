// Copyright 2023 QMK
// SPDD-License-Identifier: GPL-2.0-or-later


    // [1] = LAYOUT(
    //     _______, _______, _______, _______, _______, _______,                                                       _______, _______, _______, _______, _______, _______,
    //              _______, _______, _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______, _______,
    //              _______, _______, _______, _______, _______, _______,                                     _______, _______, _______, _______, _______, _______
    // )



#include QMK_KEYBOARD_H
#include "split_util.h"


void keyboard_post_init_user(void) {
  // Set our LED pin as output
  setPinOutput(GP24);
  // Turn the LED off
  // (Due to technical reasons, high is off and low is on)
            //   if (!isLeftHand)
            //     writePinLow(GP24);
            //   else
    writePinHigh(GP24);
}



bool led_update_kb(led_t led_state) {
    bool res = led_update_user(led_state);
    if(res) {
        // gpio_write_pin sets the pin high for 1 and low for 0.
        // In this example the pins are inverted, setting
        // it low/0 turns it on, and high/1 turns the LED off.
        // This behavior depends on whether the LED is between the pin
        // and VCC or the pin and GND.
        if (isLeftHand)
            gpio_write_pin(GP24, !led_state.caps_lock);
        else
            gpio_write_pin(GP24, !led_state.num_lock);

    }
    return res;
}



// homerow mod keys
#define LHRM_G MT(MOD_LGUI, KC_A)
#define LHRM_A MT(MOD_LALT, KC_S)
#define LHRM_C MT(MOD_LCTL, KC_D)
#define LHRM_S MT(MOD_LSFT, KC_F)
#define RHRM_S MT(MOD_RSFT, KC_J)
#define RHRM_C MT(MOD_RCTL, KC_K)
#define RHRM_A MT(MOD_LALT, KC_L)
#define RHRM_G MT(MOD_RGUI, KC_SCLN)


enum layer_names {
    _QWERTY,
    _L1,
    _L2,
    _Fn,
    _NOITA
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [_QWERTY] = LAYOUT(
//      /           /           /           /           /           /           /           /                       /           /           /           /           /           /           /           /
        QK_GESC,    KC_Q,       KC_W,       KC_E,       KC_R,       KC_T,                                                                   KC_Y,       KC_U,       KC_I,       KC_O,       KC_P,       KC_BSPC,
                    LHRM_G,     LHRM_A,     LHRM_C,     LHRM_S,     KC_G,       KC_TAB ,    KC_SPC,                 KC_ENT,     _______,    KC_H,       RHRM_S,     RHRM_C,     RHRM_A,     RHRM_G,
                    KC_Z,       KC_X,       KC_C,       KC_V,       KC_B,       MO(_L1),                                        MO(_L2),    KC_N,       KC_M,       KC_COMM,    KC_DOT,     KC_SLSH

    ),

    [_L1] = LAYOUT(
//      /           /           /           /           /           /           /           /                       /           /           /           /           /           /           /           /
        QK_BOOT,    _______,    _______,    _______,    _______,    KC_LCBR,                                                                KC_RCBR,    KC_7,       KC_8,       KC_9,       KC_MINS,    KC_EQL,
                    _______,    _______,    _______,    _______,    KC_LBRC,    MO(_Fn),    KC_BSPC,                KC_DEL,     KC_QUOT,    KC_RBRC,    KC_4,       KC_5,       KC_6,       KC_BSLS,
                    _______,    _______,    _______,    _______,    KC_LPRN,    _______,                                        _______,    KC_RPRN,    KC_1,       KC_2,       KC_3,       KC_0
    ),

    [_L2] = LAYOUT(
//      /           /           /           /           /           /           /           /                       /           /           /           /           /           /           /           /
        QK_RBT,     _______,    KC_HOME,    KC_UP  ,    KC_END ,    KC_PGUP,                                                                KC_PSLS,    KC_P7,      KC_P8,      KC_P9,      KC_PMNS,    KC_PPLS,
                    _______,    KC_LEFT,    KC_DOWN,    KC_RGHT,    KC_PGDN,    _______,    _______,                KC_PENT,    MO(_Fn), KC_PAST,    KC_P4,      KC_P5,      KC_P6,      KC_PDOT,
                    _______,    _______,    _______,    _______,    _______,    _______,                                        _______,    KC_PDOT,    KC_P1,      KC_P2,      KC_P3,      KC_P0
    ),

    [_Fn] = LAYOUT(
//      /           /           /           /           /           /           /           /                       /           /           /           /           /           /           /           /
        QK_RBT,     KC_CAPS,    KC_NUM ,    _______,    _______,    TG(_NOITA),                                                             KC_PSLS,    KC_F7,      KC_F8,      KC_F9,      KC_F12,     KC_PSCR,
                    _______,    _______,    _______,    _______,    _______,    _______,    KC_PSCR,                _______,    _______,    KC_PAST,    KC_F4,      KC_F5,      KC_F6,      KC_F11,
                    _______,    _______,    _______,    _______,    _______,    _______,                                        _______,    KC_PDOT,    KC_F1,      KC_F2,      KC_F3,      KC_F10
    ),

    [_NOITA] = LAYOUT(
//      /           /           /           /           /           /           /           /                       /           /           /           /           /           /           /           /
        QK_GESC,    KC_2,       KC_Q,       KC_W,       KC_E,       KC_2,                                                                  _______,     _______,    _______,    _______,    _______,    TG(_NOITA),
                    KC_3,       KC_A,       KC_S,       KC_D,       KC_3,       MOD_LSFT,   KC_SPC,                _______,    _______,    _______,     _______,    _______,    _______,    _______,
                    KC_G,       KC_X,       KC_C,       KC_V,       KC_4,       KC_TAB,                                        _______,    _______,     _______,    _______,    _______,    _______

    )


};
