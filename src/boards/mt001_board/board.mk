MCU_SUB_VARIANT = nrf52840

# Define board-specific macro for conditional compilation
CFLAGS += -DDEVICE_NAME='"MT001-OTA"'
CFLAGS += -DBOARD_HAS_SSD1306
