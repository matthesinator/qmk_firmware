#pragma once
#include QMK_KEYBOARD_H

#define TIMEOUT_SECONDS 10

static uint32_t timeout_timer;
static bool timed_out = false;

typedef struct _set_timeout_msg {
    bool timeout;
} set_timeout_msg;

void update_left_display(void);
void update_right_display_mode(void);
void update_right_display_setting(void);
void reset_oled_timeout(void);
void set_timeout_rpc(uint8_t buf_len, const void* in_data, uint8_t out_buflen, void* out_data);
void check_oled_timeout(void);
