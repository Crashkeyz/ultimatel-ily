#ifndef RF_MODULE_H
#define RF_MODULE_H

#include <Arduino.h>
#include <ELECHOUSE_CC1101_SRC_DRV.h>
#include "config.h"
#include "rf_signal.h"

class RFModule {
public:
    RFModule();
    bool begin();
    void setFrequency(float freq);
    float getFrequency();
    void setModulation(ModulationType mod);
    void startReceive();
    void stopReceive();
    bool signalDetected();
    RFSignal captureSignal();
    void transmitSignal(const RFSignal& signal);
    void scanFrequencies(float startFreq, float endFreq, float step);
    
private:
    float currentFrequency;
    ModulationType currentModulation;
    bool receiving;
    
    void configureCC1101();
    void setupRegisters();
};

#endif // RF_MODULE_H
