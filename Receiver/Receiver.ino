
// Receiver.ino
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include "RelayManager.h"
#include "RFCommon.h"

#define CE_PIN 9
#define CSN_PIN 10

RF24 radio(CE_PIN, CSN_PIN);
RelayManager relay(7);
bool relayState = false;

void setup() {
    Serial.begin(BAUD_RATE);
    radio.begin();
    radio.openReadingPipe(0, RF_ADDRESS);
    radio.setPALevel(RF24_PA_LOW);
    radio.startListening();
    relay.begin();
    Serial.println("Receiver ready");
}

void loop() {
    if (radio.available()) {
        radio.read(&relayState, sizeof(relayState));
        relay.setState(relayState);
    }
    delay(100);
}
