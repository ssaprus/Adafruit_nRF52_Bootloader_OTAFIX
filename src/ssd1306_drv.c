#ifdef BOARD_HAS_SSD1306

#include "ssd1306_drv.h"
#include "ssd1306_comm.h"
#include "font_8x8.h"
#include "nrf_delay.h"
#include <string.h>
#include <stdlib.h> 

// Configuration: Choose display method based on hardware
// Board-specific configuration
#ifdef BOARD_HAS_CH1116G
// CH1116G controller (SSD1306 compatible) has some addressing differences
// Use paged method for better text display and special handling for rightmost columns
#endif

static uint8_t ssd1306_buffer[SSD1306_WIDTH * SSD1306_HEIGHT / 8];
static bool display_enabled = false;

// fix some wrong cmd not good with this screen (commited by Dylan)
bool ssd1306_init(void) {
    if (!ssd1306_comm_init()) {
        display_enabled = false;
        return false;
    }
    
    display_enabled = true;

    // Hardware reset sequence - critical for reset from application
    ssd1306_write_command(0xAE); // Display off
    nrf_delay_ms(10);
    
    // Disable charge pump to ensure complete reset
    ssd1306_write_command(0x8D); 
    ssd1306_write_command(0x10); 
    nrf_delay_ms(10);
    
    // SSD1306 initialization sequence (restored from original working code)
    ssd1306_write_command(0xD5); // Set display clock divide ratio
    ssd1306_write_command(0x80); // Default ratio
    ssd1306_write_command(0xA8); // Set multiplex ratio
    ssd1306_write_command(0x3F); // 64 lines
    ssd1306_write_command(0xD3); // Set display offset
    ssd1306_write_command(0x00); // No offset
    ssd1306_write_command(0x40); // Set start line address
    ssd1306_write_command(0x8D); // Charge pump setting
    ssd1306_write_command(0x14); // Enable charge pump
    ssd1306_write_command(0x20); // Memory addressing mode
    ssd1306_write_command(0x00); // Horizontal addressing mode
    ssd1306_write_command(0xA1); // Set segment remap (A0/A1)
    ssd1306_write_command(0xC8); // Set COM output scan direction
    ssd1306_write_command(0xDA); // Set COM pins hardware configuration
    ssd1306_write_command(0x12); // Alternative COM pin config
    ssd1306_write_command(0x81); // Set contrast control
    ssd1306_write_command(0xCF); // High contrast
    ssd1306_write_command(0xD9); // Set pre-charge period
    ssd1306_write_command(0xF1); // Phase 1: 1 DCLK, Phase 2: 15 DCLK
    ssd1306_write_command(0xDB); // Set VCOMH deselect level
    ssd1306_write_command(0x40); // 0.77 * VCC
    ssd1306_write_command(0xA4); // Entire display ON (resume to RAM content)
    ssd1306_write_command(0xA6); // Set normal display (not inverted)
    
    // Clear screen
    ssd1306_clear();
    
    ssd1306_write_command(0xAF); // Display on
    
    return true;
}

void ssd1306_uninit(void) {
    if (display_enabled) {
        // Simply mark as disabled, don't touch hardware here
        // Hardware reset is handled in board_teardown()
        display_enabled = false;
    }
}

// Method 1: Fast clear using the fast display method
void ssd1306_clear_fast(void) {
    if (!display_enabled) return;
    
    memset(ssd1306_buffer, 0, sizeof(ssd1306_buffer));
    ssd1306_display_fast();
}

// Method 2: Hardware clear directly on display (for stubborn displays)
void ssd1306_clear_hardware(void) {
    if (!display_enabled) return;
    
    // Clear buffer first
    memset(ssd1306_buffer, 0, sizeof(ssd1306_buffer));
    
#ifdef BOARD_HAS_CH1116G
    // CH1116G specific clearing: Use horizontal addressing for better coverage
    ssd1306_write_command(0x20); // Memory addressing mode
    ssd1306_write_command(0x00); // Horizontal addressing mode
    
    // Set full column and page range
    ssd1306_write_command(0x21); // Column address
    ssd1306_write_command(0x00); // Start column 0
    ssd1306_write_command(0x7F); // End column 127
    ssd1306_write_command(0x22); // Page address  
    ssd1306_write_command(0x00); // Start page 0
    ssd1306_write_command(0x07); // End page 7
    
    // Send zeros to clear entire display
    ssd1306_write_data(ssd1306_buffer, sizeof(ssd1306_buffer));
    nrf_delay_ms(20);
    
    // Additional page-by-page clearing for CH1116G edge cases
    for (uint8_t page = 0; page < 8; page++) {
        ssd1306_write_command(0xB0 + page); // Set page address
        ssd1306_write_command(0x00);        // Lower column start
        ssd1306_write_command(0x10);        // Higher column start
        
        // Send 132 bytes for CH1116G (some variants need padding)
        uint8_t extended_clear[132] = {0};
        ssd1306_write_data(extended_clear, 132);
        nrf_delay_ms(5);
    }
#else
    // Standard SSD1306 page-by-page clearing
    for (uint8_t page = 0; page < 8; page++) {
        ssd1306_write_command(0xB0 + page); // Set page address
        ssd1306_write_command(0x00);        // Lower column start
        ssd1306_write_command(0x10);        // Higher column start
        
        // Send 128 bytes to clear the page
        uint8_t clear_data[128] = {0};
        ssd1306_write_data(clear_data, 128);
        nrf_delay_ms(5);
    }
#endif
}

