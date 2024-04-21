#include QMK_KEYBOARD_H

#define MODS_SHIFT_MASK  (MOD_BIT(KC_LSFT)|MOD_BIT(KC_RSFT))
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
    WIN = SAFE_RANGE,
    LINUX,
    KX_AE,      //Ä: U+00C4/ALT+142     ä: U+00E4/ALT+132
    KX_OE,      //Ö: U+00D6/ALT+153     ö: U+00F6/ALT+148
    KX_UE,      //Ü: U+00DC/ALT+154     ü: U+00FC/ALT+129
    KX_SS,      //ẞ: U+1E9E/ALT+7838    ß: U+00DF/ALT+225
    KX_EURO     //€: U+20AC/ALT+0128
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

enum operating_systems {
    windows = 0,
    linux = 1
};

enum operating_systems os_mode = windows;



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
        KC_LCTL, KC_A   , KC_S   , KC_D   , KC_F   , KC_G   ,                   KC_H   , KC_J   , KC_K   , KC_L   , KC_SCLN, KC_QUOT,
        KC_LSFT, KC_Z   , KC_X   , KC_C   , KC_V   , KC_B   , XXXXXXX, XXXXXXX, KC_N   , KC_M   , KC_COMM, KC_DOT , KC_SLSH, KC_RSFT,
                          KC_LALT, KC_LGUI, MO(1)  , KC_SPC ,                   KC_ENT , MO(2)  , KC_BSPC, KC_RALT
    ),
    [_FUN1] = LAYOUT( // FN Layer 1: Arrows, Home/End/Page, Umlauts, F-Keys
        KC_F1  , KC_F2  , KC_F3  , KC_F4  , KC_F5  , KC_F6  ,                   KC_F7  , KC_F8  , KC_F9  , KC_F10 , KC_F11 , KC_F12,
        _______, _______, _______, KX_EURO, _______, _______,                   _______, KX_UE  , _______, KX_OE  , KC_LBRC, KC_RBRC,
        KC_GRV , KX_AE  , KX_SS  , KC_MPRV, KC_MNXT, KC_MPLY,                   KC_CIRC, KC_LEFT, KC_DOWN, KC_UP  , KC_RGHT, KC_BSLS,
        _______, _______, _______, _______, _______, _______, XXXXXXX, XXXXXXX, XXXXXXX, KC_HOME, KC_PGDN, KC_PGUP, KC_END , XXXXXXX,
                          _______, _______, _______, _______,                   _______, MO(3)  , KC_DEL , _______
    ),
    [_FUN2] = LAYOUT( // FN Layer 2: -- tbd -- (maybe numpad keys in 3x3 square on left?)
        KC_GRV , KC_1   , KC_2   , KC_3   , KC_4   , KC_5   ,                   _______, _______, _______, _______, _______, _______,
        _______, KC_6   , KC_7   , KC_8   , KC_9   , KC_0   ,                   _______, _______, _______, _______, _______, _______,
        KC_F1  , KC_F2  , KC_F3  , KC_F4  , KC_F5  , KC_F6  ,                   XXXXXXX, KC_LEFT, KC_DOWN, KC_UP  , KC_RGHT, XXXXXXX,
        KC_F7  , KC_F8  , KC_F9  , KC_F10 , KC_F11 , KC_F12 , XXXXXXX, XXXXXXX, KC_PLUS, KC_MINS, KC_EQL , KC_LBRC, KC_RBRC, KC_BSLS,
                          _______, _______, MO(3)  , _______,                   _______, _______, _______, _______
    ),
    [_OPTS] = LAYOUT( // Options Layer: Lighting & OS Control
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX, RGB_TOG, RGB_HUI, RGB_SAI, RGB_VAI,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, RGB_MOD, RGB_HUD, RGB_SAD, RGB_VAD,
                          _______, _______, _______, _______,                   _______, _______, _______, _______)
};

// TODO: LSFT + RSFT = CAPS
// TODO: Encoder Left
// TODO: Encoder Right
//      - Press: Switch Functionality
//      - Think about different functionalities
// TODO: Copy & adapt underglow
// TODO: Set up backlight & options
// TODO: Set up left-dominant gaming layer

#if defined(ENCODER_ENABLE) && defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {

};
#endif // defined(ENCODER_ENABLE) && defined(ENCODER_MAP_ENABLE)

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
        register_code(KC_NUM);
        unregister_code(KC_NUM);
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
