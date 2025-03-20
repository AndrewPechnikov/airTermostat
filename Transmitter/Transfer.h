#ifndef TRANSFER_H
#define TRANSFER_H

#include <RF24.h>
#include "RFCommon.h"

class Transfer {
public:
    Transfer(uint8_t ce_pin = 9, uint8_t csn_pin = 10, uint8_t irq_pin = 2);
    void begin();
    bool sendData(float currentTemp, float targetTemp);
    static void handleIRQ();
    
private:
    RF24 radio;
    uint8_t irq_pin;
    volatile static bool txComplete;
    void setupIRQ();
};

#endif