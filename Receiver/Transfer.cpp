#include "Transfer.h"

Transfer::Transfer(int ce, int cs) : radio(ce, cs) {}

void Transfer::begin() {
    byte address[][6] = {"1Node"};  // Адреса для зв'язку

    radio.begin();
    radio.setAutoAck(true);
    radio.setRetries(0, 15);
    radio.enableAckPayload();
    radio.setPayloadSize(32);
    radio.openReadingPipe(1, address[0]);
    radio.setChannel(CH_NUM);
    radio.setPALevel(SIG_POWER);
    radio.setDataRate(SIG_SPEED);
    radio.powerUp();
    radio.startListening();
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