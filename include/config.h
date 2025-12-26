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

// Note: GPIO 0 is a boot strapping pin on ESP32-S3
// If using GPIO 0 for BUTTON_UP causes issues with boot or upload,
// change to a different GPIO that doesn't have special functions.
// Safe alternatives: GPIO 3, 6, 7, 16, 17, 18, etc.
// Avoid: GPIO 0 (boot), GPIO 46 (input only), GPIO 45 (strapping)

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

// Advanced Research Feature Flags
// These features are for educational and authorized security research only
#define ENABLE_ROLLING_CODE_ANALYSIS 1
#define ENABLE_SIGNAL_INTELLIGENCE 1
#define ENABLE_ADVANCED_TX 1
#define ENABLE_RF_RESEARCH 0  // Disabled by default, requires explicit user activation

// Safety limits
#define MAX_TX_DURATION_MS 5000
#define EMERGENCY_STOP_BUTTON GPIO_NUM_0
#define MAX_SWEEP_DURATION_MS 10000
#define MIN_PULSE_INTERVAL_MS 100

// Research mode settings
#define RESEARCH_MODE_TIMEOUT_MS 300000  // 5 minutes
#define REQUIRE_DISCLAIMER_ACCEPTANCE 1

#endif // CONFIG_H
