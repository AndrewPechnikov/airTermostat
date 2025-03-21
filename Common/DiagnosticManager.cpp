#include "DiagnosticManager.h"

DiagnosticManager& DiagnosticManager::getInstance() {
    static DiagnosticManager instance;
    return instance;
}

void DiagnosticManager::begin() {
    Serial.println(F("Diagnostic system initialized"));
    loadFromEEPROM();
    data.uptime = 0;
}

void DiagnosticManager::logPacketSent() {
    packetsSent++;
    Serial.println(F("Packet sent"));
    data.packetsSent++;
    saveToEEPROM();
}

void DiagnosticManager::logPacketReceived() {
    packetsReceived++;
    Serial.println(F("Packet received"));
    data.packetsReceived++;
    saveToEEPROM();
}

void DiagnosticManager::logError(uint8_t errorCode) {
    errors++;
    Serial.print(F("Error: "));
    Serial.println(errorCode);
    data.failedTransmissions++;
    data.lastError = errorCode;
    saveToEEPROM();
}

void DiagnosticManager::updateTemperature(float temp) {
    data.lastTemperature = temp;
}

void DiagnosticManager::updateBatteryLevel(uint8_t level) {
    data.batteryLevel = level;
}

DiagnosticData DiagnosticManager::getData() const {
    return data;
}

void DiagnosticManager::reset() {
    data = DiagnosticData();
    saveToEEPROM();
}

void DiagnosticManager::saveToEEPROM() {
    EEPROM.put(EEPROM_ADDR, data);
}

void DiagnosticManager::loadFromEEPROM() {
    EEPROM.get(EEPROM_ADDR, data);
} 