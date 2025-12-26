#ifndef SIGNAL_INTELLIGENCE_H
#define SIGNAL_INTELLIGENCE_H

#include <Arduino.h>
#include "rf_signal.h"

// Signal encoding types
enum EncodingType {
    ENCODING_MANCHESTER,
    ENCODING_DIFFERENTIAL_MANCHESTER,
    ENCODING_PWM,
    ENCODING_PPM,
    ENCODING_UNKNOWN
};

// Signal quality metrics
struct SignalQuality {
    float snr;           // Signal-to-noise ratio
    float avgPulseWidth;
    float pulseVariance;
    bool cleanSignal;
    String qualityReport;
};

// Protocol identification result
struct ProtocolInfo {
    String protocolName;
    ModulationType modulation;
    EncodingType encoding;
    float confidence;
    uint32_t bitrate;
    String description;
};

/**
 * Signal Intelligence Module
 * 
 * EDUCATIONAL AND RESEARCH PURPOSES ONLY
 * 
 * Provides advanced signal analysis and protocol identification
 * capabilities for RF security research and education.
 */
class SignalIntelligence {
public:
    SignalIntelligence();
    
    // Automatic protocol identification
    ProtocolInfo autoIdentifyProtocol(const RFSignal& signal);
    
    // Modulation detection
    ModulationType detectModulation(const RFSignal& signal);
    
    // Timing pattern recognition
    EncodingType detectEncoding(const RFSignal& signal);
    
    // Bit extraction and decoding
    std::vector<uint8_t> extractBits(const RFSignal& signal);
    String decodeBitstream(const std::vector<uint8_t>& bits);
    
    // Manchester decoding
    std::vector<uint8_t> decodeManchesterBits(const RFSignal& signal);
    std::vector<uint8_t> decodeDifferentialManchesterBits(const RFSignal& signal);
    
    // Preamble and sync word detection
    bool detectPreamble(const RFSignal& signal, uint32_t& preambleLength);
    bool detectSyncWord(const RFSignal& signal, uint32_t& syncWord);
    
    // CRC validation
    bool validateCRC(const uint8_t* data, size_t length, uint16_t crc);
    uint16_t calculateCRC16(const uint8_t* data, size_t length);
    
    // Signal quality analysis
    SignalQuality analyzeQuality(const RFSignal& signal);
    
    // Timing analysis
    float calculateBitrate(const RFSignal& signal);
    std::vector<uint16_t> extractUniquePulseWidths(const RFSignal& signal);
    
    // Export analysis
    String exportAnalysis(const ProtocolInfo& info, const SignalQuality& quality);
    
private:
    // Helper functions
    float calculateMean(const std::vector<uint16_t>& values);
    float calculateVariance(const std::vector<uint16_t>& values, float mean);
    bool isPulseWidthConsistent(const std::vector<uint16_t>& timings, float tolerance);
    String modulationToString(ModulationType mod);
    String encodingToString(EncodingType enc);
};

#endif // SIGNAL_INTELLIGENCE_H
