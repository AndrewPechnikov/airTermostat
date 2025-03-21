#ifndef RELAY_MANAGER_H
#define RELAY_MANAGER_H

#include <Arduino.h>

class RelayManager {
public:
    RelayManager(uint8_t pin);
    void begin();
    void turnOn();
    void turnOff();
    bool isOn() const;
    
private:
    uint8_t relayPin;
    bool state;
};

#endif 