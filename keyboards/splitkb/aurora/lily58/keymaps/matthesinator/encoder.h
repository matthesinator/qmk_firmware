#pragma once
#include QMK_KEYBOARD_H

#define PAGE_LENGTH 3 // Entries per page on right oled
#define ENCODER_HOLD_LENGTH 500 // How many ms the encoder needs to be pressed to switch to settings

enum encoder_mode {
    HISTORY,
    SCROLL,
    ZOOM,
    BRIGHTNESS,
};

enum encoder_setting { // TODO: Remove enum to have array as single source of truth
    LED_STATE,
    LED_BRIGHTNESS,
    LED_COLOR,
    LED_SATURATION,
    LED_MODE,
};

typedef struct _enc_mode_msg {
    bool using_mode;
    enum encoder_mode mode;
    enum encoder_setting setting;
} enc_mode_msg;

extern enum encoder_mode enc_mode;
extern enum encoder_setting enc_setting;
extern bool using_modes;
extern uint16_t press_time;
extern const char* encoder_settings[];
extern int setting_count;


void fire_encoder_event(bool clockwise);
void change_encoder_mode(bool switch_modes);
void update_enc_display_rpc(uint8_t buf_len, const void* in_data, uint8_t out_buflen, void* out_data);
