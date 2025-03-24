#include "Transfer.h"
#include "Arduino.h"
#include "RF24.h"

Transfer::Transfer(uint8_t ce, uint8_t csn, uint8_t irq) : 
    radio(ce, csn), 
    irqPin(irq) 
{
}

bool Transfer::begin() {
    radio.begin();
    radio.setPayloadSize(sizeof(uint8_t));
    radio.setPALevel(RF24_PA_HIGH);
    radio.setDataRate(RF24_250KBPS);
    radio.openReadingPipe(0, 0xF0F0F0F0E1LL);
    radio.openWritingPipe(0xF0F0F0F0D2LL);
    radio.startListening();
    return true;
}

bool Transfer::sendData(uint8_t data) {
    radio.stopListening();
    bool result = radio.write(&data, sizeof(data));
    radio.startListening();
    return result;
}

uint8_t Transfer::getData() {
    uint8_t data;
    radio.read(&data, sizeof(data));
    return data;
} 