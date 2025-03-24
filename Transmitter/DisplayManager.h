#ifndef DISPLAY_MANAGER_H
#define DISPLAY_MANAGER_H

#include <LiquidCrystal.h>
#include "Config.h"

class DisplayManager {
public:
    DisplayManager();
    void begin();
    void updateDisplay(float currentTemp, float targetTemp, bool relayState, float humidity, unsigned long time, unsigned long timeToNextCheck);
    void showError(const char* message);
    void showConfig();
    void noDisplay();
    void display();
    
private:
    void showPage0(float currentTemp, float targetTemp, bool relayState);
    void showPage1(float humidity, unsigned long time);
    void showPage2(unsigned long timeToNextCheck);
    void showPage3();
    
    LiquidCrystal lcd;
    uint8_t currentPage;
};

#endif 