#ifndef CLOCK_MANAGER_H
#define CLOCK_MANAGER_H

#include <iarduino_RTC.h>

class ClockManager {
private:
    iarduino_RTC rtc;
public:
    ClockManager();
    void begin();
    String getTime();
};

#endif
