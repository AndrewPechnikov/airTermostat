



#include "SensorConfig.h"
#include "Transfer.h"
#include "SensorManager.h"
#include "RelayManager.h"
#include "Config.h"
#include "Arduino.h"




RelayManager relay(PIN_RELAY_ON, PIN_RELAY_OFF);
SensorManager sensorManager;    


void setup() {
    Serial.begin(9600);
    relay.begin();
    Serial.println(F("Transmitter started"));
    sensorManager.begin();
}

void loop() {

    float temperature = sensorManager.getTemperature();
    Serial.println(temperature);
    delay(1000);
}


