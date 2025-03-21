#ifndef TRANSFER_H
#define TRANSFER_H

#include <SPI.h>
#include <RF24.h>
#include "RFCommon.h"

class Transfer {
public:
    Transfer(uint8_t ce, uint8_t csn, uint8_t irq);
    bool begin();
    bool sendCommand(const Command& cmd);
    Command getCommand();
    
private:
    RF24 radio;
    uint8_t irqPin;
};

#endif 