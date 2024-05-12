#pragma once

#include QMK_KEYBOARD_H

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

enum operating_system {
    WINDOWS = 0,
    LINUX = 1
};

extern enum operating_system os_mode;
