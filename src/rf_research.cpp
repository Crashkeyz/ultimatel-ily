#include "rf_research.h"
#include "config.h"

RFResearch::RFResearch(RFModule* rfModule) : rf(rfModule), researchModeEnabled(false),
    disclaimerAccepted(false), transmitting(false), txStartTime(0), 
    txMaxDuration(MAX_TX_DURATION_MS) {
}

void RFResearch::enableResearchMode(bool enable) {
#if ENABLE_RF_RESEARCH
    if (enable && !disclaimerAccepted) {
        Serial.println("ERROR: Must accept legal disclaimer before enabling research mode");
        return;
    }
    
    researchModeEnabled = enable;
    
    if (enable) {
        Serial.println("⚠️⚠️⚠️ RF RESEARCH MODE ENABLED ⚠️⚠️⚠️");
        Serial.println("EXTREME CAUTION REQUIRED");
        Serial.println("ILLEGAL WITHOUT AUTHORIZATION");
        logUsage("Research mode enabled");
    } else {
        Serial.println("RF Research mode disabled");
        logUsage("Research mode disabled");
    }
#else
    Serial.println("ERROR: RF Research features are disabled in config.h");
    Serial.println("These features require explicit activation due to legal concerns");
#endif
}

bool RFResearch::isResearchModeEnabled() const {
    return researchModeEnabled;
}

void RFResearch::acceptLegalDisclaimer() {
#if REQUIRE_DISCLAIMER_ACCEPTANCE
    Serial.println("==============================================");
    Serial.println("         LEGAL DISCLAIMER ACCEPTANCE          ");
    Serial.println("==============================================");
    Serial.println(getDetailedWarning());
    Serial.println("==============================================");
    Serial.println("By continuing, you accept all legal responsibility");
    Serial.println("Disclaimer accepted - logged for compliance");
    
    disclaimerAccepted = true;
    logUsage("Legal disclaimer accepted");
#else
    disclaimerAccepted = true;
#endif
}

bool RFResearch::hasAcceptedDisclaimer() const {
    return disclaimerAccepted;
}

void RFResearch::sweepJammer(float startFreq, float endFreq) {
    Serial.println("⚠️⚠️⚠️ CRITICAL WARNING ⚠️⚠️⚠️");
    Serial.println("FREQUENCY SWEEP JAMMER - EDUCATIONAL ONLY");
    Serial.println("ILLEGAL WITHOUT AUTHORIZATION");
    
    if (!performSafetyCheck()) {
        return;
    }
    
    logUsage("Sweep jammer (EDUCATIONAL)");
    
    Serial.println("Educational demonstration:");
    Serial.print("Theoretical sweep from ");
    Serial.print(startFreq);
    Serial.print(" to ");
    Serial.print(endFreq);
    Serial.println(" MHz");
    Serial.println("ACTUAL TRANSMISSION DISABLED FOR SAFETY");
    Serial.println("This demonstrates the CONCEPT only");
    Serial.println("Real implementation would violate regulations");
}

void RFResearch::cwTransmit(float frequency, uint32_t durationMs) {
    Serial.println("⚠️⚠️⚠️ CRITICAL WARNING ⚠️⚠️⚠️");
    Serial.println("CONTINUOUS WAVE TRANSMISSION - EDUCATIONAL ONLY");
    Serial.println("REGULATED BY FCC/LOCAL AUTHORITIES");
    
    if (!performSafetyCheck()) {
        return;
    }
    
    if (durationMs > txMaxDuration) {
        Serial.println("ERROR: Duration exceeds safety limit");
        return;
    }
    
    logUsage("CW transmit (EDUCATIONAL)");
    
    Serial.println("Educational demonstration:");
    Serial.print("Theoretical CW at ");
    Serial.print(frequency);
    Serial.print(" MHz for ");
    Serial.print(durationMs);
    Serial.println(" ms");
    Serial.println("ACTUAL TRANSMISSION DISABLED FOR SAFETY");
}

