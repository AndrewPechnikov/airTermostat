#include "RelayManager.h"

RelayManager::RelayManager() :  state(false) {
}

void RelayManager::begin() {
    
}

void RelayManager::turnOn() {
    state = true;
}

void RelayManager::turnOff() {
    state = false;
}

bool RelayManager::isOn() const {
    return state;
} 