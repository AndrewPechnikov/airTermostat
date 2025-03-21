#include "RelayManager.h"

RelayManager::RelayManager(uint8_t pin) : relayPin(pin), state(false) {
}

void RelayManager::begin() {
    pinMode(relayPin, OUTPUT);
    turnOff();
}

void RelayManager::turnOn() {
    digitalWrite(relayPin, HIGH);
    state = true;
}

void RelayManager::turnOff() {
    digitalWrite(relayPin, LOW);
    state = false;
}

bool RelayManager::isOn() const {
    return state;
} 