#include "SensorManager.h"

SensorManager::SensorManager(int resist) : temperature(0) {}

void SensorManager::begin() {
    pinMode(NTC_PIN, INPUT); // Ініціалізуємо пін для зчитування
}

void SensorManager::requestTemperature() {
  int raw = 0;
  for (int i = 0; i < SAMPLES; i++)
  {
    raw += analogRead(NTC_PIN);
  }

  raw = raw / SAMPLES;

  float Vread = (VCC / 1023.00) * raw;
  float R_ntc = ((VCC / (VCC - Vread)) -1) * R1;

  float steinhart;
  steinhart = log(R_ntc / R_NTC);
  steinhart = steinhart / B;
  steinhart = steinhart + 1.0 / (NOMINAL_T + KELVIN_T);
  steinhart = 1.0 / steinhart;
  temperature =  steinhart - KELVIN_T;    // келівін -> цельсій
  Serial.println(temperature);
}

float SensorManager::getTemperature() {
    return temperature;
}

bool SensorManager::isDataValid() {
    return !isnan(temperature);
}

bool SensorManager::testSensor() {
    float temp = getCurrentTemperature();
    if (isnan(temp)) {
        return false;
    }
    
    if (temp < -40 || temp > 80) {
        return false;
    }
    
    return true;
}

float SensorManager::getLastReading() {
    return lastTemp;
}