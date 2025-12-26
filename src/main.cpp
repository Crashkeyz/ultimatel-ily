#include <Arduino.h>
#include "config.h"
#include "rf_module.h"
#include "display.h"
#include "storage.h"
#include "rf_signal.h"

#if ENABLE_ROLLING_CODE_ANALYSIS
#include "rolling_code_analyzer.h"
#endif

#if ENABLE_SIGNAL_INTELLIGENCE
#include "signal_intelligence.h"
#endif

#if ENABLE_ADVANCED_TX
#include "advanced_tx.h"
#endif

#if ENABLE_RF_RESEARCH
#include "rf_research.h"
#endif

// Global objects
RFModule rfModule;
Display display;
Storage storage;

#if ENABLE_ROLLING_CODE_ANALYSIS
RollingCodeAnalyzer rollingCodeAnalyzer;
#endif

#if ENABLE_SIGNAL_INTELLIGENCE
SignalIntelligence signalIntel;
#endif

#if ENABLE_ADVANCED_TX
AdvancedTx* advancedTx = nullptr;
#endif

#if ENABLE_RF_RESEARCH
RFResearch* rfResearch = nullptr;
#endif

// Menu state
int currentMenuItem = 0;
int maxMenuItems = 7;  // Increased for Advanced Research menu
MenuState currentMenu = MENU_MAIN;

// Button states
bool buttonUpPressed = false;
bool buttonDownPressed = false;
bool buttonSelectPressed = false;

// Cached saved signals list (loaded on demand)
std::vector<String> savedSignals;
int selectedSignal = 0;
bool signalsListLoaded = false;

// Advanced research state
int advancedMenuItem = 0;
int rollingCodeMenuItem = 0;
int signalIntelMenuItem = 0;
int rfResearchMenuItem = 0;
bool legalDisclaimerAccepted = false;

// Function prototypes
void handleMainMenu();
void handleCaptureMode();
void handleReplayMode();
void handleScanMode();
void handleSavedSignalsMenu();
void handleSettingsMenu();
void handleInfoScreen();
void handleAdvancedResearchMenu();
void handleRollingCodeMenu();
void handleSignalIntelMenu();
void handleRFResearchMenu();
void handleLegalWarning();
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
    
    // Initialize advanced features
#if ENABLE_ADVANCED_TX
    advancedTx = new AdvancedTx(&rfModule);
    Serial.println("Advanced TX initialized");
#endif

#if ENABLE_RF_RESEARCH
    rfResearch = new RFResearch(&rfModule);
    Serial.println("RF Research module loaded (disabled by default)");
#endif
    
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
        case MENU_ADVANCED_RESEARCH:
            handleAdvancedResearchMenu();
            break;
        case MENU_ROLLING_CODE:
            handleRollingCodeMenu();
            break;
        case MENU_SIGNAL_INTEL:
            handleSignalIntelMenu();
            break;
        case MENU_RF_RESEARCH:
            handleRFResearchMenu();
            break;
        case MENU_LEGAL_WARNING:
            handleLegalWarning();
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
                
            case 6:  // Advanced Research
                currentMenu = MENU_ADVANCED_RESEARCH;
                advancedMenuItem = 0;
                display.showAdvancedResearchMenu(advancedMenuItem);
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

void handleAdvancedResearchMenu() {
    // Check for navigation
    static bool upPressed = false;
    static bool downPressed = false;
    
    if (digitalRead(BUTTON_UP) == LOW && !upPressed) {
        upPressed = true;
        advancedMenuItem--;
        if (advancedMenuItem < 0) advancedMenuItem = 3;
        display.showAdvancedResearchMenu(advancedMenuItem);
        delay(200);
    } else if (digitalRead(BUTTON_UP) == HIGH) {
        upPressed = false;
    }
    
    if (digitalRead(BUTTON_DOWN) == LOW && !downPressed) {
        downPressed = true;
        advancedMenuItem++;
        if (advancedMenuItem > 3) advancedMenuItem = 0;
        display.showAdvancedResearchMenu(advancedMenuItem);
        delay(200);
    } else if (digitalRead(BUTTON_DOWN) == HIGH) {
        downPressed = false;
    }
    
    if (buttonSelectPressed) {
        buttonSelectPressed = false;
        
        switch (advancedMenuItem) {
            case 0:  // Legal Warning
                currentMenu = MENU_LEGAL_WARNING;
                display.showLegalWarning("");
                break;
                
            case 1:  // Rolling Code Analysis
#if ENABLE_ROLLING_CODE_ANALYSIS
                currentMenu = MENU_ROLLING_CODE;
                rollingCodeMenuItem = 0;
                display.showRollingCodeMenu(rollingCodeMenuItem);
#else
                display.showStatus("Feature disabled");
                delay(1000);
                display.showAdvancedResearchMenu(advancedMenuItem);
#endif
                break;
                
            case 2:  // Signal Intelligence
#if ENABLE_SIGNAL_INTELLIGENCE
                currentMenu = MENU_SIGNAL_INTEL;
                signalIntelMenuItem = 0;
                display.showSignalIntelMenu(signalIntelMenuItem);
#else
                display.showStatus("Feature disabled");
                delay(1000);
                display.showAdvancedResearchMenu(advancedMenuItem);
#endif
                break;
                
            case 3:  // RF Research Tools
#if ENABLE_RF_RESEARCH
                currentMenu = MENU_RF_RESEARCH;
                rfResearchMenuItem = 0;
                display.showRFResearchMenu(rfResearchMenuItem);
#else
                display.showStatus("Feature disabled in config");
                delay(2000);
                display.showAdvancedResearchMenu(advancedMenuItem);
#endif
                break;
        }
    }
}

