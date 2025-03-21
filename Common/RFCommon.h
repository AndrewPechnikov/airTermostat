#ifndef RF_COMMON_H
#define RF_COMMON_H

enum CommandType {
    CMD_TURN_ON = 1,
    CMD_TURN_OFF = 2,
    CMD_ACK = 3,
    CMD_ERROR = 4
};

struct Command {
    CommandType type;
    bool success;
};

#endif 