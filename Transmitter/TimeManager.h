#ifndef TIME_MANAGER_H
#define TIME_MANAGER_H

#include <Arduino.h>

class TimeManager {
public:
    TimeManager();
    void begin();
    unsigned long getCurrentTime();
    unsigned long getLastCheckTime();
    void setTargetTemperature(float temp);
    float getTargetTemperature() const;

    bool isTimeToCheck();
    void resetCheckTimer();
    
private:
    unsigned long lastCheckTime;
    float targetTemperature;
};

#endif 