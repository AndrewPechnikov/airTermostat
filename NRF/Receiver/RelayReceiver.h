#ifndef RELAYRECEIVER_H
#define RELAYRECEIVER_H

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

class RelayReceiver {
public:
    RelayReceiver(uint8_t cePin, uint8_t csnPin, uint64_t rxAddress, uint8_t relayPin);
    void begin();
    void listen();

private:
    RF24 radio;
    uint64_t rxAddr;
    uint8_t relay;

    void activateRelay(bool state);
};

#endif