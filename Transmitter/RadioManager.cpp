#include "RadioManager.h"

RadioManager::RadioManager(uint8_t cePin, uint8_t csnPin, uint64_t txAddress)
    : radio(cePin, csnPin), txAddr(txAddress) {}

void RadioManager::begin() {
    radio.begin();
    radio.setPALevel(RF24_PA_LOW);
    radio.setDataRate(RF24_1MBPS);
    radio.setRetries(5, 5);
    radio.enableAckPayload();
    radio.openWritingPipe(txAddr);
    radio.stopListening();
}

bool RadioManager::sendRelayCommand(bool state, bool &confirmation) {
    bool success = radio.write(&state, sizeof(state));
    if (success && radio.isAckPayloadAvailable()) {
        radio.read(&confirmation, sizeof(confirmation));
        return true;
    }
    return false;
}
