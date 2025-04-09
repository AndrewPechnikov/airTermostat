#ifndef NRFRELAY_H
#define NRFRELAY_H

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

class NRFRelay {
public:
    NRFRelay(uint8_t cePin, uint8_t csnPin, uint64_t txAddress);
    void begin();
    bool sendRelayCommand(bool state, bool &confirmation);

private:
    RF24 radio;
    uint64_t txAddr;
};

#endif