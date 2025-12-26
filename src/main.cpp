#include <Arduino.h>
#include "config.h"
#include "rf_module.h"
#include "display.h"
#include "storage.h"
#include "rf_signal.h"

// Global objects
RFModule rfModule;
Display display;
Storage storage;

// Menu state
int currentMenuItem = 0;
int maxMenuItems = 6;
MenuState currentMenu = MENU_MAIN;

// Button states
bool buttonUpPressed = false;
bool buttonDownPressed = false;
bool buttonSelectPressed = false;

// Cached saved signals list (loaded on demand)
std::vector<String> savedSignals;
int selectedSignal = 0;
bool signalsListLoaded = false;

// Function prototypes
void handleMainMenu();
void handleCaptureMode();
void handleReplayMode();
void handleScanMode();
void handleSavedSignalsMenu();
void handleSettingsMenu();
void handleInfoScreen();
void checkButtons();
void navigateMenu(int direction);

void setup() {
    Serial.begin(115200);
    delay(1000);
    
    Serial.println("====================================");
    Serial.println(FIRMWARE_NAME);
    Serial.println("Version: " + String(FIRMWARE_VERSION));
    Serial.println("====================================");
    
    // Initialize display
    if (!display.begin()) {
        Serial.println("Display initialization failed!");
        while(1) delay(1000);
    }
    
    // Show splash screen
    display.clear();
    display.showInfo();
    delay(2000);
    
    // Initialize RF module
    if (!rfModule.begin()) {
        Serial.println("RF Module initialization failed!");
        display.showStatus("RF Init Failed!");
        while(1) delay(1000);
    }
    
    // Initialize storage
    if (!storage.begin()) {
        Serial.println("Storage initialization failed!");
        display.showStatus("Storage Init Failed!");
        // Continue anyway, just won't be able to save
    }
    
    // Note: Saved signals list will be loaded on demand when accessing saved signals menu
    Serial.println("Storage ready - signals list will load on demand");
    
    // Configure button pins (using internal pull-ups)
    // Note: Actual button pins may vary - these are placeholders
    pinMode(BUTTON_UP, INPUT_PULLUP);
    pinMode(BUTTON_DOWN, INPUT_PULLUP);
    pinMode(BUTTON_SELECT, INPUT_PULLUP);
    
    // Show main menu
    display.showMainMenu(currentMenuItem);
    display.showStatus("Ready");
    
    Serial.println("System ready!");
}

void loop() {
    checkButtons();
    
    switch (currentMenu) {
        case MENU_MAIN:
            handleMainMenu();
            break;
        case MENU_CAPTURE:
            handleCaptureMode();
            break;
        case MENU_REPLAY:
            handleReplayMode();
            break;
        case MENU_SCAN:
            handleScanMode();
            break;
        case MENU_SAVED_SIGNALS:
            handleSavedSignalsMenu();
            break;
        case MENU_SETTINGS:
            handleSettingsMenu();
            break;
        case MENU_INFO:
            handleInfoScreen();
            break;
    }
    
    delay(10);
}

void checkButtons() {
    // Check UP button
    if (digitalRead(BUTTON_UP) == LOW && !buttonUpPressed) {
        buttonUpPressed = true;
        navigateMenu(-1);
        delay(200);  // Debounce
    } else if (digitalRead(BUTTON_UP) == HIGH) {
        buttonUpPressed = false;
    }
    
    // Check DOWN button
    if (digitalRead(BUTTON_DOWN) == LOW && !buttonDownPressed) {
        buttonDownPressed = true;
        navigateMenu(1);
        delay(200);  // Debounce
    } else if (digitalRead(BUTTON_DOWN) == HIGH) {
        buttonDownPressed = false;
    }
    
    // Check SELECT button
    if (digitalRead(BUTTON_SELECT) == LOW && !buttonSelectPressed) {
        buttonSelectPressed = true;
        delay(200);  // Debounce
    } else if (digitalRead(BUTTON_SELECT) == HIGH) {
        buttonSelectPressed = false;
    }
}

void navigateMenu(int direction) {
    if (currentMenu == MENU_MAIN) {
        currentMenuItem += direction;
        if (currentMenuItem < 0) currentMenuItem = maxMenuItems - 1;
        if (currentMenuItem >= maxMenuItems) currentMenuItem = 0;
        display.showMainMenu(currentMenuItem);
    } else if (currentMenu == MENU_SAVED_SIGNALS) {
        if (savedSignals.size() > 0) {
            selectedSignal += direction;
            if (selectedSignal < 0) selectedSignal = savedSignals.size() - 1;
            if (selectedSignal >= (int)savedSignals.size()) selectedSignal = 0;
            display.showSavedSignals(selectedSignal);
        }
    }
}

