#ifndef NOTIFICATION_MANAGER_H
#define NOTIFICATION_MANAGER_H

enum NotificationType {
    TEMP_TOO_HIGH,
    TEMP_TOO_LOW,
    CONNECTION_LOST,
    SENSOR_ERROR,
    BATTERY_LOW
};

class NotificationManager {
public:
    void setup();
    void notify(NotificationType type);
    void clearNotification();
private:
    void sendSerialNotification(const char* message);
    void activateBuzzer();
    static const int BUZZER_PIN = 8;
};

#endif 