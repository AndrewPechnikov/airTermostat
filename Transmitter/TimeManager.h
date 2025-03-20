#ifndef TIME_MANAGER_H
#define TIME_MANAGER_H

#include <RTClib.h>
#include "EEPROMManager.h"

class TimeManager {
public:
    void setup();
    float getTargetTemperature();
    bool isNightTime();
    void setSchedule(uint8_t nightStart, uint8_t nightEnd);
private:
    RTC_DS3231 rtc;
    Settings settings;
    EEPROMManager eeprom;
};

#endif 