void handleMainMenu() {
    if (buttonSelectPressed) {
        buttonSelectPressed = false;
        
        switch (currentMenuItem) {
            case 0:  // Capture Signal
                currentMenu = MENU_CAPTURE;
                display.showCaptureScreen();
                rfModule.startReceive();
                display.showStatus("Listening...");
                break;
                
            case 1:  // Replay Signal
                // Load signals list if not already loaded
                if (!signalsListLoaded) {
                    savedSignals = storage.listSignals();
                    signalsListLoaded = true;
                    Serial.print("Loaded ");
                    Serial.print(savedSignals.size());
                    Serial.println(" saved signals");
                }
                
                if (savedSignals.size() > 0) {
                    currentMenu = MENU_SAVED_SIGNALS;
                    selectedSignal = 0;
                    display.showSavedSignals(selectedSignal);
                } else {
                    display.showStatus("No saved signals!");
                    delay(1000);
                    display.showMainMenu(currentMenuItem);
                }
                break;
                
            case 2:  // Frequency Scan
                currentMenu = MENU_SCAN;
                display.showScanScreen(FREQ_433MHZ, -100);
                display.showStatus("Scanning...");
                break;
                
            case 3:  // Saved Signals
                // Load signals list if not already loaded
                if (!signalsListLoaded) {
                    savedSignals = storage.listSignals();
                    signalsListLoaded = true;
                    Serial.print("Loaded ");
                    Serial.print(savedSignals.size());
                    Serial.println(" saved signals");
                }
                
                currentMenu = MENU_SAVED_SIGNALS;
                selectedSignal = 0;
                display.showSavedSignals(selectedSignal);
                break;
                
            case 4:  // Settings
                currentMenu = MENU_SETTINGS;
                display.showSettings(0);
                break;
                
            case 5:  // Info
                currentMenu = MENU_INFO;
                display.showInfo();
                break;
        }
    }
}

void handleCaptureMode() {
    // Check for signal
    if (rfModule.signalDetected()) {
        display.showStatus("Signal detected!");
        
        // Capture the signal
        capturedSignal = rfModule.captureSignal();
        
        if (capturedSignal.timings.size() > 0) {
            display.showSignalDetails(capturedSignal);
            display.showStatus("Press SELECT to save");
            
            // Wait for user to decide
            unsigned long waitStart = millis();
            while (millis() - waitStart < 5000) {
                checkButtons();
                if (buttonSelectPressed) {
                    buttonSelectPressed = false;
                    
                    // Generate filename with timestamp
                    String filename = "signal_" + String(millis());
                    capturedSignal.name = filename;
                    
                    if (storage.saveSignal(capturedSignal, filename)) {
                        display.showStatus("Signal saved!");
                        // Invalidate cache so list will be reloaded next time
                        signalsListLoaded = false;
                    } else {
                        display.showStatus("Save failed!");
                    }
                    delay(1000);
                    break;
                }
                delay(10);
            }
        } else {
            display.showStatus("Capture failed!");
            delay(1000);
        }
        
        rfModule.stopReceive();
        currentMenu = MENU_MAIN;
        display.showMainMenu(currentMenuItem);
        
    } else if (buttonSelectPressed) {
        // Cancel capture
        buttonSelectPressed = false;
        rfModule.stopReceive();
        currentMenu = MENU_MAIN;
        display.showMainMenu(currentMenuItem);
        display.showStatus("Cancelled");
    }
}

void handleReplayMode() {
    if (selectedSignal >= 0 && selectedSignal < (int)savedSignals.size()) {
        RFSignal signal;
        if (storage.loadSignal(savedSignals[selectedSignal], signal)) {
            display.showReplayScreen(signal);
            rfModule.transmitSignal(signal);
            display.showStatus("Transmitted!");
            delay(1000);
        } else {
            display.showStatus("Load failed!");
            delay(1000);
        }
    }
    
    currentMenu = MENU_MAIN;
    display.showMainMenu(currentMenuItem);
}

void handleScanMode() {
    // Scan common frequencies
    float frequencies[] = {FREQ_315MHZ, FREQ_433MHZ, FREQ_868MHZ, FREQ_915MHZ};
    
    for (int i = 0; i < 4; i++) {
        rfModule.setFrequency(frequencies[i]);
        delay(100);
        
        // This is a simplified scan - CC1101 library may not expose RSSI easily
        display.showScanScreen(frequencies[i], -90);
        delay(500);
        
        checkButtons();
        if (buttonSelectPressed) {
            buttonSelectPressed = false;
            break;
        }
    }
    
    currentMenu = MENU_MAIN;
    display.showMainMenu(currentMenuItem);
    display.showStatus("Scan complete");
}

void handleSavedSignalsMenu() {
    if (buttonSelectPressed) {
        buttonSelectPressed = false;
        
        if (savedSignals.size() > 0 && selectedSignal >= 0 && selectedSignal < (int)savedSignals.size()) {
            RFSignal signal;
            if (storage.loadSignal(savedSignals[selectedSignal], signal)) {
                display.showReplayScreen(signal);
                rfModule.transmitSignal(signal);
                display.showStatus("Transmitted!");
                delay(1000);
            } else {
                display.showStatus("Load failed!");
                delay(1000);
            }
        }
        
        currentMenu = MENU_MAIN;
        display.showMainMenu(currentMenuItem);
    }
}

void handleSettingsMenu() {
    if (buttonSelectPressed) {
        buttonSelectPressed = false;
        currentMenu = MENU_MAIN;
        display.showMainMenu(currentMenuItem);
    }
}

void handleInfoScreen() {
    if (buttonSelectPressed) {
        buttonSelectPressed = false;
        currentMenu = MENU_MAIN;
        display.showMainMenu(currentMenuItem);
    }
}
