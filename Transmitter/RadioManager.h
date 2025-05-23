#ifndef RADIOMANAGER_H
#define RADIOMANAGER_H

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

class RadioManager {
public:
    RadioManager(uint8_t cePin, uint8_t csnPin, uint64_t txAddress);
    void begin();
    bool sendRelayCommand(bool state, bool &confirmation);

private:
    RF24 radio;
    uint64_t txAddr;
};

#endif