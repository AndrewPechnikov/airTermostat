#ifndef TRANSFER
#define TRANSFER

#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"



class Transfer {
private:
RF24 radio;

#define SIG_POWER RF24_PA_LOW
#define CH_NUM 0x60 
#define SIG_SPEED RF24_1MBPS


bool transmit_data = true;    
bool telemetry;         
byte rssi;
int trnsmtd_pack = 1, failed_pack;
unsigned long RSSI_timer;



public:
    Transfer();  // Конструктор
    void begin();            // Ініціалізація піну
    bool isRemoteSwitchEnable(); // Запит на оновлення температури
    void send(bool data);
};

#endif