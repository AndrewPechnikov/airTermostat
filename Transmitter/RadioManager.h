#ifndef RADIO_MANAGER_H
#define RADIO_MANAGER_H

#include "Config.h"

#include <RF24.h>


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