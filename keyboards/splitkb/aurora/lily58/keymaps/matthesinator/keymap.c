#include QMK_KEYBOARD_H
#include <string.h>
#include "transactions.h"
#include "oled.h"
#include "encoder.h"

#define MODS_SHIFT_MASK (MOD_BIT(KC_LSFT)|MOD_BIT(KC_RSFT))
#define SHIFTED get_mods()&MODS_SHIFT_MASK
#define CAPS_ON host_keyboard_led_state().caps_lock
#define NUM_LOCK_ON host_keyboard_led_state().num_lock

#define _BASE 0 // Base layer
// #define _GAME 1 // Gaming Layer
#define _FUN1 1 // Function layer
#define _FUN2 2 // Function layer
#define _OPTS 3 // Options layer
#define _QUIC 4 // Quicksettings layer




/**********************************************************/
/*                       VARIABLES                        */
/**********************************************************/


enum my_keycodes {
    KX_WIN = SAFE_RANGE,
    KX_LIN,
    KX_ENC,     // right encoder press
    KX_AE,      // Ä: U+00C4/ALT+142     ä: U+00E4/ALT+132
    KX_OE,      // Ö: U+00D6/ALT+153     ö: U+00F6/ALT+148
    KX_UE,      // Ü: U+00DC/ALT+154     ü: U+00FC/ALT+129
    KX_SS,      // ẞ: U+1E9E/ALT+7838    ß: U+00DF/ALT+225
    KX_EURO     // €: U+20AC/ALT+0128
};

struct special_character {
    uint8_t unicode_sequence[4];
    uint8_t alt_code_sequence[4];
};

const struct special_character AE   = {{KC_0, KC_0, KC_C, KC_4}, {KC_P1, KC_P4, KC_P2, KC_NO}};
const struct special_character ae   = {{KC_0, KC_0, KC_E, KC_4}, {KC_P1, KC_P3, KC_P2, KC_NO}};
const struct special_character OE   = {{KC_0, KC_0, KC_D, KC_6}, {KC_P1, KC_P5, KC_P3, KC_NO}};
const struct special_character oe   = {{KC_0, KC_0, KC_F, KC_6}, {KC_P1, KC_P4, KC_P8, KC_NO}};
const struct special_character UE   = {{KC_0, KC_0, KC_D, KC_C}, {KC_P1, KC_P5, KC_P4, KC_NO}};
const struct special_character ue   = {{KC_0, KC_0, KC_F, KC_C}, {KC_P1, KC_P2, KC_P9, KC_NO}};
const struct special_character SS   = {{KC_1, KC_E, KC_9, KC_E}, {KC_P7, KC_P8, KC_P3, KC_P8}};
const struct special_character ss   = {{KC_0, KC_0, KC_D, KC_F}, {KC_P2, KC_P2, KC_P5, KC_NO}};
const struct special_character euro = {{KC_2, KC_0, KC_A, KC_C}, {KC_P0, KC_P1, KC_P2, KC_P8}};

enum operating_system {
    WINDOWS = 0,
    LINUX = 1
};

enum operating_system os_mode = WINDOWS;






/*  EMPTY LAYOUT
    LAYOUT(
        _______, _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, XXXXXXX, XXXXXXX, _______, _______, _______, _______, _______, _______,
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
        _______ , KX_AE  , KX_SS  , KC_MPRV, KC_MNXT, KC_MPLY,                  KC_LEFT, KC_DOWN, KC_UP  , KC_RGHT, KC_CIRC, KC_BSLS,
        _______, _______, _______, _______, _______, _______, _______, _______, KC_HOME, KC_END , KC_PGDN, KC_PGUP, _______ , _______,
                          _______, _______, _______, _______,                   _______, KC_DEL , MO(3)  , _______
    ),
    [_FUN2] = LAYOUT( // FN Layer 2: -- tbd -- (maybe numpad keys in 3x3 square on left?)
        KC_GRV , _______, KC_2   , KC_3   , KC_4   , _______,                   _______, _______, _______, _______, _______, _______,
        _______, _______, KC_P7  , KC_P8  , KC_P9  , _______,                   _______, _______, _______, _______, _______, _______,
        KC_CAPS, _______, KC_P4  , KC_P5  , KC_P6  , _______,                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        _______, KC_P0  , KC_P1  , KC_P2  , KC_P3  , _______, _______, _______, KC_PLUS, KC_MINS, KC_EQL , KC_LBRC, KC_RBRC, KC_BSLS,
                          _______, _______, MO(3)  , _______,                   _______, _______, _______, _______
    ),
    [_OPTS] = LAYOUT( // Options Layer: Lighting & OS Control
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX, RGB_TOG, RGB_HUI, RGB_SAI, RGB_VAI,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______, _______, XXXXXXX, XXXXXXX, RGB_MOD, RGB_HUD, RGB_SAD, RGB_VAD,
                          _______, _______, _______, _______,                   _______, _______, _______, _______)
};

// TODO: Right encoder
// Use right encoder for rgb menu?
//      -> remove enc brightness
// TODO: Copy & adapt underglow
// TODO: Set up backlight & options
// TODO: Set up left-dominant gaming layer

#ifdef ENCODER_ENABLE

bool encoder_update_user(uint8_t index, bool clockwise) {
    reset_oled_timeout();

    if (index == 0) return true; // left encoder for volume

    if (using_modes) {
        encoder_update_mode(clockwise);
    } else {
        encoder_update_setting(clockwise);
    }

    return false;
}
#endif

/**********************************************************/
/*                  DISPLAY FUNCTIONALITY                 */
/**********************************************************/






