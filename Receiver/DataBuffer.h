#ifndef DATA_BUFFER_H
#define DATA_BUFFER_H

#include <CircularBuffer.h>

struct TempData {
    float temp;
    unsigned long timestamp;
};

class DataBuffer {
public:
    static const int BUFFER_SIZE = 24; // Зберігаємо дані за добу
    void addData(float temp);
    float getAverageTemp(unsigned long timeWindow);
    TempData getLastData();
private:
    CircularBuffer<TempData, BUFFER_SIZE> buffer;
};

#endif 