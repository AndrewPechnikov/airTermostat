#include "RelayReceiver.h"

RelayReceiver::RelayReceiver(uint8_t cePin, uint8_t csnPin, uint64_t rxAddress, uint8_t relayPin)
    : radio(cePin, csnPin), rxAddr(rxAddress), relay(relayPin) {}

void RelayReceiver::begin() {
    pinMode(relay, OUTPUT);
    digitalWrite(relay, LOW);

    radio.begin();
    radio.setPALevel(RF24_PA_LOW);
    radio.setDataRate(RF24_1MBPS);
    radio.enableAckPayload();
    radio.openReadingPipe(1, rxAddr);
    radio.startListening();
}

void RelayReceiver::listen() {
    if (radio.available()) {
        bool command;
        radio.read(&command, sizeof(command));
        activateRelay(command);
        radio.writeAckPayload(1, &command, sizeof(command));
    }
}

void RelayReceiver::activateRelay(bool state) {
    digitalWrite(relay, state ? HIGH : LOW);
}