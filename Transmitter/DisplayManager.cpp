#include "DisplayManager.h"

DisplayManager::DisplayManager() : 
    lcd(PIN_LCD_RS, PIN_LCD_EN, PIN_LCD_D4, PIN_LCD_D5, PIN_LCD_D6, PIN_LCD_D7),
    currentPage(0)
{
}

void DisplayManager::begin() {
    lcd.begin(16, 2);
    lcd.clear();
}

void DisplayManager::updateDisplay(float currentTemp, float targetTemp, bool relayState, float humidity, unsigned long time, unsigned long timeToNextCheck) {
    switch(currentPage) {
        case 0:
            showPage0(currentTemp, targetTemp, relayState);
            break;
        case 1:
            showPage1(humidity, time);
            break;
        case 2:
            showPage2(timeToNextCheck);
            break;
        case 3:
            showPage3();
            break;
    }
}

void DisplayManager::showError(const char* message) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Error:");
    lcd.setCursor(0, 1);
    lcd.print(message);
}

void DisplayManager::showConfig() {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Config");
}

void DisplayManager::noDisplay() {
    lcd.noDisplay();
}

void DisplayManager::display() {
    lcd.display();
}

void DisplayManager::showPage0(float currentTemp, float targetTemp, bool relayState) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Temp: ");
    lcd.print(currentTemp, 1);
    lcd.print("C");
    lcd.setCursor(0, 1);
    lcd.print("Target: ");
    lcd.print(targetTemp, 1);
    lcd.print("C ");
    lcd.print(relayState ? "ON" : "OFF");
}

void DisplayManager::showPage1(float humidity, unsigned long time) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Humidity: ");
    lcd.print(humidity, 1);
    lcd.print("%");
    lcd.setCursor(0, 1);
    lcd.print("Time: ");
    lcd.print(time);
}

void DisplayManager::showPage2(unsigned long timeToNextCheck) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Next check in:");
    lcd.setCursor(0, 1);
    lcd.print(timeToNextCheck);
    lcd.print("s");
}

void DisplayManager::showPage3() {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("AirTermostat");
    lcd.setCursor(0, 1);
    lcd.print("v1.0");
} 