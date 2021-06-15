#include QMK_KEYBOARD_H

#include "notifications.h"

enum alt_keycodes {
    U_T_AUTO = SAFE_RANGE,  // USB Extra Port Toggle Auto Detect / Always Active
    U_T_AGCR,               // USB Toggle Automatic GCR control
    DBG_TOG,                // DEBUG Toggle On / Off
    DBG_MTRX,               // DEBUG Toggle Matrix Prints
    DBG_KBD,                // DEBUG Toggle Keyboard Prints
    DBG_MOU,                // DEBUG Toggle Mouse Prints
    MD_BOOT,                // Restart into bootloader after hold timeout
};

enum {
    LAYER_DEFAULT,
    L_FN,
    LAYER_CAPS,
    L_MAC,
};

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [LAYER_DEFAULT] = LAYOUT(
        KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC, _______, \
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS, KC_HOME, \
MO(LAYER_CAPS),  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,  KC_PGUP, \
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,          KC_UP,   KC_PGDN, \
        KC_LCTL, KC_LGUI, KC_LALT,                            KC_SPC,                             KC_RALT, MO(L_FN),KC_LEFT, KC_DOWN, KC_RGHT  \
    ),
    [L_FN] = LAYOUT(
        KC_GRV,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_MPLY, KC_MUTE, \
        _______, RGB_SPD, RGB_VAI, RGB_SPI, RGB_HUI, RGB_SAI, _______, U_T_AUTO,U_T_AGCR,_______, KC_PSCR, KC_SLCK, KC_PAUS, _______, KC_END, \
        _______, RGB_RMOD,RGB_VAD, RGB_MOD, RGB_HUD, RGB_SAD, _______, _______, _______, _______, _______, _______,          _______, KC_VOLU, \
        _______, RGB_TOG, _______, _______, _______, MD_BOOT, _______, DBG_TOG, _______, _______, _______, _______,          KC_PGUP, KC_VOLD, \
      TG(L_MAC), _______, _______,                            _______,                            _______, _______, KC_HOME, KC_PGDN, KC_END  \
    ),
    [LAYER_CAPS] = LAYOUT(
        _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  _______, _______, \
        _______, _______, _______, _______, _______, _______, _______, KC_BSPC, KC_UP,   KC_DEL,  _______, _______, _______, RESET,   _______, \
        _______, _______, KC_VOLD, KC_VOLU, KC_MUTE, _______, KC_PGUP, KC_LEFT, KC_DOWN, KC_RGHT, _______, _______,          _______, _______, \
        _______, _______, _______, _______, _______, _______, KC_PGDN, _______, _______, _______, _______, _______,          _______, _______, \
        _______, _______, _______,                            KC_LCTL,                            _______, _______, _______, _______, _______ \
    ),
    [L_MAC] = LAYOUT(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______, \
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______, \
        KC_LGUI, KC_LCTL, _______,                            _______,                            _______, _______, _______, _______, _______  \
    ),



    /*
    [X] = LAYOUT(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______, \
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______, \
        _______, _______, _______,                            _______,                            _______, _______, _______, _______, _______  \
    ),
    */
};
// clang-format on

