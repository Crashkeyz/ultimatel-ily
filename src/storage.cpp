#include "storage.h"

Storage::Storage() 
    : initialized(false)
    , signalsPath("/signals") {
}

bool Storage::begin() {
    if (!SPIFFS.begin(true)) {
        Serial.println("SPIFFS Mount Failed");
        return false;
    }
    
    initialized = true;
    Serial.println("SPIFFS initialized");
    
    // Create signals directory if it doesn't exist
    if (!SPIFFS.exists(signalsPath)) {
        SPIFFS.mkdir(signalsPath);
    }
    
    return true;
}

bool Storage::saveSignal(const RFSignal& signal, const String& filename) {
    if (!initialized) return false;
    
    String filepath = signalsPath + "/" + filename + ".json";
    File file = SPIFFS.open(filepath, FILE_WRITE);
    
    if (!file) {
        Serial.println("Failed to open file for writing");
        return false;
    }
    
    String jsonStr = signalToJson(signal);
    file.print(jsonStr);
    file.close();
    
    Serial.println("Signal saved: " + filepath);
    return true;
}

bool Storage::loadSignal(const String& filename, RFSignal& signal) {
    if (!initialized) return false;
    
    String filepath = signalsPath + "/" + filename + ".json";
    File file = SPIFFS.open(filepath, FILE_READ);
    
    if (!file) {
        Serial.println("Failed to open file for reading");
        return false;
    }
    
    String jsonStr = file.readString();
    file.close();
    
    return jsonToSignal(jsonStr, signal);
}

bool Storage::deleteSignal(const String& filename) {
    if (!initialized) return false;
    
    String filepath = signalsPath + "/" + filename + ".json";
    return SPIFFS.remove(filepath);
}

std::vector<String> Storage::listSignals() {
    std::vector<String> signals;
    
    if (!initialized) return signals;
    
    File root = SPIFFS.open(signalsPath);
    if (!root || !root.isDirectory()) {
        return signals;
    }
    
    File file = root.openNextFile();
    while (file) {
        if (!file.isDirectory()) {
            String name = file.name();
            if (name.endsWith(".json")) {
                name.remove(name.length() - 5);  // Remove .json extension
                signals.push_back(name);
            }
        }
        file = root.openNextFile();
    }
    
    return signals;
}

bool Storage::formatStorage() {
    if (!initialized) return false;
    
    SPIFFS.format();
    Serial.println("Storage formatted");
    return true;
}

size_t Storage::getFreeSpace() {
    return SPIFFS.totalBytes() - SPIFFS.usedBytes();
}

size_t Storage::getTotalSpace() {
    return SPIFFS.totalBytes();
}

String Storage::signalToJson(const RFSignal& signal) {
    JsonDocument doc;
    
    doc["frequency"] = signal.frequency;
    doc["modulation"] = (int)signal.modulation;
    doc["captureTime"] = signal.captureTime;
    doc["name"] = signal.name;
    
    JsonArray timingsArray = doc["timings"].to<JsonArray>();
    for (size_t i = 0; i < signal.timings.size(); i++) {
        timingsArray.add(signal.timings[i]);
    }
    
    JsonArray rawDataArray = doc["rawData"].to<JsonArray>();
    for (size_t i = 0; i < signal.rawDataLength; i++) {
        rawDataArray.add(signal.rawData[i]);
    }
    
    String output;
    serializeJson(doc, output);
    return output;
}

bool Storage::jsonToSignal(const String& json, RFSignal& signal) {
    JsonDocument doc;
    DeserializationError error = deserializeJson(doc, json);
    
    if (error) {
        Serial.print("JSON parsing failed: ");
        Serial.println(error.c_str());
        return false;
    }
    
    signal.frequency = doc["frequency"];
    signal.modulation = (ModulationType)(int)doc["modulation"];
    signal.captureTime = doc["captureTime"];
    signal.name = doc["name"].as<String>();
    
    signal.timings.clear();
    JsonArray timingsArray = doc["timings"];
    for (JsonVariant v : timingsArray) {
        signal.timings.push_back(v.as<uint16_t>());
    }
    
    signal.rawDataLength = 0;
    JsonArray rawDataArray = doc["rawData"];
    for (JsonVariant v : rawDataArray) {
        if (signal.rawDataLength < 256) {
            signal.rawData[signal.rawDataLength++] = v.as<uint8_t>();
        }
    }
    
    return true;
}
