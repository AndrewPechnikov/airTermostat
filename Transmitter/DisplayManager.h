#ifndef DISPLAY_MANAGER_H
#define DISPLAY_MANAGER_H

#include <Wire.h>
#include <LCD03.h> // Include the I2C LCD library

class DisplayManager {
private:
    LCD03 lcd;  // I2C LCD object

public:
    DisplayManager(int lcdAddr);  // Constructor with I2C address as argument
    void begin();                 // Initialize the display
    void showTemperature(float temperature);   // Display temperature
    void showRelayState(bool state);           // Display relay state (ON/OFF)
    void showError(const char* message);      // Display error message
};

#endif