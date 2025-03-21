#ifndef CONFIG_H
#define CONFIG_H

// Піни
#define PIN_CE 9
#define PIN_CSN 10
#define PIN_IRQ 2
#define PIN_DHT 3
#define PIN_LCD_RS 4
#define PIN_LCD_EN 5
#define PIN_LCD_D4 6
#define PIN_LCD_D5 7
#define PIN_LCD_D6 8
#define PIN_LCD_D7 9

// Налаштування nRF24L01
#define RF_CHANNEL 76
#define RF_PA_LEVEL RF24_PA_HIGH

// Налаштування DHT22
#define DHT_TYPE DHT22
#define DHT_READ_INTERVAL 2000

// Налаштування дисплея
#define DISPLAY_UPDATE_INTERVAL 300000 // 5 хвилин
#define DISPLAY_PAGES 4 // Кількість сторінок на дисплеї

// Налаштування температури
#define TEMP_HYSTERESIS 0.5 // Гістерезис температури
#define DEFAULT_TARGET_TEMP 20.0 // Температура за замовчуванням

// Налаштування енергозбереження
#define SLEEP_INTERVAL 300000 // 5 хвилин
#define WAKEUP_INTERVAL 300000 // 5 хвилин

#endif 