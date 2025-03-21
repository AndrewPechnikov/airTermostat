#include <DHT.h>
#include "Config.h"
#include "SensorConfig.h"

DHT dht(PIN_DHT, DHT_TYPE);
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
    logInfo(F("Starting Sensor Test..."));
    
    // Ініціалізація датчика
    dht.begin();
    logSuccess(F("Sensor initialized"));
    
    // Тест зчитування температури
    logInfo(F("Testing temperature reading..."));
    float temp = dht.readTemperature();
    if (isnan(temp)) {
        logError(F("Failed to read temperature!"));
        return;
    }
    logSuccess(F("Temperature reading successful"));
    Serial.print(F("Temperature: "));
    Serial.print(temp);
    Serial.println(F("°C"));
    
    // Тест зчитування вологості
    logInfo(F("Testing humidity reading..."));
    float humidity = dht.readHumidity();
    if (isnan(humidity)) {
        logError(F("Failed to read humidity!"));
        return;
    }
    logSuccess(F("Humidity reading successful"));
    Serial.print(F("Humidity: "));
    Serial.print(humidity);
    Serial.println(F("%"));
    
    // Тест діапазону температури
    logInfo(F("Testing temperature range..."));
    if (temp < -40.0 || temp > 80.0) {
        logError(F("Temperature out of valid range!"));
        return;
    }
    logSuccess(F("Temperature within valid range"));
    
    // Тест діапазону вологості
    logInfo(F("Testing humidity range..."));
    if (humidity < 0.0 || humidity > 100.0) {
        logError(F("Humidity out of valid range!"));
        return;
    }
    logSuccess(F("Humidity within valid range"));
    
    // Тест стабільності показань
    logInfo(F("Testing reading stability..."));
    float temp2 = dht.readTemperature();
    float humidity2 = dht.readHumidity();
    
    if (abs(temp2 - temp) > 1.0) {
        logError(F("Temperature reading unstable!"));
        return;
    }
    if (abs(humidity2 - humidity) > 1.0) {
        logError(F("Humidity reading unstable!"));
        return;
    }
    logSuccess(F("Readings stable"));
    
    // Тест швидкості відгуку
    logInfo(F("Testing response time..."));
    unsigned long startTime = millis();
    dht.readTemperature();
    unsigned long responseTime = millis() - startTime;
    
    if (responseTime > 2000) {
        logError(F("Sensor response time too slow!"));
        return;
    }
    logSuccess(F("Response time acceptable"));
    
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