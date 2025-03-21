#include "DataBuffer.h"
#include <Arduino.h>

void DataBuffer::addData(float temp) {
    TempData data;
    data.temp = temp;
    data.timestamp = millis();
    buffer.push(data);
}

float DataBuffer::getAverageTemp(unsigned long timeWindow) {
    if (buffer.isEmpty()) return 0;
    
    float sum = 0;
    int count = 0;
    unsigned long currentTime = millis();
    
    for (int i = 0; i < buffer.size(); i++) {
        TempData data = buffer[i];
        if (currentTime - data.timestamp <= timeWindow) {
            sum += data.temp;
            count++;
        }
    }
    
    return count > 0 ? sum / count : 0;
}

TempData DataBuffer::getLastData() {
    return buffer.first();
} 