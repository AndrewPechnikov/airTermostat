#ifndef POWER_MANAGER_H
#define POWER_MANAGER_H

#include <avr/sleep.h>
#include <avr/wdt.h>
#include <avr/interrupt.h>
#include <avr/power.h>
#include <Arduino.h>

class PowerManager {
public:
    static PowerManager& getInstance() {
        static PowerManager instance;
        return instance;
    }
    
    void setup();
    void begin();
    void enterSleepMode();
    void wakeUp();
    void enterLightSleep();
    bool testSleepMode();
    float getBatteryLevel();
    float getCurrentConsumption();
    
    static void watchdogSetup();
    static void watchdogReset();

    bool isTimeToSleep();
    
    // Нові методи
    void enterDeepSleep(unsigned long duration);
    void setupWatchdog(unsigned long timeout);
    bool isLowBattery();
    void enterSleep();
    unsigned long lastWakeTime;

    
private:
    PowerManager();
    bool isLowPowerMode;
    uint8_t batteryLevel;
    float currentConsumption;
    
    void setupADC();
    uint16_t readADC(uint8_t pin);
    
    static void watchdogDisable();
    static void watchdogEnable();
    
    static const uint8_t BATTERY_LOW_THRESHOLD = 20; // 20%
    static const uint8_t BATTERY_CRITICAL_THRESHOLD = 10; // 10%
};

#endif