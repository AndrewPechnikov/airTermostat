#ifndef SENSOR_CONFIG_H
#define SENSOR_CONFIG_H

// =============================================
// Вибір датчика температури
// =============================================
#define TEMP_SENSOR_TYPE NONE  // NONE, DHT22, DS18B20, THERMISTOR

// =============================================
// Налаштування DHT22
// =============================================
#if TEMP_SENSOR_TYPE == DHT22
    #define DHT_PIN A0
    #define DHT_TYPE DHT22
    #define DHT_READ_INTERVAL 2000  // Мінімальний інтервал між зчитуваннями (мс)
#endif

// =============================================
// Налаштування DS18B20
// =============================================
#if TEMP_SENSOR_TYPE == DS18B20
    #define DS18B20_PIN 2
    #define DS18B20_RESOLUTION 12  // Розрядність (9-12)
    #define DS18B20_READ_INTERVAL 750  // Мінімальний інтервал між зчитуваннями (мс)
#endif

// =============================================
// Налаштування термістора
// =============================================
#if TEMP_SENSOR_TYPE == THERMISTOR
    #define THERMISTOR_PIN A0
    #define THERMISTOR_SERIES_RESISTOR 10000  // Опір послідовного резистора (Ом)
    #define THERMISTOR_NOMINAL 10000  // Номінальний опір термістора (Ом)
    #define THERMISTOR_TEMP_NOMINAL 25  // Температура при номінальному опорі (°C)
    #define THERMISTOR_BETA_COEFFICIENT 3950  // Бета-коефіцієнт термістора
    #define THERMISTOR_READ_INTERVAL 100  // Мінімальний інтервал між зчитуваннями (мс)
#endif

// =============================================
// Загальні налаштування
// =============================================
#define TEMP_READ_TIMEOUT 1000  // Таймаут на зчитування (мс)
#define TEMP_ERROR_VALUE -999.9  // Значення помилки
#define TEMP_FILTER_SAMPLES 5  // Кількість зчитувань для фільтрації

#endif // SENSOR_CONFIG_H 