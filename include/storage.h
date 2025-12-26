#ifndef STORAGE_H
#define STORAGE_H

#include <Arduino.h>
#include <SPIFFS.h>
#include <ArduinoJson.h>
#include "rf_signal.h"
#include <vector>

class Storage {
public:
    Storage();
    bool begin();
    bool saveSignal(const RFSignal& signal, const String& filename);
    bool loadSignal(const String& filename, RFSignal& signal);
    bool deleteSignal(const String& filename);
    std::vector<String> listSignals();
    bool formatStorage();
    size_t getFreeSpace();
    size_t getTotalSpace();
    
private:
    bool initialized;
    String signalsPath;
    
    String signalToJson(const RFSignal& signal);
    bool jsonToSignal(const String& json, RFSignal& signal);
};

#endif // STORAGE_H
