#include "../../Transmitter/SensorManager.h"
#include "../../Transmitter/DisplayManager.h"
#include "../../Transmitter/Transfer.h"
#include "../../Transmitter/PowerManager.h"

SensorManager sensor;
DisplayManager display;
Transfer transfer;
PowerManager powerManager;

void setup() {
    Serial.begin(9600);
    Serial.println("Starting System Integration Test...");
    
    // Тест 1: Ініціалізація всіх компонентів
    Serial.println("Test 1 - Component Initialization:");
    
    if (!sensor.begin()) {
        Serial.println("FAIL - Sensor init failed");
        return;
    }
    Serial.println("Sensor: PASS");
    
    if (!display.begin()) {
        Serial.println("FAIL - Display init failed");
        return;
    }
    Serial.println("Display: PASS");
    
    if (!transfer.begin()) {
        Serial.println("FAIL - Radio init failed");
        return;
    }
    Serial.println("Radio: PASS");
    
    powerManager.setup();
    Serial.println("Power Manager: PASS");
}

void loop() {
    // Тест 2: Повний цикл роботи
    static unsigned long lastCheck = 0;
    if (millis() - lastCheck >= 5000) {
        Serial.println("\nRunning full system cycle test:");
        
        // Зчитування температури
        float temp = sensor.getCurrentTemperature();
        Serial.print("Temperature reading: ");
        Serial.println(temp);
        
        // Відображення на дисплеї
        display.showTemperature(temp);
        Serial.println("Display update: OK");
        
        // Передача даних
        if (transfer.sendData(temp, 22.0)) {
            Serial.println("Data transmission: OK");
        } else {
            Serial.println("Data transmission: FAIL");
        }
        
        // Режим сну
        Serial.println("Entering sleep mode...");
        powerManager.enterSleepMode();
        Serial.println("Woke up from sleep mode");
        
        lastCheck = millis();
    }
} 