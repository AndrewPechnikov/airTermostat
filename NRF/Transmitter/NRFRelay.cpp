#include "NRFRelay.h"

NRFRelay::NRFRelay(uint8_t cePin, uint8_t csnPin, uint64_t txAddress)
    : radio(cePin, csnPin), txAddr(txAddress) {}

void NRFRelay::begin() {
    radio.begin();
    radio.setPALevel(RF24_PA_LOW);
    radio.setDataRate(RF24_1MBPS);
    radio.setRetries(5, 5);
    radio.enableAckPayload();
    radio.openWritingPipe(txAddr);
    radio.stopListening();
}

bool NRFRelay::sendRelayCommand(bool state, bool &confirmation) {
    bool success = radio.write(&state, sizeof(state));
    if (success && radio.isAckPayloadAvailable()) {
        radio.read(&confirmation, sizeof(confirmation));
        return true;
    }
    return false;
}