/**********************************************************/
/*                  CUSTOM FUNCTIONALITY                  */
/**********************************************************/

/*
    Holds ALT and enters a key sequence to input special characters in Windows. Enables numlock if
    it's not enabled. If a shift key is pressed, it will be disabled and re-enabled to make
    entering the alt-code possible.
*/
void send_alt_code(uint8_t* sequence) {
    bool lshift = get_mods() & MOD_BIT(KC_LSFT);
    bool rshift = get_mods() & MOD_BIT(KC_RSFT);

    if (lshift) {
        unregister_code(KC_LSFT);
    }

    if (rshift) {
        unregister_code(KC_RSFT);
    }

    if (!NUM_LOCK_ON) {
        tap_code(KC_NUM);
    }

    register_code(KC_LALT);
    for (int i = 0; i < 4; i++) {
        tap_code(sequence[i]);
    }
    unregister_code(KC_LALT);

    if (lshift) {
        register_code(KC_LSFT);
    }

    if (rshift) {
        register_code(KC_RSFT);
    }
}

/*
    Presses Ctrl+Shift+u to allow entering the hex value of a unicode character on Linux.
*/
void send_unicode(uint8_t* sequence) {
    SEND_STRING(SS_LCTL(SS_LSFT("u")));
    for (int i = 0; i < 4; i++) {
        tap_code(sequence[i]);
    }
    tap_code(KC_ENT);

}

/*
    Checks which special character to send and if it is capitalized. Depending on the active OS it
    sends either an ALT code (Windows) or a unicode(Linux).
*/
void send_special_character(uint16_t keycode) {
    struct special_character character;

    switch (keycode) {
        case KX_AE:
            character = (SHIFTED || CAPS_ON) ? AE : ae;
            break;
        case KX_OE:
            character = (SHIFTED || CAPS_ON) ? OE : oe;
            break;
        case KX_UE:
            character = (SHIFTED || CAPS_ON) ? UE : ue;
            break;
        case KX_SS:
            character = (SHIFTED || CAPS_ON) ? SS : ss;
            break;
        case KX_EURO:
            character = euro;
            break;
        default:
            break;
    }
    switch (os_mode) {
        case WINDOWS:
            send_alt_code(character.alt_code_sequence);
            break;
        case LINUX:
            send_unicode(character.unicode_sequence);
            break;
    }
}

/*
    Checks if both (left & right) shift keys are pressed and toggles caps lock if both are pressed.
*/
void check_shift_state(void) {
    if (get_mods() & (MOD_BIT(KC_LSFT) | MOD_BIT(KC_RSFT))) {
        tap_code(KC_CAPS);
    }
}

bool oled_task_user(void) {
    if (timed_out) {
        return false;
    }
    if (is_keyboard_master()) {
        update_left_display();
        return false;
    }
    if (using_modes) {
        update_right_display_mode();
    } else {
        update_right_display_setting();
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
            case KC_LSFT:
            case KC_RSFT:
                check_shift_state();
                return true;
            default:
                return true;
        }
    } else if (!record->event.pressed && keycode == KX_ENC) {
        change_encoder_mode(record->event.time - press_time > HOLD_LENGTH);
        return false;
    }

    return true;
}

void keyboard_pre_init_user(void) {
    // disable on-board LED
    setPinOutput(24);
    writePinHigh(24);
}

void keyboard_post_init_user(void) {
    transaction_register_rpc(ENC_MODE, update_enc_display_rpc);
    transaction_register_rpc(SET_TIMEOUT, set_timeout_rpc);
    timeout_timer = timer_read32();
}

void housekeeping_task_user(void) {
    if (is_keyboard_master()) {
        check_oled_timeout();
    }
}
