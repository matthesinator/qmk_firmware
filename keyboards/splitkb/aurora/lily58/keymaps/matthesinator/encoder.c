#include QMK_KEYBOARD_H
#include "transactions.h"
#include "encoder.h"
#include "oled.h"

const char* encoder_settings[] = {"Tgl", "Brig", "Clr", "Sat", "Mode"};

enum encoder_mode enc_mode = HISTORY;
enum encoder_setting enc_setting = LED_STATE;
bool using_modes = true;
int setting_count = sizeof(encoder_settings) / sizeof(encoder_settings[0]);
uint16_t press_time = 0;

void encoder_update_mode(bool clockwise);
void encoder_update_setting(bool clockwise);
/*
    Fire the encoder event.
    Delegates to #encoder_update_mode or #encoder_update_settings depending on which mode is active.
*/
void fire_encoder_event(bool clockwise) {
    if (using_modes) {
        encoder_update_mode(clockwise);
    } else {
        encoder_update_setting(clockwise);
    }
}

/*
    Send the corresponding key press for the selected mode and direction.
*/
void encoder_update_mode(bool clockwise) {
    if (clockwise) {
        switch (enc_mode) {
            case HISTORY:
                tap_code16(C(KC_Y));
                break;
            case SCROLL:
                tap_code(KC_MS_WH_DOWN);
                break;
            case ZOOM:
                tap_code16(S(C(KC_EQL)));
                break;
            case BRIGHTNESS:
                rgb_matrix_increase_val();
                break;
        }
    } else {
        switch (enc_mode) {
            case HISTORY:
                tap_code16(C(KC_Z));
                break;
            case SCROLL:
                tap_code(KC_MS_WH_UP);
                break;
            case ZOOM:
                tap_code16(C(KC_MINS));
                break;
            case BRIGHTNESS:
                rgb_matrix_decrease_val();
                break;
        }
    }
}

/*
    Update the keyboard settings.
    Updates the setting depending on the selected setting and direction.
*/
void encoder_update_setting(bool clockwise) {
    if (clockwise) {
        switch (enc_setting) {
            case LED_STATE:
                rgb_matrix_enable();
                break;
            case LED_BRIGHTNESS:
                rgb_matrix_increase_val();
                break;
            case LED_COLOR:
                rgb_matrix_increase_hue();
                break;
            case LED_SATURATION:
                rgb_matrix_increase_sat();
                break;
            case LED_MODE:
                break;
        }
    } else {
        switch (enc_setting) {
            case LED_STATE:
                rgb_matrix_disable();
                break;
            case LED_BRIGHTNESS:
                rgb_matrix_decrease_val();
                break;
            case LED_COLOR:
                rgb_matrix_decrease_hue();
                break;
            case LED_SATURATION:
                rgb_matrix_decrease_sat();
                break;
            case LED_MODE:
                break;
        }
    }
}

/*
    Changes the encoders current mode and switches between modes and settings. Sends an RPC call to the slave.
*/
void change_encoder_mode(bool switch_modes) {
    if (switch_modes) {
        using_modes = !using_modes;
        enc_mode_msg data = {using_modes, enc_mode, enc_setting};
        transaction_rpc_send(ENC_MODE, sizeof(data), &data);
        return;
    }

    if (using_modes) {
        enc_mode += 1;
        enc_mode %= 4;
    } else {
        enc_setting += 1;
        enc_setting %= setting_count;
    }
    update_right_display();

    enc_mode_msg data = {using_modes, enc_mode, enc_setting};
    transaction_rpc_send(ENC_MODE, sizeof(data), &data);
}

/*
    RPC on the slave to update the current encoder mode.
*/
void update_enc_display_rpc(uint8_t buf_len, const void* in_data, uint8_t out_buflen, void* out_data) {
    const enc_mode_msg *data = (const enc_mode_msg*) in_data;
    using_modes = data->using_mode;
    enc_mode = data->mode;
    enc_setting = data->setting;
    update_right_display();
}
