#ifndef POWER_MANAGER_H
#define POWER_MANAGER_H

#include <avr/sleep.h>
#include <avr/power.h>

class PowerManager {
public:
    void setup();
    void enterSleepMode();
    void wakeUp();
    void enterLightSleep();
    bool testSleepMode();
    float getCurrentConsumption();
private:
    static void watchdogSetup();
};

#endif 