#include QMK_KEYBOARD_H
#include "special_chars.h"

const struct special_character AE   = {{KC_0, KC_0, KC_C, KC_4}, {KC_P1, KC_P4, KC_P2, KC_NO}};
const struct special_character ae   = {{KC_0, KC_0, KC_E, KC_4}, {KC_P1, KC_P3, KC_P2, KC_NO}};
const struct special_character OE   = {{KC_0, KC_0, KC_D, KC_6}, {KC_P1, KC_P5, KC_P3, KC_NO}};
const struct special_character oe   = {{KC_0, KC_0, KC_F, KC_6}, {KC_P1, KC_P4, KC_P8, KC_NO}};
const struct special_character UE   = {{KC_0, KC_0, KC_D, KC_C}, {KC_P1, KC_P5, KC_P4, KC_NO}};
const struct special_character ue   = {{KC_0, KC_0, KC_F, KC_C}, {KC_P1, KC_P2, KC_P9, KC_NO}};
const struct special_character SS   = {{KC_1, KC_E, KC_9, KC_E}, {KC_P7, KC_P8, KC_P3, KC_P8}};
const struct special_character ss   = {{KC_0, KC_0, KC_D, KC_F}, {KC_P2, KC_P2, KC_P5, KC_NO}};
const struct special_character euro = {{KC_2, KC_0, KC_A, KC_C}, {KC_P0, KC_P1, KC_P2, KC_P8}};

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
