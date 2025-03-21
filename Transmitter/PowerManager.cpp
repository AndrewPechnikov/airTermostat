#include "PowerManager.h"
#include "Config.h"

PowerManager::PowerManager() : lastWakeTime(0) {
}

void PowerManager::begin() {
    lastWakeTime = millis();
}

void PowerManager::enterSleep() {
    set_sleep_mode(SLEEP_MODE_PWR_DOWN);
    sleep_enable();
    sleep_mode();
    sleep_disable();
}

void PowerManager::wakeUp() {
    lastWakeTime = millis();
}

bool PowerManager::isTimeToSleep() {
    return (millis() - lastWakeTime >= SLEEP_INTERVAL);
} 