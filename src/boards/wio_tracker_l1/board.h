/*
 * The MIT License (MIT)
 *
 * Copyright (c) 2018 Ha Thach for Adafruit Industries
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

#ifndef _TRACKER_L1
#define _TRACKER_L1

#define _PINNUM(port, pin)    ((port)*32 + (pin))

/*------------------------------------------------------------------*/
/* LED
 *------------------------------------------------------------------*/
#define LEDS_NUMBER           1
#define LED_PRIMARY_PIN       _PINNUM(1, 1)
#define LED_STATE_ON          1

#define NEOPIXELS_NUMBER      0

/*------------------------------------------------------------------*/
/* BUTTON
 *------------------------------------------------------------------*/
#define BUTTONS_NUMBER        2
#define BUTTON_1              _PINNUM(0, 8) // user button
#define BUTTON_2              _PINNUM(0, 8)
#define BUTTON_PULL           NRF_GPIO_PIN_PULLUP

//--------------------------------------------------------------------+
// I2C for SSD1306 OLED Display
//--------------------------------------------------------------------+
#define I2C_SCL_PIN           _PINNUM(0, 5)   // P0.05 - I2C SCL
#define I2C_SDA_PIN           _PINNUM(0, 6)   // P0.06 - I2C SDA
#define SSD1306_I2C_ADDR      0x3D            // SSD1306 I2C Address

// Display configuration
#define SSD1306_COM_PINS      0x02            // Sequential COM pin configuration
#define SSD1306_SEGMENT_REMAP 0xA0            // No segment remap
#define SSD1306_COM_SCAN_DIR  0xC0            // Normal COM scan direction

//--------------------------------------------------------------------+
// BLE OTA
//--------------------------------------------------------------------+
#define BLEDIS_MANUFACTURER   "Seeed"
#define BLEDIS_MODEL          "Wio Tracker L1"

//--------------------------------------------------------------------+
// USB
//--------------------------------------------------------------------+
#define USB_DESC_VID           0x2886
#define USB_DESC_UF2_PID       0x1667
#define USB_DESC_CDC_ONLY_PID  0x1667

//------------- UF2 -------------//
#define UF2_PRODUCT_NAME   "Seeed TRACKER L1"
#define UF2_VOLUME_LABEL   "TRACKER L1"
#define UF2_BOARD_ID       "TRACKER L1"
#define UF2_INDEX_URL      "https://www.seeedstudio.com/"

#endif // _TRACKER_L1
