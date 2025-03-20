#include "Transfer.h"

volatile bool Transfer::txComplete = false;

Transfer::Transfer(uint8_t ce_pin, uint8_t csn_pin, uint8_t irq_pin) 
    : radio(ce_pin, csn_pin), irq_pin(irq_pin) {}

void Transfer::begin() {
    radio.begin();
    radio.setChannel(76);
    radio.setDataRate(RF24_250KBPS);
    radio.setPALevel(RF24_PA_MAX);
    radio.enableDynamicPayloads();
    radio.setRetries(5, 15);
    radio.openWritingPipe(RF_ADDRESS);
    
    // Налаштування IRQ
    setupIRQ();
    radio.maskIRQ(false, true, true); // маскуємо всі IRQ крім TX_DS
}

void Transfer::setupIRQ() {
    pinMode(irq_pin, INPUT);
    attachInterrupt(digitalPinToInterrupt(irq_pin), handleIRQ, FALLING);
}

void Transfer::handleIRQ() {
    txComplete = true;
}

bool Transfer::sendData(float currentTemp, float targetTemp) {
    txComplete = false;
    
    Data data;
    data.currentTemp = currentTemp;
    data.targetTemp = targetTemp;
    
    radio.stopListening();
    radio.write(&data, sizeof(Data));
    
    // Чекаємо на переривання замість активного очікування
    unsigned long started_waiting_at = millis();
    while (!txComplete && (millis() - started_waiting_at < 500)) {
        // Входимо в режим сну на короткий час
        set_sleep_mode(SLEEP_MODE_IDLE);
        sleep_mode();
    }
    
    bool success = txComplete;
    
    if (success) {
        uint8_t pipe;
        if (radio.available(&pipe)) {
            AckData ackData;
            radio.read(&ackData, sizeof(AckData));
        }
    }
    
    return success;
}

bool Transfer::testConnection() {
    if (!radio.begin()) {
        return false;
    }
    
    // Тест базових налаштувань
    radio.setChannel(76);
    if (radio.getChannel() != 76) {
        return false;
    }
    
    // Тест потужності
    radio.setPALevel(RF24_PA_MAX);
    if (radio.getPALevel() != RF24_PA_MAX) {
        return false;
    }
    
    return true;
}
