#include "RelayReceiver.h"

RelayReceiver receiver(9, 10, 0xF0F0F0F0D2LL, 7);

void setup() {
    Serial.begin(9600);
    receiver.begin();
}

void loop() {
    receiver.listen();
}