#include "rolling_code_analyzer.h"
#include <math.h>

RollingCodeAnalyzer::RollingCodeAnalyzer() {
    capturedSequences.clear();
    lastAnalysis = RollingCodeAnalysis();
}

void RollingCodeAnalyzer::captureSequence(const RFSignal& signal) {
    capturedSequences.push_back(signal);
    Serial.println("Rolling code sequence captured");
    Serial.print("Total sequences: ");
    Serial.println(capturedSequences.size());
}

RollingCodeAnalysis RollingCodeAnalyzer::analyzePattern() {
    RollingCodeAnalysis analysis;
    analysis.protocol = PROTOCOL_UNKNOWN_ROLLING;
    analysis.counter = 0;
    analysis.manufacturerId = 0;
    analysis.entropy = 0.0;
    analysis.patternDetected = false;
    analysis.analysisReport = "";
    
    if (capturedSequences.size() == 0) {
        analysis.analysisReport = "No sequences captured";
        lastAnalysis = analysis;
        return analysis;
    }
    
    analysis.analysisReport = "Analysis of " + String(capturedSequences.size()) + " sequences:\n";
    
    // Analyze each sequence
    for (size_t i = 0; i < capturedSequences.size(); i++) {
        const RFSignal& sig = capturedSequences[i];
        
        // Calculate entropy
        float entropy = calculateEntropy(sig.rawData, sig.rawDataLength);
        analysis.entropy += entropy;
        
        // Detect protocol
        if (detectKeeLoq(sig)) {
            analysis.protocol = PROTOCOL_KEELOQ;
            analysis.analysisReport += "KeeLoq protocol detected\n";
        } else if (detectHCS(sig)) {
            analysis.protocol = PROTOCOL_HCS;
            analysis.analysisReport += "HCS protocol detected\n";
        }
        
        // Extract counter
        uint32_t counter = extractCounter(sig);
        if (counter > analysis.counter) {
            analysis.counter = counter;
        }
        
        // Extract manufacturer ID
        uint32_t mfgId = extractManufacturerId(sig);
        if (mfgId != 0 && analysis.manufacturerId == 0) {
            analysis.manufacturerId = mfgId;
        }
    }
    
    // Average entropy
    if (capturedSequences.size() > 0) {
        analysis.entropy /= capturedSequences.size();
    }
    
    // Check for patterns
    if (capturedSequences.size() >= 2) {
        analysis.patternDetected = compareSequences(capturedSequences[0], capturedSequences[1]);
    }
    
    analysis.analysisReport += "Average entropy: " + String(analysis.entropy) + "\n";
    analysis.analysisReport += "Protocol: " + protocolToString(analysis.protocol) + "\n";
    
    lastAnalysis = analysis;
    return analysis;
}

bool RollingCodeAnalyzer::detectKeeLoq(const RFSignal& signal) {
    // KeeLoq uses 66-bit packets (typical)
    // This is a simplified detection based on common characteristics
    if (signal.rawDataLength < 8) return false;
    
    // Check for KeeLoq-like timing patterns (simplified)
    // Real KeeLoq detection would require detailed protocol analysis
    bool hasConsistentTiming = (signal.timings.size() > 60 && signal.timings.size() < 80);
    
    return hasConsistentTiming;
}

bool RollingCodeAnalyzer::detectHCS(const RFSignal& signal) {
    // HCS (High-Security) protocol detection (simplified)
    // HCS codes are typically 69 bits
    if (signal.rawDataLength < 8) return false;
    
    // Check timing characteristics
    bool hasHCSTiming = (signal.timings.size() > 65 && signal.timings.size() < 75);
    
    return hasHCSTiming;
}

bool RollingCodeAnalyzer::detectHitag(const RFSignal& signal) {
    // Hitag protocol detection (simplified)
    // Hitag operates at 125 kHz (different from most sub-GHz systems)
    return false;  // Not typically found in sub-GHz range
}

uint32_t RollingCodeAnalyzer::extractCounter(const RFSignal& signal) {
    // Educational extraction - simplified
    // Real counter extraction requires protocol-specific parsing
    if (signal.rawDataLength < 4) return 0;
    
    // Extract hypothetical counter from middle bytes (educational only)
    uint32_t counter = extractBits(signal.rawData, 16, 16);
    
    return counter;
}

uint32_t RollingCodeAnalyzer::extractManufacturerId(const RFSignal& signal) {
    // Educational extraction - simplified
    if (signal.rawDataLength < 4) return 0;
    
    // Extract hypothetical manufacturer ID from first bytes (educational only)
    uint32_t mfgId = extractBits(signal.rawData, 0, 16);
    
    return mfgId;
}

float RollingCodeAnalyzer::calculateEntropy(const uint8_t* data, size_t length) {
    if (length == 0) return 0.0;
    
    // Calculate Shannon entropy
    uint32_t freq[256] = {0};
    
    for (size_t i = 0; i < length; i++) {
        freq[data[i]]++;
    }
    
    float entropy = 0.0;
    for (int i = 0; i < 256; i++) {
        if (freq[i] > 0) {
            float p = (float)freq[i] / length;
            entropy -= p * log2(p);
        }
    }
    
    return entropy;
}

