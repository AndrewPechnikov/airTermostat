#include "TimeManager.h"
#include "Config.h"

TimeManager::TimeManager() : 
    lastCheckTime(0),
    targetTemperature(DEFAULT_TARGET_TEMP)
{
}

void TimeManager::begin() {
    lastCheckTime = millis();
}

unsigned long TimeManager::getCurrentTime() {
    return millis();
}

void TimeManager::setTargetTemperature(float temp) {
    targetTemperature = temp;
}

float TimeManager::getTargetTemperature() const {
    return targetTemperature;
}

bool TimeManager::isTimeToCheck() {
    return (millis() - lastCheckTime >= WAKEUP_INTERVAL);
}

void TimeManager::resetCheckTimer() {
    lastCheckTime = millis();
} 

unsigned long TimeManager::getLastCheckTime() {
    return lastCheckTime ;
}