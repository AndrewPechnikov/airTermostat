#include "../../../Transmitter/Transfer.h"

Transfer radio;

void setup() {
    Serial.begin(9600);
    Serial.println(F("Starting Radio Test..."));
    
    if (radio.testConnection()) {
        Serial.println(F("Radio test: PASS"));
    } else {
        Serial.println(F("Radio test: FAIL"));
    }
}

void loop() {
    // Порожній loop
} 