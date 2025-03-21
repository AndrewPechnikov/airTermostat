#ifndef DIAGNOSTIC_MANAGER_H
#define DIAGNOSTIC_MANAGER_H


#include <Arduino.h>
#include <EEPROM.h>

struct DiagnosticData {
    uint32_t packetsSent;
    uint32_t packetsReceived;
    uint32_t failedTransmissions;
    uint32_t lastError;
    uint32_t uptime;
    float lastTemperature;
    uint8_t batteryLevel;
};

enum ErrorType {
    ERROR_NONE = 0,
    ERROR_COMMUNICATION = 1,
    ERROR_SENSOR = 2,
    ERROR_BATTERY = 3,
    ERROR_RELAY = 4
};

class DiagnosticManager {
public:
    static DiagnosticManager& getInstance() {
        static DiagnosticManager instance;
        return instance;
    }
    
    void begin();
    void logPacketSent();
    void logPacketReceived();
    void logError(ErrorType error);
    void updateTemperature(float temp);
    void updateBatteryLevel(uint8_t level);
    DiagnosticData getData() const;
    void reset();
    
private:
    DiagnosticManager() : data() {}
    DiagnosticData data;
    static const int EEPROM_ADDR = 100;
    void saveToEEPROM();
    void loadFromEEPROM();
};

#endif 