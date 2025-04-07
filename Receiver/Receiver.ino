#include "RelayManager.h"



RelayManager relay(PIN_RELAY_ON, PIN_RELAY_OFF);

void setup() {
    relay.begin();
}

