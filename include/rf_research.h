#ifndef RF_RESEARCH_H
#define RF_RESEARCH_H

#include <Arduino.h>
#include "rf_module.h"
#include "config.h"

/**
 * RF Research Tools
 * 
 * ⚠️ EDUCATIONAL PURPOSES ONLY - DISABLED BY DEFAULT ⚠️
 * 
 * WARNING: The features in this class are for educational RF security
 * research ONLY and are ILLEGAL without proper authorization.
 * 
 * These tools are designed to teach about RF vulnerabilities and
 * countermeasures. They must ONLY be used:
 * - On your own devices
 * - In authorized security testing
 * - In controlled lab environments
 * - With proper legal authorization
 * 
 * NEVER use these features:
 * - Against unauthorized systems
 * - To interfere with communications
 * - For malicious purposes
 * - In violation of local laws
 * 
 * Jamming and unauthorized RF interference are FEDERAL CRIMES in most
 * countries with severe penalties including fines and imprisonment.
 * 
 * USER ASSUMES ALL LEGAL RESPONSIBILITY.
 */
class RFResearch {
public:
    RFResearch(RFModule* rfModule);
    
    // Feature enable/disable (disabled by default)
    void enableResearchMode(bool enable);
    bool isResearchModeEnabled() const;
    
    // Legal disclaimer acceptance (required before use)
    void acceptLegalDisclaimer();
    bool hasAcceptedDisclaimer() const;
    
    // EDUCATIONAL ONLY: Frequency sweep research
    // Used to study RF spectrum and understand interference effects
    void sweepJammer(float startFreq, float endFreq);
    
    // EDUCATIONAL ONLY: Continuous wave transmission
    // Used to understand carrier wave behavior
    void cwTransmit(float frequency, uint32_t durationMs);
    
    // EDUCATIONAL ONLY: Pulsed transmission research
    // Used to study timing-based RF patterns
    void pulseJammer(uint32_t onTimeMs, uint32_t offTimeMs, uint32_t durationMs);
    
    // EDUCATIONAL ONLY: Noise generation research
    // Used to understand signal-to-noise ratios
    void noiseGenerator(float frequency, uint32_t durationMs);
    
    // Emergency stop (kills all transmission immediately)
    void emergencyStop();
    
    // Safety features
    bool checkEmergencyStop();
    uint32_t getRemainingTime() const;
    
    // Authorization check (public for UI access)
    void checkAuthorization();
    
    // Legal warnings
    static String getLegalWarning();
    static String getDetailedWarning();
    
private:
    RFModule* rf;
    bool researchModeEnabled;
    bool disclaimerAccepted;
    bool transmitting;
    unsigned long txStartTime;
    uint32_t txMaxDuration;
    
    // Safety checks
    bool performSafetyCheck();
    void logUsage(const String& feature);
};

#endif // RF_RESEARCH_H
