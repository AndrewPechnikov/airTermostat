#include "SensorConfig.h"
#include "SensorManager.h"
#include "RelayManager.h"
#include "Config.h"
#include "Arduino.h"
#include "RadioManager.h"

// Ініціалізація об'єктів менеджерів
RelayManager relay;
SensorManager sensorManager;    
RadioManager radio ( 9, 10, 0xF0F0F0F0D2LL);

// Масив з двома значеннями, які передаються через радіо
float data[]  = {10, 20};

// Лічильники успішних (successfulTransmissions ) і невдалих (failedTransmissions) передач
int successfulTransmissions = 0;
int failedTransmissions = 0;
unsigned long RSSI_timer;  // Таймер для перевірки рівня сигналу
unsigned long send_timer;
unsigned long controlTemperatureTimer;
int PAUSE_SEND = 1000;
int PAUSE_MONITORING= 1000;
int HYST = 1;
int setTemperature = 25;


void setup() {
    Serial.begin(9600); // Запуск серійного монітору

    relay.begin(); // Ініціалізація реле
    Serial.println(F("Relay begin"));

    radio.begin(); // Ініціалізація NRF модуля
    Serial.println(F("Radio begin"));

    sensorManager.begin(); // Ініціалізація сенсора температури
    Serial.println(F("Sensor begin"));
}
float temperature = 25;
void loop() {







    
    // Надсилання даних через радіо
    if(controlTemperatureTimer + PAUSE_MONITORING < millis()){

         // Генеруємо випадкову зміну від -0.3 до +0.3
        float delta = (random(-50, 51)) / 100.0;

        // Змінюємо температуру
        temperature += delta;

        // Обмежуємо значення в межах 0 - 50
        if (temperature < 0) temperature = 0;
        if (temperature > 50) temperature = 50;


        // float temperature = sensorManager.getTemperature();
        if(temperature - HYST > setTemperature ){
            
            relay.turnOff();
        }
        else{
            relay.turnOn();
        }


        Serial.print("Temperature:");
        Serial.print(temperature, 1); // Один знак після коми
        Serial.print("\t"); // Розділяємо дані пробілом або табуляцією
        Serial.print("RelayState:");
        Serial.println(relay.isOn() ? "40" : "25");
        controlTemperatureTimer = millis();
    }




    

    bool confirmation;
    if(send_timer+PAUSE_SEND < millis()){


        if (radio.sendRelayCommand(relay.isOn(), confirmation)) {

            // Serial.print("Пітдвердження стану вітдаленого реле: ");
            // Serial.println((confirmation == relay.isOn()) ? "Співпадає" : "Не співпадає");
        } else {
            // Serial.println("Failed to get confirmation.");
        }
        send_timer = millis();

    }

    

 

    // Раз на секунду перевіряємо рівень сигналу і зчитуємо температуру
    // if (millis() - RSSI_timer > 1000) {
    //     radio.checkRSSI(successfulTransmissions, failedTransmissions); // Перевірка якості з'єднання
    //     RSSI_timer = millis();

    //     data[0] = sensorManager.getTemperature(); // Отримання температури з датчика
    //     Serial.println(data[0]); // Виведення температури в серійний монітор
    // }
}
