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

#ifndef _GAT562_BOARD_H
#define _GAT562_BOARD_H

// change default 1.8v to 3.3v, add by taylor
#define UICR_REGOUT0_VALUE UICR_REGOUT0_VOUT_3V3

#define _PINNUM(port, pin)    ((port)*32 + (pin))

/*------------------------------------------------------------------*/
/* LED
 *------------------------------------------------------------------*/
#define LEDS_NUMBER           2
#define LED_PRIMARY_PIN       _PINNUM(1, 3)
#define LED_SECONDARY_PIN     _PINNUM(1, 4)
#define LED_STATE_ON          1

/*------------------------------------------------------------------*/
/* BUTTON
 *------------------------------------------------------------------*/
#define BUTTONS_NUMBER        2
#define BUTTON_1              _PINNUM(0, 9)
#define BUTTON_2              _PINNUM(0, 9)
#define BUTTON_PULL           NRF_GPIO_PIN_PULLUP

//--------------------------------------------------------------------+
// I2C for SSD1306 Display
//--------------------------------------------------------------------+
#define I2C_SDA_PIN           _PINNUM(0, 13)  // P0.13 - I2C SDA
#define I2C_SCL_PIN           _PINNUM(0, 14)  // P0.14 - I2C SCL
#define SSD1306_I2C_ADDR      0x3C            // SSD1306 OLED Display I2C Address

// SSD1306 display configuration (默认配置)
#define SSD1306_COM_PINS      0x12            // Alternative COM pin configuration
#define SSD1306_SEGMENT_REMAP 0xA1            // Segment remap 
#define SSD1306_COM_SCAN_DIR  0xC8            // Reverse COM scan direction

//--------------------------------------------------------------------+
// BLE OTA
//--------------------------------------------------------------------+
#define BLEDIS_MANUFACTURER   "GAT-IOT"
#define BLEDIS_MODEL          "GAT562"

//--------------------------------------------------------------------+
// USB
//--------------------------------------------------------------------+
#define USB_DESC_VID           0x239A
#define USB_DESC_UF2_PID       0x0029
#define USB_DESC_CDC_ONLY_PID  0x002A

//------------- UF2 -------------//
#define UF2_PRODUCT_NAME      "GAT562 BOARD"
#define UF2_VOLUME_LABEL      "GAT562-BOOT"
#define UF2_BOARD_ID          "GAT562-Board"
#define UF2_INDEX_URL         "http://www.gat-iot.com"

#endif // _GAT562_BOARD_H
