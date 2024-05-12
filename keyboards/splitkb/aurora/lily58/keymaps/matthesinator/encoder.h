#pragma once
#include QMK_KEYBOARD_H

#define PAGE_LENGTH 3 // Entries per page on right oled
#define HOLD_LENGTH 500 // How many ms a button needs to be held

enum encoder_mode { // TODO: Remove enum to have array as single source of truth
    HISTORY,
    SCROLL,
    ZOOM,
    BRIGHTNESS,
};

enum encoder_setting {
    LED_STATE,
    LED_BRIGHTNESS,
    LED_COLOR,
    LED_SATURATION,
    LED_MODE,
};

const char* encoder_settings[] = {"Tgl", "Brig", "Clr", "Sat", "Mode"};

enum encoder_mode enc_mode = HISTORY;
enum encoder_setting enc_setting = LED_STATE;
bool using_modes = true;
int setting_count = sizeof(encoder_settings) / sizeof(encoder_settings[0]);
uint16_t press_time = 0;

typedef struct _enc_mode_msg {
    bool using_mode;
    enum encoder_mode mode;
    enum encoder_setting setting;
} enc_mode_msg;


void encoder_update_mode(bool clockwise);
void encoder_update_setting(bool clockwise);
void change_encoder_mode(bool switch_modes);
void update_enc_display_rpc(uint8_t buf_len, const void* in_data, uint8_t out_buflen, void* out_data);
