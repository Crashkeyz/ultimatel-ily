#include "signal_intelligence.h"
#include <math.h>

SignalIntelligence::SignalIntelligence() {
}

ProtocolInfo SignalIntelligence::autoIdentifyProtocol(const RFSignal& signal) {
    ProtocolInfo info;
    info.protocolName = "Unknown";
    info.modulation = signal.modulation;
    info.encoding = ENCODING_UNKNOWN;
    info.confidence = 0.0;
    info.bitrate = 0;
    info.description = "";
    
    // Detect modulation type
    info.modulation = detectModulation(signal);
    
    // Detect encoding
    info.encoding = detectEncoding(signal);
    
    // Calculate bitrate
    info.bitrate = (uint32_t)calculateBitrate(signal);
    
    // Identify common protocols based on characteristics
    if (signal.timings.size() > 0) {
        // Check for Princeton PT2262 (very common)
        if (signal.timings.size() > 20 && signal.timings.size() < 100) {
            std::vector<uint16_t> unique = extractUniquePulseWidths(signal);
            if (unique.size() == 2 || unique.size() == 3) {
                info.protocolName = "Princeton PT2262";
                info.confidence = 0.7;
                info.description = "Common fixed-code remote protocol";
            }
        }
        
        // Check for EV1527
        if (signal.timings.size() >= 48 && signal.timings.size() <= 52) {
            info.protocolName = "EV1527";
            info.confidence = 0.65;
            info.description = "Learning code protocol";
        }
        
        // Check for weather station protocols
        if (info.bitrate > 1000 && info.bitrate < 10000) {
            info.protocolName = "Weather Station";
            info.confidence = 0.5;
            info.description = "Possible weather sensor protocol";
        }
    }
    
    return info;
}

ModulationType SignalIntelligence::detectModulation(const RFSignal& signal) {
    // Return the modulation from signal if already detected
    if (signal.modulation != MOD_UNKNOWN) {
        return signal.modulation;
    }
    
    // Analyze timing patterns to guess modulation
    // Most simple protocols use ASK/OOK
    return MOD_ASK_OOK;
}

EncodingType SignalIntelligence::detectEncoding(const RFSignal& signal) {
    if (signal.timings.size() < 4) {
        return ENCODING_UNKNOWN;
    }
    
    std::vector<uint16_t> unique = extractUniquePulseWidths(signal);
    
    // PWM typically has 2-3 unique pulse widths
    if (unique.size() == 2 || unique.size() == 3) {
        return ENCODING_PWM;
    }
    
    // Manchester has more consistent timing
    if (isPulseWidthConsistent(signal.timings, 0.3)) {
        return ENCODING_MANCHESTER;
    }
    
    // PPM has varying gaps
    if (unique.size() > 3) {
        return ENCODING_PPM;
    }
    
    return ENCODING_UNKNOWN;
}

std::vector<uint8_t> SignalIntelligence::extractBits(const RFSignal& signal) {
    std::vector<uint8_t> bits;
    
    if (signal.timings.size() < 2) {
        return bits;
    }
    
    // Simple bit extraction based on pulse width
    // Assume short pulse = 0, long pulse = 1
    std::vector<uint16_t> unique = extractUniquePulseWidths(signal);
    if (unique.size() < 2) return bits;
    
    uint16_t threshold = (unique[0] + unique[1]) / 2;
    
    for (size_t i = 0; i < signal.timings.size(); i++) {
        bits.push_back(signal.timings[i] > threshold ? 1 : 0);
    }
    
    return bits;
}

String SignalIntelligence::decodeBitstream(const std::vector<uint8_t>& bits) {
    String result = "";
    
    for (size_t i = 0; i < bits.size(); i++) {
        result += bits[i] ? "1" : "0";
        if ((i + 1) % 8 == 0) result += " ";
    }
    
    return result;
}

std::vector<uint8_t> SignalIntelligence::decodeManchesterBits(const RFSignal& signal) {
    std::vector<uint8_t> decoded;
    
    if (signal.timings.size() < 4) return decoded;
    
    // Manchester decoding: transition in middle of bit period
    // High-to-Low = 1, Low-to-High = 0
    for (size_t i = 0; i < signal.timings.size() - 1; i += 2) {
        // Simplified Manchester decoding
        if (signal.timings[i] < signal.timings[i + 1]) {
            decoded.push_back(0);
        } else {
            decoded.push_back(1);
        }
    }
    
    return decoded;
}

