#include "RelayManager.h"

RelayManager::RelayManager(int pin) : relayPin(pin) {}

void RelayManager::begin() {
    pinMode(relayPin, OUTPUT);
}

void RelayManager::setState(bool state) {
    digitalWrite(relayPin, state ? HIGH : LOW);
}
