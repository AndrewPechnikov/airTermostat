#include "NRFRelay.h"

NRFRelay relay(9, 10, 0xF0F0F0F0D2LL);

void setup() {
    Serial.begin(9600);
    relay.begin();
}

void loop() {
    bool desiredState = true;
    bool confirmation = false;

    if (relay.sendRelayCommand(desiredState, confirmation)) {
        Serial.print("Confirmation: ");
        Serial.println(confirmation);
    } else {
        Serial.println("Failed to get confirmation.");
    }

    delay(1000);
}