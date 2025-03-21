#include "Config.h"
#include "PowerManager.h"

PowerManager powerManager;
bool testPassed = false;
String errorMessage = "";

void logError(const char* message) {
    Serial.print(F("ERROR: "));
    Serial.println(message);
    errorMessage = message;
    testPassed = false;
}

void logInfo(const char* message) {
    Serial.print(F("INFO: "));
    Serial.println(message);
}

void logSuccess(const char* message) {
    Serial.print(F("SUCCESS: "));
    Serial.println(message);
}

void setup() {
    Serial.begin(9600);
    logInfo(F("Starting Power Management Test..."));
    
    // Тест ініціалізації
    logInfo(F("Testing initialization..."));
    if (!powerManager.begin()) {
        logError(F("Failed to initialize power manager!"));
        return;
    }
    logSuccess(F("Power manager initialized"));
    
    // Тест режиму сну
    logInfo(F("Testing sleep mode..."));
    if (!powerManager.enterSleepMode(5)) {
        logError(F("Failed to enter sleep mode!"));
        return;
    }
    logSuccess(F("Sleep mode test successful"));
    
    // Тест рівня батареї
    logInfo(F("Testing battery level..."));
    float batteryLevel = powerManager.getBatteryLevel();
    if (batteryLevel < 0.0 || batteryLevel > 100.0) {
        logError(F("Invalid battery level reading!"));
        return;
    }
    logSuccess(F("Battery level reading successful"));
    Serial.print(F("Battery Level: "));
    Serial.print(batteryLevel);
    Serial.println(F("%"));
    
    // Тест споживання струму
    logInfo(F("Testing current consumption..."));
    float current = powerManager.getCurrentConsumption();
    if (current < 0.0) {
        logError(F("Invalid current consumption reading!"));
        return;
    }
    logSuccess(F("Current consumption reading successful"));
    Serial.print(F("Current Consumption: "));
    Serial.print(current);
    Serial.println(F("mA"));
    
    // Тест режиму енергозбереження
    logInfo(F("Testing power saving mode..."));
    if (!powerManager.enablePowerSaving()) {
        logError(F("Failed to enable power saving mode!"));
        return;
    }
    logSuccess(F("Power saving mode enabled"));
    
    // Тест вимкнення режиму енергозбереження
    if (!powerManager.disablePowerSaving()) {
        logError(F("Failed to disable power saving mode!"));
        return;
    }
    logSuccess(F("Power saving mode disabled"));
    
    // Тест перевірки стану живлення
    logInfo(F("Testing power state check..."));
    if (!powerManager.checkPowerState()) {
        logError(F("Power state check failed!"));
        return;
    }
    logSuccess(F("Power state check successful"));
    
    // Тест перевірки критичного рівня батареї
    logInfo(F("Testing critical battery level check..."));
    if (batteryLevel < 20.0) {
        logInfo(F("Warning: Battery level is critical!"));
    }
    
    logInfo(F("Test completed"));
    logInfo(F("Result: ") + String(testPassed ? F("PASSED") : F("FAILED")));
    if (!testPassed) {
        logInfo(F("Error: ") + errorMessage);
    }
}

void loop() {
    // Тест завершено
    while(1) {
        digitalWrite(LED_BUILTIN, testPassed);
        delay(1000);
        digitalWrite(LED_BUILTIN, !testPassed);
        delay(1000);
    }
} 