void handleRollingCodeMenu() {
#if ENABLE_ROLLING_CODE_ANALYSIS
    // Navigation
    static bool upPressed = false;
    static bool downPressed = false;
    
    if (digitalRead(BUTTON_UP) == LOW && !upPressed) {
        upPressed = true;
        rollingCodeMenuItem--;
        if (rollingCodeMenuItem < 0) rollingCodeMenuItem = 4;
        display.showRollingCodeMenu(rollingCodeMenuItem);
        delay(200);
    } else if (digitalRead(BUTTON_UP) == HIGH) {
        upPressed = false;
    }
    
    if (digitalRead(BUTTON_DOWN) == LOW && !downPressed) {
        downPressed = true;
        rollingCodeMenuItem++;
        if (rollingCodeMenuItem > 4) rollingCodeMenuItem = 0;
        display.showRollingCodeMenu(rollingCodeMenuItem);
        delay(200);
    } else if (digitalRead(BUTTON_DOWN) == HIGH) {
        downPressed = false;
    }
    
    if (buttonSelectPressed) {
        buttonSelectPressed = false;
        
        switch (rollingCodeMenuItem) {
            case 0:  // Capture Sequence
                display.showStatus("Capturing sequence...");
                rfModule.startReceive();
                delay(3000);
                if (rfModule.signalDetected()) {
                    capturedSignal = rfModule.captureSignal();
                    rollingCodeAnalyzer.captureSequence(capturedSignal);
                    display.showStatus("Sequence captured!");
                } else {
                    display.showStatus("No signal detected");
                }
                rfModule.stopReceive();
                delay(1000);
                display.showRollingCodeMenu(rollingCodeMenuItem);
                break;
                
            case 1:  // Analyze Pattern
                {
                    RollingCodeAnalysis analysis = rollingCodeAnalyzer.analyzePattern();
                    display.showAnalysisResult(analysis.analysisReport);
                    delay(3000);
                    display.showRollingCodeMenu(rollingCodeMenuItem);
                }
                break;
                
            case 2:  // Protocol Detection
                display.showStatus("Detecting protocol...");
                delay(1000);
                display.showStatus("See serial output");
                delay(1000);
                display.showRollingCodeMenu(rollingCodeMenuItem);
                break;
                
            case 3:  // Export Data
                {
                    String report = rollingCodeAnalyzer.exportAnalysis();
                    Serial.println(report);
                    display.showStatus("Exported to serial");
                    delay(1000);
                    display.showRollingCodeMenu(rollingCodeMenuItem);
                }
                break;
                
            case 4:  // Clear Sequences
                rollingCodeAnalyzer.clearSequences();
                display.showStatus("Sequences cleared");
                delay(1000);
                display.showRollingCodeMenu(rollingCodeMenuItem);
                break;
        }
    }
#endif
}

