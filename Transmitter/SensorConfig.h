#ifndef SENSOR_CONFIG_H
#define SENSOR_CONFIG_H

// Тип сенсора (виберіть один)
#define TEMP_SENSOR_TYPE DHT11
//#define TEMP_SENSOR_TYPE DS18B20
//#define TEMP_SENSOR_TYPE THERMISTOR

// Налаштування DHT11
#if TEMP_SENSOR_TYPE == DHT11
    #define DHT_PIN 2
    #define DHT_TYPE DHT11
    #define DHT_READ_INTERVAL 2000
#endif

// Налаштування DS18B20
#if TEMP_SENSOR_TYPE == DS18B20
    #define DS18B20_PIN 2
    #define DS18B20_RESOLUTION 12
    #define DS18B20_READ_INTERVAL 2000
#endif

// Налаштування термістора
#if TEMP_SENSOR_TYPE == THERMISTOR
    #define THERMISTOR_PIN 2
    #define THERMISTOR_SERIES_RESISTOR 10000
    #define THERMISTOR_NOMINAL 10000
    #define THERMISTOR_TEMP_NOMINAL 25
    #define THERMISTOR_BETA_COEFFICIENT 3950
    #define THERMISTOR_READ_INTERVAL 1000
    #define TEMP_FILTER_SAMPLES 5
#endif

#endif 