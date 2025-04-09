#ifndef RELAY_MANAGER_H
#define RELAY_MANAGER_H

#include <Arduino.h>

class RelayManager {
public:
    RelayManager(); // Конструктор
    void begin();
    void turnOn();
    void turnOff();
    bool isOn(); // Повертає стан реле

private:
    bool state; // Внутрішній стан (включено/вимкнено)
};

#endif