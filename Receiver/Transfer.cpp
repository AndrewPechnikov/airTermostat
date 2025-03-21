#include "Transfer.h"

Transfer::Transfer(uint8_t ce, uint8_t csn, uint8_t irq) : 
    radio(ce, csn), 
    irqPin(irq),
    pipeNo(0),
    received_data(false)
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

bool Transfer::getStateRelay() {
    if (radio.available(&pipeNo)) {  // Перевірка наявності даних
        radio.read(&received_data, sizeof(received_data));
        return received_data;
    }
    return false;  // Повертаємо false, якщо даних немає
}

void Transfer::returnRelayState(bool realStateRelay) {
    radio.writeAckPayload(pipeNo, &realStateRelay, sizeof(realStateRelay));
}