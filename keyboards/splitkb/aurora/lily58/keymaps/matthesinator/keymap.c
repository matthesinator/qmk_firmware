#include QMK_KEYBOARD_H
#include <string.h>
#include "transactions.h"
#include "keymap.h"
#include "oled.h"
#include "encoder.h"
#include "special_chars.h"

enum operating_system os_mode = WINDOWS;

/*
Ideas:
- Mirror right side to left side to allow for one handed typing?
- Set up Home Row Mods?

TODOs:
- LED Modes
- Figure out better encoder mode naming: mode(mode, setting) is confusing.
- Update readme
*/

/**********************************************************/
/*                         LAYOUT                         */
/**********************************************************/

/*  TEMPLATE
    LAYOUT(
        _______, _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
                          _______, _______, _______, _______,                   _______, _______, _______, _______,
    )
 */

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BASE] = LAYOUT( // Base Layer
        KC_ESC , KC_1   , KC_2   , KC_3   , KC_4   , KC_5   ,                   KC_6   , KC_7   , KC_8   , KC_9   , KC_0   , KC_MINS,
        KC_TAB , KC_Q   , KC_W   , KC_E   , KC_R   , KC_T   ,                   KC_Y   , KC_U   , KC_I   , KC_O   , KC_P   , KC_EQL,
        KC_LSFT, KC_A   , KC_S   , KC_D   , KC_F   , KC_G   ,                   KC_H   , KC_J   , KC_K   , KC_L   , KC_SCLN, KC_QUOT,
        KC_LCTL, KC_Z   , KC_X   , KC_C   , KC_V   , KC_B   , KC_MUTE, KX_ENC , KC_N   , KC_M   , KC_COMM, KC_DOT , KC_SLSH, KC_LGUI,
                          KC_LGUI, KC_LALT, MO(1)  , KC_SPC ,                   KC_ENT , KC_BSPC, MO(2)  , KC_RALT
    ),
    [_FUN1] = LAYOUT( // FN Layer 1: Arrows, Home/End/Page, Umlauts, F-Keys
        KC_F1  , KC_F2  , KC_F3  , KC_F4  , KC_F5  , KC_F6  ,                   KC_F7  , KC_F8  , KC_F9  , KC_F10 , KC_F11 , KC_F12,
        _______, _______, _______, KX_EURO, _______, _______,                   _______, KX_UE  , _______, KX_OE  , KC_LBRC, KC_RBRC,
        _______, KX_AE  , KX_SS  , KC_MPRV, KC_MNXT, KC_MPLY,                  KC_LEFT, KC_DOWN, KC_UP  , KC_RGHT, KC_CIRC, KC_BSLS,
        _______, _______, _______, _______, _______, _______, _______, _______, KC_HOME, KC_END , KC_PGDN, KC_PGUP, _______ , _______,
                          _______, _______, _______, _______,                   _______, KC_DEL , MO(3)  , _______
    ),
    [_FUN2] = LAYOUT( // FN Layer 2: -- tbd -- (maybe numpad keys in 3x3 square on left?)
        KC_GRV , _______, KC_2   , KC_3   , KC_4   , _______,                   _______, _______, _______, _______, _______, _______,
        _______, _______, KC_P7  , KC_P8  , KC_P9  , _______,                   _______, _______, _______, _______, _______, _______,
        _______, _______, KC_P4  , KC_P5  , KC_P6  , _______,                   _______, _______, _______, _______, _______, _______,
        _______, KC_P0  , KC_P1  , KC_P2  , KC_P3  , _______, _______, _______, KC_PLUS, KC_MINS, KC_EQL , KC_LBRC, KC_RBRC, KC_BSLS,
                          _______, _______, MO(3)  , _______,                   _______, _______, _______, _______
    ),
    [_OPTS] = LAYOUT( // Options Layer: Lighting & OS Control
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        KC_CAPS, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX, RGB_TOG, RGB_HUI, RGB_SAI, RGB_VAI,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______, _______, XXXXXXX, XXXXXXX, RGB_MOD, RGB_HUD, RGB_SAD, RGB_VAD,
                          _______, _______, _______, _______,                   _______, _______, _______, _______)
};

/**********************************************************/
/*                      USER FUNCTIONS                    */
/**********************************************************/

bool encoder_update_user(uint8_t index, bool clockwise) {
    reset_oled_timeout();
    if (index == 0) return true; // left encoder for volume
    fire_encoder_event(clockwise);
    return false;
}

bool oled_task_user(void) {
    if (oled_timed_out) {
        return false;
    }

    if (is_keyboard_master()) {
        update_left_display();
    } else {
        update_right_display();
    }
    return false;
}

/*
    Called whenever a key is pressed or released. Handles OS switches and delegates to other
    functions to send special characters.
*/
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    reset_oled_timeout();

    if (record->event.pressed) {
        switch (keycode) {
            case KX_WIN:
                os_mode = WINDOWS;
                // TODO: Show change on display
                return false;
            case KX_LIN:
                os_mode = LINUX;
                // TODO: Show change on display
                return false;
            case KX_ENC:
                press_time = record->event.time;
                return false;
            case KX_AE:
            case KX_OE:
            case KX_UE:
            case KX_SS:
            case KX_EURO:
                send_special_character(keycode);
                return false;
            default:
                return true;
        }
    } else if (!record->event.pressed && keycode == KX_ENC) {
        change_encoder_mode(record->event.time - press_time > ENCODER_HOLD_LENGTH);
        return false;
    }

    return true;
}

/**********************************************************/
/*                  INIT AND HOUSEKEEPING                 */
/**********************************************************/

void keyboard_pre_init_user(void) {
    // disable on-board LED
    setPinOutput(24);
    writePinHigh(24);
}

void keyboard_post_init_user(void) {
    transaction_register_rpc(ENC_MODE, update_enc_display_rpc);
    transaction_register_rpc(SET_TIMEOUT, set_timeout_rpc);
    oled_timeout_timer = timer_read32();
}

void housekeeping_task_user(void) {
    if (is_keyboard_master()) {
        check_oled_timeout();
    }
}
