#include "advanced_tx.h"
#include "config.h"

AdvancedTx::AdvancedTx(RFModule* rfModule) : rf(rfModule), transmitting(false), 
    maxTxDuration(MAX_TX_DURATION_MS), txStartTime(0) {
}

void AdvancedTx::sweepFrequencies(float startFreq, float endFreq, float step, uint32_t dwellTime) {
    Serial.println("⚠️ WARNING: Frequency sweep starting ⚠️");
    Serial.println("Educational/Research purposes only");
    
    if (!checkTransmissionSafe(dwellTime * ((endFreq - startFreq) / step))) {
        Serial.println("ERROR: Sweep duration exceeds safety limits");
        return;
    }
    
    startTransmission();
    
    for (float freq = startFreq; freq <= endFreq; freq += step) {
        if (!transmitting) break;  // Emergency stop check
        
        rf->setFrequency(freq);
        delay(dwellTime);
        
        Serial.print("Sweep: ");
        Serial.print(freq);
        Serial.println(" MHz");
    }
    
    stopTransmission();
    Serial.println("Frequency sweep completed");
}

void AdvancedTx::transmitCW(float frequency, uint32_t durationMs) {
    Serial.println("⚠️ WARNING: CW transmission starting ⚠️");
    
    if (!checkTransmissionSafe(durationMs)) {
        Serial.println("ERROR: Duration exceeds safety limits");
        return;
    }
    
    startTransmission();
    
    rf->setFrequency(frequency);
    // Note: Actual CW transmission would require CC1101 to be set to continuous TX mode
    // This is a placeholder for the concept
    
    Serial.println("CW transmission active...");
    delay(durationMs);
    
    stopTransmission();
    Serial.println("CW transmission stopped");
}

void AdvancedTx::transmitAtTime(const RFSignal& signal, uint32_t delayMs) {
    Serial.println("Scheduling transmission...");
    
    delay(delayMs);
    
    startTransmission();
    rf->transmitSignal(signal);
    stopTransmission();
    
    Serial.println("Timed transmission completed");
}

void AdvancedTx::fuzzProtocol(const RFSignal& baseSignal, uint32_t iterations) {
    Serial.println("⚠️ Protocol fuzzing started ⚠️");
    Serial.println("Educational/Testing purposes only");
    
    startTransmission();
    
    for (uint32_t i = 0; i < iterations && transmitting; i++) {
        RFSignal fuzzed = baseSignal;
        
        // Randomly modify timing values (fuzzing)
        for (size_t j = 0; j < fuzzed.timings.size(); j++) {
            // Add random variation (-20% to +20%)
            int32_t variation = (random(-20, 21) * fuzzed.timings[j]) / 100;
            fuzzed.timings[j] += variation;
        }
        
        rf->transmitSignal(fuzzed);
        delay(100);
        
        if (i % 10 == 0) {
            Serial.print("Fuzzing iteration: ");
            Serial.println(i);
        }
    }
    
    stopTransmission();
    Serial.println("Protocol fuzzing completed");
}

void AdvancedTx::replayWithTimingVariation(const RFSignal& signal, float variation) {
    Serial.println("Replaying with timing variation...");
    
    RFSignal modified = signal;
    
    // Apply timing variation
    for (size_t i = 0; i < modified.timings.size(); i++) {
        int32_t adjust = (int32_t)(modified.timings[i] * variation);
        modified.timings[i] += adjust;
    }
    
    startTransmission();
    rf->transmitSignal(modified);
    stopTransmission();
    
    Serial.println("Replay with variation completed");
}

void AdvancedTx::replayWithAmplitudeVariation(const RFSignal& signal, int8_t powerDbm) {
    Serial.println("Replaying with power variation...");
    Serial.print("Power: ");
    Serial.print(powerDbm);
    Serial.println(" dBm");
    
    // Note: CC1101 power adjustment would be done here
    // This is a placeholder - actual implementation requires CC1101 PA table configuration
    
    startTransmission();
    rf->transmitSignal(signal);
    stopTransmission();
    
    Serial.println("Replay with amplitude variation completed");
}

void AdvancedTx::transmitBurst(const RFSignal& signal, uint32_t count, uint32_t intervalMs) {
    Serial.println("Burst transmission starting...");
    
    if (!checkTransmissionSafe(count * intervalMs)) {
        Serial.println("ERROR: Burst duration exceeds safety limits");
        return;
    }
    
    startTransmission();
    
    for (uint32_t i = 0; i < count && transmitting; i++) {
        rf->transmitSignal(signal);
        delay(intervalMs);
        
        Serial.print("Burst ");
        Serial.print(i + 1);
        Serial.print("/");
        Serial.println(count);
    }
    
    stopTransmission();
    Serial.println("Burst transmission completed");
}

void AdvancedTx::transmitPattern(const RFSignal& signal, const uint32_t* pattern, size_t patternLength) {
    Serial.println("Pattern transmission starting...");
    
    startTransmission();
    
    for (size_t i = 0; i < patternLength && transmitting; i++) {
        rf->transmitSignal(signal);
        delay(pattern[i]);
    }
    
    stopTransmission();
    Serial.println("Pattern transmission completed");
}

void AdvancedTx::emergencyStop() {
    transmitting = false;
    stopTransmission();
    Serial.println("⚠️ EMERGENCY STOP ACTIVATED ⚠️");
}

bool AdvancedTx::isTransmitting() const {
    return transmitting;
}

bool AdvancedTx::checkTransmissionSafe(uint32_t durationMs) {
    if (durationMs > maxTxDuration) {
        Serial.println("ERROR: Transmission duration exceeds maximum allowed");
        return false;
    }
    
    // Check emergency stop button
    if (digitalRead(EMERGENCY_STOP_BUTTON) == LOW) {
        Serial.println("ERROR: Emergency stop button pressed");
        return false;
    }
    
    return true;
}

void AdvancedTx::setMaxDuration(uint32_t maxMs) {
    maxTxDuration = maxMs;
    Serial.print("Max TX duration set to: ");
    Serial.print(maxMs);
    Serial.println(" ms");
}

uint32_t AdvancedTx::getMaxDuration() const {
    return maxTxDuration;
}

String AdvancedTx::getLegalWarning() {
    return "⚠️ WARNING: ADVANCED TRANSMISSION FEATURES ⚠️\n\n"
           "These features are for AUTHORIZED testing only:\n"
           "✓ Security research on own devices\n"
           "✓ Authorized penetration testing\n"
           "✓ Educational demonstrations\n"
           "✓ Protocol development\n\n"
           "NEVER use for:\n"
           "✗ Unauthorized transmissions\n"
           "✗ Interfering with communications\n"
           "✗ Violating FCC/local regulations\n"
           "✗ Accessing systems without permission\n\n"
           "User assumes all legal responsibility.\n"
           "RF transmissions are REGULATED by law.";
}

void AdvancedTx::checkSafetyLimits(uint32_t durationMs) {
    if (transmitting && (millis() - txStartTime) > maxTxDuration) {
        emergencyStop();
        Serial.println("SAFETY: Maximum transmission time exceeded - stopped");
    }
}

void AdvancedTx::startTransmission() {
    transmitting = true;
    txStartTime = millis();
    Serial.println("Transmission started");
}

void AdvancedTx::stopTransmission() {
    transmitting = false;
    Serial.print("Transmission stopped - Duration: ");
    Serial.print(millis() - txStartTime);
    Serial.println(" ms");
}
