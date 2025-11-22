#ifdef BOARD_HAS_SSD1306

#include "ssd1306_comm.h"
#include "boards.h"
#include "nrfx_twi.h"
#include "nrf_delay.h"
#include <string.h>

static const nrfx_twi_t twi = NRFX_TWI_INSTANCE(0);
static bool twi_initialized = false;

bool ssd1306_comm_init(void) {
    if (twi_initialized) {
        ssd1306_comm_uninit();
    }

    nrf_delay_ms(20); // Stability delay

    nrfx_twi_config_t twi_config = NRFX_TWI_DEFAULT_CONFIG(I2C_SCL_PIN, I2C_SDA_PIN);
    twi_config.frequency = NRF_TWI_FREQ_400K;

    // Ensure I2C pins are in correct state
    nrf_gpio_cfg_output(I2C_SCL_PIN);
    nrf_gpio_cfg_output(I2C_SDA_PIN);
    nrf_gpio_pin_set(I2C_SCL_PIN);
    nrf_gpio_pin_set(I2C_SDA_PIN);
    nrf_delay_ms(5);

    nrfx_err_t err = nrfx_twi_init(&twi, &twi_config, NULL, NULL);
    if (err != NRFX_SUCCESS) {
        // Single retry with bus reset
        nrfx_twi_uninit(&twi);
        
        // Basic bus reset
        for (int i = 0; i < 9; i++) {
            nrf_gpio_pin_clear(I2C_SCL_PIN);
            nrf_delay_us(5);
            nrf_gpio_pin_set(I2C_SCL_PIN);
            nrf_delay_us(5);
        }
        nrf_delay_ms(10);
        
        err = nrfx_twi_init(&twi, &twi_config, NULL, NULL);
        if (err != NRFX_SUCCESS) return false;
    }

    nrfx_twi_enable(&twi);
    twi_initialized = true;
    nrf_delay_ms(50);
    
    // Simple communication test
    uint8_t test_data = 0x00;
    nrfx_twi_xfer_desc_t test_xfer = NRFX_TWI_XFER_DESC_TX(SSD1306_I2C_ADDR, &test_data, 1);
    err = nrfx_twi_xfer(&twi, &test_xfer, 0);
    if (err != NRFX_SUCCESS) {
        ssd1306_comm_uninit();
        return false;
    }
    
    return true;
}

void ssd1306_comm_uninit(void) {
    if (twi_initialized) {
        nrfx_twi_disable(&twi);
        nrfx_twi_uninit(&twi);
        twi_initialized = false;
    }
}

void ssd1306_write_command(uint8_t cmd) {
    if (!twi_initialized) return;

    uint8_t data[2] = {0x00, cmd}; // Control byte (Co=0, D/C=0) + command
    nrfx_twi_xfer_desc_t xfer = NRFX_TWI_XFER_DESC_TX(SSD1306_I2C_ADDR, data, 2);
    nrfx_twi_xfer(&twi, &xfer, 0);
    
    nrf_delay_ms(1);
}

// refact this function  take lager buffer --maybe useless :) (commited by Dylan)
void ssd1306_write_data(const uint8_t* data, uint16_t len) {
    if (!twi_initialized || !data || len == 0) return;

    // upgrade: bigger chunk
    const uint16_t max_chunk_size = 254; // 255-1
    uint8_t buffer[max_chunk_size + 1];
    uint16_t sent = 0;

    buffer[0] = 0x40; 

    while (sent < len) {
        uint16_t to_send = (len - sent > max_chunk_size) ? max_chunk_size : (len - sent);
        memcpy(&buffer[1], &data[sent], to_send);

        nrfx_twi_xfer_desc_t xfer = NRFX_TWI_XFER_DESC_TX(SSD1306_I2C_ADDR, buffer, to_send + 1);
        nrfx_twi_xfer(&twi, &xfer, 0);

        sent += to_send;
        
        if (sent < len) {
            nrf_delay_ms(1);
        }
    }
}

#endif // BOARD_HAS_SSD1306
