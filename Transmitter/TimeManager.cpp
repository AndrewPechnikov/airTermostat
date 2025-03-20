#include "TimeManager.h"

void TimeManager::setup() {
    if (!rtc.begin()) {
        Serial.println(F("Помилка ініціалізації RTC!"));
        return;
    }
    settings = eeprom.loadSettings();
}

float TimeManager::getTargetTemperature() {
    return isNightTime() ? settings.nightTemp : settings.defaultTemp;
}

bool TimeManager::isNightTime() {
    DateTime now = rtc.now();
    uint8_t currentHour = now.hour();
    
    if (settings.nightStartHour < settings.nightEndHour) {
        return currentHour >= settings.nightStartHour && 
               currentHour < settings.nightEndHour;
    } else {
        return currentHour >= settings.nightStartHour || 
               currentHour < settings.nightEndHour;
    }
} 