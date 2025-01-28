#ifndef SENSOR_MANAGER_H
#define SENSOR_MANAGER_H

#include <Arduino.h>

class SensorManager {
private:
    #define NTC_PIN A0
    #define NOMINAL_T 25
    #define KELVIN_T 273.15
    #define R_NTC 10000 // Номінальний резистор термістора
    #define B 3435        // Постійна Бета
    #define VCC 5.0          // Напруга живлення
    #define SAMPLES 20       // Кількість зчитувань
    #define R1 10290

    float temperature;       // Температура в градусах Цельсія
    int sensorPin;           // Пін для термістора

public:
    SensorManager(int resist);  // Конструктор
    void begin();            // Ініціалізація піну
    void requestTemperature(); // Запит на оновлення температури
    bool isDataValid();      // Перевірка валідності даних
    float getTemperature();  // Отримання температури
};

#endif