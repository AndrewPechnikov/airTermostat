#include "../../../Transmitter/PowerManager.h"

PowerManager power;
const unsigned long TEST_DURATION = 10000; // 10 секунд

void setup() {
    Serial.begin(9600);
    Serial.println(F("Starting Power Management Test..."));
    
    if (power.testSleepMode()) {
        Serial.println(F("Sleep mode test: PASS"));
        Serial.print(F("Current consumption: "));
        Serial.print(power.getCurrentConsumption());
        Serial.println(F(" mA"));
    } else {
        Serial.println(F("Sleep mode test: FAIL"));
    }
}

void loop() {
    // Тест 3: Довготривалий тест
    static unsigned long lastCheck = 0;
    if (millis() - lastCheck >= 30000) { // кожні 30 секунд
        Serial.println("Performing long-term power test...");
        power.enterSleepMode();
        Serial.println("Woke up from sleep mode");
        lastCheck = millis();
    }
} 