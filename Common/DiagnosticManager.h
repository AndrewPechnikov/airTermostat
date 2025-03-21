#ifndef DIAGNOSTIC_MANAGER_H
#define DIAGNOSTIC_MANAGER_H

#include <Arduino.h>

class DiagnosticManager {
public:
    static DiagnosticManager& getInstance();
    
    void begin();
    void logPacketReceived();
    void logPacketSent();
    void logError(uint8_t errorCode);
    
private:
    DiagnosticManager() = default;
    DiagnosticManager(const DiagnosticManager&) = delete;
    DiagnosticManager& operator=(const DiagnosticManager&) = delete;
    
    unsigned long packetsReceived = 0;
    unsigned long packetsSent = 0;
    unsigned long errors = 0;
};

#endif 