std::vector<uint8_t> SignalIntelligence::decodeDifferentialManchesterBits(const RFSignal& signal) {
    std::vector<uint8_t> decoded;
    
    if (signal.timings.size() < 4) return decoded;
    
    // Differential Manchester: transition at start = 0, no transition = 1
    bool lastState = false;
    
    for (size_t i = 0; i < signal.timings.size() - 1; i++) {
        bool currentState = signal.timings[i] > signal.timings[i + 1];
        if (currentState != lastState) {
            decoded.push_back(0);
        } else {
            decoded.push_back(1);
        }
        lastState = currentState;
    }
    
    return decoded;
}

bool SignalIntelligence::detectPreamble(const RFSignal& signal, uint32_t& preambleLength) {
    preambleLength = 0;
    
    if (signal.timings.size() < 10) return false;
    
    // Look for repeated pattern at start (common preamble characteristic)
    uint16_t firstTiming = signal.timings[0];
    const uint16_t tolerance = 50;
    
    for (size_t i = 1; i < signal.timings.size() && i < 20; i++) {
        if (abs((int16_t)signal.timings[i] - (int16_t)firstTiming) > tolerance) {
            preambleLength = i;
            return i > 4;  // At least 4 pulses for valid preamble
        }
    }
    
    return false;
}

bool SignalIntelligence::detectSyncWord(const RFSignal& signal, uint32_t& syncWord) {
    syncWord = 0;
    
    // Simplified sync word detection
    // Look for distinctive pattern after preamble
    uint32_t preambleLen;
    if (!detectPreamble(signal, preambleLen)) return false;
    
    if (preambleLen + 8 > signal.timings.size()) return false;
    
    // Extract potential sync word (simplified)
    for (size_t i = 0; i < 8 && (preambleLen + i) < signal.timings.size(); i++) {
        if (signal.timings[preambleLen + i] > signal.timings[0]) {
            syncWord |= (1 << i);
        }
    }
    
    return true;
}

bool SignalIntelligence::validateCRC(const uint8_t* data, size_t length, uint16_t crc) {
    if (length == 0) return false;
    
    uint16_t calculated = calculateCRC16(data, length);
    return calculated == crc;
}

uint16_t SignalIntelligence::calculateCRC16(const uint8_t* data, size_t length) {
    // CRC-16-CCITT
    uint16_t crc = 0xFFFF;
    
    for (size_t i = 0; i < length; i++) {
        crc ^= (uint16_t)data[i] << 8;
        for (int j = 0; j < 8; j++) {
            if (crc & 0x8000) {
                crc = (crc << 1) ^ 0x1021;
            } else {
                crc <<= 1;
            }
        }
    }
    
    return crc;
}

SignalQuality SignalIntelligence::analyzeQuality(const RFSignal& signal) {
    SignalQuality quality;
    quality.snr = 0.0;
    quality.avgPulseWidth = 0.0;
    quality.pulseVariance = 0.0;
    quality.cleanSignal = false;
    quality.qualityReport = "";
    
    if (signal.timings.size() == 0) {
        quality.qualityReport = "No timing data available";
        return quality;
    }
    
    // Calculate average pulse width
    uint32_t sum = 0;
    for (size_t i = 0; i < signal.timings.size(); i++) {
        sum += signal.timings[i];
    }
    quality.avgPulseWidth = (float)sum / signal.timings.size();
    
    // Calculate variance
    float variance = 0.0;
    for (size_t i = 0; i < signal.timings.size(); i++) {
        float diff = signal.timings[i] - quality.avgPulseWidth;
        variance += diff * diff;
    }
    quality.pulseVariance = variance / signal.timings.size();
    
    // Estimate SNR (simplified - based on timing consistency)
    float stdDev = sqrt(quality.pulseVariance);
    quality.snr = quality.avgPulseWidth / stdDev;
    
    // Determine if signal is clean
    quality.cleanSignal = (quality.snr > 5.0);
    
    // Generate report
    quality.qualityReport = "Signal Quality Analysis:\n";
    quality.qualityReport += "Average Pulse Width: " + String(quality.avgPulseWidth) + " µs\n";
    quality.qualityReport += "Pulse Variance: " + String(quality.pulseVariance) + "\n";
    quality.qualityReport += "SNR: " + String(quality.snr) + "\n";
    quality.qualityReport += "Clean Signal: " + String(quality.cleanSignal ? "Yes" : "No") + "\n";
    
    return quality;
}

