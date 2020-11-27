#include QMK_KEYBOARD_H

#define _NP 0
#define _BL 1

enum custom_keycodes { NP = SAFE_RANGE, BL };

// clang-format off
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
    RESET, _______, _______, _______,
    _______, _______, _______, BL_INC,
    RGB_SPD, RGB_HUI, RGB_SPI, BL_INC,
   RGB_RMOD, RGB_HUD, RGB_MOD, BL_INC,
    RGB_VAD, _______, RGB_VAI, BL_DEC,
    RGB_TOG, RGB_TOG, _______, BL_DEC
  )

};
// clang-format on
