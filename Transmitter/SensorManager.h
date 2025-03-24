#include "SensorConfig.h"
#include <OneWire.h>
#include <DallasTemperature.h>

class SensorManager {
public:
    SensorManager();
    void begin();
    float getTemperature();
private:
    OneWire oneWire;
    DallasTemperature sensors;
};