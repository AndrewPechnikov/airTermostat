#include <SPI.h>
#include <DHT.h>
#include "Config.h"
#include "SensorConfig.h"
#include "DisplayManager.h"
#include "TimeManager.h"
#include "RadioManager.h"
#include "PowerManager.h"

// Ініціалізація об'єктів
DHT dht(PIN_DHT, DHT_TYPE);
DisplayManager display;
TimeManager timeManager;
RadioManager radio;
PowerManager powerManager;

bool testPassed = false;
String errorMessage = "";
unsigned long testStartTime = 0;
unsigned long testDuration = 0;

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
    logInfo(F("Starting System Integration Test..."));
    testStartTime = millis();
    
    // Ініціалізація компонентів
    logInfo(F("Initializing components..."));
    
    // Ініціалізація датчика
    dht.begin();
    logSuccess(F("Sensor initialized"));
    
    // Ініціалізація дисплея
    if (!display.begin()) {
        logError(F("Failed to initialize display!"));
        return;
    }
    logSuccess(F("Display initialized"));
    
    // Ініціалізація менеджера часу
    if (!timeManager.begin()) {
        logError(F("Failed to initialize time manager!"));
        return;
    }
    logSuccess(F("Time manager initialized"));
    
    // Ініціалізація радіо
    if (!radio.begin()) {
        logError(F("Failed to initialize radio!"));
        return;
    }
    logSuccess(F("Radio initialized"));
    
    // Ініціалізація менеджера живлення
    if (!powerManager.begin()) {
        logError(F("Failed to initialize power manager!"));
        return;
    }
    logSuccess(F("Power manager initialized"));
    
    // Тест вимірювання температури
    logInfo(F("Testing temperature measurement..."));
    float temp = dht.readTemperature();
    if (isnan(temp)) {
        logError(F("Failed to read temperature!"));
        return;
    }
    logSuccess(F("Temperature reading successful"));
    Serial.print(F("Temperature: "));
    Serial.print(temp);
    Serial.println(F("°C"));
    
    // Тест оновлення дисплея
    logInfo(F("Testing display update..."));
    if (!display.updateDisplay(temp, 22.0, true, 60.0, 0, 30)) {
        logError(F("Failed to update display!"));
        return;
    }
    logSuccess(F("Display updated successfully"));
    
    // Тест передачі даних
    logInfo(F("Testing data transmission..."));
    Data data;
    data.temperature = temp;
    data.humidity = dht.readHumidity();
    data.timestamp = timeManager.getCurrentTime();
    data.relayState = true;
    
    if (!radio.sendData(data)) {
        logError(F("Failed to send data!"));
        return;
    }
    logSuccess(F("Data sent successfully"));
    
    // Тест режиму сну
    logInfo(F("Testing sleep mode..."));
    if (!powerManager.enterSleepMode(5)) {
        logError(F("Failed to enter sleep mode!"));
        return;
    }
    logSuccess(F("Sleep mode test successful"));
    
    // Тест перевірки часу
    logInfo(F("Testing time check..."));
    if (!timeManager.isTimeToCheck()) {
        logError(F("Time check failed!"));
        return;
    }
    logSuccess(F("Time check successful"));
    
    // Тест рівня батареї
    logInfo(F("Testing battery level..."));
    float batteryLevel = powerManager.getBatteryLevel();
    if (batteryLevel < 0.0 || batteryLevel > 100.0) {
        logError(F("Invalid battery level!"));
        return;
    }
    logSuccess(F("Battery level check successful"));
    Serial.print(F("Battery Level: "));
    Serial.print(batteryLevel);
    Serial.println(F("%"));
    
    // Вимірювання тривалості тесту
    testDuration = millis() - testStartTime;
    logInfo(F("Test duration: ") + String(testDuration) + F("ms"));
    
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