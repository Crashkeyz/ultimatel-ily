// TFT_eSPI User Setup for LilyGO T-Embed CC1101
// This file should be placed in the TFT_eSPI library folder
// or configured via build flags

#define USER_SETUP_INFO "User_Setup for LilyGO T-Embed"

#define ST7789_DRIVER

#define TFT_WIDTH  170
#define TFT_HEIGHT 320

#define TFT_MOSI 11
#define TFT_SCLK 12
#define TFT_CS   9
#define TFT_DC   8
#define TFT_RST  14
#define TFT_BL   15

#define LOAD_GLCD
#define LOAD_FONT2
#define LOAD_FONT4
#define LOAD_FONT6
#define LOAD_FONT7
#define LOAD_FONT8
#define LOAD_GFXFF

#define SMOOTH_FONT

#define SPI_FREQUENCY  40000000
#define SPI_READ_FREQUENCY  20000000
#define SPI_TOUCH_FREQUENCY  2500000
