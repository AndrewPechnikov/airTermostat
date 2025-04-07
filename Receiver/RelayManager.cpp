#include "RelayManager.h"

RelayManager::RelayManager(uint8_t pin1, uint8_t pin2) : relayPin1(pin1), relayPin2(pin2), state(false) {
}

void RelayManager::begin() {
    pinMode(relayPin1, OUTPUT); // реле on
    pinMode(relayPin2, OUTPUT); // реле off
    digitalWrite(relayPin1, LOW);
    digitalWrite(relayPin2, HIGH);
}

void RelayManager::turnOn() {
    digitalWrite(relayPin2, LOW);
    delay(100);
    digitalWrite(relayPin1, HIGH);
    
    state = true;
}

void RelayManager::turnOff() {
    digitalWrite(relayPin1, LOW);
    delay(100);
    digitalWrite(relayPin2, HIGH);
    state = false;
}

bool RelayManager::isOn() const {
    return state;
} 