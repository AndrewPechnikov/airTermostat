#include <SPI.h>
#include <DHT.h>
#include "Config.h"
#include "DisplayManager.h"
#include "TimeManager.h"
#include "RadioManager.h"
#include "PowerManager.h"

// Ініціалізація об'єктів
DHT dht(PIN_DHT, DHT_TYPE);
DisplayManager display;
TimeManager time;
RadioManager radio;
PowerManager& power = PowerManager::getInstance();

// Глобальні змінні
float currentTemp = 0;
bool relayState = false;
unsigned long lastDisplayUpdate = 0;

void setup() {
    Serial.begin(9600);
    
    // Ініціалізація об'єктів
    dht.begin();
    display.begin();
    time.begin();
    radio.begin();
    power.begin();
    
    Serial.println(F("Transmitter ready"));
}

void loop() {
    // Перевірка температури та керування реле
    if (time.isTimeToCheck()) {
        float temp = dht.readTemperature();
        if (!isnan(temp)) {
            currentTemp = temp;
            
            // Логіка керування реле
            if (temp > time.getTargetTemperature() + TEMP_HYSTERESIS) {
                relayState = false;
            } else if (temp < time.getTargetTemperature() - TEMP_HYSTERESIS) {
                relayState = true;
            }
            
            // Відправка даних
            Data data;
            data.temperature = temp;
            data.humidity = dht.readHumidity();
            data.timestamp = time.getCurrentTime();
            data.relayState = relayState;
            
            if (radio.sendData(data)) {
                Serial.print(F("Sent: Temp="));
                Serial.print(temp);
                Serial.print(F("C, Relay="));
                Serial.println(relayState ? "ON" : "OFF");
            }
        }
        
        time.resetCheckTimer();
    }
    
    // Оновлення дисплея
    if (time.getCurrentTime() - lastDisplayUpdate >= DISPLAY_UPDATE_INTERVAL) {
        display.updateDisplay(
            currentTemp,
            time.getTargetTemperature(),
            relayState,
            dht.readHumidity(),
            time.getCurrentTime(),
            WAKEUP_INTERVAL - (time.getCurrentTime() - time.getLastCheckTime())
        );
        lastDisplayUpdate = time.getCurrentTime();
    }
    
    // Режим сну
    if (power.isTimeToSleep()) {
        display.noDisplay();
        radio.powerDown();
        power.enterSleep();
        radio.powerUp();
        display.display();
        power.wakeUp();
    }
}
