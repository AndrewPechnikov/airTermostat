#ifndef RF_COMMON_H
#define RF_COMMON_H

#include <Arduino.h>

const byte RF_ADDRESS[6] = "00001";
const float HYST_CONST = 1.0;
const int BAUD_RATE = 9600;

enum CommandType {
    CMD_TURN_ON = 1,
    CMD_TURN_OFF = 2,
    CMD_ACK = 3
};

struct Command {
    CommandType type;
    bool success;
};

#endif
