#include "RelayManager.h"

// Конструктор зі списком ініціалізації
RelayManager::RelayManager(int onPin, int offPin, int statePin, int time) 
    : TIME_FOR_OPERATION_RELAY(time),
      relayPinOn(onPin),
      relayPinOff(offPin),
      stateRelayPin(statePin) {}

void RelayManager::begin() {
    pinMode(relayPinOn, OUTPUT);
    pinMode(relayPinOff, OUTPUT);
    pinMode(stateRelayPin, INPUT);
}

void RelayManager::setState(bool state) {
    digitalWrite(relayPinOn, state ? HIGH : LOW);
    digitalWrite(relayPinOff, !state ? HIGH : LOW);
    delay(TIME_FOR_OPERATION_RELAY);  // Імпульс для активації реле
    digitalWrite(relayPinOn, LOW);    // Вимкнути управляючі сигнали
    digitalWrite(relayPinOff, LOW);
}

bool RelayManager::isRelayIsEnable() {
    return digitalRead(stateRelayPin);  // Читаємо реальний стан з піна
}