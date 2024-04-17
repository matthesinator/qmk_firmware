#include QMK_KEYBOARD_H

#define MODS_SHIFT_MASK  (MOD_BIT(KC_LSFT)|MOD_BIT(KC_RSFT))
#define SHIFTED get_mods()&MODS_SHIFT_MASK
#define CAPS_ON host_keyboard_led_state().caps_lock
#define NUM_LOCK_ON host_keyboard_led_state().num_lock

#define _BSE 0  // Base layer
#define _GM 1   // Gaming Layer
#define _FN 2   // Function layer
#define _OPT 3  // Options layer
#define _QS 4   // Quicksettings layer

#define BLINK_SPEED 100
#define BLINK_REPEATS 3

/**********************************************************/
/*                         LAYOUT                         */
/**********************************************************/

/*
 * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───────┐
 * │00 │01 │02 │03 │04 │05 │06 │07 │08 │09 │0a │0b │0c │0e     │
 * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─────┤
 * │10   │12 │13 │14 │15 │16 │17 │18 │19 │1a │1b │1c │1d │1e   │
 * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴─────┤
 * │20    │22 │23 │24 │25 │26 │27 │28 │29 │2a │2b │2c │2d      │
 * ├──────┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴────┬───┤
 * │30      │32 │33 │34 │35 │36 │37 │38 │39 │3a │3b │3d    │3e │
 * ├────┬───┴┬──┴─┬─┴───┴───┴┬──┴─┬─┴───┴──┬┴──┬┴──┬┴──┬───┤───┤
 * │40  │41  │43  │44        │46  │48      │4a │4b │4c │4d │4e │
 * └────┴────┴────┴──────────┴────┴────────┴───┴───┴───┴───┴───┘
*/
#define LAYOUT_matthesinator( \
    k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, k0c,      k0e, \
    k10,      k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c, k1d, k1e, \
    k20,      k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b, k2c, k2d,      \
    k30,      k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b,      k3d, k3e, \
    k40, k41,      k43, k44,      k46,      k48,      k4a, k4b, k4c, k4d, k4e  \
) { \
    { k00,  k01,   k02,   k03,  k04,   k05,   k06,  k07,   k08,   k09,   k0a,  k0b,  k0c,   KC_NO, k0e   }, \
    { k10,  KC_NO, k12,   k13,  k14,   k15,   k16,  k17,   k18,   k19,   k1a,  k1b,  k1c,   k1d,   k1e   }, \
    { k20,  KC_NO, k22,   k23,  k24,   k25,   k26,  k27,   k28,   k29,   k2a,  k2b,  k2c,   k2d,   KC_NO }, \
    { k30,  KC_NO, k32,   k33,  k34,   k35,   k36,  k37,   k38,   k39,   k3a,  k3b,  KC_NO, k3d,   k3e   }, \
    { k40,  k41,   KC_NO, k43,  k44,   KC_NO, k46,  KC_NO, k48,   KC_NO, k4a,  k4b,  k4c,   k4d,   k4e   }  \
}

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


/**********************************************************/
/*                         LAYERS                         */
/**********************************************************/

/* Empty layer for copying
[name] = LAYOUT_matthesinator(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______,                   _______, _______, _______,          _______, _______, _______, _______, _______
    )
*/

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    // 0: Base Layer
    [_BSE] = LAYOUT_matthesinator(
        QK_GESC, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,     KC_MINS, KC_EQL,   KC_BSPC,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,     KC_LBRC, KC_RBRC,  KC_BSLS,
        KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN,  KC_QUOT,           KC_ENT,
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,  KC_RSFT, KC_DEL,
        KC_LCTL, KC_LGUI, KC_LALT,                KC_BSPC,    MO(_FN), KC_SPC,           KC_RALT, OSL(_QS), TO(_GM), TO(_OPT), KC_RCTL
    ),

    // 1: Gaming Layer
    [_GM] = LAYOUT_matthesinator(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______,                    KC_SPC, MO(_FN), KC_SPC,           _______, _______, KC_PGDN, KC_PGUP, _______
    ),

    // 2: Mod Layer: Arrows, Fn Keys, Umlauts
    [_FN] = LAYOUT_matthesinator(
        KC_GRV,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_BSPC,
        _______, _______, _______, KX_EURO, _______, _______, _______, KX_UE,   _______, KX_OE,   KC_PSCR, _______, _______, _______,
        _______, KX_AE,   KX_SS,   KC_VOLD, KC_VOLU, KC_MUTE, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, _______, _______,          _______,
        _______, _______, _______, KC_MPRV, KC_MNXT, KC_MPLY, KC_HOME, KC_END,  _______, _______, _______, _______, _______,
        _______, _______, _______,                   _______, _______, _______,          _______, TO(_BSE), _______, _______, _______
    ),

    // 4: Keyboard Options, Keyboard Lighting
    [_OPT] = LAYOUT_matthesinator(
        TO(_BSE), RGB_M_P, RGB_M_B, RGB_M_R, RGB_M_SW, RGB_M_SN, RGB_M_K, RGB_M_X, RGB_M_G, RGB_M_T, _______, _______, _______, _______,
        _______,  RGB_TOG, RGB_HUI, RGB_SAI, RGB_VAI,  _______,  _______, _______, _______, _______, _______, _______, _______, QK_REBOOT,
        _______,  RGB_SPI, _______, _______, _______,  _______,  _______, KC_BRIU, KC_BRID, _______, _______, _______,          _______,
        _______,  _______, _______, _______, _______,  _______,  _______, _______, _______, _______, _______, _______, _______,
            WIN,  _______, _______,                    _______,  TO(_BSE),_______,          _______, _______, KC_NO,  TO(_BSE), LINUX
    ),

    // 5: Quicksettings
    [_QS] = LAYOUT_matthesinator(
        TO(_BSE), WIN,    LINUX,   _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, RGB_TOG, _______, _______,          _______,
        _______, _______, _______, _______, _______, _______, KC_NUM,  _______, _______, _______, _______, _______, _______,
        _______, _______, _______,                   _______, TO(_BSE),_______,          _______, KC_NO,   KC_NO,   KC_NO,   _______
    )
};



