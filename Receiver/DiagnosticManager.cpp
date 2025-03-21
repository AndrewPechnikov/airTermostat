#include "DiagnosticManager.h"
#include <EEPROM.h>

void DiagnosticManager::begin() {
    loadFromEEPROM();
    data.uptime = 0;
}

void DiagnosticManager::logPacketSent() {
    data.packetsSent++;
    saveToEEPROM();
}

void DiagnosticManager::logPacketReceived() {
    data.packetsReceived++;
    saveToEEPROM();
}

void DiagnosticManager::logError(ErrorType error) {
    data.failedTransmissions++;
    data.lastError = error;
    saveToEEPROM();
}

void DiagnosticManager::updateTemperature(float temp) {
    data.lastTemperature = temp;
    saveToEEPROM();
}

void DiagnosticManager::updateBatteryLevel(uint8_t level) {
    data.batteryLevel = level;
    saveToEEPROM();
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