float SignalIntelligence::calculateBitrate(const RFSignal& signal) {
    if (signal.timings.size() < 2) return 0.0;
    
    // Calculate average bit period
    float avgPeriod = calculateMean(signal.timings);
    
    // Bitrate = 1 / period (in bits per second)
    if (avgPeriod > 0) {
        return 1000000.0 / avgPeriod;  // Convert from µs to bps
    }
    
    return 0.0;
}

std::vector<uint16_t> SignalIntelligence::extractUniquePulseWidths(const RFSignal& signal) {
    std::vector<uint16_t> unique;
    const uint16_t tolerance = 50;  // 50 µs tolerance
    
    for (size_t i = 0; i < signal.timings.size(); i++) {
        bool found = false;
        for (size_t j = 0; j < unique.size(); j++) {
            if (abs((int16_t)signal.timings[i] - (int16_t)unique[j]) <= tolerance) {
                found = true;
                break;
            }
        }
        if (!found) {
            unique.push_back(signal.timings[i]);
        }
    }
    
    return unique;
}

String SignalIntelligence::exportAnalysis(const ProtocolInfo& info, const SignalQuality& quality) {
    String report = "=== Signal Intelligence Analysis ===\n\n";
    
    report += "Protocol Information:\n";
    report += "  Name: " + info.protocolName + "\n";
    report += "  Modulation: " + modulationToString(info.modulation) + "\n";
    report += "  Encoding: " + encodingToString(info.encoding) + "\n";
    report += "  Confidence: " + String(info.confidence * 100) + "%\n";
    report += "  Bitrate: " + String(info.bitrate) + " bps\n";
    report += "  Description: " + info.description + "\n\n";
    
    report += quality.qualityReport;
    
    return report;
}

float SignalIntelligence::calculateMean(const std::vector<uint16_t>& values) {
    if (values.size() == 0) return 0.0;
    
    uint32_t sum = 0;
    for (size_t i = 0; i < values.size(); i++) {
        sum += values[i];
    }
    
    return (float)sum / values.size();
}

float SignalIntelligence::calculateVariance(const std::vector<uint16_t>& values, float mean) {
    if (values.size() == 0) return 0.0;
    
    float variance = 0.0;
    for (size_t i = 0; i < values.size(); i++) {
        float diff = values[i] - mean;
        variance += diff * diff;
    }
    
    return variance / values.size();
}

bool SignalIntelligence::isPulseWidthConsistent(const std::vector<uint16_t>& timings, float tolerance) {
    if (timings.size() < 2) return false;
    
    float mean = calculateMean(timings);
    float variance = calculateVariance(timings, mean);
    float stdDev = sqrt(variance);
    
    // Check if standard deviation is within tolerance of mean
    return (stdDev / mean) < tolerance;
}

String SignalIntelligence::modulationToString(ModulationType mod) {
    switch (mod) {
        case MOD_ASK_OOK: return "ASK/OOK";
        case MOD_2FSK: return "2-FSK";
        case MOD_4FSK: return "4-FSK";
        case MOD_MSK: return "MSK";
        case MOD_GFSK: return "GFSK";
        default: return "Unknown";
    }
}

String SignalIntelligence::encodingToString(EncodingType enc) {
    switch (enc) {
        case ENCODING_MANCHESTER: return "Manchester";
        case ENCODING_DIFFERENTIAL_MANCHESTER: return "Differential Manchester";
        case ENCODING_PWM: return "PWM";
        case ENCODING_PPM: return "PPM";
        default: return "Unknown";
    }
}
