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
        "6. Info",
        "7. Advanced Research"
    };
    
    int yPos = 40;
    for (int i = 0; i < 7; i++) {
        drawMenuItem(yPos, menuItems[i], i == selectedItem);
        yPos += 32;  // Adjusted spacing for 7 items
    }
    
    // Warning indicator for Advanced Research
    if (selectedItem == 6) {
        tft.setTextColor(TFT_RED);
        tft.setTextSize(1);
        tft.setTextDatum(MC_DATUM);
        tft.drawString("EDUCATIONAL USE ONLY", SCREEN_WIDTH / 2, SCREEN_HEIGHT - 35);
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

void Display::showAdvancedResearchMenu(int selectedItem) {
    clear();
    drawHeader("Advanced Research");
    
    // Warning indicator
    tft.fillRect(0, 30, SCREEN_WIDTH, 20, TFT_RED);
    tft.setTextColor(TFT_WHITE);
    tft.setTextSize(1);
    tft.setTextDatum(MC_DATUM);
    tft.drawString("EDUCATIONAL USE ONLY", SCREEN_WIDTH / 2, 40);
    
    const char* menuItems[] = {
        "Legal Warning",
        "Rolling Code Analysis",
        "Signal Intelligence",
        "RF Research Tools"
    };
    
    int yPos = 60;
    for (int i = 0; i < 4; i++) {
        drawMenuItem(yPos, menuItems[i], i == selectedItem);
        yPos += 35;
    }
    
    currentState = MENU_ADVANCED_RESEARCH;
}

void Display::showRollingCodeMenu(int selectedItem) {
    clear();
    drawHeader("Rolling Code");
    
    const char* menuItems[] = {
        "Capture Sequence",
        "Analyze Pattern",
        "Protocol Detection",
        "Export Data",
        "Clear Sequences"
    };
    
    int yPos = 40;
    for (int i = 0; i < 5; i++) {
        drawMenuItem(yPos, menuItems[i], i == selectedItem);
        yPos += 35;
    }
    
    currentState = MENU_ROLLING_CODE;
}

void Display::showSignalIntelMenu(int selectedItem) {
    clear();
    drawHeader("Signal Intel");
    
    const char* menuItems[] = {
        "Auto-Identify Protocol",
        "Decode Signal",
        "Quality Analysis",
        "Extract Bits",
        "Export Analysis"
    };
    
    int yPos = 40;
    for (int i = 0; i < 5; i++) {
        drawMenuItem(yPos, menuItems[i], i == selectedItem);
        yPos += 35;
    }
    
    currentState = MENU_SIGNAL_INTEL;
}

void Display::showRFResearchMenu(int selectedItem) {
    clear();
    
    // EXTREME WARNING HEADER
    tft.fillRect(0, 0, SCREEN_WIDTH, 40, TFT_RED);
    tft.setTextColor(TFT_WHITE);
    tft.setTextSize(2);
    tft.setTextDatum(MC_DATUM);
    tft.drawString("WARNING!", SCREEN_WIDTH / 2, 10);
    tft.setTextSize(1);
    tft.drawString("ILLEGAL WITHOUT AUTH", SCREEN_WIDTH / 2, 30);
    
    const char* menuItems[] = {
        "Authorization Check",
        "Frequency Sweep",
        "Signal Injection",
        "Protocol Fuzzing"
    };
    
    int yPos = 50;
    for (int i = 0; i < 4; i++) {
        // Draw with red background for danger
        if (selectedItem == i) {
            tft.fillRect(0, yPos, SCREEN_WIDTH, 30, TFT_ORANGE);
            tft.setTextColor(TFT_BLACK);
        } else {
            tft.setTextColor(TFT_RED);
        }
        tft.setTextSize(2);
        tft.setTextDatum(ML_DATUM);
        tft.drawString(menuItems[i], 10, yPos + 15);
        yPos += 35;
    }
    
    currentState = MENU_RF_RESEARCH;
}

void Display::showLegalWarning(const String& warningText) {
    clear();
    
    // Red warning header
    tft.fillRect(0, 0, SCREEN_WIDTH, 30, TFT_RED);
    tft.setTextColor(TFT_WHITE);
    tft.setTextSize(2);
    tft.setTextDatum(MC_DATUM);
    tft.drawString("LEGAL WARNING", SCREEN_WIDTH / 2, 15);
    
    // Warning text
    tft.setTextColor(TFT_YELLOW);
    tft.setTextSize(1);
    tft.setTextDatum(TL_DATUM);
    
    // Word wrap the warning text
    int yPos = 40;
    int lineHeight = 12;
    int maxWidth = SCREEN_WIDTH - 20;
    
    // Display first few lines (screen space limited)
    String lines[] = {
        "EDUCATIONAL USE ONLY",
        "",
        "RF research features",
        "are for authorized",
        "security research",
        "and education only.",
        "",
        "Unauthorized use is",
        "ILLEGAL and may result",
        "in fines and",
        "imprisonment.",
        "",
        "Press SELECT to",
        "accept responsibility."
    };
    
    for (int i = 0; i < 14 && yPos < SCREEN_HEIGHT - 40; i++) {
        tft.drawString(lines[i], 10, yPos);
        yPos += lineHeight;
    }
    
    currentState = MENU_LEGAL_WARNING;
}

void Display::showAnalysisResult(const String& result) {
    clear();
    drawHeader("Analysis Result");
    
    tft.setTextColor(TEXT_COLOR);
    tft.setTextSize(1);
    tft.setTextDatum(TL_DATUM);
    
    // Display result text (simplified - real implementation would scroll)
    int yPos = 40;
    int lineHeight = 12;
    
    // Split result into lines and display
    int startIdx = 0;
    for (int i = 0; i < result.length() && yPos < SCREEN_HEIGHT - 40; i++) {
        if (result.charAt(i) == '\n' || (i - startIdx) > 25) {
            String line = result.substring(startIdx, i);
            tft.drawString(line, 10, yPos);
            yPos += lineHeight;
            startIdx = i + 1;
        }
    }
    
    // Draw last line
    if (startIdx < result.length() && yPos < SCREEN_HEIGHT - 40) {
        String line = result.substring(startIdx);
        tft.drawString(line, 10, yPos);
    }
}

