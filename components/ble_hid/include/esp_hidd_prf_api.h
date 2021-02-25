// Copyright 2017-2018 Espressif Systems (Shanghai) PTE LTD
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at

//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#ifndef __ESP_HIDD_API_H__
#define __ESP_HIDD_API_H__

#include "esp_bt_defs.h"
#include "esp_gatt_defs.h"
#include "esp_err.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    ESP_HIDD_EVENT_REG_FINISH = 0,
    ESP_BAT_EVENT_REG,
    ESP_HIDD_EVENT_DEINIT_FINISH,
    ESP_HIDD_EVENT_BLE_CONNECT,
    ESP_HIDD_EVENT_BLE_DISCONNECT,
    ESP_HIDD_EVENT_BLE_VENDOR_REPORT_WRITE_EVT,
} esp_hidd_cb_event_t;

/// HID config status
typedef enum {
    ESP_HIDD_STA_CONN_SUCCESS = 0x00,
    ESP_HIDD_STA_CONN_FAIL    = 0x01,
} esp_hidd_sta_conn_state_t;

/// HID init status
typedef enum {
    ESP_HIDD_INIT_OK = 0,
    ESP_HIDD_INIT_FAILED = 1,
} esp_hidd_init_state_t;

/// HID deinit status
typedef enum {
    ESP_HIDD_DEINIT_OK = 0,
    ESP_HIDD_DEINIT_FAILED = 0,
} esp_hidd_deinit_state_t;

#define LEFT_CONTROL_KEY_MASK        (1 << 0)
#define LEFT_SHIFT_KEY_MASK          (1 << 1)
#define LEFT_ALT_KEY_MASK            (1 << 2)
#define LEFT_GUI_KEY_MASK            (1 << 3)
#define RIGHT_CONTROL_KEY_MASK       (1 << 4)
#define RIGHT_SHIFT_KEY_MASK         (1 << 5)
#define RIGHT_ALT_KEY_MASK           (1 << 6)
#define RIGHT_GUI_KEY_MASK           (1 << 7)

typedef uint8_t key_mask_t;

