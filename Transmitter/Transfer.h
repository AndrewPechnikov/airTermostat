#ifndef TRANSFER_H
#define TRANSFER_H

#include <SPI.h>
#include "RF24.h"
#include "Config.h"



class Transfer {
public:
    Transfer(uint8_t ce, uint8_t csn, uint8_t irq);
    bool begin();
    bool sendData(uint8_t data);
    uint8_t getData();
    
private:
    RF24 radio;
    uint8_t irqPin;
};

#endif