void RFResearch::pulseJammer(uint32_t onTimeMs, uint32_t offTimeMs, uint32_t durationMs) {
    Serial.println("⚠️⚠️⚠️ CRITICAL WARNING ⚠️⚠️⚠️");
    Serial.println("PULSE JAMMER - EDUCATIONAL ONLY");
    Serial.println("ILLEGAL - FEDERAL CRIME IN MOST JURISDICTIONS");
    
    if (!performSafetyCheck()) {
        return;
    }
    
    logUsage("Pulse jammer (EDUCATIONAL)");
    
    Serial.println("Educational demonstration:");
    Serial.print("Theoretical pulse pattern: ");
    Serial.print(onTimeMs);
    Serial.print("ms ON, ");
    Serial.print(offTimeMs);
    Serial.print("ms OFF, duration ");
    Serial.print(durationMs);
    Serial.println("ms");
    Serial.println("ACTUAL TRANSMISSION DISABLED FOR SAFETY");
    Serial.println("Real jamming devices are ILLEGAL and carry severe penalties");
}

void RFResearch::noiseGenerator(float frequency, uint32_t durationMs) {
    Serial.println("⚠️⚠️⚠️ CRITICAL WARNING ⚠️⚠️⚠️");
    Serial.println("NOISE GENERATOR - EDUCATIONAL ONLY");
    
    if (!performSafetyCheck()) {
        return;
    }
    
    logUsage("Noise generator (EDUCATIONAL)");
    
    Serial.println("Educational demonstration:");
    Serial.print("Theoretical noise at ");
    Serial.print(frequency);
    Serial.print(" MHz for ");
    Serial.print(durationMs);
    Serial.println(" ms");
    Serial.println("ACTUAL TRANSMISSION DISABLED FOR SAFETY");
}

void RFResearch::emergencyStop() {
    transmitting = false;
    researchModeEnabled = false;
    
    Serial.println("⚠️⚠️⚠️ EMERGENCY STOP ACTIVATED ⚠️⚠️⚠️");
    Serial.println("All RF research operations halted");
    
    logUsage("EMERGENCY STOP");
}

bool RFResearch::checkEmergencyStop() {
    // Check emergency stop button
    if (digitalRead(EMERGENCY_STOP_BUTTON) == LOW) {
        emergencyStop();
        return true;
    }
    
    // Check timeout
    if (transmitting && (millis() - txStartTime) > RESEARCH_MODE_TIMEOUT_MS) {
        Serial.println("Research mode timeout - safety shutdown");
        emergencyStop();
        return true;
    }
    
    return false;
}

uint32_t RFResearch::getRemainingTime() const {
    if (!transmitting) return 0;
    
    uint32_t elapsed = millis() - txStartTime;
    if (elapsed >= txMaxDuration) return 0;
    
    return txMaxDuration - elapsed;
}

String RFResearch::getLegalWarning() {
    return "⚠️⚠️⚠️ EXTREME WARNING ⚠️⚠️⚠️\n\n"
           "RF RESEARCH TOOLS - ILLEGAL WITHOUT AUTHORIZATION\n\n"
           "These features are DISABLED BY DEFAULT and for\n"
           "EDUCATIONAL PURPOSES ONLY.\n\n"
           "Using RF jamming/interference devices is a\n"
           "FEDERAL CRIME under:\n"
           "- FCC regulations (USA)\n"
           "- Similar laws in all countries\n\n"
           "Penalties include:\n"
           "- Heavy fines ($100,000+)\n"
           "- Imprisonment\n"
           "- Equipment seizure\n"
           "- Criminal record\n\n"
           "DO NOT PROCEED unless you have:\n"
           "✓ Written legal authorization\n"
           "✓ Appropriate licenses\n"
           "✓ Controlled environment\n"
           "✓ Full legal compliance\n\n"
           "USER ASSUMES ALL LEGAL RESPONSIBILITY";
}

