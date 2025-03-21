#include "RadioManager.h"

RadioManager::RadioManager() : 
    radio(PIN_CE, PIN_CSN)
{
}

void RadioManager::begin() {
    if (!radio.begin()) {
        Serial.println(F("RF24 failed!"));
        while(1);
    }
    radio.setChannel(RF_CHANNEL);
    radio.setPALevel(RF_PA_LEVEL);
    radio.openWritingPipe(0xF0F0F0F0E1LL);
}

bool RadioManager::sendData(const Data& data) {
    return radio.write(&data, sizeof(Data));
}

void RadioManager::powerDown() {
    radio.powerDown();
}

void RadioManager::powerUp() {
    radio.powerUp();
} 