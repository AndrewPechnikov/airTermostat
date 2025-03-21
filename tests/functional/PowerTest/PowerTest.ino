#include "Config.h"
#include "PowerManager.h"
#include "Transfer.h"
#include "SensorManager.h"

#if ENABLE_POWER_MANAGER
PowerManager powerManager;
#endif

#if ENABLE_NRF24
Transfer radio(PIN_CE, PIN_CSN, PIN_IRQ);
#endif

#if ENABLE_DHT22
SensorManager sensor(PIN_DHT);
#endif

void setup() {
    Serial.begin(9600);
    Serial.println(F("Starting Power Management Test..."));
    
    #if ENABLE_POWER_MANAGER
    powerManager.setup();
    #endif
    
    #if ENABLE_NRF24
    radio.begin();
    #endif
    
    #if ENABLE_DHT24
    sensor.begin();
    #endif
}

void loop() {
    #if ENABLE_POWER_MANAGER
    // Тест рівня заряду
    uint8_t batteryLevel = powerManager.getBatteryLevel();
    Serial.print(F("Battery level: "));
    Serial.print(batteryLevel);
    Serial.println(F("%"));
    
    // Перевірка порогів
    if (batteryLevel <= BATTERY_CRITICAL) {
        Serial.println(F("CRITICAL: Battery level critical!"));
    } else if (batteryLevel <= BATTERY_LOW) {
        Serial.println(F("WARNING: Battery level low!"));
    }
    
    // Тест режимів сну
    Serial.println(F("\nTesting sleep modes..."));
    
    // Легкий сон
    Serial.println(F("Entering light sleep..."));
    powerManager.enterLightSleep();
    Serial.println(F("Woke up from light sleep"));
    
    // Глибокий сон
    Serial.println(F("Entering deep sleep..."));
    powerManager.enterDeepSleep(5000); // 5 секунд
    Serial.println(F("Woke up from deep sleep"));
    
    // Тест споживання енергії
    Serial.println(F("\nMeasuring power consumption..."));
    float current = powerManager.measureCurrent();
    Serial.print(F("Current consumption: "));
    Serial.print(current);
    Serial.println(F("mA"));
    #else
    Serial.println(F("ERROR: Power management is disabled in Config.h"));
    #endif
    
    delay(5000);
} 