String RFResearch::getDetailedWarning() {
    return "═══════════════════════════════════════════════════════\n"
           "     RF RESEARCH LEGAL DISCLAIMER & WARNING\n"
           "═══════════════════════════════════════════════════════\n\n"
           "⚠️  EDUCATIONAL PURPOSES ONLY  ⚠️\n\n"
           "The RF research features in this firmware are designed\n"
           "EXCLUSIVELY for educational purposes to teach about:\n"
           "  • RF security vulnerabilities\n"
           "  • Wireless protocol weaknesses\n"
           "  • Communication system hardening\n"
           "  • Defensive countermeasures\n\n"
           "═══════════════════════════════════════════════════════\n"
           "                    LEGAL NOTICE\n"
           "═══════════════════════════════════════════════════════\n\n"
           "RF JAMMING AND INTERFERENCE ARE ILLEGAL:\n\n"
           "United States:\n"
           "  • Communications Act of 1934, as amended\n"
           "  • 47 U.S.C. § 333 - Willful interference\n"
           "  • FCC Rules Part 15\n"
           "  • Penalties: Up to $112,500 per violation + imprisonment\n\n"
           "International:\n"
           "  • ITU Radio Regulations\n"
           "  • Local telecommunications laws\n"
           "  • Criminal penalties in all jurisdictions\n\n"
           "═══════════════════════════════════════════════════════\n"
           "                 PROHIBITED USES\n"
           "═══════════════════════════════════════════════════════\n\n"
           "DO NOT USE THESE FEATURES TO:\n"
           "  ✗ Interfere with any communications\n"
           "  ✗ Jam cellular/WiFi/GPS signals\n"
           "  ✗ Disrupt emergency services\n"
           "  ✗ Access unauthorized systems\n"
           "  ✗ Bypass security mechanisms\n"
           "  ✗ Violate any laws or regulations\n\n"
           "═══════════════════════════════════════════════════════\n"
           "                  AUTHORIZED USES\n"
           "═══════════════════════════════════════════════════════\n\n"
           "These features MAY ONLY be used:\n"
           "  ✓ On your own devices in controlled environments\n"
           "  ✓ With proper legal authorization and licenses\n"
           "  ✓ In authorized security research facilities\n"
           "  ✓ For educational demonstrations with permission\n"
           "  ✓ In compliance with ALL applicable laws\n\n"
           "═══════════════════════════════════════════════════════\n"
           "              ASSUMPTION OF RESPONSIBILITY\n"
           "═══════════════════════════════════════════════════════\n\n"
           "By using these features, YOU ACKNOWLEDGE:\n\n"
           "  1. You have read and understood this warning\n"
           "  2. You understand the legal implications\n"
           "  3. You have obtained all necessary authorizations\n"
           "  4. You accept FULL legal responsibility\n"
           "  5. The developers assume NO liability\n"
           "  6. You will comply with all applicable laws\n\n"
           "═══════════════════════════════════════════════════════\n"
           "                     DISCLAIMER\n"
           "═══════════════════════════════════════════════════════\n\n"
           "The developers of this firmware:\n"
           "  • Provide these tools for EDUCATIONAL purposes only\n"
           "  • Do NOT endorse illegal activities\n"
           "  • Accept NO responsibility for misuse\n"
           "  • Will cooperate with law enforcement\n"
           "  • Strongly discourage any illegal use\n\n"
           "═══════════════════════════════════════════════════════\n\n"
           "If you do not agree to these terms or cannot comply\n"
           "with all applicable laws, DO NOT USE these features.\n\n"
           "═══════════════════════════════════════════════════════";
}

bool RFResearch::performSafetyCheck() {
    // Check if research mode is enabled
    if (!researchModeEnabled) {
        Serial.println("ERROR: Research mode not enabled");
        return false;
    }
    
    // Check disclaimer acceptance
    if (!disclaimerAccepted) {
        Serial.println("ERROR: Legal disclaimer not accepted");
        return false;
    }
    
    // Check emergency stop
    if (checkEmergencyStop()) {
        return false;
    }
    
    // Check if feature is enabled in config
#if !ENABLE_RF_RESEARCH
    Serial.println("ERROR: RF Research features disabled in config.h");
    Serial.println("Set ENABLE_RF_RESEARCH to 1 to enable (NOT RECOMMENDED)");
    return false;
#endif
    
    return true;
}

void RFResearch::checkAuthorization() {
    Serial.println("⚠️ AUTHORIZATION CHECK ⚠️");
    Serial.println("Verify you have:");
    Serial.println("  [ ] Written legal authorization");
    Serial.println("  [ ] Appropriate licenses");
    Serial.println("  [ ] Controlled environment");
    Serial.println("  [ ] Legal compliance documentation");
}

void RFResearch::logUsage(const String& feature) {
    // Log all research feature usage for compliance
    Serial.print("[RESEARCH LOG] ");
    Serial.print(millis());
    Serial.print(" - ");
    Serial.println(feature);
    
    // In production, this should log to persistent storage
    // for audit trail and legal compliance
}
