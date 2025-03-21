#include "Transfer.h"

Transfer::Transfer(uint8_t ce, uint8_t csn, uint8_t irq) : 
    radio(ce, csn), 
    irqPin(irq) 
{
}

bool Transfer::begin() {
    radio.begin();
    radio.setPayloadSize(sizeof(Command));
    radio.setPALevel(RF24_PA_HIGH);
    radio.setDataRate(RF24_250KBPS);
    radio.openReadingPipe(0, 0xF0F0F0F0E1LL);
    radio.openWritingPipe(0xF0F0F0F0D2LL);
    radio.startListening();
    return true;
}

bool Transfer::sendCommand(const Command& cmd) {
    radio.stopListening();
    bool result = radio.write(&cmd, sizeof(Command));
    radio.startListening();
    return result;
}

Command Transfer::getCommand() {
    Command cmd;
    radio.read(&cmd, sizeof(Command));
    return cmd;
} 