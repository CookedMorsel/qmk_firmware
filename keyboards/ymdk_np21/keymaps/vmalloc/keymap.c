#include QMK_KEYBOARD_H

#define _NP 0
#define _BL 1

enum custom_keycodes {
  NP = SAFE_RANGE,
  BL
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  /* Qwerty */

  [_NP] = LAYOUT_ortho_6x4(
    KC_ESC,  KC_TAB,  KC_BSPC, MO(_BL),
    KC_NLCK, KC_PSLS, KC_PAST, KC_PMNS,
    KC_P7,   KC_P8,   KC_P9,   KC_PPLS,
    KC_P4,   KC_P5,   KC_P6,   KC_PPLS,
    KC_P1,   KC_P2,   KC_P3,   KC_PENT,
    KC_P0,   KC_DOT,  KC_PDOT, KC_PENT
  ),

  [_BL] = LAYOUT_ortho_6x4(
    _______, _______, _______, _______,
    _______, _______, _______, _______,
    _______, _______, _______, RGB_MOD,
    _______, _______, _______, RGB_RMOD,
    RGB_SPI, RGB_SAI, RGB_HUI, BL_INC,
    RGB_SPD, RGB_SAD, RGB_HUD, BL_DEC
  )

};
