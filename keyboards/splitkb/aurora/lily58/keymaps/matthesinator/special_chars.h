#pragma once

#include QMK_KEYBOARD_H
#include "keymap.h"

struct special_character {
    uint8_t unicode_sequence[4];
    uint8_t alt_code_sequence[4];
};

extern const struct special_character AE;
extern const struct special_character ae;
extern const struct special_character OE;
extern const struct special_character oe;
extern const struct special_character UE;
extern const struct special_character ue;
extern const struct special_character SS;
extern const struct special_character ss;
extern const struct special_character euro;

void send_special_character(uint16_t keycode);
