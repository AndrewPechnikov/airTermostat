#ifndef EEPROM_MANAGER_H
#define EEPROM_MANAGER_H

#include <EEPROM.h>
#include <Arduino.h>

class EEPROMManager {
public:
    static EEPROMManager& getInstance() {
        static EEPROMManager instance;
        return instance;
    }
    
    void begin();
    void saveSettings();
    void loadSettings();
    
    // Налаштування
    void setTargetTemp(float temp);
    float getTargetTemp() const;
    
    void setHysteresis(float hyst);
    float getHysteresis() const;
    
    void setScheduleEnabled(bool enabled);
    bool isScheduleEnabled() const;
    
    void setScheduleStart(uint8_t hour, uint8_t minute);
    void setScheduleEnd(uint8_t hour, uint8_t minute);
    void getScheduleStart(uint8_t& hour, uint8_t& minute) const;
    void getScheduleEnd(uint8_t& hour, uint8_t& minute) const;
    
private:
    EEPROMManager();
    
    // Структура налаштувань
    struct Settings {
        float targetTemp;
        float hysteresis;
        bool scheduleEnabled;
        uint8_t scheduleStartHour;
        uint8_t scheduleStartMinute;
        uint8_t scheduleEndHour;
        uint8_t scheduleEndMinute;
    };
    
    Settings settings;
    
    // Адреси в EEPROM
    static const int EEPROM_START_ADDR = 100; // Починаємо після DiagnosticManager
};

#endif 