#ifndef CONFIG_H
#define CONFIG_H

// Hardware Pin Definitions
#define CC1101_GDO0_PIN 4
#define CC1101_GDO2_PIN 5
#define CC1101_SCK_PIN 12
#define CC1101_MISO_PIN 13
#define CC1101_MOSI_PIN 11
#define CC1101_CS_PIN 10

#define TFT_CS_PIN 9
#define TFT_DC_PIN 8
#define TFT_RST_PIN 14
#define TFT_BL_PIN 15

#define BUTTON_UP 0
#define BUTTON_DOWN 1
#define BUTTON_SELECT 2

// CC1101 Frequency Presets (in MHz)
#define FREQ_315MHZ 315.0
#define FREQ_433MHZ 433.92
#define FREQ_868MHZ 868.0
#define FREQ_915MHZ 915.0

// Signal capture settings
#define MAX_SIGNAL_LENGTH 1024
#define SAMPLE_RATE_US 10

// File system
#define MAX_SAVED_SIGNALS 50

// Display settings
#define SCREEN_WIDTH 170
#define SCREEN_HEIGHT 320
#define BACKGROUND_COLOR TFT_BLACK
#define TEXT_COLOR TFT_WHITE
#define HIGHLIGHT_COLOR TFT_CYAN

// Version
#define FIRMWARE_VERSION "1.0.0"
#define FIRMWARE_NAME "Ultimatel-ily"

#endif // CONFIG_H
