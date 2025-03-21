#include "Config.h"
#include "DisplayManager.h"

DisplayManager display;
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
    logInfo(F("Starting Display Test..."));
    
    // Тест ініціалізації
    logInfo(F("Testing initialization..."));
    if (!display.begin()) {
        logError(F("Failed to initialize display!"));
        return;
    }
    logSuccess(F("Display initialized"));
    
    // Тест відображення тексту
    logInfo(F("Testing text display..."));
    if (!display.showText(F("Test Text"))) {
        logError(F("Failed to display text!"));
        return;
    }
    logSuccess(F("Text display successful"));
    delay(1000);
    
    // Тест режимів відображення
    logInfo(F("Testing display modes..."));
    
    // Режим температури
    if (!display.setMode(DISPLAY_MODE_TEMP)) {
        logError(F("Failed to set temperature mode!"));
        return;
    }
    logSuccess(F("Temperature mode set"));
    delay(1000);
    
    // Режим налаштувань
    if (!display.setMode(DISPLAY_MODE_CONFIG)) {
        logError(F("Failed to set config mode!"));
        return;
    }
    logSuccess(F("Config mode set"));
    delay(1000);
    
    // Тест відображення помилок
    logInfo(F("Testing error display..."));
    if (!display.showError(F("Test Error"))) {
        logError(F("Failed to display error!"));
        return;
    }
    logSuccess(F("Error display successful"));
    delay(1000);
    
    // Тест відображення налаштувань
    logInfo(F("Testing config display..."));
    if (!display.showConfig(21.5, 22.0, 23.0)) {
        logError(F("Failed to display config!"));
        return;
    }
    logSuccess(F("Config display successful"));
    delay(1000);
    
    // Тест яскравості
    logInfo(F("Testing brightness control..."));
    for (uint8_t brightness = 0; brightness <= 255; brightness += 51) {
        if (!display.setBrightness(brightness)) {
            logError(F("Failed to set brightness!"));
            return;
        }
        delay(500);
    }
    logSuccess(F("Brightness control successful"));
    
    // Тест очищення
    logInfo(F("Testing clear function..."));
    if (!display.clear()) {
        logError(F("Failed to clear display!"));
        return;
    }
    logSuccess(F("Clear function successful"));
    
    // Тест оновлення
    logInfo(F("Testing update function..."));
    if (!display.update()) {
        logError(F("Failed to update display!"));
        return;
    }
    logSuccess(F("Update function successful"));
    
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