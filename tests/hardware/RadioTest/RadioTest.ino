#include <SPI.h>
#include <RF24.h>
#include "Config.h"
#include "RadioManager.h"

RadioManager radio;
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
    logInfo(F("Starting Radio Test..."));
    
    // Ініціалізація радіомодуля
    if (!radio.begin()) {
        logError(F("Radio hardware not responding!"));
        return;
    }
    logSuccess(F("Radio hardware initialized"));
    
    // Налаштування радіомодуля
    radio.setPayloadSize(sizeof(Data));
    radio.setPALevel(RF24_PA_LOW);
    radio.setDataRate(RF24_250KBPS);
    logSuccess(F("Radio configuration applied"));
    
    // Тестова передача
    Data testData;
    testData.temperature = 25.5;
    testData.humidity = 60.0;
    testData.timestamp = millis();
    testData.relayState = true;
    
    if (!radio.sendData(testData)) {
        logError(F("Failed to send test data"));
        return;
    }
    logSuccess(F("Test data sent successfully"));
    
    // Тест режимів живлення
    logInfo(F("Testing power modes..."));
    radio.powerDown();
    delay(100);
    if (radio.isPowered()) {
        logError(F("Failed to enter power down mode"));
        return;
    }
    logSuccess(F("Entered power down mode"));
    
    radio.powerUp();
    delay(100);
    if (!radio.isPowered()) {
        logError(F("Failed to enter power up mode"));
        return;
    }
    logSuccess(F("Entered power up mode"));
    
    // Тест каналу
    uint8_t channel = radio.getChannel();
    if (channel < 0 || channel > 125) {
        logError(F("Invalid radio channel"));
        return;
    }
    logSuccess(F("Radio channel verified"));
    
    // Тест потужності
    uint8_t powerLevel = radio.getPALevel();
    if (powerLevel != RF24_PA_LOW) {
        logError(F("Invalid power level"));
        return;
    }
    logSuccess(F("Power level verified"));
    
    // Тест швидкості передачі
    uint8_t dataRate = radio.getDataRate();
    if (dataRate != RF24_250KBPS) {
        logError(F("Invalid data rate"));
        return;
    }
    logSuccess(F("Data rate verified"));
    
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