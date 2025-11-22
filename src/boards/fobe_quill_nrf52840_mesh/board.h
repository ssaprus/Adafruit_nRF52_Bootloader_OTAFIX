/*
 * The MIT License (MIT)
 *
 * Copyright (c) 2025 FoBE Studio.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#ifndef _FOBE_QUILL_NRF52840_MESH_H_
#define _FOBE_QUILL_NRF52840_MESH_H_

#define _PINNUM(port, pin)    ((port)*32 + (pin))

/*------------------------------------------------------------------*/
/* LED
 *------------------------------------------------------------------*/
#define LEDS_NUMBER        1
#define LED_PRIMARY_PIN   _PINNUM(1, 15) // Blue
#define LED_STATE_ON      0

#define NEOPIXELS_NUMBER      0

/*------------------------------------------------------------------*/
/* BUTTON
 *------------------------------------------------------------------*/
#define BUTTONS_NUMBER        2
#define BUTTON_1              _PINNUM(0, 18)  // P1.03: NC
#define BUTTON_2              _PINNUM(1, 10)  // P1.18: NC
#define BUTTON_PULL           NRF_GPIO_PIN_PULLUP

//--------------------------------------------------------------------+
// Display
//--------------------------------------------------------------------+

// VTFT_CTRL required to power the display
#define DISPLAY_VSENSOR_PIN   _PINNUM(0,  7)
#define DISPLAY_VSENSOR_ON    0

#define DISPLAY_CONTROLLER_ST7789

#define DISPLAY_PIN_SCK       _PINNUM(1,  9)
#define DISPLAY_PIN_MOSI      _PINNUM(0,  8)

#define DISPLAY_PIN_CS        _PINNUM(0, 12)
#define DISPLAY_PIN_DC        _PINNUM(0,  6)
#define DISPLAY_PIN_RST       _PINNUM(0, 26)
#define DISPLAY_PIN_BL        _PINNUM(0, 27)
#define DISPLAY_BL_ON         0  // GPIO state to enable back light

#define DISPLAY_WIDTH         240
#define DISPLAY_HEIGHT        135

// Display orientation configuration
#define DISPLAY_COL_OFFSET    53
#define DISPLAY_ROW_OFFSET    40
#define DISPLAY_MADCTL        (TFT_MADCTL_MX | TFT_MADCTL_RGB)

#define DISPLAY_VSCSAD        0

#define DISPLAY_TITLE         "FoBE Quill"

//--------------------------------------------------------------------+
// BLE OTA
//--------------------------------------------------------------------+
#define BLEDIS_MANUFACTURER   "FoBE Studio"
#define BLEDIS_MODEL          "FoBE Quill nRF52840 Mesh"

//--------------------------------------------------------------------+
// USB
//--------------------------------------------------------------------+
#define USB_DESC_VID           0x239A
#define USB_DESC_UF2_PID       0x0029
#define USB_DESC_CDC_ONLY_PID  0x002A

//--------------------------------------------------------------------+
// UF2
//--------------------------------------------------------------------+
#define UF2_PRODUCT_NAME        "FoBE Quill nRF52840 Mesh"
#define UF2_VOLUME_LABEL        "FOBEBOOT"
#define UF2_BOARD_ID            "nRF52840-FoBEF1101-rev1a"
#define UF2_INDEX_URL           "https://docs.fobestudio.com/product/f1101"


#endif /* _FOBE_QUILL_NRF52840_MESH_H_ */
