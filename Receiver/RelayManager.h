#ifndef RELAY_MANAGER_H
#define RELAY_MANAGER_H

#include <Arduino.h>

class RelayManager {
private:
    int relayPin;
public:
    RelayManager(int pin);
    void begin();
    void setState(bool state);
};

#endif