#define Keyboard_a                4   // Keyboard a and A
#define Keyboard_b                5   // Keyboard b and B
#define Keyboard_c                6   // Keyboard c and C
#define Keyboard_d                7   // Keyboard d and D
#define Keyboard_e                8   // Keyboard e and E
#define Keyboard_f                9   // Keyboard f and F
#define Keyboard_g                10  // Keyboard g and G
#define Keyboard_h                11  // Keyboard h and H
#define Keyboard_i                12  // Keyboard i and I
#define Keyboard_j                13  // Keyboard j and J
#define Keyboard_k                14  // Keyboard k and K
#define Keyboard_l                15  // Keyboard l and L
#define Keyboard_m                16  // Keyboard m and M
#define Keyboard_n                17  // Keyboard n and N
#define Keyboard_o                18  // Keyboard o and O
#define Keyboard_p                19  // Keyboard p and P
#define Keyboard_q                20  // Keyboard q and Q
#define Keyboard_r                21  // Keyboard r and R
#define Keyboard_s                22  // Keyboard s and S
#define Keyboard_t                23  // Keyboard t and T
#define Keyboard_u                24  // Keyboard u and U
#define Keyboard_v                25  // Keyboard v and V
#define Keyboard_w                26  // Keyboard w and W
#define Keyboard_x                27  // Keyboard x and X
#define Keyboard_y                28  // Keyboard y and Y
#define Keyboard_z                29  // Keyboard z and Z
#define Keyboard_1                30  // Keyboard 1 and !
#define Keyboard_2                31  // Keyboard 2 and @
#define Keyboard_3                32  // Keyboard 3 and #
#define Keyboard_4                33  // Keyboard 4 and $
#define Keyboard_5                34  // Keyboard 5 and %
#define Keyboard_6                35  // Keyboard 6 and ^
#define Keyboard_7                36  // Keyboard 7 and &
#define Keyboard_8                37  // Keyboard 8 and *
#define Keyboard_9                38  // Keyboard 9 and (
#define Keyboard_0                39  // Keyboard 0 and )
#define Keyboard_ENTER            40  // Keyboard ENTER
#define Keyboard_ESCAPE           41  // Keyboard ESCAPE
#define Keyboard_Backspace        42  // Keyboard Backspace
#define Keyboard_Tab              43  // Keyboard Tab
#define Keyboard_KongGe           44  // Keyboard Spacebar
#define Keyboard_JianHao          45  // Keyboard - and _(underscore)
#define Keyboard_DengHao          46  // Keyboard = and +
#define Keyboard_ZuoZhongKuoHao   47  // Keyboard [ and {
#define Keyboard_YouZhongKuoHao   48  // Keyboard ] and }
#define Keyboard_FanXieGang       49  // Keyboard \ and |
#define Keyboard_FenHao           51  // Keyboard ; and :
#define Keyboard_DanYinHao        52  // Keyboard ‘ and “
#define Keyboard_BoLangXian       53  // Keyboard `(Grave Accent) and ~(Tilde)
#define Keyboard_Douhao           54  // Keyboard, and <
#define Keyboard_JuHao            55  // Keyboard . and >
#define Keyboard_XieGang_WenHao   56  // Keyboard / and ?
#define Keyboard_CapsLock         57  // Keyboard Caps Lock
#define Keyboard_F1               58  // Keyboard F1
#define Keyboard_F2               59  // Keyboard F2
#define Keyboard_F3               60  // Keyboard F3
#define Keyboard_F4               61  // Keyboard F4
#define Keyboard_F5               62  // Keyboard F5
#define Keyboard_F6               63  // Keyboard F6
#define Keyboard_F7               64  // Keyboard F7
#define Keyboard_F8               65  // Keyboard F8
#define Keyboard_F9               66  // Keyboard F9
#define Keyboard_F10              67  // Keyboard F10
#define Keyboard_F11              68  // Keyboard F11
#define Keyboard_F12              69  // Keyboard F12
#define Keyboard_PrintScreen      70  // Keyboard PrintScreen
#define Keyboard_ScrollLock       71  // Keyboard Scroll Lock
#define Keyboard_Pause            72  // Keyboard Pause
#define Keyboard_Insert           73  // Keyboard Insert
#define Keyboard_Home             74  // Keyboard Home
#define Keyboard_PageUp           75  // Keyboard PageUp
#define Keyboard_Delete           76  // Keyboard Delete
#define Keyboard_End              77  // Keyboard End
#define Keyboard_PageDown         78  // Keyboard PageDown
#define Keyboard_RightArrow       79  // Keyboard RightArrow
#define Keyboard_LeftArrow        80  // Keyboard LeftArrow
#define Keyboard_DownArrow        81  // Keyboard DownArrow
#define Keyboard_UpArrow          82  // Keyboard UpArrow
#define Keypad_NumLock            83  // Keypad Num Lock and Clear
#define Keypad_ChuHao             84  // Keypad /
#define Keypad_ChengHao           85  // Keypad *
#define Keypad_JianHao            86  // Keypad -
#define Keypad_JiaHao             87  // Keypad +
#define Keypad_ENTER              88  // Keypad ENTER
#define Keypad_1_and_End          89  // Keypad 1 and End
#define Keypad_2_and_DownArrow    90  // Keypad 2 and Down Arrow
#define Keypad_3_and_PageDn       91  // Keypad 3 and PageDn
#define Keypad_4_and_LeftArrow    92  // Keypad 4 and Left Arrow
#define Keypad_5                  93  // Keypad 5
#define Keypad_6_and_RightArrow   94  // Keypad 6 and Right Arrow
#define Keypad_7_and_Home         95  // Keypad 7 and Home
#define Keypad_8_and_UpArrow      96  // Keypad 8 and Up Arrow
#define Keypad_9_and_PageUp       97  // Keypad 9 and PageUp
#define Keypad_0_and_Insert       98  // Keypad 0 and Insert
#define Keypad_Dian_and_Delete    99  // Keypad . and Delete
#define Keyboard_Application      101 // Keyboard Application
#define Keyboard_LeftControl      224
#define Keyboard_LeftShift        225
#define Keyboard_LeftAlt          226
#define Keyboard_LeftWindows      227
#define Keyboard_RightControl     228
#define Keyboard_RightShift       229
#define Keyboard_RightAlt         230
#define Keyboard_RightWindows     231


