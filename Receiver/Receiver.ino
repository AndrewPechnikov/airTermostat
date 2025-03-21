#include "Config.h"
#include "RelayManager.h"
#include "Transfer.h"
#include "RFCommon.h"
#include "DiagnosticManager.h"
#include <avr/sleep.h>

#if ENABLE_RELAY
RelayManager relay(PIN_RELAY);
#endif

#if ENABLE_NRF24
Transfer radio(PIN_CE, PIN_CSN, PIN_IRQ);
#endif

volatile bool commandReceived = false;

void handleIRQ() {
    commandReceived = true;
}

void setup() {
    Serial.begin(9600);
    
    #if ENABLE_LED
    pinMode(PIN_LED, OUTPUT);
    #endif
    
    #if ENABLE_RELAY
    relay.begin();
    #endif
    
    #if ENABLE_NRF24
    radio.begin();
    #endif
    
    #if ENABLE_DIAGNOSTICS
    DiagnosticManager::getInstance().begin();
    #endif
    
    #if ENABLE_NRF24
    attachInterrupt(digitalPinToInterrupt(PIN_IRQ), handleIRQ, FALLING);
    #endif
    
    Serial.println(F("Receiver ready"));
}

void loop() {
    #if ENABLE_NRF24
    if (commandReceived) {
        Command cmd = radio.getCommand();
        
        #if ENABLE_DIAGNOSTICS
        DiagnosticManager::getInstance().logPacketReceived();
        #endif
        
        bool success = true;
        
        #if ENABLE_RELAY
        switch (cmd.type) {
            case CMD_TURN_ON:
                relay.turnOn();
                #if ENABLE_LED
                digitalWrite(PIN_LED, HIGH);
                #endif
                break;
            case CMD_TURN_OFF:
                relay.turnOff();
                #if ENABLE_LED
                digitalWrite(PIN_LED, LOW);
                #endif
                break;
            case CMD_ERROR:
                Serial.println(F("Error from transmitter"));
                break;
            default:
                success = false;
                break;
        }
        #endif
        
        // Відправляємо підтвердження
        Command ack = {CMD_ACK, success};
        if (radio.sendCommand(ack)) {
            #if ENABLE_DIAGNOSTICS
            DiagnosticManager::getInstance().logPacketSent();
            #endif
        } else {
            #if ENABLE_DIAGNOSTICS
            DiagnosticManager::getInstance().logError((ErrorType)DIAG_ERROR_COMMUNICATION);
            #endif
        }
        
        commandReceived = false;
    }
    #endif
    
    // Спимо поки не прийде команда
    set_sleep_mode(SLEEP_MODE_PWR_DOWN);
    sleep_enable();
    sleep_mode();
    sleep_disable();
}