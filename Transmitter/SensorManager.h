#ifndef SENSOR_MANAGER_H
#define SENSOR_MANAGER_H

#include <DHT.h>

class SensorManager {
public:
    SensorManager(uint8_t pin = 2);
    bool begin();
    float getCurrentTemperature();
    bool testSensor();        // Новий метод для тестування
    float getLastReading();   // Новий метод для тестування
    
private:
    DHT dht;
    float lastTemp;
};

#endif