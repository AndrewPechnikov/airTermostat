#ifndef EEPROM_MANAGER_H
#define EEPROM_MANAGER_H

#include <EEPROM.h>

struct Settings {
    float defaultTemp;
    float nightTemp;
    uint8_t nightStartHour;
    uint8_t nightEndHour;
};

class EEPROMManager {
public:
    void saveSettings(const Settings& settings);
    Settings loadSettings();
    void setDefaults();
private:
    static const int SETTINGS_ADDR = 0;
    static const float DEFAULT_TEMP = 21.0;
    static const float DEFAULT_NIGHT_TEMP = 18.0;
    static const uint8_t DEFAULT_NIGHT_START = 23;
    static const uint8_t DEFAULT_NIGHT_END = 6;
};

#endif 