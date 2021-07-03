#include QMK_KEYBOARD_H

void matrix_init_user(void) {
    rgb_matrix_config.speed = 0;

    rgb_matrix_config.hsv.h = 151;
    rgb_matrix_config.hsv.s = 250;
    rgb_matrix_config.hsv.v = 255;

    rgb_matrix_increase_speed();

#ifdef VMALLOC_DISABLE_RGB_ON_STARTUP
    rgb_matrix_set_flags(LED_FLAG_NONE);
#endif
}

void keyboard_post_init_user(void) {
    // rgb_matrix_set_flags(LED_FLAG_NONE);
    debug_enable = true;
}