// Default clear method - calls the appropriate method based on configuration
void ssd1306_clear(void) {
#ifdef BOARD_HAS_CH1116G
    ssd1306_clear_hardware(); // Use hardware clear for CH1116G
#else
    ssd1306_clear_fast();      // Use fast clear for standard SSD1306
#endif
}

// Method 1: Fast update using column/page address ranges (original method)
// Best for most SSD1306 displays, more efficient
void ssd1306_display_fast(void) {
    if (!display_enabled) return;
    
    // 设置列地址范围
    ssd1306_write_command(0x21); // Column address
    ssd1306_write_command(0x00); // Start column
    ssd1306_write_command(0x7F); // End column (127)
    
    // 设置页地址范围
    ssd1306_write_command(0x22); // Page address
    ssd1306_write_command(0x00); // Start page
    ssd1306_write_command(0x07); // End page (7)
    
    // 发送显示数据
    ssd1306_write_data(ssd1306_buffer, sizeof(ssd1306_buffer));
}

// Method 2: Page-by-page update (alternative method)
// Use for displays that have issues with address range commands
void ssd1306_display_paged(void) {
    if (!display_enabled) return;
    
    for (uint8_t page = 0; page < 8; page++) {
        ssd1306_write_command(0xB0 + page); // Set page address
        ssd1306_write_command(0x00);        // Lower column start
        ssd1306_write_command(0x10);        // Higher column start
        
        // Send the page data
        ssd1306_write_data(&ssd1306_buffer[page * SSD1306_WIDTH], SSD1306_WIDTH);
        
#ifdef BOARD_HAS_CH1116G
        // For CH1116G: ensure the last 2 columns are properly addressed
        if (page < 8) { // Additional safety check
            ssd1306_write_command(0x0E);        // Column 126 low bits
            ssd1306_write_command(0x17);        // Column 126 high bits
            
            // Resend the last 2 bytes to ensure they're displayed
            uint8_t last_cols[2];
            last_cols[0] = ssd1306_buffer[page * SSD1306_WIDTH + 126];
            last_cols[1] = ssd1306_buffer[page * SSD1306_WIDTH + 127];
            ssd1306_write_data(last_cols, 2);
        }
#endif
    }
}

// Default display method - calls the appropriate method based on configuration
void ssd1306_display(void) {
#ifdef BOARD_HAS_CH1116G
    ssd1306_display_paged(); // Use paged method for CH1116G (better text display)
#else
    ssd1306_display_fast();  // Use fast method for standard SSD1306
#endif
}

void ssd1306_set_pixel(uint8_t x, uint8_t y, bool on) {
    if (!display_enabled || x >= SSD1306_WIDTH || y >= SSD1306_HEIGHT) return;
    
    uint16_t index = x + (y / 8) * SSD1306_WIDTH;
    uint8_t bit = y % 8;
    
    if (on) {
        ssd1306_buffer[index] |= (1 << bit);
    } else {
        ssd1306_buffer[index] &= ~(1 << bit);
    }
}

void ssd1306_draw_char(uint8_t x, uint8_t y, char c) {
    if (!display_enabled || c < 32 || c > 126) return;
    if (x + 8 > SSD1306_WIDTH || y + 8 > SSD1306_HEIGHT) return;
    
    const uint8_t* char_data = font_8x8[c - 32];
    
    // 正确的字体绘制：横向排列，高位在左
    for (int row = 0; row < 8; row++) {
        uint8_t byte = char_data[row];
        for (int col = 0; col < 8; col++) {
            if (byte & (0x80 >> col)) {  // 从高位开始，0x80右移col位
                ssd1306_set_pixel(x + col, y + row, true);
            }
        }
    }
}

void ssd1306_draw_string(uint8_t x, uint8_t y, const char* str) {
    if (!display_enabled || !str) return;
    
    uint8_t cur_x = x;
    while (*str && cur_x + 8 <= SSD1306_WIDTH) {
        ssd1306_draw_char(cur_x, y, *str);
        cur_x += 8;
        str++;
    }
}

void ssd1306_draw_string_centered(uint8_t y, const char* str) {
    if (!display_enabled || !str) return;
    
    uint8_t len = strlen(str);
    if (len == 0) return;
    
    uint8_t total_width = len * 8;
    if (total_width > SSD1306_WIDTH) {
        ssd1306_draw_string(0, y, str);
    } else {
        uint8_t x = (SSD1306_WIDTH - total_width) / 2;
        ssd1306_draw_string(x, y, str);
    }
}

bool ssd1306_is_enabled(void) {
    return display_enabled;
}

#endif // BOARD_HAS_SSD1306
