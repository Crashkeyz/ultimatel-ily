#include "rf_module.h"

RFModule::RFModule() 
    : currentFrequency(FREQ_433MHZ)
    , currentModulation(MOD_ASK_OOK)
    , receiving(false) {
}

bool RFModule::begin() {
    // Initialize CC1101
    ELECHOUSE_cc1101.Init();
    ELECHOUSE_cc1101.setMHZ(currentFrequency);
    ELECHOUSE_cc1101.SetRx();
    
    configureCC1101();
    
    Serial.println("CC1101 initialized");
    Serial.print("Frequency: ");
    Serial.print(currentFrequency);
    Serial.println(" MHz");
    
    return true;
}

void RFModule::setFrequency(float freq) {
    currentFrequency = freq;
    ELECHOUSE_cc1101.setMHZ(freq);
    Serial.print("Frequency set to: ");
    Serial.print(freq);
    Serial.println(" MHz");
}

float RFModule::getFrequency() {
    return currentFrequency;
}

void RFModule::setModulation(ModulationType mod) {
    currentModulation = mod;
    setupRegisters();
}

void RFModule::startReceive() {
    ELECHOUSE_cc1101.SetRx();
    receiving = true;
    Serial.println("Started receiving");
}

void RFModule::stopReceive() {
    ELECHOUSE_cc1101.setSidle();
    receiving = false;
    Serial.println("Stopped receiving");
}

bool RFModule::signalDetected() {
    if (!receiving) return false;
    
    // Check if data is available via GDO0 pin
    return digitalRead(CC1101_GDO0_PIN) == HIGH;
}

RFSignal RFModule::captureSignal() {
    RFSignal signal;
    signal.frequency = currentFrequency;
    signal.modulation = currentModulation;
    signal.captureTime = millis();
    signal.rawDataLength = 0;
    
    // Note: rawData could be populated by reading CC1101 FIFO buffer
    // Currently we use timing-based capture which is stored in timings vector
    // Future enhancement: Add FIFO buffer reading for protocol-aware capture
    
    // Capture timing data
    unsigned long startTime = micros();
    unsigned long lastChange = startTime;
    int state = digitalRead(CC1101_GDO0_PIN);
    
    // Capture for up to 1 second or until buffer is full
    while (micros() - startTime < 1000000 && signal.timings.size() < MAX_SIGNAL_LENGTH) {
        int newState = digitalRead(CC1101_GDO0_PIN);
        if (newState != state) {
            unsigned long now = micros();
            uint16_t duration = now - lastChange;
            signal.timings.push_back(duration);
            lastChange = now;
            state = newState;
        }
        
        // If no transitions for 10ms, stop capturing
        if (micros() - lastChange > 10000) {
            break;
        }
    }
    
    Serial.print("Captured signal with ");
    Serial.print(signal.timings.size());
    Serial.println(" transitions");
    
    return signal;
}

void RFModule::transmitSignal(const RFSignal& signal) {
    // Set frequency and modulation
    setFrequency(signal.frequency);
    setModulation(signal.modulation);
    
    Serial.println("Transmitting signal...");
    
    // Switch to TX mode
    ELECHOUSE_cc1101.SetTx();
    
    // Replay the timing pattern using the CC1101's built-in transmission
    // Note: For more sophisticated replay, we'd send data bytes through the CC1101
    // For now, we do multiple short transmissions to simulate the pattern
    for (int repeat = 0; repeat < 5; repeat++) {
        ELECHOUSE_cc1101.SetTx();
        delay(20);  // Hold TX for pattern duration
        ELECHOUSE_cc1101.setSidle();
        delay(20);  // Gap between repeats
    }
    
    // Return to RX mode
    ELECHOUSE_cc1101.SetRx();
    
    Serial.println("Transmission complete");
    Serial.println("Note: Advanced timing replay requires CC1101 FIFO buffer usage");
}

void RFModule::scanFrequencies(float startFreq, float endFreq, float step) {
    Serial.println("Starting frequency scan...");
    
    for (float freq = startFreq; freq <= endFreq; freq += step) {
        setFrequency(freq);
        ELECHOUSE_cc1101.SetRx();
        delay(100);  // Listen for 100ms
        
        // Check RSSI (Received Signal Strength Indicator)
        int rssi = ELECHOUSE_cc1101.getRssi();
        
        if (rssi > -90) {  // Threshold for signal detection
            Serial.print("Signal detected at ");
            Serial.print(freq);
            Serial.print(" MHz, RSSI: ");
            Serial.println(rssi);
        }
    }
    
    Serial.println("Scan complete");
}

void RFModule::configureCC1101() {
    // Basic configuration for ASK/OOK modulation
    ELECHOUSE_cc1101.setModulation(2);  // ASK/OOK
    ELECHOUSE_cc1101.setDRate(512);     // Data rate in kBaud
    ELECHOUSE_cc1101.setRxBW(812);      // RX bandwidth in kHz
    ELECHOUSE_cc1101.setPA(12);         // Power amplifier (max = 12)
}

void RFModule::setupRegisters() {
    // Configure modulation based on type
    switch (currentModulation) {
        case MOD_ASK_OOK:
            ELECHOUSE_cc1101.setModulation(2);
            break;
        case MOD_2FSK:
            ELECHOUSE_cc1101.setModulation(0);
            break;
        case MOD_GFSK:
            ELECHOUSE_cc1101.setModulation(1);
            break;
        case MOD_MSK:
            ELECHOUSE_cc1101.setModulation(7);
            break;
        default:
            ELECHOUSE_cc1101.setModulation(2);  // Default to ASK/OOK
            break;
    }
}
