#include "EEPROMManager.h"

EEPROMManager::EEPROMManager() {
    // Значення за замовчуванням
    settings.targetTemp = 22.0;
    settings.hysteresis = 1.0;
    settings.scheduleEnabled = false;
    settings.scheduleStartHour = 8;
    settings.scheduleStartMinute = 0;
    settings.scheduleEndHour = 22;
    settings.scheduleEndMinute = 0;
}

void EEPROMManager::begin() {
    loadSettings();
}

void EEPROMManager::saveSettings() {
    EEPROM.put(EEPROM_START_ADDR, settings);
}

void EEPROMManager::loadSettings() {
    EEPROM.get(EEPROM_START_ADDR, settings);
}

void EEPROMManager::setTargetTemp(float temp) {
    settings.targetTemp = temp;
    saveSettings();
}

float EEPROMManager::getTargetTemp() const {
    return settings.targetTemp;
}

void EEPROMManager::setHysteresis(float hyst) {
    settings.hysteresis = hyst;
    saveSettings();
}

float EEPROMManager::getHysteresis() const {
    return settings.hysteresis;
}

void EEPROMManager::setScheduleEnabled(bool enabled) {
    settings.scheduleEnabled = enabled;
    saveSettings();
}

bool EEPROMManager::isScheduleEnabled() const {
    return settings.scheduleEnabled;
}

void EEPROMManager::setScheduleStart(uint8_t hour, uint8_t minute) {
    settings.scheduleStartHour = hour;
    settings.scheduleStartMinute = minute;
    saveSettings();
}

void EEPROMManager::setScheduleEnd(uint8_t hour, uint8_t minute) {
    settings.scheduleEndHour = hour;
    settings.scheduleEndMinute = minute;
    saveSettings();
}

void EEPROMManager::getScheduleStart(uint8_t& hour, uint8_t& minute) const {
    hour = settings.scheduleStartHour;
    minute = settings.scheduleStartMinute;
}

void EEPROMManager::getScheduleEnd(uint8_t& hour, uint8_t& minute) const {
    hour = settings.scheduleEndHour;
    minute = settings.scheduleEndMinute;
} 