/**********************************************************/
/*                    LIGHTING: LAYERS                    */
/**********************************************************/

const rgblight_segment_t PROGMEM gaming_layer[] = RGBLIGHT_LAYER_SEGMENTS (
    {0, 1, HSV_PURPLE},
    {7, 2, HSV_PURPLE},
    {15, 1, HSV_PURPLE}
);

const rgblight_segment_t PROGMEM options_layer[] = RGBLIGHT_LAYER_SEGMENTS (
    {10, 1, HSV_OFF},
    {11, 1, HSV_RED},
    {12, 1, HSV_WHITE},
    {13, 1, HSV_OFF}
);

const rgblight_segment_t PROGMEM qs_layer[] = RGBLIGHT_LAYER_SEGMENTS (
    {10, 1, HSV_OFF},
    {11, 1, HSV_WHITE},
    {12, 1, HSV_RED},
    {13, 1, HSV_OFF}
);

const rgblight_segment_t PROGMEM windows_layer[] = RGBLIGHT_LAYER_SEGMENTS (
    {0, 16, HSV_BLUE}
);

const rgblight_segment_t PROGMEM linux_layer[] = RGBLIGHT_LAYER_SEGMENTS (
    {0, 16, HSV_ORANGE}
);

const rgblight_segment_t* const PROGMEM my_rgb_layers[] = RGBLIGHT_LAYERS_LIST (
    gaming_layer,
    options_layer,
    qs_layer,
    windows_layer,
    linux_layer
);



/**********************************************************/
/*                 LIGHTING: FUNCTIONALITY                */
/**********************************************************/

/*
    Disables all lighting layers.
*/
void disable_lighting_layers (void) {
    rgblight_set_layer_state(0, false);
    rgblight_set_layer_state(1, false);
    rgblight_set_layer_state(2, false);
}

/*
    Enables the given lighting layer and disables all other layers.
*/
void set_lighting_layer (int index) {
    rgblight_set_layer_state(index, true);
    rgblight_set_layer_state(0, index == 0);
    rgblight_set_layer_state(1, index == 1);
    rgblight_set_layer_state(2, index == 2);
}

/*
    Called when the layer state changes. Finds out the highest layer and sets the lighting layers
    accordingly.
*/
layer_state_t layer_state_set_user (layer_state_t state) {
    switch (get_highest_layer(state)) {
        case _BSE:
            disable_lighting_layers();
            break;
        case _FN:
            disable_lighting_layers();
            break;
        case _GM:
            set_lighting_layer(0);
            break;
        case _OPT:
            set_lighting_layer(1);
            break;
        case _QS:
            set_lighting_layer(2);
            break;
    }
    return state;
}



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
        case 0: // windows
            send_alt_code(character.alt_code_sequence);
            break;
        case 1: // linux
            send_unicode(character.unicode_sequence);
            break;
    }
}

/*
    Called whenever a key is pressed or released. Handles OS switches and delegates to other
    functions to send special characters.
*/
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        switch (keycode) {
            case WIN:
                os_mode = 0;
                rgblight_blink_layer_repeat(3, BLINK_SPEED, BLINK_REPEATS);
                return false;
                break;
            case LINUX:
                os_mode = 1;
                rgblight_blink_layer_repeat(4, BLINK_SPEED, BLINK_REPEATS);
                return false;
                break;
            case KX_AE:
            case KX_OE:
            case KX_UE:
            case KX_SS:
            case KX_EURO:
                send_special_character(keycode);
                return false;
                break;
            default:
                return true;
                break;
        }
    }
    return true;
}



/**********************************************************/
/*                  SETUPS AND DEFAULTS                   */
/**********************************************************/

// void led_set_keymap(uint8_t usb_led) {
//     if (!(usb_led & (1<<USB_LED_NUM_LOCK))) {
//         register_code(KC_NUM);
//         unregister_code(KC_NUM);
//     }
// }

void keyboard_post_init_user(void) {
    rgblight_layers = my_rgb_layers;
}
