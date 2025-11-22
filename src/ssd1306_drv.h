#ifndef SSD1306_DRV_H
#define SSD1306_DRV_H

#include <stdint.h>
#include <stdbool.h>

#ifdef BOARD_HAS_SSD1306

// 显示参数
#define SSD1306_WIDTH  128
#define SSD1306_HEIGHT 64

// 初始化和基础功能
bool ssd1306_init(void);
void ssd1306_uninit(void);
void ssd1306_clear(void);             // Default clear method
void ssd1306_clear_fast(void);        // Fast clear using buffer + fast display
void ssd1306_clear_hardware(void);    // Hardware clear for stubborn displays
void ssd1306_display(void);           // Default display method
void ssd1306_display_fast(void);      // Fast update using column/page address ranges
void ssd1306_display_paged(void);     // Page-by-page update for problematic displays

// 文字显示功能 (8x8字体)
void ssd1306_draw_char(uint8_t x, uint8_t y, char c);
void ssd1306_draw_string(uint8_t x, uint8_t y, const char* str);
void ssd1306_draw_string_centered(uint8_t y, const char* str);

// 设置像素
void ssd1306_set_pixel(uint8_t x, uint8_t y, bool on);

// 显示状态管理
bool ssd1306_is_enabled(void);

#endif // BOARD_HAS_SSD1306

#endif // SSD1306_DRV_H
