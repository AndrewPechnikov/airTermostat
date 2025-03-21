#include "DisplayManager.h"

DisplayManager::DisplayManager() : 
    lcd(PIN_LCD_RS, PIN_LCD_EN, PIN_LCD_D4, PIN_LCD_D5, PIN_LCD_D6, PIN_LCD_D7),
    currentPage(0)
{
}

void DisplayManager::begin() {
    lcd.begin(16, 2);
    lcd.print(F("Initializing..."));
}

void DisplayManager::updateDisplay(float currentTemp, float targetTemp, bool relayState, 
                                 float humidity, unsigned long time, unsigned long nextCheck) {
    lcd.clear();
    
    switch(currentPage) {
        case 0:
            showPage0(currentTemp, targetTemp);
            break;
        case 1:
            showPage1(relayState, humidity);
            break;
        case 2:
            showPage2(time, nextCheck);
            break;
        case 3:
            showPage3();
            break;
    }
    
    currentPage = (currentPage + 1) % DISPLAY_PAGES;
}

void DisplayManager::showPage0(float currentTemp, float targetTemp) {
    lcd.print(F("Temp: "));
    lcd.print(currentTemp, 1);
    lcd.print(F("C"));
    lcd.setCursor(0, 1);
    lcd.print(F("Target: "));
    lcd.print(targetTemp, 1);
    lcd.print(F("C"));
}

void DisplayManager::showPage1(bool relayState, float humidity) {
    lcd.print(F("Relay: "));
    lcd.print(relayState ? "ON" : "OFF");
    lcd.setCursor(0, 1);
    lcd.print(F("Humidity: "));
    lcd.print(humidity, 1);
    lcd.print(F("%"));
}

void DisplayManager::showPage2(unsigned long time, unsigned long nextCheck) {
    lcd.print(F("Time: "));
    lcd.print(time / 1000);
    lcd.print(F("s"));
    lcd.setCursor(0, 1);
    lcd.print(F("Next check: "));
    lcd.print(nextCheck / 1000);
    lcd.print(F("s"));
}

void DisplayManager::showPage3() {
    lcd.print(F("System Status"));
    lcd.setCursor(0, 1);
    lcd.print(F("Running..."));
}

void DisplayManager::showError(const char* message) {
    lcd.clear();
    lcd.print(F("Error:"));
    lcd.setCursor(0, 1);
    lcd.print(message);
}

void DisplayManager::showConfig(float targetTemp) {
    lcd.clear();
    lcd.print(F("Config Mode"));
    lcd.setCursor(0, 1);
    lcd.print(F("Target: "));
    lcd.print(targetTemp, 1);
    lcd.print(F("C"));
} 