void handleSignalIntelMenu() {
#if ENABLE_SIGNAL_INTELLIGENCE
    // Navigation
    static bool upPressed = false;
    static bool downPressed = false;
    
    if (digitalRead(BUTTON_UP) == LOW && !upPressed) {
        upPressed = true;
        signalIntelMenuItem--;
        if (signalIntelMenuItem < 0) signalIntelMenuItem = 4;
        display.showSignalIntelMenu(signalIntelMenuItem);
        delay(200);
    } else if (digitalRead(BUTTON_UP) == HIGH) {
        upPressed = false;
    }
    
    if (digitalRead(BUTTON_DOWN) == LOW && !downPressed) {
        downPressed = true;
        signalIntelMenuItem++;
        if (signalIntelMenuItem > 4) signalIntelMenuItem = 0;
        display.showSignalIntelMenu(signalIntelMenuItem);
        delay(200);
    } else if (digitalRead(BUTTON_DOWN) == HIGH) {
        downPressed = false;
    }
    
    if (buttonSelectPressed) {
        buttonSelectPressed = false;
        
        switch (signalIntelMenuItem) {
            case 0:  // Auto-Identify Protocol
                display.showStatus("Capturing signal...");
                rfModule.startReceive();
                delay(3000);
                if (rfModule.signalDetected()) {
                    capturedSignal = rfModule.captureSignal();
                    ProtocolInfo info = signalIntel.autoIdentifyProtocol(capturedSignal);
                    String result = "Protocol: " + info.protocolName + "\n";
                    result += "Confidence: " + String(info.confidence * 100) + "%";
                    display.showAnalysisResult(result);
                    delay(3000);
                } else {
                    display.showStatus("No signal detected");
                    delay(1000);
                }
                rfModule.stopReceive();
                display.showSignalIntelMenu(signalIntelMenuItem);
                break;
                
            case 1:  // Decode Signal
                display.showStatus("See serial output");
                delay(1000);
                display.showSignalIntelMenu(signalIntelMenuItem);
                break;
                
            case 2:  // Quality Analysis
                if (capturedSignal.timings.size() > 0) {
                    SignalQuality quality = signalIntel.analyzeQuality(capturedSignal);
                    display.showAnalysisResult(quality.qualityReport);
                    delay(3000);
                } else {
                    display.showStatus("Capture signal first");
                    delay(1000);
                }
                display.showSignalIntelMenu(signalIntelMenuItem);
                break;
                
            case 3:  // Extract Bits
                display.showStatus("See serial output");
                delay(1000);
                display.showSignalIntelMenu(signalIntelMenuItem);
                break;
                
            case 4:  // Export Analysis
                display.showStatus("Exported to serial");
                delay(1000);
                display.showSignalIntelMenu(signalIntelMenuItem);
                break;
        }
    }
#endif
}

void handleRFResearchMenu() {
#if ENABLE_RF_RESEARCH
    // Navigation
    static bool upPressed = false;
    static bool downPressed = false;
    
    if (digitalRead(BUTTON_UP) == LOW && !upPressed) {
        upPressed = true;
        rfResearchMenuItem--;
        if (rfResearchMenuItem < 0) rfResearchMenuItem = 3;
        display.showRFResearchMenu(rfResearchMenuItem);
        delay(200);
    } else if (digitalRead(BUTTON_UP) == HIGH) {
        upPressed = false;
    }
    
    if (digitalRead(BUTTON_DOWN) == LOW && !downPressed) {
        downPressed = true;
        rfResearchMenuItem++;
        if (rfResearchMenuItem > 3) rfResearchMenuItem = 0;
        display.showRFResearchMenu(rfResearchMenuItem);
        delay(200);
    } else if (digitalRead(BUTTON_DOWN) == HIGH) {
        downPressed = false;
    }
    
    if (buttonSelectPressed) {
        buttonSelectPressed = false;
        
        if (rfResearch == nullptr) {
            display.showStatus("RF Research not available");
            delay(1000);
            currentMenu = MENU_ADVANCED_RESEARCH;
            display.showAdvancedResearchMenu(advancedMenuItem);
            return;
        }
        
        switch (rfResearchMenuItem) {
            case 0:  // Authorization Check
                display.showStatus("Check serial output");
                rfResearch->checkAuthorization();
                delay(2000);
                display.showRFResearchMenu(rfResearchMenuItem);
                break;
                
            case 1:  // Frequency Sweep (educational demo)
                display.showStatus("EDUCATIONAL DEMO");
                Serial.println(RFResearch::getLegalWarning());
                rfResearch->sweepJammer(433.0, 434.0);
                delay(2000);
                display.showRFResearchMenu(rfResearchMenuItem);
                break;
                
            case 2:  // Signal Injection
                display.showStatus("EDUCATIONAL DEMO");
                delay(1000);
                display.showRFResearchMenu(rfResearchMenuItem);
                break;
                
            case 3:  // Protocol Fuzzing
                display.showStatus("EDUCATIONAL DEMO");
                delay(1000);
                display.showRFResearchMenu(rfResearchMenuItem);
                break;
        }
    }
#endif
}

void handleLegalWarning() {
    if (buttonSelectPressed) {
        buttonSelectPressed = false;
        
        // User accepted legal warning
        legalDisclaimerAccepted = true;
        
#if ENABLE_RF_RESEARCH
        if (rfResearch != nullptr) {
            rfResearch->acceptLegalDisclaimer();
        }
#endif
        
        Serial.println("Legal disclaimer accepted by user");
        display.showStatus("Disclaimer accepted");
        delay(1000);
        
        // Return to advanced menu
        currentMenu = MENU_ADVANCED_RESEARCH;
        display.showAdvancedResearchMenu(advancedMenuItem);
    }
}
