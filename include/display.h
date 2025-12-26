#ifndef DISPLAY_H
#define DISPLAY_H

#include <TFT_eSPI.h>
#include "config.h"
#include "rf_signal.h"

enum MenuState {
    MENU_MAIN,
    MENU_CAPTURE,
    MENU_REPLAY,
    MENU_SCAN,
    MENU_SAVED_SIGNALS,
    MENU_SETTINGS,
    MENU_INFO,
    MENU_ADVANCED_RESEARCH,
    MENU_ROLLING_CODE,
    MENU_SIGNAL_INTEL,
    MENU_RF_RESEARCH,
    MENU_LEGAL_WARNING
};

class Display {
public:
    Display();
    bool begin();
    void clear();
    void showMainMenu(int selectedItem);
    void showCaptureScreen();
    void showReplayScreen(const RFSignal& signal);
    void showScanScreen(float freq, int rssi);
    void showSavedSignals(int selectedItem);
    void showSettings(int selectedItem);
    void showInfo();
    void showStatus(const String& message);
    void showSignalDetails(const RFSignal& signal);
    void setBacklight(uint8_t brightness);
    
    // Advanced research screens
    void showAdvancedResearchMenu(int selectedItem);
    void showRollingCodeMenu(int selectedItem);
    void showSignalIntelMenu(int selectedItem);
    void showRFResearchMenu(int selectedItem);
    void showLegalWarning(const String& warningText);
    void showAnalysisResult(const String& result);
    
private:
    TFT_eSPI tft;
    MenuState currentState;
    uint8_t backlightLevel;
    
    void drawHeader(const String& title);
    void drawMenuItem(int y, const String& text, bool selected);
    void drawProgressBar(int x, int y, int width, int progress);
};

#endif // DISPLAY_H
