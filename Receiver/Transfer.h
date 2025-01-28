#ifndef TRANSFER_H
#define TRANSFER_H

#include <RF24.h>

#define SIG_POWER RF24_PA_LOW   // Рівень потужності передачі
#define CH_NUM 0x60             // Номер каналу (96 у десятковій)
#define SIG_SPEED RF24_1MBPS    // Швидкість передачі

class Transfer {
private:
    RF24 radio;         // Об'єкт радіомодуля
    uint8_t pipeNo;     // Номер труби для зв'язку
    bool received_data; // Отримані дані

public:
    Transfer(int ce, int cs);
    void begin();
    bool getStateRelay();
    void returnRelayState(bool realStateRelay);
};

#endif