#include "Config.h"
#include "TimeManager.h"

TimeManager timeManager;
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
    logInfo(F("Starting Time Management Test..."));
    
    // Тест ініціалізації
    logInfo(F("Testing initialization..."));
    if (!timeManager.begin()) {
        logError(F("Failed to initialize time manager!"));
        return;
    }
    logSuccess(F("Time manager initialized"));
    
    // Тест отримання поточного часу
    logInfo(F("Testing current time..."));
    unsigned long currentTime = timeManager.getCurrentTime();
    if (currentTime == 0) {
        logError(F("Failed to get current time!"));
        return;
    }
    logSuccess(F("Current time retrieved"));
    Serial.print(F("Current Time: "));
    Serial.println(currentTime);
    
    // Тест перевірки часу
    logInfo(F("Testing time check..."));
    if (!timeManager.isTimeToCheck()) {
        logError(F("Time check failed!"));
        return;
    }
    logSuccess(F("Time check successful"));
    
    // Тест отримання цільової температури
    logInfo(F("Testing target temperature..."));
    float targetTemp = timeManager.getTargetTemperature();
    if (targetTemp < 0.0 || targetTemp > 30.0) {
        logError(F("Invalid target temperature!"));
        return;
    }
    logSuccess(F("Target temperature retrieved"));
    Serial.print(F("Target Temperature: "));
    Serial.print(targetTemp);
    Serial.println(F("°C"));
    
    // Тест встановлення цільової температури
    logInfo(F("Testing temperature setting..."));
    if (!timeManager.setTargetTemperature(22.0)) {
        logError(F("Failed to set target temperature!"));
        return;
    }
    logSuccess(F("Target temperature set"));
    
    // Тест таймера
    logInfo(F("Testing timer..."));
    if (!timeManager.startTimer(60)) {
        logError(F("Failed to start timer!"));
        return;
    }
    logSuccess(F("Timer started"));
    
    // Тест перевірки таймера
    if (!timeManager.isTimerActive()) {
        logError(F("Timer not active!"));
        return;
    }
    logSuccess(F("Timer active"));
    
    // Тест скидання таймера
    logInfo(F("Testing timer reset..."));
    if (!timeManager.resetTimer()) {
        logError(F("Failed to reset timer!"));
        return;
    }
    logSuccess(F("Timer reset successful"));
    
    // Тест перевірки режиму
    logInfo(F("Testing mode check..."));
    if (!timeManager.isModeActive()) {
        logError(F("Mode check failed!"));
        return;
    }
    logSuccess(F("Mode check successful"));
    
    // Тест оновлення
    logInfo(F("Testing update function..."));
    if (!timeManager.update()) {
        logError(F("Failed to update time manager!"));
        return;
    }
    logSuccess(F("Update successful"));
    
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