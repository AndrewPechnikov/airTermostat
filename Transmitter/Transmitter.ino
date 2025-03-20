// Transmitter.ino
// #include <SPI.h>
// #include <nRF24L01.h>
// #include <RF24.h>
#include "SensorManager.h"
#include "DisplayManager.h"
#include "ClockManager.h"
#include "RFCommon.h"
#include "Transfer.h"
#include "PowerManager.h"
#include "TimeManager.h"
#include "NotificationManager.h"
#include "EEPROMManager.h"

// #define CE_PIN 9
// #define CSN_PIN 10

// RF24 radio(CE_PIN, CSN_PIN);
SensorManager sensor(A0);
DisplayManager display(6, 7, 8, 9, 10, 11);
ClockManager clock;
Transfer postman;

PowerManager powerManager;
TimeManager timeManager;
NotificationManager notificationManager;
EEPROMManager eepromManager;

float setPoint = 22.0;
bool relayState = false;

void setup() {
    Serial.begin(9600);
    sensor.begin();
    display.begin();
    clock.begin();
    postman.begin();
    powerManager.setup();
    timeManager.setup();
    notificationManager.setup();
    
    // Завантаження налаштувань
    Settings settings = eepromManager.loadSettings();
    Serial.println("Transmitter ready");
}

void loop() {
    static unsigned long lastUpdate = 0;
    
    if (millis() - lastUpdate >= UPDATE_INTERVAL) {
        float currentTemp = sensor.getCurrentTemperature();
        float targetTemp = timeManager.getTargetTemperature();
        
        if (abs(currentTemp - targetTemp) > MAX_TEMP_DIFFERENCE) {
            notificationManager.notify(TEMP_TOO_HIGH);
        }
        
        if (!postman.sendData(currentTemp, targetTemp)) {
            notificationManager.notify(CONNECTION_LOST);
        }
        
        lastUpdate = millis();
        powerManager.enterSleepMode();
    }
}
