#pragma once

#include QMK_KEYBOARD_H



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

void send_alt_code(uint8_t* sequence);
void send_unicode(uint8_t* sequence);
void send_special_character(uint16_t keycode);
