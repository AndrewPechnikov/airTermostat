// #include "DisplayManager.h"
// #include <Wire.h>
// #include <LCD03.h>  // Include the I2C LCD library

// DisplayManager::DisplayManager(int lcdAddr)
//     : lcd(lcdAddr, 16, 2) {}  // Pass the I2C address and screen size (16x2)

// void DisplayManager::begin() {
//     lcd.begin(16, 2);    // Initialize the LCD
//     lcd.clear();         // Clear the display
// }

// void DisplayManager::showTemperature(float temperature) {
//     lcd.setCursor(0, 0);  // Set the cursor to the first row
//     lcd.print("Temp: ");
//     lcd.print(temperature, 1);  // Print temperature with one decimal
// }

// void DisplayManager::showRelayState(bool state) {
//     lcd.setCursor(0, 1);  // Set the cursor to the second row
//     lcd.print("Relay: ");
//     lcd.print(state ? "ON " : "OFF");  // Print relay state (ON/OFF)
// }

// void DisplayManager::showError(const char* message) {
//     lcd.setCursor(0, 0);  // Set the cursor to the first row
//     lcd.print(message);   // Print error message
// }