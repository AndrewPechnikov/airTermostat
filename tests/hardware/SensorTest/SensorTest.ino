#include "../../../Transmitter/SensorManager.h"

SensorManager sensor;

void setup() {
    Serial.begin(9600);
    Serial.println(F("Starting Sensor Test..."));
    
    if (sensor.testSensor()) {
        Serial.println(F("Sensor test: PASS"));
        Serial.print(F("Current temperature: "));
        Serial.println(sensor.getLastReading());
    } else {
        Serial.println(F("Sensor test: FAIL"));
    }
}

void loop() {
    // Порожній loop
} 