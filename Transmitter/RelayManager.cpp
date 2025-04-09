#include "RelayManager.h"

RelayManager::RelayManager() : state(false) {}

void RelayManager::begin() {
    // Тут можеш додати ініціалізацію пінів, якщо потрібно
}

void RelayManager::turnOn() {
    state = true;
}

void RelayManager::turnOff() {
    state = false;
}

bool RelayManager::isOn() {
    return state;
}