RGB_MATRIX_EFFECT(vmalloc_static_color_green)
RGB_MATRIX_EFFECT(vmalloc_static_color_blue)

#ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS

static bool vmalloc_static_color_green(effect_params_t* params) {
    RGB_MATRIX_USE_LIMITS(led_min, led_max);
    for (uint8_t i = led_min; i < led_max; i++) {
        rgb_matrix_set_color(i, 0, 0xff, 0x00);
    }
    return led_max < DRIVER_LED_TOTAL;
}

static bool vmalloc_static_color_blue(effect_params_t* params) {
    RGB_MATRIX_USE_LIMITS(led_min, led_max);
    for (uint8_t i = led_min; i < led_max; i++) {
        rgb_matrix_set_color(i, 0, 0, 0xff);
    }
    return led_max < DRIVER_LED_TOTAL;
}

#endif  // RGB_MATRIX_CUSTOM_EFFECT_IMPLS
