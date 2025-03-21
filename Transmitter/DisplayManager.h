#ifndef DISPLAY_MANAGER_H
#define DISPLAY_MANAGER_H

#include <LiquidCrystal.h>
#include "Config.h"

class DisplayManager {
public:
    DisplayManager();
    void begin();
    void updateDisplay(float currentTemp, float targetTemp, bool relayState, float humidity, 
                      unsigned long time, unsigned long nextCheck);
    void showError(const char* message);
    void showConfig(float targetTemp);
    void noDisplay() { lcd.noDisplay(); }
    void display() { lcd.display(); }
    
private:
    LiquidCrystal lcd;
    int currentPage;
    void showPage0(float currentTemp, float targetTemp);
    void showPage1(bool relayState, float humidity);
    void showPage2(unsigned long time, unsigned long nextCheck);
    void showPage3();
};

#endif 