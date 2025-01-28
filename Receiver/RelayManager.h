#ifndef RELAY_MANAGER_H
#define RELAY_MANAGER_H

#include <Arduino.h>

class RelayManager {
private:
    const int TIME_FOR_OPERATION_RELAY;  // Константа часу активації реле
    int relayPinOn;                      // Пін для включення реле
    int relayPinOff;                     // Пін для виключення реле
    int stateRelayPin;                   // Пін для читання стану реле
    // bool realStateRelay; // Видаліть - не використовується

public:
    RelayManager(int onPin, int offPin, int statePin, int time);
    void begin();
    void setState(bool state);
    bool isRelayIsEnable();
};

#endif