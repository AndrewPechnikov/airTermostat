#ifndef TRANSFER_H
#define TRANSFER_H

#include <SPI.h>
#include <RF24.h>
#include "RFCommon.h"

#define SIG_POWER RF24_PA_LOW   // Рівень потужності передачі
#define CH_NUM 0x60             // Номер каналу (96 у десятковій)
#define SIG_SPEED RF24_1MBPS    // Швидкість передачі

class Transfer {
public:
    Transfer(uint8_t ce, uint8_t csn, uint8_t irq);
    bool begin();
    bool sendCommand(const Command& cmd);
    Command getCommand();
    bool getStateRelay();
    void returnRelayState(bool realStateRelay);
    
private:
    RF24 radio;
    uint8_t irqPin;
    uint8_t pipeNo;
    bool received_data;
};

#endif