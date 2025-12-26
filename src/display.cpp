#include "display.h"

Display::Display() 
    : tft(TFT_eSPI())
    , currentState(MENU_MAIN)
    , backlightLevel(255) {
}

bool Display::begin() {
    tft.init();
    tft.setRotation(0);
    tft.fillScreen(BACKGROUND_COLOR);
    
    // Setup backlight pin
    pinMode(TFT_BL_PIN, OUTPUT);
    setBacklight(backlightLevel);
    
    Serial.println("Display initialized");
    return true;
}

void Display::clear() {
    tft.fillScreen(BACKGROUND_COLOR);
}

void Display::drawHeader(const String& title) {
    tft.fillRect(0, 0, SCREEN_WIDTH, 30, TFT_DARKGREY);
    tft.setTextColor(TFT_WHITE);
    tft.setTextSize(2);
    tft.setTextDatum(MC_DATUM);
    tft.drawString(title, SCREEN_WIDTH / 2, 15);
}

void Display::drawMenuItem(int y, const String& text, bool selected) {
    if (selected) {
        tft.fillRect(0, y, SCREEN_WIDTH, 30, HIGHLIGHT_COLOR);
        tft.setTextColor(TFT_BLACK);
    } else {
        tft.setTextColor(TEXT_COLOR);
    }
    tft.setTextSize(2);
    tft.setTextDatum(ML_DATUM);
    tft.drawString(text, 10, y + 15);
}

void Display::showMainMenu(int selectedItem) {
    clear();
    drawHeader(FIRMWARE_NAME);
    
    const char* menuItems[] = {
        "1. Capture Signal",
        "2. Replay Signal",
        "3. Frequency Scan",
        "4. Saved Signals",
        "5. Settings",
        "6. Info"
    };
    
    int yPos = 40;
    for (int i = 0; i < 6; i++) {
        drawMenuItem(yPos, menuItems[i], i == selectedItem);
        yPos += 35;
    }
    
    currentState = MENU_MAIN;
}

void Display::showCaptureScreen() {
    clear();
    drawHeader("Capture Signal");
    
    tft.setTextColor(TEXT_COLOR);
    tft.setTextSize(2);
    tft.setTextDatum(MC_DATUM);
    
    tft.drawString("Listening...", SCREEN_WIDTH / 2, 80);
    tft.drawString("Press SELECT", SCREEN_WIDTH / 2, 120);
    tft.drawString("to save", SCREEN_WIDTH / 2, 140);
    
    currentState = MENU_CAPTURE;
}

void Display::showReplayScreen(const RFSignal& signal) {
    clear();
    drawHeader("Replay Signal");
    
    tft.setTextColor(TEXT_COLOR);
    tft.setTextSize(2);
    tft.setTextDatum(MC_DATUM);
    
    tft.drawString("Transmitting...", SCREEN_WIDTH / 2, 80);
    
    tft.setTextSize(1);
    String freqStr = String(signal.frequency, 2) + " MHz";
    tft.drawString(freqStr, SCREEN_WIDTH / 2, 120);
    
    currentState = MENU_REPLAY;
}

void Display::showScanScreen(float freq, int rssi) {
    if (currentState != MENU_SCAN) {
        clear();
        drawHeader("Frequency Scan");
        currentState = MENU_SCAN;
    }
    
    tft.setTextColor(TEXT_COLOR);
    tft.setTextSize(2);
    tft.setTextDatum(MC_DATUM);
    
    String freqStr = String(freq, 2) + " MHz";
    tft.drawString(freqStr, SCREEN_WIDTH / 2, 80);
    
    String rssiStr = "RSSI: " + String(rssi) + " dBm";
    tft.drawString(rssiStr, SCREEN_WIDTH / 2, 110);
}

void Display::showSavedSignals(int selectedItem) {
    clear();
    drawHeader("Saved Signals");
    
    // This will be populated with actual saved signals
    tft.setTextColor(TEXT_COLOR);
    tft.setTextSize(2);
    tft.setTextDatum(MC_DATUM);
    tft.drawString("No signals saved", SCREEN_WIDTH / 2, 80);
    
    currentState = MENU_SAVED_SIGNALS;
}

void Display::showSettings(int selectedItem) {
    clear();
    drawHeader("Settings");
    
    const char* settingsItems[] = {
        "Backlight",
        "Default Freq",
        "Modulation",
        "Format Storage"
    };
    
    int yPos = 40;
    for (int i = 0; i < 4; i++) {
        drawMenuItem(yPos, settingsItems[i], i == selectedItem);
        yPos += 35;
    }
    
    currentState = MENU_SETTINGS;
}

void Display::showInfo() {
    clear();
    drawHeader("Info");
    
    tft.setTextColor(TEXT_COLOR);
    tft.setTextSize(2);
    tft.setTextDatum(MC_DATUM);
    
    tft.drawString(FIRMWARE_NAME, SCREEN_WIDTH / 2, 50);
    tft.setTextSize(1);
    tft.drawString("Version: " + String(FIRMWARE_VERSION), SCREEN_WIDTH / 2, 75);
    tft.drawString("", SCREEN_WIDTH / 2, 100);
    tft.drawString("Multi-Protocol", SCREEN_WIDTH / 2, 120);
    tft.drawString("RF Tool", SCREEN_WIDTH / 2, 135);
    tft.drawString("", SCREEN_WIDTH / 2, 160);
    tft.drawString("Supported:", SCREEN_WIDTH / 2, 180);
    tft.drawString("315/433/868/915 MHz", SCREEN_WIDTH / 2, 195);
    
    currentState = MENU_INFO;
}

void Display::showStatus(const String& message) {
    tft.fillRect(0, SCREEN_HEIGHT - 30, SCREEN_WIDTH, 30, TFT_DARKGREY);
    tft.setTextColor(TFT_WHITE);
    tft.setTextSize(1);
    tft.setTextDatum(MC_DATUM);
    tft.drawString(message, SCREEN_WIDTH / 2, SCREEN_HEIGHT - 15);
}

void Display::showSignalDetails(const RFSignal& signal) {
    clear();
    drawHeader("Signal Details");
    
    tft.setTextColor(TEXT_COLOR);
    tft.setTextSize(1);
    tft.setTextDatum(ML_DATUM);
    
    int yPos = 40;
    tft.drawString("Frequency: " + String(signal.frequency, 2) + " MHz", 10, yPos);
    yPos += 20;
    tft.drawString("Timings: " + String(signal.timings.size()), 10, yPos);
    yPos += 20;
    tft.drawString("Modulation: ASK/OOK", 10, yPos);
    yPos += 20;
    if (signal.name.length() > 0) {
        tft.drawString("Name: " + signal.name, 10, yPos);
    }
}

void Display::drawProgressBar(int x, int y, int width, int progress) {
    tft.drawRect(x, y, width, 10, TFT_WHITE);
    int fillWidth = (width - 2) * progress / 100;
    tft.fillRect(x + 1, y + 1, fillWidth, 8, HIGHLIGHT_COLOR);
}

void Display::setBacklight(uint8_t brightness) {
    backlightLevel = brightness;
    analogWrite(TFT_BL_PIN, brightness);
}
