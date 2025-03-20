#ifndef POWER_MANAGER_H
#define POWER_MANAGER_H

#include <avr/sleep.h>
#include <avr/power.h>

class PowerManager {
public:
    void setup();
    void enterSleepMode();
    void wakeUp();
private:
    static void watchdogSetup();
};

#endif 