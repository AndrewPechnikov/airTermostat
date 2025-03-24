#include "SensorManager.h"

SensorManager::SensorManager() : oneWire(DS18B20_PIN), sensors(&oneWire) {
}

void SensorManager::begin() {

    sensors.begin();

}

float SensorManager::getTemperature() {
    sensors.requestTemperatures();
    return sensors.getTempCByIndex(0);

}