/**
 * @brief HIDD callback parameters union
 */
typedef union {
    /**
	 * @brief ESP_HIDD_EVENT_INIT_FINISH
	 */
    struct hidd_init_finish_evt_param {
        esp_hidd_init_state_t state;				/*!< Initial status */
        esp_gatt_if_t gatts_if;
    } init_finish;							      /*!< HID callback param of ESP_HIDD_EVENT_INIT_FINISH */

    /**
	 * @brief ESP_HIDD_EVENT_DEINIT_FINISH
	 */
    struct hidd_deinit_finish_evt_param {
        esp_hidd_deinit_state_t state;				/*!< De-initial status */
    } deinit_finish;								/*!< HID callback param of ESP_HIDD_EVENT_DEINIT_FINISH */

    /**
     * @brief ESP_HIDD_EVENT_CONNECT
	 */
    struct hidd_connect_evt_param {
        uint16_t conn_id;
        esp_bd_addr_t remote_bda;                   /*!< HID Remote bluetooth connection index */
    } connect;									    /*!< HID callback param of ESP_HIDD_EVENT_CONNECT */

    /**
     * @brief ESP_HIDD_EVENT_DISCONNECT
	 */
    struct hidd_disconnect_evt_param {
        esp_bd_addr_t remote_bda;                   /*!< HID Remote bluetooth device address */
    } disconnect;									/*!< HID callback param of ESP_HIDD_EVENT_DISCONNECT */

    /**
     * @brief ESP_HIDD_EVENT_BLE_VENDOR_REPORT_WRITE_EVT
	 */
    struct hidd_vendor_write_evt_param {
        uint16_t conn_id;                           /*!< HID connection index */
        uint16_t report_id;                         /*!< HID report index */
        uint16_t length;                            /*!< data length */
        uint8_t  *data;                             /*!< The pointer to the data */
    } vendor_write;									/*!< HID callback param of ESP_HIDD_EVENT_BLE_VENDOR_REPORT_WRITE_EVT */

} esp_hidd_cb_param_t;


/**
 * @brief HID device event callback function type
 * @param event : Event type
 * @param param : Point to callback parameter, currently is union type
 */
typedef void (*esp_hidd_event_cb_t) (esp_hidd_cb_event_t event, esp_hidd_cb_param_t *param);



/**
 *
 * @brief           This function is called to receive hid device callback event
 *
 * @param[in]    callbacks: callback functions
 *
 * @return         ESP_OK - success, other - failed
 *
 */
esp_err_t esp_hidd_register_callbacks(esp_hidd_event_cb_t callbacks);

/**
 *
 * @brief           This function is called to initialize hid device profile
 *
 * @return          ESP_OK - success, other - failed
 *
 */
esp_err_t esp_hidd_profile_init(void);

/**
 *
 * @brief           This function is called to de-initialize hid device profile
 *
 * @return          ESP_OK - success, other - failed
 *
 */
esp_err_t esp_hidd_profile_deinit(void);

/**
 *
 * @brief           Get hidd profile version
 *
 * @return          Most 8bit significant is Great version, Least 8bit is Sub version
 *
 */
uint16_t esp_hidd_get_version(void);

void esp_hidd_send_consumer_value(uint16_t conn_id, uint8_t key_cmd, bool key_pressed);

void esp_hidd_send_keyboard_value(uint16_t conn_id, key_mask_t special_key_mask, uint8_t *keyboard_cmd, uint8_t num_key);

void esp_hidd_send_mouse_value(uint16_t conn_id, uint8_t mouse_button, int8_t mickeys_x, int8_t mickeys_y);

#ifdef __cplusplus
}
#endif

#endif /* __ESP_HIDD_API_H__ */
