#include "RadioManager.h"

RadioManager::RadioManager() {
#if ENABLE_NRF24
    radio = RF24(PIN_CE, PIN_CSN);
#endif
}

void RadioManager::begin() {

    if (!radio.begin()) {
        Serial.println(F("RF24 failed!"));
    }
    radio.setChannel(RADIO_CHANNEL);
    radio.setPALevel(RADIO_PA_LEVEL);
    radio.setDataRate(RADIO_DATA_RATE);
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