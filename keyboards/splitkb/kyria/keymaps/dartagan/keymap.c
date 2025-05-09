/* Copyright 2019 Thomas Baart <thomas@splitkb.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include QMK_KEYBOARD_H

enum layers { _BASE = 0, _NAV, _SYM, _SYM_NEW, _GAME };

// Aliases for readability

#define NAV MO(_NAV)
#define SYM MO(_SYM)
#define SYM_NEW TG(_SYM_NEW)
#define GAME TG(_GAME)

#define ESC_CTL MT(MOD_LCTL, KC_ESC)
#define CTL_QUOT MT(MOD_RCTL, KC_QUOTE)
#define CTL_MINS MT(MOD_RCTL, KC_MINUS)
#define ALT_ENT MT(MOD_LALT, KC_ENT)
// Note: LAlt/Enter (ALT_ENT) is not the same thing as the keyboard shortcut Alt+Enter.
// The notation `mod/tap` denotes a key that activates the modifier `mod` when held down, and
// produces the key `tap` when tapped (i.e. pressed and released).

// Note: disabled combos.  Re-enable in rules.mk if desired.
// Holding both FKEYS and SYM keys activates the Nav layer
// Holding both Tab and Backspace keys toggles the Game layer
//const uint16_t PROGMEM fkeys_sym_combo[] = {FKEYS, SYM, COMBO_END};
//const uint16_t PROGMEM tab_bksp_combo[] = {KC_TAB, KC_BSPC, COMBO_END};

// It seems like Vial doesn't support manually defined combos, only ones done in the GUI
// Update `VIAL_COMBO_ENTRIES` in `config.h` to equal the number of combos here
//combo_t key_combos[COMBO_COUNT] = {
//    //COMBO(fkeys_sym_combo, NAV),
//    COMBO(tab_bksp_combo, GAME),
//};
// TODO: compare to tri-state layer https://docs.splitkb.com/hc/en-us/articles/360018614379-Using-tri-state-layers

// clang-format off
#define LAYOUT_via( \
    L00, L01, L02, L03, L04, L05, LE0, LE1, RE0, RE1, R06, R07, R08, R09, R10, R11, \
    L12, L13, L14, L15, L16, L17,                     R18, R19, R20, R21, R22, R23, \
    L24, L25, L26, L27, L28, L29, L30, L31, R32, R33, R34, R35, R36, R37, R38, R39, \
                   L40, L41, L42, L43, L44, R45, R46, R47, R48, R49 \
) \
{ \
    { LE0,   LE1,   L05,   L04,   L03,   L02,   L01,   L00   }, \
    { RE0,   RE1,   L17,   L16,   L15,   L14,   L13,   L12   }, \
    { L31,   L30,   L29,   L28,   L27,   L26,   L25,   L24   }, \
    { L44,   L43,   L42,   L41,   L40,   KC_NO, KC_NO, KC_NO }, \
    { KC_NO, KC_NO, R06,   R07,   R08,   R09,   R10,   R11   }, \
    { KC_NO, KC_NO, R18,   R19,   R20,   R21,   R22,   R23   }, \
    { R32,   R33,   R34,   R35,   R36,   R37,   R38,   R39   }, \
    { R45,   R46,   R47,   R48,   R49,   KC_NO, KC_NO, KC_NO }, \
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/*
 * Base Layer: QWERTY
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |  Tab   |   Q  |   W  |   E  |   R  |   T  |                              |   Y  |   U  |   I  |   O  |   P  |  Bksp  |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |Esc/Ctrl|   A  |   S  |   D  |   F  |   G  |                              |   H  |   J  |   K  |   L  | ;  : |  '  "  |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * | LShift |   Z  |   X  |   C  |   V  |   B  | [ {  |CapsLk|  |      |  ] } |   N  |   M  | ,  < | . >  | /  ? | RShift |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        |      | LGUI | Nav  |LAlt/ |      |  |      | Space| Sym  | RCtrl|      |
 *                        |      |      |      |Enter |      |  |      |      |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
    [_BASE] = LAYOUT_via(
     KC_TAB  , KC_Q ,  KC_W   ,  KC_E  ,   KC_R ,   KC_T , _______, _______,   _______, _______,  KC_Y,   KC_U ,  KC_I ,   KC_O ,  KC_P , KC_BSPC,
     ESC_CTL , KC_A ,  KC_S   ,  KC_D  ,   KC_F ,   KC_G ,                                        KC_H,   KC_J ,  KC_K ,   KC_L ,KC_SCLN, KC_QUOTE,
     KC_LSFT , KC_Z ,  KC_X   ,  KC_C  ,   KC_V ,   KC_B , KC_LBRC,KC_CAPS,    _______, KC_RBRC, KC_N,   KC_M ,KC_COMM, KC_DOT ,KC_SLSH, KC_RSFT,
                                 KC_NO , KC_LGUI,   NAV  , ALT_ENT,  KC_NO,        KC_NO, KC_SPC, SYM , KC_RCTL, KC_NO
    ),


/*
 * Nav Layer: Media, navigation
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |        |  F9  | F10  | F11  | F12  |      |                              | Home | PgDn | PgUp | End  | VolUp| Delete |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |        |  F5  |  F6  |  F7  |  F8  |      |                              |  ←   |  ↓   |  ↑   |  →   | VolDn|  Bksp  |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * |        |  F1  |  F2  |  F3  |  F4  |      |      |      |  | GAME |      |      |M Prev|M Play|M Next|VolMut|        |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
      //_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_PGUP, KC_HOME, KC_UP,   KC_END,  KC_VOLU, KC_DEL,
      //_______, KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT, _______,                                     KC_PGDN, KC_LEFT, KC_DOWN, KC_RGHT, KC_VOLD, KC_INS,

    [_NAV] = LAYOUT_via(
      _______, KC_F9 ,  KC_F10,  KC_F11,  KC_F12, _______, _______, _______, _______, _______, KC_HOME, KC_PGDN, KC_PGUP, KC_END,  KC_VOLU, KC_DEL,
      _______, KC_F5 ,  KC_F6 ,  KC_F7 ,  KC_F8 , _______,                                     KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_VOLD, KC_BSPC,
      _______, KC_F1 ,  KC_F2 ,  KC_F3 ,  KC_F4 , _______, _______, _______,    GAME, _______, _______, KC_MPRV, KC_MPLY, KC_MNXT, KC_MUTE, _______,
                                _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    ),

/*
 * Sym Layer: Numbers and symbols
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |    `   |  1   |  2   |  3   |  4   |  5   |                              |   6  |  7   |  8   |  9   |  0   |  Bksp  |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |    ~   |  !   |  @   |  #   |  $   |  %   |                              |   ^  |  &   |  *   |  (   |  )   |   =    |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * |    |   |   \  |  [   |  ]   |  -   |  {   | [ {  |      |  |SYM_NEW| ] } |   }  |  _   |  ,   |  .   |  /   |   +    |
 * `----------------------+------+------+------+------+------|  |-------+-----+------+------+------+----------------------'
 *                        |      |      |      |      |      |  |       |     |      |      |      |
 *                        |      |      |      |      |      |  |       |     |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
    [_SYM] = LAYOUT_via(
      KC_GRV ,   KC_1 ,   KC_2 ,   KC_3 ,   KC_4 ,   KC_5 , _______, _______, _______, _______, KC_6 ,   KC_7 ,   KC_8 ,   KC_9 ,   KC_0 , KC_BSPC ,
     KC_TILD , KC_EXLM,  KC_AT , KC_HASH,  KC_DLR, KC_PERC,                                     KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_EQL,
     KC_PIPE , KC_BSLS, KC_LBRC, KC_RBRC, KC_MINS, KC_LCBR, KC_LBRC, _______, SYM_NEW, KC_RBRC, KC_RCBR, KC_UNDS, KC_COMM,  KC_DOT, KC_SLSH, KC_PLUS,
                                 _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    ),

/*
 * NEW Sym Layer: Numbers and symbols
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |   Tab  |  !   |  @   |  #   |  $   |  [   |                              |   ]  |  7   |  8   |  9   |  0   |  Bksp  |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |    `   |  %   |  &   |  *   |  -   |  (   |                              |   )  |  4   |  5   |  6   |  .   |   =    |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * |    ~   |  \   |  |   |  ^   |  _   |  {   |      |      |  |SYM_NEW|     |   }  |  1   |  2   |  3   |  /   |   +    |
 * `----------------------+------+------+------+------+------|  |-------+-----+------+------+------+----------------------'
 *                        |      |      |      |      |      |  |       |     |      |      |      |
 *                        |      |      |      |      |      |  |       |     |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
    [_SYM_NEW] = LAYOUT_via(
      KC_TAB, KC_EXLM, KC_AT,   KC_HASH,  KC_DLR, KC_LBRC, _______, _______, _______, _______, KC_RBRC, KC_7, KC_8, KC_9, KC_0, KC_BSPC,
      KC_GRV, KC_PERC, KC_AMPR, KC_ASTR, KC_MINS, KC_LPRN,                                     KC_RPRN, KC_4, KC_5, KC_6, KC_DOT,    KC_EQL,
     KC_TILD, KC_BSLS, KC_PIPE, KC_CIRC, KC_UNDS, KC_LCBR, _______, _______, SYM_NEW, _______, KC_RCBR, KC_1, KC_2, KC_3, KC_SLSH,  KC_PLUS,
                                _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    ),


/*
 * GAME Layer: Optimized for hand position while playing WASD games
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |  Tab   |      |  Q   |  W   |  E   |  R   |                              |  T   |  7   |  8   |  9   |  0   | Bksp   |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |  Esc   |LShift|  A   |  S   |  D   |  F   |                              |  G   |  4   |  5   |  6   |      |        |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * | LShift |LCtrl |  Z   |  X   |  C   |  V   | M    |      |  | GAME |      |  B   |  1   |  2   |  3   |      |        |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        |      | LAlt |LCtrl |Space |      |  |      |      |      |      |      |
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
    [_GAME] = LAYOUT_via(
      KC_TAB,  _______, KC_Q,    KC_W,    KC_E,    KC_R, _______, _______, _______, _______,    KC_T,    KC_7,    KC_8,   KC_9,    KC_0, KC_BSPC,
      KC_ESC,  KC_LSFT, KC_A,    KC_S,    KC_D,    KC_F,                                        KC_G,    KC_4,    KC_5,   KC_6, _______, _______,
      KC_LSFT, KC_LCTL, KC_Z,    KC_X,    KC_C,    KC_V,    KC_M, _______,    GAME, _______,    KC_B,    KC_1,    KC_2,   KC_3, _______, _______,
                              _______, KC_LALT, KC_LCTL,  KC_SPC, _______, _______, _______, _______, _______, _______
    ),
};
// clang-format on

#ifdef ENCODER_ENABLE
static uint8_t  encoder_state[2] = {0};
static keypos_t encoder_ccw[2]   = {{0, 0}, {0, 1}};
static keypos_t encoder_cw[2]    = {{1, 0}, {1, 1}};

void encoder_action_unregister(void) {
    for (int index = 0; index < 2; ++index) {
        if (encoder_state[index]) {
            keyevent_t encoder_event = (keyevent_t){.key = encoder_state[index] >> 1 ? encoder_cw[index] : encoder_ccw[index], .pressed = false, .time = (timer_read() | 1)};
            encoder_state[index]     = 0;
            action_exec(encoder_event);
        }
    }
}

void encoder_action_register(uint8_t index, bool clockwise) {
    keyevent_t encoder_event = (keyevent_t){.key = clockwise ? encoder_cw[index] : encoder_ccw[index], .pressed = true, .time = (timer_read() | 1)};
    encoder_state[index]     = (clockwise ^ 1) | (clockwise << 1);
    action_exec(encoder_event);
}

void matrix_scan_user(void) { encoder_action_unregister(); }

bool encoder_update_user(uint8_t index, bool clockwise) {
    encoder_action_register(index, clockwise);
    return false;
};
#endif

#ifdef RGBLIGHT_ENABLE
//const rgblight_segment_t PROGMEM rgb_base_layer[] = RGBLIGHT_LAYER_SEGMENTS(
//    {1, 4, HSV_GREEN},       // Light 4 LEDs, starting with LED 6
//    {6, 10, HSV_GREEN}       // Light 4 LEDs, starting with LED 12
//);
//
//const rgblight_segment_t PROGMEM rgb_game_layer[] = RGBLIGHT_LAYER_SEGMENTS(
//    {1, 4, HSV_CYAN},       // Light 4 LEDs, starting with LED 6
//    {6, 10, HSV_CYAN}       // Light 4 LEDs, starting with LED 12
//);
//
//const rgblight_segment_t* const PROGMEM rgb_layers[] = RGBLIGHT_LAYERS_LIST(
//    rgb_base_layer,
//    rgb_game_layer
//);

const rgblight_segment_t PROGMEM rgb_base_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 10, HSV_RED},       // Light 10 LEDs, starting with LED 0
    {10, 10, HSV_RED}
);

const rgblight_segment_t PROGMEM rgb_sym_new_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 10, HSV_CYAN},       // Light 10 LEDs, starting with LED 0
    {10, 10, HSV_CYAN}
);

const rgblight_segment_t PROGMEM rgb_game_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 10, HSV_GREEN},       // Light 10 LEDs, starting with LED 0
    {10, 10, HSV_GREEN}
);

const rgblight_segment_t* const PROGMEM rgb_layers[] = RGBLIGHT_LAYERS_LIST(
    rgb_base_layer,
    rgb_sym_new_layer,
    rgb_game_layer
);

void keyboard_post_init_user(void) {
    rgblight_layers = rgb_layers;
}

//bool led_update_user(led_t led_state) {
//    rgblight_set_layer_state(1, led_state.caps_lock);
//    return true;
//}

layer_state_t default_layer_state_set_user(layer_state_t state) {
    rgblight_set_layer_state(0, layer_state_cmp(state, _BASE));
    return state;
}

layer_state_t layer_state_set_user(layer_state_t state) {
    rgblight_set_layer_state(1, layer_state_cmp(state, _SYM_NEW));
    rgblight_set_layer_state(2, layer_state_cmp(state, _GAME));
    return state;
}
#endif

#ifdef OLED_ENABLE
bool oled_task_user(void) {
    if (is_keyboard_master()) {
        // QMK Logo and version information
        // clang-format off
        static const char PROGMEM qmk_logo[] = {
            0x80,0x81,0x82,0x83,0x84,0x85,0x86,0x87,0x88,0x89,0x8a,0x8b,0x8c,0x8d,0x8e,0x8f,0x90,0x91,0x92,0x93,0x94,
            0xa0,0xa1,0xa2,0xa3,0xa4,0xa5,0xa6,0xa7,0xa8,0xa9,0xaa,0xab,0xac,0xad,0xae,0xaf,0xb0,0xb1,0xb2,0xb3,0xb4,
            0xc0,0xc1,0xc2,0xc3,0xc4,0xc5,0xc6,0xc7,0xc8,0xc9,0xca,0xcb,0xcc,0xcd,0xce,0xcf,0xd0,0xd1,0xd2,0xd3,0xd4,0};
        // clang-format on

        oled_write_P(qmk_logo, false);
        oled_write_P(PSTR("Kyria rev1.0 w/ VIA\n\n"), false);

        // Host Keyboard Layer Status
        oled_write_P(PSTR("Layer: "), false);
        switch (get_highest_layer(layer_state | default_layer_state)) {
            case 0:
                oled_write_P(PSTR("Base\n"), false);
                break;
            case 1:
                oled_write_P(PSTR("Nav\n"), false);
                break;
            case 2:
                oled_write_P(PSTR("Sym\n"), false);
                break;
            case 3:
                oled_write_P(PSTR("New Sym\n"), false);
                break;
            case 4:
                oled_write_P(PSTR("Game\n"), false);
                break;
        }

        // Host Keyboard LED Status
        led_t led_usb_state = host_keyboard_led_state();
        oled_write_P(led_usb_state.num_lock ? PSTR("NUMLCK ") : PSTR("       "), false);
        oled_write_P(led_usb_state.caps_lock ? PSTR("CAPLCK ") : PSTR("       "), false);
        oled_write_P(led_usb_state.scroll_lock ? PSTR("SCRLCK ") : PSTR("       "), false);
    } else {
        // clang-format off
        static const char PROGMEM kyria_logo[] = {
            0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,128,128,192,224,240,112,120, 56, 60, 28, 30, 14, 14, 14,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7, 14, 14, 14, 30, 28, 60, 56,120,112,240,224,192,128,128,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
            0,  0,  0,  0,  0,  0,  0,192,224,240,124, 62, 31, 15,  7,  3,  1,128,192,224,240,120, 56, 60, 28, 30, 14, 14,  7,  7,135,231,127, 31,255,255, 31,127,231,135,  7,  7, 14, 14, 30, 28, 60, 56,120,240,224,192,128,  1,  3,  7, 15, 31, 62,124,240,224,192,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
            0,  0,  0,  0,240,252,255, 31,  7,  1,  0,  0,192,240,252,254,255,247,243,177,176, 48, 48, 48, 48, 48, 48, 48,120,254,135,  1,  0,  0,255,255,  0,  0,  1,135,254,120, 48, 48, 48, 48, 48, 48, 48,176,177,243,247,255,254,252,240,192,  0,  0,  1,  7, 31,255,252,240,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
            0,  0,  0,255,255,255,  0,  0,  0,  0,  0,254,255,255,  1,  1,  7, 30,120,225,129,131,131,134,134,140,140,152,152,177,183,254,248,224,255,255,224,248,254,183,177,152,152,140,140,134,134,131,131,129,225,120, 30,  7,  1,  1,255,255,254,  0,  0,  0,  0,  0,255,255,255,  0,  0,  0,  0,255,255,  0,  0,192,192, 48, 48,  0,  0,240,240,  0,  0,  0,  0,  0,  0,240,240,  0,  0,240,240,192,192, 48, 48, 48, 48,192,192,  0,  0, 48, 48,243,243,  0,  0,  0,  0,  0,  0, 48, 48, 48, 48, 48, 48,192,192,  0,  0,  0,  0,  0,
            0,  0,  0,255,255,255,  0,  0,  0,  0,  0,127,255,255,128,128,224,120, 30,135,129,193,193, 97, 97, 49, 49, 25, 25,141,237,127, 31,  7,255,255,  7, 31,127,237,141, 25, 25, 49, 49, 97, 97,193,193,129,135, 30,120,224,128,128,255,255,127,  0,  0,  0,  0,  0,255,255,255,  0,  0,  0,  0, 63, 63,  3,  3, 12, 12, 48, 48,  0,  0,  0,  0, 51, 51, 51, 51, 51, 51, 15, 15,  0,  0, 63, 63,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 48, 48, 63, 63, 48, 48,  0,  0, 12, 12, 51, 51, 51, 51, 51, 51, 63, 63,  0,  0,  0,  0,  0,
            0,  0,  0,  0, 15, 63,255,248,224,128,  0,  0,  3, 15, 63,127,255,239,207,141, 13, 12, 12, 12, 12, 12, 12, 12, 30,127,225,128,  0,  0,255,255,  0,  0,128,225,127, 30, 12, 12, 12, 12, 12, 12, 12, 13,141,207,239,255,127, 63, 15,  3,  0,  0,128,224,248,255, 63, 15,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
            0,  0,  0,  0,  0,  0,  0,  3,  7, 15, 62,124,248,240,224,192,128,  1,  3,  7, 15, 30, 28, 60, 56,120,112,112,224,224,225,231,254,248,255,255,248,254,231,225,224,224,112,112,120, 56, 60, 28, 30, 15,  7,  3,  1,128,192,224,240,248,124, 62, 15,  7,  3,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
            0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  1,  3,  7, 15, 14, 30, 28, 60, 56,120,112,112,112,224,224,224,224,224,224,224,224,224,224,224,224,224,224,224,224,112,112,112,120, 56, 60, 28, 30, 14, 15,  7,  3,  1,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0
        };
        // clang-format on
        oled_write_raw_P(kyria_logo, sizeof(kyria_logo));
    }
    return false;
}
#endif
