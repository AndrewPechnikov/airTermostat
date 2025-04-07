#ifndef RELAY_MANAGER_H
#define RELAY_MANAGER_H

#include <Arduino.h>

class RelayManager {
public:
    RelayManager(uint8_t pin1, uint8_t pin2); // pin1 - реле on, pin2 - реле off
    void begin();
    void turnOn();
    void turnOff();
    bool isOn() const;
    
private:
    uint8_t relayPin1;
    uint8_t relayPin2;
    bool state;
};

#endif 