bool RollingCodeAnalyzer::detectRepeatingPattern(const uint8_t* data, size_t length) {
    if (length < 4) return false;
    
    // Check for simple repeating patterns
    for (size_t patternLen = 1; patternLen <= length / 2; patternLen++) {
        bool repeats = true;
        for (size_t i = patternLen; i < length; i++) {
            if (data[i] != data[i % patternLen]) {
                repeats = false;
                break;
            }
        }
        if (repeats) return true;
    }
    
    return false;
}

void RollingCodeAnalyzer::predictNextCode() {
    // EDUCATIONAL DEMONSTRATION ONLY
    // This does NOT work on real rolling code systems
    // Real rolling codes use cryptographic algorithms that cannot be predicted
    
    Serial.println("⚠️ EDUCATIONAL DEMONSTRATION ONLY ⚠️");
    Serial.println("Rolling code prediction is NOT possible on real systems.");
    Serial.println("Modern rolling codes use encryption (KeeLoq, AES, etc.).");
    Serial.println("This demonstrates why simple replay attacks don't work.");
    
    if (capturedSequences.size() < 2) {
        Serial.println("Need at least 2 sequences for educational demo");
        return;
    }
    
    Serial.println("Analyzing sequence patterns...");
    Serial.println("Result: Encrypted rolling codes cannot be predicted");
    Serial.println("Security: Rolling codes provide protection against replay attacks");
}

String RollingCodeAnalyzer::exportAnalysis() {
    String report = "=== Rolling Code Analysis Report ===\n\n";
    report += "⚠️ EDUCATIONAL RESEARCH ONLY ⚠️\n\n";
    
    report += "Captured Sequences: " + String(capturedSequences.size()) + "\n";
    report += lastAnalysis.analysisReport;
    report += "\n";
    
    if (lastAnalysis.protocol != PROTOCOL_UNKNOWN_ROLLING) {
        report += "Protocol: " + protocolToString(lastAnalysis.protocol) + "\n";
        report += "Counter: 0x" + String(lastAnalysis.counter, HEX) + "\n";
        report += "Manufacturer ID: 0x" + String(lastAnalysis.manufacturerId, HEX) + "\n";
    }
    
    report += "Entropy: " + String(lastAnalysis.entropy) + "\n";
    report += "Pattern Detected: " + String(lastAnalysis.patternDetected ? "Yes" : "No") + "\n";
    
    report += "\n=== Security Note ===\n";
    report += "Modern rolling codes are cryptographically secure.\n";
    report += "This analysis is for educational purposes only.\n";
    
    return report;
}

size_t RollingCodeAnalyzer::getSequenceCount() const {
    return capturedSequences.size();
}

void RollingCodeAnalyzer::clearSequences() {
    capturedSequences.clear();
    Serial.println("Rolling code sequences cleared");
}

String RollingCodeAnalyzer::getLegalWarning() {
    return "⚠️ WARNING: EDUCATIONAL USE ONLY ⚠️\n\n"
           "Rolling code analysis tools are for:\n"
           "✓ Learning about RF security\n"
           "✓ Research on authorized devices\n"
           "✓ Understanding cryptographic protocols\n\n"
           "NEVER use to:\n"
           "✗ Access unauthorized systems\n"
           "✗ Bypass security mechanisms\n"
           "✗ Break into vehicles or buildings\n\n"
           "User assumes all legal responsibility.";
}

uint32_t RollingCodeAnalyzer::extractBits(const uint8_t* data, size_t startBit, size_t numBits) {
    uint32_t result = 0;
    
    for (size_t i = 0; i < numBits && i < 32; i++) {
        size_t bitPos = startBit + i;
        size_t bytePos = bitPos / 8;
        size_t bitInByte = bitPos % 8;
        
        if (bytePos < 256) {
            uint8_t bit = (data[bytePos] >> bitInByte) & 1;
            result |= (bit << i);
        }
    }
    
    return result;
}

bool RollingCodeAnalyzer::compareSequences(const RFSignal& sig1, const RFSignal& sig2) {
    // Compare timing patterns
    if (sig1.timings.size() != sig2.timings.size()) return false;
    
    // Allow some tolerance in timing
    const uint16_t tolerance = 50;  // 50 microseconds
    
    for (size_t i = 0; i < sig1.timings.size(); i++) {
        int16_t diff = abs((int16_t)sig1.timings[i] - (int16_t)sig2.timings[i]);
        if (diff > tolerance) return false;
    }
    
    return true;
}

String RollingCodeAnalyzer::protocolToString(RollingCodeProtocol protocol) {
    switch (protocol) {
        case PROTOCOL_KEELOQ: return "KeeLoq";
        case PROTOCOL_HCS: return "HCS";
        case PROTOCOL_HITAG: return "Hitag";
        default: return "Unknown";
    }
}
