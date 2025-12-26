#ifndef ROLLING_CODE_ANALYZER_H
#define ROLLING_CODE_ANALYZER_H

#include <Arduino.h>
#include <vector>
#include "rf_signal.h"

// Rolling code protocol types
enum RollingCodeProtocol {
    PROTOCOL_KEELOQ,
    PROTOCOL_HCS,
    PROTOCOL_HITAG,
    PROTOCOL_UNKNOWN_ROLLING
};

// Rolling code analysis result
struct RollingCodeAnalysis {
    RollingCodeProtocol protocol;
    uint32_t counter;
    uint32_t manufacturerId;
    float entropy;
    bool patternDetected;
    String analysisReport;
};

/**
 * Rolling Code Analyzer
 * 
 * EDUCATIONAL AND RESEARCH PURPOSES ONLY
 * 
 * This class provides tools for analyzing rolling code transmissions
 * to understand their security mechanisms. It is designed for:
 * - Learning about RF security
 * - Understanding rolling code protocols
 * - Security research on authorized devices only
 * 
 * WARNING: Using this to access unauthorized systems is illegal.
 * User assumes all legal responsibility.
 */
class RollingCodeAnalyzer {
public:
    RollingCodeAnalyzer();
    
    // Capture and store rolling code sequence
    void captureSequence(const RFSignal& signal);
    
    // Analyze captured sequences for patterns
    RollingCodeAnalysis analyzePattern();
    
    // Protocol detection
    bool detectKeeLoq(const RFSignal& signal);
    bool detectHCS(const RFSignal& signal);
    bool detectHitag(const RFSignal& signal);
    
    // Extract information (educational)
    uint32_t extractCounter(const RFSignal& signal);
    uint32_t extractManufacturerId(const RFSignal& signal);
    
    // Statistical analysis
    float calculateEntropy(const uint8_t* data, size_t length);
    bool detectRepeatingPattern(const uint8_t* data, size_t length);
    
    // Educational research (prediction study - does not work on real systems)
    void predictNextCode();  // Educational demonstration only
    
    // Export analysis for research
    String exportAnalysis();
    
    // Get captured sequence count
    size_t getSequenceCount() const;
    
    // Clear captured sequences
    void clearSequences();
    
    // Get legal warning
    static String getLegalWarning();
    
private:
    std::vector<RFSignal> capturedSequences;
    RollingCodeAnalysis lastAnalysis;
    
    // Helper functions
    uint32_t extractBits(const uint8_t* data, size_t startBit, size_t numBits);
    bool compareSequences(const RFSignal& sig1, const RFSignal& sig2);
    String protocolToString(RollingCodeProtocol protocol);
};

#endif // ROLLING_CODE_ANALYZER_H
