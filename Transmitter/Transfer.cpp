#include "Transfer.h"


Transfer::Transfer() : radio(9, 10) {}  
void Transfer::begin() {
  byte address[][6] = {"1Node", "2Node", "3Node", "4Node", "5Node", "6Node"};
  radio.begin();                      // активировать модуль
  radio.setAutoAck(1);                // режим подтверждения приёма, 1 вкл 0 выкл
  radio.setRetries(0, 15);            // (время между попыткой достучаться, число попыток)
  radio.enableAckPayload();           // разрешить отсылку данных в ответ на входящий сигнал
  radio.setPayloadSize(32);           // размер пакета, в байтах
  radio.openWritingPipe(address[0]);  // мы - труба 0, открываем канал для передачи данных
  radio.setChannel(CH_NUM);           // выбираем канал (в котором нет шумов!)
  radio.setPALevel(SIG_POWER);        // уровень мощности передатчика
  radio.setDataRate(SIG_SPEED);       // скорость обмена
  // должна быть одинакова на приёмнике и передатчике!
  // при самой низкой скорости имеем самую высокую чувствительность и дальность!!

  radio.powerUp();        // начать работу
  radio.stopListening();  // не слушаем радиоэфир, мы передатчик
}


void Transfer::send(bool data) {
  // забиваем transmit_data данными, для примера



  // отправка пакета transmit_data
  if (radio.write(&transmit_data, sizeof(transmit_data))) {
    trnsmtd_pack++;
    if (!radio.available()) {  // если получаем пустой ответ
    } else {
      while (radio.available()) {                   // если в ответе что-то есть
        radio.read(&telemetry, sizeof(telemetry));  // читаем
        // получили забитый данными массив telemetry ответа от приёмника
      }
    }
  } else {
    failed_pack++;
  }

  if (millis() - RSSI_timer > 1000) {  // таймер RSSI
    // расчёт качества связи (0 - 100%) на основе числа ошибок и числа успешных передач
    rssi = (1 - ((float)failed_pack / trnsmtd_pack)) * 100;

    // сбросить значения
    failed_pack = 0;
    trnsmtd_pack = 0;
    RSSI_timer = millis();
  }
}

bool Transfer::isRemoteSwitchEnable() {

  return telemetry;
}
