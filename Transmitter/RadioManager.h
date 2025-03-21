#ifndef RADIO_MANAGER_H
#define RADIO_MANAGER_H

#include <RF24.h>
#include "Config.h"

struct Data {
    float temperature;
    float humidity;
    unsigned long timestamp;
    bool relayState;
};

class RadioManager {
public:
    RadioManager();
    void begin();
    bool sendData(const Data& data);
    void powerDown();
    void powerUp();
    
    
private:
    RF24 radio;
};

#endif 