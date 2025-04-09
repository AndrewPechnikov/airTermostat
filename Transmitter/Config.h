#ifndef CONFIG_H
#define CONFIG_H

// =============================================
// Конфігурація обладнання
// =============================================

// Вимкнення/вмикання компонентів
#define ENABLE_RELAY         1   // Реле для керування нагрівачем
#define ENABLE_RTC           1   // Модуль реального часу DS3231
#define ENABLE_NRF24         1   // Радіомодуль nRF24L01
#define ENABLE_TEMPERATURE_SENSOR        1   // Датчик температури DHT22
#define ENABLE_LCD           1   // LCD дисплей
#define ENABLE_LED           1   // Світлодіод для індикації
#define ENABLE_BUTTONS       1   // Кнопки керування
#define ENABLE_EEPROM        1   // Збереження налаштувань в EEPROM
#define ENABLE_DIAGNOSTICS   1   // Система діагностики
#define ENABLE_POWER_MANAGER 1   // Менеджер живлення
#define ENABLE_NOTIFICATIONS 1   // Система сповіщень

// =============================================
// Піни для компонентів
// =============================================

// Реле
#define PIN_RELAY_ON         7   // Пін для керування реле on
#define PIN_RELAY_OFF        8   // Пін для керування реле off

// nRF24L01
#define PIN_CE               9   // Пін CE для nRF24L01
#define PIN_CSN              10  // Пін CSN для nRF24L01
#define PIN_IRQ              3   // Пін IRQ для nRF24L01

// DHT22
#define PIN_DHT              A0  // Пін для датчика температури
#define DHT_TYPE            DHT22  // Тип датчика DHT22

// LCD
#define PIN_LCD_RS           6   // Пін RS для LCD
#define PIN_LCD_EN           7   // Пін EN для LCD
#define PIN_LCD_D4           8   // Пін D4 для LCD
#define PIN_LCD_D5           9   // Пін D5 для LCD
#define PIN_LCD_D6           10  // Пін D6 для LCD
#define PIN_LCD_D7           11  // Пін D7 для LCD

// Кнопки
#define PIN_BTN_UP           3   // Кнопка збільшення температури
#define PIN_BTN_DOWN         4   // Кнопка зменшення температури
#define PIN_BTN_MODE         5   // Кнопка зміни режиму

// LED
#define PIN_LED              8   // Вбудований LED

// =============================================
// Налаштування системи
// =============================================

// Радіо

#define TIME_BETWEEN_ATTEMPT_TRANSFER 0
#define NUM_ATTEMPT_TRANSFER 15
#define SIZE_PACK            32
#define RADIO_CHANNEL        0x60  // Канал радіо
#define RADIO_PA_LEVEL       RF24_PA_MIN // Потужність передачі
#define RADIO_DATA_RATE      RF24_1MBPS // Швидкість передачі

// Температура
#define TEMP_HYSTERESIS      1.0  // Гістерезис температури
#define MIN_TEMP             5.0  // Мінімальна температура
#define MAX_TEMP             30.0 // Максимальна температура
#define DEFAULT_TARGET_TEMP  21.0 // Температура за замовчуванням

// Живлення
#define BATTERY_LOW          20   // Поріг низького заряду (%)
#define BATTERY_CRITICAL     10   // Критичний заряд (%)
#define SLEEP_INTERVAL       3000  // Інтервал сну (5 хвилин)
#define WAKEUP_INTERVAL      3000  // Інтервал пробудження (5 хвилин)

// Таймери
#define MEASURE_INTERVAL     3000  // Інтервал вимірювання (5 хвилин)
#define DISPLAY_TIMEOUT      10000   // Час вимкнення дисплея (30 секунд)
#define DISPLAY_UPDATE_INTERVAL 1000 // Інтервал оновлення дисплея (1 секунда)

// =============================================
// Діагностика
// =============================================

#if ENABLE_DIAGNOSTICS
    #define DIAG_EEPROM_ADDR     100  // Адреса в EEPROM для діагностики
    #define DIAG_LOG_INTERVAL     60000  // Інтервал логування (1 хвилина)
#endif

// Коди помилок
#define ERROR_COMMUNICATION 1

#endif // CONFIG_H 