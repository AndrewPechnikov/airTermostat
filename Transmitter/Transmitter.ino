
// Transmitter.ino
// #include <SPI.h>
// #include <nRF24L01.h>
// #include <RF24.h>
#include "SensorManager.h"
// #include "DisplayManager.h"
// #include "ClockManager.h"
// #include "RFCommon.h"
// #include "Transfer.h"

// #define CE_PIN 9
// #define CSN_PIN 10

// RF24 radio(CE_PIN, CSN_PIN);
SensorManager sensor(A0);
// DisplayManager display(6, 7, 8, 9, 10, 11);
// ClockManager clock;
// Transfer postman;

float setPoint = 22.0;
bool relayState = false;

void setup() {
    Serial.begin(9600);
    sensor.begin();
    // display.begin();
    // clock.begin();
    // postman.begin();
    Serial.println("Transmitter ready");
}

void loop() {
    sensor.requestTemperature();
    delay(500);
    if (sensor.isDataValid()) {
        float temperature = sensor.getTemperature();
        Serial.println(temperature);
        // display.showTemperature(temperature);
        // if (temperature < setPoint - HYST_CONST) {
        //     relayState = true;
        //     postman.send(relayState);
            
        // } else if (temperature > setPoint) {
        //     relayState = false;
        //     postman.send(relayState);
        // }
        // if(postman.isRemoteSwitchEnable()==relayState){
        //     display.showRelayState(relayState);
        // }
        
    } else {
      Serial.println("Sensor error");
        // display.showError("Sensor Error");
    }
    delay(1000);
}