#define MODS_SHIFT (get_mods() & MOD_BIT(KC_LSHIFT) || get_mods() & MOD_BIT(KC_RSHIFT))
#define MODS_CTRL (get_mods() & MOD_BIT(KC_LCTL) || get_mods() & MOD_BIT(KC_RCTRL))
#define MODS_ALT (get_mods() & MOD_BIT(KC_LALT) || get_mods() & MOD_BIT(KC_RALT))

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    static uint32_t key_timer;

    notifications_key_pressed();

    switch (keycode) {
        case U_T_AUTO:
            if (record->event.pressed && MODS_SHIFT && MODS_CTRL) {
                TOGGLE_FLAG_AND_PRINT(usb_extra_manual, "USB extra port manual mode");
            }
            return false;
        case U_T_AGCR:
            if (record->event.pressed && MODS_SHIFT && MODS_CTRL) {
                TOGGLE_FLAG_AND_PRINT(usb_gcr_auto, "USB GCR auto mode");
            }
            return false;
        case DBG_TOG:
            if (record->event.pressed) {
                TOGGLE_FLAG_AND_PRINT(debug_enable, "Debug mode");
            }
            return false;
        case DBG_MTRX:
            if (record->event.pressed) {
                TOGGLE_FLAG_AND_PRINT(debug_matrix, "Debug matrix");
            }
            return false;
        case DBG_KBD:
            if (record->event.pressed) {
                TOGGLE_FLAG_AND_PRINT(debug_keyboard, "Debug keyboard");
            }
            return false;
        case DBG_MOU:
            if (record->event.pressed) {
                TOGGLE_FLAG_AND_PRINT(debug_mouse, "Debug mouse");
            }
            return false;
        case MD_BOOT:
            if (record->event.pressed) {
                key_timer = timer_read32();
            } else {
                if (timer_elapsed32(key_timer) >= 500) {
                    reset_keyboard();
                }
            }
            return false;
        case RGB_TOG:
            if (record->event.pressed) {
                switch (rgb_matrix_get_flags()) {
                    case LED_FLAG_ALL: {
                        rgb_matrix_set_flags(LED_FLAG_KEYLIGHT);
                        rgb_matrix_set_color_all(0, 0, 0);
                    } break;
                    case LED_FLAG_KEYLIGHT: {
                        rgb_matrix_set_flags(LED_FLAG_UNDERGLOW);
                        rgb_matrix_set_color_all(0, 0, 0);
                    } break;
                    case LED_FLAG_UNDERGLOW: {
                        rgb_matrix_set_flags(LED_FLAG_NONE);
                        rgb_matrix_set_color_all(0, 0, 0);
                    } break;
                    default: {
                        rgb_matrix_set_flags(LED_FLAG_ALL);
                        rgb_matrix_enable_noeeprom();
                    } break;
                }
            }
            return false;
        default:
            return true;  // Process all other keycodes normally
    }
}

enum { LED_INDEX_ESC = 0, LED_INDEX_1, LED_INDEX_2, LED_INDEX_3, LED_INDEX_4, LED_INDEX_5, LED_INDEX_6, LED_INDEX_7, LED_INDEX_8, LED_INDEX_9, LED_INDEX_0, LED_INDEX_MINS, LED_INDEX_EQL, LED_INDEX_BSPC, LED_INDEX_DEL, LED_INDEX_TAB, LED_INDEX_Q, LED_INDEX_W, LED_INDEX_E, LED_INDEX_R, LED_INDEX_T, LED_INDEX_Y, LED_INDEX_U, LED_INDEX_I, LED_INDEX_O, LED_INDEX_P, LED_INDEX_LBRC, LED_INDEX_RBRC, LED_INDEX_BSLS, LED_INDEX_HOME, LED_INDEX_CAPS, LED_INDEX_A, LED_INDEX_S, LED_INDEX_D, LED_INDEX_F, LED_INDEX_G, LED_INDEX_H, LED_INDEX_J, LED_INDEX_K, LED_INDEX_L, LED_INDEX_SCLN, LED_INDEX_QUOT, LED_INDEX_ENT, LED_INDEX_PGUP, LED_INDEX_LSFT, LED_INDEX_Z, LED_INDEX_X, LED_INDEX_C, LED_INDEX_V, LED_INDEX_B, LED_INDEX_N, LED_INDEX_M, LED_INDEX_COMM, LED_INDEX_DOT, LED_INDEX_SLSH, LED_INDEX_RSFT, LED_INDEX_UP, LED_INDEX_PGDN, LED_INDEX_LCTL, LED_INDEX_LGUI, LED_INDEX_LALT, LED_INDEX_SPC, LED_INDEX_RALT, LED_INDEX_FN, LED_INDEX_LEFT, LED_INDEX_DOWN, LED_INDEX_RGHT, LED_4FRAME_0 };

#define COLORIZE_RED(key) rgb_matrix_set_color(key, 0xFF, 0, 0)
#define COLORIZE_BLUE(key) rgb_matrix_set_color(key, 0, 0, 0xFF)
