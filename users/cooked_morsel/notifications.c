#include QMK_KEYBOARD_H
#include "print.h"

#define FADE_TIME_MS (500)
#define min(a, b) ((a) > (b)) ? (b) : (a)
#define max(a, b) ((a) < (b)) ? (b) : (a)

typedef struct notification_s {
    bool     enabled;
    uint8_t  r;
    uint8_t  g;
    uint8_t  b;
    uint16_t last_timer;
    uint32_t num_milliseconds;
    uint32_t elapsed;
} notification_t;

notification_t g_notification;

void raw_hid_receive(uint8_t *data, uint8_t length) {
    // uprintf("DEBUG length=%d\n", (int)length);
    if (length > 0) {
        if (data[0] == 1) {
            g_notification.r                = data[1];
            g_notification.g                = data[2];
            g_notification.b                = data[3];
            g_notification.num_milliseconds = (uint32_t)(data[4] << 8) + data[5];
            g_notification.elapsed          = 0;
            g_notification.enabled          = true;
            g_notification.last_timer       = timer_read();
        } else {
            uprintf("WARN Got unknown control code %d\n", (int)data[0]);
        }
    }
}

static void rgb_matrix_set_color_range(int start, int finish, int r, int g, int b) {
    for (int i = start; i < finish; ++i) {
        rgb_matrix_set_color(i, r, g, b);
    }
}

void notifications_key_pressed(void) {
    if (g_notification.enabled && g_notification.num_milliseconds == 0) {
        g_notification.num_milliseconds = 1000;
        g_notification.last_timer       = timer_read();
        g_notification.elapsed          = 500;
    }
}

#define FADE_SPEED (255.0)

void rgb_matrix_indicators_user(void) {
    if (g_notification.enabled) {
        float    duration = g_notification.num_milliseconds;
        uint16_t elapsed  = timer_elapsed(g_notification.last_timer);
        g_notification.elapsed += elapsed;

        if (duration > 0) {
            g_notification.last_timer = timer_read();

            if (g_notification.elapsed >= duration) {
                g_notification.enabled = false;
                rgb_matrix_set_color_range(0, DRIVER_LED_TOTAL, 0, 0, 0);
            } else {
                float factor = max(min(-abs(g_notification.elapsed - (duration / 2.0)) + (duration / 2.0), FADE_SPEED), 0) / FADE_SPEED;
                rgb_matrix_set_color_range(0, DRIVER_LED_TOTAL, g_notification.r * factor, g_notification.g * factor, g_notification.b * factor);
            }
        } else {
            float factor = max(min(g_notification.elapsed / 100.0, FADE_SPEED), 0) / FADE_SPEED;
            rgb_matrix_set_color_range(0, DRIVER_LED_TOTAL, g_notification.r * factor, g_notification.g * factor, g_notification.b * factor);
        }
    }
}
