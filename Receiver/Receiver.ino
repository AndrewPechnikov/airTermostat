#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include "RelayManager.h"
#include "Transfer.h"

// Конфігурація пінів
const int PIN_RELAY_ON = 5;
const int PIN_RELAY_OFF = 6;
const int PIN_STATE_RELAY = 7;
const int TIME_FOR_OPERATION_RELAY = 50;

const int CE_PIN = 9;
const int CS_PIN = 10;

RelayManager relay(PIN_RELAY_ON, PIN_RELAY_OFF, PIN_STATE_RELAY, TIME_FOR_OPERATION_RELAY);
Transfer radio(CE_PIN, CS_PIN);

bool relayState;

void setup() {
    Serial.begin(9600);
    relay.begin();
    radio.begin();
    Serial.println("Receiver ready");
}

void loop() {
    relayState = radio.getStateRelay();  // Отримати стан від передавача
    
    if (relay.isRelayIsEnable() != relayState) {
        relay.setState(relayState);      // Синхронізувати стан реле
    }
    
    radio.returnRelayState(relay.isRelayIsEnable());  // Відправити актуальний стан
    delay(100);
}