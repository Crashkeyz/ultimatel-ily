#ifndef ADVANCED_TX_H
#define ADVANCED_TX_H

#include <Arduino.h>
#include "rf_signal.h"
#include "rf_module.h"

/**
 * Advanced Transmission Features
 * 
 * EDUCATIONAL AND RESEARCH PURPOSES ONLY
 * 
 * Provides advanced RF transmission capabilities for security research
 * and testing on authorized systems only.
 * 
 * WARNING: Many features are regulated and may be illegal without
 * proper authorization. User assumes all legal responsibility.
 */
class AdvancedTx {
public:
    AdvancedTx(RFModule* rfModule);
    
    // Frequency sweeping (for testing/research)
    void sweepFrequencies(float startFreq, float endFreq, float step, uint32_t dwellTime);
    
    // Continuous wave transmission (CW mode)
    void transmitCW(float frequency, uint32_t durationMs);
    
    // Signal injection at precise timing
    void transmitAtTime(const RFSignal& signal, uint32_t delayMs);
    
    // Protocol fuzzing (randomized testing)
    void fuzzProtocol(const RFSignal& baseSignal, uint32_t iterations);
    
    // Replay with variations
    void replayWithTimingVariation(const RFSignal& signal, float variation);
    void replayWithAmplitudeVariation(const RFSignal& signal, int8_t powerDbm);
    
    // Multi-burst transmission patterns
    void transmitBurst(const RFSignal& signal, uint32_t count, uint32_t interval);
    void transmitPattern(const RFSignal& signal, const uint32_t* pattern, size_t patternLength);
    
    // Emergency stop
    void emergencyStop();
    bool isTransmitting() const;
    
    // Safety checks
    bool checkTransmissionSafe(uint32_t durationMs);
    void setMaxDuration(uint32_t maxMs);
    uint32_t getMaxDuration() const;
    
    // Get legal warning
    static String getLegalWarning();
    
private:
    RFModule* rf;
    bool transmitting;
    uint32_t maxTxDuration;
    unsigned long txStartTime;
    
    // Safety checks
    void checkSafetyLimits(uint32_t durationMs);
    void startTransmission();
    void stopTransmission();
};

#endif // ADVANCED_TX_H
