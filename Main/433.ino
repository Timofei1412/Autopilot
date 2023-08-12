#include <Gyver433.h>
Gyver433_RX<Radio433Pin, 30> rx;  // указали пин и размер буфера

// формат пакета для приёма (такой же как отправляется)
struct DataPack {
  float ax;
  float ay;
  float az;
  float speed;
};

void getSig() {
  if (rx.tick()) {
    DataPack data;            // "буферная" структура
    if (rx.readData(data)) {  // переписываем данные в неё
      rTx = data.ax;
      rTy = data.ay;
      rTz = data.az;
      Ts = data.speed;
    } else {
      Serial.println("Wrong data");
    }
  }
}


