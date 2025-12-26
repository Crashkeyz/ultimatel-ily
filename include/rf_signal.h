#ifndef RF_SIGNAL_H
#define RF_SIGNAL_H

#include <Arduino.h>
#include <vector>

// Signal modulation types
enum ModulationType {
    MOD_ASK_OOK,
    MOD_2FSK,
    MOD_4FSK,
    MOD_MSK,
    MOD_GFSK,
    MOD_UNKNOWN
};

// Signal structure
struct RFSignal {
    float frequency;
    ModulationType modulation;
    std::vector<uint16_t> timings;  // Pulse timings in microseconds
    uint32_t captureTime;
    String name;
    uint8_t rawData[256];
    size_t rawDataLength;
};

// Protocol types
enum ProtocolType {
    PROTOCOL_RAW,
    PROTOCOL_FIXED_CODE,
    PROTOCOL_ROLLING_CODE,
    PROTOCOL_UNKNOWN
};

#endif // RF_SIGNAL_H
